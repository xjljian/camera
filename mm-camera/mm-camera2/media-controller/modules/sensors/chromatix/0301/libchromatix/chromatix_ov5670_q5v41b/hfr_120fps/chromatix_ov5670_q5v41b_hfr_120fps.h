/*========================================================================
                          C H R O M A T I X

Copyright (c) 2014 Qualcomm Technologies, Inc. All Rights Reserved.
Qualcomm Technologies Proprietary and Confidential.
==========================================================================*/

/* Chromatix common DMSS header file version number */
0x0301,
0, // Not compressed
1, // Revision
/* VFE Blocks */
{
   /* Black-Level Subtraction */
   {

/*********************************************************************/
// Feature name :
// Use gain or lux_index to control black level subtraction.
// Range: 0 or 1.
// 0 means to use lux_index to control.
// 1 means to use gain to control.
/*********************************************************************/

      0, /* Control Method - 1 = Gain, 0 = Lux Index */

/*********************************************************************/
// Feature name :
// Trigger point for black level subtraction.
// gain start :
// When gain >= gain_start, lowlight black level is interpolated with normal black level.
// Range: min_gain to max_gain. Gain means digital and analog combined gain.
// Effect: Increasing this value will use lowlight black level under lower light condition.
//
// gain end:
// When gain >= gain_end, 100% lowlight black level is used.
// Range: min_gain to max_gain. Gain means digital and analog combined gain.
// Constraint: gain_end > gain_start.
// Effect: Increasing this value will use 100% lowlight black level under lower light condition.
//
// lux_index_start:
// When lux_index >= lux_index_start, lowlight black level is interpolated with normal black level.
// Range: For linear AFR case: 0 to max_index from exposure table.
//          For non-linear AFR case : 0 to max_index*numberof_FPS_supported.
// Effect: Increasing this value will use lowlight black level under lower light condition.
//
// lux_index_end:
// When lux_index >= lux_index_end, 100% lowlight black level is used.
// Range: For linear AFR case: 0 to max_index from exposure table.
//          For non-linear AFR case : 0 to max_index*numberof_FPS_supported.
// Constraint: lux_index_end > lux_index_start.
// Effect: Increasing this value will use 100% lowlight black level under lower light condition.
//
/*********************************************************************/

      /* Low-Light Trigger Points */
      {
         7.200000f, /* Gain Start */
         8.000000f, /* Gain End */
         338, /* Lux Index Start */
         376, /* Lux Index End */
      },

/*********************************************************************/
// Feature name :
// Amount of black level increase under lowlight.
// Range: 0 to "black level offset"(next entry in chromatix header)
// Constraint: Smaller than or equal to "black level offset".
// Effect: Larger value will increase signal level but has less contrast.
/*********************************************************************/

      0, /* Max Black Increase */

/*********************************************************************/
// Feature name :
// 4 channel Black level offsets under normal and bright light.
// This set parameters is used in QSC6270(6240), QSC6295, QSD8x50.
// Range: 0 to 1023 for MSM7x25, MSM7x27 and QSD8x50; 0 to 256 for QSC6270(6240), QSC6295.
// Effect: Usually we should use sensor recommended value. Smaller value will
//           reduce contrast and has "foggy" effect.
/*********************************************************************/

      /* Four Channel Normal Light Black-Level */
      {64, 64, 64, 64},
   },
   /* Channel Balance Gains */
   {1.000000f, 1.000000f, 1.000000f, 1.000000f},

/******************************************************************************/
// Feature name : ABF2.
// Applicale chipset: QSD8x60, MSM7x30 and later.
// Applicable operation mode:  For VF and snapshot.
//
// Desription of variables in chromatix_adaptive_bayer_filter_data_type2
// structure.
//
// Variable names: threshold_red[3], threshold_green[3],threshold_blue[3].
// The three threshold values for each of
// the red, green, and blue channels define boundaries for smoothing,
// no-processing, and sharpening regions of ABF filter.
// Default values (for 12-bit data):
//   low-light : threshold_red[0]=24*16; threshold_red[1]=24*16; threshold_red[2]=25*16;
//   med-light : threshold_red[0]=21*16; threshold_red[1]=21*16; threshold_red[2]=22*16;
//   high-light: threshold_red[0]=18*16; threshold_red[1]=18*16; threshold_red[2]=19*16;
//   Default values of threshold_green[0-2] and threshold_blue[0-2] are same as
//   threshold_red[0-2] for different exposure levels
// Data range: 0 to 255*16 (for 12-bit data).
// Constraints: threshold_red[0] <= threshold_red[1] < threshold_red[2].
// Effect: Larger value for threshold_red[0] will result in increased smoothing area;
// larger value for threshold_red[1] will result in reduced sharpening area.
//
// Variable names: scale_factor_red[2], scale_factor_green[2],scale_factor_blue[2].
// Control extent of smoothing and sharpening in
// smoothing and sharpening regions of the new ABF filter.
// Default values:
//   low-light  : scale_factor_red[0]=0.80; scale_factor_red[1]=0.04;
//   med-light  : scale_factor_red[0]=0.68; scale_factor_red[1]=0.04;
//   high-light : scale_factor_red[0]=0.50; scale_factor_red[1]=0.04;
//   Default values of scale_factor_green[0-1] and scale_factor blue[0-1] are
//   same as scale_factor_red[0-1] for different exposure levels
// Data range: 0 to 1.
// Constraints: 0 < scale_factor_red[0-1] <= 1; similar contrasints applicable
// to green- and blue-channel scaling factors.
// Effect: Larger value for scale_factor_red\green\blue[0] increases smoothing in
// smoothing region of ABF filter; larger value for scale_factor_red\green\blue[1]
// increases sharpening in sharpening region of ABF filter.
//
// variable name: a[2]
// Spatial component of ABF filter; controls
// influence of neighboring pixels on output pixel value
// default values:
//   low-light  : a[0] = a[1] = 1;
//   med-light  : a[0] = a[1] = 1;
//   high-light : a[0] = a[1] = 1;
// Data range: 0 to 1.
// Constraints: 0 <= a[0-1] <= 1;
// Effect: When a[0] = a[1] = 0, ABF is essentially turned off; When a[0] = a[1] = 1,
// we see maximum smoothing/sharpening effects of applying the ABF filter.
//
// Variable name: table_pos[16].
// Lookup table values determine
// amount of smoothing at different levels of local gradient magnitude.
// Default values:
// table_pos[16] = {1.0000, 0.9764, 0.9214, 0.8346, 0.7244, 0.6063, 0.4882,
//     0.3780, 0.2756, 0.1969, 0.1339, 0.0866, 0.0551, 0.0315, 0.0236, 0.0079};
// Data range: 0 to 1.
// Constraints: 0 <= table_pos[0-15] <= 1;
// Effect: Larger values for table_pos[0-15] entries represent increased amount of
// smoothing. We do not recommend changing these values.
//
// Variable name: table_neg[8].
// Lookup table values determine
// amount of sharpening at different values of local gradient magnitude.
// Default values:
// table_neg[8] = {-1.000, -1.000, -1.000, -1.000, -1.000, -1.000, -1.000, -1.000}.
// Data range: -1.000 to 0.000
// Constraints: -1.0 <= table_neg[0-7] <= 0.0;
// Effect: Larger values for table_neg[0-7] represent increased amount of
// sharpening. We do not recommend changing these values.
/******************************************************************************/

   /* Adaptive Bayer Filter 2 */
   {
      1, /* Control Method - 1 = Gain, 0 = Lux Index */
      56, /* Enable Lux Index */
      
/******************************************************************************/
// Feature name : ABF2 Low Light Trigger Points
/******************************************************************************/

      /* ABF2 Low Light Trigger Points */
      {
         7.600000f, /* Gain Start */
         8.000000f, /* Gain End */
         338, /* Lux Index Start */
         376, /* Lux Index End */
      },

/******************************************************************************/
// Feature name : ABF2 Bright Light Trigger Points
/******************************************************************************/

      /* ABF2 Bright Light Trigger Points */
      {
         2.000000f, /* Gain Start */
         1.000000f, /* Gain End */
         188, /* Lux Index Start */
         169, /* Lux Index End */
      },

/******************************************************************************/
// Feature name : ABF2 Low Light parameters
/******************************************************************************/

      /* ABF2 Low Light */
      {
         /* Red channel parameters */
         {256, 272, 2256}, /* 12-bit pixels */
         {0.522295f, 0.000000f},

         /* Green channel parameters */
         {256, 272, 2256}, /* 12-bit pixels */
         {0.419875f, 0.000000f},
         {1.000000f, 1.000000f},

         /* Blue channel parameters */
         {256, 272, 2256}, /* 12-bit pixels */
         {0.572281f, 0.000000f},

         /* Positive table */
         {
            1.000000f, 1.000000f, 1.000000f, 1.000000f,
            0.958504f, 0.873343f, 0.762780f, 0.627080f,
            0.544563f, 0.420712f, 0.328491f, 0.243769f,
            0.186971f, 0.111392f, 0.051032f, 0.020852f
         },
         /* Negative table */
         {
            -0.375422f, -0.780031f, -1.000000f, -0.774302f,
            -0.542681f, -0.285798f, -0.229886f, -0.015727f
         },
      },
      /* ABF2 Normal Light */
      {
         /* Red channel parameters */
         {224, 240, 2256}, /* 12-bit pixels */
         {0.352766f, 0.000000f},

         /* Green channel parameters */
         {224, 240, 2256}, /* 12-bit pixels */
         {0.283933f, 0.000000f},
         {1.000000f, 1.000000f},

         /* Blue channel parameters */
         {224, 240, 2256}, /* 12-bit pixels */
         {0.386404f, 0.000000f},

         /* Positive table */
         {
            1.000000f, 1.000000f, 1.000000f, 1.000000f,
            1.000000f, 0.946446f, 0.835988f, 0.694184f,
            0.638193f, 0.501802f, 0.409604f, 0.306424f,
            0.242332f, 0.189711f, 0.089156f, 0.042842f
         },
         /* Negative table */
         {
            -0.296074f, -0.956122f, -0.984580f, -0.577663f,
            -0.466037f, -0.286912f, -0.148290f, -0.044771f
         },
      },
      /* ABF2 Bright Light */
      {
         /* Red channel parameters */
         {176, 192, 2256}, /* 12-bit pixels */
         {0.283659f, 0.000000f},

         /* Green channel parameters */
         {176, 192, 2256}, /* 12-bit pixels */
         {0.210544f, 0.000000f},
         {1.000000f, 1.000000f},

         /* Blue channel parameters */
         {176, 192, 2256}, /* 12-bit pixels */
         {0.282417f, 0.000000f},

         /* Positive table */
         {
            1.000000f, 1.000000f, 1.000000f, 1.000000f,
            1.000000f, 1.000000f, 0.961824f, 0.920340f,
            0.793686f, 0.710718f, 0.584064f, 0.450794f,
            0.390070f, 0.224029f, 0.178934f, 0.082131f
         },
         /* Negative table */
         {
            -0.225386f, -1.000000f, -0.832691f, -0.403374f,
            -0.514555f, -0.184732f, -0.070245f, -0.062097f
         },
      },
   },
   /* Bad Pixel Correction */
   {

/*********************************************************************/
// Feature name : bad pixel correction parameters
// Fmin and Fmax are used for bad pixel correction (BPC).
// Range: 1 to 127.
// Constraint: Fmax > Fmin.
// Effect: Smaller Fmin and higher Fmax will have least amount of correction.
//        Setting Fmax=Fmin will have the max amount of correction.
/*********************************************************************/


/*********************************************************************/
// Feature name :
// The following BPC parameters are used for QSD8x50, QSC6270(6240), QSC6295,MSM7x25, MSM7x27.
//
/*********************************************************************/


/*********************************************************************/
// Feature name :
// Use gain or lux_index to control BPC.
// Range: 0 or 1.
// 0 means to use lux_index to control.
// 1 means to use gain to control.
/*********************************************************************/

      0, /* Control Method - 1 = Gain, 0 = Lux Index */

/*********************************************************************/
// Feature name :
// Trigger point for lowlight BPC.
// gain start :
// When gain >= gain_start, lowlight BPC is interpolated with normal BPC.
// Range: min_gain to max_gain. Gain means digital and analog combined gain.
// Effect: Increasing this value will use lowlight BPC under lower light condition.
//
// gain end:
// When gain >= gain_end, 100% lowlight BPC is used.
// Range: min_gain to max_gain. Gain means digital and analog combined gain.
// Constraint: gain_end > gain_start.
// Effect: Increasing this value will use 100% lowlight BPC under lower light condition.
//
// lux_index_start:
// When lux_index >= lux_index_start, lowlight BPC is interpolated with normal BPC.
// Range: For linear AFR case: 0 to max_index from exposure table.
//          For non-linear AFR case : 0 to max_index*numberof_FPS_supported.
// Effect: Increasing this value will use lowlight BPC under lower light condition.
//
// lux_index_end:
// When lux_index >= lux_index_end, 100% lowlight BPC is used.
// Range: for linear AFR case: 0 to max_index from exposure table.
//          For non-linear AFR case : 0 to max_index*numberof_FPS_supported.
// Constraint: lux_index_end > lux_index_start.
// Effect: Increasing this value will use 100% lowlight BPC under lower light condition.
//
/*********************************************************************/

      /* Low-Light Trigger Points */
      {
         7.600000f, /* Gain Start */
         8.000000f, /* Gain End */
         338, /* Lux Index Start */
         376, /* Lux Index End */
      },
      32, /* Fmin */
      96, /* Fmax */
      64, /* Lowlight Fmin */
      64, /* Lowlight Fmax */

/******************************************************************************/
// Feature name : bad pixel correction.
// Applicable chipset:  MSM7x30, QSD8x60 and later.
// Applicable operation mode: Viewfinder and snapshot.
//
// Variable name: bpc_offset_r_hi.
// Red channel pixel difference higher offset value.
// Default value: 0.
// Data range: 0 to 1023.
// Constraints: bpc_offset_r_hi >= bpc_offset_r_lo.
// Effect: Higher value results in less DPC to be corrected.
//
// Variable name: bpc_offset_r_lo.
// Red channel pixel difference lower offset value.
// Default value: 0.
// Data range: 0 to 1023.
// Constraints: bpc_offset_r_hi >= bpc_offset_r_lo.
// Effect: Higher value results in less DPC to be corrected.
//
// Variable name: bpc_offset_gr_hi.
// Green (next to red) channel pixel difference higher offset value
// Default Value: 0.
// Data Range: 0 to 1023.
// Constraints: bpc_offset_gr_hi >= bpc_offset_gr_lo.
// Effect: Higher value results in less DPC to be corrected.
//
// Variable name: bpc_offset_gr_lo.
// Green (next to red) channel pixel difference lower offset value
// Default Value: 0.
// Data Range: 0 to 1023.
// Constraints: bpc_offset_gr_hi >= bpc_offset_gr_lo.
// Effect: Higher value results in less DPC to be corrected.
//
// Variable name: bpc_offset_gb_hi.
// Green (next to blue) channel pixel difference higher offset value.
// Default value: 0.
// Data range: 0 to 1023.
// Constraints: bpc_offset_gb_hi >= bpc_offset_gb_lo.
// Effect: Higher value results in less DPC to be corrected.
//
// Variable name: bpc_offset_gb_lo.
// Green (next to blue) channel pixel difference lower offset value.
// Default value: 0.
// Data range: 0 to 1023.
// Constraints: bpc_offset_gb_hi >= bpc_offset_gb_lo.
// Effect: Higher value results in less DPC to be corrected.
//
// Variable name: bpc_offset_b_hi.
// Blue channel pixel difference higher offset value.
// Default value: 0.
// Data range: 0 to 1023.
// Constraints: bpc_offset_b_hi >= bpc_offset_b_lo.
// Effect: Higher value results in less DPC to be corrected.
//
// variable name: bpc_offset_b_lo.
// Description:  Blue channel pixel difference lower offset value.
// Default value: 0.
// Data range: 0 to 1023.
// Constraints: bpc_offset_b_hi >= bpc_offset_b_lo.
// Effect: Higher value results in less DPC to be corrected.
/******************************************************************************/

      /* Offsets */
      {
         /* Normal Light */
         {
            20, /* R Hi */
            20, /* R Lo */
            20, /* Gr Hi */
            20, /* Gr Lo */
            20, /* Gb Hi */
            20, /* Gb Lo */
            20, /* B Hi */
            20, /* B Lo */
         },
         /* Low Light */
         {
            2, /* R Hi */
            2, /* R Lo */
            2, /* Gr Hi */
            2, /* Gr Lo */
            2, /* Gb Hi */
            2, /* Gb Lo */
            2, /* B Hi */
            2, /* B Lo */
         },
      },

/******************************************************************************/
// Feature name : bad cluster correction (BCC)
/******************************************************************************/

      0, /* Control Method - 1 = Gain, 0 = Lux Index */

/******************************************************************************/
// Feature name : BCC lowlight trigger points
/******************************************************************************/

      /* Low-Light Trigger Points */
      {
         7.600000f, /* Gain Start */
         8.000000f, /* Gain End */
         338, /* Lux Index Start */
         376, /* Lux Index End */
      },
      32, /* Fmin */
      96, /* Fmax */
      32, /* Lowlight Fmin */
      96, /* Lowlight Fmax */

/******************************************************************************/
// Feature name : BCC offset parameters
// Applicable chipset:  8960 and later.
// Applicable operation mode: Viewfinder and snapshot.
//
// Variable name: bcc_offset_r_hi.
// Red channel pixel difference higher offset value.
// Default value: 0.
// Data range: 0 to 1023.
// Constraints: bcc_offset_r_hi >= bcc_offset_r_lo.
// Effect: Higher value results in less BCC to be corrected
//
// Variable name: bcc_offset_r_lo.
// Red channel pixel difference lower offset value.
// Default value: 0.
// Data range: 0 to 1023.
// Constraints: bcc_offset_r_hi >= bcc_offset_r_lo.
// Effect: Higher value results in less DCC to be corrected.
//
// Variable name: bcc_offset_gr_hi.
// Green(next to red) channel pixel difference higher offset value.
// Default value: 0.
// Data range: 0 to 1023.
// Constraints: bcc_offset_gr_hi >= bcc_offset_gr_lo.
// Effect: Higher value results in less DCC to be corrected.
//
// Variable name: bcc_offset_gr_lo.
// Green(next to red) channel pixel difference lower offset value.
// Default value: 0.
// Data range: 0 to 1023.
// Constraints: bcc_offset_gr_hi >= bcc_offset_gr_lo.
// Effect: Higher value results in less DCC to be corrected.
//
// Variable name: bcc_offset_gb_hi.
// Green (next to blue) channel pixel difference higher offset value.
// Default value: 0.
// Data range: 0 to 1023.
// Constraints: bcc_offset_gb_hi >= bcc_offset_gb_lo.
// Effect: Higher value results in less DCC to be corrected.
//
// Variable name: bcc_offset_gb_lo.
// Green (next to blue) channel pixel difference lower offset value.
// Default value: 0.
// Data range: 0 to 1023.
// Constraints: bcc_offset_gb_hi >= bcc_offset_gb_lo.
// Effect: Higher value results in less DCC to be corrected.
//
// Variable name: bcc_offset_b_hi.
// Blue channel pixel difference higher offset value.
// Default value: 0.
// Data range: 0 to 1023.
// Constraints: bcc_offset_b_hi >= bcc_offset_b_lo.
// Effect: Higher value results in less DCC to be corrected.
//
// Variable name: bcc_offset_b_lo.
// Blue channel pixel difference lower offset value.
// Default value: 0.
// Data range: 0 to 1023.
// Constraints: bcc_offset_b_hi >= bcc_offset_b_lo.
// Effect: Higher value results in less DCC to be corrected.
/******************************************************************************/

      /* Offsets */
      {
         /* Normal Light */
         {
            0, /* R Hi */
            0, /* R Lo */
            0, /* Gr Hi */
            0, /* Gr Lo */
            0, /* Gb Hi */
            0, /* Gb Lo */
            0, /* B Hi */
            0, /* B Lo */
         },
         /* Low Light */
         {
            0, /* R Hi */
            0, /* R Lo */
            0, /* Gr Hi */
            0, /* Gr Lo */
            0, /* Gb Hi */
            0, /* Gb Lo */
            0, /* B Hi */
            0, /* B Lo */
         },
      },
   },
   /* Demosaic3 */
   {
      0, /* Control Method - 1 = Gain, 0 = Lux Index */

/******************************************************************************/
// Feature name : Demosaic3 lowlight trigger points
/******************************************************************************/

      /* Low-Light Trigger Points */
      {
         7.600000f, /* Gain Start */
         8.000000f, /* Gain End */
         338, /* Lux Index Start */
         376, /* Lux Index End */
      },

/******************************************************************************/
// Feature name: Demosaic3.
// Applicale chipset(s): 8960, 8x55A and later chipsets.
// Applicable operation mode:
//     Viewfinder, snapshot processing, and video modes.
// 3A mode: N/A.
//
// Variable name: wk[18] // HW: 10uQ10
// Discrete adaboost parameters required for local window classification.
// Default value: {0.1338, 0.0889, 0.0889, 0.9990, 0.9004, 0.0908, 0.1904,
// 0.0967, 0.0625, 0.3115, 0.1924, 0.0859, 0.0820, 0.1064,  0.1475, 0.0957,
// 0.0645, 0.0742}.
// Range for each element in 18-D array: [0,1.0].
// The classification parameters are optimized in an offline
// training process. Once the parameters are optimized, they remain fixed.
//
// Variable name: bk[18]  // HW: 1uQ0
// Discrete adaboost parameters required for local window classification.
// Default: {1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1}.
// Range for each element in 18-D array: {0,1}.
// The classification parameters are optimized in an offline
// training process. Once the parameters are optimized, they remain fixed.
//
// Variable name: lk[18]  // HW: 4uQ0
// Discrete adaboost parameters required for local window classification.
// Default value: {0, 0, 1, 2, 2, 3, 9, 9, 9, 4, 4, 5, 6, 7, 8, 8, 10, 10}.
// Range for each element in 18-D array is {0, 1, ..., 12}.
// The classification parameters are optimized in an offline
// training process. Once the parameters are optimized, they remain fixed.
//
// Variable name: Tk[18]  // HW: 10sQ0
// Discrete adaboost parameters required for local window classification.
// Default:     {2, 1, 0, 0, -1, 2, 0, -1, 1, 0, -1, 2, 0, 2, 2, 1, 0, 100}.
// Range for each element in 18-D array {-512, ..., 511}
// The classification parameters are optimized in an offline training process.
// Once the parameters are optimized, they remain fixed.
/******************************************************************************/

      /* Demosaic LUT */
      {
         /* wk */
         {
            0.133800f, 0.088900f, 0.088900f, 0.999000f, 0.900400f, 0.090800f, 0.190400f, 0.096700f, 0.062500f,
            0.311500f, 0.192400f, 0.085900f, 0.082000f, 0.106400f, 0.147500f, 0.095700f, 0.064500f, 0.074200f
         },
         /* bk */
         {
            1, 0, 1, 1, 0, 1, 1, 0, 0,
            1, 0, 1, 1, 1, 1, 0, 1, 1
         },
         /* lk */
         {
            0, 0, 1, 2, 2, 3, 9, 9, 9,
            4, 4, 5, 6, 7, 8, 8, 10, 10
         },
         /* Tk */
         {
            2, 1, 0, 0, -1, 2, 0, -1, 1,
            0, -1, 2, 0, 2, 2, 1, 0, 100
         },
      },

/******************************************************************************/
// Applicale chipset(s): 8960, 8x55A and later chipsets.
// Applicable operation mode:
//     Viewfinder, snapshot processing, and video modes.
// 3A mode: N/A.
//
// Variable names: demosic3_aG[2] //HW: 6uQ6
// Green-channel interpolation parameter (2 light conditions).
// Default value: 0.4 (for each light condition).
// Range: [0.3,0.5].
// This parameter is used to control the tradeoff between noise
// suppression and aliasing. A higher value of this variable provides more
// noise suppression but, on the negative side, leads to higher aliasing.
// For best performance, this parameter should be optimized separately for
// low, medium, and high lux-index levels. The default value shown above works
// reasonably well for all lux-index levels, and for both snapshot and
// viewfinder modes.
//
// Variable names: demosic3_bL[2] //HW: 8uQ8
// Green-channel interpolation parameter (2 light conditions).
// Default value: 0.0 (for each light condition).
// Range: [0,0.46].
// In general, a low value of this parameter provides better noise
// suppression while a high value of bL provides better detail preservation.
// For best performance, the parameters should be optimized separately for low,
// medium, and high lux-index levels. The default value shown above works
// reasonably well for all lux-index levels and for both preview and snapshot
// modes.
/******************************************************************************/

      /* aG */
      {
         0.400000f, /* aG[0] */
         0.400000f, /* aG[1] */
      },
      /* bL */
      {
         0.000000f, /* bL[0] */
         0.000000f, /* bL[1] */
      },
   },
   /* Chroma and Luma Filters */
   {
      1, /* Control Method - 1 = Gain, 0 = Lux Index */

/******************************************************************************/
// Feature name : Chroma filter lowlight trigger points.
/******************************************************************************/

      /* Low-Light Trigger Points */
      {
         7.600000f, /* Gain Start */
         8.000000f, /* Gain End */
         338, /* Lux Index Start */
         376, /* Lux Index End */
      },
      1, /* Enable Index */

/******************************************************************************/
// Feature name : Chroma filter.
// Applicale chipset(s): 8960, 8x55A and later chipsets.
// Applicable operation mode:
//     Viewfinder, snapshot processing, and video modes.
//  3A mode: N/A.
//
// Variable name: h[4]
// Horizontal component of separable Gaussian filter.
// Default value : {0.1429, 0.1429, 0.1429, 0.142}.
// Range of each component of array: [0,1.0].
// Constraints: h[0]>=h[1] >=h[2] >=h[3]; h[0]+2*h[1]+2*h[2]+2*h[3] = 1.
// Effect: Smoothing amount decreaes as h[1], h[2], and h[3] get smaller.
// The default value shown above works great for all lux-index levels,
// and for both viewfinder and snapshot modes. However, for greater
// flexibility, current recommendation is to tune it separately for different
// lux-index levels.
//
// Variable name: v[2]
// Vertical component of separable Gaussian filter.
// Default value: {0.3333, 0.3333}.
// Range of each component of array [0,1.0].
// Constraints: v[0]>=v[1]; v[0]+2*v[1] = 1.
// Effect: Smoothing amount decreases as v[1] gets smaller.
// The default value shown above works great for all lux-index levels and
// for both viewfinder and snapshot modes. However, for greater flexibility,
// current recommendation is to tune it separately for different lux-index
// levels.
/******************************************************************************/

      /* Filters */
      {
         /* Lowlight Chroma Filter */
         {
            /* H */
            {
               1.000000f, 0.000000f, 0.000000f, 0.000000f
            },
            /* V */
            {
               1.000000f, 0.000000f
            },
         },
         /* Normal Light Chroma Filter */
         {
            /* H */
            {
               1.000000f, 0.000000f, 0.000000f, 0.000000f
            },
            /* V */
            {
               1.000000f, 0.000000f
            },
         },
      },
      1, /* Control Method - 1 = Gain, 0 = Lux Index */

/******************************************************************************/
// Feature name : Luma filter low light trigger points.
/******************************************************************************/

      /* Low-Light Trigger Points */
      {
         7.600000f, /* Gain Start */
         8.000000f, /* Gain End */
         338, /* Lux Index Start */
         376, /* Lux Index End */
      },

/******************************************************************************/
// Feature name : Luma filter bright light trigger points.
/******************************************************************************/

      /* Bright Light Trigger Points */
      {
         2.000000f, /* Gain Start */
         1.000000f, /* Gain End */
         188, /* Lux Index Start */
         169, /* Lux Index End */
      },
      1, /* Enable Index */

/******************************************************************************/
// Feature name : Luma filter low light parameters.
/******************************************************************************/

      /* Luma Filter Low Light */
      {
         /* Thresholds */
         {320, 336, 2576}, /* 12-bit pixels */
         /* Scale Factors */
         {0.855975f, 0.000000f},

         /* Positive table */
         {
            1.000000f, 1.000000f, 1.000000f, 0.958119f,
            0.895297f, 0.820426f, 0.658637f, 0.505342f,
            0.414471f, 0.278163f, 0.210812f, 0.165911f,
            0.105804f, 0.049318f, 0.025375f, 0.010034f
         },
         /* Negative table */
         {
            -0.007342f, -1.000000f, -0.151464f, -0.982590f,
            -0.271603f, -0.094906f, -0.138952f, -0.624776f
         },
      },

/******************************************************************************/
// Feature name : Luma filter normal light parameters.
/******************************************************************************/

      /* Luma Filter Normal Light */
      {
         /* Thresholds */
         {224, 240, 2256}, /* 12-bit pixels */
         /* Scale Factors */
         {0.547970f, 0.000000f},

         /* Positive table */
         {
            1.000000f, 1.000000f, 1.000000f, 1.000000f,
            0.958183f, 0.874549f, 0.790915f, 0.682843f,
            0.550333f, 0.417823f, 0.309999f, 0.226860f,
            0.143722f, 0.082077f, 0.041926f, 0.021850f
         },
         /* Negative table */
         {
            -0.366296f, -0.743745f, -1.000000f, -0.838795f,
            -0.488576f, -0.265261f, -0.323751f, -0.099250f
         },
      },

/******************************************************************************/
// Feature name : Luma filter bright light parameters.
/******************************************************************************/

      /* Luma Filter Bright Light */
      {
         /* Thresholds */
         {128, 144, 2256}, /* 12-bit pixels */
         /* Scale Factors */
         {0.127364f, 0.000000f},

         /* Positive table */
         {
            1.000000f, 1.000000f, 1.000000f, 1.000000f,
            1.000000f, 1.000000f, 0.889278f, 0.889278f,
            0.667833f, 0.667833f, 0.446389f, 0.446389f,
            0.269484f, 0.269484f, 0.137119f, 0.070936f
         },
         /* Negative table */
         {
            -0.289412f, -1.000000f, -0.936796f, -0.385966f,
            -0.376675f, -0.285460f, -0.072711f, -0.049934f
         },
      },
   },
   /* Color Correction */
   {

/*********************************************************************/
// Feature name :
// Use gain or lux_index to control color correction.
// Range: 0 or 1.
// 0 means to use lux_index to control
// 1 means to use gain to control
/*********************************************************************/

      0, /* Control Method - 1 = Gain, 0 = Lux Index */

/*********************************************************************/
// Feature name :
// Trigger point for color correction.
// gain start :
// When gain >= gain_start, lowlight CC is interpolated with normal CC.
// default: N/A
// Range: min_gain to max_gain. Gain means digital and analog combined gain.
// Effect: Increasing this value will use lowlight CC under lower light condition.
//
// gain end:
// When gain >= gain_end, 100% lowlight CC is used.
// default: N/A
// range: min_gain to max_gain. Gain means digital and analog combined gain.
// constraint: gain_end > gain_start.
// effect: Increasing this value will use 100% lowlight CC under lower light condition.
//
// lux_index_start:
// When lux_index >= lux_index_start, lowlight CC is interpolated with normal CC.
// default: N/A
// range: For linear AFR case: 0 to max_index from exposure table.
//          For non-linear AFR case : 0 to max_index*numberof_FPS_supported.
// effect: Increasing this value will use lowlight CC under lower light condition
//
// lux_index_end:
// When lux_index >= lux_index_end, 100% lowlight CC is used.
// default: N/A
// range: Ror linear AFR case: 0 to max_index from exposure table.
//          For non-linear AFR case : 0 to max_index*numberof_FPS_supported.
// constraint: lux_index_end > lux_index_start.
// effect: Increasing this value will use 100% lowlight CC under lower light condition.
//
/*********************************************************************/

      /* Trigger Points */
      {
         7.200000f, /* Gain Start */
         8.000000f, /* Gain End */
         338, /* Lux Index Start */
         376, /* Lux Index End */
      },
      /* A CCT Trigger */
      {

/*********************************************************************/
// Feature name :
// Trigger point for color temperature related control (A).
// Applicable chipset: For all chipsets.
// 3A version: 2.2
// When the color temperature < A_start and > A_end, use interpolation between A and FL.
// When the color temperature >=A_end, just use A parameters.
// Range: 4100 > A_start > A_end > 2850.
// Effect: A_start and A_end controls the range of interpolation between A and FL.
// Constraint: A_start > A_end.
/*********************************************************************/

         3300, /* Start */
         3200, /* End */
      },
      /* D65 CCT Trigger */
      {

/*********************************************************************/
// Feature name :
// Trigger point for color temperature related control (Daylight).
// Applicable chipset: For all chipsets.
// 3A version: 2.2
// When the color temperature > Daylight_start and < Daylight_end, use interpolation between D65 and FL.
// When the color temperature >=D65_end, just use D65 parameters.
// Range: 4100 < Dayligh_start < Dayligh_end < 5000.
// Effect: Daylight_start and Daylight_end controls the range of interpolation between Daylight and FL.
// Constraint: Daylight_start < Daylight_end.
/*********************************************************************/

         4800, /* Start */
         4900, /* End */
      },

/******************************************************************************/
// Feature name: Color Correction Trigger Point for LED Flash
// Applicale chipset(s): ALL with LED Flash
// Applicable operation mode:  Flash Snapshot and ZSL, determined in preview
//
// Variable name: CC_LED_start
// Sets start trigger for interpolation of CC
//     k1 = aec_d->flash_si.off / aec_d->flash_si.high;
// Default value:  1.0
// Data range: 1.0 to 100
// Constraints: None
// Effect: Higher value allows less LED CC to be used
//
// Variable name: CC_LED_end
// Sets end trigger for interpolation of CC
//     k1 = aec_d->flash_si.off / aec_d->flash_si.high;
// Default value:  7.5
// Data range: 1.0 to 100
// Constraints: None
// Effect: Higher value allows less LED CC to be used, value closer to
//     CC_LED_start may cause shot to shot variation due to sudden change in CC
/******************************************************************************/

      1.000000f, /* LED Start */
      7.500000f, /* LED End */

/******************************************************************************/
// Feature name: Color Correction Trigger Point for Xenon Strobe Flash
// Applicale chipset(s): ALL with Strobe Flash
// Applicable operation mode:  Flash Snapshot and ZSL, determined in preview
//
// Variable name: CC_strobe_start
// Sets start trigger for interpolation of CC
//     k1 = aec_d->flash_si.off / aec_d->flash_si.high;
// Default value:  1.0
// Data range: 1.0 to 100
// Constraints: None
// Effect: Higher value allows less Xenon Strobe CC to be used
//
// variable name: CC_strobe_end
// Sets end trigger for interpolation of CC
//     k1 = aec_d->flash_si.off / aec_d->flash_si.high;
// Default value:  7.5
// Data range: 1.0 to 100
// Constraints: None
// Effect: Higher value allows less Xenon Flash CC to be used, value closer to
//     CC_strobe_start may cause shot to shot variation due to sudden change in CC
/******************************************************************************/

      1.000000f, /* Strobe Start */
      7.500000f, /* Strobe End */

/*********************************************************************/
// Feature name :
// Normal and bright light color correction.
// 3x3 coefficients:
// Data range: -15.99 to 15.99.
// Constraint: The sum of each row needs to be 1.
// Effect: Higher diagonal values result in higher color saturation with higher noise.
//
// 3 offsets
// Data range: -1023 to 1023.
// Default : 0
// Effect: Negative values will make image darker while positive values make image brighter.
//
// Q factor:
// Always set it to 0.
/*********************************************************************/

      /* TL84 Color Correction */
      /* Noise Weight: 0.000000 */
      /* Saturation: Red - 1.000000, Green - 1.000000, Blue - 1.000000 */
      {
         1.7220f,    -0.4305f,    -0.2916f,
         -0.3038f,    1.4894f,    -0.1856f,
         -0.0297f,    -0.8730f,    1.9028f,
         0,    0,    0,
         0
      },

/*********************************************************************/
// Feature name :
// Low light color correction.
/*********************************************************************/

      /* Low-Light Color Correction */
      /* Noise Weight: 0.000000 */
      /* Saturation: Red - 1.000000, Green - 1.000000, Blue - 1.000000 */
      {
         1.7060f,    -0.5778f,    -0.1282f,
         -0.1742f,    1.2966f,    -0.1224f,
         0.0272f,    -0.8082f,    1.7810f,
         0,    0,    0,
         0
      },
      /* D65 Color Correction */
      /* Noise Weight: 0.000000 */
      /* Saturation: Red - 1.000000, Green - 1.000000, Blue - 1.000000 */
      {
         1.7777f,    -0.8086f,    0.0309f,
         -0.2662f,    1.5984f,    -0.3322f,
         -0.0042f,    -0.6016f,    1.6057f,
         0,    0,    0,
         0
      },
      /* A Color Correction */
      /* Noise Weight: 0.000000 */
      /* Saturation: Red - 1.000000, Green - 1.000000, Blue - 1.000000 */
      {
         1.9643f,    -0.1222f,    -0.8422f,
         -0.3003f,    1.3868f,    -0.0865f,
         -0.2403f,    -0.8689f,    2.1092f,
         0,    0,    0,
         0
      },
      /* Outdoor Color Correction */
      {
         1.0000f,    0.0000f,    0.0000f,
         0.0000f,    1.0000f,    0.0000f,
         0.0000f,    0.0000f,    1.0000f,
         0,    0,    0,
         0
      },
      /* LED Flash Color Correction */
      {
         2.0468f,    -0.8254f,    -0.2214f,
         -0.1014f,    1.1093f,    -0.0079f,
         0.1276f,    -0.9069f,    1.7793f,
         0,    0,    0,
         0
      },
      /* Strobe Flash Color Correction */
      {
         2.0468f,    -0.8254f,    -0.2214f,
         -0.1014f,    1.1093f,    -0.0079f,
         0.1276f,    -0.9069f,    1.7793f,
         0,    0,    0,
         0
      },
   },
   /* Gamma Tables */
   {

/*********************************************************************/
// Feature name :
// Control for lowlight gamma.
// 0 means using lux index to control.
// 1 means using gain to control.
/*********************************************************************/

      0, /* Control Method - 1 = Gain, 0 = Lux Index */

/*********************************************************************/
// Feature name :
// Trigger point for lowlight gamma.
// gain start:
// When gain >= gain_start, lowlight gamma is interpolated with normal gamma.
// Range: min_gain to max_gain. Gain means digital and analog combined gain.
// Effect: Increasing this value will use lowlight gamma under lower light condition.
//
// gain end:
// When gain >= gain_end, 100% lowlight gamma is used.
// Range: min_gain to max_gain. Gain means digital and analog combined gain.
// Constraint: gain_end > gain_start.
// Effect: Increasing this value will use 100% lowlight gamma under lower light condition.
//
// lux_index_start:
// When lux_index >= lux_index_start, lowlight gamma is interpolated with normal gamma.
// Range: For linear AFR case: 0 to max_index from exposure table.
//          For non-linear AFR case : 0 to max_index*numberof_FPS_supported.
// Effect: Increasing this value will use lowlight gamma under lower light condition.
//
// lux_index_end:
// When lux_index >= lux_index_end, 100% lowlight gamma is used.
// Range: For linear AFR case: 0 to max_index from exposure table.
//          For non-linear AFR case : 0 to max_index*numberof_FPS_supported.
// Constraint: lux_index_end > lux_index_start.
// Effect: Increasing this value will use 100% lowlight gamma under lower light condition.
//
/*********************************************************************/

      /* Low-Light Trigger Points */
      {
         7.200000f, /* Gain Start */
         8.000000f, /* Gain End */
         338, /* Lux Index Start */
         376, /* Lux Index End */
      },

/*********************************************************************/
// Feature name :
// Trigger point for brightlight gamma.
// gain start :
// When gain <= gain_start, brightlight gamma is interpolated with normal gamma.
// Range: min_gain to max_gain. Gain means digital and analog combined gain.
// Effect: Decreasing this value will use brightlight gamma under brighter light condition.
//
// gain end:
// When gain <= gain_end, 100% brightlight gamma is used.
// Range: min_gain to max_gain. Gain means digital and analog combined gain.
// Constraint: gain_end < gain_start.
// Effect: Decreasing this value will use 100% brightlight gamma under brighter light condition.
//
// lux_index_start:
// When lux_index <= lux_index_start, brightlight gamma is interpolated with normal gamma.
// Range: For linear AFR case: 0 to max_index from exposure table.
//          For non-linear AFR case : 0 to max_index*numberof_FPS_supported.
// Effect: Decreasing this value will use brightlight gamma under brighter light condition.
//
// lux_index_end:
// When lux_index <= lux_index_end, 100% lowlight gamma is used.
// Range: For linear AFR case: 0 to max_index from exposure table.
//          For non-linear AFR case : 0 to max_index*numberof_FPS_supported.
// Constraint: lux_index_end < lux_index_start.
// Effect: Decreasing this value will use 100% brightlight gamma under brighter light condition.
//
/*********************************************************************/

      /* Outdoor Trigger Points */
      {
         4.800000f, /* Gain Start */
         2.400000f, /* Gain End */
         150, /* Lux Index Start */
         112, /* Lux Index End */
      },

/*********************************************************************/
// Feature name :
// Normal light gamma.
// Range: 0 to 255.
//
// linear flag:
// This is a HW flag. Always set this flag to 0.
/*********************************************************************/

      /* Gamma Table */
      /* Gamma Option: Medium, Weight: 0 */
      {
         {
            0, 5, 14, 25, 37, 48, 58, 69, 78, 87, 96, 103, 110, 117, 123, 129,
            134, 139, 144, 148, 153, 156, 160, 164, 167, 170, 173, 176, 179, 182, 184, 187,
            189, 192, 195, 197, 200, 202, 205, 207, 209, 212, 214, 216, 219, 221, 223, 225,
            227, 229, 231, 233, 235, 236, 238, 240, 242, 243, 245, 247, 248, 250, 252, 253
         },
      },

/*********************************************************************/
//Feature name :
// Lowlight light gamma.
// Range: 0 to 255.
//
// linear flag:
// This is a HW flag. Always set this flag to 0.
/*********************************************************************/

      /* Low-Light Gamma Table */
      /* Gamma Option: Medium, Weight: 0 */
      {
         {
            0, 11, 21, 31, 41, 49, 58, 66, 74, 81, 88, 95, 101, 107, 113, 119,
            124, 129, 134, 139, 144, 148, 153, 157, 161, 165, 168, 172, 176, 179, 182, 186,
            189, 192, 195, 197, 200, 203, 206, 208, 211, 213, 215, 218, 220, 222, 224, 226,
            228, 230, 232, 234, 236, 238, 239, 241, 243, 244, 246, 248, 249, 251, 252, 254
         },
      },

/*********************************************************************/
// Feature name :
// Bright light gamma for.
// Range: 0 to 255.
//
// linear flag:
// This is a HW flag.Always set this flag to 0.
/*********************************************************************/

      /* Outdoor Gamma Table */
      /* Gamma Option: Medium, Weight: 0 */
      {
         {
            2, 13, 26, 39, 51, 62, 71, 80, 87, 95, 101, 108, 114, 119, 125, 130,
            135, 140, 145, 149, 153, 157, 161, 165, 168, 171, 175, 178, 181, 184, 187, 189,
            192, 195, 197, 200, 203, 205, 207, 210, 212, 214, 216, 218, 220, 222, 224, 226,
            228, 230, 232, 233, 235, 237, 239, 241, 242, 244, 245, 247, 249, 250, 252, 253
         },
      },
   },
   /* Color Conversion */
   {

/*********************************************************************/
// Feature name :
// use gain or lux_index to control color conversion
// range: 0 or 1.
// 0 means to use lux_index to control
// 1 means to use gain to control
/*********************************************************************/

      0, /* Control Method - 1 = Gain, 0 = Lux Index */

/**************************************************************************************/
// Feature name :
// Trigger point for snapshot and viewfinder color conversion (advanced chroma enhancement).
// gain start :
// When gain >= gain_start, lowlight CV is interpolated with normal CV.
// Range: min_gain to max_gain. Gain means digital and analog combined gain.
// Effect: Increasing this value will use lowlight CV under lower light condition.
//
// gain end:
// When gain >= gain_end, 100% lowlight CV is used.
// Range: min_gain to max_gain. Gain means digital and analog combined gain.
// Constraint: gain_end > gain_start.
// Effect: Increasing this value will use 100% lowlight CV under lower light condition.
//
// lux_index_start:
// When lux_index >= lux_index_start, lowlight CV is interpolated with normal CV.
// Range: For linear AFR case: 0 to max_index from exposure table.
//          For non-linear AFR case : 0 to max_index*numberof_FPS_supported.
// Effect: Increasing this value will use lowlight CV under lower light condition.
//
// lux_index_end:
// When lux_index >= lux_index_end, 100% lowlight CV is used.
// Range: For linear AFR case: 0 to max_index from exposure table.
//          For non-linear AFR case : 0 to max_index*numberof_FPS_supported.
// Constraint: lux_index_end > lux_index_start.
// Effect: Increasing this value will use 100% lowlight CV under lower light condition
//
/**************************************************************************************/

      /* Low-Light Trigger Points */
      {
         7.200000f, /* Gain Start */
         8.000000f, /* Gain End */
         338, /* Lux Index Start */
         376, /* Lux Index End */
      },
      /* A CCT Trigger */
      {
         3300, /* Start */
         3200, /* End */
      },
      /* D65 CCT Trigger */
      {
         4800, /* Start */
         4900, /* End */
      },

/*********************************************************************/
// Feature name :
// Normal light advanced chroma enhancement for snapshot and viewfinder for 7k and 8k.
//
// am, ap,: Color saturation on Cb
// Data range: -3.99 to 3.99. 0.5 is unity.
// Effect: Higher values result in higher color saturation in Cb with higher noise.
//
// cm, cp,: Color saturation on Cr
// Data range: -3.99 to 3.99. 0.5 is unity.
// Effect: Higher values result in higher color saturation in Cr with higher noise.
//
// bm, bp: Certain offset coeffs for Cb calculation.
// Data range: -1023 to 1023.
//
// dm, dp: Certain offset coeffs for Cr calculation.
// Data range: -1023 to 1023.
//
// k_cb, k_cr: Offsets for Cb,Cr, respectively.
// Data range: -1023 to 1023.
// Default: 128.
//
// v0, v1, v2:
// Coefficients from RGB to Y conversion.
// Range: -7.99 to 7.99.
// Constraint: Sum of them needs to be 1.
//
// K offset: Offset to convert from RGB to Y.
// Range: 0 to 255.
// Default : 0.
// Effect: Positive values make image brighter and negative values make image darker.
/*********************************************************************/

      /* TL84 Color Conversion */
      /* Noise Weight: 0.000000 */
      /* Saturation: Red - 1.000000, Green - 1.000000, Blue - 1.000000 */
      {
         {
            /* a_m, a_p */
            0.5873f, 0.5873f,
            /* b_m, b_p */
            -0.3007f, -0.3007f,
            /* c_m, c_p */
            0.5678f, 0.5678f,
            /* d_m, d_p */
            -0.1485f, -0.1485f,
            /* k_cb, k_cr */
            128, 128
         },
         {
            /* v0, v1, v2 */
            0.2990f, 0.5870f, 0.1140f,
            /* k */
            0
         }
      },
      /* A Color Conversion */
      /* Noise Weight: 0.000000 */
      /* Saturation: Red - 1.000000, Green - 1.000000, Blue - 1.000000 */
      {
         {
            /* a_m, a_p */
            0.5890f, 0.5890f,
            /* b_m, b_p */
            -0.2806f, -0.2806f,
            /* c_m, c_p */
            0.5519f, 0.5519f,
            /* d_m, d_p */
            -0.1600f, -0.1600f,
            /* k_cb, k_cr */
            128, 128
         },
         {
            /* v0, v1, v2 */
            0.2990f, 0.5870f, 0.1140f,
            /* k */
            0
         }
      },
      /* D65 Color Conversion */
      /* Noise Weight: 0.000000 */
      /* Saturation: Red - 1.000000, Green - 1.000000, Blue - 1.000000 */
      {
         {
            /* a_m, a_p */
            0.5944f, 0.5944f,
            /* b_m, b_p */
            -0.3135f, -0.3135f,
            /* c_m, c_p */
            0.5532f, 0.5532f,
            /* d_m, d_p */
            -0.1915f, -0.1915f,
            /* k_cb, k_cr */
            128, 128
         },
         {
            /* v0, v1, v2 */
            0.2990f, 0.5870f, 0.1140f,
            /* k */
            0
         }
      },
      /* Yhi-Ylo Color Conversion */
      {
         {
            /* a_m, a_p */
            0.5000f, 0.5000f,
            /* b_m, b_p */
            -0.3380f, -0.3380f,
            /* c_m, c_p */
            0.5000f, 0.5000f,
            /* d_m, d_p */
            -0.1620f, -0.1620f,
            /* k_cb, k_cr */
            128, 128
         },
         {
            /* v0, v1, v2 */
            0.2990f, 0.5870f, 0.1140f,
            /* k */
            0
         }
      },
      /* Outdoor Color Conversion */
      {
         {
            /* a_m, a_p */
            0.5000f, 0.5000f,
            /* b_m, b_p */
            -0.3380f, -0.3380f,
            /* c_m, c_p */
            0.5000f, 0.5000f,
            /* d_m, d_p */
            -0.1620f, -0.1620f,
            /* k_cb, k_cr */
            128, 128
         },
         {
            /* v0, v1, v2 */
            0.2990f, 0.5870f, 0.1140f,
            /* k */
            0
         }
      },
      /* Monochrome Color Conversion */
      {
         {
            /* a_m, a_p */
            0.0000f, 0.0000f,
            /* b_m, b_p */
            0.0000f, 0.0000f,
            /* c_m, c_p */
            0.0000f, 0.0000f,
            /* d_m, d_p */
            0.0000f, 0.0000f,
            /* k_cb, k_cr */
            128, 128
         },
         {
            /* v0, v1, v2 */
            0.2990f, 0.5870f, 0.1140f,
            /* k */
            0
         }
      },
      /* Sepia Color Conversion */
      {
         {
            /* a_m, a_p */
            0.0000f, 0.0000f,
            /* b_m, b_p */
            0.0000f, 0.0000f,
            /* c_m, c_p */
            0.0000f, 0.0000f,
            /* d_m, d_p */
            0.0000f, 0.0000f,
            /* k_cb, k_cr */
            110, 140
         },
         {
            /* v0, v1, v2 */
            0.2990f, 0.5870f, 0.1140f,
            /* k */
            0
         }
      },
      /* Negative Color Conversion */
      {
         {
            /* a_m, a_p */
            -0.5000f, -0.5000f,
            /* b_m, b_p */
            -0.3380f, -0.3380f,
            /* c_m, c_p */
            -0.5000f, -0.5000f,
            /* d_m, d_p */
            -0.1620f, -0.1620f,
            /* k_cb, k_cr */
            128, 128
         },
         {
            /* v0, v1, v2 */
            -0.2990f, -0.5870f, -0.1140f,
            /* k */
            255
         }
      },
      /* Aqua Color Conversion */
      {
         {
            /* a_m, a_p */
            0.0000f, 0.0000f,
            /* b_m, b_p */
            0.0000f, 0.0000f,
            /* c_m, c_p */
            0.0000f, 0.0000f,
            /* d_m, d_p */
            0.0000f, 0.0000f,
            /* k_cb, k_cr */
            160, 80
         },
         {
            /* v0, v1, v2 */
            0.2990f, 0.5870f, 0.1140f,
            /* k */
            0
         }
      },
      1.100000f, /* Saturated Color Conversion Factor */
   },
   /* 5x5 ASF */
   {

/*********************************************************************/
// Feature name :
// Use gain or lux_index to control ASF
// Range: 0 or 1.
// 0 means to use lux_index to control.
// 1 means to use gain to control.
/*********************************************************************/

      1, /* Control Method - 1 = Gain, 0 = Lux Index */

/*********************************************************************/
// Feature name :
// Trigger point for 5x5ASF.
// This set of parameters is used for all chipsets.
// gain start :
// When gain >= gain_start, lowlight ASF is interpolated with normal ASF.
// Range: min_gain to max_gain. Gain means digital and analog combined gain.
// Effect: Increasing this value will use lowlight ASF under lower light condition.
//
// gain end:
// When gain >= gain_end, 100% lowlight ASF is used.
// Range: min_gain to max_gain. Gain means digital and analog combined gain.
// Constraint: gain_end > gain_start.
// Effect: Increasing this value will use 100% lowlight ASF under lower light condition.
//
// lux_index_start:
// When lux_index >= lux_index_start, lowlight ASF is interpolated with normal ASF.
// Range: For linear AFR case: 0 to max_index from exposure table.
//          For non-linear AFR case : 0 to max_index*numberof_FPS_supported.
// Effect: Increasing this value will use lowlight ASF under lower light condition.
//
// lux_index_end:
// When lux_index >= lux_index_end, 100% lowlight ASF is used.
// Range: For linear AFR case: 0 to max_index from exposure table.
//          For non-linear AFR case : 0 to max_index*numberof_FPS_supported.
// Constraint: lux_index_end > lux_index_start.
// Effect: Increasing this value will use 100% lowlight ASF under lower light condition.
//
/*********************************************************************/

      /* Low-Light Trigger Points */
      {
         7.200000f, /* Gain Start */
         7.840000f, /* Gain End */
         338, /* Lux Index Start */
         368, /* Lux Index End */
      },

/*********************************************************************/
// Feature name :
// Trigger point for brightlight 5x5 ASF.
// This set of parameters is used for all chipsets.
// gain start :
// When gain <= gain_start, brightlight ASF is interpolated with normal ASF.
// Range: min_gain to max_gain. Gain means digital and analog combined gain.
// Effect: Decreasing this value will use brightlight ASF under brighter light condition.
//
// gain end:
// When gain <= gain_end, 100% brightlight ASF is used.
// Range: min_gain to max_gain. Gain means digital and analog combined gain.
// Constraint: gain_end < gain_start.
// Effect: Decreasing this value will use 100% brightlight ASF under brighter light condition.
//
// lux_index_start:
// When lux_index <= lux_index_start, brightlight ASF is interpolated with normal ASF.
// Range: For linear AFR case: 0 to max_index from exposure table.
//          For non-linear AFR case : 0 to max_index*numberof_FPS_supported.
// Effect: Decreasing this value will use brightlight ASF under brighter light condition.
//
// lux_index_end:
// When lux_index <= lux_index_end, 100% lowlight ASF is used.
// Range: For linear AFR case: 0 to max_index from exposure table.
//          For non-linear AFR case : 0 to max_index*numberof_FPS_supported.
// Constraint: lux_index_end < lux_index_start.
// Effect: Decreasing this value will use 100% brightlight ASF under brighter light condition.
//
/*********************************************************************/

      /* Outdoor Trigger Points */
      {
         2.000000f, /* Gain Start */
         1.000000f, /* Gain End */
         188, /* Lux Index Start */
         169, /* Lux Index End */
      },

/*********************************************************************/
// Feature name :
// 5x5 ASF filter mode.
// This set of parameters is used for all chipsets with some exceptions, please see each item for details.
// 0 means ASF is off.
// 1 means single 5x5 ASF filter.
// 2 means two 5x5 ASF filters.
// 3 means smart mode. Currently software does not support this mode.
// Default: 2
//
//Please do not change smoothing filter and Laplacian filter.
//
// Normalization factors for horizontal and veritical directions.
// mode.
// Constraint: It has to be the inverse value of the center cofficient in
//                sharpening filter for horizontal and vertical directions,
//                respectively.
//
// Sharpening coeff. for horizontal and vertical directions, respectively.
// These parameters are used for all chipsets.
// Range: Middle coeff -63.9 to 63, surounding ceoff -127 to 127.
// Constraints: All coffs need to sum to 0.
//
// Extraction factor is not supported by software.
//
// 5x5 ASF parameters under lowlight, normal, and bright light.
//
// e1
// Noise threshold.
// It is for all chipsets.
// Range: 0 to 127.
// Effect: Smaller value will result in more edges to be sharpened.
//
// e2
// Sharpening Limit
// Range: 0 to 127.
// Constraint: e2>=e1.
// Effect: Larger values will result in sharper strong edges.
// For MSM7601, MSM7201, MSM7501, e2 affects horizontal and vertical edges.
// For QSD8x50, QSC6270(6240), QSC6295, e2 only affects horizontal positive edges.
//
// e3
// Sharpening limit for horizontal negative edge.
// e3 is only supported on QSD8x50, QSC6270(6240), QSC6295, MSM7x25, MSM7x27.
// Default: -e2
// Range: -128 to 0.
// Constraints: |e3| >= e1.
// Effect: Smaller values will result in sharper negative strong edges.
//
// e4
// Sharpening limit for vertical positive edge.
// e4 is only supported on QSD8x50, QSC6270(6240), QSC6295, MSM7x25, MSM7x27.
// Default: e2.
// Range: 0 to 127
// Constraints: e4 >= e1.
// Effect: Larger values will result in sharper positive strong edges.
//
// e5
// Sharpening limit for vertical negative edge.
// e5 is only supported on QSD8x50, QSC6270(6240), QSC6295, MSM7x25, MSM7x27.
// Default: -e4.
// Range: -128 to 0.
// Constraints: |e5| >= e1.
// Effect: Smaller values will result in sharper negative strong edges.
//
// k1 and k2
// Sharpening degree for horizontal and vertical edges.
// These are supported in all chipsets.
// Range: 0 to 3.9. (except for sROC; on sROC max value is 1.9.)
// Effect: Larger value result in sharper edges.
//
// sp
// Smoothing percentage.
// It is for all chipsets.
// Range: 0 to 100.
// Effect: Larger value results in smoother images.
//
/*********************************************************************/

      /* 5x5 ASF */
      {
         2, /* Filter Mode */
         0.250000f, /* Normalize Factor 1 */
         0.250000f, /* Normalize Factor 2 */
         /* 5x5 Filter 1 */
         {
            0, -1, -2, -1, 0,
            0, 0, 0, 0, 0,
            0, 2, 4, 2, 0,
            0, 0, 0, 0, 0,
            0, -1, -2, -1, 0
         },
         /* 5x5 Filter 2 */
         {
            0, 0, 0, 0, 0,
            -1, 0, 2, 0, -1,
            -2, 0, 4, 0, -2,
            -1, 0, 2, 0, -1,
            0, 0, 0, 0, 0
         },
         80, /* Extraction Factor */
         /* Settings */
         {
            /* Low Light */
            {
               30, /* e1 */
               60, /* e2 */
               -60, /* e3 */
               60, /* e4 */
               -60, /* e5 */
               0.000000f, /* k1 */
               0.000000f, /* k2 */
               100, /* sp */
               50, /* sp 5x5 */
            },
            /* Normal Light */
            {
               10, /* e1 */
               32, /* e2 */
               -32, /* e3 */
               32, /* e4 */
               -32, /* e5 */
               0.750000f, /* k1 */
               0.750000f, /* k2 */
               30, /* sp */
               0, /* sp 5x5 */
            },
            /* Bright Light */
            {
               5, /* e1 */
               28, /* e2 */
               -28, /* e3 */
               28, /* e4 */
               -28, /* e5 */
               0.800000f, /* k1 */
               0.800000f, /* k2 */
               0, /* sp */
               0, /* sp 5x5 */
            }
         }
      },

/*********************************************************************/
// Feature name :
// Soft focus degree.
// This parameter is used for portrait mode under Best Shot Mode.
// Range: 0.5 to 1.
// Effect: Smaller value will result in softer focus.
/*********************************************************************/

      0.900000f, /* Soft Focus Degree */

/*********************************************************************/
// Feature name :
// Sharpness control parameters per upscaling for 5x5 ASF.
// This parameter is used for all chipsets.
// Range: 0.25 to 1.
// Effect: Larger value will result in little sharpening change for upscaling.
//           Setting it to 1 will use the same sharpening for upscaling case as
//           no scaling.
//
/*********************************************************************/

      0.250000f, /* 5x5 Sharp Min DS Factor */

/*********************************************************************/
// Feature name :
// Sharpness control parameters per downscaling for 5x5 ASF.
// This parameter is used for all chipsets.
// We do not recommend changing this value.
/*********************************************************************/

      12.000000f, /* 5x5 Sharp Max DS Factor */

/*********************************************************************/
// Feature name :
// Sharpness control parameters per downscaling for 5x5 ASF.
// This parameter is used for all chipsets.
// Range: 1 to 3.
// Effect: Larger value will result in more sharpening for downscaling case.
// Default value (target-specific): 1 for QSC6xxx, QSD8xxx and MSM7201, MSM7601, MSM7501, MSM7x30, 2 for MSM7x25, MSM7x27.
/*********************************************************************/

      1.000000f, /* 5x5 Sharp Max Factor */
   },
   /* 7x7 ASF */
   {
      1, /* Control Method - 1 = Gain, 0 = Lux Index */
      /* Low-Light Trigger Points */
      {
         7.200000f, /* Gain Start */
         7.840000f, /* Gain End */
         338, /* Lux Index Start */
         368, /* Lux Index End */
      },
      /* Bright Light Trigger Points */
      {
         2.000000f, /* Gain Start */
         1.000000f, /* Gain End */
         188, /* Lux Index Start */
         169, /* Lux Index End */
      },

/*********************************************************************/
// VFE4 7x7 ASF filter
//
// 7x7 ASF parameters under lowlight, normal, and bright
// light.
//
// Variable name: SP.
// 3x3 cross type median filter smoothing percentage.
// Data range: 0 to 100.
// Effect: Larger value results in smoother images.
//
// 7x7 edge detection (F1: horizontal & F2: vertical), sharpening
// (F3: horizontal & F4: vertical), and smoothing (F5) coefficients.
// Altered kernel symmatry by (negation & zero)'s according to zones:
// (nz flags are defaulted to 0s, i.e., no change.)
// nz[0]          |nz[1]|          nz[2]
//        0  1  2 |   3 |  2  1  0
//        4  5  6 |   7 |  6  5  4
//        8  9 10 |  11 | 10  9  8
// ---------------+-----+---------------
// nz[7] 12 13 14 |  15 | 14 13 12 nz[3]
// ---------------+-----+---------------
//        8  9 10 |  11 | 10  9  8
//        4  5  6 |   7 |  6  5  4
//        0  1  2 |   3 |  2  1  0
// nz[6]          |nz[5]|          nz[4]
// Data range: Center coeff -2047 to 2047, axes coeff -1023 to 1023,
//        quadrant ceoff -511 to 511.  All are Q10 numbers.
// Constraints: After mirroring, all 49 coefficients in the high-pass
//        filters must sum up to 0, and all 49 coefficients in F5 must
//        sum up to 1.0.
//
//        For MSM8974 (VFE4.0), F1 to F5 must have the same coefficient
//        symmetry, i.e., F1 to F4 should be 2nd order HPFs and F5 be
//        LPF.  For VFE4.1 and after, F1 and F2 can have independent
//        symmetries, i.e., 1st order HPFs.
//
// Variable name: LUT1
// Horizontal edge endhancement strength with noise threshold.
// Data range: 24-entry LUT mapping from absolute edge detection [0, 95] of
//        F1 to edge enhancement strength [0, 7.96] for F3.
// Effect: This mapping curve is optimized with the 7x7 edge sharpening
//        filter.  Small edges due to noise can be thresholded by curve
//        being 0.
//
// Variable name: LUT2
// Vertical edge endhancement strength with noise threshold.
// Data range: 24-entry LUT mapping from absolute edge detection [0, 95] of
//        F2 to edge enhancement strength [0, 7.96] for F4.
// Effect: This mapping curve is optimized with the 7x7 edge sharpening
//        filter.  Small edges due to noise can be thresholded by curve
//        being 0.
//
// Variable name: LUT3
// HPF weighting curve.
// Data range: 12-entry LUT mapping from absolute edge detection [0, 47] of
//        F1+F2 to unsharp HPF output wighting [0, 1.0] of F3+F4.
// Effect: This mapping curve is optimized with the 7x7 edge sharpening
//        filter.  HPF image is blended with LPF image by convex
//        combination, where the output of LPF F5 is weighted as
//        (1.0 - HPF weighting).
//
// Variable names: Smax, Smin
// Ratio to the maximum and minimum in neighborhood for dynamic
// high-end and low-end clamping of edge enhancement.
// Data range: 0 to 7.9.
// Effect: Smax applies to the difference of the maximum in 3x3 diamond
//        neighborhood of the input pixel to the center pixel after 3x3
//        cross-type median filter for high-end clamping level, and
//        Smin similarly applies to the difference of the minimum in
//        neighborhood for low-end clamping level.  Increasing Smax and
//        Smin allow wider swing of edge enhancement proportionally,
//        and vice versa for narrower edge enhancement range.  Dynamic
//        clamping helps reducing edge overshoots to avoid halo
//        artifacts.  The high and low clamping levels apply to
//        horizontal and vertical edge enhancements equally.
//
// Variable names: Omax, Omin
// Offset to the maximum and minimum in neighborhood for dynamic
// high-end and low-end clamping of edge enhancement.
// Data range: 0 to 127.
// Effect: Similar to Smax and Smin, Omax adds offset to the high-end
//        dynamic clamping level and Omin subtracts to the low-end
//        dynamic clamping level.  Increasing Omax and Omin increases
//        the swing range of edge enhancement and vice versa.  The high
//        and low clamping levels apply to horizontal and vertical edge
//        enhancements equally.
//
// Variable names: Clamp_HH, Clamp_HL
// Static high-end and low-end clamping levels of horizontal edge
// enhancement.
// Data range: -255 to 255.
// Effect: If dynamic clamping is disabled, these values are applied to
//        limit the high-end and low-end swing range of edge
//        enhancement of F3 in horizontal direction.
//
// Variable names: Clamp_VH, Clamp_VL
// Static high-end and low-end clamping levels of vertical edge
// enhancement.
// Data range: -255 to 255.
// Effect: If dynamic clamping is disabled, these values are applied to
//        limit the high-end and low-end swing range of edge
//        enhancement of F4 in vertical direction.
//
// Variable names: en_sp_eff, neg_abs_y1, nz[7::0]
// Special effects (emboss, sketch, neon) only.  For normal edge
// enhancement, these should be set to zero.
/*********************************************************************/

      /* 7x7 ASF */
      {
         1, /* Enable */
         /* 3x3 Smooth Percentage */
         {
            0,  /* Lowlight */
            0, /* Normal Light */
            0 /* Bright Light */
         },
         0, /* Enable Special Effects */
         0, /* neg_abs_y1 */
         {0, 0, 0}, /* nz [0] for F1, [1] for F2, [2] for F3 and F4 */
         /* F1 */
         {
            /* Lowlight */
            {
               0.000000f, 0.000000f, 0.000000f, 0.000000f,
               -0.020800f, -0.020800f, 0.020800f, 0.041700f,
               -0.083300f, -0.083300f, 0.083300f, 0.166700f,
               -0.125000f, -0.125000f, 0.125000f, 0.250000f
            },
            /* Normal Light */
            {
               0.000000f, 0.000000f, 0.000000f, 0.000000f,
               -0.015600f, -0.031300f, 0.015600f, 0.062500f,
               -0.062500f, -0.125000f, 0.062500f, 0.250000f,
               -0.093800f, -0.187500f, 0.093800f, 0.375000f
            },
            /* Bright Light */
            {
               0.000000f, 0.000000f, 0.000000f, 0.000000f,
               0.000000f, -0.062500f, 0.000000f, 0.125000f,
               0.000000f, -0.250000f, 0.000000f, 0.500000f,
               0.000000f, -0.375000f, 0.000000f, 0.750000f
            },
         },
         /* F2 */
         {
            /* Lowlight */
            {
               0.000000f, -0.020800f, -0.083300f, -0.125000f,
               0.000000f, -0.020800f, -0.083300f, -0.125000f,
               0.000000f, 0.020800f, 0.083300f, 0.125000f,
               0.000000f, 0.041700f, 0.166700f, 0.250000f
            },
            /* Normal Light */
            {
               0.000000f, -0.015600f, -0.062500f, -0.093800f,
               0.000000f, -0.031300f, -0.125000f, -0.187500f,
               0.000000f, 0.015600f, 0.062500f, 0.093800f,
               0.000000f, 0.062500f, 0.250000f, 0.375000f
            },
            /* Bright Light */
            {
               0.000000f, 0.000000f, 0.000000f, 0.000000f,
               0.000000f, -0.062500f, -0.250000f, -0.375000f,
               0.000000f, 0.000000f, 0.000000f, 0.000000f,
               0.000000f, 0.125000f, 0.500000f, 0.750000f
            },
         },
         /* F3 */
         {
            /* Lowlight */
            {
               -0.001200f, -0.004400f, 0.026200f, -0.035700f,
               0.017000f, -0.062500f, 0.029100f, 0.054100f,
               -0.028700f, -0.102700f, 0.001600f, 0.229800f,
               -0.000300f, -0.145600f, 0.033100f, 0.231700f
            },
            /* Normal Light */
            {
               -0.001200f, -0.004400f, 0.026200f, -0.035700f,
               0.017000f, -0.062500f, 0.029100f, 0.054100f,
               -0.028700f, -0.102700f, 0.001600f, 0.229800f,
               -0.000300f, -0.145600f, 0.033100f, 0.231700f
            },
            /* Bright Light */
            {
               -0.001200f, -0.004400f, 0.026200f, -0.035700f,
               0.017000f, -0.062500f, 0.029100f, 0.054100f,
               -0.028700f, -0.102700f, 0.001600f, 0.229800f,
               -0.000300f, -0.145600f, 0.033100f, 0.231700f
            },
         },
         /* F4 */
         {
            /* Lowlight */
            {
               -0.001200f, 0.017000f, -0.028700f, -0.000300f,
               -0.004400f, -0.062500f, -0.102700f, -0.145600f,
               0.026200f, 0.029100f, 0.001600f, 0.033100f,
               -0.035700f, 0.054100f, 0.229800f, 0.231700f
            },
            /* Normal Light */
            {
               -0.001200f, 0.017000f, -0.028700f, -0.000300f,
               -0.004400f, -0.062500f, -0.102700f, -0.145600f,
               0.026200f, 0.029100f, 0.001600f, 0.033100f,
               -0.035700f, 0.054100f, 0.229800f, 0.231700f
            },
            /* Bright Light */
            {
               -0.001200f, 0.017000f, -0.028700f, -0.000300f,
               -0.004400f, -0.062500f, -0.102700f, -0.145600f,
               0.026200f, 0.029100f, 0.001600f, 0.033100f,
               -0.035700f, 0.054100f, 0.229800f, 0.231700f
            },
         },
         /* F5 */
         {
            0.000000f, 0.000000f, 0.000000f, 0.000000f,
            0.000000f, 0.000000f, 0.000000f, 0.000000f,
            0.000000f, 0.000000f, 0.000000f, 0.000000f,
            0.000000f, 0.000000f, 0.000000f, 1.000000f
         },
         /* H / Lut1 */
         {
            /* Lowlight */
            {
               0.000000f, 0.000000f, 0.008081f, 0.159851f, 0.323415f, 0.387289f,
               0.398902f, 0.399951f, 0.399999f, 0.400000f, 0.400000f, 0.400000f,
               0.400000f, 0.400000f, 0.400000f, 0.400000f, 0.400000f, 0.400000f,
               0.400000f, 0.400000f, 0.400000f, 0.400000f, 0.400000f, 0.400000f
            },
            /* Normal Light */
            {
               0.000000f, 0.000000f, 0.167792f, 0.632121f, 0.915363f, 0.989866f,
               0.999368f, 0.999979f, 1.000000f, 1.000000f, 1.000000f, 1.000000f,
               1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f,
               1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f
            },
            /* Bright Light */
            {
               0.000000f, 0.000000f, 0.167792f, 0.632121f, 0.915363f, 0.989866f,
               0.999368f, 0.999979f, 1.000000f, 1.000000f, 1.000000f, 1.000000f,
               1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f,
               1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f
            },
         },
         /* V / Lut2 */
         {
            /* Lowlight */
            {
               0.000000f, 0.000000f, 0.008081f, 0.159851f, 0.323415f, 0.387289f,
               0.398902f, 0.399951f, 0.399999f, 0.400000f, 0.400000f, 0.400000f,
               0.400000f, 0.400000f, 0.400000f, 0.400000f, 0.400000f, 0.400000f,
               0.400000f, 0.400000f, 0.400000f, 0.400000f, 0.400000f, 0.400000f
            },
            /* Normal Light */
            {
               0.000000f, 0.000000f, 0.167792f, 0.632121f, 0.915363f, 0.989866f,
               0.999368f, 0.999979f, 1.000000f, 1.000000f, 1.000000f, 1.000000f,
               1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f,
               1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f
            },
            /* Bright Light */
            {
               0.000000f, 0.000000f, 0.167792f, 0.632121f, 0.915363f, 0.989866f,
               0.999368f, 0.999979f, 1.000000f, 1.000000f, 1.000000f, 1.000000f,
               1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f,
               1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f
            },
         },
         {0, 0, 0},/* Enable Dynamic Clamping */
         {1.000000, 1.000000, 1.000000},/* smax */
         {6, 6, 6},/* omax */
         {1.000000, 1.000000, 1.000000},/* smin */
         {6, 6, 6}, /* omin */
         {14, 14, 14},/* reg_hh */
         {-14, -14, -14},/* reg_hl */
         {14, 14, 14},/* reg_vh */
         {-14, -14, -14},/* oreg_vlmin */
         /* Lut3 */
         {
            /* Lowlight */
            {
               0.000600f, 0.588900f, 0.971400f, 0.999700f, 1.000000f, 1.000000f,
               1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f
            },
            /* Normal Light */
            {
               0.000600f, 0.588900f, 0.971400f, 0.999700f, 1.000000f, 1.000000f,
               1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f
            },
            /* Bright Light */
            {
               0.000600f, 0.588900f, 0.971400f, 0.999700f, 1.000000f, 1.000000f,
               1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f
            },
         },
      },
      0.900000f, /* 7x7 Soft Focus Degree */
      0.250000f, /* 7x7 Sharp Min DS Factor */
      12.000000f, /* 7x7 Sharp Max DS Factor */
      2.000000f, /* 7x7 Sharp Max Factor */
   },
   /* Luma Adaptation */
   {
      0, /* Luma Adaptation Enable */
      0, /* Control Method - 1 = Gain, 0 = Lux Index */

/******************************************************************************/
// Feature name : Luma Adaptation bright light trigger points
//
/******************************************************************************/

      /* Bright Light Trigger Points */
      {
         4.800000f, /* Gain Start */
         2.400000f, /* Gain End */
         150, /* Lux Index Start */
         112, /* Lux Index End */
      },

/******************************************************************************/
// Feature name: Luma Adaptation (LA) ARM Processing
// applicale chipset(s): QSD8x50, MSM7x30, QSD8x60, MSM8960, MSM8974
// applicable operation mode:
//     QSD8x50: Snapshot processing mode only
//     MSM7x30, QSD8x60, MSM8960, MSM8974: Viewfinder, snapshot, and video
//     modes
//
// variable name: shadow_range.
// Defines the range of low light shadow.
// Default value: 70.
// Data range: 1 to 127.
// Effect: shadow_range defines the low light boost range [0, shadow_range].
//     Shadow pixels on the 0 end are enhanced more than the shadow_range end.
//
// Variable name: shadow_boost_allowance.
// Index for the strength of shadow boost.
// Default value: 0.
// Data range: 0 to 100.
// Constraints:
// Effect: Increasing shadow_boost_allowance will allow stronger shadow boost,
//     and vice versa.  shadow_boost_allowance can be proportional to backlight
//     ratio.
//
// Variable name: LA_reduction_fine_tune.
// Fine tune parameter to reduce overall luma enhancement.
// Default value: 0.
// Data range: 0 to 100.
// Effect: Increasing LA_reduction_fine_tune will decrease overall luma
//     enhancement effects, and vice versa.
//
// Variable name: shadow_boost_fine_tune.
// Fine tune parameter to boost the shadow luminance.
// Default value: 0.
// Data range: 0 to 100.
// Effect: Increasing shadow_boost_fine_tune will make shadow area brighter,
//     and vice versa.
//
// Variable name: highlight_suppress_fine_tune.
// Fine tune parameter to enhance the highlight details.
// Default value: 0.
// Data range: 0 to 100.
// Effect: Increasing highlight_suppress_fine_tune will make highlight regions
//     darker, and vice versa.
/******************************************************************************/

      /* Indoor Luma Adaptation */
      {
         70, /* Shadow Range */
         0, /* Shadow Boost Allowance */
         0, /* Reduction Fine Tune */
         0, /* Highlight Supress Fine Tune */
         0, /* Shadow Boost Fine Tune */
      },
      /* Outdoor Luma Adaptation */
      {
         70, /* Shadow Range */
         0, /* Shadow Boost Allowance */
         0, /* Reduction Fine Tune */
         0, /* Highlight Supress Fine Tune */
         0, /* Shadow Boost Fine Tune */
      },
      -7, /* Luma Target Adjust */
   },
   /* Chroma Suppression/Memory Color Enhancement */
   {

/*********************************************************************/
// Feature name :
// Use gain or lux_index to control chroma suppression (CS).
// Range: 0 or 1.
// 0 means to use lux_index to control.
// 1 means to use gain to control.
/*********************************************************************/

      0, /* Control Method - 1 = Gain, 0 = Lux Index */

/*********************************************************************/
// Feature name :
// Trigger point for chroma suppression (CS)
// gain start:
// When gain >= gain_start, lowlight CS is interpolated with normal CS.
// Range: min_gain to max_gain. Gain means digital and analog combined gain.
// Effect: Increasing this value will use lowlight CS under lower light condition.
//
// gain end:
// When gain >= gain_end, 100% lowlight CS is used.
// Range: min_gain to max_gain. Gain means digital and analog combined gain.
// Constraint: gain_end > gain_start.
// Effect: Increasing this value will use 100% lowlight CS under lower light condition.
//
// lux_index_start:
// When lux_index >= lux_index_start, lowlight CS is interpolated with normal CS.
// Range: For linear AFR case: 0 to max_index from exposure table.
//          For non-linear AFR case : 0 to max_index*numberof_FPS_supported.
// Effect: Increasing this value will use lowlight CS under lower light condition.
//
// lux_index_end:
// When lux_index >= lux_index_end, 100% lowlight CS is used.
// Range: For linear AFR case: 0 to max_index from exposure table.
//          For non-linear AFR case : 0 to max_index*numberof_FPS_supported.
// Constraint: lux_index_end > lux_index_start.
// Effect: Increasing this value will use 100% lowlight CS under lower light condition.
//
/*********************************************************************/

      /* Low-Light Trigger Points */
      {
         7.600000f, /* Gain Start */
         8.000000f, /* Gain End */
         338, /* Lux Index Start */
         376, /* Lux Index End */
      },

/*********************************************************************/
// Feature name :
// CS parameters for lowlight.
//
// Luma Threshold 1 and Luma Threshold 2
// Range: 0 to 255.
// Constraint: For 7x30 and later,
//             4 <= (threshold2 - threshold1) <= 127
//             For earlier chips,
//             (threshold2 - threshold1) > 0 and is a power of 2.
// Effect: Larger (threshold2 - threshold1) tends to result in more dark pixels
//         to be pulled towards grey.
//
// Luma Threshold 3 and Luma Threshold 4
// Range: 0 to 255.
// Constraint: For 7x30 and later,
//             4 <= (threshold4 - threshold3) <= 127
//             For earlier chips,
//             (threshold4 - threshold3) > 0 and is a power of 2.
// Effect: Larger (threshold4 - threshold3) tends to result in more bright pixels
//         to be pulled towards grey.
//
// Chroma Threshold 1 and Chroma Threshold 2
// Range: 0 to 255.
// Constraint: For 7x30 and later,
//             4 <= (threshold2 - threshold1) <= 127
//             For earlier chips,
//             (threshold2 - threshold1) > 0 and is a power of 2.
// Effect: Larger (threshold2 - threshold1) tends to result in more color pixels
//         to be pulled towards grey.
//
/*********************************************************************/

      /* Low-Light Chroma Suppression */
      {
         5, /* Luma Threshold 1 */
         9, /* Luma Threshold 2 */
         176, /* Luma Threshold 3 */
         240, /* Luma Threshold 4 */
         15, /* Chroma Threshold 1 */
         31, /* Chroma Threshold 2 */
      },

/*********************************************************************/
// Feature name : CS parameters.
// CS parameters for normal light.
// Please see details under lowlight.
/*********************************************************************/

      /* Chroma Suppression */
      {
         43, /* Luma Threshold 1 */
         75, /* Luma Threshold 2 */
         250, /* Luma Threshold 3 */
         254, /* Luma Threshold 4 */
         5, /* Chroma Threshold 1 */
         13, /* Chroma Threshold 2 */
      },

/*********************************************************************/
// Feature name : Chroma threshold for strong chroma suppression (CS).
// Variable name: chroma_thresh_BW.
// When max chroma < chroma_thresh_BW, strong CS will be used.
// Default value: 40.
// Data range: 0 to 127.
// Effect: Increasing this value will make image more likely to use strong chroma suppression.
//
// Feature name : Chroma threshold for regualr chroma suppression (CS).
// Variable name: chroma_thresh_color.
// When max chroma > chroma_thresh_color, regualr CS will be used.
// Default value: 60.
// Data range: 0 to 127.
// Effect: Increasing this value will make image less likely to use regular chroma suppression.
/*********************************************************************/

      40, /* Chroma Thresh BW */
      60, /* Chroma Thresh Color */

/******************************************************************************/
// Feature name : MCE (Memory Color Enhancement)
// RGB color gains and their corresponding color boundary & transition zone
// applicale chipset(s): 7X30, 8660, 867x
// applicable operation mode: preivew and snapshot
// effect: larger boost factor --> lager color saturation
//
// variable name: green_y
// Adjustment point in Y
// default value: {20, 40, 200, 235}
// data range: 0-255
// constraints: 0-255
// effect: adjust the boost factor relative to Y
//
// variable name: green_boost_factor
// Max boost factor for green
// default value: 1.0
// data range: 1.0 - 2.0
// constraints: 1.0 - 2.0
// effect: larger vale --> greener
//
// variable name: green_cr_boundary
// Cr boundary for green
// default value: default = -10
// data range: -127 to 127
// constraints: green zone should not overlap with other color zones
// effect: size of the green zone, more negative --> smaller green zone
//
// variable name: green_cb_boundary
// Cb boundary for green
// default value: -12
// data range: -127 to 127
// constraints: green zone should not overlap with other color zones
//              must be same as green_cr_boundary
// effect: size of the green zone, more negative --> smaller green zone
//
// variable name: green_cr_transition_width
// Transition zone width for Cr boundary for green
// default value: 8
// data range: 4 to 31
// constraints: green zone should not overlap with other color zones
// effect: Cr width of the green zone transition, larger-> smoother change
//
// variable name: green_cb_transition_width
// Transition zone width for Cb boundary for green
// default value: 8
// data range: 4 to 31
// constraints: green zone should not overlap with other color zones
// effect: Cb width of the green zone transition, larger-> smoother change
//
// variable name: green_bright_index
// Exposure index for full green boosting effect
// default value (calculated) : AEC outdoor index
// data range: 0 to max exp index
// constraints: < green_dark_index
// effect: adjust the exposure level for full green boosting effect.
//
// variable name: green_dark_index
// Exposure index for no green boosting effect
// default value: default (calculated): (AEC indoor index+AEC outdoor index)/2
// data range: 0 to max exp index
// constraints: > green_bright_index
// effect: adjust the exposure level for no green boosting effect.
//
// variable name: blue_y
// Adjustment point in Y
// default value: {80, 150, 235, 255}
// data range: 0-255
// constraints: 0-255
// effect: adjust the boost factor relative to Y
//
// variable name: blue_boost_factor
// Max boost factor for blue
// default value: 1.0
// data range: 1.0 - 2.0
// constraints: 1.0 - 2.0
// effect: larger vale --> bluer
//
// variable name: blue_cr_boundary
// Cr boundary for blue
// default value: default = -18
// data range: -127 to 127
// constraints: blue zone should not overlap with other color zones
// effect: size of the blue zone, more negative --> smaller blue zone
//
// variable name: blue_cb_boundary
// Cb boundary for blue
// default value: 25
// data range: -127 to 127
// constraints: blue zone should not overlap with other color zones
//              must be same as blue_cr_boundary
// effect: size of the blue zone, more positive --> smaller blue zone
//
// variable name: blue_cr_transition_width
// Transition zone width for Cr boundary for blue
// default value: 10
// data range: 4 to 31
// constraints: blue zone should not overlap with other color zones
// effect: Cr width of the blue zone transition, larger-> smoother change
//
// variable name: blue_cb_transition_width
// Transition zone width for Cb boundary for blue
// default value: 10
// data range: 4 to 31
// constraints: blue zone should not overlap with other color zones
// effect: Cb width of the blue zone transition, larger-> smoother change
//
// variable name: blue_bright_index
// Exposure index for full blue boosting effect
// default value (calculated) : AEC outdoor index
// data range: 0 to max exp index
// constraints: < blue_dark_index
// effect: adjust the exposure level for full blue boosting effect.
//
// variable name: blue_dark_index
// Exposure index for no blue boosting effect
// default value: default (calculated): (AEC indoor index+AEC outdoor index)/2
// data range: 0 to max exp index
// constraints: > blue_bright_index
// effect: adjust the exposure level for no blue boosting effect.
//
// variable name: red_y
// Adjustment point in Y
// default value: {10, 30, 200, 235}
// data range: 0-255
// constraints: 0-255
// effect: adjust the boost factor relative to Y
//
// variable name: red_boost_factor
// Max boost factor for red
// default value: 1.0
// data range: 1.0 - 2.0
// constraints: 1.0 - 2.0
// effect: larger vale --> redder
//
// variable name: red_cr_boundary
// Cr boundary for red
// default value: 45
// data range: -127 to 127
// constraints: red zone should not overlap with other color zones
// effect: size of the red zone, more positive --> smaller red zone.
//
// variable name: red_cb_boundary
// Cb boundary for red
// default value: 127
// data range: -127 to 127
// constraints: red zone should not overlap with other color zones
//              must be same as red_cr_boundary
// effect: size of the red zone, more positive --> larger red zone
//
// variable name: red_cr_transition_width
// Transition zone width for Cr boundary for red
// default value: 10
// data range: 4 to 31
// constraints: red zone should not overlap with other color zones
// effect: Cr width of the red zone transition, larger-> smoother change
//
// variable name: red_cb_transition_width
// Transition zone width for Cb boundary for red
// default value: 10
// data range: 4 to 31
// constraints: red zone should not overlap with other color zones
// effect: Cb width of the red zone transition, larger-> smoother change
//
// variable name: red_bright_index
// Exposure index for full red boosting effect
// default value (calculated) : AEC outdoor index
// data range: 0 to max exp index
// constraints: < red_dark_index
// effect: adjust the exposure level for full red boosting effect.
//
// variable name: red_dark_index
// Exposure index for no red boosting effect
// default value (calculated): (AEC indoor index+AEC outdoor index)/2
// data range: 0 to max exp index
// constraints: > red_bright_index
// effect: adjust the exposure level for no red boosting effect.
/******************************************************************************/

      /* Memory Color Enhancement */
      {
         {20, 40, 200, 235}, /* green y */
         1.000000f, /* green boost factor */
         -10, /* green cr boundary */
         -12, /* green cb boundary */
         8, /* green cr transition width */
         8, /* green cb transition width; ignored, green cr transition width used */
         110, /* green bright index */
         160, /* green dark index */

         {80, 150, 235, 255}, /* blue y */
         1.000000f, /* blue boost factor */
         -18, /* blue cr boundary */
         25, /* blue cb boundary */
         10, /* blue cr transition width */
         10, /* blue cb transition width; ignored, blue cr transition width used */
         110, /* blue bright index */
         160, /* blue dark index */

         {10, 30, 200, 235}, /* red y */
         1.000000f, /* red boost factor */
         45, /* red cr boundary */
         127, /* red cb boundary */
         10, /* red cr transition width */
         10, /* red cb transition width; ignored, red cr transition width used */
         110, /* red bright index */
         160  /* red dark index */
      },
   },
   /* Wavelet Denoise */
   {

/******************************************************************************/
// Feature name: Wavelet denoise
// Applicable chipset:  N/A.
// 3A version: N/A.
// Applicable operation mode:  Snapshot.
//
// Variable name: trigger_value.
// Gain or lux index value for each of the 6 profiles.
// Default value: 1.
// Data range: >=1. Value for the 6 patches are in incrementing order.
//
// Variable name: referenceNoiseProfileData.
// Noise profile (std) of an gray patch. There a total of 6 gray scale levels corresponding to 6 sets of profiles.
// From bright to dark patches.
// Each set of profile has 24 values. The order is:
// y 1st layer HL, y 2nd layer HL, y 3rd layer HL, y 4th layer HL, y 1st layer HH, y 2nd layer HH, y 3rd layer HH, y 4th layer HH,
// Cb 1st layer HL, Cb 2nd layer HL, Cb 3rd layer HL, Cb 4th layer HL, Cb 1st layer HH, Cb 2nd layer HH, Cb 3rd layer HH, Cb 4th layer HH,
// Cr 1st layer HL, Cr 2nd layer HL, Cr 3rd layer HL, Cr 4th layer HL, Cr 1st layer HH, Cr 2nd layer HH, Cr 3rd layer HH, Crb 4th layer HH
// VFE 4 or later chip sets have HW version wavelet, all HL noise profiles are not used.
// Default value: 0.
// Data range: 0-255.
//
// Variable name: denoise_scale.
// Denoise level.
// Default value: 3.
// Data range: 1-7.99
// Effect: Increase noise_scale to denoise more.
//
// Variable name: denoise_edge_softness.
// Edge softness level.
// Default value: 3.
// Data range: 1-15.99
// Effect: Increase denoise_edge_softness to make the edges softer and denoise more.
//
// Variable name: denoise_weight.
// How much of the details are kept with the noise.
// Default value: 0.3
// Data range: 0-1.
// Effect: Decrease denoise_weight to remove details and denoise more.
//
// Variable name: sw_denoise_edge_threshold.
// Edge threshold for the 4th level LL band.
// Default value: 204.
// Data range: 0-1024.
// Effect: Increase sw_denoise_edge_threshold to denoise more for an approximately 16x16 size noise.
/******************************************************************************/

      /* Wavelet Noise SW 420 */
      {

/******************************************************************************/
// Variable name: wavelet_enable_index.
// lux_index threshold above which the wavelet denoise is applied.
// Applicable chipset:  N/A.
// 3A version: N/A
// Applicable operation mode: Snapshot.
// default Value: 1.
// Data Range: 1 to max_exp_index.
// Effect: Larger value results in pictures less likely to undergo wavelet denoise.
/******************************************************************************/

         1, /* Enable Index */
         0, /* Control Method - 1 = Gain, 0 = Lux Index */

/******************************************************************************/
// Feature name: Wavelet denoise
// Variable name: referencePatchAverageValue.
// Lux index or gain for the image.
// Applicable chipset:  N/A.
// 3A version: N/A.
// Applicable operation mode:  Snapshot.
// Default value: 0.
// Data range: 0-255.
//
// Variable name: referenceNoiseProfileData.
// Noise profile(std) of an gray patch.
// Applicable chipset:  N/A.
// 3A version: N/A.
// Applicable operation mode:  snapshot.
// Default value: 0.
// Data range: 0-255.
/******************************************************************************/

         /* Reference Noise */
         {
            /* Noise Profile 1 */
            {
               214.000000f, /* Trigger Value */
               {
                  3.376628f, 4.677872f, 6.443893f, 8.601169f, 2.198115f, 3.094730f, 5.620307f, 7.449698f,
                  0.848824f, 2.293394f, 5.000000f, 5.000000f, 0.348427f, 0.587957f, 4.536259f, 5.000000f,
                  0.593252f, 1.472406f, 5.000000f, 5.000000f, 0.325376f, 0.421650f, 2.875625f, 5.000000f
               },
               /* Denoise Scale Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Scale Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Weight Y */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               /* Denoise Weight Chroma */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               204, /* SW Denosie Edge Threshold Y */
               204, /* SW Denosie Edge Threshold Chroma */
            },
            /* Noise Profile 2 */
            {
               245.000000f, /* Trigger Value */
               {
                  3.911580f, 5.499390f, 7.502824f, 9.579436f, 2.604117f, 3.575772f, 6.665649f, 9.463703f,
                  1.179965f, 2.566192f, 5.000000f, 5.000000f, 0.387337f, 0.608351f, 5.000000f, 5.000000f,
                  0.820130f, 1.595146f, 5.000000f, 5.000000f, 0.320294f, 0.383999f, 3.732808f, 5.000000f
               },
               /* Denoise Scale Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Scale Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Weight Y */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               /* Denoise Weight Chroma */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               204, /* SW Denosie Edge Threshold Y */
               204, /* SW Denosie Edge Threshold Chroma */
            },
            /* Noise Profile 3 */
            {
               275.000000f, /* Trigger Value */
               {
                  4.066029f, 5.589563f, 9.489944f, 12.477220f, 2.744151f, 3.663030f, 7.771169f, 11.066762f,
                  1.494449f, 3.203344f, 6.666667f, 6.666667f, 0.428216f, 0.785964f, 6.666667f, 6.666667f,
                  1.121827f, 2.355729f, 6.666667f, 6.666667f, 0.372860f, 0.593241f, 4.920244f, 6.666667f
               },
               /* Denoise Scale Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Scale Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Weight Y */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               /* Denoise Weight Chroma */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               204, /* SW Denosie Edge Threshold Y */
               204, /* SW Denosie Edge Threshold Chroma */
            },
            /* Noise Profile 4 */
            {
               301.000000f, /* Trigger Value */
               {
                  4.786110f, 7.060870f, 12.792579f, 16.516064f, 3.258939f, 4.365493f, 9.779598f, 13.758019f,
                  2.282425f, 3.867791f, 6.666667f, 6.666667f, 0.662846f, 0.854278f, 6.666667f, 6.666667f,
                  1.493901f, 2.551473f, 6.666667f, 6.666667f, 0.459018f, 0.503784f, 5.024048f, 6.666667f
               },
               /* Denoise Scale Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Scale Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Weight Y */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               /* Denoise Weight Chroma */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               204, /* SW Denosie Edge Threshold Y */
               204, /* SW Denosie Edge Threshold Chroma */
            },
            /* Noise Profile 5 */
            {
               332.000000f, /* Trigger Value */
               {
                  4.875287f, 7.163033f, 12.519852f, 16.661526f, 3.390900f, 4.397045f, 9.844277f, 15.091941f,
                  1.618993f, 4.504890f, 10.000000f, 10.000000f, 0.426637f, 1.136408f, 8.698471f, 10.000000f,
                  1.092578f, 2.829245f, 10.000000f, 10.000000f, 0.376488f, 0.607081f, 5.374961f, 10.000000f
               },
               /* Denoise Scale Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Scale Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Weight Y */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               /* Denoise Weight Chroma */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               204, /* SW Denosie Edge Threshold Y */
               204, /* SW Denosie Edge Threshold Chroma */
            },
            /* Noise Profile 6 */
            {
               357.000000f, /* Trigger Value */
               {
                  5.636543f, 7.729031f, 13.559294f, 19.470200f, 3.915365f, 5.006947f, 11.092156f, 15.357324f,
                  2.503997f, 4.357904f, 10.000000f, 10.000000f, 0.742090f, 0.977382f, 9.463223f, 10.000000f,
                  1.654765f, 2.883477f, 10.000000f, 10.000000f, 0.504174f, 0.634189f, 5.980941f, 10.000000f
               },
               /* Denoise Scale Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Scale Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Weight Y */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               /* Denoise Weight Chroma */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               204, /* SW Denosie Edge Threshold Y */
               204, /* SW Denosie Edge Threshold Chroma */
            },
         },
      },
      /* Wavelet Noise SW 422 */
      {

/******************************************************************************/
// Variable name: wavelet_enable_index.
// lux_index threshold above which the wavelet denoise is applied.
// Applicable chipset:  N/A.
// 3A version: N/A
// Applicable operation mode: Snapshot.
// default Value: 1.
// Data Range: 1 to max_exp_index.
// Effect: Larger value results in pictures less likely to undergo wavelet denoise.
/******************************************************************************/

         1, /* Enable Index */
         0, /* Control Method - 1 = Gain, 0 = Lux Index */

/******************************************************************************/
// Feature name: Wavelet denoise
// Variable name: referencePatchAverageValue.
// Lux index or gain for the image.
// Applicable chipset:  N/A.
// 3A version: N/A.
// Applicable operation mode:  Snapshot.
// Default value: 0.
// Data range: 0-255.
//
// Variable name: referenceNoiseProfileData.
// Noise profile(std) of an gray patch.
// Applicable chipset:  N/A.
// 3A version: N/A.
// Applicable operation mode:  snapshot.
// Default value: 0.
// Data range: 0-255.
/******************************************************************************/

         /* Reference Noise */
         {
            /* Noise Profile 1 */
            {
               0.000000f, /* Trigger Value */
               {
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f,
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f,
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f
               },
               /* Denoise Scale Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Scale Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Weight Y */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               /* Denoise Weight Chroma */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               204, /* SW Denosie Edge Threshold Y */
               204, /* SW Denosie Edge Threshold Chroma */
            },
            /* Noise Profile 2 */
            {
               0.000000f, /* Trigger Value */
               {
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f,
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f,
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f
               },
               /* Denoise Scale Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Scale Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Weight Y */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               /* Denoise Weight Chroma */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               204, /* SW Denosie Edge Threshold Y */
               204, /* SW Denosie Edge Threshold Chroma */
            },
            /* Noise Profile 3 */
            {
               0.000000f, /* Trigger Value */
               {
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f,
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f,
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f
               },
               /* Denoise Scale Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Scale Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Weight Y */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               /* Denoise Weight Chroma */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               204, /* SW Denosie Edge Threshold Y */
               204, /* SW Denosie Edge Threshold Chroma */
            },
            /* Noise Profile 4 */
            {
               0.000000f, /* Trigger Value */
               {
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f,
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f,
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f
               },
               /* Denoise Scale Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Scale Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Weight Y */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               /* Denoise Weight Chroma */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               204, /* SW Denosie Edge Threshold Y */
               204, /* SW Denosie Edge Threshold Chroma */
            },
            /* Noise Profile 5 */
            {
               0.000000f, /* Trigger Value */
               {
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f,
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f,
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f
               },
               /* Denoise Scale Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Scale Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Weight Y */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               /* Denoise Weight Chroma */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               204, /* SW Denosie Edge Threshold Y */
               204, /* SW Denosie Edge Threshold Chroma */
            },
            /* Noise Profile 6 */
            {
               0.000000f, /* Trigger Value */
               {
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f,
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f,
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f
               },
               /* Denoise Scale Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Scale Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Weight Y */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               /* Denoise Weight Chroma */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               204, /* SW Denosie Edge Threshold Y */
               204, /* SW Denosie Edge Threshold Chroma */
            },
         },
      },
      /* Wavelet Noise HW 420 */
      {

/******************************************************************************/
// Variable name: wavelet_enable_index.
// lux_index threshold above which the wavelet denoise is applied.
// Applicable chipset:  N/A.
// 3A version: N/A
// Applicable operation mode: Snapshot.
// default Value: 1.
// Data Range: 1 to max_exp_index.
// Effect: Larger value results in pictures less likely to undergo wavelet denoise.
/******************************************************************************/

         1, /* Enable Index */
         0, /* Control Method - 1 = Gain, 0 = Lux Index */

/******************************************************************************/
// Feature name: Wavelet denoise
// Variable name: referencePatchAverageValue.
// Lux index or gain for the image.
// Applicable chipset:  N/A.
// 3A version: N/A.
// Applicable operation mode:  Snapshot.
// Default value: 0.
// Data range: 0-255.
//
// Variable name: referenceNoiseProfileData.
// Noise profile(std) of an gray patch.
// Applicable chipset:  N/A.
// 3A version: N/A.
// Applicable operation mode:  snapshot.
// Default value: 0.
// Data range: 0-255.
/******************************************************************************/

         /* Reference Noise */
         {
            /* Noise Profile 1 */
            {
               0.000000f, /* Trigger Value */
               {
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.000000f, 1.000000f, 0.500000f, 0.250000f,
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.000000f, 1.000000f, 0.500000f, 0.250000f,
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.000000f, 1.000000f, 0.500000f, 0.250000f
               },
               /* Denoise Scale Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Scale Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Weight Y */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               /* Denoise Weight Chroma */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               204, /* SW Denosie Edge Threshold Y */
               204, /* SW Denosie Edge Threshold Chroma */
            },
            /* Noise Profile 2 */
            {
               0.000000f, /* Trigger Value */
               {
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.000000f, 1.000000f, 0.500000f, 0.250000f,
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.000000f, 1.000000f, 0.500000f, 0.250000f,
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.000000f, 1.000000f, 0.500000f, 0.250000f
               },
               /* Denoise Scale Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Scale Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Weight Y */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               /* Denoise Weight Chroma */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               204, /* SW Denosie Edge Threshold Y */
               204, /* SW Denosie Edge Threshold Chroma */
            },
            /* Noise Profile 3 */
            {
               0.000000f, /* Trigger Value */
               {
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.000000f, 1.000000f, 0.500000f, 0.250000f,
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.000000f, 1.000000f, 0.500000f, 0.250000f,
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.000000f, 1.000000f, 0.500000f, 0.250000f
               },
               /* Denoise Scale Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Scale Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Weight Y */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               /* Denoise Weight Chroma */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               204, /* SW Denosie Edge Threshold Y */
               204, /* SW Denosie Edge Threshold Chroma */
            },
            /* Noise Profile 4 */
            {
               0.000000f, /* Trigger Value */
               {
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.000000f, 1.000000f, 0.500000f, 0.250000f,
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.000000f, 1.000000f, 0.500000f, 0.250000f,
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.000000f, 1.000000f, 0.500000f, 0.250000f
               },
               /* Denoise Scale Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Scale Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Weight Y */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               /* Denoise Weight Chroma */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               204, /* SW Denosie Edge Threshold Y */
               204, /* SW Denosie Edge Threshold Chroma */
            },
            /* Noise Profile 5 */
            {
               0.000000f, /* Trigger Value */
               {
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.000000f, 1.000000f, 0.500000f, 0.250000f,
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.000000f, 1.000000f, 0.500000f, 0.250000f,
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.000000f, 1.000000f, 0.500000f, 0.250000f
               },
               /* Denoise Scale Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Scale Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Weight Y */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               /* Denoise Weight Chroma */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               204, /* SW Denosie Edge Threshold Y */
               204, /* SW Denosie Edge Threshold Chroma */
            },
            /* Noise Profile 6 */
            {
               0.000000f, /* Trigger Value */
               {
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.000000f, 1.000000f, 0.500000f, 0.250000f,
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.000000f, 1.000000f, 0.500000f, 0.250000f,
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.000000f, 1.000000f, 0.500000f, 0.250000f
               },
               /* Denoise Scale Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Scale Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Weight Y */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               /* Denoise Weight Chroma */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               204, /* SW Denosie Edge Threshold Y */
               204, /* SW Denosie Edge Threshold Chroma */
            },
         },
      },
      /* Wavelet Noise HW 422 */
      {

/******************************************************************************/
// Variable name: wavelet_enable_index.
// lux_index threshold above which the wavelet denoise is applied.
// Applicable chipset:  N/A.
// 3A version: N/A
// Applicable operation mode: Snapshot.
// default Value: 1.
// Data Range: 1 to max_exp_index.
// Effect: Larger value results in pictures less likely to undergo wavelet denoise.
/******************************************************************************/

         1, /* Enable Index */
         0, /* Control Method - 1 = Gain, 0 = Lux Index */

/******************************************************************************/
// Feature name: Wavelet denoise
// Variable name: referencePatchAverageValue.
// Lux index or gain for the image.
// Applicable chipset:  N/A.
// 3A version: N/A.
// Applicable operation mode:  Snapshot.
// Default value: 0.
// Data range: 0-255.
//
// Variable name: referenceNoiseProfileData.
// Noise profile(std) of an gray patch.
// Applicable chipset:  N/A.
// 3A version: N/A.
// Applicable operation mode:  snapshot.
// Default value: 0.
// Data range: 0-255.
/******************************************************************************/

         /* Reference Noise */
         {
            /* Noise Profile 1 */
            {
               0.000000f, /* Trigger Value */
               {
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.000000f, 1.000000f, 0.500000f, 0.250000f,
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.000000f, 1.000000f, 0.500000f, 0.250000f,
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.000000f, 1.000000f, 0.500000f, 0.250000f
               },
               /* Denoise Scale Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Scale Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Weight Y */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               /* Denoise Weight Chroma */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               204, /* SW Denosie Edge Threshold Y */
               204, /* SW Denosie Edge Threshold Chroma */
            },
            /* Noise Profile 2 */
            {
               0.000000f, /* Trigger Value */
               {
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.000000f, 1.000000f, 0.500000f, 0.250000f,
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.000000f, 1.000000f, 0.500000f, 0.250000f,
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.000000f, 1.000000f, 0.500000f, 0.250000f
               },
               /* Denoise Scale Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Scale Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Weight Y */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               /* Denoise Weight Chroma */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               204, /* SW Denosie Edge Threshold Y */
               204, /* SW Denosie Edge Threshold Chroma */
            },
            /* Noise Profile 3 */
            {
               0.000000f, /* Trigger Value */
               {
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.000000f, 1.000000f, 0.500000f, 0.250000f,
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.000000f, 1.000000f, 0.500000f, 0.250000f,
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.000000f, 1.000000f, 0.500000f, 0.250000f
               },
               /* Denoise Scale Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Scale Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Weight Y */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               /* Denoise Weight Chroma */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               204, /* SW Denosie Edge Threshold Y */
               204, /* SW Denosie Edge Threshold Chroma */
            },
            /* Noise Profile 4 */
            {
               0.000000f, /* Trigger Value */
               {
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.000000f, 1.000000f, 0.500000f, 0.250000f,
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.000000f, 1.000000f, 0.500000f, 0.250000f,
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.000000f, 1.000000f, 0.500000f, 0.250000f
               },
               /* Denoise Scale Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Scale Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Weight Y */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               /* Denoise Weight Chroma */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               204, /* SW Denosie Edge Threshold Y */
               204, /* SW Denosie Edge Threshold Chroma */
            },
            /* Noise Profile 5 */
            {
               0.000000f, /* Trigger Value */
               {
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.000000f, 1.000000f, 0.500000f, 0.250000f,
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.000000f, 1.000000f, 0.500000f, 0.250000f,
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.000000f, 1.000000f, 0.500000f, 0.250000f
               },
               /* Denoise Scale Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Scale Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Weight Y */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               /* Denoise Weight Chroma */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               204, /* SW Denosie Edge Threshold Y */
               204, /* SW Denosie Edge Threshold Chroma */
            },
            /* Noise Profile 6 */
            {
               0.000000f, /* Trigger Value */
               {
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.000000f, 1.000000f, 0.500000f, 0.250000f,
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.000000f, 1.000000f, 0.500000f, 0.250000f,
                  0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.000000f, 1.000000f, 0.500000f, 0.250000f
               },
               /* Denoise Scale Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Scale Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Y */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Edge Softness Chroma */
               {
                  3.000000f, 3.000000f, 3.000000f, 3.000000f
               },
               /* Denoise Weight Y */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               /* Denoise Weight Chroma */
               {
                  0.300000f, 0.300000f, 0.300000f, 0.300000f
               },
               204, /* SW Denosie Edge Threshold Y */
               204, /* SW Denosie Edge Threshold Chroma */
            },
         },
      },
   },
   /* Wavelet Temporal Noise */
   {
      300, /* Enable Index */
      1, /* Control Method - 1 = Gain, 0 = Lux Index */
      /* Reference Noise */
      {

/******************************************************************************/
// Feature name: Temporal denoise
// Variable name: temporal_denoise_scale_y, temporal_denoise_scale_chroma.
// Denoise level.
// Default value: 3.
// Data range: 1-7.99
// Effect: Increase temporal_denoise_scale to reduce flickering more with increase in ghosting
/******************************************************************************/

         /* Profile 1 */
         {
            0.000000f, /* Trigger Value */
            /* Noise Profile */
            {
               0.000000f, /* Y */
               0.000000f, /* cb */
               0.000000f, /* cr */
            },
            3.000000f, /* Denoise Scale Y */
            3.000000f, /* Denosie Scale Chroma */
         },
         /* Profile 2 */
         {
            0.000000f, /* Trigger Value */
            /* Noise Profile */
            {
               0.000000f, /* Y */
               0.000000f, /* cb */
               0.000000f, /* cr */
            },
            3.000000f, /* Denoise Scale Y */
            3.000000f, /* Denosie Scale Chroma */
         },
         /* Profile 3 */
         {
            0.000000f, /* Trigger Value */
            /* Noise Profile */
            {
               0.000000f, /* Y */
               0.000000f, /* cb */
               0.000000f, /* cr */
            },
            3.000000f, /* Denoise Scale Y */
            3.000000f, /* Denosie Scale Chroma */
         },
         /* Profile 4 */
         {
            0.000000f, /* Trigger Value */
            /* Noise Profile */
            {
               0.000000f, /* Y */
               0.000000f, /* cb */
               0.000000f, /* cr */
            },
            3.000000f, /* Denoise Scale Y */
            3.000000f, /* Denosie Scale Chroma */
         },
         /* Profile 5 */
         {
            0.000000f, /* Trigger Value */
            /* Noise Profile */
            {
               0.000000f, /* Y */
               0.000000f, /* cb */
               0.000000f, /* cr */
            },
            3.000000f, /* Denoise Scale Y */
            3.000000f, /* Denosie Scale Chroma */
         },
         /* Profile 6 */
         {
            0.000000f, /* Trigger Value */
            /* Noise Profile */
            {
               0.000000f, /* Y */
               0.000000f, /* cb */
               0.000000f, /* cr */
            },
            3.000000f, /* Denoise Scale Y */
            3.000000f, /* Denosie Scale Chroma */
         },
      },
      1, /* Algorithm Select, 0 power function, 1 Gaussian, 2 local linear minimum mean-squared error */
   },
   /* Skin Color Enhancement */
   {
      0, /* Skin Color Enhancement Enable */
      0, /* Control Method - 1 = Gain, 0 = Lux Index */

/******************************************************************************/
// Feature name : SCE(skin color enhancement) lowlight trigger points for
// preview and snapashot
/******************************************************************************/

      /* Lowlight Trigger Points */
      {
         7.600000f, /* Gain Start */
         8.000000f, /* Gain End */
         338, /* Lux Index Start */
         376, /* Lux Index End */
      },
      /* A CCT Trigger */
      {
         3300, /* Start */
         3200, /* End */
      },
      /* D65 CCT Trigger */
      {
         4800, /* Start */
         4900, /* End */
      },

/******************************************************************************/
// Feature name : SCE(skin color enhancement)
// variable name: cr_cb_triangle
// Three (Cr,Cb) points form a triangle.
// applicale chipset(s): 7x30, 8660, 867x
// applicable operation mode: preview and snapshot
// default value
// triangle 1: (40,-30), (17,-3), (10,-20)
// triangle 2: (40,-30), (70,-25), (17,-3)
// triangle 3: (40,-30), (65,-55), (70,-25)
// triangle 4: (40,-30), (45,-90), (65,-55)
// triangle 5: (40,-30), (10,-20), (45,-90)
// data range: (-128, 127) for each color channel
// constraints: triangles should not overlap each other
//              points should be in counter-clockwise order
// effect: change color from starting triangular area to target triangular area
/******************************************************************************/

      /* TL84 Origin Triangles */
      {
         /* SCE Origin Triangle 1 */
         {
            {40, -30},
            {17, -3},
            {10, -20}
         },
         /* SCE Origin Triangle 2 */
         {
            {40, -30},
            {70, -25},
            {17, -3}
         },
         /* SCE Origin Triangle 3 */
         {
            {40, -30},
            {65, -55},
            {70, -25}
         },
         /* SCE Origin Triangle 4 */
         {
            {40, -30},
            {45, -90},
            {65, -55}
         },
         /* SCE Origin Triangle 5 */
         {
            {40, -30},
            {10, -20},
            {45, -90}
         },
      },
      /* TL84 Destination Triangles */
      {
         /* SCE Destination Triangle 1 */
         {
            {40, -30},
            {17, -3},
            {10, -20}
         },
         /* SCE Destination Triangle 2 */
         {
            {40, -30},
            {70, -25},
            {17, -3}
         },
         /* SCE Destination Triangle 3 */
         {
            {40, -30},
            {65, -55},
            {70, -25}
         },
         /* SCE Destination Triangle 4 */
         {
            {40, -30},
            {45, -90},
            {65, -55}
         },
         /* SCE Destination Triangle 5 */
         {
            {40, -30},
            {10, -20},
            {45, -90}
         },
      },
      /* TL84 Shift Vector */
      {
         -0.640000f, /* cr */
         0.768000f, /* cb */
      },

/******************************************************************************/
// Feature name : SCE(skin color enhancement)
// variable name: sce_affine_transform_2d
// 2x3 transformation matrix
// applicale chipset(s): 7x30, 8660, 867x
// applicable operation mode: preview and snapshot
// default: a=1, b=0, c=0, d=0,e=1, f=0.
// data range: computed according to start and target triangles
// constraints:
//  cr' = [ a   b    c] cr
//  cb' = [ d   e    f] cb
//   1  = [ 0   0    1] 1
// effect: remap a color to a different color
/******************************************************************************/

      /* Outside Region Mapping */
      {
         1.000000f, /* a */
         0.000000f, /* b */
         0.000000f, /* c */
         0.000000f, /* d */
         1.000000f, /* e */
         0.000000f, /* f */
      },
      /* A Origin Triangles */
      {
         /* SCE Origin Triangle 1 */
         {
            {40, -30},
            {17, -3},
            {10, -20}
         },
         /* SCE Origin Triangle 2 */
         {
            {40, -30},
            {70, -25},
            {17, -3}
         },
         /* SCE Origin Triangle 3 */
         {
            {40, -30},
            {65, -55},
            {70, -25}
         },
         /* SCE Origin Triangle 4 */
         {
            {40, -30},
            {45, -90},
            {65, -55}
         },
         /* SCE Origin Triangle 5 */
         {
            {40, -30},
            {10, -20},
            {45, -90}
         },
      },
      /* A Destination Triangles */
      {
         /* SCE Destination Triangle 1 */
         {
            {40, -30},
            {17, -3},
            {10, -20}
         },
         /* SCE Destination Triangle 2 */
         {
            {40, -30},
            {70, -25},
            {17, -3}
         },
         /* SCE Destination Triangle 3 */
         {
            {40, -30},
            {65, -55},
            {70, -25}
         },
         /* SCE Destination Triangle 4 */
         {
            {40, -30},
            {45, -90},
            {65, -55}
         },
         /* SCE Destination Triangle 5 */
         {
            {40, -30},
            {10, -20},
            {45, -90}
         },
      },
      /* A Shift Vector */
      {
         -0.640000f, /* cr */
         0.768000f, /* cb */
      },
      /* D65 Origin Triangles */
      {
         /* SCE Origin Triangle 1 */
         {
            {40, -30},
            {17, -3},
            {10, -20}
         },
         /* SCE Origin Triangle 2 */
         {
            {40, -30},
            {70, -25},
            {17, -3}
         },
         /* SCE Origin Triangle 3 */
         {
            {40, -30},
            {65, -55},
            {70, -25}
         },
         /* SCE Origin Triangle 4 */
         {
            {40, -30},
            {45, -90},
            {65, -55}
         },
         /* SCE Origin Triangle 5 */
         {
            {40, -30},
            {10, -20},
            {45, -90}
         },
      },
      /* D65 Destination Triangles */
      {
         /* SCE Destination Triangle 1 */
         {
            {40, -30},
            {17, -3},
            {10, -20}
         },
         /* SCE Destination Triangle 2 */
         {
            {40, -30},
            {70, -25},
            {17, -3}
         },
         /* SCE Destination Triangle 3 */
         {
            {40, -30},
            {65, -55},
            {70, -25}
         },
         /* SCE Destination Triangle 4 */
         {
            {40, -30},
            {45, -90},
            {65, -55}
         },
         /* SCE Destination Triangle 5 */
         {
            {40, -30},
            {10, -20},
            {45, -90}
         },
      },
      /* D65 Shift Vector */
      {
         -0.640000f, /* cr */
         0.768000f, /* cb */
      },
   },
   /* Statistics Configuration */
   {
      /* AWB Stats */
      {

/*********************************************************************/
// Feature name : AWB Low Light Bounding Box
// Bounding box to select near gray pixels for AWB under low light.
// This setting is used  when exposure_index reaches max
// exposure_index provided in exposure table in Chromatix header.
/*********************************************************************/

         /* Low-Light AWB Stats */
         {
            20, /* YMin */
            210, /* YMax */
            /* Slope of neutral region and line number */
            7,
            -16,
            16,
            -16,
            /* Cb intercept of neutral region and line number */
            73,
            130,
            -87,
            257
         },

/*********************************************************************/
// Feature name : AWB Bounding Box
// Bounding box to select near gray pixels for AWB under normal and bright light.
// This setting is used  when exposure_index is less than max
// exposure_index provided in exposure table in Chromatix header.
/*********************************************************************/

         /* Normal AWB Stats */
         {
            20, /* YMin */
            210, /* YMax */
            /* Slope of neutral region and line number */
            7,
            -16,
            16,
            -16,
            /* Cb intercept of neutral region and line number */
            73,
            130,
            -87,
            257
         },

/*********************************************************************/
// Feature name : AWB Bright Best Shot Bounding Box
// Bounding box to select near gray pixels for AWB under bright light for
// the following best shot mode only: landscape, beach, snow. Under non best
// shot mode, this setting is not used.
//
/*********************************************************************/

         /* Outdoor AWB Stats */
         {
            20, /* YMin */
            210, /* YMax */
            /* Slope of neutral region and line number */
            7,
            -16,
            16,
            -16,
            /* Cb intercept of neutral region and line number */
            73,
            130,
            -87,
            257
         },
      },
      /* Auto Flicker Detection (8k) */
      {

/******************************************************************************/
// Feature name : Auto flicker detection config (8k)
//
// chromatix_rscs_stat_config_type.row_sum_enable
// default value: 1
// data range: 0 or 1, 0 means disable, 1 means enable.
// constraints: N/A
// effect: enabled or disable AFD STATs collection
//
// chromatix_rscs_stat_config_type.row_sum_hor_Loffset_ratio
// Row sum window left offset/imageWidth ratio in horizontal direction
// default value: 0.0
// data range: 0.0 to 0.9
// constraints:
// effect: larger value will have less pixels on the left side contributed to STATs
//
// chromatix_rscs_stat_config_type.row_sum_ver_Toffset_ratio
// Row sum window top offset/imageWidth ratio in verticle direction
// default value: 0.0
// data range: 0.0 to 0.9
// constraints:
// effect: larger value will have less pixels from the top of image contributed to STATs
//
// chromatix_rscs_stat_config_type.row_sum_hor_Roffset_ratio
// Row sum window right offset/imageWidth ratio in horizontal direction
// default value: 0.0
// data range: 0.0 to 0.9
// constraints:
// effect: larger value will have less pixels on the right side contributed to STATs
//
// chromatix_rscs_stat_config_type.row_sum_ver_Boffset_ratio
// Row sum window bottom offset/imageWidth ratio in verticle direction
// default value: 0.0
// data range: 0.0 to 0.9
// constraints:
// effect: larger value will have less pixels from the bottom of image contributed to STATs
//
// chromatix_rscs_stat_config_type.row_sum_V_subsample_ratio
// Row sum vertical subsample ratio
// default value: 1
// data range: 1,2,3,4
// constraints: integer
// effect: larger value will have less STAT data
//
// chromatix_rscs_stat_config_type.col_sum_enable
// default value: 0
// data range: 0 or 1, 0 means disable, 1 means enable.
// constraints: N/A
// effect: enabled or disable column sum STATs collection
//
// chromatix_rscs_stat_config_type.col_sum_hor_Loffset_ratio
// Col sum window left offset/imageWidth ratio in horizontal direction
// default value: 0.0
// data range: 0.0 to 0.9
// constraints:
// effect: larger value will have less pixels on the left side contributed to STATs
//
// chromatix_rscs_stat_config_type.col_sum_ver_Toffset_ratio
// Col sum window top offset/imageHeight ratio in verticle direction
// default value: 0.0
// data range: 0.0 to 0.9
// constraints:
// effect: larger value will have less pixels from the top of image contributed to STATs
//
// chromatix_rscs_stat_config_type.col_sum_hor_Roffset_ratio
// Col sum window right offset/imageWidth ratio in horizontal direction
// default value: 0.0
// data range: 0.0 to 0.9
// constraints:
// effect: larger value will have less pixels on the left side contributed to STATs
//
// chromatix_rscs_stat_config_type.col_sum_ver_Boffset_ratio
// Col sum window bottom offset/imageHeight ratio in verticle direction
// default value: 0.0
// data range: 0.0 to 0.9
// constraints:
// effect: larger value will have less pixels from the top of image contributed to STATs
//
// chromatix_rscs_stat_config_type.col_sum_H_subsample_ratio
// Col sum horizontal subsample ratio
// default value: 2
// data range: 2,3,4
// constraints: integer
// effect: larger value will have less STAT data
/******************************************************************************/

         1, /* Row Sum Enable */
         0.000000f, /* Row Sum Hor Loffset Ratio */
         0.000000f, /* Row Sum Ver Toffset Ratio */
         0.000000f, /* Row Sum Hor Roffset Ratio */
         0.000000f, /* Row Sum Ver Loffset Batio */
         1, /* Row Sum V Subsample Ratio */
         0, /* Col Sum Enable */
         0.000000f, /* Col Sum Hor Loffset Ratio */
         0.000000f, /* Col Sum Ver Toffset Ratio */
         0.000000f, /* Col Sum Hor Roffset Ratio */
         0.000000f, /* Col Sum Ver Loffset Batio */
         2, /* Col Sum H Subsample Ratio */
      },
      /* Bayer Histogram Config */
      {

/*********************************************************************/
// Feature name :  Bayer Histogram Statistics
// This group of parameters defines the coordinates of single Bayer Histogram window.
// Applicable chipset: all.
// Applicable operation mode:  For VF , snapshot and video.
// Supported 3A version:
//
// Variable name: HorizontalOffsetRatio.
// Horizontal location of first pixel in terms of the ratio to the whole frame size.
// For example, image width is 1000, we want to use the middle 500
// as BH window. Horizontal offset ratio is 250/1000=0.25.
// Data range: 0.0  0.5
// Default value:  0.0
// Constraints: horizontalOffsetRatio + horizontalWindowRatio <= 1.0
//
// Variable name: VerticalOffsetRatio.
// Similar to Horizontal Offset Ratio, but this is in the vertical direction.
// Data range: 0.0  0.5
// Default value:  0.0
// Constraints: verticalOffsetRatio + verticalWindowRatio   <= 1.0
//
// Variable name: HorizontalWindowRatio.
// BH window horizontal size in terms of ratio to the whole image. For the
// same example above, Horizontal Window Ratio is 500/1000=0.5.
// Data range: 0.0  1.0
// Default value:  1.0
// Constraints: horizontalOffsetRatio + horizontalWindowRatio <= 1.0
//
// Variable name: VerticalWindowRatio.
// BH window veritical size in terms of ratio to the whole image. For the
// same example above, Vertical Window Ratio is 500/1000=0.5.
// Data range: 0.0  1.0
// Default value:  1.0
// Constraints: verticalOffsetRatio + verticalWindowRatio   <= 1.0
/*********************************************************************/

         0.000000f, /* Horizontal Offset Ratio */
         0.000000f, /* Vertical Offset Ratio */
         1.000000f, /* Horizontal Window Ratio */
         1.000000f, /* Vertical Window Ratio */
      },
      /* Bayer Grid Config */
      {

/*********************************************************************/
// Feature name :  Bayer Grid Statistics
// This group of parameters defines the coordinates of single Bayer Grid window.
// Applicable chipset: all.
// Applicable operation mode:  For VF , snapshot and video.
// supported 3A version:
//
// Variable name: saturation_thresh_R.
// When collecting Bayer Grid statistics, only pixels with all of its channel values
// same or higher than each channel�s threshold will be counted. This value is the
// threshold for R channel
// Data range: 0  255.
// Default value: 239.
//
// Variable name: saturation_thresh_Gr.
// Similar to saturation_thresh_R, this value is the threshold for Gr channel
// Data range: 0  255
// Default value: 239
//
// Variable name: saturation_thresh_Gb.
// Similar to saturation_thresh_R, this value is the threshold for Gb channel
// Data range: 0  255.
// Default value: 239.
//
// Variable name: saturation_thresh_B.
// Similar to saturation_thresh_R, this value is the threshold for B channel
// Data range: 0  255.
// Default value: 239.
//
// Variable name: HorizontalOffsetRatio.
// Horizontal location of first pixel in terms of the ratio to the whole frame size.
// For example, image width is 1000, we want to use the middle 500 pixels
// as BG window. Horizontal offset ratio is 250/1000=0.25.
// Data range: 0.0  0.5.
// default: 0.015
// Constraints: horizontalOffsetRatio + horizontalWindowRatio <= 1.0
//
// Variable name: VerticalOffsetRatio.
// Similar to Horizontal Offset Ratio, but this is in the vertical direction.
// Data range: 0.0  0.5.
// default: 0.015
// Constraints: verticalOffsetRatio + verticalWindowRatio   <= 1.0
//
// Variable name: HorizontalWindowRatio.
// BG window horizontal size in terms of ratio to the whole image. For the
// same example above, Horizontal Window Ratio is 500/1000=0.5.
// Data range: 0.0  1.0.
// Default value: 0.97
// Constraints: horizontalOffsetRatio + horizontalWindowRatio <= 1.0
//
// Variable name: VerticalWindowRatio.
// BG window veritical size in terms of ratio to the whole image. For the
// same example above, Vertical Window Ratio is 500/1000=0.5.
// Data range: 0.0  1.0.
// Default value: 0.97
// Constraints: verticalOffsetRatio + verticalWindowRatio   <= 1.0
//
// Variable name: num_H_regions.
// Number of Bayer Grid regions in horizontal direction
// range: 1  72.
// Default value: 64.
//
// Variable name: num_V_regions.
// Number of Bayer Grid regions in vertical direction
// Data range: 1  48.
// Default value: 48.
/*********************************************************************/

         239, /* Saturation Thresh R */
         239, /* Saturation Thresh GR */
         239, /* Saturation Thresh GB */
         239, /* Saturation Thresh B */
         0.015000f, /* Horizontal Offset Ratio */
         0.015000f, /* Vertical Offset Ratio */
         0.970000f, /* Horizontal Window Ratio */
         0.970000f, /* Vertical Window Ratio */
         64, /* Num H Regions */
         48, /* Num V Regions */
      },
      /* Bayer Exp Window */
      {
         255, /* Saturation Thresh R */
         255, /* Saturation Thresh GR */
         255, /* Saturation Thresh GB */
         255, /* Saturation Thresh B */
         0.000000f, /* Horizontal Offset Ratio */
         0.000000f, /* Vertical Offset Ratio */
         1.000000f, /* Horizontal Window Ratio */
         1.000000f, /* Vertical Window Ratio */
         32, /* Num H Regions */
         24, /* Num V Regions */
      },
   },
   /* Skintone Detection */
   {

/******************************************************************************/
// Feature name : Skin Tone Detection
// Applicale chipset(s): MSM8xxx chips.
// Applicable operation mode: For VF and snapshot.
//
// skintone_Hmin
// The negative of the minimum value of the H range.
// Default value:  1.5.
// Data range: 1.0 to 3.0.
// Constraints: skintone_Hmin > skintone_Hmax (because the original data is negative).
// Effect: Larger values will result in smaller skin tone range.
//
// skintone_Hmax
// The negative of the maximum value of the H range.
// Default value:  0.5.
// Data range: 0.0 to 1.0.
// Constraints: skintone_Hmin > skintone_Hmax (because the original data is negative)
// Effect: Larger values will result in wider skin tone range.
//
// skintone_Ymin
// The minimum value of the Y range.
// Applicable operation mode:  For VF and snapshot.
// Default value:  0.1.
// Data range: 0.0 to 0.3.
// Constraints: skintone_Ymax > skintone_Ymin.
// Effect: Smaller values will result in wider skin tone range, including more dark areas.
//
// skintone_Ymax
// The maximum value of the Y range.
// Default value:  0.9.
// Data range: 0.7 to 1.0.
// Constraints: skintone_Ymax > skintone_Ymin.
// Effect: Larger values will result in wider skin tone range, including more bright areas.
//
// skintone_S_HY_min
// The minimum value of S on Ymax level.
// Default value:  0.05.
// Data range: 0.0 to 0.4.
// Constraints: skintone_S_HY_max > skintone_S_HY_min.
// Effect: Smaller values will result in wider skin tone range.
//
// skintone_S_HY_max
// The maximum value of S on Ymax level.
// Default value:  0.25.
// Data range: 0.1 to 0.5.
// Constraints: skintone_S_HY_max > skintone_S_HY_min.
// Effect: Larger values will result in wider skin tone range.
//
// skintone_S_LY_min
// The minimum value of S on Ymin level.
// Default value:  0.25.
// Data range: 0.0 to 0.5.
// Constraints: skintone_S_LY_max > skintone_S_LY_min.
// Effect: smaller values will result in wider skin tone range.
//
// skintone_S_LY_max
// The maximum value of S on Ymin level.
// Default value:  0.6.
// Data range: 0.2 to 1.0.
// Constraints: skintone_S_LY_max > skintone_S_LY_min.
// Effect: Larger values will result in wider skin tone range.
//
// skintone_percentage
// Percentage of skin color pixels to activate skin color map.
// Default value:  50.
// Data range: 0 to 100.
// Effect: The larger the value, the harder to activate the skin color map.
/******************************************************************************/

      1.500000f, /* H Min */
      0.500000f, /* H Max */
      0.100000f, /* Y Min */
      0.900000f, /* Y Max */
      0.050000f, /* S HY Min */
      0.250000f, /* S HY Max */
      0.250000f, /* S LY Min */
      0.600000f, /* S LY Max */
      50, /* Percentage */
   },
},
/* Manual Whitebalance */
{

/*********************************************************************/
// Feature name :
// Manual white balance gains for both snapshot and viewfinder.
/*********************************************************************/

   /* TL84 Whitebalance - RGB */
   {1.386000f, 1.000000f, 2.126000f},
   /* D50 Whitebalance - RGB */
   {1.807000f, 1.000000f, 2.006000f},
   /* A Whitebalance - RGB */
   {1.239000f, 1.000000f, 2.671000f},
   /* D65 Whitebalance - RGB */
   {1.997000f, 1.000000f, 1.406000f},
   /* Strobe Flash Whitebalance - RGB */
   {1.989000f, 1.000000f, 1.689000f},
   /* LED Flash Whitebalance - RGB */
   {1.989000f, 1.000000f, 1.689000f},
},
/* Auto Whitebalance */
{
   1, /* Software Type */

/*********************************************************************/
// Feature name :
//
// R/G ratio, B/G ratio: AWB referecne points used for auto WB calculation.
//
//Red Gain Adjust,Blue Gain Adjust: Additional gain applied for snapshot only.
/*********************************************************************/

   /* AWB Reference Points w/HW */
   {
      /* D65 AWB Reference Point */
      {
         1.000000f,   /* R/G ratio */
         1.000000f,   /* B/G ratio */
      },
      /* Shade AWB Reference Point */
      {
         1.000000f,   /* R/G ratio */
         1.000000f,   /* B/G ratio */
      },
      /* A AWB Reference Point */
      {
         1.000000f,   /* R/G ratio */
         1.000000f,   /* B/G ratio */
      },
      /* TL84 AWB Reference Point */
      {
         1.000000f,   /* R/G ratio */
         1.000000f,   /* B/G ratio */
      },
      /* CoolWhite AWB Reference Point */
      {
         1.000000f,   /* R/G ratio */
         1.000000f,   /* B/G ratio */
      },
      /* Horizon AWB Reference Point */
      {
         1.000000f,   /* R/G ratio */
         1.000000f,   /* B/G ratio */
      },
      /* D50 AWB Reference Point */
      {
         1.000000f,   /* R/G ratio */
         1.000000f,   /* B/G ratio */
      },
      /* Cust. Fluor. AWB Reference Point */
      {
         1.000000f,   /* R/G ratio */
         1.000000f,   /* B/G ratio */
      },
      /* Noon AWB Reference Point */
      {
         1.000000f,   /* R/G ratio */
         1.000000f,   /* B/G ratio */
      },
      /* Custom Daylight AWB Reference Point */
      {
         1.000000f,   /* R/G ratio */
         1.000000f,   /* B/G ratio */
      },
      /* Custom A AWB Reference Point */
      {
         1.000000f,   /* R/G ratio */
         1.000000f,   /* B/G ratio */
      },
      /* U30 AWB Reference Point */
      {
         1.000000f,   /* R/G ratio */
         1.000000f,   /* B/G ratio */
      },
   },
   /* LED Gain Adjust */
   {
      1.000000f, /* Red */
      1.000000f, /* Blue */
   },
   /* Strobe Gain Adjust */
   {
      1.000000f, /* Red */
      1.000000f, /* Blue */
   },
   /* AWB Gain Adjust */
   {
      /* D65 */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* D75 */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* A */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* TL84 */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* CW */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* Horizon */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* D50 */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* Cust Flo */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* Noon */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* Daylight */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* Cust A */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* U30 */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
   },
   /* AWB Lowlight Gain Adjust */
   {
      /* D65 */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* D75 */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* A */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* TL84 */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* CW */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* Horizon */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* D50 */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* Cust Flo */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* Noon */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* Daylight */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* Cust A */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* U30 */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
   },

/*********************************************************************/
// Comment:
// Indoor and outdoor index are the parameters used in AWB algorithm in
// a variety of heuristics. We do not recommend the user change these values.
/*********************************************************************/

   290, /* Indoor Index */
   190, /* Outdoor Index */

/*********************************************************************/
// Feature name :
// Blue gain adj ratio is used for Snow and Beach best shot modes only. This factor
// is applied on top of the blue WB gain determined by AWB algorithm.
// Range: 0.7 to 1.5.
/*********************************************************************/

   1.100000f, /* Snow Blue Gain Adj Ratio */
   0.900000f, /* Beach Blue Gain Adj Ratio */

/*********************************************************************/
// Feature name :
// The following group of parameters are used by AWB algorithm. We do not
// recommend the user modify them.
/*********************************************************************/

   8, /* Outlier Distance */
   0, /* Green Zone Offset RG */
   0, /* Green Zone Offset BG */
   2, /* Num Frames to skip after changing VFE */

/*******************************************************************************/
// variable name: awb_extreme_RG_ratio_threshold
// boundary to collect stat in R/G direction
// applicale chipset(s): VFE 3.1 and higher
// applicable operation mode: preview, camcorder, snapshot
// default value (calculated-NA): 1.1 x R/G value of blue patch on MCC (#15) under Horizon
// data range: 0.0 to 4.0
// constraints: 0.0 to 4.0
// effect: higher value allows less pixels to be collected.
/******************************************************************************/

   100.000000f, /* AWB Extreme RG Ratio Treshold */

/*******************************************************************************/
// variable name: awb_extreme_BG_ratio_threshold
// boundary to collect stat in B/G direction
// applicale chipset(s): VFE 3.1 and higher
// applicable operation mode: preview, camcorder, snapshot
// default value (calculated-NA): 1.1 x B/G value of blue patch on MCC (#13) under TL84
// data range: 0.0 to 4.0
// constraints: 0.0 to 4.0
// effect: higher value allows less pixels to be collected.
/******************************************************************************/

   100.000000f, /* AWB Extreme BG Ratio Treshold */
   /* More AWB Parameters */
   60, /* Compact Cluster R2 */
   101, /* Compact Cluster To Ref Point R2 */
   75, /* A Cluster Threshold */
   75, /* F Cluster Threshold */
   60, /* Day Cluster Threshold */
   12, /* Outdoor Green Threshold */
   8, /* Outdoor Green Threshold Bright F */
   15, /* Outdoor Green Threshold Dark F */
   12, /* Day Cluster Threshold For F */
   1, /* Whitebalance Allow FLine */
   15, /* Outdoor Valid Sample Count Threshold */
   25, /* Outdoor Green Upper Threshold */
   1000, /* R2 Threshold */
   8, /* Outdoor Green Threshold Bright A */
   15, /* Outdoor Green Threshold Dark A */
   12, /* Day Cluster Threshold For A */

/*********************************************************************/
// Feature name :
// The final WB gain applied to the system is mandated to be between min
// and max WB values.  We do not recommend the user change the values.
/*********************************************************************/

   /* AWB Min Gains - RGB */
   {1.000000f, 1.000000f, 1.000000f},
   /* AWB Max Gains - RGB */
   {3.990000f, 3.990000f, 3.990000f},

/*********************************************************************/
// Feature name :
// The following group of parameters are used by AWB algorithm. We do not
// recommend the user modify them.
/*********************************************************************/

   { 1.000000f, 1.000000f }, /* AWB Sample Influence, Outdoor/Indoor */
   /* AWB Weight Vector */
   {
      {1, 80, 20}, /* AWB Weight Vector D65 */
      {5, 40, 20}, /* AWB Weight Vector D75 */
      {5, 2, 1}, /* AWB Weight Vector A */
      {100, 1, 20}, /* AWB Weight Vector Warm F */
      {90, 1, 15}, /* AWB Weight Vector Cool F */
      {3, 1, 1}, /* AWB Weight Vector Horizon */
      {1, 100, 5}, /* AWB Weight Vector D50 */
      {5, 1, 3}, /* AWB Weight Vector Cust F */
      {1, 100, 5}, /* AWB Weight Vector Daylight Noon */
      {1, 1, 1}, /* AWB Weight Vector Custom Daylight */
      {1, 1, 1}, /* AWB Weight Vector Custom A */
      {1, 1, 1}, /* AWB Weight Vector U30 */
      {1, 1, 1}, /* AWB Weight Vector DayLine 1 */
      {1, 1, 1}, /* AWB Weight Vector DayLine 2 */
      {1, 1, 1}, /* AWB Weight Vector FLine */
      {1, 1, 1}, /* AWB Weight Vector ALine 1 */
      {1, 1, 1}, /* AWB Weight Vector ALine 2 */
   },
   70, /* AWB White World Y Min Ratio */

/*********************************************************************/
// Feature name :
// AWB aggresiveness
// 0 low aggressive
// 1 medium aggressive
// 2 high aggressive
/*********************************************************************/

   0, /* AWB Aggressiveness */
   0, /* AWB Self-Calibrate */

/******************************************************************************/
// Feature name : AWB self calibration
// variable name:
// Adjust amount of adjustment allowed for AWB self calibration
// applicale chipset(s): all MSM
// applicable operation mode: preview
// default value: high=1.15
// default value: low=0.9
// data range: high (1.0, 1.2), low (0.8, 1.0)
// constraints:
// effect: larger high = larger adjustment, smaller low = larger adjustment
/******************************************************************************/

   1.150000f, /* AWB Self-Calibrate Adjust Ratio High */
   0.900000f, /* AWB Self-Calibrate Adjust Ratio Low */

/******************************************************************************/
// Feature name : AWB
// applicale chipset(s): all MSM
// applicable operation mode: preview
//
// variable name: awb_enable_lock_heuristics_1
// Enable lock heuristics #1
// default value: 1 (enable)
// data range: 0 or 1
// constraints: 0 or 1
// effect: 1 to enable lock/unlock heuristics #1.
// Prevents outdoor decision to be switched into indoor.
//
// variable name: awb_enable_lock_heuristics_2
// Enable lock heuristics #2
// default value: 1 (enable)
// data range: 0 or 1
// constraints: 0 or 1
// effect: 1 to enable lock/unlock heuristics #2.
// Prevents fluorescent light to be switched to outdoor.
//
// variable name: awb_enable_lock_heuristics_3
// Enable lock heuristics #3
// default value: 1 (enable)
// data range: 0 or 1
// constraints: 0 or 1
// effect: 1 to enable lock/unlock heuristics #3.
// Prevents fluorescent light to be switched to incandescent.
/******************************************************************************/

   1, /* AWB Enable Lock Heuristics 1 */
   1, /* AWB Enable Lock Heuristics 2 */
   1, /* AWB Enable Lock Heuristics 3 */
   0, /* Indoor Daylight Lock Enable */

/******************************************************************************/
// Feature name : AWB
// variable name: awb_enable_white_world
// Enable adaptive white world
// applicale chipset(s): all MSM
// applicable operation mode: preview
// default value: 1 (enable)
// data range: 0 or 1
// constraints: 0 or 1
// effect: 1 to enable adaptive white world
/******************************************************************************/

   1, /* AWB Enable White World */
   /* Purple Prevent */
   {

/******************************************************************************/
// Feature name : AWB Extended
// applicable chipset:  all VFEs.
// applicable operation mode: View finder and snapshot.
//
// variable name: AWB_purple_prevent_enable
// Enables the feature.
// default value: 1
// data range: 0 and 1
// constraints: None
//
// variable name: control_purple_prevent
// Control with gain or lux_index
// default Value: 0
// Data Range: 0 or 1.
// constraints: None
// effect: use gain or lux_index for control purple sky prevention
//
// variable name: purple_prevent_trigger
// Control the purple sky prevention adjustment trigger
// default Value: between  outdoor index and outdoor index
// Data Range: integers 0 to a few hundreds.
// constraints: only for bright outdoor
// effect: smaller index values make the purple sky prevention harder to take effect. (has to be very bright)
//
// variable name: purple_sky_prevention_bg_threshold
// Control the purple sky prevention adjustment
// default Value: BG ratio of D50
// Data Range: 0 to 2
// constraints: around D50
// effect: smaller index values make the adjustment larger.
/******************************************************************************/

      1, /* Enable */
      0, /* Control Method - 1 = Gain, 0 = Lux Index */
      /* Trigger Point */
      {
         2.000000f, /* Gain Start */
         1.000000f, /* Gain End */
         188, /* Lux Index Start */
         169, /* Lux Index End */
      },
      1.000000f, /* Sky Prevention BG Thresh */
   },
   60, /* AWB Ymin Low Threshold */
   98, /* AWB Ymin High Threshold */

/******************************************************************************/
// Feature name : AWB golden module calibration data
//               for module-by-module variation
// applicale chipset(s): all MSM
// applicable operation mode: camera & camcorder preview/recording/snapshot
//
// variable name: AWB_golden_module_R_Gr_ratio
// Not tunable. Read it out from module�s EEPROM and convert into floating point
// default value: none. The value read out from module�s EEPROM
// data range: 0 and 4
// constraints: none
// effect: not tunable

// variable name: AWB_golden_module_Gb_Gr_ratio
// Not tunable. Read it out from module�s EEPROM and convert into floating point
// default value: none. The value read out from module�s EEPROM
// data range: 0.8 and 1.2
// constraints: none
// effect: not tunable
//
// variable name: AWB_golden_module_B_Gr_ratio
// Not tunable. Read it out from module�s EEPROM and convert into floating point
// default value: none. The value read out from module�s EEPROM
// data range: 0 and 4
// constraints: none
// effect: not tunable
/******************************************************************************/

   /* R/Gr */
   {
      1.000000f, /* Golden Module R/Gr ratio D65 */
      1.000000f, /* Golden Module R/Gr ratio D75 */
      1.000000f, /* Golden Module R/Gr ratio A */
      1.000000f, /* Golden Module R/Gr ratio TL84 */
      1.000000f, /* Golden Module R/Gr ratio CW */
      1.000000f, /* Golden Module R/Gr ratio H */
      1.000000f, /* Golden Module R/Gr ratio D50 */
      1.000000f, /* Golden Module R/Gr ratio Cust F */
      1.000000f, /* Golden Module R/Gr ratio Noon */
      1.000000f, /* Golden Module R/Gr ratio Cust Daylight */
      1.000000f, /* Golden Module R/Gr ratio Cust A */
      1.000000f, /* Golden Module R/Gr ratio U30 */
   },
   /* Gb/Gr */
   {
      1.000000f, /* Golden Module Gb/Gr ratio D65 */
      1.000000f, /* Golden Module Gb/Gr ratio D75 */
      1.000000f, /* Golden Module Gb/Gr ratio A */
      1.000000f, /* Golden Module Gb/Gr ratio TL84 */
      1.000000f, /* Golden Module Gb/Gr ratio CW */
      1.000000f, /* Golden Module Gb/Gr ratio H */
      1.000000f, /* Golden Module Gb/Gr ratio D50 */
      1.000000f, /* Golden Module Gb/Gr ratio Cust F */
      1.000000f, /* Golden Module Gb/Gr ratio Noon */
      1.000000f, /* Golden Module Gb/Gr ratio Cust Daylight */
      1.000000f, /* Golden Module Gb/Gr ratio Cust A */
      1.000000f, /* Golden Module Gb/Gr ratio U30 */
   },
   /* B/Gr */
   {
      1.000000f, /* Golden Module B/Gr ratio D65 */
      1.000000f, /* Golden Module B/Gr ratio D75 */
      1.000000f, /* Golden Module B/Gr ratio A */
      1.000000f, /* Golden Module B/Gr ratio TL84 */
      1.000000f, /* Golden Module B/Gr ratio CW */
      1.000000f, /* Golden Module B/Gr ratio H */
      1.000000f, /* Golden Module B/Gr ratio D50 */
      1.000000f, /* Golden Module B/Gr ratio Cust F */
      1.000000f, /* Golden Module B/Gr ratio Noon */
      1.000000f, /* Golden Module B/Gr ratio Cust Daylight */
      1.000000f, /* Golden Module B/Gr ratio Cust A */
      1.000000f, /* Golden Module B/Gr ratio U30 */
   },
   0, /* Enable AWB Module Cal */
   /* AWB Motion Sensor */
   {

/******************************************************************************/
// Feature name : AWB_motion_sensor_type to aide AWB in determining a change in
//           scene.
// Applicable chipset: MSM7x30, QSD8x60, and newer chipsets.
// Applicable operation mode: Viewfinder and video.
//
// Variable name: awb_gyro_trigger.
// Used to control how scene change should be detected for AEC
// 3A version: 3.0.
// Default value: 0.0.
// Data range: -16000.0 to +16000.0.
// Constraints: None .
// Effect: The bigger the value is, the less sensitive AEC response to
//         gyro output value.
//
// Variable name: awb_accelerometer_trigger.
// Used to control how scene change should be detected for AEC.
// 3A version: 3.0.
// Default value: 0.0.
// Data range: -16000.0 to +16000.0.
// Constraints: None.
// Effect: The bigger the value is, the less sensitive AEC response to
//         accelerometer change.
//
// Variable name: awb_magnetometer_trigger.
// Used to control how scene change should be detected for AEC
// 3A version: 3.0.
// Default value: 0.0.
// Data range: 0.0 to 360.0.
// Constraints: None.
// Effect: The bigger the value is, the less sensitive AEC response to
//         magnetic field change.
//
// Variable name: awb_DIS_motion_vector_trigger.
// Used to control how scene change should be detected for AEC.
// 3A version: 3.0.
// Default value: 0.0.
// Data range: -16000.0 to +16000.0.
// Constraints: None.
// Effect: The bigger the value is, the less sensitive AEC response to
//         digital image stabilization movement/compensation value.
/******************************************************************************/

      0.000000f, /* Gyro Trigger */
      0.000000f, /* Accelerometer Trigger */
      0.000000f, /* Magnetometer Trigger */
      0.000000f, /* DIS Motion Vector Trigger */
   },
   0.000000f, /* LED/Strobe Adjustment Factor */
   0, /* Lowlight Toggle Enable */
   0, /* Interpolate Gain Adj Enable */
   /* Lowlight LUT */
   {
      1, /* Enable */
      {
         /* Entry 0 */
         {
            232, /* Lux Index */
            0.000000f, /* Green RG Offset Adj */
            0.000000f, /* Green BG Offset Adj */
            0.000000f, /* Outlier Dist Adj */
         },
         /* Entry 1 */
         {
            262, /* Lux Index */
            -1.679850f, /* Green RG Offset Adj */
            -4.880369f, /* Green BG Offset Adj */
            5.161385f, /* Outlier Dist Adj */
         },
         /* Entry 2 */
         {
            287, /* Lux Index */
            -11.184973f, /* Green RG Offset Adj */
            -11.330027f, /* Green BG Offset Adj */
            15.920839f, /* Outlier Dist Adj */
         },
         /* Entry 3 */
         {
            316, /* Lux Index */
            -11.184973f, /* Green RG Offset Adj */
            -11.330027f, /* Green BG Offset Adj */
            15.920839f, /* Outlier Dist Adj */
         },
         /* Entry 4 */
         {
            344, /* Lux Index */
            -11.184973f, /* Green RG Offset Adj */
            -11.330027f, /* Green BG Offset Adj */
            15.920839f, /* Outlier Dist Adj */
         },
         /* Entry 5 */
         {
            357, /* Lux Index */
            -11.184973f, /* Green RG Offset Adj */
            -11.330027f, /* Green BG Offset Adj */
            15.920839f, /* Outlier Dist Adj */
         },
      },
   },

/******************************************************************************/
// Feature name : Match LED Level
// Applicale chipset: MSM8x30 and later.
// Applicable operation mode:  For video and snapshot.
//
// This is the feature to match dual LED flash with the ambient lighting.
//
// Desription of variables in chromatix_match_LED_lighting_table
// structure.
//
// Variable names: table_size, CCT_control[table_size-1].
// The three values for the table entries:
// The color temperature
// The LED1 current configuration for LED controller IC
// The LED2 current configuration for LED controller IC
/******************************************************************************/

   /* Mix LED Table */
   {
      0, /* Table Size */
      {
         /* Entry 0 */
         {
            0, /* CCT */
            0, /* LED1 Config */
            0, /* LED2 Config */
         },
         /* Entry 1 */
         {
            0, /* CCT */
            0, /* LED1 Config */
            0, /* LED2 Config */
         },
         /* Entry 2 */
         {
            0, /* CCT */
            0, /* LED1 Config */
            0, /* LED2 Config */
         },
         /* Entry 3 */
         {
            0, /* CCT */
            0, /* LED1 Config */
            0, /* LED2 Config */
         },
         /* Entry 4 */
         {
            0, /* CCT */
            0, /* LED1 Config */
            0, /* LED2 Config */
         },
         /* Entry 5 */
         {
            0, /* CCT */
            0, /* LED1 Config */
            0, /* LED2 Config */
         },
         /* Entry 6 */
         {
            0, /* CCT */
            0, /* LED1 Config */
            0, /* LED2 Config */
         },
         /* Entry 7 */
         {
            0, /* CCT */
            0, /* LED1 Config */
            0, /* LED2 Config */
         },
         /* Entry 8 */
         {
            0, /* CCT */
            0, /* LED1 Config */
            0, /* LED2 Config */
         },
         /* Entry 9 */
         {
            0, /* CCT */
            0, /* LED1 Config */
            0, /* LED2 Config */
         },
         /* Entry 10 */
         {
            0, /* CCT */
            0, /* LED1 Config */
            0, /* LED2 Config */
         },
         /* Entry 11 */
         {
            0, /* CCT */
            0, /* LED1 Config */
            0, /* LED2 Config */
         },
         /* Entry 12 */
         {
            0, /* CCT */
            0, /* LED1 Config */
            0, /* LED2 Config */
         },
         /* Entry 13 */
         {
            0, /* CCT */
            0, /* LED1 Config */
            0, /* LED2 Config */
         },
         /* Entry 14 */
         {
            0, /* CCT */
            0, /* LED1 Config */
            0, /* LED2 Config */
         },
         /* Entry 15 */
         {
            0, /* CCT */
            0, /* LED1 Config */
            0, /* LED2 Config */
         },
      },
   },
},
/* Bayer AWB Params */
{

/*****************************************************************/
// Feature name: Bayer AWB parameters.
// Applicable chipset:  VFE3.3 and higher.
// 3A version: 4.0 and higher.
// Applicable operation mode: preview and snapshot
// (except for preview aggressivenes and camcorder aggressiveness).
//
// Variable name: bright_green_percentage.
// Bright green percentage at outdoor index.
// Default value: 6.
// Data range: 0 to 100.
// Constraints: This is a pre-set threshold obtained by testing.
// Effect: Higher value extends the outdoor green range.
//
// Variable name: dark_green_percentage.
// Dark green percentage at indoor index.
// Default value: 12.
// Data range: 0 to 100.
// Constraints: This is a pre-set threshold obtained by testing.
// Effect: Indoor green range is extended or narrowed down.
//
// Variable names: dark_r_threshold, dark_g_threshold, dark_b_threshold.
// R(or G or B) stat ave below this value is rejected (8-bit domain).
// Default value: 1.
// Data range: 0 to 255.
// Constraints: This is a pre-set threshold for collecting certain level of the red/green/blue stat.
// Effect: Lower values allow stats with lower r, g, b values be collected.
//
// Variable name: white_stat_y_threshold_high.
// The Y threshold for a region to be a white stat.
// Default value: white_stat_y_threshold_high=245.
// Data range: 0 to 255.
// Constraints: None.
// Effect: The upper limit for collecting white stat.
//         Too high will involve saturated stat,
//         and too low may reduce white stat collection accuracy.
//
// Variable names: threshold_extreme_b_percent, threshold_extreme_r_percent.
// Threshold of the blue or red extreme stat counts.
// Default value: 0.1
// Data range: 0 to 1.
// Constraints: None.
// Effect: Higher value requires a higher number of the collected
//         extreme stats to be recognized as an extreme color case.
//
// Variable name: threshold_compact_cluster.
// Compact cluster threshold.
// Default value: 60.
// Data range: 0 to 1000.
// Constraints: None.
// Effect: This is the threshold of measured distance from outlier sample grid to the average.
//         If the measured maximum distance is lower than this threshold, a compact cluster is recognized.
//         Therefore, a too high threshod results in false-alarm compact cluster recognition,
//         and too low threshold may result in missed detection on the compact cluters.
//
// Variable name: compact_to_grey_dis.
// Outlier compact cluster distance to grey zone.
// Default value: 4.
// Data range: 0 to 100.
// Constraints: None
// Effect: Lower value requires the recognized compact cluster is
//         closer to the grey zone.
//
// Variable name: threshold_compact_cluster_valid.
// Radius of the compact cluster within grey zone.
// Default value: 4.
// Data range: 0 to 100.
// Constraints: None.
// Effect: Lower value requires that the recognized compact cluster have a smaller radius.
//
// Variable name: dominant_cluster_threshold.
// Dominant cluster threshold.
// Default value: 4.
// Data range: 0 to 1000.
// Constraints: None
// Effect: This threshold decides on if there is a dominant cluster or not.
//         Higher threshold gives higher requirement on the cluster counts
//         to be recognized as a dominant cluster.
//
// Variable name: distance_weight_table[121].
// Distance weight table.
// Data range: 0 to 3888.
// Constraints: None
// Effect: This array is used to control the distance weighting.  The index to the LUT is the grid distance.
//         If the outlier distance is N, only the first N entries of this weight table is non-zero, and all other entries are 0�s.
//         With a Gaussian kernel, the stat closer to reference points are given higher weight than stat farther away.
//         With equal weight, all samples in the grey zone are treated equally.
//
// Variable name: outdoor_adjustment.
// Adjustable parameters for outdoor exposure range control.
// Default value: 30.
// Data range: 0 to 140.
// Constraints: None.
// Effect: This parameter adjusts the range of the exposure in outdoor conditions.
//         Higher values give narrower range for Noon and D50 exposure range but larger D65 exposure range.
//         This parameter is used for easy exposure adjustment for different sensors.
//
// Variable name: exposure_adjustment.
// Interpolation range adjustment on the boundary of two different AWB decisions.
// Default value: 5.
// Data range: 0 to 140.
// Constraints: None.
// Effect: This parameter adjusts the interpolation range on the boundary of two different AWB decisions based on exposure.
//         Higher values give a larger interpolation range which results in a smoother AWB decision change.
//
// Variable name: outlier_valid_ymax_ratio.
// Check if Y max in outliers is outlier_valid_ymax_ratio
// times higher than the Y max in valid samples.
// Default value: 3.
// Data range: 1 to 10.
// Constraints: None.
// Effect: If outlier Y max is outlier_valid_ymax times more than the Y max in valid samples,
//         set white world decision to be -1. higher value requires a higher threshold for this decision.
//
// Variable names: cluster_high_pec, cluster_mid_pec, cluster_low_pec
// Cluster percentage to determine dominant light in heuristics.
// Default values: 0.40, 0.25, 0.15;
// Data range: 0 to 1
// Constraints: None.
// Effect: These three parameters set three boundaries to recognize the dominant cluster in heuristics.
//         Higher values require a larger number of cluster counts. For example, cluster_high_pec=0.25 requires
//         the corresponding cluster to have a 25 percentage of the total-cluster-counts to proceed to the
//         corresponding AWB decision making. While cluster_low_pec=0.1 only requires 10 percentage of the
//         total-cluster counts to proceed to the corresponding AWB decision making.
//
// Variable name: weight_vector.
// Weight vector corresponding to different range of exposure index.
// Four columns correspond to four exp index ranges: [0,outdoor], [outdoor, inoutdoor], [inoutdoor, indoor], [indoor, maxindex].
// Default value: { {1, 10, 10, 5},/* D65 30 */
//                  {1, 10, 10, 5},/* D75 30*/
//                  {0, 0, 1, 8},/* A */
//                  {0, 0, 5, 10},/* TL84 wf 3800*/
//                  {0, 0, 3, 10},/* cf 4000*/
//                  {0, 0, 1, 2},/* H */
//                  {10, 10, 1, 1}, /* D50 30*/
//                  {0, 0, 1, 8},/* custom f */
//                  {10, 10, 1, 1}, /* noon */
//                  {8, 9, 8, 3}, /* daylight hybrid 1*/
//                  {1, 5, 10, 5},/* daylight hybrid 2 */
//                  {0, 0, 2, 3},/* A light line 1*/
//                  {0, 0, 1, 2},/* A light line 2*/
//                  {0, 0, 5, 10},/* F line */
//                  {1, 10, 10,5}, /* Custom day */
//                  {0, 0, 1, 8},// { 1, 1, 1, 1}, /* Custom A */
//                  {0, 0, 1, 8}//{ 1, 1, 1, 1} /* U30 */
//                  };
// Data range: 0 to 10.
// Constraints: None.
// Effect: Higher values give higher weight to the stat at the exposure index in the corresponding range.
//
// Variable names: ref_b_bg_tl84, ref_r_rg_a.
// This reference R, B 's r/g b/g are for 8k FFA; it needs to be tuned for other sensors.
// Corresponding rolloff table should be applied when doing the measurement.
// Default value: these two values are specifically estimated for the corresponding sensor. Default value for 8k foxcon sensor are:  ref_b_bg_tl84 = 1.4049; ref_r_rg_a = 3.1547;
// Data range: 0 to 10
// Constraints: None.
// Effect: Accurately estimated values decide the stat collected for extreme blue and red.
//         For calibration of these two values, take full-view MCC chart under TL84 and A lighting.
//         Apply correct rolloff table and then measure the blue�s b/g from the MCC taken under TL84.
//         Measure the red�s r/g from the MCC taken under A.
//
// Variable names: extreme_range_perc_b, extreme_range_perc_r.
// Extreme blue and red threshold.
// Default value: 1.
// Data range: 0 to 10.
// Constraints: None.
// Effect: Higher values increase the boundary of collecting extreme red and blue stat.
//         Lower values reduce the boundary of collecting the extreme stat.
//
// Variable name: threshold_compact_cluster_grey.
// Threshold of distance from the outlier compact cluster to the grey zone.
// Default value: 20.
// Data range: 1 to 1000.
// Constraints: None.
// Effect: Lower value requires the distance from the outlier compact cluster to be closer to the grey zone; higher value
//         loosens this requirement by allowing a farther outlier compact cluster to be recognized as a compact cluster.
//
// Variable names: camera_preview_aggressiveness, camcorder_aggressiveness.
// Step size for temporal filter for camera preview and camcorder mode
// Applicable operation mode: camera preview and camcorder
// Default value: 0.1
// Data range: 0 to 1.
// Constraints: None.
// Effect: Slow down or speed up the awb temporal domain convergence.
//
// Variable name: blue_sky_pec.
// Percentage of the extreme blue stats.
// Default value: 0.20
// Data range: 0 to 1.
// Constraints: None.
// Effect: If the extreme blue stats exceed this percentage of all the collected stats, the blue sky prevention is to be conducted
//         to prevent purple sky. The smaller the percentage, the easier the purple sky prevention will be performed when AWB decision
//         is day light.
//
// Variable name: blue_sky_pec_buffer.
// Percentage of the extreme blue stats.
// Default value: 0.15
// Data range: 0 to awb2_blue_sky_pec.
// Constraints: None.
// Effect: This percentage is to set a buffer zone between doing the purple sky prevention and not doing it. The closer to awb2_blue_sky_pec,
//         the smaller the buffer zone is. The smaller it is than awb2_blue_sky_pec, the larger the buffer zone is.
//
// Variable name: slope_factor_m.
// The parameter to adjust the slope of the projection line from center of the green stats to the day light line.
// Default value: 1.5
// Data range:
// Constraints: None.
// Effect: The smaller the value, the smaller slope the projection line has. The resulted green scene images go towards the bluish green direction.
//         The larger the value, the larger slope the projection line has. The resulted green scene images go towards the yellowish green color direction.
/******************************************************************/


/*********************************************************************/
// Feature name :
//
// R/G ratio, B/G ratio: AWB referecne points used for auto WB calculation.
//
//Red Gain Adjust,Blue Gain Adjust: Additional gain applied for snapshot only.
/*********************************************************************/

   /* AWB Reference Points w/HW */
   {
      /* D65 AWB Reference Point */
      {
         0.477000f,   /* R/G ratio */
         0.715000f,   /* B/G ratio */
      },
      /* Shade AWB Reference Point */
      {
         0.442000f,   /* R/G ratio */
         0.759000f,   /* B/G ratio */
      },
      /* A AWB Reference Point */
      {
         0.766000f,   /* R/G ratio */
         0.386000f,   /* B/G ratio */
      },
      /* TL84 AWB Reference Point */
      {
         0.712000f,   /* R/G ratio */
         0.476000f,   /* B/G ratio */
      },
      /* CoolWhite AWB Reference Point */
      {
         0.614000f,   /* R/G ratio */
         0.422000f,   /* B/G ratio */
      },
      /* Horizon AWB Reference Point */
      {
         1.009000f,   /* R/G ratio */
         0.332000f,   /* B/G ratio */
      },
      /* D50 AWB Reference Point */
      {
         0.531000f,   /* R/G ratio */
         0.599000f,   /* B/G ratio */
      },
      /* Cust. Fluor. AWB Reference Point */
      {
         0.490000f,   /* R/G ratio */
         0.524000f,   /* B/G ratio */
      },
      /* Noon AWB Reference Point */
      {
         0.567000f,   /* R/G ratio */
         0.606000f,   /* B/G ratio */
      },
      /* Custom Daylight AWB Reference Point */
      {
         0.477000f,   /* R/G ratio */
         0.715000f,   /* B/G ratio */
      },
      /* Custom A AWB Reference Point */
      {
         0.766000f,   /* R/G ratio */
         0.386000f,   /* B/G ratio */
      },
      /* U30 AWB Reference Point */
      {
         0.766000f,   /* R/G ratio */
         0.386000f,   /* B/G ratio */
      },
   },
   /* LED Gain Adjust */
   {
      1.000000f, /* Red */
      1.000000f, /* Blue */
   },
   /* Strobe Gain Adjust */
   {
      1.000000f, /* Red */
      1.000000f, /* Blue */
   },
   /* AWB Gain Adjust */
   {
      /* D65 */
      {
         1.010000f, /* Red */
         0.960000f, /* Blue */
      },
      /* D75 */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* A */
      {
         0.960000f, /* Red */
         1.000000f, /* Blue */
      },
      /* TL84 */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* CW */
      {
         1.000000f, /* Red */
         0.980000f, /* Blue */
      },
      /* Horizon */
      {
         0.960000f, /* Red */
         1.000000f, /* Blue */
      },
      /* D50 */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* Cust Flo */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* Noon */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* Daylight */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* Cust A */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* U30 */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
   },
   /* AWB Lowlight Gain Adjust */
   {
      /* D65 */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* D75 */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* A */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* TL84 */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* CW */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* Horizon */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* D50 */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* Cust Flo */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* Noon */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* Daylight */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* Cust A */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
      /* U30 */
      {
         1.000000f, /* Red */
         1.000000f, /* Blue */
      },
   },

/*********************************************************************/
// Comment:
// Indoor and outdoor index are the parameters used in AWB algorithm in
// a variety of heuristics. We do not recommend the user change these values.
/*********************************************************************/

   240, /* Indoor Index */
   140, /* Outdoor Index */

/*********************************************************************/
// Feature name :
// Blue gain adj ratio is used for Snow and Beach best shot modes only. This factor
// is applied on top of the blue WB gain determined by AWB algorithm.
// Range: 0.7 to 1.5.
/*********************************************************************/

   1.100000f, /* Snow Blue Gain Adj Ratio */
   0.900000f, /* Beach Blue Gain Adj Ratio */

/*********************************************************************/
// Feature name :
// The following group of parameters are used by AWB algorithm. We do not
// recommend the user modify them.
/*********************************************************************/

   16, /* Outlier Distance */
   -10, /* Green Zone Offset RG */
   -10, /* Green Zone Offset BG */
   2, /* Num Frames to skip after changing VFE */

/*********************************************************************/
// Feature name :
// The final WB gain applied to the system is mandated to be between min
// and max WB values.  We do not recommend the user change the values.
/*********************************************************************/

   /* AWB Min Gains - RGB */
   {1.000000f, 1.000000f, 1.000000f},
   /* AWB Max Gains - RGB */
   {3.990000f, 3.990000f, 3.990000f},
   0, /* AWB Aggressiveness */
   0, /* AWB Self-Calibrate */

/******************************************************************************/
// Feature name : AWB self calibration
// variable name:
// Adjust amount of adjustment allowed for AWB self calibration
// applicale chipset(s): all MSM
// applicable operation mode: preview
// default value: high=1.15
// default value: low=0.9
// data range: high (1.0, 1.2), low (0.8, 1.0)
// constraints:
// effect: larger high = larger adjustment, smaller low = larger adjustment
/******************************************************************************/

   1.150000f, /* AWB Self-Calibrate */
   0.900000f, /* AWB Self-Calibrate Adjust Ratio Low */
   /* Purple Prevent */
   {

/******************************************************************************/
// Feature name : AWB Extended
// applicable chipset:  all VFEs.
// applicable operation mode: View finder and snapshot.
//
// variable name: AWB_purple_prevent_enable
// Enables the feature.
// default value: 1
// data range: 0 and 1
// constraints: None
//
// variable name: control_purple_prevent
// Control with gain or lux_index
// default Value: 0
// Data Range: 0 or 1.
// constraints: None
// effect: use gain or lux_index for control purple sky prevention
//
// variable name: purple_prevent_trigger
// Control the purple sky prevention adjustment trigger
// default Value: between  outdoor index and outdoor index
// Data Range: integers 0 to a few hundreds.
// constraints: only for bright outdoor
// effect: smaller index values make the purple sky prevention harder to take effect. (has to be very bright)
//
// variable name: purple_sky_prevention_bg_threshold
// Control the purple sky prevention adjustment
// default Value: BG ratio of D50
// Data Range: 0 to 2
// constraints: around D50
// effect: smaller index values make the adjustment larger.
/******************************************************************************/

      1, /* Enable */
      0, /* Control Method - 1 = Gain, 0 = Lux Index */
      /* Trigger Point */
      {
         2.000000f, /* Gain Start */
         1.000000f, /* Gain End */
         190, /* Lux Index Start */
         95, /* Lux Index End */
      },
      0.000000f, /* Sky Prevention BG Thresh */
   },
   0, /* Enable AWB Module Cal */
   /* AWB Motion Sensor */
   {

/******************************************************************************/
// Feature name : AWB_motion_sensor_type to aide AWB in determining a change in
//           scene.
// Applicable chipset: MSM7x30, QSD8x60, and newer chipsets.
// Applicable operation mode: Viewfinder and video.
//
// Variable name: awb_gyro_trigger.
// Used to control how scene change should be detected for AEC
// 3A version: 3.0.
// Default value: 0.0.
// Data range: -16000.0 to +16000.0.
// Constraints: None .
// Effect: The bigger the value is, the less sensitive AEC response to
//         gyro output value.
//
// Variable name: awb_accelerometer_trigger.
// Used to control how scene change should be detected for AEC.
// 3A version: 3.0.
// Default value: 0.0.
// Data range: -16000.0 to +16000.0.
// Constraints: None.
// Effect: The bigger the value is, the less sensitive AEC response to
//         accelerometer change.
//
// Variable name: awb_magnetometer_trigger.
// Used to control how scene change should be detected for AEC
// 3A version: 3.0.
// Default value: 0.0.
// Data range: 0.0 to 360.0.
// Constraints: None.
// Effect: The bigger the value is, the less sensitive AEC response to
//         magnetic field change.
//
// Variable name: awb_DIS_motion_vector_trigger.
// Used to control how scene change should be detected for AEC.
// 3A version: 3.0.
// Default value: 0.0.
// Data range: -16000.0 to +16000.0.
// Constraints: None.
// Effect: The bigger the value is, the less sensitive AEC response to
//         digital image stabilization movement/compensation value.
/******************************************************************************/

      0.000000f, /* Gyro Trigger */
      0.000000f, /* Accelerometer Trigger */
      0.000000f, /* Magnetometer Trigger */
      0.000000f, /* DIS Motion Vector Trigger */
   },
   0.000000f, /* LED/Strobe Adjustment Factor */
   0, /* Interpolate Gain Adj Enable */
   /* Lowlight LUT */
   {
      1, /* Enable */
      {
         /* Entry 0 */
         {
            232, /* Lux Index */
            0.000000f, /* Green RG Offset Adj */
            0.000000f, /* Green BG Offset Adj */
            0.000000f, /* Outlier Dist Adj */
         },
         /* Entry 1 */
         {
            262, /* Lux Index */
            -1.679850f, /* Green RG Offset Adj */
            -4.880369f, /* Green BG Offset Adj */
            5.161385f, /* Outlier Dist Adj */
         },
         /* Entry 2 */
         {
            287, /* Lux Index */
            -11.184973f, /* Green RG Offset Adj */
            -11.330027f, /* Green BG Offset Adj */
            15.920839f, /* Outlier Dist Adj */
         },
         /* Entry 3 */
         {
            316, /* Lux Index */
            -11.184973f, /* Green RG Offset Adj */
            -11.330027f, /* Green BG Offset Adj */
            15.920839f, /* Outlier Dist Adj */
         },
         /* Entry 4 */
         {
            344, /* Lux Index */
            -11.184973f, /* Green RG Offset Adj */
            -11.330027f, /* Green BG Offset Adj */
            15.920839f, /* Outlier Dist Adj */
         },
         /* Entry 5 */
         {
            357, /* Lux Index */
            -11.184973f, /* Green RG Offset Adj */
            -11.330027f, /* Green BG Offset Adj */
            15.920839f, /* Outlier Dist Adj */
         },
      },
   },

/******************************************************************************/
// Feature name : Match LED Level
// Applicale chipset: MSM8x30 and later.
// Applicable operation mode:  For video and snapshot.
//
// This is the feature to match dual LED flash with the ambient lighting.
//
// Desription of variables in chromatix_match_LED_lighting_table
// structure.
//
// Variable names: table_size, CCT_control[table_size-1].
// The three values for the table entries:
// The color temperature
// The LED1 current configuration for LED controller IC
// The LED2 current configuration for LED controller IC
/******************************************************************************/

   /* Mix LED Table */
   {
      0, /* Table Size */
      {
         /* Entry 0 */
         {
            0, /* CCT */
            0, /* LED1 Config */
            0, /* LED2 Config */
         },
         /* Entry 1 */
         {
            0, /* CCT */
            0, /* LED1 Config */
            0, /* LED2 Config */
         },
         /* Entry 2 */
         {
            0, /* CCT */
            0, /* LED1 Config */
            0, /* LED2 Config */
         },
         /* Entry 3 */
         {
            0, /* CCT */
            0, /* LED1 Config */
            0, /* LED2 Config */
         },
         /* Entry 4 */
         {
            0, /* CCT */
            0, /* LED1 Config */
            0, /* LED2 Config */
         },
         /* Entry 5 */
         {
            0, /* CCT */
            0, /* LED1 Config */
            0, /* LED2 Config */
         },
         /* Entry 6 */
         {
            0, /* CCT */
            0, /* LED1 Config */
            0, /* LED2 Config */
         },
         /* Entry 7 */
         {
            0, /* CCT */
            0, /* LED1 Config */
            0, /* LED2 Config */
         },
         /* Entry 8 */
         {
            0, /* CCT */
            0, /* LED1 Config */
            0, /* LED2 Config */
         },
         /* Entry 9 */
         {
            0, /* CCT */
            0, /* LED1 Config */
            0, /* LED2 Config */
         },
         /* Entry 10 */
         {
            0, /* CCT */
            0, /* LED1 Config */
            0, /* LED2 Config */
         },
         /* Entry 11 */
         {
            0, /* CCT */
            0, /* LED1 Config */
            0, /* LED2 Config */
         },
         /* Entry 12 */
         {
            0, /* CCT */
            0, /* LED1 Config */
            0, /* LED2 Config */
         },
         /* Entry 13 */
         {
            0, /* CCT */
            0, /* LED1 Config */
            0, /* LED2 Config */
         },
         /* Entry 14 */
         {
            0, /* CCT */
            0, /* LED1 Config */
            0, /* LED2 Config */
         },
         /* Entry 15 */
         {
            0, /* CCT */
            0, /* LED1 Config */
            0, /* LED2 Config */
         },
      },
   },
   6, /* Bright Green Percentage */
   12, /* Dark Green Percentage */
   5, /* Dark R Threshold */
   5, /* Dark G Threshold */
   5, /* Dark B Threshold */
   204, /* White Stat Y Threshold High */
   0.200000f, /* Threshold Extreme B Percent */
   0.500000f, /* Threshold Extreme R Percent */
   60, /* Threshold Compact Cluster */
   4, /* Compact To Grey DIS */
   4, /* Threshold Compact Cluster Valid */
   4, /* Dominant Cluster Threshold */
   /* Dist Weight Table */
   {
      1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1,
      1
   },
   30, /* Outdoor Adjustment */
   10, /* Exposure Adjustment */
   4.000000f, /* Outlier Valid yMax */
   0.400000f, /* Cluster High PEC */
   0.250000f, /* Cluster Mid PEC */
   0.150000f, /* Cluster Low PEC */
   /* Weight Vector */
   {
      {1, 10, 10, 5}, /* D65 */
      {1, 10, 10, 5}, /* D75 */
      {0, 0, 1, 8}, /* A */
      {0, 0, 5, 10}, /* Warm Fluorescent */
      {0, 0, 3, 10}, /* Cool Fluorescent */
      {0, 0, 1, 2}, /* Horizon */
      {10, 10, 1, 1}, /* D50 */
      {0, 0, 1, 8}, /* Custom Fluorescent */
      {10, 10, 1, 1}, /* Noon */
      {1, 1, 1, 1}, /* Custom Daylight */
      {0, 0, 1, 8}, /* Custom A */
      {0, 0, 1, 8}, /* U30 */
      {8, 9, 8, 3}, /* Daylight Hybrid 1 */
      {1, 5, 10, 5}, /* Daylight Hybrid 2 */
      {0, 0, 2, 3}, /* A Line 1 */
      {0, 0, 1, 2}, /* A Line 2 */
      {0, 0, 5, 10}, /* F Line */
   },
   1.039538f, /* Ref B BG Tl84 */
   2.134818f, /* Ref R RG A */
   1.250000f, /* Extreme Range Offset B */
   1.000000f, /* Extreme Range Offset R */
   20, /* Threshold Compact Cluster Grey */
   0.200000f, /* Blue Sky Percent */
   0.150000f, /* Blue Sky Percent Buffer */
   1.089775f, /* Slope Factor M */
   1.404646f, /* Extreme MCC Blue Threshold */
},
/* AEC */
{
   0, /* Software Type */
   1.100000f, /* CC Global Gain */

/*********************************************************************/
// Comments:
// Variable name: exp_table_flag
// This parameter is unused.
//
// Variable name: valid_entries
// Number of entries in the exposure table, not counting EV lowlight section.
//
// Variable name: aec_enable_digital_gain_for_EV_lowlight
// Indicates if extended exp table is used for EV lowlight case.
// Default: 1.
// Data range : 0 or 1.
//
// Variable name: total_entries_with_digital_gain_for_EV;
// The maximum exposure table size when EV lowlight in enabled.
// It needs to be in sync with the table contents.
//
// Variable name: exposure_entries
// Exposure table contains 2 columns. The first column is real gain values
//    right shifted 8 bits. For example, 256 means gain of 1.0. The 2nd colum
//    is sensor integration (exposure) time in terms of number of lines.
//    Exposure table is generated by Chromatix or sensor driver team.
//    It can be regenerated in Chromatix tool by specifying different max gain
//    and max line count.  We do not recommend user to manually modify it because it
//    potentially will change trigger points for many parameters.
/*********************************************************************/

   /* Exposure Table */
   {
      1, /* Use Digital Gain */
      /* Exposure Table */
      377, /* Max Exposure Table Entries When Digital Gain is Used for EV */
      0, /* Enable Digital Gain for EV Lowlight */
      377, /* Max Exposure Table Entries for Regular AEC */
      {
         {256, 1},   /* Gain= 1.000   Exposure Index=0   */
         {264, 1},   /* Gain= 1.031   Exposure Index=1   */
         {272, 1},   /* Gain= 1.063   Exposure Index=2   */
         {280, 1},   /* Gain= 1.094   Exposure Index=3   */
         {288, 1},   /* Gain= 1.125   Exposure Index=4   */
         {297, 1},   /* Gain= 1.160   Exposure Index=5   */
         {306, 1},   /* Gain= 1.195   Exposure Index=6   */
         {315, 1},   /* Gain= 1.230   Exposure Index=7   */
         {324, 1},   /* Gain= 1.266   Exposure Index=8   */
         {334, 1},   /* Gain= 1.305   Exposure Index=9   */
         {344, 1},   /* Gain= 1.344   Exposure Index=10   */
         {354, 1},   /* Gain= 1.383   Exposure Index=11   */
         {365, 1},   /* Gain= 1.426   Exposure Index=12   */
         {376, 1},   /* Gain= 1.469   Exposure Index=13   */
         {387, 1},   /* Gain= 1.512   Exposure Index=14   */
         {399, 1},   /* Gain= 1.559   Exposure Index=15   */
         {411, 1},   /* Gain= 1.605   Exposure Index=16   */
         {423, 1},   /* Gain= 1.652   Exposure Index=17   */
         {436, 1},   /* Gain= 1.703   Exposure Index=18   */
         {449, 1},   /* Gain= 1.754   Exposure Index=19   */
         {462, 1},   /* Gain= 1.805   Exposure Index=20   */
         {476, 1},   /* Gain= 1.859   Exposure Index=21   */
         {490, 1},   /* Gain= 1.914   Exposure Index=22   */
         {505, 1},   /* Gain= 1.973   Exposure Index=23   */
         {260, 2},   /* Gain= 1.016   Exposure Index=24   */
         {268, 2},   /* Gain= 1.047   Exposure Index=25   */
         {276, 2},   /* Gain= 1.078   Exposure Index=26   */
         {284, 2},   /* Gain= 1.109   Exposure Index=27   */
         {293, 2},   /* Gain= 1.145   Exposure Index=28   */
         {302, 2},   /* Gain= 1.180   Exposure Index=29   */
         {311, 2},   /* Gain= 1.215   Exposure Index=30   */
         {320, 2},   /* Gain= 1.250   Exposure Index=31   */
         {330, 2},   /* Gain= 1.289   Exposure Index=32   */
         {340, 2},   /* Gain= 1.328   Exposure Index=33   */
         {350, 2},   /* Gain= 1.367   Exposure Index=34   */
         {361, 2},   /* Gain= 1.410   Exposure Index=35   */
         {372, 2},   /* Gain= 1.453   Exposure Index=36   */
         {383, 2},   /* Gain= 1.496   Exposure Index=37   */
         {263, 3},   /* Gain= 1.027   Exposure Index=38   */
         {271, 3},   /* Gain= 1.059   Exposure Index=39   */
         {279, 3},   /* Gain= 1.090   Exposure Index=40   */
         {287, 3},   /* Gain= 1.121   Exposure Index=41   */
         {296, 3},   /* Gain= 1.156   Exposure Index=42   */
         {305, 3},   /* Gain= 1.191   Exposure Index=43   */
         {314, 3},   /* Gain= 1.227   Exposure Index=44   */
         {323, 3},   /* Gain= 1.262   Exposure Index=45   */
         {333, 3},   /* Gain= 1.301   Exposure Index=46   */
         {257, 4},   /* Gain= 1.004   Exposure Index=47   */
         {265, 4},   /* Gain= 1.035   Exposure Index=48   */
         {273, 4},   /* Gain= 1.066   Exposure Index=49   */
         {281, 4},   /* Gain= 1.098   Exposure Index=50   */
         {289, 4},   /* Gain= 1.129   Exposure Index=51   */
         {298, 4},   /* Gain= 1.164   Exposure Index=52   */
         {307, 4},   /* Gain= 1.199   Exposure Index=53   */
         {316, 4},   /* Gain= 1.234   Exposure Index=54   */
         {260, 5},   /* Gain= 1.016   Exposure Index=55   */
         {268, 5},   /* Gain= 1.047   Exposure Index=56   */
         {276, 5},   /* Gain= 1.078   Exposure Index=57   */
         {284, 5},   /* Gain= 1.109   Exposure Index=58   */
         {293, 5},   /* Gain= 1.145   Exposure Index=59   */
         {302, 5},   /* Gain= 1.180   Exposure Index=60   */
         {259, 6},   /* Gain= 1.012   Exposure Index=61   */
         {267, 6},   /* Gain= 1.043   Exposure Index=62   */
         {275, 6},   /* Gain= 1.074   Exposure Index=63   */
         {283, 6},   /* Gain= 1.105   Exposure Index=64   */
         {291, 6},   /* Gain= 1.137   Exposure Index=65   */
         {257, 7},   /* Gain= 1.004   Exposure Index=66   */
         {265, 7},   /* Gain= 1.035   Exposure Index=67   */
         {273, 7},   /* Gain= 1.066   Exposure Index=68   */
         {281, 7},   /* Gain= 1.098   Exposure Index=69   */
         {289, 7},   /* Gain= 1.129   Exposure Index=70   */
         {260, 8},   /* Gain= 1.016   Exposure Index=71   */
         {268, 8},   /* Gain= 1.047   Exposure Index=72   */
         {276, 8},   /* Gain= 1.078   Exposure Index=73   */
         {284, 8},   /* Gain= 1.109   Exposure Index=74   */
         {260, 9},   /* Gain= 1.016   Exposure Index=75   */
         {268, 9},   /* Gain= 1.047   Exposure Index=76   */
         {276, 9},   /* Gain= 1.078   Exposure Index=77   */
         {284, 9},   /* Gain= 1.109   Exposure Index=78   */
         {263, 10},   /* Gain= 1.027   Exposure Index=79   */
         {271, 10},   /* Gain= 1.059   Exposure Index=80   */
         {279, 10},   /* Gain= 1.090   Exposure Index=81   */
         {261, 11},   /* Gain= 1.020   Exposure Index=82   */
         {269, 11},   /* Gain= 1.051   Exposure Index=83   */
         {277, 11},   /* Gain= 1.082   Exposure Index=84   */
         {262, 12},   /* Gain= 1.023   Exposure Index=85   */
         {270, 12},   /* Gain= 1.055   Exposure Index=86   */
         {257, 13},   /* Gain= 1.004   Exposure Index=87   */
         {265, 13},   /* Gain= 1.035   Exposure Index=88   */
         {273, 13},   /* Gain= 1.066   Exposure Index=89   */
         {261, 14},   /* Gain= 1.020   Exposure Index=90   */
         {269, 14},   /* Gain= 1.051   Exposure Index=91   */
         {259, 15},   /* Gain= 1.012   Exposure Index=92   */
         {267, 15},   /* Gain= 1.043   Exposure Index=93   */
         {258, 16},   /* Gain= 1.008   Exposure Index=94   */
         {266, 16},   /* Gain= 1.039   Exposure Index=95   */
         {258, 17},   /* Gain= 1.008   Exposure Index=96   */
         {266, 17},   /* Gain= 1.039   Exposure Index=97   */
         {259, 18},   /* Gain= 1.012   Exposure Index=98   */
         {267, 18},   /* Gain= 1.043   Exposure Index=99   */
         {261, 19},   /* Gain= 1.020   Exposure Index=100   */
         {269, 19},   /* Gain= 1.051   Exposure Index=101   */
         {263, 20},   /* Gain= 1.027   Exposure Index=102   */
         {258, 21},   /* Gain= 1.008   Exposure Index=103   */
         {266, 21},   /* Gain= 1.039   Exposure Index=104   */
         {262, 22},   /* Gain= 1.023   Exposure Index=105   */
         {258, 23},   /* Gain= 1.008   Exposure Index=106   */
         {266, 23},   /* Gain= 1.039   Exposure Index=107   */
         {263, 24},   /* Gain= 1.027   Exposure Index=108   */
         {260, 25},   /* Gain= 1.016   Exposure Index=109   */
         {258, 26},   /* Gain= 1.008   Exposure Index=110   */
         {266, 26},   /* Gain= 1.039   Exposure Index=111   */
         {264, 27},   /* Gain= 1.031   Exposure Index=112   */
         {262, 28},   /* Gain= 1.023   Exposure Index=113   */
         {261, 29},   /* Gain= 1.020   Exposure Index=114   */
         {260, 30},   /* Gain= 1.016   Exposure Index=115   */
         {259, 31},   /* Gain= 1.012   Exposure Index=116   */
         {258, 32},   /* Gain= 1.008   Exposure Index=117   */
         {258, 33},   /* Gain= 1.008   Exposure Index=118   */
         {258, 34},   /* Gain= 1.008   Exposure Index=119   */
         {258, 35},   /* Gain= 1.008   Exposure Index=120   */
         {258, 36},   /* Gain= 1.008   Exposure Index=121   */
         {259, 37},   /* Gain= 1.012   Exposure Index=122   */
         {260, 38},   /* Gain= 1.016   Exposure Index=123   */
         {261, 39},   /* Gain= 1.020   Exposure Index=124   */
         {262, 40},   /* Gain= 1.023   Exposure Index=125   */
         {257, 42},   /* Gain= 1.004   Exposure Index=126   */
         {259, 43},   /* Gain= 1.012   Exposure Index=127   */
         {261, 44},   /* Gain= 1.020   Exposure Index=128   */
         {257, 46},   /* Gain= 1.004   Exposure Index=129   */
         {259, 47},   /* Gain= 1.012   Exposure Index=130   */
         {261, 48},   /* Gain= 1.020   Exposure Index=131   */
         {258, 50},   /* Gain= 1.008   Exposure Index=132   */
         {261, 51},   /* Gain= 1.020   Exposure Index=133   */
         {259, 53},   /* Gain= 1.012   Exposure Index=134   */
         {257, 55},   /* Gain= 1.004   Exposure Index=135   */
         {260, 56},   /* Gain= 1.016   Exposure Index=136   */
         {259, 58},   /* Gain= 1.012   Exposure Index=137   */
         {258, 60},   /* Gain= 1.008   Exposure Index=138   */
         {257, 62},   /* Gain= 1.004   Exposure Index=139   */
         {256, 64},   /* Gain= 1.000   Exposure Index=140   */
         {260, 65},   /* Gain= 1.016   Exposure Index=141   */
         {260, 67},   /* Gain= 1.016   Exposure Index=142   */
         {256, 70},   /* Gain= 1.000   Exposure Index=143   */
         {256, 72},   /* Gain= 1.000   Exposure Index=144   */
         {257, 74},   /* Gain= 1.004   Exposure Index=145   */
         {258, 76},   /* Gain= 1.008   Exposure Index=146   */
         {259, 78},   /* Gain= 1.012   Exposure Index=147   */
         {257, 81},   /* Gain= 1.004   Exposure Index=148   */
         {258, 83},   /* Gain= 1.008   Exposure Index=149   */
         {256, 86},   /* Gain= 1.000   Exposure Index=150   */
         {258, 88},   /* Gain= 1.008   Exposure Index=151   */
         {257, 91},   /* Gain= 1.004   Exposure Index=152   */
         {256, 94},   /* Gain= 1.000   Exposure Index=153   */
         {258, 96},   /* Gain= 1.008   Exposure Index=154   */
         {258, 99},   /* Gain= 1.008   Exposure Index=155   */
         {258, 102},   /* Gain= 1.008   Exposure Index=156   */
         {258, 105},   /* Gain= 1.008   Exposure Index=157   */
         {258, 108},   /* Gain= 1.008   Exposure Index=158   */
         {256, 112},   /* Gain= 1.000   Exposure Index=159   */
         {257, 115},   /* Gain= 1.004   Exposure Index=160   */
         {258, 118},   /* Gain= 1.008   Exposure Index=161   */
         {257, 122},   /* Gain= 1.004   Exposure Index=162   */
         {256, 126},   /* Gain= 1.000   Exposure Index=163   */
         {258, 129},   /* Gain= 1.008   Exposure Index=164   */
         {258, 133},   /* Gain= 1.008   Exposure Index=165   */
         {256, 138},   /* Gain= 1.000   Exposure Index=166   */
         {256, 142},   /* Gain= 1.000   Exposure Index=167   */
         {256, 146},   /* Gain= 1.000   Exposure Index=168   */
         {257, 150},   /* Gain= 1.004   Exposure Index=169   */
         {256, 155},   /* Gain= 1.000   Exposure Index=170   */
         {257, 159},   /* Gain= 1.004   Exposure Index=171   */
         {257, 164},   /* Gain= 1.004   Exposure Index=172   */
         {257, 169},   /* Gain= 1.004   Exposure Index=173   */
         {257, 174},   /* Gain= 1.004   Exposure Index=174   */
         {257, 179},   /* Gain= 1.004   Exposure Index=175   */
         {256, 185},   /* Gain= 1.000   Exposure Index=176   */
         {257, 190},   /* Gain= 1.004   Exposure Index=177   */
         {257, 196},   /* Gain= 1.004   Exposure Index=178   */
         {257, 202},   /* Gain= 1.004   Exposure Index=179   */
         {257, 208},   /* Gain= 1.004   Exposure Index=180   */
         {256, 215},   /* Gain= 1.000   Exposure Index=181   */
         {257, 221},   /* Gain= 1.004   Exposure Index=182   */
         {257, 228},   /* Gain= 1.004   Exposure Index=183   */
         {257, 235},   /* Gain= 1.004   Exposure Index=184   */
         {257, 242},   /* Gain= 1.004   Exposure Index=185   */
         {256, 250},   /* Gain= 1.000   Exposure Index=186   */
         {256, 257},   /* Gain= 1.000   Exposure Index=187   */
         {257, 264},   /* Gain= 1.004   Exposure Index=188   */
         {257, 272},   /* Gain= 1.004   Exposure Index=189   */
         {256, 281},   /* Gain= 1.000   Exposure Index=190   */
         {256, 289},   /* Gain= 1.000   Exposure Index=191   */
         {257, 297},   /* Gain= 1.004   Exposure Index=192   */
         {256, 307},   /* Gain= 1.000   Exposure Index=193   */
         {256, 316},   /* Gain= 1.000   Exposure Index=194   */
         {256, 325},   /* Gain= 1.000   Exposure Index=195   */
         {257, 334},   /* Gain= 1.004   Exposure Index=196   */
         {256, 345},   /* Gain= 1.000   Exposure Index=197   */
         {256, 355},   /* Gain= 1.000   Exposure Index=198   */
         {256, 365},   /* Gain= 1.000   Exposure Index=199   */
         {257, 375},   /* Gain= 1.004   Exposure Index=200   */
         {257, 387},   /* Gain= 1.004   Exposure Index=201   */
         {256, 400},   /* Gain= 1.000   Exposure Index=202   */
         {256, 412},   /* Gain= 1.000   Exposure Index=203   */
         {256, 424},   /* Gain= 1.000   Exposure Index=204   */
         {256, 436},   /* Gain= 1.000   Exposure Index=205   */
         {256, 449},   /* Gain= 1.000   Exposure Index=206   */
         {256, 462},   /* Gain= 1.000   Exposure Index=207   */
         {256, 475},   /* Gain= 1.000   Exposure Index=208   */
         {256, 489},   /* Gain= 1.000   Exposure Index=209   */
         {258, 500},   /* Gain= 1.008   Exposure Index=210   */
         {266, 500},   /* Gain= 1.039   Exposure Index=211   */
         {274, 500},   /* Gain= 1.070   Exposure Index=212   */
         {282, 500},   /* Gain= 1.102   Exposure Index=213   */
         {290, 500},   /* Gain= 1.133   Exposure Index=214   */
         {299, 500},   /* Gain= 1.168   Exposure Index=215   */
         {308, 500},   /* Gain= 1.203   Exposure Index=216   */
         {317, 500},   /* Gain= 1.238   Exposure Index=217   */
         {327, 500},   /* Gain= 1.277   Exposure Index=218   */
         {337, 500},   /* Gain= 1.316   Exposure Index=219   */
         {347, 500},   /* Gain= 1.355   Exposure Index=220   */
         {357, 500},   /* Gain= 1.395   Exposure Index=221   */
         {368, 500},   /* Gain= 1.438   Exposure Index=222   */
         {379, 500},   /* Gain= 1.480   Exposure Index=223   */
         {390, 500},   /* Gain= 1.523   Exposure Index=224   */
         {402, 500},   /* Gain= 1.570   Exposure Index=225   */
         {414, 500},   /* Gain= 1.617   Exposure Index=226   */
         {426, 500},   /* Gain= 1.664   Exposure Index=227   */
         {439, 500},   /* Gain= 1.715   Exposure Index=228   */
         {452, 500},   /* Gain= 1.766   Exposure Index=229   */
         {466, 500},   /* Gain= 1.820   Exposure Index=230   */
         {480, 500},   /* Gain= 1.875   Exposure Index=231   */
         {494, 500},   /* Gain= 1.930   Exposure Index=232   */
         {509, 500},   /* Gain= 1.988   Exposure Index=233   */
         {524, 500},   /* Gain= 2.047   Exposure Index=234   */
         {540, 500},   /* Gain= 2.109   Exposure Index=235   */
         {556, 500},   /* Gain= 2.172   Exposure Index=236   */
         {573, 500},   /* Gain= 2.238   Exposure Index=237   */
         {590, 500},   /* Gain= 2.305   Exposure Index=238   */
         {608, 500},   /* Gain= 2.375   Exposure Index=239   */
         {626, 500},   /* Gain= 2.445   Exposure Index=240   */
         {645, 500},   /* Gain= 2.520   Exposure Index=241   */
         {664, 500},   /* Gain= 2.594   Exposure Index=242   */
         {684, 500},   /* Gain= 2.672   Exposure Index=243   */
         {705, 500},   /* Gain= 2.754   Exposure Index=244   */
         {726, 500},   /* Gain= 2.836   Exposure Index=245   */
         {748, 500},   /* Gain= 2.922   Exposure Index=246   */
         {770, 500},   /* Gain= 3.008   Exposure Index=247   */
         {793, 500},   /* Gain= 3.098   Exposure Index=248   */
         {817, 500},   /* Gain= 3.191   Exposure Index=249   */
         {842, 500},   /* Gain= 3.289   Exposure Index=250   */
         {867, 500},   /* Gain= 3.387   Exposure Index=251   */
         {893, 500},   /* Gain= 3.488   Exposure Index=252   */
         {920, 500},   /* Gain= 3.594   Exposure Index=253   */
         {948, 500},   /* Gain= 3.703   Exposure Index=254   */
         {976, 500},   /* Gain= 3.813   Exposure Index=255   */
         {1005, 500},   /* Gain= 3.926   Exposure Index=256   */
         {1035, 500},   /* Gain= 4.043   Exposure Index=257   */
         {1066, 500},   /* Gain= 4.164   Exposure Index=258   */
         {1098, 500},   /* Gain= 4.289   Exposure Index=259   */
         {1131, 500},   /* Gain= 4.418   Exposure Index=260   */
         {1165, 500},   /* Gain= 4.551   Exposure Index=261   */
         {1200, 500},   /* Gain= 4.688   Exposure Index=262   */
         {1236, 500},   /* Gain= 4.828   Exposure Index=263   */
         {1273, 500},   /* Gain= 4.973   Exposure Index=264   */
         {1311, 500},   /* Gain= 5.121   Exposure Index=265   */
         {1350, 500},   /* Gain= 5.273   Exposure Index=266   */
         {1391, 500},   /* Gain= 5.434   Exposure Index=267   */
         {1433, 500},   /* Gain= 5.598   Exposure Index=268   */
         {1476, 500},   /* Gain= 5.766   Exposure Index=269   */
         {1520, 500},   /* Gain= 5.938   Exposure Index=270   */
         {1566, 500},   /* Gain= 6.117   Exposure Index=271   */
         {1613, 500},   /* Gain= 6.301   Exposure Index=272   */
         {1661, 500},   /* Gain= 6.488   Exposure Index=273   */
         {1711, 500},   /* Gain= 6.684   Exposure Index=274   */
         {1762, 500},   /* Gain= 6.883   Exposure Index=275   */
         {1815, 500},   /* Gain= 7.090   Exposure Index=276   */
         {1869, 500},   /* Gain= 7.301   Exposure Index=277   */
         {1925, 500},   /* Gain= 7.520   Exposure Index=278   */
         {1983, 500},   /* Gain= 7.746   Exposure Index=279   */
         {2042, 500},   /* Gain= 7.977   Exposure Index=280   */
         {2048, 500},   /* Gain= 8.000   Exposure Index=281   */
         {2048, 515},   /* Gain= 8.000   Exposure Index=282   */
         {2048, 530},   /* Gain= 8.000   Exposure Index=283   */
         {2048, 545},   /* Gain= 8.000   Exposure Index=284   */
         {2048, 561},   /* Gain= 8.000   Exposure Index=285   */
         {2048, 577},   /* Gain= 8.000   Exposure Index=286   */
         {2048, 594},   /* Gain= 8.000   Exposure Index=287   */
         {2048, 611},   /* Gain= 8.000   Exposure Index=288   */
         {2048, 629},   /* Gain= 8.000   Exposure Index=289   */
         {2048, 647},   /* Gain= 8.000   Exposure Index=290   */
         {2048, 666},   /* Gain= 8.000   Exposure Index=291   */
         {2048, 685},   /* Gain= 8.000   Exposure Index=292   */
         {2048, 705},   /* Gain= 8.000   Exposure Index=293   */
         {2048, 726},   /* Gain= 8.000   Exposure Index=294   */
         {2048, 747},   /* Gain= 8.000   Exposure Index=295   */
         {2048, 769},   /* Gain= 8.000   Exposure Index=296   */
         {2048, 792},   /* Gain= 8.000   Exposure Index=297   */
         {2048, 815},   /* Gain= 8.000   Exposure Index=298   */
         {2048, 839},   /* Gain= 8.000   Exposure Index=299   */
         {2048, 864},   /* Gain= 8.000   Exposure Index=300   */
         {2048, 889},   /* Gain= 8.000   Exposure Index=301   */
         {2048, 915},   /* Gain= 8.000   Exposure Index=302   */
         {2048, 942},   /* Gain= 8.000   Exposure Index=303   */
         {2048, 970},   /* Gain= 8.000   Exposure Index=304   */
         {2048, 999},   /* Gain= 8.000   Exposure Index=305   */
         {2048, 1028},   /* Gain= 8.000   Exposure Index=306   */
         {2048, 1058},   /* Gain= 8.000   Exposure Index=307   */
         {2048, 1089},   /* Gain= 8.000   Exposure Index=308   */
         {2048, 1121},   /* Gain= 8.000   Exposure Index=309   */
         {2048, 1154},   /* Gain= 8.000   Exposure Index=310   */
         {2048, 1188},   /* Gain= 8.000   Exposure Index=311   */
         {2048, 1223},   /* Gain= 8.000   Exposure Index=312   */
         {2048, 1259},   /* Gain= 8.000   Exposure Index=313   */
         {2048, 1296},   /* Gain= 8.000   Exposure Index=314   */
         {2048, 1334},   /* Gain= 8.000   Exposure Index=315   */
         {2048, 1374},   /* Gain= 8.000   Exposure Index=316   */
         {2048, 1415},   /* Gain= 8.000   Exposure Index=317   */
         {2048, 1457},   /* Gain= 8.000   Exposure Index=318   */
         {2048, 1500},   /* Gain= 8.000   Exposure Index=319   */
         {2048, 1545},   /* Gain= 8.000   Exposure Index=320   */
         {2048, 1591},   /* Gain= 8.000   Exposure Index=321   */
         {2048, 1638},   /* Gain= 8.000   Exposure Index=322   */
         {2048, 1687},   /* Gain= 8.000   Exposure Index=323   */
         {2048, 1737},   /* Gain= 8.000   Exposure Index=324   */
         {2048, 1789},   /* Gain= 8.000   Exposure Index=325   */
         {2048, 1842},   /* Gain= 8.000   Exposure Index=326   */
         {2048, 1897},   /* Gain= 8.000   Exposure Index=327   */
         {2048, 1953},   /* Gain= 8.000   Exposure Index=328   */
         {2048, 2011},   /* Gain= 8.000   Exposure Index=329   */
         {2048, 2071},   /* Gain= 8.000   Exposure Index=330   */
         {2048, 2133},   /* Gain= 8.000   Exposure Index=331   */
         {2048, 2196},   /* Gain= 8.000   Exposure Index=332   */
         {2048, 2261},   /* Gain= 8.000   Exposure Index=333   */
         {2048, 2328},   /* Gain= 8.000   Exposure Index=334   */
         {2048, 2397},   /* Gain= 8.000   Exposure Index=335   */
         {2048, 2468},   /* Gain= 8.000   Exposure Index=336   */
         {2048, 2542},   /* Gain= 8.000   Exposure Index=337   */
         {2048, 2618},   /* Gain= 8.000   Exposure Index=338   */
         {2048, 2696},   /* Gain= 8.000   Exposure Index=339   */
         {2048, 2776},   /* Gain= 8.000   Exposure Index=340   */
         {2048, 2859},   /* Gain= 8.000   Exposure Index=341   */
         {2048, 2944},   /* Gain= 8.000   Exposure Index=342   */
         {2048, 3032},   /* Gain= 8.000   Exposure Index=343   */
         {2048, 3122},   /* Gain= 8.000   Exposure Index=344   */
         {2048, 3215},   /* Gain= 8.000   Exposure Index=345   */
         {2048, 3311},   /* Gain= 8.000   Exposure Index=346   */
         {2048, 3410},   /* Gain= 8.000   Exposure Index=347   */
         {2048, 3512},   /* Gain= 8.000   Exposure Index=348   */
         {2048, 3617},   /* Gain= 8.000   Exposure Index=349   */
         {2048, 3725},   /* Gain= 8.000   Exposure Index=350   */
         {2048, 3836},   /* Gain= 8.000   Exposure Index=351   */
         {2048, 3951},   /* Gain= 8.000   Exposure Index=352   */
         {2048, 4069},   /* Gain= 8.000   Exposure Index=353   */
         {2048, 4191},   /* Gain= 8.000   Exposure Index=354   */
         {2048, 4316},   /* Gain= 8.000   Exposure Index=355   */
         {2048, 4445},   /* Gain= 8.000   Exposure Index=356   */
         {2048, 4578},   /* Gain= 8.000   Exposure Index=357   */
         {2048, 4715},   /* Gain= 8.000   Exposure Index=358   */
         {2048, 4856},   /* Gain= 8.000   Exposure Index=359   */
         {2048, 5001},   /* Gain= 8.000   Exposure Index=360   */
         {2048, 5151},   /* Gain= 8.000   Exposure Index=361   */
         {2048, 5305},   /* Gain= 8.000   Exposure Index=362   */
         {2048, 5464},   /* Gain= 8.000   Exposure Index=363   */
         {2048, 5627},   /* Gain= 8.000   Exposure Index=364   */
         {2048, 5795},   /* Gain= 8.000   Exposure Index=365   */
         {2048, 5968},   /* Gain= 8.000   Exposure Index=366   */
         {2048, 6147},   /* Gain= 8.000   Exposure Index=367   */
         {2048, 6331},   /* Gain= 8.000   Exposure Index=368   */
         {2048, 6520},   /* Gain= 8.000   Exposure Index=369   */
         {2048, 6715},   /* Gain= 8.000   Exposure Index=370   */
         {2048, 6916},   /* Gain= 8.000   Exposure Index=371   */
         {2048, 7123},   /* Gain= 8.000   Exposure Index=372   */
         {2048, 7336},   /* Gain= 8.000   Exposure Index=373   */
         {2048, 7556},   /* Gain= 8.000   Exposure Index=374   */
         {2048, 7782},   /* Gain= 8.000   Exposure Index=375   */
         {2048, 8015},   /* Gain= 8.000   Exposure Index=376   */
      },
   },

/******************************************************************************/
// Feature name : AEC Snapshot LUT
// applicale chipset(s):All MSM
// applicable operation mode: Snapshot
//
// variable name: enable
// Allows snapshot to maximize exposure time used when luma target
//  cannot be reached.
// default value: 0
// data range: 0 or 1
// constraints: LUT needs to be entered or wrong snapshot brightness may ocurr.
// effect: Allows snapshot gains and exposure times to be modified by a
//  snapshot_ae_table LUT.
//
// variable name: exposure_stretch_enable
// default value: 0
// data range: 0 and 1
// constraints: None
// effect: Allowing auto stretch will cause snapshot to be brighter than preview
//  when preview does not reach luma target.
//
// variable name: valid_entries
// Number of entries used in ae_table LUT.
// default value: 2
// data range: 2 to 10
// constraints: None
// effect: Higher values allow more entries in LUT.
//
// variable name: snapshot_ae_table
// Each entry contains a triplet of settings:
//  lux_index, gain_trade_off, max_exp_time
// default value: {0, 1/2, 0.200}, {1000, 1/2, 0.200}
// data range: lux_index --> 0 to 1000
//             gain_trade_off --> 1 to .1 (1 means keep preview gain, .1 means reduce gain 10 times)
//             max_exp_time --> 1 (up to number of seconds allowed of exposure)
// constraints: None
// effect: By setting this LUT, at specified lux_idx the gain tradeoff and exposure
//  caps will be used.  At lux_idx between entries, gain trade-offs and exposure
//  caps will be linearly interpolated.
/******************************************************************************/

   /* AEC Snapshot Exposure */
   {
      0, /* Enable */
      0, /* Stretch Enable */
      2, /* Valid Entries */
      /* Snapshot Table */
      {
         /* 0 */
         {
            0,
            0.500000f,
            0.200000f
         },
         /* 1 */
         {
            1000,
            0.500000f,
            0.200000f
         },
         /* 2 */
         {
            0,
            0.000000f,
            0.000000f
         },
         /* 3 */
         {
            0,
            0.000000f,
            0.000000f
         },
         /* 4 */
         {
            0,
            0.000000f,
            0.000000f
         },
         /* 5 */
         {
            0,
            0.000000f,
            0.000000f
         },
         /* 6 */
         {
            0,
            0.000000f,
            0.000000f
         },
         /* 7 */
         {
            0,
            0.000000f,
            0.000000f
         },
         /* 8 */
         {
            0,
            0.000000f,
            0.000000f
         },
         /* 9 */
         {
            0,
            0.000000f,
            0.000000f
         },
      },
   },

/*********************************************************************/
// Feature name :
// Luma target is used for AEC. These values are the Y value before gamma
// in the linear domain, it includes the result from sensor exposure,
// analog gain, and digital gain.
// Range: 20 to 100.
// Effect: Larger value results in brighter images.
//
/*********************************************************************/

   56, /* Default Luma Target */
   56, /* Outdoor Luma Target */

/*********************************************************************/
// Feature name :
// Luma tolerance is used in AEC.
// Range: 2 to 8.
// Effect: Larger value results in stable and fast AEC convergence but
//           the picture brightness is not consistent.
//
/*********************************************************************/

   2, /* Luma Tolerance */

/*********************************************************************/
// Feature name :
// Exposure index adj step is tied to exposure table. It is 1/(log(step size)).
// 77.9 corresponds to 3% exposure step size.
// We do not recommend the user change this value unless exposure table step size is changed.
/*********************************************************************/

   77.900002f, /* Exposure Index Adj Step */

/*********************************************************************/
// Feature name :
// ISO 100 gain is calibrated by Chromatix tool.
/*********************************************************************/

   1.000000f, /* ISO 100 Gain */

/*********************************************************************/
// Feature name :
// AEC indoor index and outdoor index are used in some dynamic EV related
// features. We recommand not to modify these values.
/*********************************************************************/

   210, /* AEC Indoor Index */
   110, /* AEC Outdoor Index */
   
/*********************************************************************/
// Feature name :
// Max exposure time allowed is defined in seconds. It is used
// for lowlight.
// Effect: Larger value will result in lower noise image but with more blur.
/*********************************************************************/

   0.500000f, /* Max Snapshot Exposure Time Allowed */

/*********************************************************************/
// Feature name :
// AEC aggresiveness determines AEC convergence speed.
// Range: 0 to 1.
// Effect: Higher value results in faster convergence.
/*********************************************************************/

   0.800000f, /* Aggressiveness */

/*********************************************************************/
// Feature name :
// For linear AFR case, Fix FPS AEC Table Index is the last index
// in the exposure table before the frame rate is changed. User should not manually
// change this value, it is determine by Chromatix tool based on exposure table.
// This parameter is not used for non linear AFR case.
/*********************************************************************/

   281, /* Fix FPS AEC Table Index */
   
/*********************************************************************/
// Feature name :
// High luma region threshold is used for indoor snapshot only as part of dynamic
// EV feature.
// Range: 80 to 255.
// Effect: Lower value tends to avoid over exposure areas for indoor snapshot
//           pictures.  Setting to 255 will remove the effect of this feature.
/*********************************************************************/

   255, /* High Luma Region Threshold */

/******************************************************************************/
// Feature name : AEC bright_region
// Feature name : Bright region discrimination.
//  This is a dynamic EV feature for OUTDOOR only, it will increase luma target
//  when there are a large amount very bright areas in the pictures.
// applicale chipset(s): All MSM
// applicable operation mode: Preview and snapshot
//
// variable name: is_supported
// Enables bright region feture.
// default value: 0
// data range: 0 or 1
// constraints: None
// effect: Enables feature.
//
// variable name: reduction
// How bright regions influence will be reduced.
// default value: 0.5
// data range: 0 to 1
// constraints: None
// effect: 1 means bright region will not influence luma calculation. 0 completely
//  discards bright region from luma calculation.
//
// variable name: threshold_LO
// Threshold to compare AEC stats regions when lux_idx is at lux_index_LO.
// default value (calculated): 4 * Default Luma Target
// data range: 0 to 256
// constraints: Must be higher than threshold_HI
// effect: 0 detects all regions as bright, 256 detects none, disable feature.
//  Tends to make image brighter at presence of bright areas.
//
// variable name: lux_index_LO
// Trigger point to calculate thershold used for bright region feature.
//  Pairs with threshold_LO.
// default value (calculated):  AEC outdoor index - 25
// data range: 0 to Max exp table index
// constraints: Higher value than lux_index_HI
// effect: Determines when bright region feature starts to get used.
//
// variable name:threshold_HI
// Threshold to compare AEC stats regions when lux_idx is at lux_index_HI.
// default value (calculated): 2.5 * Default Luma Target
// data range: 0 to 256
// constraints: Lower value than lux_index_LO
// effect: Determines in outdoor type scenes when a region is considered very bright
//  so it can be discarded from luma calculation.
//
// variable name: lux_index_HI
// Trigger point to calculate thershold used for bright region feature.
//  Pairs with threshold_HI.
// default value (calculated): AEC Outdoor Index/2
// data range: 0 to Max exp table index
// constraints: Smaller value than lux_index_LO
// effect: Determines when bright region feature max effect takes place.
//
// variable name: discard_ratio
// Percent of regions' biases that may be modified by bright region.
// default value: 0.5
// data range: 0 to 0.5
// constraints: 0 disbles feature.  Algorithm caps at 0.5,
// effect: 0 disables feature, higher value allowes more regions to get discarded
//  from luma calculation.
/******************************************************************************/

   /* AEC Bright Region */
   {
      0, /* Is Supported  */
      0.500000f, /* Reduction */
      200, /* Threshold Low */
      85, /* Lux Index Low */
      125, /* Threshold High */
      55, /* Lux Index High */
      0.500000f, /* Discard Ratio */
   },

/******************************************************************************/
// Feature name : AEC dark_region
// Feature name : Dark region discrimination .
//  This is a dynamic EV feature for indoor and outdoor, it will decrease luma target when there
//  are a large amount very dark areas in the pictures. It applies to both viewfinder and snapshot.
// applicale chipset(s):All MSM
// applicable operation mode: Preview and snapshot
//
// variable name: is_supported
// Enables feature.
// default value: 0
// data range: 0 and 1
// constraints: none
// effect: Detects regions that are dark and reduces their effect on luma
//  calculation.
//
// variable name: threshold_LO
// Any region below this brightness
//  value will be not used for luma calculation.
// default value: 0.1
// data range: 0 to 0.1
// constraints: None
// effect: Lower Value reduces impact of feature. Tend to make image darker
//  in presence of dark and bright objects in the scene.
//
// variable name:threshold_HI
// Any region above this brightness
//  value will be not used for luma calculation.
// default value: 0.5
// data range: 0 to 0.8
// constraints: None
// effect: Higher value increases effect of dark region feature. Tend to make
//  image darker in presence of dark and bright objects in the scene.
//
// variable name: discard_ratio
// Percent of regions' biases that may be modified by bright region.
// default value: 0.5
// data range: 0 to 0.5
// constraints: None
// effect: 0 disables the feature.
/******************************************************************************/

   /* AEC Dark Region */
   {
      0, /* Is Supported  */
      0.100000f, /* Threshold Low */
      0.500000f, /* Threshold Hi */
      0.500000f, /* Discard Ratio */
   },

/******************************************************************************/
// Feature name : AEC LED
// variable name: wled_trigger_idx
// Lux index when LED strobe will start to
//  be used.  Anytime lux-idx is higher than this, it will flag for LED usage.
// applicale chipset(s): All MSM
// applicable operation mode: Preview and snapshot.
// default value (calculated) : Max Exposure Table Index-1
// data range: 0 to max lux_idx
// constraints: None
// effect: 0 will always make LED strobe to be used. Larger value requires scene
//  to be darker to LED to be used.
/******************************************************************************/

   375, /* wLED Trigger Index */

/******************************************************************************/
// Feature name : AEC LED
// variable name: aec_led_preview_flux
// Amount of light flux emitted by LED in preview.
// applicale chipset(s): All MSM
// applicable operation mode: Preview
// default value: 1
// data range: Any positive number
// constraints: None
// effect: Ratio between aec_led_preview_flux and aec_led_snapshot_flux determines
//  AEC compensation to be used.
/******************************************************************************/

   1.000000f, /* AEC LED Preview Flux */

/******************************************************************************/
// Feature name : AEC LED
// applicale chipset(s):All
// applicable operation mode:Snapshot
//
// variable name: aec_led_snapshot_flux_hi
// Sets LED flux output at highest current
//  mode.  LED power to be used is determined by available power on battery
//  for this feature, which is customizable by OEM.
// default value: 4.0
// data range: 1.0 to 1000
// constraints: Positive number
// effect: Higher values means LED outputs more lumen.  If brighter image is
//  needed, make this value smaller, for darker image make value higher.
//
// variable name: aec_led_snapshot_flux_med
// Sets LED flux output at medium current
//  mode. LED power to be used is determined by available power on battery
//  for this feature, which is customizable by OEM.
// default value: 1.0
// data range: 1.0 to 1000
// constraints: Positive number
// effect: Higher values means LED outputs more lumen.  If brighter image is
//  needed, make this value smaller, for darker image make value higher.
//
// variable name: aec_led_snapshot_flux_low
// Sets LED flux output at low current
//  mode. LED power to be used is determined by available power on battery
//  for this feature, which is customizable by OEM.
// default value: 1.0
// data range: 1.0 to 1000
// constraints: Positive number
// effect: Higher values means LED outputs more lumen.  If brighter image is
//  needed, make this value smaller, for darker image make value higher.
/******************************************************************************/

   4.000000f, /* AEC LED Snapshot Flux Hi */
   1.000000f, /* AEC LED Snapshot Flux Med */
   1.000000f, /* AEC LED Snapshot Flux Low */

/******************************************************************************/
// Feature name : AEC Motion ISO
// applicale chipset(s):All MSM
// applicable operation mode: snapshot, preview, and video
// (Defaults are same for all 3 modes)
//
// variable name: motion_iso_enable
// motion_iso_enable
// default value: 0
// data range: 0 or 1
// constraints: None
// effect: Enables motion ISO feature. while scenes are changing or moving,
//  higher AE gains are used in efforts to reduce motion blur.
//
// variable name: motion_iso_aggressiveness
// Determines how fast motion effect is applied
//  to preview and snapshot.  Higher values cause gains to react rapidly upon any
//  motion detection.
// default value: 0.5
// data range: 0.01 to 1
// constraints: None
// effect: Lower value makes motion to take longer to affect gains and exposure
//  times and also longer to dissipate.
//
// variable name: motion_iso_threshold
// Motion metric caclulated by algorithm
// is compared to this threshold, if higher thant motion ISO is applied.
// default value: 40
// data range: Any positive value.
// constraints: Depending on sensor noise, this threshold needs to be adjusted
//   to make sure sensor noise is not triggering motion iso.  Value also needs
//   be adjusted based on 256 or 64 AE stats region mode used.
// effect: Lower value trigger motion ISO sooner.  Higher value requires
//  more scene motion to trigger feature.
//
// variable name:motion_iso_max_gain
// Max gain allowed to be used when motion ISO feature is triggered.
// default value (calculated):  2 *  Max Exposure Table Gain.
// data range: max AEC table gain to max gain supported by system.
// constraints: If this value is set to default normal mode max gain, motion
//  ISO will have no effect in low light.
// effect: Higher gains allow more Motion ISO effect for low light scenes.
//  Expect higher noise due to high gains used.
/******************************************************************************/

   /* Motion ISO */
   {
      0, /* Enable */
      0.500000f, /* Aggressiveness */
      40.000000f, /* Threshold */
      16.000000f, /* Max Gain */
   },

/******************************************************************************/
// Feature name : camcorder aec convergence
// variable name: aec_holding_time_adj
// Adjust camcorder aec convergence.
// applicale chipset(s): all MSM
// applicable operation mode: camcorder preview/recording
// default value: 0
// data range: -10 to 10
// constraints: none
// effect: larger value, longer holding time. Negative number, shorter holding time
/******************************************************************************/

   0, /* Convergence Holding Time Adjust */

/*********************************************************************/
// Feature name :
// The following framerate information should reflect the sensor driver setting.
// They should be in sync with the sensor driver capability. Forcefully
// changing their values will NOT actually change the frame, instead it may
// cause issues with internal alogirhms that use this information as input.
/*********************************************************************/

   30.000000f, /* Max Video FPS */

/******************************************************************************/
// variable name: max_sensitivity_lux_index
// Max lux_index when luma target is able to be reached.
// applicable chipset:  all chipsets
// 3A version: N/A
// applicable operation mode: preview and snapshot
// default Value (calculated) : Max Exposure Table Index
// Data Range: 0 to 1000
// constraints: none
// effect: we do not set this value, it is a value determined by exp table
//         and supported FPS.
// Other info: Currently linear AFR case is used. For non-linear AFR case, default is
//                max_exp_index + (Num_FPS-1)*(max_FPS/min_FPS)*23
/******************************************************************************/

   376, /* Max Sensitivity Lux Index */

/******************************************************************************/
// variable name: AEC_weight_center_weighted
// Weight for each AEC STATs region under center weighted mode
// applicable chipset:  all chipsets
// 3A version: N/A
// applicable operation mode: preview and snapshot
// default Value:
// Data Range: N/A
// constraints: none
// effect: region with higher weight value has more influence to AEC.
/******************************************************************************/

   /* Center Weighted */
   {
      {
         0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f
      },
      {
         0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f
      },
      {
         0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f
      },
      {
         0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f
      },
      {
         0.533000f, 0.533000f, 0.533000f, 0.533000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f
      },
      {
         0.533000f, 0.533000f, 0.533000f, 0.533000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f
      },
      {
         0.533000f, 0.533000f, 0.533000f, 0.533000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f
      },
      {
         0.533000f, 0.533000f, 0.533000f, 0.533000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f
      },
      {
         0.533000f, 0.533000f, 0.533000f, 0.533000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f
      },
      {
         0.533000f, 0.533000f, 0.533000f, 0.533000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f
      },
      {
         0.533000f, 0.533000f, 0.533000f, 0.533000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f
      },
      {
         0.533000f, 0.533000f, 0.533000f, 0.533000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 2.400000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f
      },
      {
         0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f
      },
      {
         0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f
      },
      {
         0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f
      },
      {
         0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f, 0.533000f
      },
   },

/******************************************************************************/
// variable name: AEC_weight_spot_weighted
// Weight for each AEC STATs region under spot weighted mode
// applicable chipset:  all chipsets
// 3A version: N/A
// applicable operation mode: preview and snapshot
// default Value:
// Data Range: N/A
// constraints: none
// effect: region with higher weight value has more influence to AEC.
/******************************************************************************/

   /* Spot Weighted */
   {
      {
         0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f
      },
      {
         0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f
      },
      {
         0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f
      },
      {
         0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f
      },
      {
         0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f
      },
      {
         0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f
      },
      {
         0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f
      },
      {
         0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 1.000000f, 1.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f
      },
      {
         0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 1.000000f, 1.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f
      },
      {
         0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f
      },
      {
         0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f
      },
      {
         0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f
      },
      {
         0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f
      },
      {
         0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f
      },
      {
         0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f
      },
      {
         0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f
      },
   },
   /* Strobe Flash */
   {

/******************************************************************************/
// Feature name: AEC strobe flash estimation.
// Applicable chipset:  7k and newer supporting strobe flash and precision timers.
// 3A version: 2.1
// Applicable operation mode: Viewfinder and snapshot.
//
// Variable name: strobe_flash_enable.
// 1 (TRUE) uses strobe flash estimation,
// 0 (FALSE) no flash estimation used for AEC.
// Default value: 0.
// Data range: 0 or 1.
// Constraints: None.
//
// Variable name: strobe_min_time.
// Preflash strobe trigger time used. Also minimum strobe trigger
//  time (microseconds scale) used for snapshot.
// Default value: 10.
// Data range: 5 or 1000  (0us to 1ms).
// Constraints: Need to verify that strobe capacitor is not discharged too much
//              so rest of charge can be used for snapshot capture.
// Effect: Some strobes require specify minimum strobe trigger time. If made
//         shorter then strobe intensity is not consistent from flash to flash
//         or strobe will not fire.
//
// Variable name: intersect_time_gain.
// Trigger time where strobe output light gain starts to
//  compress with respect to trigger time.
// Default value: 7.
// Data range: 1 to 20.
// Constraints: None.
//
// Variable name: post_intersect_strobe_flux_rate_increase.
// After compression point determined by trigger time set in
//  intersect_time_gain, this value specifies the
//  trigger time increment for each 1x strobe light flux gain increment.
// Default value: 138.
// Data range: 1 to 1000 in us.
// Constraints: None.
//
// Variable name: max_strobe_gain.
// Max strobe gain available.
// Default Value: 8.
// Data Range: 1 to 20.
// Constraints: None.
// Effect: If value is too high, AWB may be wrong when strobe and ambient
//  illuminants are mixed and scene is far such that strobe has little effect.
//  AEC may show underexposed if value is higher than strobe is capable of.
//
// Variable name: strobe_flash_lux_idx_trigger.
// When lux index is larger than this value
//   Xenon strobe will be used if full frame exposure for snapshot contraint
//   is met.
// Default value (calculated) :  AEC Indoor Index + 46.
// Data range: 0 to 1000.
// Constraints: Lux_idx trigger may be met but if exposure time condition is
//   not met, then flash won't be used.
// Effect: Larger value will require scene to be darker for strobe to be used.
/******************************************************************************/

      0, /* Enable */
      10, /* Min Time */
      7.000000f, /* Intersect Time Gain */
      138.000000f, /* Post Intersect Flux Rate Incrase */
      8.000000f, /* Max Gain */
      286, /* Lux Idx Trigger */
   },
   /* Touch */
   {

/******************************************************************************/
// Feature name : Touch AEC  3A 2.2
// applicable chipset:  8k, 7x30 and newer.
// 3A version : 2.2.
// applicable operation mode: View finder and snapshot.
//
// variable name: touch_roi_enable
// 1 (TRUE) enables the feature, 0 (FALSE) disables the feature.
// default Value: 1
// Data Range: 0 or 1
// constraints:
// effect: 1 (TRUE) enables the feature, 0 (FALSE) disables the feature.
//
// variable name: touch_roi_weight
// Determines influence or weight of UI (touch) area vs. normal
//  AEC metering mode.
// default Value: 0.8
// Data Range: 0 to 1
// constraints:
// effect: 0 means no influence form UI selected area, 1 means "spot meter" on
//         area selected.  0.5 means both selected area luma and normal AEC luma
//         are averaged.
/******************************************************************************/

      1, /* ROI Enable */
      0.800000f, /* Weight */
   },
   /* Face */
   {

/******************************************************************************/
// Feature name : Face priority AEC, 3A 2.2
// applicable chipset:  7k and newer supporting face detection and interface
//                      with auto exposure.
// 3A version: 2.2
// applicable operation mode: View finder and snapshot.
//
// variable name: aec_face_enable
// 1 (TRUE) enables the feature, 0 (FALSE) disables the feature.
// default Value: 0
// Data Range: 0 or 1
// constraints:
// effect:
//
// variable name: aec_face_weight
// Determines how much face area contributes for frame luma calculation.
// default Value: 0.8
// Data Range: 0 to 1
// constraints:
// effect: 1 means all influence comes from face area.  0 means face information
// has no influence on AEC.
//
// variable name: dark_skin_ratio
// Skin luma vs. white point luma ratio if close to this value
//  then we set flag face as dark skin.
// default Value: 0.3
// Data Range: 0 to 1
// constraints:
// effect:
//
// variable name: light_skin_ratio
// Skin luma vs. white point luma ratio if close to this value
//  then we flag face as light skin.
// default Value: 0.7
// Data Range: 0 to 1
// constraints:
// effect:
//
// variable name: dark_skin_luma_target
// Desired luma for dark skin face.
// default Value (calculated): Default Luma Target * 0.8
// Data Range: 0 to 255
// constraints: To be applied post UI EV udpates.
// effect: AEC tries to make a dark face luma achieve this target.
//
// variable name: light_skin_luma_target
// Desiored luma for light skin face.
// default Value (calculated): Default Luma Target * 1.2
// Data Range: 0 to 255
// constraints: To be applied post UI EV udpates.
// effect: AEC tries to make a light face luma achieve this target.
/******************************************************************************/

      0, /* Enable */
      0.800000f, /* Weight */
      0.300000f, /* Dark Skin Ratio */
      0.700000f, /* Light Skin Ratio */
      40, /* Dark Skin Luma Target */
      60, /* Light Skin Luma Target */
   },

/******************************************************************************/
// Feature name: Fast Convergence AEC for camera.
// Applicable chipset(s): VFE 3.1 and later with Bayer support.
// Applicable operation mode:  Camera mode only.
//
// Variable name: aec_fast_convergence_skip.
// Frames to skip between exposure updates.
// Default value:  2.
// Data range: 1 to 5.
// Constraints: If exposure updates happen before previous frame exposure
//  updates are reflected on stats, aec oscillation may be present.  Increasing
//  aec_fast_convergence_skip will remove the problem.
// Effect: Larger values will slow down aec convergence, smaller values will
//  converge faster but may cause instability if i2c and sensor updates are
//  slow.
//
// variable name: aec_slow_convergence_skip.
// Frames to skip between exposure updates.
// Default value:  1.
// Data range: 1 to 5.
// Constraints: If exposure updates happen before previous frame exposure
//  updates are reflected on stats, aec oscillation may be present.  Increasing
//  aec_slow_convergence_skip will remove the problem.
// Effect: Larger values will slow down aec convergence, smaller values will
//  converge faster but may cause instability if i2c and sensor updates are
//  slow.
/******************************************************************************/

   2, /* AEC Fast Convergence Skip */
   1, /* AEC Slow Convergence Skip */
   /* Bayer Stats Config */
   {

/******************************************************************************/
// Feature name: Bayer Stat AEC.
// Applicable chipset(s): VFE 3.2 and later with bayer grid stats support.
// Applicable operation mode:  Preview, camcorder modes and ZSL.
//
// Variable name: bright_region_influence_adj_enable.
// Enables and disables bright region weight modification or influence
//   reduction, as bright region discrimination.
// Default value:  1.
// Data range: 0 and 1.
// Constraints: None.
// Effect: 1 enabled, 0 is disabled.
//
// Variable name: bright_weight_lux_idx_trigger.
// lux index at which to start applying different weighting to regions
//   flagged as bright.
// Default value (calculated):  Indoor_index + 60
// Data range: Indoor_index to 255
// Constraints: None.
// Effect: Defines the scene brightness range where this features works.
//
// Variable name: bright_weight_def.
// Weight to be applied on region flagged as bright for overall frame
//   luma calculation
// Default value:  0.5
// Data range: 0 to 1.0
// Constraints: None.
// Effect: 1.0 weight disables this option, i.e. all bright regions weight won't
//   be modified.  Setting 0 will make bright regions not contribute to frame
//   luma calculation.
//
// Variable name: bright_level.
// Regions above this level are flagged as bright regions.
// Default value:  220.
// Data range: 2*default_luma_target to 255.
// Constraints: None.
// Effect: 255 disables the feature as no pixel in 8 bit domain can go above 255.
//   Setting value too low will tend to flag more regions as bright.
//
// Variable name: color_based_metering_enable.
// Enables and disables color information used by AEC.
// Default value:  1.
// Data range: 0 and 1.
// Constraints: None.
// Effect: 1 enables the option to use color in AEC metering, histogram luma
//   biasing.  If disabled, portions of AEC that need color information will
//   not execute.
//
// Variable name: col_sat_weight.
// Option to apply different weight to flagged extreme color regions.
// Default value:  1.0
// Data range: 0 to 1.0
// Constraints: None.
// Effect: 1.0 disables the option as colorful regions get same weight applied.
//   0 means that a region flagged as colorful will not be used for frame luma
//   calculation.
//
// Variable name: color_luma_decrease_ratio.
// Option to lower the expected luma for flagged extreme color regions.
// Default value:  2.0
// Data range: 1.0 to 2.0
// Constraints: None.
// Effect: 1.0 disables the option as colorful regions do not get their luma
//   modified.  2.0 means that their measured luma is doubled such that it will
//   tend to make colorful regions darker after aec converges.
//
// Variable name: rg_ratio_lth.
// Lower threshold for r/g response of the region, in use with
//   bg_ratio_lth to detect extreme green regions.
// Default value:  0.85
// Data range: 0 to 1.0
// Constraints: None.
// Effect: If set too high, regions will be easier detect as extreme green color. If set
//   too low, it will be harder to detect extreme green regions.
//
// Variable name: rg_ratio_hth.
// Upper threshold for r/g response of the region.
// Default value:  2.2
// Data range: 1.0 to 4.0
// Constraints: None.
// Effect: If set too low, regions will be easier detect as extreme red color, if set
//    too high it will be harder to detect extreme red regions.
//
// Variable name: bg_ratio_lth.
// Lower threshold for b/g response of the region, in use with rg_ratio_lth to detect
//    extreme green regions.
// Default value:  0.6
// Data range: 0 to 1.0
// Constraints: None.
// Effect: If set too high, regions will be easier detect as extreme green color. If set
//   too low, it will be harder to detect extreme green regions.
//
// Variable name: bg_ratio_hth.
// Upper threshold for b/g response of the region, used to detect extreme blue regions.
// Default value:  1.8
// Data range: 1.0 to 4.0
// Constraints: None.
// Effect: If set too low, regions will be easier detect as extreme blue color regions, if set
//    too high it will be harder to detect extreme blue regions.
//
// Variable name: flat_white_grey_vs_nongrey_th.
// Threshold to determine if flat area is brighter than colored regions:
//    if (near_gr_luma > th * non_gr_luma) make overall
//    frame brighter, i.e. increase exposure.
// Default value:  1.1
// Data range: 1.05 to 2.0
// Constraints: None.
// Effect: If set too low, background will be too easy to detect as white or
//    brighter than overall scene causing tendency to increase exposure for
//    flat scenes.
//
// Variable name: flat_dark_grey_vs_nongrey_th.
// Threshold todetermine if flat area is darker than colored regions:
//    if (near_gr_luma < th*non_gr_luma) lower exposure.
// Default value:  0.5
// Data range: 0.9 to 0
// Constraints: None.
// Effect: If set too low, makes it harder to detect flat areas as dark, if set
//   too high, it will make it easier to detect flat areas as dark and tend
//   to reduce exposure on flat scenes.
//
// Variable name: hist_ent_enable.
// Enable and disable histogram frame luma offset feature.
// Default value:  1.
// Data range: o and 1.
// Constraints: None.
// Effect: 0 disabled the feature, 1 enables the feature.
//
// Variable name: hist_weight_table.
// LUT to define weight vs. pixel level bin to perform histogram analysis.
// Default value:  LUT.
// Data range: LUT.
// Constraints: None.
// Effect: By applying different weight vs. pixel level, the histogram analysis
//   may bias luma target to reduce those histogram bins with lower weight.
//
// Variable name: luma_target_reset_ratio.
// Tolerance to determine is scene changed enough to reset histogram LT offset to 0.
// Default value:  3.
// Data range: 1 to 10.
// Constraints: None.
// Effect: Higher value allows more tolerance, i.e. making scene change detection
//  less sensitivie for histogram LT offset resetting.
//
// Variable name: hist_luma_target_adjusment_cap.
// Limits the extent of luma target adjustment done by histogram analysis.
//   Example: 2 is Luma Target can be doubled, and Luma Target can be halved by
//   feature.
// Default value:  2.0
// Data range: 0 to 100.
// Constraints: None.
// Effect: If made 0 feature is disabled.  Higher values allow more modification
//   of luma target by the histogram analysis.
//
// Variable name: near_grey_tolerance.
// Region R/G and B/G tolerance to flag region as near grey.
// Default value:  0.05
// Data range: 0 to 1.0
// Constraints: None.
// Effect: Larger tolerances allow more regions to be detected as near grey for
//   flat scene dark vs. bright flat area detection.  If too large, very few color
//   regions will be detected.
//
// Variable name: bright_flat_compensation_ratio.
// Determines how much luma will be adjusted
//  for bright flat scene detection after all conditions are met
//  luma = luma * bright_flat_compensation_ratio ==> temporal filter used
// Default value:  0.6
// Data range: 0.5 to 1.0
// Constraints: None.
// Effect: Value of 1.0 will not affect luma when bright flat scene is detected.
//  Value of 0.5 will halve luma causing the overall exposure to double, i.e.,
//  final image is brighter.
//
// Variable name: dark_flat_compensation_ratio.
// Determines how much luma will be adjusted
//  for dark flat scene detection after all conditions are met
//  luma = luma * dark_flat_compensation_ratio ==> temporal filter used.
// Default value:  1.8
// Data range: 1.0 to 2.0
// Constraints: None.
// Effect: Value of 1.0 will not affect luma when dark flat scene is detected.
//  Value of 2.0 will double luma causing the overall exposure to be cut in half,
//  i.e., final image is darker.
/*******************************************************************************/

      1, /* Bright Region Influence ADJ Enable */
      200, /* Bright Weight Lux Index Trigger */
      0.500000f, /* Bright Weight Def */
      220, /* Bright Level */
      0, /* Color-Based Metering Enable */
      1.000000f, /* Color Saturated Weight */
      1.200000f, /* Color Luma Decrease Ratio */
      0.840961f, /* RG Ratio lth */
      2.247358f, /* RG Ratio hth */
      0.700220f, /* BG Ratio lth */
      1.800000f, /* BG Ratio hth */
      1.100000f, /* Flat White Gray vs Nongray Thresh */
      0.500000f, /* Flat Dark Gray vs Nongray Thresh */

/******************************************************************************/
// Feature name: Histogram pixel level weighting.
// Applicale chipset(s): VFE 3.2 and later with bayer grid stats support.
// Applicable operation mode:  Preview, camcorder modes and ZSL.
//
// Variable name: pixel_value.
// Determines the weight for the specified pixel level in this LUT.
// Default value:  0.
// Data range: 0 to 255.
// Constraints: None.
// Effect: Sets the weight for this pixel level bin in the histogram analysis.
//
// Variable name: weight.
// Determines the weight for the specified pixel level in this LUT.
// Default value:  1.
// Data range: 0 to 1.
// Constraints: None.
// Effect: Sets the weight corresponding to pixel bin in the histogram analysis.
//         Lower value means histogram luma target biasing will try to reduce
//         this pixel bin.
/*******************************************************************************/

      0, /* Hist ENT Enable */
      /* Hist Weight Table */
      {
         /* Entry 0 */
         {
            0, /* Pixel Value */
            0.000000f, /* Weight */
         },
         /* Entry 1 */
         {
            10, /* Pixel Value */
            0.100000f, /* Weight */
         },
         /* Entry 2 */
         {
            20, /* Pixel Value */
            0.400000f, /* Weight */
         },
         /* Entry 3 */
         {
            25, /* Pixel Value */
            0.800000f, /* Weight */
         },
         /* Entry 4 */
         {
            32, /* Pixel Value */
            1.000000f, /* Weight */
         },
         /* Entry 5 */
         {
            120, /* Pixel Value */
            1.000000f, /* Weight */
         },
         /* Entry 6 */
         {
            128, /* Pixel Value */
            0.800000f, /* Weight */
         },
         /* Entry 7 */
         {
            155, /* Pixel Value */
            0.400000f, /* Weight */
         },
         /* Entry 8 */
         {
            215, /* Pixel Value */
            0.100000f, /* Weight */
         },
         /* Entry 9 */
         {
            225, /* Pixel Value */
            0.000000f, /* Weight */
         },
         /* Entry 10 */
         {
            255, /* Pixel Value */
            0.000000f, /* Weight */
         },
         /* Entry 11 */
         {
            255, /* Pixel Value */
            0.000000f, /* Weight */
         },
         /* Entry 12 */
         {
            255, /* Pixel Value */
            0.000000f, /* Weight */
         },
         /* Entry 13 */
         {
            255, /* Pixel Value */
            0.000000f, /* Weight */
         },
         /* Entry 14 */
         {
            255, /* Pixel Value */
            0.000000f, /* Weight */
         },
         /* Entry 15 */
         {
            255, /* Pixel Value */
            0.000000f, /* Weight */
         },
         /* Entry 16 */
         {
            255, /* Pixel Value */
            0.000000f, /* Weight */
         },
         /* Entry 17 */
         {
            255, /* Pixel Value */
            0.000000f, /* Weight */
         },
         /* Entry 18 */
         {
            255, /* Pixel Value */
            0.000000f, /* Weight */
         },
         /* Entry 19 */
         {
            255, /* Pixel Value */
            0.000000f, /* Weight */
         },
      },
      3.000000f, /* Luma Target Reset Ratio */
      2.000000f, /* Hist Luma Target Adj Cap */
      0.050000f, /* Near Gray Tolerance */
      /* Hist Flat Detector */
      {

/******************************************************************************/
// Feature name: Bayer Grid Stat Histogram Flat Detector.
// Applicable chipset(s): VFE 3.2 and later with bayer grid stats support 3A 4.0
// Applicable operation mode:  Preview, camcorder modes and ZSL.
//
// Variable name: hist_flat_detector_enable.
// Flag to enable and disable flat scene detection.
// Default value:  1.
// Data range: 0 and 1.
// Constraints: None.
// Effect: 0 disables the flat scene detection, 1 enables flat scene detection.
//
// Variable name: start_level.
// Pixel level to start checking the histogram for flat scene.
// Default value (calculated):  42.
// Data range: range+1 to end_level-range.
// Constraints: None.
// Effect: If setting is too low, it will detect a 0 lux image as a flat image.
//
// Variable name: end_level.
// Pixel level to end checking the histogram for flat scene.
// Default value:  200.
// Data range: 255-range to 255.
// Constraints: None.
// Effect: If setting is too high, it could potentially detect saturated pixels
//   as a flat image. This is not likely to happen since AEC will bring luma down.
//
// Variable name: range.
// Pixel level range on which to check percent of pixel content.
// Default value:  40.
// Data range: 20 to 60.
// Constraints: None.
// Effect: If setting is too high, it will make it easier to detect flat scenes
//   but may wrongly detect even if not flat.  If set too low, it may not detect
//   flat scenes.
//
// Variable name: delta_th.
// If the percentage of number of pixels within the range is larger
//   than this threshold, the scene is flagged as flat.
// Default Value:  0.75.
// Data range: 0.5 to 0.9
// Constraints: None.
// Effect: If setting is too high, it will make it harder to detect flat scenes
//  or may not detect at all due to roll-off gradient.  If set too low, it may
//  falsely detect flat scenes that are not.
//
// Variable name: bright_flat_det_th.
// Describes by how much number of pixels
//   in dark tail of histogram should be greater than number of pixels in
//   bright tail of histogram
// Default value:  1.2
// Data range:  1.0 to 1.5
// Constraints:  None.
// Effect: Lower value makes it easier to detect bright flat field, a value
//   of 1.0 means that dark tail number of pixels can be greater or equal to
//   number of pixels in bright tail and still be considered bright flat
//   field.  A value of 1.5 means if condition below happens, it may be
//   considered bright field (if rest of conditions are met also)
//   dark_flat_tail_numpix > 1.5 * bright_flat_tail_numpix
//
// Variable name: dark_flat_det_th.
// Describes by how much number of pixels in bright tail of histogram
//   should be greater than number of pixels in dark tail of histogram.
// Default value:  10.0
// Data range:  1.0 to 20.0
// Constraints:  None.
// Effect: Lower value makes it easier to detect dark flat field. This value
//   means that there has to be dark_flat_det_th more pixels in the bright tail
//   than in the dark tail of the histogram.
//
// Variable name: bright_flat_tail_det.
// Defines minimum amount of pixels need to be in dark tail vs. total
//   pixels in image to be called a bright flat scene.
// Default value: 0.001
// Data range:  0.0005 to 0.01
// Constraints:  None.
// Effect: Higher value makes it harder to detect bright flat field as more
//   pixels are needed in the dark tail vs. total amount of pixels.
//
// Variable name: dark_flat_tail_det.
// Defines minimum amount of pixels needed to be in the bright tail vs.
//   total pixels in the image to be called a dark flat scene.
// Default value: 0.10
// Data range:  0.05 to 0.20
// Constraints: None.
// Effect: Higher value makes it harder to detect as dark flat field since more
//  pixels are needed in the bright tail vs. total amount of pixels in the image.
/*******************************************************************************/

         1, /* Enable */
         42, /* Start Level */
         200, /* End Level */
         40, /* Range */
         0.800000f, /* Delta Threshold */
         1.200000f, /* Bright Flat Det Th */
         10.000000f, /* Dark Flat Det Th */
         0.001000f, /* Bright Flat Tail Det */
         0.100000f, /* Dark Flat Tail Det */
      },
      0.600000f, /* Bright Flat Compensation Ratio */
      1.800000f, /* Dark Flat Compensation Ratio */
   },

/******************************************************************************/
// Feature name: Shake Detection/Indicator for Snapshot and ZSL.
//
// Variable name: Enable.
// Enables or disables the feature.
// Default value:  N/A.
// Data range: 0 to 1.
// Constraints: None.
// Effect: 0 disables the feature, 1 enables the feature.
//
// Variable name: valid_entries.
// Entries to be used from the LUT.
// Default value:  2.
// Data range: 2 to 10.
// Constraints: None
// Effect: Larger number of entries provide finer control over shake thresholds
//    vs. exposure time.
//
// Variable name: shake_table.
// LUT to defining the trade-off between
//   the motion metric and the exposure time to flag the images as containing
//   camera shake, moderate shake or no shake.
// Default value:  N/A.
// Data range: N/A.
// Constraints: None.
// Effect: N/A.
//
// Variable name: exposure_time.
// Indicator for exposure time in the LUT.
// Default value:  N/A
// Data range: 0.1ms to 1000ms.
// Constraints: Has to be increasing with LUT index.
// Effect: At this exposure time, the shake threshold specified is used.
//
// Variable name: no_shake_threshold.
// Shake value is compared to this
//   threshold to determine if the camera is shaking or not.
// Default value:  N/A.
// Data range: 10.
// Constraints: Has to be decreased with LUT index.
// Effect: At a given exposure time, the shake threshold specified is used to
//   determine if the phone is shaking during capture.
//
// Variable name: moderate_shake_threshold.
// Shake value is compared to this
//   threshold to determine if the camera is shaking or not.
// Default value:  N/A.
// Data range: 10.
// Constraints: Has to be higher than no_shake_threshold and increasing
//    with LUT index.
// Effect: At a given exposure time, the shake threshold specified is used to
//   determine if the phone is shaking during capture.
/******************************************************************************/

   /* Shake Detection */
   {
      0, /* Enable */
      0, /* Valid Entries */
      {
         /* Entry 0 */
         {
            0.000000, /* Exposure Time */
            0.000000, /* No Shake Threshold */
            0.000000, /* Moderate Shake Threshold */
         },
         /* Entry 1 */
         {
            0.000000, /* Exposure Time */
            0.000000, /* No Shake Threshold */
            0.000000, /* Moderate Shake Threshold */
         },
         /* Entry 2 */
         {
            0.000000, /* Exposure Time */
            0.000000, /* No Shake Threshold */
            0.000000, /* Moderate Shake Threshold */
         },
         /* Entry 3 */
         {
            0.000000, /* Exposure Time */
            0.000000, /* No Shake Threshold */
            0.000000, /* Moderate Shake Threshold */
         },
         /* Entry 4 */
         {
            0.000000, /* Exposure Time */
            0.000000, /* No Shake Threshold */
            0.000000, /* Moderate Shake Threshold */
         },
         /* Entry 5 */
         {
            0.000000, /* Exposure Time */
            0.000000, /* No Shake Threshold */
            0.000000, /* Moderate Shake Threshold */
         },
         /* Entry 6 */
         {
            0.000000, /* Exposure Time */
            0.000000, /* No Shake Threshold */
            0.000000, /* Moderate Shake Threshold */
         },
         /* Entry 7 */
         {
            0.000000, /* Exposure Time */
            0.000000, /* No Shake Threshold */
            0.000000, /* Moderate Shake Threshold */
         },
         /* Entry 8 */
         {
            0.000000, /* Exposure Time */
            0.000000, /* No Shake Threshold */
            0.000000, /* Moderate Shake Threshold */
         },
         /* Entry 9 */
         {
            0.000000, /* Exposure Time */
            0.000000, /* No Shake Threshold */
            0.000000, /* Moderate Shake Threshold */
         },
      },
   },
   /* Red Eye Reduction */
   {

/******************************************************************************/
// Feature name: Red eye reduction
// Applicable chipset(s): VFE 3.1 and later with Bayer support.
// Applicable operation mode:  Camera mode only.
//
// Variable name: red_eye_reduction_xenon_strobe_enable.
// Enables and disables the STROBE red-eye reduction feature.
// Default value:  0.
// Data range: 0 to 1.
// Constraints: Dependent on h/w availability of strobe unit.
// Effect: 0 disables the feature; 1 enables the feature.
//
// Variable name: red_eye_reduction_led_flash_enable.
// Enables and disables the LED red-eye reduction feature.
// Default value:  0.
// Data range: 0 to 1.
// Constraints: Dependent on h/w availability of LED unit.
// Effect: 0 disables the feature; 1 enables the feature.
//
// Variable name: number_of_preflash_cycles.
// Number of preflashes to trigger
//  prior to snapshot flash and capture.  Recommend for LED to use
//  a single longer duration cycle since it is typically not connected
//  to precision timers.
// Default value:  3.
// Data range: 0 to 20.
// Constraints: None.
// Effect: Number of preflashes.
//
// Variable name: preflash_interval_between_pulses.
// Time to wait between preflash triggers.  Unit is is millisecond (ms).
// Default value:  15.
// Data range: 0 to 33.
// Constraints: Larger than preflash pulse duration.
// Effect: Larger values is more time between pre-flashes.
//
// Variable name: preflash_xenon_pulse_duration.
// Trigger duration for strobe type pre-flash.  Unit is is microsecond (us).
// Default value:  10.
// Data range: 0 to 20.
// Constraints: Larger values may cause strobe charge in cap to deplete and
//              not have enough light output for final snapshot capture.
// Effect: Larger value is brighter pre-flash intensity.
//
// Variable name: preflash_LED_pulse_duration.
// LED on duration for LED type pre-flash.  Unit is is millisecond (ms).
// Default value:  100.
// Data range: 0 to 1000.
// Constraints: Larger values may cause LED to overheat.  Verify LED unit
//              data sheet for heat disipation requirements.
// Effect: Larger value is longer LED preflash duration.
//
// Variable name: preflash_LED_current.
// Preflash current to be used for driving the LED preflashes.  Unit is mA.
// Default value:  100.
// Data range: 0 to 1000.
// Constraints: Larger values may cause LED to overheat.  Verify LED unit
//              data sheet for heat disipation requirements.
//              S/W implementation may only support discrete current values, in
//              that case, LED current will go to nearest lower value to this
//              setting.
// Effect: Larger value is brighter LED preflash intensity.
/******************************************************************************/

      1, /* Xenon Strobe Enable */
      1, /* LED Flash Enable */
      3, /* Number of Preflash Cycles */
      15, /* Preflash Interval Between Pulses */
      10, /* Preflash Xenon Pulse Duration */
      100, /* Preflash LED Pulse Duration */
      100, /* Preflash LED Current */
   },
},

