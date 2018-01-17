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
**|        Copyright (c) 2007 - 2014 Texas Instruments Incorporated          |**
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
/*============================================================================*/
/*                                                                            */
/*     TEXAS INSTRUMENTS, INC.                                                */
/*                                                                            */
/*     NAME                                                                   */
/*        histogram                                                           */
/*                                                                            */
/*     REVISION HISTORY                                                       */
/*        8/1/2012..Original version written ................ Adarsh Nagaraja */
/*                                                                            */
/*     USAGE                                                                  */
/*        This routine is C-callable and can be called as:                    */
/*                                                                            */
/*        void VLIB_imagerescaling(unsigned char *pIn,                        */
/*                       unsigned char *pOut,                                 */
/*                       unsigned short nFactor,                              */
/*                       unsigned short width,                                */
/*                       unsigned short height)                               */
/*           (See the C compiler reference guide.)                            */
/*                                                                            */
/*     DESCRIPTION                                                            */
/*        This code takes an input image pointer of 8 bit and returns the     */
/*        image of rescaled size as mentioned by the nFactor from the given   */
/*        width and height                                                    */
/*                                                                            */
/*     ASSUMPTIONS                                                            */
/*        The input array of image data must be aligned to a 4 byte boundary  */
/*        and n must be a multiple of 8. The maximum width and height of the  */
/*        input or output image has an upper limit. Maximum dimension         */
/*        supported is 1920. Scaling factor is represented                    */
/*        in fixed format with 1<<12 as the float to fixed conversion         */
/*        nFactor of 4096(1<<12) means, no scaling up/down                    */
/*        nFactor of 2048(1<<11) means, scaling UP by 2                       */
/*        nFactor of 8192(1<<13) means, scaling DOWN by 2                     */
/*        nFactor of 2703(0.66<<12) means, scaling UP by 2/3                  */
/*                                                                            */
/*     MEMORY NOTE                                                            */
/*        No bank conflicts should occur in this code in the optimized        */
/*        forms of hand assembly and serial assembly.                         */
/*                                                                            */
/*     TECHNIQUES                                                             */
/*        This code implements the bi-linear interpolation to scale up/down   */
/*        by nFactor. The algorith calculates the x and y location of the     */
/*        pixels in the image, which needs to be sampled. For non-integer     */
/*        locations, the floor and ceil approximation is used to get the      */
/*        round off location. The weights for the pixels to be interpolated   */
/*        are also calculated with 4096(1<<12) approximation for float to     */
/*        fixed conversion of the weights. A final for loop for all the re-   */
/*        scaled positions fills the bi-linear interpolated pixels            */
/*     SOURCE                                                                 */
/*         Optimized c code based on assembly code loop developed by          */
/*         Adarsh Nagaraja, 2012                                              */
/*                                                                            */
/*============================================================================*/
/*      Copyright (C) 1997-1999 Texas Instruments Incorporated.               */
/*                      All Rights Reserved                                   */
/*============================================================================*/
#ifndef VLIB_IMAGE_RESCALE_H_
#define VLIB_IMAGE_RESCALE_H_ 1

#include "common/VLIB_types.h"
#include "VLIB_image_rescale_types.h"

/** @defgroup VLIB_image_rescale*/
/** @ingroup  VLIB_image_rescale */
/* @{ */

/**
 * @par Description
 *  This function scales scales the input image to a different resolution.
 *
 * @par
 *   @param [in]  pIn[]           8-bit input image array to one of the image channels (UQ8.0)
 *   @param [out] pOut[]          8-bit output array to one of the image channels (UQ8.0)
 *   @param [in]  nFactor         Fixed point approximation of scaling factor (Luma only, UQ16.0) Scaling factor = 4096/nFactor
 *   @param [in]  inCols          Image width in number of pixels (UQ16.0)
 *   @param [in]  inRows          Image height in number of pixels (UQ16.0)
 *   @param [in]  color_format    Color format option (SQ31.0) \n
 *                                - 0: COLOR_FORMAT_YUV_422_YUYV \n
 *                                - 1: COLOR_FORMAT_YUV_422_UYVY \n
 *                                - 3: COLOR_FORMAT_LUMA_ONLY \n
 *                                - All other values reserved (not supported)
 *
 * @par Limitations
 *    - When \c color_format is <b> 0 : COLOR_FORMAT_YUV_422_YUYV </b> or <b> 1 : COLOR_FORMAT_YUV_422_UYVY </b>:
 *        - \c nFactor is ignored, only 1/2 downscale in each direction is supported (output is 1/4 pixels as input)
 *        - \c pIn aligned to an 8 byte boundary
 *        - \c pOut aligned to an 4 byte boundary
 *        - \c inCols is a multiple of 8
 *        - \c inRows is a multiple of 2
 *    - When \c color_format is <b> 3 : COLOR_FORMAT_LUMA_ONLY </b>:
 *        - \c nFactor is supported, such that output_dimension = input_dimention*4096/nFactor
 *        - Upscaling and downscaling are supported
 *        - Max dimension of output width or height when color_format is 1920
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 */
void    VLIB_image_rescale(const uint8_t pIn[],
                           uint8_t pOut[],
                           uint16_t nFactor,
                           uint16_t inCols,
                           uint16_t inRows,
                           int32_t color_format);

/** @} */
#endif


/* ======================================================================== */
/*  End of file:  vlib_image_rescale.h                                      */
/* ======================================================================== */

