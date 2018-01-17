/*******************************************************************************
**+--------------------------------------------------------------------------+**
**|                            ****                                          |**
**|                            ****                                          |**
**|                            ******o***                                    |**
**|                      ********_///_****                                   |**
**|                      ***** /_//_/ ****                                   |**
**|                       ** ** (__/ ****                                    |**
**|                           *********                                      |**
**|                            ****                                          |**
**|                            ***                                           |**
**|                                                                          |**
**|        Copyright (c) 2007 - 2013 Texas Instruments Incorporated          |**
**|                                                                          |**
**|              All rights reserved not granted herein.                     |**
**|                                                                          |**
**|                         Limited License.                                 |**
**|                                                                          |**
**|  Texas Instruments Incorporated grants a world-wide, royalty-free,       |**
**|  non-exclusive license under copyrights and patents it now or            |**
**|  hereafter owns or controls to make, have made, use, import, offer to    |**
**|  sell and sell ("Utilize") this software subject to the terms herein.    |**
**|  With respect to the foregoing patent license, such license is granted   |**
**|  solely to the extent that any such patent is necessary to Utilize the   |**
**|  software alone.  The patent license shall not apply to any              |**
**|  combinations which include this software, other than combinations       |**
**|  with devices manufactured by or for TI ("TI Devices").  No hardware     |**
**|  patent is licensed hereunder.                                           |**
**|                                                                          |**
**|  Redistributions must preserve existing copyright notices and            |**
**|  reproduce this license (including the above copyright notice and the    |**
**|  disclaimer and (if applicable) source code license limitations below)   |**
**|  in the documentation and/or other materials provided with the           |**
**|  distribution                                                            |**
**|                                                                          |**
**|  Redistribution and use in binary form, without modification, are        |**
**|  permitted provided that the following conditions are met:               |**
**|                                                                          |**
**|    *  No reverse engineering, decompilation, or disassembly of this      |**
**|  software is permitted with respect to any software provided in binary   |**
**|  form.                                                                   |**
**|                                                                          |**
**|    *  any redistribution and use are licensed by TI for use only with    |**
**|  TI Devices.                                                             |**
**|                                                                          |**
**|    *  Nothing shall obligate TI to provide you with source code for      |**
**|  the software licensed and provided to you in object code.               |**
**|                                                                          |**
**|  If software source code is provided to you, modification and            |**
**|  redistribution of the source code are permitted provided that the       |**
**|  following conditions are met:                                           |**
**|                                                                          |**
**|    *  any redistribution and use of the source code, including any       |**
**|  resulting derivative works, are licensed by TI for use only with TI     |**
**|  Devices.                                                                |**
**|                                                                          |**
**|    *  any redistribution and use of any object code compiled from the    |**
**|  source code and any resulting derivative works, are licensed by TI      |**
**|  for use only with TI Devices.                                           |**
**|                                                                          |**
**|  Neither the name of Texas Instruments Incorporated nor the names of     |**
**|  its suppliers may be used to endorse or promote products derived from   |**
**|  this software without specific prior written permission.                |**
**|                                                                          |**
**|  DISCLAIMER.                                                             |**
**|                                                                          |**
**|  THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY      |**
**|  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE       |**
**|  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR      |**
**|  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TI AND TI'S LICENSORS BE      |**
**|  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR     |**
**|  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF    |**
**|  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR         |**
**|  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,   |**
**|  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE    |**
**|  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,       |**
**|  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                      |**
**+--------------------------------------------------------------------------+**
*******************************************************************************/

#ifndef VLIB_TEST_H_
#define VLIB_TEST_H_ 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "VLIB_types.h"
#include "VLIB_cache.h"

/* Number of significant digits in cycle formula display */
#define vlib_PROFILE_SIG_DIGIT   5

/* Exclusive test parameters */
extern uint8_t    VLIB_Verbose_Test_Level;
extern int32_t    test_cases;
extern int32_t    test_index;
extern int32_t    act_kernel;

extern uint8_t          ref_data_rescale[];
extern uint8_t          ref_data_rescale_cn[];
extern VLIB_F32         inp_data_float[];
extern uint32_t         testMag_out[];
extern uint32_t         testOrien_out[];
extern VLIB_F32         HOGBlks[];
extern const uint8_t    Input_Data_YUYV[];
extern const uint8_t    Input_Data_UYVY[];
extern const uint8_t    Input_Data_YUV_420[];
extern uint8_t          inp_data_L2_i8[];
extern uint16_t         inp_data_L2_i16[];
extern uint32_t         inp_data_L2_i32[];
extern VLIB_F32         HOGBlks_cn[];
extern uint8_t          gTITexasLogo[];

/* Local test buffers */
extern uint16_t    leftImage16[];
extern uint16_t    rightImage16[];
extern uint16_t    currentCost[];
extern uint16_t    minCost[];
extern int8_t      disparity[];
extern int8_t      disparity_cn[];
extern uint8_t     leftImage8[];
extern uint8_t     rightImage8[];
extern int8_t      disparity_i[];
extern int8_t      disparity_c[];
extern uint16_t    scratch16[];
extern int8_t      disparity[];
extern uint8_t     scratch8[];
extern uint16_t    scratch_cn[];

/* Kernel routine type enumeration (must not use explicit numbering) */
enum {
    vlib_KERNEL_OPT, /* Kernel type optimized (C-intrinsics, assembly)*/
    vlib_KERNEL_CN,  /* Kernel type natural C*/
    vlib_KERNEL_CNT
};


/* Kernel pass /fail enumeration */
enum {
    vlib_KERNEL_FAIL = 0,
    vlib_KERNEL_PASS = 1
};


/* Generic Test Utility Prototypes */
void VLIB_print_float     (float num, int printSign);
void VLIB_error_handler   (void);

/* Fractional Math Prototypes */
VLIB_F32 VLIB_getFractional32 (int32_t A, int32_t point, int32_t sign);
VLIB_F32 VLIB_getFractional16 (int16_t A, int32_t point, int32_t sign);

/* Morphological Filtering Test Utility Prototypes */
void VLIB_create32BitPackedBinImage (uint8_t  *pInLuma,
                                     uint16_t inCols,
                                     uint16_t inRows,
                                     uint32_t  *pOutPackedBin,
                                     uint8_t threshold);
void VLIB_unpack32BitPackedBinImage (uint32_t  *pPackedBin,
                                     uint16_t img_w,
                                     uint16_t img_h,
                                     uint8_t  *pUnpackedBin);
void VLIB_display_image_bits        (uint8_t  *img,
                                     int32_t m,
                                     int32_t n);

/* Legendre Moments Test Utility Prototypes */
void VLIB_LegendreMoments_imageReconstruct (VLIB_F32 *rIm,
                                            int32_t im_h,
                                            int32_t im_w,
                                            int32_t order,
                                            int16_t *Pr,
                                            int16_t *Pc,
                                            int16_t *L);

/* Connected Components Test Utility Prototypes */
void VLIB_printErrCode(int32_t status);

/* Standardized assertion utility */
void VLIB_assert (int assertion, char *err_string);

#endif /* VLIB_TEST_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_test.h                                            */
/* ======================================================================== */

