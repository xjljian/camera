/*============================================================================

  Copyright (c) 2014 Qualcomm Technologies, Inc. All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

============================================================================*/
#include <stdio.h>
#include "sensor_lib.h"

#define SENSOR_MODEL_NO_S5K5E2 "s5k5e2"
#define S5K5E2_LOAD_CHROMATIX(n) \
  "libchromatix_"SENSOR_MODEL_NO_S5K5E2"_"#n".so"

static sensor_lib_t sensor_lib_ptr;

static struct msm_sensor_power_setting power_setting[] = {
  {
    .seq_type = SENSOR_VREG,
    .seq_val = CAM_VIO,
    .config_val = 0,
    .delay = 0,
  },
  {
    .seq_type = SENSOR_VREG,
    .seq_val = CAM_VANA,
    .config_val = 0,
    .delay = 0,
  },
   {
    .seq_type = SENSOR_GPIO,
    .seq_val = SENSOR_GPIO_VDIG,
    .config_val = GPIO_OUT_LOW,
    .delay = 1,
  },
  {
    .seq_type = SENSOR_GPIO,
    .seq_val = SENSOR_GPIO_VDIG,
    .config_val = GPIO_OUT_HIGH,
    .delay = 30,
  },
  {
    .seq_type = SENSOR_GPIO,
    .seq_val = SENSOR_GPIO_RESET,
    .config_val = GPIO_OUT_LOW,
    .delay = 1,
  },
  {
    .seq_type = SENSOR_GPIO,
    .seq_val = SENSOR_GPIO_RESET,
    .config_val = GPIO_OUT_HIGH,
    .delay = 30,
  },
  {
    .seq_type = SENSOR_GPIO,
    .seq_val = SENSOR_GPIO_STANDBY,
    .config_val = GPIO_OUT_LOW,
    .delay = 1,
  },
  {
    .seq_type = SENSOR_GPIO,
    .seq_val = SENSOR_GPIO_STANDBY,
    .config_val = GPIO_OUT_HIGH,
    .delay = 30,
  },
  {
    .seq_type = SENSOR_CLK,
    .seq_val = SENSOR_CAM_MCLK,
    .config_val = 23880000,
    .delay = 1,
  },
  {
    .seq_type = SENSOR_I2C_MUX,
    .seq_val = 0,
    .config_val = 0,
    .delay = 1,
  },
};

static struct msm_camera_sensor_slave_info sensor_slave_info = {
  /* Camera slot where this camera is mounted */
  .camera_id = CAMERA_0,
  /* sensor slave address */
  .slave_addr = 0x20,
  /* sensor address type */
  .addr_type = MSM_CAMERA_I2C_WORD_ADDR,
  /* sensor id info*/
  .sensor_id_info = {
  /* sensor id register address */
  .sensor_id_reg_addr = 0x00,
  /* sensor id */
  .sensor_id = 0x5e20,
  },
  /* power up / down setting */
  .power_setting_array = {
  .power_setting = power_setting,
  .size = ARRAY_SIZE(power_setting),
  },
};

static struct msm_sensor_init_params sensor_init_params = {
  .modes_supported = 0,
  .position = 0,
  .sensor_mount_angle = 90,
};

static sensor_output_t sensor_output = {
  .output_format = SENSOR_BAYER,
  .connection_mode = SENSOR_MIPI_CSI,
  .raw_output = SENSOR_10_BIT_DIRECT,
};

static struct msm_sensor_output_reg_addr_t output_reg_addr = {
  .x_output = 0x034C,
  .y_output = 0x034E,
  .line_length_pclk = 0x0342,
  .frame_length_lines = 0x0340,
};

static struct msm_sensor_exp_gain_info_t exp_gain_info = {
  .coarse_int_time_addr = 0x0202,
  .global_gain_addr = 0x0204,
  .vert_offset = 8,
};

static sensor_aec_data_t aec_info = {
  .max_gain = 16.0,
  .max_linecount = 30834,
};

static sensor_lens_info_t default_lens_info = {
  .focal_length = 2.93,
  .pix_size = 1.4,
  .f_number = 2.8,
  .total_f_dist = 1.2,
  .hor_view_angle = 54.8,
  .ver_view_angle = 42.5,
};

