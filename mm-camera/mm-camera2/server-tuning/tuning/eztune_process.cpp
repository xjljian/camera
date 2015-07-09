/*******************************************************************************
* Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
*******************************************************************************/

//=============================================================================
/**
 * This file contains eztune process class implementation
 */
//=============================================================================

#include <string.h>
#include <stddef.h>
#include <errno.h>

#include "eztune.h"
#include "chromatix.h"
#include "chromatix_common.h"
#include "eztune_cam_adapter.h"
#include "eztune_process.h"

#ifdef _ANDROID_
#include <log/log.h>
#endif
#include "mmcam_log_utils.h"

extern "C" eztune_item_t eztune_get_item (int i);
extern "C" void eztune_change_item(eztune_item_t *item, eztune_set_val_t *item_data, eztune_t *ezctrl);
extern "C" int eztune_get_diagnostic_item(eztune_t *ezctrl, char *output_buf,
        int offset, eztune_parms_list_t id, uint16_t table_index);
extern "C" int eztune_get_af_item(eztune_t *ezctrl, char *output_buf, int offset,
                                  eztune_parms_list_t id, uint16_t table_index);

namespace eztune {
const char kImgTransInfoMajorVersion = 1;
const char kImgTransInfoMinorVersion = 0;
const uint16_t kImgTransInfoHeaderSize = 6;
const char kImgTransInfoTargetType = 1; //Linux
const char kImgTransInfoCapabilities = 0x1 | 0x2; //Preview | JPEG
const uint16_t kPreviewInfoChunkSize = 7168;
const uint16_t kPreviewMaxChunkSize = 10240;

const uint8_t kChunkStatusSuccess = 0;
const uint8_t kChunkStatusNewSize = 2;

static std::map<eztune_item_data_t, size_t> kEzTypeToSizeMapping;

typedef bool (ProcessLayer::*ProcessFunction)(size_t payload_size, string &payload, size_t &response_size, string &response);
typedef std::map<uint16_t, ProcessFunction> ProcessCmdMap;

static ProcessCmdMap kCmdToFunctionMap;

typedef enum {
    EZTUNE_ORIGIN_TOP_LEFT = 1,
    EZTUNE_ORIGIN_BOTTOM_LEFT,
    EZTUNE_ORIGIN_INVALID
} EztuneImgOriginType;

enum class TuneCmd : uint16_t {
    TUNESERVER_GET_PREVIEW_INFO = 1,
    TUNESERVER_CHANGE_CHUNK_SIZE = 2,
    TUNESERVER_GETPREVIEW_FRAME = 3,
    TUNESERVER_GETSNAPSHOT_FRAME = 4,
    TUNESERVER_GET_LIST = 1014,
    TUNESERVER_GET_PARMS = 1015,
    TUNESERVER_SET_PARMS = 1016,
    TUNESERVER_MISC_CMDS = 1021,
};

typedef struct {
    uint8_t status;
    uint16_t width;
    uint16_t height;
    uint8_t format;
    uint8_t origin;
    uint32_t frame_size;
} PreviewFrameHeader;

typedef struct  {
    uint8_t major_ver;
    uint8_t minor_ver;
} PreviewInfoVersion;

typedef struct  {
    uint16_t header_size;
    uint8_t target_type;
    uint8_t capabilities;
    uint32_t chunk_size;
} PreviewInfoHeader;

//Define below macro to enable preview frame dumps in a file for debug
//#define DEBUG_FILE_DUMP
#ifdef DEBUG_FILE_DUMP
#define DUMP_FILE_NAME "/data/process_img.yuv"
static int32_t file_fd = -1;

//only opens file one time, if file exits will not open
void debug_open_dump_file()
{
    if (access(DUMP_FILE_NAME, F_OK) != -1) {
        file_fd = -1;
    } else {
        file_fd = open(DUMP_FILE_NAME, O_RDWR | O_CREAT, 0777);
        if (file_fd < 0)
            MMCAM_LOGI("File open error: %s",  strerror(errno));
    }
}

void debug_close_dump_file()
{
    if (file_fd >= 0)
        close(file_fd);
}

void debug_write_dump_file(char *ptr, uint32_t size)
{
    if (file_fd >= 0)
        write(file_fd, ptr,  size);
}
#else //DEBUG_FILE_DUMP
void debug_open_dump_file() {}
void debug_close_dump_file() {}
void debug_write_dump_file(char *ptr, uint32_t size) {}
#endif //DEBUG_FILE_DUMP

//Define below macro to enable eztune params dump in a file for debug
//#define DEBUG_EZTUNE_PARAMS
#ifdef DEBUG_EZTUNE_PARAMS

#define DUMP_FILE_NAME "/data/eztune_params.txt"
static FILE *params_file_fp = 0;

//only opens file one time, if file exits will not open
void debug_open_paramsdump_file()
{
    params_file_fp = fopen(DUMP_FILE_NAME, "w+");
    if (!params_file_fp)
        MMCAM_LOGI("File open error: %s",  strerror(errno));
}

void debug_close_paramsdump_file()
{
    if (params_file_fp)
        fclose(params_file_fp);
}

#define debug_write_paramsdump_file(...) (\
{ \
    if (params_file_fp) \
        fprintf(params_file_fp, __VA_ARGS__); \
} \
)

