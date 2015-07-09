/**********************************************************************
* Copyright (c) 2014 Qualcomm Technologies, Inc. All Rights Reserved. *
* Qualcomm Technologies Proprietary and Confidential.                 *
**********************************************************************/


#ifndef __HDR_CHROMATIX_H__
#define __HDR_CHROMATIX_H__

/** hdr_chromatix_t
*   @enable: flag to enable hdr
*   @hdr_contrast_control: contrast_control_Q4
*
*   hdr chromatix header
**/
typedef struct {
  int8_t enable;
  /* HDR tuning parameters*/
  uint32_t hdr_contrast_control;
}hdr_chromatix_t;


#endif //__HDR_CHROMATIX_H__