#ifndef VFE_40
static struct csi_lane_params_t csi_lane_params = {
  .csi_lane_assign = 0xe4,
  .csi_lane_mask = 0x1,
  .csi_if = 1,
  .csid_core = {0},
  .csi_phy_sel = 0,
};
#else
static struct csi_lane_params_t csi_lane_params = {
  .csi_lane_assign = 0x4320,
  .csi_lane_mask = 0x7,
  .csi_if = 1,
  .csid_core = {0},
  .csi_phy_sel = 0,
};
#endif

static struct msm_camera_i2c_reg_array init_reg_array0[] = {
    {0x0100,0x01, 0},// software reset
};

static struct msm_camera_i2c_reg_array init_reg_array1[] = {
    {0x0100,0x00, 0}, //stream off
    {0x0101,0x03, 0},
    {0x3000,0x04, 0},
    {0x3002,0x03, 0},
    {0x3003,0x04, 0},
    {0x3004,0x02, 0},
    {0x3005,0x00, 0},
    {0x3006,0x10, 0},
    {0x3007,0x03, 0},
    {0x3008,0x55, 0},
    {0x3039,0x00, 0},
    {0x303A,0x00, 0},
    {0x303B,0x00, 0},
    {0x3009,0x05, 0},
    {0x300A,0x55, 0},
    {0x300B,0x38, 0},
    {0x300C,0x10, 0},
    {0x3012,0x05, 0},
    {0x3013,0x00, 0},
    {0x3014,0x22, 0},
    {0x300E,0x79, 0},
    {0x3010,0x68, 0},
    {0x3019,0x03, 0},
    {0x301A,0x00, 0},
    {0x301B,0x06, 0},
    {0x301C,0x00, 0},
    {0x301D,0x22, 0},
    {0x301E,0x00, 0},
    {0x301F,0x10, 0},
    {0x3020,0x00, 0},
    {0x3021,0x00, 0},
    {0x3022,0x0A, 0},
    {0x3023,0x1E, 0},
    {0x3024,0x00, 0},
    {0x3025,0x00, 0},
    {0x3026,0x00, 0},
    {0x3027,0x00, 0},
    {0x3028,0x1A, 0},
    {0x3015,0x00, 0},
    {0x3016,0x84, 0},
    {0x3017,0x00, 0},
    {0x3018,0xA0, 0},
    {0x302B,0x10, 0},
    {0x302C,0x0A, 0},
    {0x302D,0x06, 0},
    {0x302E,0x05, 0},
    {0x302F,0x0E, 0},
    {0x3030,0x2F, 0},
    {0x3031,0x08, 0},
    {0x3032,0x05, 0},
    {0x3033,0x09, 0},
    {0x3034,0x05, 0},
    {0x3035,0x00, 0},
    {0x3036,0x00, 0},
    {0x3037,0x00, 0},
    {0x3038,0x00, 0},
    {0x3088,0x06, 0},
    {0x308A,0x08, 0},
    {0x308C,0x05, 0},
    {0x308E,0x07, 0},
    {0x3090,0x06, 0},
    {0x3092,0x08, 0},
    {0x3094,0x05, 0},
    {0x3096,0x21, 0},
    //CDS
    {0x3099,0x0E, 0},
    {0x3070,0x10, 0},
    {0x3085,0x11, 0},
    {0x3086,0x01, 0},
    {0x3064,0x00, 0},
    {0x3062,0x08, 0},
    //RMP
    {0x3061,0x11, 0},
    {0x307B,0x20, 0},
    //Bias sampling
    {0x3068,0x00, 0},
    {0x3074,0x00, 0},
    {0x307D,0x00, 0},
    {0x3045,0x01, 0},
    {0x3046,0x05, 0},
    {0x3047,0x78, 0},
    //Smart PLA
    {0x307F,0xB1, 0},
    {0x3098,0x01, 0},
    {0x305C,0xF6, 0},
    {0x306B,0x10, 0},
    {0x3063,0x27, 0},
    {0x320C,0x07, 0},
    {0x320D,0x00, 0},
    {0x3400,0x01, 0},//Shading 0x00=On,0x01=Off
    {0x3235,0x49, 0},
    {0x3233,0x00, 0},
    {0x3234,0x00, 0},
    {0x3300,0x0C, 0},

    //ADC_OFFSET - 1215
    {0x3203,0x45, 0}, // ADC_OFFSET_EVEN
    {0x3205,0x4D, 0}, // ADC_OFFSET_ODD
    {0x320B,0x40, 0}, // ADC_DEFAULT
    {0x320C,0x06, 0}, // ADC_MAX
    {0x320D,0xC0, 0},