#else //DEBUG_EZTUNE_PARAMS

void debug_open_paramsdump_file() {}
void debug_close_paramsdump_file() {}
void debug_write_paramsdump_file(...) {}
#endif //DEBUG_EZTUNE_PARAMS

ProcessLayer::ProcessLayer(void *camera_adapter_handle)
{
    //Register processing function for all eazytune cmds
    kCmdToFunctionMap[(uint16_t)TuneCmd::TUNESERVER_GET_LIST] = &ProcessLayer::ProcessGetListCmd;
    kCmdToFunctionMap[(uint16_t)TuneCmd::TUNESERVER_GET_PARMS] = &ProcessLayer::ProcessGetParamCmd;
    kCmdToFunctionMap[(uint16_t)TuneCmd::TUNESERVER_SET_PARMS] = &ProcessLayer::ProcessSetParamCmd;
    kCmdToFunctionMap[(uint16_t)TuneCmd::TUNESERVER_MISC_CMDS] = &ProcessLayer::ProcessMiscCmd;

    kCmdToFunctionMap[(uint16_t)TuneCmd::TUNESERVER_GET_PREVIEW_INFO] = &ProcessLayer::ProcessImgTransInfo;
    kCmdToFunctionMap[(uint16_t)TuneCmd::TUNESERVER_CHANGE_CHUNK_SIZE] = &ProcessLayer::ProcessChangeChunkSize;
    kCmdToFunctionMap[(uint16_t)TuneCmd::TUNESERVER_GETPREVIEW_FRAME] = &ProcessLayer::ProcessGetPreviewFrame;
    kCmdToFunctionMap[(uint16_t)TuneCmd::TUNESERVER_GETSNAPSHOT_FRAME] = &ProcessLayer::ProcessGetSnapshotFrame;

    //Add all eztune size to actual sizes here
    kEzTypeToSizeMapping[EZT_D_FLOAT] = sizeof(float);
    kEzTypeToSizeMapping[EZT_D_INT8] = sizeof(int8_t);
    kEzTypeToSizeMapping[EZT_D_INT16] = sizeof(int16_t);
    kEzTypeToSizeMapping[EZT_D_INT32] = sizeof(int32_t);
    kEzTypeToSizeMapping[EZT_D_UINT8] = sizeof(uint8_t);
    kEzTypeToSizeMapping[EZT_D_UINT16] = sizeof(uint16_t);
    kEzTypeToSizeMapping[EZT_D_UINT32] = sizeof(uint32_t);
    kEzTypeToSizeMapping[EZT_D_DOUBLE] = sizeof(double);

    //rest of the initialization
    m_init_done = false;
    m_items_added = 0;
    m_pending_set_param_apply = false;

    m_pending_preview_send_size = 0;
    m_pending_snapshot_send_size = 0;
    m_preview_header_sent = false;
    m_snapshot_header_sent = false;
    m_chunk_size = kPreviewInfoChunkSize;

    m_pending_cmds = new std::vector<eztune_set_val_t>;

    m_cam_adapter = new eztune::CamAdapter(camera_adapter_handle);
}