/******************************************************************************/
// Feature name: auto flicker detection.
// Parameters used for AFD algorithm.
// Applicable chipset(s): MSM7xxx and QSD8xxx.
// Applicable operation mode: VF.
//
// Variable name: AFD_continuous_enable
// Used to determine if run continuous AFD
// Default value: 0.
// Data range: 0 or 1.
// Constraints:
// Effect: 1 means AFD is continuous run periodically, 0 means only run once at camera startup.
//
// Variable name: chromatix_auto_flicker_detection_data_type.afd_std_threshold
// Used to determine if a periodic pattern is present. We measure the distance
//    between adjacent peaks and if the standard deviation of these distances is
//    smaller than the afd_std_threshold  value, it has periodic pattern,
//    ie. flicker detect flag is set.  This is part of the multi-peak algorithm.
// Default value: 0.15
// Data range:
// Constraints:
// Effect: We do not recommend the user change this parameter.
//
// Variable name: chromatix_auto_flicker_detection_data_type.afd_percent_threshold
// Used by the single peak algorithm only, which is under zoom.
//    The entire single peak algorithm is not needed if we are getting the row-sum stats from VFE HW.
//    Therefore, this parameter is only used for SW AFD solution.
//    Four frames (4 = AFD_NUM_FRAMES  AFD_FRAME_SKIP  1)
//    must have a peak present.  For flicker to be detected, the percentage of peak leading and
//    falling edges must be larger than this percentage.
// Default value: 50.
// Data range:
// Constraints:
// Effect: We do not recommend the user change this parameter.
//
// Variable name: chromatix_auto_flicker_detection_data_type.afd_diff_threshold
// Filtered Peak (diff between neighboring frames) value must be above this threshold to be considered a valid peak,
//    otherwise it is considered noise and is ignored.  When the view finder
//    window changes size, the threshold value should also be tuned.
//    The reason has to do with row sums are not calculated for every row but every other.
//    Tuning consists of finding a threshold value that detects the valid peaks while rejecting noise.
// Default value: 90.
// Data range:
// Constraints:
// Effect: We do not recommend the user change this parameter.
//
// Variable Name: chromatix_auto_flicker_detection_data_type.afd_frame_ct_threshold
// Determines if the AFD process should start, afd_frame_ct_threshold
//    number of frames are skipped before commencing the AFD algorithm.
// Default value: 60.
// Data range:
// Constraints:
// Effect: we do not recommend the user change this parameter.
//
// Variable name: chromatix_auto_flicker_detection_data_type.afd_num_frames
// This is the number of simultaneous frames to use in the AFD.
//    The frame information is saved and once this number is available the algorithm starts.
// Default value: 6.
// Data range:
// Constraints:
// Effect: we do not recommend the user change this parameter.
//
// Varialbe name: chromatix_auto_flicker_detection_data_type.afd_frame_skip
// Reflect frame skip pattern when collecting AFD STATs.
// Default value: 1.
// Data range: 0 to 4. 0 means to collect/analyze STAT for every frame. 1 means
//   to collect/analyze STATs every other frame.
// Constraints:
// Effect: we do not recommend user to change this parameter.
//
// Varialbe name: chromatix_auto_flicker_detection_data_type.afd_num_rows
// Image height when AFD STATS is collected.
// Default value: VF image height
// Data range: 240 to VF image height
// Constraints:
// Effect: This value has to reflect the VF height.
//
// Variable name: chromatix_auto_flicker_detection_data_type.afd_num_frames_settle
// Number of frames to wait after switching exposure tables.
// Default value: 3.
// Eata range: 2 to 6.
// Constraints:
// Effect: larger value will take longer time to complete AFD but allow plenty time for
//    exposure table change to settle.
/******************************************************************************/

