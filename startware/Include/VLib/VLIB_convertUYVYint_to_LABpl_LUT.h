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

#ifndef VLIB_CONVERTUYVYINT_TO_LABPL_LUT_H_
#define VLIB_CONVERTUYVYINT_TO_LABPL_LUT_H_ 1

#include "common/VLIB_types.h"

/** @defgroup VLIB_convertUYVYint_to_LABpl_LUT */
/** @ingroup  VLIB_convertUYVYint_to_LABpl_LUT */
/* @{ */

/**
 * @par Introduction and Use Cases:
 *   This function is a fast approximation to the function \ref VLIB_convertUYVYint_to_LABpl. Lab color space is
 *   an important color-opponent color space. It is derived from the CIE XYZ color space through a non-linear
 *   compression, which assures perceptual uniformity. If the input data is in the interleaved YUV422 color
 *   format, this function transforms the data into the LAB format and separates the three color channels into
 *   separate buffers, color planes.
 *
 * @par Description:
 *   This function calculates LAB color space representation of pixels
 *   represented in interleaved YUV422 format based on LUT.
 * @par
 *   The calculated values are stored as 16-bit values.The approximate relationship
 *   to the floating-point values calculated by the VLIB function
 *   \ref VLIB_convertUYVYint_to_LABpl is as follows:
 * @verbatim
    L = (uint16_t)(439.832L_f + 3518.66 + 0.5);
    a = (uint16_t)(232.394a_f + 29513.99 + 0.5);
    b = (uint16_t)(221.402b_f + 29225.07 + 0.5);
@endverbatim
 * @par
 *   The conversion back to the floating pt. representation is given by:
 * @verbatim
    L_f = (L - 3518.66)/439.832;
    a_f = (a - 29513.99)/232.394;
    b_f = (b - 29225.07)/221.402;
@endverbatim
 * @par
 *   Parameter d defines the sparsity of the LUT  each of three dimensions of the LUT is subsampled by a
 *   factor of ~2d. The size of the LUT in memory is determined by the following equation:
 *   4 x 2 x ((256 >> d) + 1)^3 bytes. The associated memory / accuracy trade-off is given in the following Table:
 * @verbatim
 |========+============+============+==========+=========+==========+=========+==========+=========|
 |        |            |            |   0 < L < 65536    |   0 < a < 65536    |   0 < b < 65536    |
 |========+============+============+==========+=========+==========+=========+==========+=========|
 | Param  | Decimation | Memory for | Mean abs | Max abs | Mean abs | Max abs | Mean abs | Max abs |
 |   d    |   Factor   |    LUT     |   err    |   err   |   err    |   err   |   err    |   err   |
 |========+============+============+==========+=========+==========+=========+==========+=========|
 |   0    |      1     |  129 MB    |    0     |    0    |    0     |    0    |    0     |    0    |
 |   1    |    2x2x2   |   16 MB    |   0.43   |    15   |   0.98   |    55   |   0.7    |    28   |
 |   2    |    4x4x4   |    2 MB    |   1.72   |    46   |   4.23   |   169   |   2.97   |    99   |
 |   3    |    8x8x8   |  281 KB    |   7.51   |   165   |   16.6   |   521   |   12.1   |   283   |
 |   4    |   16x16x16 |   38 KB    |   30.7   |   597   |   61.3   |  1705   |   46.9   |   699   |
 |========+============+============+==========+=========+==========+=========+==========+=========|
@endverbatim
 * @par
 *   The pointer LabExt points to the LUT, which can be generated using the
 *   initialization function \ref VLIB_initUYVYint_to_LABpl_LUT.
 * @par
 *   The matrix coefficients specified by the array coeff are typically as shown in
 *   Equation (a) for the case of RGB levels that correspond the 219-level
 *   range of Y. Expected ranges are [16..235] for Y and [16..240] for Cb and Cr.
 *   - coeff[] = { 0x2000, 0x2BDD, -0x0AC5, -0x1658, 0x3770 }; (a)
 * @par
 *   Alternatively, as shown in Equation (b), for the case of RGB conversion with
 *   the 219-level range of Y expanded to fill the full RGB dynamic range.
 *   Expected ranges are [16..235] for Y and [16..240] for Cb and Cr.
 *   - coeff[] = { 0x2543, 0x3313, -0x0C8A, -0x1A04, 0x408D }; (b)
 * @par
 *   The white point specification is used in the normalization step of the
 *   intermediate XYZ color space. A common value is a D65 value given by Equation(c)
 *   - float whitePoint[3] = {0.950456, 1.0, 1.088754}; (c)
 *
 * @par
 *   @param [in]  *yc         Interleaved luma/chroma                          (UQ8.0)
 *   @param [in]   width      Width of input image (number of luma pixels)     (in pixels)
 *   @param [in]   pitch      Pitch of input image (number of luma pixels)     (in pixels)
 *   @param [in]   height     Height of input image(number of luma pixels)     (in pixels)
 *   @param [in]   d          Defines the LUT sparsity: 1/2^(3d)               (valid range = 0-4)
 *   @param [in]  *LabExt     Pointer to the Lab LUT                           (UQ16.0)
 *   @param [out] *L          Pointer to L plane                               (UQ16.0)
 *   @param [out] *a          Pointer to A plane                               (UQ16.0)
 *   @param [out] *b          Pointer to B plane                               (UQ16.0)
 *
 * @par Assumptions
 *  - LabExt should be 8 byte aligned.
 *  - LabExt should be of size: 4 x 2 x ((256 >> d) + 1)^3 bytes
 *  - All other arrays should be 2 byte aligned.
 *  - width should be a multiple of 2, and greater than 0
 *  - pitch should be a multiple of 2, >= width
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 * @par References:
 *  -# <em> Digital Image Processing </em> by R.C.Gonzales and R.E.Woods, Prentice-Hall, 2007
 *
 */
int32_t VLIB_convertUYVYint_to_LABpl_LUT(const uint8_t *restrict yc,
                                         int32_t width,
                                         int32_t pitch,
                                         int32_t height,
                                         int32_t d,
                                         const uint16_t *restrict LabExt,
                                         uint16_t *restrict L,
                                         uint16_t *restrict a,
                                         uint16_t *restrict b);

/** @} */
#endif /* VLIB_CONVERTUYVYINT_TO_LABPL_LUT_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_convertUYVYint_to_LABpl_LUT.h                        */
/* ======================================================================== */