ProcessLayer::~ProcessLayer()
{
    delete m_cam_adapter;

    std::vector<eztune_set_val_t> *pending_cmds = (std::vector<eztune_set_val_t> *)m_pending_cmds;
    delete pending_cmds;
}

bool ProcessLayer::ProcessAndGenerateResponse(uint16_t cmd, size_t payload_size, string &payload, size_t &response_size, string &response)
{
    bool rc = true;

    ProcessCmdMap::const_iterator function = kCmdToFunctionMap.find(cmd);

    if (function == kCmdToFunctionMap.end()) {
        response_size = 0;
        MMCAM_LOGE("Cmd not recognized by eztune engine: %d", cmd);
        goto error;
    }
    return (this->*(function->second))(payload_size, payload, response_size, response);

error:
    return rc;
}

bool ProcessLayer::Init(eztune_server_t mode)
{
    m_mode = mode;

    if (m_mode == EZTUNE_SERVER_CONTROL) {
        //Get tuning tables first to ensure the stream has started
        eztune_t ezctrl;
        m_cam_adapter->GetTuningTables(&ezctrl);

        m_cam_adapter->FetchChromatixData();
        m_cam_adapter->FetchAFTuneData();

        tuning_set_vfe(NULL, VFE_MODULE_ALL, SET_STATUS, 1);
        tuning_set_pp(NULL, PP_MODULE_ALL, SET_STATUS, 1);
        tuning_set_3a(NULL, EZ_STATUS, 1);

        std::vector<eztune_set_val_t> *pending_cmds = (std::vector<eztune_set_val_t> *)m_pending_cmds;
        pending_cmds->clear();

        debug_open_paramsdump_file();

        MMCAM_LOGI("%s:Control Mode Init", __func__ );
    } else {
        MMCAM_LOGI("%s:Preview Mode Init", __func__ );
    }

    m_init_done = true;
    return true;
}

bool ProcessLayer::DeInit()
{
    MMCAM_ASSERT_PRE(m_init_done == true, "Process Layer is not yet initialized");

    if (m_mode == EZTUNE_SERVER_CONTROL) {
        debug_close_paramsdump_file();

        tuning_set_vfe(NULL, VFE_MODULE_ALL, SET_STATUS, 0);
        tuning_set_pp(NULL, PP_MODULE_ALL, SET_STATUS, 0);
        tuning_set_3a(NULL, EZ_STATUS, 0);

        MMCAM_LOGV("%s:Server Mode DeInit", __func__ );
    } else {
        MMCAM_LOGV("%s:Preview Mode DeInit", __func__ );
    }

    m_init_done = false;
    return true;
}

bool ProcessLayer::ProcessImgTransInfo(size_t payload_size, string &payload, size_t &response_size, string &response)
{
    response.clear();

    PreviewInfoVersion version = {
        .major_ver = kImgTransInfoMajorVersion,
        .minor_ver = kImgTransInfoMinorVersion
    };

    response.append((char *)&version, sizeof(version));

    PreviewInfoHeader header = {
        .header_size = kImgTransInfoHeaderSize,
        .target_type = kImgTransInfoTargetType,
        .capabilities = kImgTransInfoCapabilities,
        .chunk_size = kPreviewInfoChunkSize
    };

    response.append((char *)&header, sizeof(header));

    response_size = response.size();

    MMCAM_LOGV("%s: Size(%zu)", __func__, response_size);

    return true;
}

bool ProcessLayer::ProcessChangeChunkSize(size_t payload_size, string &payload, size_t &response_size, string &response)
{
    uint32_t new_chunk_size = *(uint32_t *)payload.data();
    uint8_t status;
    uint32_t chunk_size;

    if (new_chunk_size <= kPreviewMaxChunkSize) {
        status = kChunkStatusSuccess;
        chunk_size = new_chunk_size;
    } else {
        status = kChunkStatusNewSize;
        chunk_size = kPreviewMaxChunkSize;
    }
    m_chunk_size = chunk_size;

    response.clear();
    response.append((char *)&status, sizeof(status));
    response.append((char *)&chunk_size, sizeof(chunk_size));

    response_size = response.size();

    MMCAM_LOGV("%s: Size(%zu)", __func__, response_size);

    return true;
}