    // Clock Setting
    {0x0305,0x05, 0},
    {0x0306,0x00, 0},
    {0x0307,0xB4, 0},
    {0x3C1F,0x01, 0},
    {0x0820,0x01, 0},
    {0x0821,0xB0, 0},
    {0x3C1C,0x54, 0},
    {0x0114,0x01, 0},
    //Size Setting
    {0x0340,0x03, 0}, // frame_length_lines : def. 1962d (7C2 --> 7A6 Mimnimum 22 lines)
    {0x0341,0xD7, 0},
    {0x0342,0x0B, 0}, // line_length_pck : def. 2900d
    {0x0343,0x86, 0},
    {0x0344,0x00, 0},        //x_addr_start                                     8
    {0x0345,0x08, 0},        //
    {0x0346,0x00, 0},        //y_addr_start                                     0
    {0x0347,0x08, 0},        //
    {0x0348,0x0A, 0},        //x_addr_end : def. 2575d                          167
    {0x0349,0x07, 0},        //
    {0x034A,0x07, 0},        //y_addr_end : def. 1936d                          1935
    {0x034B,0x87, 0},        //
    {0x034C,0x05, 0},        //x_output size : def. 2560d                       2560
    {0x034D,0x00, 0},        //
    {0x034E,0x03, 0},        //y_output size : def. 1920d                       1936
    {0x034F,0xC0, 0},        //
    //Digital Binning(default)
    {0x0900,0x01, 0},    //0x0 Binning
    {0x0901,0x22, 0},
    {0x0387,0x03, 0},
    {0x0204,0x00, 0},        //Analog gain x1                                    0
    {0x0205,0x20, 0},        //                                                  32
    //Integration time
    {0x0202,0x02, 0},  // coarse integration
    {0x0203,0x00, 0},
    {0x0200,0x04, 0},  // fine integration (AC4h --> A1Ah)
    {0x0201,0x98, 0},
    //streaming ON
    {0x0100,0x01, 0},
};

static struct msm_camera_i2c_reg_setting init_reg_setting[] = {
  {
    .reg_setting = init_reg_array0,
    .size = ARRAY_SIZE(init_reg_array0),
    .addr_type = MSM_CAMERA_I2C_WORD_ADDR,
    .data_type = MSM_CAMERA_I2C_BYTE_DATA,
    .delay = 50,
  },
  {
    .reg_setting = init_reg_array1,
    .size = ARRAY_SIZE(init_reg_array1),
    .addr_type = MSM_CAMERA_I2C_WORD_ADDR,
    .data_type = MSM_CAMERA_I2C_BYTE_DATA,
    .delay = 0,
  },
};

static struct sensor_lib_reg_settings_array init_settings_array = {
  .reg_settings = init_reg_setting,
  .size = 2,
};

static struct msm_camera_i2c_reg_array start_reg_array[] = {
    {0x0100, 0x01, 0},

};

static  struct msm_camera_i2c_reg_setting start_settings = {
  .reg_setting = start_reg_array,
  .size = ARRAY_SIZE(start_reg_array),
  .addr_type = MSM_CAMERA_I2C_WORD_ADDR,
  .data_type = MSM_CAMERA_I2C_BYTE_DATA,
  .delay = 0,
};

static struct msm_camera_i2c_reg_array stop_reg_array[] = {
    {0x0100, 0x00, 0},
};

static struct msm_camera_i2c_reg_setting stop_settings = {
  .reg_setting = stop_reg_array,
  .size = ARRAY_SIZE(stop_reg_array),
  .addr_type = MSM_CAMERA_I2C_WORD_ADDR,
  .data_type = MSM_CAMERA_I2C_BYTE_DATA,
  .delay = 0,
};

static struct msm_camera_i2c_reg_array groupon_reg_array[] = {
  {0x0104, 0x01, 0},
};

static struct msm_camera_i2c_reg_setting groupon_settings = {
  .reg_setting = groupon_reg_array,
  .size = ARRAY_SIZE(groupon_reg_array),
  .addr_type = MSM_CAMERA_I2C_WORD_ADDR,
  .data_type = MSM_CAMERA_I2C_BYTE_DATA,
  .delay = 0,
};