/* Auto Flicker Detection */
{
   0, /* Continuous Enable */
   0.150000f, /* Standard Threshold */
   50, /* Percent Threshold */
   90, /* Difference Threshold */
   60, /* Frame CT Threshold */
   6, /* Number of Frames */
   1, /* Frame Skip */
   240, /* Number of Rows */
   3, /* Numer of Frames Settle */

/******************************************************************************/
// Feature name : AFD parameters
// applicable chipset:  7k and 8k
// 3A version: N/A
// applicable operation mode: preview
//
// variable name: AFD_num_peaks_threshold
// Minimum number of peaks are need for AFD algorithm to continue
// default Value: 6
// Data Range: 3 to 8
// constraints: none
// effect: higher value imposes higher requirement for flicker detection
//
// variable name: AFD_INTL_adj_factor
// Determine how big a factor that INTL has to be away from band gap
//    when creating exp table for AFD
// default Value: 0.25
// Data Range: 0 to 0.45
// constraints: none
// effect: higher value is easier for flicker to be detected
/******************************************************************************/

   6, /* Num Peaks Threshold */
   0.250000f, /* INTL Adjust Factor */
},
/* Auto Scene Detection */
{
   0, /* Software Type */
   /* Scene Change Detection */
   {

/******************************************************************************/
// Feature name : 3A Scene Change Detection
// applicable chipset(s): for all chipsets
// 3a Version: 2.0
// applicable operation mode: camcorder
//
// variable name: scd_3a_enable
// The flag to enable or disable 3a scene change detection
// default value: 1
// data range: 0(feature off) and 1 (feature on)
// constraints: N/A
// effect: Enable 3A scene change detection feature
//
// variable name: scd_aec_para_mean
// This parameter controls the contribution to the dynamic threshold
//  from the mean value of the latest scd_aec_dy_window frames SADs
//  (sum of the absolute difference).
// default value: 2
// data range: 1.0 to 4.0
// constraints: N/A
// effect: Increasing this value results in an increase in the dynamic
//  threshold and therefore less scene changes will be detected.
//
// variable name: scd_aec_para_std
// This parameter control the contribution to the dynamic threshold from
//  the standard deviation of the latest scd_aec_dy_window frames SADs
//  (sum of the absolute difference)
// default value: 2.76
// data range: 1 to 10
// constraints: N/A
// effect: Increasing this value results in an increase in the dynamic
//  threshold and therefore less scene changes will be detected.
//
// variable name: scd_aec_dy_window
// This value is used to control the window size (how many frames) for
//  computing the mean and the standard deviation.
// default value: 15
// data range: [1, maximum frame rate that can be achieved]
// constraints: N/A
// effect: The smaller the window size, the higher possibility to result
//  in faulse alarms in scene change detection. The longer the window size,
//  the more possibility to result in missed scene change detections.
//
// variable name: scd_threshold_aec_lux
// This parameter is a predefined threshold in AEC scene change detection
//  lux index method.
// default value: 10
// data range: [10,100]
// constraints: N/A
// effect: Increasing this parameter will increase the threshold for lux
//  method, which results in higher requirement on the lux index changes
//  to be classified as a scene change. In another words, the higher the
//  scd_threshold_aec_lux, the less scene changes caused by brightness
//  level change will be detected.
//
// variable name: scd_af_range_threshold
// Used to control the threshold of scene change detection in auto focus
// default value: 0.5
// data range: [0,1]
// constraints: N/A
// effect: Increasing this parameter will increase threshold for scene
//  change detection caused by auto focus, therefore less scene changes
//  will be detected.
/******************************************************************************/

      1, /* Enable */
      2.000000f, /* AEC Para Mean */
      2.760000f, /* AEC Para Std */
      15, /* DY Window */
      10, /* AEC Lux Threshold */
      0.500000f, /* AF Range Threshold */
   },
   /* Snow Scene Detection */
   {

/******************************************************************************/
// Feature name: Snow/cloudy Scene Detection.
// Applicable chipset:  8k, 7x30 and newer.
// 3A version: 2.0
//
// Variable name: snow_scene_detection_enable.
// 1 (TRUE) enables the feature from AEC perspective, 0 (FALSE)
//  disables the feature.
// Applicable operation mode: Viewfinder and snapshot.
// Default value: 1.
// Data range: 0 or 1.
// Constraints: None.
// Effect: When enabled snow scene detection and compensation feature is
//         enabled.
//
// Variable name: y_cloudy_snow_threshold.
// AEC Stat regions luma values above this threshold may be
//  used as potential snow samples.
// Applicable operation mode: Viewfinder.
// default Value (calculated): Default Luma Target
// Data range: 0 or 255.
// Constraints: Should be same as or above luma target.
// Effect: Higher values detect less snow samples, lower values cause more
//         near white regions to be detected as snow samples.
//
// Variable name: awb_y_max_in_grey.
// Any AE region above this threshold is considered potential
//  snow/cloudy region.  These regions will not have WB data
//  because WB considered too bright and above YMAX WB
//  configuration.
// Applicable operation mode: Viewfinder.
// Default value (calculated) : Normal Light AWB YMax
// Data Range: 0 to 255.
// Constraints: >= AWB bounding box YMax value.
// Effect: Higher values detect less snow samples, lower values cause more
//         close to saturated regions to be detected as snow samples.
//
// Variable name: min_snow_cloudy_sample_th.
// If count of snow/cloudy regions detected above this
//  threshold, we consider the scene as snow/cloudy. Snow scene
//  severity is 0 when snow samples are less than this threshold.
// Applicable operation mode: Viewfinder.
// Default value: 10
// Data range: 0 to 64.
// Constraints: None.
// Effect: Higher values make it harder to flag current scene as snow scene.
//
// Variable name: extreme_snow_cloudy_sample_th.
// If count of detected snow regions above this threshold,
//  scene is considered extreme snow/cloudy scene.  Snow scene
//  severity is 255 when snow samples is equal or larger than this
//  threshold.
//  Full extreme_luma_target_offset is applied.
// Applicable operation mode: Viewfinder and snapshot.
// Default value: 55.
// Data range: min_snow_cloudy_sample_th to 64.
// Constraints: None.
// Effect: Higher values make it harder to flag current scene as extreme snow
//         scene or severity set to 255.
//
// Variable name: extreme_luma_target_offset.
// Maximum luma offset that can be applied when snow scene is
//  detected.  This happens when extreme_snow_cloudy_sample_th is
//  reached or exceeded and exposure index is less than outdoor
//  index.
//  Luma offset is gradually reduced for darker scenes until
//  eventually made 0 for indoor cases, this is based on exp_index.
//  (Cannot use lux_idx due to rapid change based on frame luma;
//  will cause luma offset to be unstable.)
// Applicable operation mode: Viewfinder and snapshot.
// default Value (calculated): Default Luma Target
// Data range: 0 to twice luma target.
// Constraints: None.
// Effect: Higher values make image brighter for snow scene detected.
//
// Variable name: severe_snow_scene_cap.
// Point at which �backlit_max_digital_gain will be applied, value
//  is 0 to 255 for severity.  255 means snow scene detection must report 255 severity
//  for backlit_max_digital_gain to be applied.  If set to 0, it is always applied.
//  Care is needed to not use 0 otherwise backlit_max_digital_gain will always be applied.
// Spplicable operation mode: Viewfinder and snapshot.
// Default value: 255
// Data range: 0 to 255
// Constraints: None.
// Effect: See description above.
//
// Variable name: snowscene_aggressiveness
// Adjust reaction time of snow/cloudy scene compensation.
// Default value: 0.2
// Data range: 0 to 1.0
// Constraints:
// Effect: Larger makes snow/cloudy compensation react faster by updating luma
//         target.  If set too aggressive, AE oscillation may happen.
//
// Variable name: ui_snow_cloudy_display_th.
// When detection severity is larger than this threshold, UI may display icon
//     representing this type of scene.
// Applicable operation Mode: Preview, camcorder.
// Default value: 80.
// Data range: 1 to 255.
// Constraints: Larger vlaue requires scene severity to be larger to display
//              icon.
// Effect: ICON display on UI when option is enabled in UI.
/******************************************************************************/

      1, /* Enable */
      56, /* Y Snow Threshold */
      210, /* AWB Y Max in Grey */
      10, /* Min Snow Sample Threshold */
      55, /* Extreme Snow Sample Threshold */
      56.000000f, /* Extreme Luma Target Offset */
      255, /* Severe Snow Cap */
      0.200000f, /* Aggressiveness */
      80, /* UI Display Th */
   },
   /* Backlit Scene Detection */
   {

/******************************************************************************/
// Feature name: Backlit Scene Detection.
// Applicable chipset:  8k, 7x30 and newer.
// 3A version: 2.0
//
// Variable name: backlight_detection_enable.
// 1 (TRUE) enables the feature, 0 (FALSE) disables the feature.
// Applicable operation mode: Viewfinder and snapshot.
// Default value: 1.
// Data range: 0 or 1.
// Constraints: None.
// Effect: 1 enables the feature.
//
// Variable name: low_luma_threshold.
// Preview frame histogram samples which luma is below this
//  threshold are added to low luma count.
// Applicable operation mode: Viewfinder.
// Default value: 10.
// Data range: 0 to high_luma_threshold.
// Constraints: None.
// Effect: Lower values detect less samples as "dark" to be considered for
//         backlit detection.
//
// Variable name: high_luma_threshold.
// Histogram samples which luma is above this threshold are
//  added to high luma count.
// Applicable operation mode: Viewfinder.
// Default value: 235.
// Data range: low_luma_threshold to 255.
// Constraints: None.
// Effect: Higher values detect less samples as "bright" to be considered for
//         backlit detection.
//
// Variable name: low_luma_count_percent_threshold.
// If count of low luma samples exceed this percentage of total
//  samples, we consider potential backlight case.
// Applicable operation mode: Viewfinder.
// Default value: 10.
// Data range: 0 to 100.
// Constraints: None.
// Effect: Higher value requires more dark samples for histogram portion of
// backlight detection to flag as potential backlit scene so it reduces probability
// to detect backlight condition.
//
// Variable name: high_luma_count_percent_threshold.
// If count of high luma samples exceed this percentage of total
//  samples, we consider potential backlight case.
// Applicable operation mode: Viewfinder.
// Default value: 10.
// Data range: 0 to 100.
// Constraints: None.
// Effect: Higher value requires more bright samples for histogram portion of
// backlight detection to flag as potential backlit scene so it reduces probability
// to detect backlight condition.
//
// Variable name: backlight_la_8k_config.
// Luma Adaptation configuration when backlight scene is
//  detected, compensation portion.
// Applicable operation mode: Viewfinder.
// Default value: Same as normal light.
// Data range: N/A.
// constraints: None.
//
// Variable name: backlight_max_la_luma_target_adj.
// Maximum luma target adjustment when backlight is detected.
//  We expect to increase luma target.
// Applicable operation mode: Viewfinder.
// Default value: 1.1
// Data range: 0.5 to 2.
// Constraints: None
// Effect: >1 value will increase luma target and bring out the dark areas. <1 value
// will decrease luma target and avoid saturation in highlight areas.
//
// Variable name: max_percent_threshold.
// End of interpolation range for severity.
//   Closer value to min_percent_threshold will cause backlit compensation to
//   have more effect.
// Applicable operation mode:  Camera mode only.
// Default value:  1.
// Data range: 0.5 to 1.0
// Constraints: Due to nature of compensation affecting the detection, a smaller
//   value may cause the backlit detection to become unstable.
// Effect: More aggresive application of backlit compensation for smaller
//   max_percent_threshold values.
//
// Variable name: ui_backlit_display_th.
// When detection severity is larger than this threshold, UI may display icon
//     representing this type of scene.
// Applicable operation mode: Preview, camcorder.
// Default value: 80.
// Data range: 1 to 255.
// Constraints: Larger value requires scene severity to be larger to display
//              icon
// Effect: ICON display on UI when option is enabled in UI.
/******************************************************************************/

      1, /* Enable */
      10, /* Low Luma Threshold */
      235, /* High Luma Threshold */
      10.000000f, /* Low Luma Count Percent Threshold */
      10.000000f, /* High Luma Count Percent Threshold */
      /* Outdoor Luma Adaptation */
      {
         70, /* Shadow Range */
         100, /* Shadow Boost Allowance */
         0, /* Reduction Fine Tune */
         0, /* Highlight Supress Fine Tune */
         0, /* Shadow Boost Fine Tune */
      },
      20, /* Max Luma Target Adjust */
      0.200000f, /* Aggressiveness */
      1.000000f, /* Max Percent Threshold */
      80, /* UI Display Th */
   },
   /* Landscape Scene Detection */
   {

/******************************************************************************/
// Feature name: Landscape Scene Detection and Compensation.
// Applicable chipset(s): VFE 3.2 and later with bayer grid stats support.
// 3A version: 4.0
// Applicable operation mode:  Preview, camcorder modes and ZSL.
//
// Variable name: asd_ext_blue_th.
// Extreme blue region detection threshold If region from Bayer Grid stats is
//    above this threshold, region is considered extreme blue.
// Default value:  1.15
// Data range: 1.0 to 3.0
// Constraints: None.
// Effect: Higher value allows less extreme blue regions to be detected.
//
// Variable name: asd_ext_green_th_r.
// Extreme green region detection threshold. If region from Bayer Grid stats is
//    below this threshold and below asd_ext_green_th_b, region is considered extreme green.
// Default value:  1.1
// Data range: 0.5 to 3.0
// Constraints: Region has been white balanced.
// Effect: Higher value allows more extreme green regions to be detected.
//
// Variable name: asd_ext_green_th_b.
// Extreme green region detection threshold. If region from Bayer Grid stats is
//    below this threshold and below asd_ext_green_th_r, region is considered extreme green.
// Default value:  1.2
// Data range: 0.5 to 3.0
// Constraints: Region has been white balanced.
// Effect: Higher value allows more extreme green regions to be detected.
/****************************************************************************/

      1, /* Enable */
      1.300000f, /* Red Boost Factor */
      1.600000f, /* Green Boost Factor */
      1.600000f, /* Blue Boost Factor */
      0.050000f, /* Min Blue Green Content Detection Threshold */
      0.120000f, /* Max Blue Green Content Detection Threshold */
      0, /* Green Offset RG */
      0, /* Green Offset BG */
      1.150000f, /* Extreme Blue Threshold */
      1.100000f, /* Extreme Green Threshold R */
      1.200000f, /* Extreme Green Threshold B */
      0.500000f, /* Aggressiveness */
      217, /* Lux Idx Indoor */
      140, /* Lux Idx Outdoor */
      80, /* UI Display Th */
   },
   /* Portrait Scene Detection */
   {

/******************************************************************************/
// Feature name: Portrait Scene Detection.
// Applicable chipset(s): VFE 3.1 and later with Bayer support.
//
// Variable name: portrait_detection_enable.
// Enables and disables the feature.
// Applicable operation mode:  Preview, camcorder record and snapshot.
// Default value:  1.
// Data range: 0 to 1.
// Constraints: None.
// Effect: 0 disables the feature; 1 enables the feature.
//
// Variable name: skin_color_boost_factor.
// Allows skin tones to be modified to look paler or tanner.
// Applicable operation mode:  Preview, camcorder record and snapshot.
// Default value:  0.
// Data range: -1 to +1.
// Constraints: -1 to +1 in 1/100 step.
// Effect: +1 = most pale, -1 = most tan.
//
// Variable name: min_face_content_threshold.
// Determines amount of area with respect to frame size to be called a
//     portrait scene.
// Applicable operation mode:  Preview, camcorder record and snapshot.
// Default value:  0.010
// Data range: 0 to 1.
// Constraints: None.
// Effect: 0 will always detect as portrait as long as a face has been detected.
//   1 will require face area to cover the whole frame to be called a portait
//   scene.  Default value needs 1% of the frame area to be face to be called
//   portrait, although severity will be close to 0.
//
// Variable name: max_face_content_threshold.
// Determines amount of area with respect to frame size to be called a
//     portrait scene.
// Applicable operation mode:  Preview, camcorder record and snapshot.
// Default value:  0.05
// Data range: 0 to 1.
// Constraints: None.
// Effect: If face area w.r.t. to frame size is larger than this threshold,
//   portrait severity will be 255.  Portrait severity is interpolated based
//   on face area between min and max_face_content_threshold.
//
// Variable name: soft_focus_degree.
// Amount of blurring to be applied
//  on image when portrait scene is detected.  This gets interpolated
//  according to portrait severity value.
// Applicable operation mode:  Preview, camcorder record and snapshot.
// Default value:  0.9
// Data range: 0.5 to 1.
// Constraints: None.
// Effect: Smaller value will result in softer focus appearance.
//
// Variable name: aggressiveness.
// Adjust reaction time of portrait compensation.
// Applicable operation mode:  Preview, camcorder.
// Default value: 0.5
// Data range: 0 to 1.0
// Constraints: None.
// Effect: Larger value makes portrait compensation react faster.
//
// Variable name: ui_portrait_display_th.
// When detection severity is larger than this threshold, UI may display icon
//     representing this type of scene.
// Applicable operation mode:  Preview, camcorder.
// Default value: 80.
// Data range: 1 to 255.
// Constraints: Larger value requires scene severity to be larger to display
//              icon.
// Effect: ICON display on UI when option is enabled in UI.
/******************************************************************************/

      1, /* Enable */
      0.000000f, /* Skin Color Boost Factor */
      0.010000f, /* Min Face Content Threshold */
      0.050000f, /* Max Face Content Threshold */
      0.900000f, /* 7x7 Soft Focus Degree */
      0.900000f, /* Soft Focus Degree */
      0.500000f, /* Aggressiveness */
      80, /* UI Display Th */
   },
   /* Sunset Color Conversion */
   /* Noise Weight: 0.000000 */
   /* Saturation: Red - 1.000000, Green - 1.000000, Blue - 1.000000 */
   {
      {
         /* a_m, a_p */
         0.5890f, 0.5890f,
         /* b_m, b_p */
         -0.2806f, -0.2806f,
         /* c_m, c_p */
         0.5519f, 0.5519f,
         /* d_m, d_p */
         -0.1600f, -0.1600f,
         /* k_cb, k_cr */
         128, 128
      },
      {
         /* v0, v1, v2 */
         0.2990f, 0.5870f, 0.1140f,
         /* k */
         0
      }
   },
   /* TL84 Skintone Color Conversion */
   /* Noise Weight: 0.000000 */
   /* Saturation: Red - 1.000000, Green - 1.000000, Blue - 1.000000 */
   {
      {
         /* a_m, a_p */
         0.5873f, 0.5873f,
         /* b_m, b_p */
         -0.3007f, -0.3007f,
         /* c_m, c_p */
         0.5678f, 0.5678f,
         /* d_m, d_p */
         -0.1485f, -0.1485f,
         /* k_cb, k_cr */
         128, 128
      },
      {
         /* v0, v1, v2 */
         0.2990f, 0.5870f, 0.1140f,
         /* k */
         0
      }
   },
   /* D65 Skintone Color Conversion */
   /* Noise Weight: 0.000000 */
   /* Saturation: Red - 1.000000, Green - 1.000000, Blue - 1.000000 */
   {
      {
         /* a_m, a_p */
         0.5944f, 0.5944f,
         /* b_m, b_p */
         -0.3135f, -0.3135f,
         /* c_m, c_p */
         0.5532f, 0.5532f,
         /* d_m, d_p */
         -0.1915f, -0.1915f,
         /* k_cb, k_cr */
         128, 128
      },
      {
         /* v0, v1, v2 */
         0.2990f, 0.5870f, 0.1140f,
         /* k */
         0
      }
   },
   /* A Skintone Color Conversion */
   /* Noise Weight: 0.000000 */
   /* Saturation: Red - 1.000000, Green - 1.000000, Blue - 1.000000 */
   {
      {
         /* a_m, a_p */
         0.5890f, 0.5890f,
         /* b_m, b_p */
         -0.2806f, -0.2806f,
         /* c_m, c_p */
         0.5519f, 0.5519f,
         /* d_m, d_p */
         -0.1600f, -0.1600f,
         /* k_cb, k_cr */
         128, 128
      },
      {
         /* v0, v1, v2 */
         0.2990f, 0.5870f, 0.1140f,
         /* k */
         0
      }
   },
},
/* Zero Shutter Lag */
{

/******************************************************************************/
// Feature name: Zero shutter lag.
//
// Variable name: default_shutter_lag.
// Default shutter lag value used in Zero Shutter Lag mode in ms.
// Default value: 300.
// Data range: bigger than or equal to 0.
// Constraints: None.
// Effect: The bigger the value is, the more images buffered in ZSL mode.
//
// Variable name: max_Q_factor_reduction.
// The maximum image Q factor percentage reduction used in image buffer size
//   control. The min image Q factor =
//   default Q factor * (1-�max_Q_factor_reduction).
// Default value: 20.
// Data range: 0 to 30.
// Constraints: None.
// Effect: The bigger the value is, the lower the potential image quality when
//         buffer length control is enabled.
/******************************************************************************/

   300, /* Default Shutter Lag */
   20, /* Max Q Factor Reduction */
},
/* Post Processing */
{
   /* HDR */
   {

/******************************************************************************/
// Feature name: HDR.
// Applicable chipset(s): ALL with HDR feature.
// Applicable operation mode:  HDR feature turned on.
//
// Variable name: global_motion_tolerance.
// The maximum amount of global motion which can be tolerated
//       before HDR is turned off.
// Default value:  0.05
// Data range: 0 to 0.05
// Constraints: None.
// Effect: Decreasing the tolerance allows less global motion in the image
//         before HDR is turned off.
//
// Variable name: contrast_meter.
// The overall contrast of the HDR image.
// Default value:  0.25
// Data range: 0 to 1.0
// Constraints: None.
// Effect: Increasing contrast gives more contrast to the final HDR image.
//
// Variable name: normal_lowlight_boost_meter.
// Adjustment of the length of the tail of the histogram control curve under normal light.
// Default value:  0.5
// Data range: 0 to 1.0
// Donstraints: Highly recommended not to modify it.
// Effect: Increasing the parameter will boost up more in the low light area.
//
// Variable name: bright_lowlight_boost_meter.
// Adjustment of the length of the tail of the histogram control curve under bright light.
// Default value:  0.5
// Data range: 0 to 1.0
// Constraints: Highly recommended not to modify it.
// Effect: Increasing the parameter will boost up more in the low light area.
/********************************************************************************/

      0.050000f, /* Tolerance */
      0.250000f, /* Contrast Meter */
      0.500000f, /* Normal/Lowlight Boost Meter */
      0.500000f, /* Bright light Boost Meter */
   },
   /* Face Detection */
   {

/******************************************************************************/
// Feature name : Face Detection/Recognition.
// Applicable chipset:  7k and newer supporting face detection.
// Applicable operation mode: Viewfinder.
//
// Variable name: minimum_face_width.
// Minimum number of pixels for a side for the face to be detected; cannot go lower than 20
// Default: 20.
// Data Range: 20-8192
// Effect: It affects performance; the lower the minimum is, the longer it takes
//
// Variable name: maximum_face_width.
// Maximum number of pixels for a side for the face to be detected;
// Default: 0.
// Data Range: 0, 20-8192 (bigger than minimum_face_width).
// Effect: It affects performance; the higher the maximum is, the longer it takes.
//   If 0, it indicates it will be set to the shorter edge of the input frame.
//
// Variable name: maximum_num_face_to_detect.
// Maximum number of faces to detect (up to 1023)
// Default: 8.
// Effect: It affects performance; the higher the maximum is, the longer it takes to detect.
//
// For the following three variables, please read section below first:
//
// Face image direction and angle range (Non-tracking related settings)
// Lower  12 bits are for right side of Diagonal and Sideway faces
// Higher 12 bits are for left  side of Diagonal and Sideway faces
// The angles below are according the following diagram:
//
//                                                /^\
//                                               / | \
//                                                 |
//                           0                  _______
//                     315   |   45            /       \
//                        \     /             / .    .  \
//                  270 -         - 90       (     |     )
//                        /     \             \  \___/  /
//                     225   |    135          \       /
//                          180                 \_____/
//
//
// ANGLE_0  = 0x00001001  /* Top of the head facing from 345 degrees to 15  degrees */
// ANGLE_1  = 0x00002002  /* Top of the head facing from 15  degrees to 45  degrees */
// ANGLE_2  = 0x00004004  /* Top of the head facing from 45  degrees to 75  degrees */
// ANGLE_3  = 0x00008008  /* Top of the head facing from 75  degrees to 105 degrees */
// ANGLE_4  = 0x00010010  /* Top of the head facing from 105 degrees to 135 degrees */
// ANGLE_5  = 0x00020020  /* Top of the head facing from 135 degrees to 165 degrees */
// ANGLE_6  = 0x00040040  /* Top of the head facing from 165 degrees to 195 degrees */
// ANGLE_7  = 0x00080080  /* Top of the head facing from 195 degrees to 225 degrees */
// ANGLE_8  = 0x00100100  /* Top of the head facing from 225 degrees to 255 degrees */
// ANGLE_9  = 0x00200200  /* Top of the head facing from 255 degrees to 285 degrees */
// ANGLE_10 = 0x00400400  /* Top of the head facing from 285 degrees to 315 degrees */
// ANGLE_11 = 0x00800800  /* Top of the head facing from 315 degrees to 345 degrees */
//
// Variable name: angles_to_detect_pose_front.
// Detectable angles for front pose faces (bitwise OR the angles together e.g. ANGLE_0 | ANGLE_1 | ANGLE_2).
// Default: ANGLE_8 | ANGLE_9 | ANGLE_10 | ANGLE_11 | ANGLE_0 | ANGLE_1 | ANGLE_2 | ANGLE_3 | ANGLE_4
//   This default takes care of the phone rotating either left of right (depends on the way modules are mounted also).
// Effect: It affects performance; the more angles, the longer it takes.
//
// Variable name: angles_to_detect_pose_half_profile.
// Detectable angles for half profile faces (faces not looking directly toward the phone, but 45 degress to the side).
// Default: ANGLE_8 | ANGLE_9 | ANGLE_10 | ANGLE_11 | ANGLE_0 | ANGLE_1 | ANGLE_2 | ANGLE_3 | ANGLE_4
//   This default takes care of the phone rotating either left of right (depends on the way modules are mounted also).
// Effect: It affects performance; the more angles, the longer it takes.
//
// Variable name: angles_to_detect_pose_profile.
// Detectable angles for sideways faces.
// Default: ANGLE_NONE.
// Effect: It affects performance; the more angles, the longer it takes.
//
// Below are face recognition tuning parameters
//
// Variable name: max_num_users.
// Maximum number of users in the database.
// Default: 10
// Data Range: anything greater than or equal to 1.
//
// Variable name: max_data_per_user.
// Maximum number of data per user in the database.
// Default: 5.
// Data Range: 1-10.
/******************************************************************************/

      20, /* Minimum Face Width */
      0, /* Maximum Face Width */
      8, /* Maximum Num Faces to Detect */
      15859487, /* Angles to Detect Front */
      15859487, /* Angles to Detect Half-Profile */
      0, /* Angles to Detect Profile */
   },
   /* Face Recognition */
   {
      10, /* Max Number of Users */
      5, /* Max Data per User */
   },
   /* Chroma Aliasing */
   {
      0, /* Control Method - 1 = Gain, 0 = Lux Index */
      /* Trigger Points */
      {
         7.200000f, /* Gain Start */
         8.000000f, /* Gain End */
         338, /* Lux Index Start */
         376, /* Lux Index End */
      },

/******************************************************************************/
// Feature name: Chroma aliasing correction.
// Applicable chipset(s): ALL with chroma aliasing correction.
// Applicable operation mode:  Chroma aliasing correction feature turned on
//
// Variable name: correction_strength.
// Control the overall strength of chroma suprresion effect.
// Default value:  0.
// Data range: 0 or 1.
// Constraints: Boolean type (o or 1).
// Effect: Default setting 0 works for most cases, when much stronger chroma aliasing correction is needed,
//         the parameter is set to 1.
//
// Variable name: brightness_threshold.
// Chroma aliasing correction is applied on the areas that are brighter than the threshold.
// Default value:  10.
// Data range: 0 to 255.
// Constraints: None.
// Effect: Increasing the threshold will have less areas been influenced by chroma aliasing correction.
//
// Variable name: soft_threshold_center.
// There is a soft thresholding control in chroma aliasing correction, which controls the sensitivity of
//       the correction. This parameter is the soft thresholding center.
// Default value:  45.
// Data range: 0 to 255.
// Constraints: None.
// Effect: Increasing the threshold center will make chroma aliasing correction to be less sensitive,
//       so it will have less correction.
//
// Variable name: soft_threshold_span.
// There is a soft thresholding control in chroma aliasing correction, which controls the sensitivity of
//       the correction. This parameter is the soft thresholding span range.
// Default value:  10.
// Data range: 0 to 63.
// Constraints: None.
// Effect: This parameter controls the transfer range of the soft thresholding, the larger the number,
//       the larger the transfer range.
/********************************************************************************/

      /* Lowlight */
      {
         0, /* Correction Strength */
         10, /* Brightness Threshold */
         45, /* Threshold Center */
         10, /* Soft Threshold Span */
      },
      /* Normal light */
      {
         0, /* Correction Strength */
         10, /* Brightness Threshold */
         45, /* Threshold Center */
         10, /* Soft Threshold Span */
      },
   },
   /* Color Tint */
   {

/******************************************************************************/
// Feature name: Color tint correction.
// Applicable chipset(s): ALL with color tint correction.
// Applicable operation mode:  color tint correction feature turned on.
//
// Variable name: tint_correction_mode.
// Select the mode of color tint correction.
// Default value:  0.
// Data range: 0 or 1.
// Constraints: Boolean type (0 or 1).
// Effect: Mode 0 works for most cases, it has short latency and reasonable accuracy.
//         Mode 1 has higher correction accuracy but with longer latency.
//
// Variable name: tint_correction_strength.
// Control the strength of color tint correction.
// Default value:  4.
// Data range: 0 or 10.
// Constraints: Default value is highly recommended.
// Effect: Increasing this number will increase the color tint correction strength meaning
//    more severe color tint can be corrected, but it may desaturate some colors when it�s too high.
//
// Variable name: tint_correction_accuracy_degree.
// Control the accuracy degree of color tint correction.
// Default value:  8.
// Data range: 1 or 16.
// Constraints: Default value is highly recommended.
// Effect: Increasing this number will increase the color tint correction accuracy. However,
//       when the setting is too high some trailing color tint may happen for video or viewfinder mode
//       when camera or objects move.
/********************************************************************************/

      0, /* Correction Mode */
      4, /* Correction Strength */
      8, /* Correction Accuracy Degree */
   },
   /* Local Tone Mapping */
   {

/******************************************************************************/
// Feature name : LTM.
// Applicable chipset: MSM8094 and later.
// Applicable operation mode:  For VF and snapshot.
//
// Variable names: fCV_R, fCV_G, fCV_B, fCV_Kc, fCV_Cthr.
// RGB to Yp conversion coefficients and strong color inclusion parameters.
// Default values (for 12-bit data):
//   0.299000f, 0.587000f, 0.114000f, 0.700000f, 32.000000f
// Data range: 0 to 1.0f for fCV_R, fCV_G, fCV_B, 0 to 10.0f for fCV_Kc, and
//   0 to 127 for fCV_Cthr.
// Constraints: fCV_R, fCV_G, fCV_B should sum up to 1.0f.
// Effect: fCV_R, fCV_G, fCV_B are regular RGB->Y conversion; fCV_Cthr sets the
//   threshold of strong Cb/Cr color, and fCV_Kc sets the strength of strong
//   color inclusion to Yp.  Note that debug_out_sel in hardware register allows
//   LTM to output local tone mapped RGB output (0x0, default), brightness filter
//   output (0x1), local tone mapped Yp output (0x2), and Yp (0x3) images.
//   Choosing 0x3 allows monitoring the Yp tuning effects.
//
// Variable name: nInitCntFactor.
// Initial pixel count factor of brightness filter 3D bins.
// Default value: 1.
// Data range: 0 to 8.
// Constraints: 0 <= nInitCntFactor <= 8;
// Effect: nInitCntFactor initialized brightness filter bin pixel counts to
//   2^nInitCntFactor. Larger values would reduce the strength of brightness
//   filter and vice versa.
//
// Variable name: fSigmaXY, fSigmaZ.
// Sigma of Gaussian smoothing of brightness mask filter 3D bins in XY and Z
//    dimensions.
// Default values: 1.100000f, 2.700000f.
// Data range: 0.2f to 12.0f.
// Constraints: None.
// Effect: Higher value of fSigmaXY and fSigmaZ enhance brightness mask
//   filtering in image and brightness dimensions, respectively.  Note that
//   debug_out_sel in hardware register allows LTM to output local tone mapped
//   RGB output (0x0, default), brightness filter output (0x1), local tone mapped
//   Yp output (0x2), and Yp (0x3) images. Choosing 0x1 allows monitoring
//   brightness mask tuning effects.
//
// Variable name: nNormalLoCut, nNormalHiCut, nStrongLoCut, nStrongHiCut.
// Cutoff values of scene-dependent brightness mask rectification curve for
//    normal and strong image clutterness.
// Default values: 1, 5, 17, 17.
// Data range: 0 to 31.
// Constraints: Integer indices for 64-entry LUT of mask rectification curve.
// Effect: Rectification curve further adjusts brightness mask output to
//   approximate local image brightness. Low cuts of normal and strong image
//   clutterness control the low brightness pixels and High cuts control the
//   high brightness pixels.  Choosing debug_out_sel = 0x1 allows monitoring
//   brightness mask and rectification curve tuning effects.
//
// Variable name: fBusyThr1, fBusyThr2.
// Image busyness decision thresholds.
// Default values: 1.300000f, 3.100000f.
// Data range: > 0.
// Constraints: fBusyThr1 < fBusyThr2.
// Effect: Image busyness is 0 if heuristics #1 is less than fBusyThr1 and
//   busyness is 1 if heuristics #1 is greater than fBusyThr2, and linearly
//   increasing from 0 to 1.0 in between. Image busyness is later combined with
//   low-end image clutterness to decide the low cutoff value of mask
//   rectification curve.
//
// Variable name: nLowTrig0, nLowTrig1, nLowTrig2, nLowTrig3;
//   nHighTrig0, nHighTrig1, nHighTrig2, nHighTrig3.
// Image clutterness decision thresholds.
// Default values:
//   6000, 12000, 20000, 35000;
//   4000, 9000, 50000, 60000.
// Data range: > 0.
// Constraints: nLowTrig0 < nLowTrig1 < nLowTrig2 < nLowTrig3 and
//   nHighTrig0 < nHighTrig1 < nHighTrig2 < nHighTrig3.
// Effect: When low-end heuristics #2 goes from nLowTrig0 to nLowTrig1, low-end
//   image clutterness goes linearly from 0 to 1.0. From nLowTrig1 to nLowTrig2,
//   low-end image clutterness remains 1.0. From nLowTrig2 to nLowTrig3, low-end
//   image clutterness descend from 1.0 to 0. Similarly for high-end heuristics
//   #2.  Low-end image clutterness is combined with image busyness to determine
//   low-end cutoff value of mask rectification curve and high-end image
//   clutterness decides the high-end cutoff value of mask rectification curve.
//
// Variable name: fManualGTMGain, fManualGTMSigma, fW1_LA.
// Manual global tone mapping curve generation parameters and weighting factor of
//    automatic global tone mapping curve (LA curve).
// Default values: 2.200000f, 10.240000f, 0.500000f.
// Data range: 0 < fManualGTMGain; 0 < fManualGTMSigma < 64.0f;
//   0 <= fW1_LA <= 1.0f.
// Constraints: None.
// Effect: fManualGTMGain and fManualGTMSigma decide the magnitude and sigma of
//   Gaussian-shaped manual global tone mapping (GTM) curve. fW1_LA is the
//   weight of automatic luma adaptation (LA) global tone mapping curve.
//   (1 - fW1_LA) is the weight of manual GTM curve which modulates the LA GTM
//   curve. Increasing fManualGTMGain would make output image brighter.
//   Increasing fManualGTMSigma would make brightness boost range wider.
//
// Variable name: fScaleConstraintLB.
// Lower bound constraint for scene-dependent master/shift Gaussian-like scale
//    curve.
// Default value: 0.450000f.
// Data range: 0.0 to 1.0.
// Constraints: None.
// Effect: fScaleConstraintLB controls the lower bound of the master/shift
//   Gaussian-like scale curve.  Lower value may provide larger curve set change
//   from low brightness mask value to high mask value, but artifacts may arise
//   if not carefully tuned.
//
// Variable name: fScaleSigmaMult, fScaleWidthLB.
// Sigma multiplication factor and width lower bound of master/shift scale curve.
// Default values: 0.750000f, 10.000000f.
// Data range: fScaleSigmaMult: 0 to 20.0f; fScaleWidthLB: 1.0f to 127.0f.
// Constraints: None.
// Effect: fScaleSigmaMult multiplies to the estimated sigma for the sigma of the
//   master/shift scale curve, and fScaleWidthLB bounds the scale curve sigma
//   from below. Increasing fScaleSigmaMult makes the scene-dependent scale
//   curve wider, and increasing fScaleWidthLB makes the minimum scale curve
//   width wider.
//
// Variable name: fMasterScaleAdj.
// Magnitude adjusting factor for master scale curve.
// Default value: 0.750000f.
// Data range: 0 to 1.0f.
// Constraints: None.
// Effect: fMasterScaleAdj is multiplied to the estimated scene-dependent
//   master/shift scale curve magnitude to scale down the range from top (always
//   1.0) to bottom. If fMasterScaleAdj is 0, then the resultant master scale
//   curve will be a flat line of 1.0.
//
// Variable name: fShiftSigma, fShiftMag.
// Sigma and magnitude of sigmoid shift curve.
// Default values: 0.100000f, 0.250000f.
// Data range: > 0.
// Constraints: None.
// Effect: fShiftSigma and fShiftMag are the sigma and magnitude of the sigmoid
//   shift curve, respectively. Increasing fShiftSigma makes the sigmoid shift
//   curve wider and flatter, and increasing fShiftMag makes the magnitude of the
//   shift curve larger.
//
// Variable name: nSoftThr0, nSoftThr1, nSoftThrSlope.
// Soft threshold curve parameters to overlay sigmoid shift curve.
// Default values: 3, 18, 16.
// Data range: nSoftThr0 & nSoftThr1: 0 to 64; nSoftThrSlope (Q8): >= 0.
// Constraints: nSoftThr1 > nSoftThr0.
// Effect: Soft threshold overlay is 0 between 0 and nSoftThr0, then linearly
//   increasing to nSoftThrSlope * (nSoftThr1 - nSoftThr0) / 256 at nSoftThr1,
//   and flat afterwards.  This curve is added upon the sigmoid shift curve for
//   the final shift curve.
//
// Variable name: fShiftScaleAdj.
// Adjusting factor of the shift scale magnitude
// Default value: 1.050000f.
// Data range: >= 0.
// Constraints: None.
// Effect: fShiftScaleAdj is multiplied to the estimated scene-dependent
//   master/shift scale curve magnitude to scale up/down the range from top
//   (always 1.0) to bottom.  If fShiftScaleAdj is 0, then the resultant shift
//   scale curve will be a flat line of 1.0.
/******************************************************************************/

      0.299000f, /* CV_R */
      0.587000f, /* CV_G */
      0.114000f, /* CV_B */
      0.700000f, /* CV_Kc */
      32.000000f, /* CV_Cthr */
      1, /* InitCntFactor */
      1.100000f, /* SigmaXY */
      2.700000f, /* SigmaZ */
      1, /* NormalLoCut */
      5, /* NormalHiCut */
      17, /* StrongLoCut */
      17, /* StrongHiCut */
      1.300000f, /* BusyThr1 */
      3.100000f, /* BusyThr2 */
      6000, /* LowTrig0 */
      12000, /* LowTrig1 */
      20000, /* LowTrig2 */
      35000, /* LowTrig3 */
      4000, /* HighTrig0 */
      9000, /* HighTrig1 */
      50000, /* HighTrig2 */
      60000, /* HighTrig3 */
      2.200000f, /* ManualGTMGain */
      10.240000f, /* ManualGTMSigma */
      0.500000f, /* W1_LA */
      0.450000f, /* ScaleConstraintLB */
      0.750000f, /* ScaleSigmaMult */
      10.000000f, /* ScaleWidthLB */
      0.750000f, /* MasterScaleAdj */
      0.100000f, /* ShiftSigna */
      0.250000f, /* ShiftMag */
      3, /* SoftThr0 */
      18, /* SoftThr1 */
      16, /* SoftThrSlope */
      1.050000f, /* ShiftScaleAdj */
   },
},

/******************************************************************/