bool ProcessLayer::ProcessGetPreviewFrame(size_t payload_size, string &payload, size_t &response_size, string &response)
{
    bool done = false;
    MMCAM_LOGV("%s: pending_preview_send_size (%zu), chunk_size(%zu)", __func__, m_pending_preview_send_size, m_chunk_size);
    //start with clear string
    response.clear();

    //if header not sent, send header first, and then send preview chunks separately
    if (m_preview_header_sent == false) {

        //get pointer to preview buffer and set pending size as full image size
        //if cannot get a buffer, fill nothing and return
        if (m_cam_adapter->GetPreviewBuffer(&m_preview_buffer) == false) {
            MMCAM_LOGW("Getting preview frame failed perhaps due to timeout");
            done = true;
            goto end;
        }

        //set status as success
        uint8_t status = 0;
        response.append((char *)&status, sizeof(status));

        uint16_t width;
        uint16_t height;
        uint8_t format;
        uint32_t frame_size;
        m_cam_adapter->GetPreviewInfo(width,
                                      height,
                                      format,
                                      frame_size);
        uint8_t origin = EZTUNE_ORIGIN_BOTTOM_LEFT;

        response.append((char *)&width, sizeof(width));
        response.append((char *)&height, sizeof(height));
        response.append((char *)&format, sizeof(format));
        response.append((char *)&origin, sizeof(origin));
        response.append((char *)&frame_size, sizeof(frame_size));

        m_pending_preview_send_size = frame_size;
        //move the pointer towards the end
        m_preview_buffer =  (uint8_t *)((uint32_t) m_preview_buffer + m_pending_preview_send_size);
        m_preview_header_sent = true;

        //only for debug
        debug_open_dump_file();

    } else {

        //Pointer is reset to end of buffer in the header sent condition above
        // Now Subtract pending size, which shrinks with every call
        char *ptr = (char *) (m_preview_buffer - m_pending_preview_send_size);

        uint32_t size;
        if (m_pending_preview_send_size > m_chunk_size) {
            size = m_chunk_size;
            m_pending_preview_send_size = m_pending_preview_send_size - m_chunk_size;
        } else {
            size = m_pending_preview_send_size;
            m_pending_preview_send_size = 0;
            m_preview_header_sent = false;
            done = true;
        }

        response.append(ptr, size);

        //only for debug
        debug_write_dump_file(ptr, size);
        if (done) {
            debug_close_dump_file();
        }
    }
end:
    response_size = response.size();

    MMCAM_LOGV("%s: Size(%zu)", __func__, response_size);

    return done;
}