static struct msm_camera_i2c_reg_array groupoff_reg_array[] = {
    {0x0104, 0x00, 0},
};

static struct msm_camera_i2c_reg_setting groupoff_settings = {
  .reg_setting = groupoff_reg_array,
  .size = ARRAY_SIZE(groupoff_reg_array),
  .addr_type = MSM_CAMERA_I2C_WORD_ADDR,
  .data_type = MSM_CAMERA_I2C_BYTE_DATA,
  .delay = 0,
};

static struct msm_camera_csid_vc_cfg s5k5e2_cid_cfg[] = {
  {0, CSI_RAW10, CSI_DECODE_10BIT},
  {1, CSI_EMBED_DATA, CSI_DECODE_8BIT},
};

static struct msm_camera_csi2_params s5k5e2_csi_params = {
    .csid_params = {
     .lane_cnt = 2,
     .lut_params = {
      .num_cid = 2,
      .vc_cfg = {
         &s5k5e2_cid_cfg[0],
         &s5k5e2_cid_cfg[1],
      },
    },
  },
  .csiphy_params = {
    .lane_cnt = 2,
    .settle_cnt = 0x18,
  },
};

static struct msm_camera_csi2_params *csi_params[] = {
  &s5k5e2_csi_params, /* RES 0*/
  &s5k5e2_csi_params, /* RES 1*/
};

static struct sensor_lib_csi_params_array csi_params_array = {
  .csi2_params = &csi_params[0],
  .size = ARRAY_SIZE(csi_params),
};

static struct sensor_pix_fmt_info_t s5k5e2_pix_fmt0_fourcc[] = {
  { V4L2_PIX_FMT_SGBRG10 },// V4L2_PIX_FMT_SGBRG10
};

static struct sensor_pix_fmt_info_t s5k5e2_pix_fmt1_fourcc[] = {
  { MSM_V4L2_PIX_FMT_META },
};

static sensor_stream_info_t s5k5e2_stream_info[] = {
  {1, &s5k5e2_cid_cfg[0], s5k5e2_pix_fmt0_fourcc},
  {1, &s5k5e2_cid_cfg[1], s5k5e2_pix_fmt1_fourcc},
};

static sensor_stream_info_array_t s5k5e2_stream_info_array = {
  .sensor_stream_info = s5k5e2_stream_info,
  .size = ARRAY_SIZE(s5k5e2_stream_info),
};

static struct msm_camera_i2c_reg_array res0_reg_array[] = {
    /*Output Size Capture(2560x1920)*/
    {0x0305,0x05, 0},
    {0x0306,0x00, 0},
    {0x0307,0xB4, 0},
    {0x3C1F,0x01, 0},
    {0x0820,0x01, 0},
    {0x0821,0xB0, 0},
    {0x3C1C,0x54, 0},
    {0x0114,0x01, 0},
    {0x0340,0x07, 0},
    {0x0341,0xA1, 0},
    {0x0342,0x0B, 0},
    {0x0343,0x86, 0},
    {0x0344,0x00, 0},
    {0x0345,0x08, 0},
    {0x0346,0x00, 0},
    {0x0347,0x08, 0},
    {0x0348,0x0A, 0},
    {0x0349,0x07, 0},
    {0x034A,0x07, 0},
    {0x034B,0x87, 0},
    {0x034C,0x0A, 0},
    {0x034D,0x00, 0},
    {0x034E,0x07, 0},
    {0x034F,0x80, 0},
    {0x0900,0x00, 0},
    {0x0901,0x20, 0},
    {0x0387,0x01, 0},
    {0x0204,0x00, 0},
    {0x0205,0x20, 0},
    {0x0202,0x02, 0},
    {0x0203,0x00, 0},
    {0x0200,0x04, 0},
    {0x0201,0x98, 0},
};

