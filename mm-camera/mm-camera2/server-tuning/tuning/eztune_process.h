/*******************************************************************************
* Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
*******************************************************************************/

#ifndef EZTUNE_PROCESS_H
#define EZTUNE_PROCESS_H

#include <string>
#include <map>
#include <cstdint>
#include <vector>

#include "eztune_interface.h"

namespace eztune
{

using std::string;

const string kEztuneVersion("2.1.0\0", 6);
const string kEztuneExtendedVersion("2.1.2\0", 6);

//forward declare
class CamAdapter;

//!  Implements processing of payload data associated with each eztune cmd
/*!
  The implementation uses eztune items c library and camera adapter to execute
  the low level functions
*/

class ProcessLayer
{
public:
    ProcessLayer(void *);
    ~ProcessLayer();

    //! This function process the payload data and generates the output response
    /*!
        Internally this class uses a camera adapter class to interface with camera and
        uses eztume_items c API to get/set eztune items

      \param in cmd: 16-bit command from host. The processing depends on this command
      \param in payload_size: Valid size of payload data in payload string
      \param in payload: Payload data string from host
      \param in/out response_size: Expected size of response data to be send back to host
      \param response: Reference to response string to which data has to be written
    */
    bool ProcessAndGenerateResponse(uint16_t cmd, size_t payload_size, string &payload, size_t &response_size, string &response);

    //! Init funciton for the process layer. Called once per client
    /*!
        This function should be called to initialize internal data structures. Should be called
        once before calling ProcessAndGenerateResponse to process commands
    */
    bool Init(eztune_server_t mode);

    //! DeInit funciton for the process layer. Called once per client when client disconnect
    /*!
        This function should be called when the client disconnects after processing multiple
        ProcessAndGenerateResponse commands
    */
    bool DeInit();

    //! Notify camera client events. Events like new meta data available
    /*
       \param in type: Event type
       \param in data: Data associated with event
    */
    void EventNotify(uint32_t type, void *data);

private:
    bool m_preview_header_sent;
    bool m_snapshot_header_sent;
    uint32_t m_pending_preview_send_size;
    uint32_t m_pending_snapshot_send_size;
    uint8_t *m_preview_buffer;
    uint8_t *m_snapshot_buffer;
    uint32_t m_chunk_size;

    bool m_init_done;
    uint16_t m_items_added;
    bool m_pending_set_param_apply;

    eztune::CamAdapter *m_cam_adapter;

    //workaround: In actual use this is a pointer to std::vector<eztune_set_val_t> *.
    //But declaring of this type would need including eztune related header files for all users
    void *m_pending_cmds;

    eztune_server_t m_mode;

    //cmd specific processing functions
    bool ProcessGetListCmd(size_t payload_size, string &payload, size_t &response_size, string &response);
    bool ProcessGetParamCmd(size_t payload_size, string &payload, size_t &response_size, string &response);
    bool ProcessSetParamCmd(size_t payload_size, string &payload, size_t &response_size, string &response);
    bool ProcessMiscCmd(size_t payload_size, string &payload, size_t &response_size, string &response);
    bool ProcessImgTransInfo(size_t payload_size, string &payload, size_t &response_size, string &response);
    bool ProcessChangeChunkSize(size_t payload_size, string &payload, size_t &response_size, string &response);
    bool ProcessGetPreviewFrame(size_t payload_size, string &payload, size_t &response_size, string &response);
    bool ProcessGetSnapshotFrame(size_t payload_size, string &payload, size_t &response_size, string &response);
};

};

#endif