bool ProcessLayer::ProcessGetSnapshotFrame(
  size_t payload_size,
  string &payload,
  size_t &response_size,
  string &response
)
{
  bool done = false;
  MMCAM_LOGE("%s: pending_snapshot_send_size (%zu), chunk_size(%zu)",
                __func__, m_pending_snapshot_send_size, m_chunk_size);
  //start with clear string
  response.clear();

  //if header not sent, send header first, and then send snapshot chunks separately
  if (false == m_snapshot_header_sent) {
    //get pointer to snapshot buffer and set pending size as full image size
    //if cannot get a buffer, fill nothing and return
    if (m_cam_adapter->GetSnapshotBuffer(&m_snapshot_buffer) == false) {
        MMCAM_LOGW("Getting snapshot frame failed perhaps due to timeout");
        done = true;
        goto end;
    }

    //set status as success
    uint8_t status = 0;
    response.append((char *)&status, sizeof(status));

    uint16_t width;
    uint16_t height;
    uint8_t format;
    uint32_t frame_size;
    m_cam_adapter->GetSnapshotInfo(width,
                                   height,
                                   format,
                                   frame_size);
    uint8_t origin = EZTUNE_ORIGIN_BOTTOM_LEFT;

    response.append((char *)&width, sizeof(width));
    response.append((char *)&height, sizeof(height));
    response.append((char *)&format, sizeof(format));
    response.append((char *)&origin, sizeof(origin));
    response.append((char *)&frame_size, sizeof(frame_size));

    m_pending_snapshot_send_size = frame_size;
    //move the pointer towards the end
    m_snapshot_buffer =  (uint8_t *)((uint32_t) m_snapshot_buffer +
                                           m_pending_snapshot_send_size);
    m_snapshot_header_sent = true;

    //only for debug
    debug_open_dump_file();
  } else {
    //Pointer is reset to end of buffer in the header sent condition above
    // Now Subtract pending size, which shrinks with every call
    char *ptr = (char *) (m_snapshot_buffer - m_pending_snapshot_send_size);

    uint32_t size;
    if (m_pending_snapshot_send_size > m_chunk_size) {
        size = m_chunk_size;
        m_pending_snapshot_send_size = m_pending_snapshot_send_size - m_chunk_size;
    } else {
        size = m_pending_snapshot_send_size;
        m_pending_snapshot_send_size = 0;
        m_snapshot_header_sent = false;
        done = true;
    }

    response.append(ptr, size);

    //only for debug
    debug_write_dump_file(ptr, size);
    if (done) {
        debug_close_dump_file();
    }
  }

end:
    response_size = response.size();
    MMCAM_LOGV("%s: Size(%zu)", __func__, response_size);
    return done;
}

bool ProcessLayer::ProcessGetListCmd(size_t payload_size, string &payload, size_t &response_size, string &response)
{
    MMCAM_ASSERT_PRE(m_init_done == true, "Process Layer is not yet initialized");

    //start with clear string
    response.clear();

    //set default first 3 bytes for status and number of records.
    //This gets overwritten to actual number of records outside the for loop
    response.append("\x00", 1);
    response.append((const char *)&m_items_added, 2);

    MMCAM_LOGV("Number of items to add: %d, Max buffer size: %zu", (EZT_PARMS_MAX - m_items_added), response_size);

    int i;
    for (i = m_items_added; i < EZT_PARMS_MAX; i++) {

        eztune_item_t item = eztune_get_item(i);

        //check if enough space to insert current entry
        if (response.size() >= (response_size - 8 - strlen(item.name) - 1))
            break;

        //insert index
        response.append((const char *)&i, 2);

        //insert offset
        if (item.offset)
            response.append((const char *)&item.size, 2);
        else
            response.append("\x01\x00", 2);

        //insert flag
        if (item.reg_flag == EZT_WRITE_FLAG) {
            response.append("\x00\x00\x00\x00", 4);
        } else if (item.reg_flag == EZT_READ_FLAG || item.reg_flag == EZT_3A_FLAG) {
            response.append("\x01\x00\x00\x00", 4);
        } else if (item.reg_flag == EZT_CHROMATIX_FLAG) {
            response.append("\x40\x00\x00\x00", 4);
        } else if (item.reg_flag == EZT_AUTOFOCUS_FLAG) {
            response.append("\x00\x04\x00\x00", 4);
        } else if (item.reg_flag == (EZT_AUTOFOCUS_FLAG | EZT_READ_FLAG)) {
            response.append("\x01\x04\x00\x00", 4);
        }

        //insert name
        response.append(item.name, strlen(item.name) + 1);
    }

    //replace the character 0 if not all params are added
    if (i != EZT_PARMS_MAX)
        response.replace(0, 1, "\x01");

    //replace character 1 and 2 to to indicate number of items added
    uint16_t items_added = i - m_items_added;
    response.replace(1, 2, (const char *)&items_added, 2);

    //update number of items added
    if (i == EZT_PARMS_MAX) {
        m_items_added = 0;
        MMCAM_LOGI("All getlist Items added");
    } else {
        m_items_added = i;
    }

    MMCAM_LOGV("Number of items added: %d, Response buffer size: %zu", items_added, response.size());

    //fill remaining data with 0 bytes
    MMCAM_ASSERT(response_size >= response.size(), "response string overflow");
    response.append(response_size - response.size(), 0);

    return true;
}