static struct msm_camera_i2c_reg_array res1_reg_array[] = {
    /*Output Size Preview(1280x960)*/
    {0x0305,0x06, 0},
    {0x0306,0x00, 0},
    {0x0307,0xDA, 0},
    {0x3C1F,0x01, 0},
    {0x0820,0x01, 0},
    {0x0821,0xB4, 0},
    {0x3C1C,0x54, 0},
    {0x0114,0x01, 0},
    {0x0340,0x03, 0},
    {0x0341,0xD7, 0},
    {0x0342,0x0B, 0},
    {0x0343,0x86, 0},
    {0x0344,0x00, 0},
    {0x0345,0x08, 0},
    {0x0346,0x00, 0},
    {0x0347,0x08, 0},
    {0x0348,0x0A, 0},
    {0x0349,0x07, 0},
    {0x034A,0x07, 0},
    {0x034B,0x87, 0},
    {0x034C,0x05, 0},
    {0x034D,0x00, 0},
    {0x034E,0x03, 0},
    {0x034F,0xC0, 0},
    {0x0900,0x01, 0},
    {0x0901,0x22, 0},
    {0x0387,0x03, 0},
    {0x0204,0x00, 0},
    {0x0205,0x20, 0},
    {0x0202,0x02, 0},
    {0x0203,0x00, 0},
    {0x0200,0x04, 0},
    {0x0201,0x98, 0},
};

static struct msm_camera_i2c_reg_array res2_reg_array[] = {
    /*Output Size Video FHD(1920x1080)*/
    {0x0305,0x06, 0},
    {0x0306,0x00, 0},
    {0x0307,0xE0, 0},
    {0x3C1F,0x00, 0},
    {0x0820,0x03, 0},
    {0x0821,0x80, 0},
    {0x3C1C,0x58, 0},
    {0x0114,0x01, 0},
    {0x0340,0x07, 0},
    {0x0341,0xE9, 0},
    {0x0342,0x0B, 0},
    {0x0343,0x86, 0},
    {0x0344,0x00, 0},
    {0x0345,0x08, 0},
    {0x0346,0x00, 0},
    {0x0347,0x08, 0},
    {0x0348,0x0A, 0},
    {0x0349,0x07, 0},
    {0x034A,0x07, 0},
    {0x034B,0x87, 0},
    {0x034C,0x0A, 0},
    {0x034D,0x00, 0},
    {0x034E,0x07, 0},
    {0x034F,0x80, 0},
    {0x0900,0x00, 0},
    {0x0901,0x20, 0},
    {0x0387,0x01, 0},
    {0x0204,0x00, 0},
    {0x0205,0x20, 0},
    {0x0202,0x02, 0},
    {0x0203,0x00, 0},
    {0x0200,0x04, 0},
    {0x0201,0x98, 0},

};
static struct msm_camera_i2c_reg_array res3_reg_array[] = {
    /*Output Size Video HD(1280x720)*/
    {0x0305,0x06, 0},
    {0x0306,0x00, 0},
    {0x0307,0xE0, 0},
    {0x3C1F,0x00, 0},
    {0x0820,0x03, 0},
    {0x0821,0x80, 0},
    {0x3C1C,0x58, 0},
    {0x0114,0x01, 0},
    {0x0340,0x03, 0},
    {0x0341,0xF4, 0},
    {0x0342,0x0B, 0},
    {0x0343,0x86, 0},
    {0x0344,0x00, 0},
    {0x0345,0x08, 0},
    {0x0346,0x00, 0},
    {0x0347,0x08, 0},
    {0x0348,0x0A, 0},
    {0x0349,0x07, 0},
    {0x034A,0x07, 0},
    {0x034B,0x87, 0},
    {0x034C,0x05, 0},
    {0x034D,0x00, 0},
    {0x034E,0x03, 0},
    {0x034F,0xC0, 0},
    {0x0900,0x01, 0},
    {0x0901,0x22, 0},
    {0x0387,0x03, 0},
    {0x0204,0x00, 0},
    {0x0205,0x20, 0},
    {0x0202,0x02, 0},
    {0x0203,0x00, 0},
    {0x0200,0x04, 0},
    {0x0201,0x98, 0},
};
static struct msm_camera_i2c_reg_setting res_settings[] = {
  {
    .reg_setting = res0_reg_array,
    .size = ARRAY_SIZE(res0_reg_array),
    .addr_type = MSM_CAMERA_I2C_WORD_ADDR,
    .data_type = MSM_CAMERA_I2C_BYTE_DATA,
    .delay = 0,
  },
  {
    .reg_setting = res1_reg_array,
    .size = ARRAY_SIZE(res1_reg_array),
    .addr_type = MSM_CAMERA_I2C_WORD_ADDR,
    .data_type = MSM_CAMERA_I2C_BYTE_DATA,
    .delay = 0,
  },
  {
    .reg_setting = res2_reg_array,
    .size = ARRAY_SIZE(res2_reg_array),
    .addr_type = MSM_CAMERA_I2C_WORD_ADDR,
    .data_type = MSM_CAMERA_I2C_BYTE_DATA,
    .delay = 0,
  },
  {
    .reg_setting = res3_reg_array,
    .size = ARRAY_SIZE(res3_reg_array),
    .addr_type = MSM_CAMERA_I2C_WORD_ADDR,
    .data_type = MSM_CAMERA_I2C_BYTE_DATA,
    .delay = 0,
  },
};