bool ProcessLayer::ProcessGetParamCmd(size_t payload_size, string &payload, size_t &response_size, string &response)
{
    MMCAM_ASSERT_PRE(m_init_done == true, "Process Layer is not yet initialized");

    const char *input = payload.data();

    uint16_t num_items =  *(uint16_t *)input;
    input = input + sizeof(uint16_t);

    response.clear();

    if (m_pending_set_param_apply == true)
        response.append("\x01", 1);
    else
        response.append("\x00", 1);

    //insert number of items
    response.append((const char *)&num_items, sizeof(uint16_t));

    eztune_t ezctrl;

    MMCAM_LOGV("Number of params to get: %d, Max buffer size: %zu", num_items, response_size);

    //get new tuning tables only if non zero items needs to be fetched
    //PS: eztune host tool periodically sends get param with no items
    if (num_items) {
        if (m_cam_adapter->GetTuningTables(&ezctrl) == false) {
            MMCAM_LOGW("Get Tuning tables failed perhaps due to timeout");
            //reset number of items added as zero
            uint16_t num_items_added = 0;
            response.replace(1, 2, (const char *)&num_items_added, 2);
            goto end;
        }
    }

    //debug
    debug_write_paramsdump_file("Adding GetParams. Num params: %d\n", num_items);

    int i;
    for (i = 0; i < num_items; ++i) {
        int rc = -1;

        uint16_t item_num = *(uint16_t *)input;
        input = input + sizeof(uint16_t);

        uint16_t table_index = *(uint16_t *)input;
        input = input + sizeof(uint16_t);

        //check if enough space to insert current entry
        if (response.size() >= (response_size - 4 - 64)) {
            break;
        }

        //insert item number and table index
        response.append((const char *)&item_num, sizeof(uint16_t));
        response.append((const char *)&table_index, sizeof(uint16_t));

        //fetch the required item and then extract info
        eztune_item_t item = eztune_get_item(item_num);

        void *chromatixptr;

        if (item.id < EZT_PARMS_SNAP_MISC_CHROMATIXVERSION)
            chromatixptr = (char *)ezctrl.chromatixptr;
        else if ((item.id >= EZT_PARMS_SNAP_MISC_CHROMATIXVERSION) &&
                 (item.id < EZT_PARMS_MISC_COMMONCHROMATIXVERSION))
            chromatixptr = (char *)ezctrl.snapchromatixptr;
        else
            chromatixptr = (char *)ezctrl.common_chromatixptr;

        char *ptr = (char *)chromatixptr + item.offset;

        //offset the pointer based on data type
        if (item.id == EZT_PARMS_AEC_TABLEEXPOSUREENTRIESGAIN ||
                item.id == EZT_PARMS_SNAP_AEC_TABLEEXPOSUREENTRIESGAIN) {

            ptr += table_index * sizeof(exposure_entry_type) + offsetof(exposure_entry_type, gain);

        } else if (item.id == EZT_PARMS_AEC_TABLEEXPOSUREENTRIESLINECT ||
                   item.id == EZT_PARMS_SNAP_AEC_TABLEEXPOSUREENTRIESLINECT) {

            ptr += table_index * sizeof(exposure_entry_type) + offsetof(exposure_entry_type, line_count);

        } else {

            auto elem = kEzTypeToSizeMapping.find(item.data);
            size_t size;

            if (elem == kEzTypeToSizeMapping.end()) {
                size = 0;
            } else {
                size = elem->second;
            }

            ptr += table_index * size;
        }

        char temp_string[EZTUNE_FORMAT_MAX];

        if (item.data == EZT_D_INVALID) {
            /* diagnostics */
            if (item.id >= EZT_PARMS_3A &&
                    item.id <= EZT_PARMS_MISC_SENSORQTRHEIGHT) {
                rc = eztune_get_diagnostic_item(&ezctrl, temp_string, 0, item.id,
                                                table_index);

            } else if (item.id >= EZT_PARMS_AFTUNE_RELOADPARAMS_ENABLE &&
                       item.id <= EZT_PARMS_AFTUNE_TUNING_TEST_MOVEFOCUS_STEPS) {
                rc = eztune_get_af_item(&ezctrl, temp_string, 0, item.id,
                                        table_index);
            } else {
                MMCAM_LOGW("Invalid item.id");
            }

        } else {

            switch (item.data) {
            case EZT_D_FLOAT:
                rc = snprintf(temp_string, EZTUNE_FORMAT_MAX,
                              "%f", *((float *)ptr));
                break;
            case EZT_D_INT8:
                rc = snprintf(temp_string, EZTUNE_FORMAT_MAX,
                              "%d", *((int8_t *)ptr));
                break;
            case EZT_D_INT16:
                rc = snprintf(temp_string, EZTUNE_FORMAT_MAX,
                              "%d", *((int16_t *)ptr));
                break;
            case EZT_D_INT32:
                rc = snprintf(temp_string, EZTUNE_FORMAT_MAX,
                              "%d", *((int32_t *)ptr));
                break;
            case EZT_D_UINT8:
                rc = snprintf(temp_string, EZTUNE_FORMAT_MAX,
                              "%d", *((uint8_t *)ptr));
                break;
            case EZT_D_UINT16:
                rc = snprintf(temp_string, EZTUNE_FORMAT_MAX,
                              "%d", *((uint16_t *)ptr));
                break;
            case EZT_D_UINT32:
                rc = snprintf(temp_string, EZTUNE_FORMAT_MAX,
                              "%d", *((uint32_t *)ptr));
                break;
            case EZT_D_DOUBLE:
                rc = snprintf(temp_string, EZTUNE_FORMAT_MAX,
                              "%lf", *((double *)ptr));
                break;

            default:
                MMCAM_LOGW("Invalid item.data");
                break;
            }
        }

        if (rc <= 0) {
            MMCAM_LOGW("Invalid item (%s). Writing 0 as item.value to avoid crash: item.id (%d), table_index(%d), item.data(%d)",
                item.name, item.id, table_index, item.data);

            rc = snprintf(temp_string, EZTUNE_FORMAT_MAX,
                          "%d", 0);
        }

        //debug
        debug_write_paramsdump_file("Item no: %d, Table Index: %d, Value: %s\n", item_num, table_index, temp_string);

        response.append((char *)temp_string, rc + 1);
    }

    MMCAM_LOGV("Number of params obtained: %d, Response buffer size: %zu", i, response.size());

    //debug
    debug_write_paramsdump_file("End of GetParams: Num items written: %d\n\n", i);

    //replace the number of items added with actual elements written
    response.replace(1, 2, (const char *)&i, 2);

end:
    //fill remaining data with 0 bytes
    MMCAM_ASSERT(response_size >= response.size(), "response string overflow");
    response.append(response_size - response.size(), 0);
    return true;
}

static void debug_item(eztune_set_val_t item)
{
    MMCAM_LOGV("Item num(%d), Item Index(%d), Item string(%s)", item.item_num, item.table_index, item.value_string);

    //debug
    debug_write_paramsdump_file("Item num(%d), Table Index(%d), Value(%s)\n", item.item_num, item.table_index, item.value_string);
}

bool ProcessLayer::ProcessSetParamCmd(size_t payload_size, string &payload, size_t &response_size, string &response)
{
    MMCAM_ASSERT_PRE(m_init_done == true, "Process Layer is not yet initialized");

    const char *input = payload.data();

    uint16_t num_items =  *(uint16_t *)input;
    input = input + sizeof(uint16_t);

    MMCAM_ASSERT(num_items < EZT_PARMS_MAX, "Invalid number of items: %u", num_items);

    MMCAM_LOGV("Set Param command");

    //debug
    debug_write_paramsdump_file("Starting SetParams: Num items requested: %d", num_items);

    ::eztune_set_val_t item;

    std::vector<eztune_set_val_t> *pending_cmds = (std::vector<eztune_set_val_t> *)m_pending_cmds;
    int i;
    for (i = 0; i < num_items; ++i) {
        item.item_num = *(uint16_t *)input;
        input = input + sizeof(uint16_t);

        item.table_index = *(uint16_t *)input;
        input = input + sizeof(uint16_t);

        size_t copy_size = strlcpy(item.value_string, input, sizeof(item.value_string));
        MMCAM_ASSERT(copy_size < sizeof(item.value_string), "Item value too long");

        input = input + strlen(input) + 1;

        debug_item(item);

        //push to pending cmds vector. This gets applied during mscl command
        pending_cmds->push_back(item);
    }

    //debug
    debug_write_paramsdump_file("Completed SetParams: Num items written: %d\n\n", i);

    m_pending_set_param_apply = true;

    response.clear();

    //set response string
    response.append("\x01", 1);

    //fill remaining data with 0 bytes
    MMCAM_ASSERT(response_size >= response.size(), "response string overflow");
    response.append(response_size - response.size(), 0);

    return true;
}