static struct sensor_lib_reg_settings_array res_settings_array = {
  .reg_settings = res_settings,
  .size = ARRAY_SIZE(res_settings),
};

static struct sensor_crop_parms_t crop_params[] = {
  {0, 0, 0, 0}, /* RES 0 */
  {0, 0, 0, 0}, /* RES 1 */
  {0, 0, 0, 0}, /* RES 2 */
  {0, 0, 0, 0}, /* RES 3 */
};

static struct sensor_lib_crop_params_array crop_params_array = {
  .crop_params = crop_params,
  .size = ARRAY_SIZE(crop_params),
};

static struct sensor_lib_out_info_t sensor_out_info[] = {
  {
    .x_output = 0x0A00,//2560
    .y_output = 0x0780,//1920
    .line_length_pclk = 0xB86,//2900
    .frame_length_lines = 0x07B2,// 1970
    .vt_pixel_clk = 87172500,//360000000, //default
    .op_pixel_clk = 174400000, //default
    .binning_factor = 0,
    .max_fps = 15,
    .min_fps = 7.5,
    .mode = SENSOR_DEFAULT_MODE,
  },
  {
    .x_output = 0x0500,//1280
    .y_output = 0x03C0,//960
    .line_length_pclk = 0xB86,//2900
    .frame_length_lines = 0x03D7,//983
    .vt_pixel_clk = 86995500,//179200000, //default
    .op_pixel_clk = 174400000, //default
    .binning_factor = 1,
    .max_fps = 30,
    .min_fps = 7.5,
    .mode = SENSOR_DEFAULT_MODE,
  },
  {
    .x_output = 0x0780,//1920
    .y_output = 0x05A0,//1440
    .line_length_pclk = 0xB86,//2950
    .frame_length_lines = 0x7E9,//2025
    .vt_pixel_clk = 179212500, //default
    .op_pixel_clk = 360000000, //default
    .binning_factor = 0,
    .max_fps = 30,
    .min_fps = 7.5,
    .mode = SENSOR_DEFAULT_MODE,
  },
  {
    .x_output = 0x0500,//1280
    .y_output = 0x03C0,//960
    .line_length_pclk = 0xB86,//2900
    .frame_length_lines = 0x3F4,//991
    .vt_pixel_clk = 179124000, //default
    .op_pixel_clk = 360000000, //default
    .binning_factor = 1,
    .max_fps = 60,
    .min_fps = 7.5,
    .mode = SENSOR_DEFAULT_MODE,
  },
};

static struct sensor_lib_out_info_array out_info_array = {
  .out_info = sensor_out_info,
  .size = ARRAY_SIZE(sensor_out_info),
};

static sensor_res_cfg_type_t s5k5e2_res_cfg[] = {
  SENSOR_SET_STOP_STREAM,
  SENSOR_SET_NEW_RESOLUTION, /* set stream config */
  SENSOR_SET_CSIPHY_CFG,
  SENSOR_SET_CSID_CFG,
  SENSOR_LOAD_CHROMATIX, /* set chromatix prt */
  SENSOR_SEND_EVENT, /* send event */
  SENSOR_SET_START_STREAM,
};

static struct sensor_res_cfg_table_t s5k5e2_res_table = {
  .res_cfg_type = s5k5e2_res_cfg,
  .size = ARRAY_SIZE(s5k5e2_res_cfg),
};