bool ProcessLayer::ProcessMiscCmd(size_t payload_size, string &payload, size_t &response_size, string &response)
{
    MMCAM_ASSERT_PRE(m_init_done == true, "Process Layer is not yet initialized");

    const char *data = payload.data();
    uint8_t cmd = *(uint8_t *)data;

    response.clear();

    if (cmd == EZTUNE_MISC_GET_VERSION) {
        MMCAM_LOGI("Get version command");
        //insert version number and return
        response.append(eztune::kEztuneVersion);
        goto end;

    } else if (cmd == EZTUNE_MISC_APPLY_CHANGES) {
        eztune_item_t item;
        bool update_chromatix = false;
        bool update_autofocus = false;

        MMCAM_ASSERT(m_pending_cmds != NULL, "Null cmd vector pointter");

        MMCAM_LOGI("Apply changes command");

        eztune_t ezctrl;
        if (m_cam_adapter->GetTuningTables(&ezctrl) == false) {
            MMCAM_LOGW("Get Tuning tables failed perhaps due to timeout");
            response.clear();
            response_size = 0;
            goto end;
        }

        std::vector<eztune_set_val_t> *pending_cmds = (std::vector<eztune_set_val_t> *)m_pending_cmds;

        //debug
        debug_write_paramsdump_file("Starting Apply. Number of params %zu\n", pending_cmds->size());

        //get elements from the pending cmds vector and apply change
        for (auto elem = pending_cmds->begin(); elem != pending_cmds->end(); ++elem) {

            item = eztune_get_item((*elem).item_num);

            MMCAM_ASSERT((item.id >= 0) && (item.id < EZT_PARMS_MAX),
                         "Out of range index ID: %d", item.id);

            debug_item(*elem);

            eztune_change_item(&item, &(*elem), &ezctrl);

            if (item.type == EZT_T_CHROMATIX)
                update_chromatix = true;
            if ((item.id >= EZT_PARMS_AFTUNE_PROCESSTYPE) &&
                    (item.id < EZT_PARMS_AFTUNE_TUNING_TEST_LINEAR_ENABLE))
                update_autofocus = true;
        }

        if (update_chromatix) {
            m_cam_adapter->UpdateCamChromatixData();
        }

        if (update_autofocus) {
            m_cam_adapter->UpdateCamAFTuneData();
        }

        //clear pending commands queue
        pending_cmds->clear();

        //debug
        debug_write_paramsdump_file("Completed Apply. Cleared size %zu\n\n", pending_cmds->size());

        //Assign response
        //TODO: Instead of setting default to 00 (no error), check error condition
        //and set the string accordingly
        response.append("\x00", 1);

        m_pending_set_param_apply = false;
    }

end:
    //fill remaining data with 0 bytes
    MMCAM_ASSERT(response_size >= response.size(), "response string overflow");
    response.append(response_size - response.size(), 0);

    return true;
}

void ProcessLayer::EventNotify(uint32_t type, void *data)
{
    if (m_init_done == true) {
        m_cam_adapter->EventNotify(type, data);
    } else {
        MMCAM_LOGV("Event skipped as init not done");
    }
}

};