static struct sensor_lib_chromatix_t s5k5e2_chromatix[] = {
  {
    .common_chromatix = S5K5E2_LOAD_CHROMATIX(common),
    .camera_preview_chromatix = S5K5E2_LOAD_CHROMATIX(snapshot), /* RES0 */
    .camera_snapshot_chromatix = S5K5E2_LOAD_CHROMATIX(snapshot), /* RES0 */
    .camcorder_chromatix = S5K5E2_LOAD_CHROMATIX(default_video), /* RES0 */
    .liveshot_chromatix = S5K5E2_LOAD_CHROMATIX(liveshot), /* RES0 */
  },
  {
    .common_chromatix = S5K5E2_LOAD_CHROMATIX(common),
    .camera_preview_chromatix = S5K5E2_LOAD_CHROMATIX(preview), /* RES1 */
    .camera_snapshot_chromatix = S5K5E2_LOAD_CHROMATIX(preview), /* RES1 */
    .camcorder_chromatix = S5K5E2_LOAD_CHROMATIX(preview), /* RES1 */
    .liveshot_chromatix = S5K5E2_LOAD_CHROMATIX(liveshot), /* RES1 */
  },
};

static struct sensor_lib_chromatix_array s5k5e2_lib_chromatix_array = {
  .sensor_lib_chromatix = s5k5e2_chromatix,
  .size = ARRAY_SIZE(s5k5e2_chromatix),
};

/*===========================================================================
 * FUNCTION    - s5k5e2_real_to_register_gain -
 *
 * DESCRIPTION:
 *==========================================================================*/
static uint16_t s5k5e2_real_to_register_gain(float gain)
{
  uint16_t reg_gain;

  if (gain < 1.0)
    gain = 1.0;

  if (gain > 16.0)
    gain = 16.0;

  reg_gain = (uint16_t)(gain * 32.0);

  return reg_gain;
}

/*===========================================================================
 * FUNCTION    - s5k5e2_register_to_real_gain -
 *
 * DESCRIPTION:
 *==========================================================================*/
static float s5k5e2_register_to_real_gain(uint16_t reg_gain)
{
  float gain;

  if (reg_gain > 0x0200)
    reg_gain = 0x0200;

  gain = (float) reg_gain / 32.0;

  return gain;
}

/*===========================================================================
 * FUNCTION    - s5k5e2_calculate_exposure -
 *
 * DESCRIPTION:
 *==========================================================================*/
static int32_t s5k5e2_calculate_exposure(float real_gain,
  uint16_t line_count, sensor_exposure_info_t *exp_info)
{
  if (!exp_info) {
    return -1;
  }
  exp_info->reg_gain = s5k5e2_real_to_register_gain(real_gain);
  exp_info->sensor_real_gain = s5k5e2_register_to_real_gain(exp_info->reg_gain);
  exp_info->digital_gain = real_gain / exp_info->sensor_real_gain;
  exp_info->line_count = line_count;
  exp_info->sensor_digital_gain = 0x1;
  return 0;
}

/*===========================================================================
 * FUNCTION    - s5k5e2_fill_exposure_array -
 *
 * DESCRIPTION:
 *==========================================================================*/
static int32_t s5k5e2_fill_exposure_array(uint16_t gain, uint32_t line,
  uint32_t fl_lines, int32_t luma_avg, uint32_t fgain,
  struct msm_camera_i2c_reg_setting *reg_setting)
{
  int32_t rc = 0;
  uint16_t reg_count = 0;
  uint16_t i = 0;

  if (!reg_setting) {
    return -1;
  }

  for (i = 0; i < sensor_lib_ptr.groupon_settings->size; i++) {
	reg_setting->reg_setting[reg_count].reg_addr =
	  sensor_lib_ptr.groupon_settings->reg_setting[i].reg_addr;
	reg_setting->reg_setting[reg_count].reg_data =
	  sensor_lib_ptr.groupon_settings->reg_setting[i].reg_data;
	reg_count = reg_count + 1;
  }

	reg_setting->reg_setting[reg_count].reg_addr =
	sensor_lib_ptr.output_reg_addr->frame_length_lines;
	reg_setting->reg_setting[reg_count].reg_data = (fl_lines & 0xFF00) >> 8;
	reg_count++;

	reg_setting->reg_setting[reg_count].reg_addr =
	sensor_lib_ptr.output_reg_addr->frame_length_lines + 1;
	reg_setting->reg_setting[reg_count].reg_data = (fl_lines & 0xFF);
	reg_count++;

	reg_setting->reg_setting[reg_count].reg_addr =
	sensor_lib_ptr.exp_gain_info->coarse_int_time_addr;
	reg_setting->reg_setting[reg_count].reg_data = (line & 0xFF00) >> 8;
	reg_count++;

	reg_setting->reg_setting[reg_count].reg_addr =
	sensor_lib_ptr.exp_gain_info->coarse_int_time_addr + 1;
	reg_setting->reg_setting[reg_count].reg_data = (line & 0xFF);
	reg_count++;

	reg_setting->reg_setting[reg_count].reg_addr =
	sensor_lib_ptr.exp_gain_info->global_gain_addr;
	reg_setting->reg_setting[reg_count].reg_data = (gain & 0xFF00) >> 8;
	reg_count++;

	reg_setting->reg_setting[reg_count].reg_addr =
	sensor_lib_ptr.exp_gain_info->global_gain_addr + 1;
	reg_setting->reg_setting[reg_count].reg_data = (gain & 0xFF);
	reg_count++;

	for (i = 0; i < sensor_lib_ptr.groupoff_settings->size; i++) {
	reg_setting->reg_setting[reg_count].reg_addr =
	  sensor_lib_ptr.groupoff_settings->reg_setting[i].reg_addr;
	reg_setting->reg_setting[reg_count].reg_data =
	  sensor_lib_ptr.groupoff_settings->reg_setting[i].reg_data;
	reg_count = reg_count + 1;
  }

	reg_setting->size = reg_count;
	reg_setting->addr_type = MSM_CAMERA_I2C_WORD_ADDR;
	reg_setting->data_type = MSM_CAMERA_I2C_BYTE_DATA;
	reg_setting->delay = 0;

  return rc;
}

static sensor_exposure_table_t s5k5e2_expsoure_tbl = {
  .sensor_calculate_exposure = s5k5e2_calculate_exposure,
  .sensor_fill_exposure_array = s5k5e2_fill_exposure_array,
};

static sensor_lib_t sensor_lib_ptr = {
  /* sensor slave info */
  .sensor_slave_info = &sensor_slave_info,
  /* sensor init params */
  .sensor_init_params = &sensor_init_params,
  /* sensor output settings */
  .sensor_output = &sensor_output,
  /* sensor output register address */
  .output_reg_addr = &output_reg_addr,
  /* sensor exposure gain register address */
  .exp_gain_info = &exp_gain_info,
  /* sensor aec info */
  .aec_info = &aec_info,
  /* sensor snapshot exposure wait frames info */
  .snapshot_exp_wait_frames = 1,
  /* number of frames to skip after start stream */
  .sensor_num_frame_skip = 1,
  /* number of frames to skip after start HDR stream */
  .sensor_num_HDR_frame_skip = 2,
  /* sensor pipeline immediate delay */
  .sensor_max_pipeline_frame_delay = 1,
  /* sensor exposure table size */
  .exposure_table_size = 8,
  /* sensor lens info */
  .default_lens_info = &default_lens_info,
  /* csi lane params */
  .csi_lane_params = &csi_lane_params,
  /* csi cid params */
  .csi_cid_params = s5k5e2_cid_cfg,
  /* csi csid params array size */
  .csi_cid_params_size = ARRAY_SIZE(s5k5e2_cid_cfg),
  /* init settings */
  .init_settings_array = &init_settings_array,
  /* start settings */
  .start_settings = &start_settings,
  /* stop settings */
  .stop_settings = &stop_settings,
  /* group on settings */
  .groupon_settings = &groupon_settings,
  /* group off settings */
  .groupoff_settings = &groupoff_settings,
  /* resolution cfg table */
  .sensor_res_cfg_table = &s5k5e2_res_table,
  /* res settings */
  .res_settings_array = &res_settings_array,
  /* out info array */
  .out_info_array = &out_info_array,
  /* crop params array */
  .crop_params_array = &crop_params_array,
  /* csi params array */
  .csi_params_array = &csi_params_array,
  /* sensor port info array */
  .sensor_stream_info_array = &s5k5e2_stream_info_array,
  /* exposure funtion table */
  .exposure_func_table = &s5k5e2_expsoure_tbl,
  /* chromatix array */
  .chromatix_array = &s5k5e2_lib_chromatix_array,
  /* sensor pipeline immediate delay */
  .sensor_max_immediate_frame_delay = 2,
};

/*===========================================================================
 * FUNCTION    - s5k5e2_q5s09l_open_lib -
 *
 * DESCRIPTION:
 *==========================================================================*/
void *s5k5e2_open_lib(void)
{
  return &sensor_lib_ptr;
}
