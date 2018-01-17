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

#ifndef VLIB_ORB_COMPUTERBRIEF_H_
#define VLIB_ORB_COMPUTERBRIEF_H_ 1

#include "common/VLIB_types.h"
#include "common/VLIB_orb.h"

/** @defgroup VLIB_ORB_computeRBrief */
/** @ingroup  VLIB_ORB_computeRBrief */
/* @{ */

/**
 * @par Description:
 *  Computes the brief pattern for each feature and populates the output->features[i].descriptor parameter.
 *  This function can be called after the fast corners are detected so that the feature list is populated.
 *  Additionally, since this function requires angles to be defined for each feature, \ref VLIB_ORB_computeOrientation
 *  should have been run.  Finally, this function requires that an integral image is available in the input->integralImage
 *  pointer, so \ref VLIB_integralImage8 should have been run.
 *
 * @par
 *  @param [in]  *parameters   The parameters for ORB
 *  @param [in]  *input        The input data for ORB - Must be double-word(64-bit) aligned.
 *  @param [out] *output       The output data for ORB - Must be double-word(64-bit) aligned.
 *
 * @par Assumptions:
 * - Pointer to the input data and output data must be double-word(64-bit) aligned.
 * - One of the following FAST corner detectors is run prior to this function:
 *     - @ref VLIB_afast9_detectCorners
 *     - @ref VLIB_originalfast9_detectCorners
 *     - @ref VLIB_afast12_detectCorners
 *     - @ref VLIB_originalfast12_detectCorners
 * - \ref VLIB_ORB_computeOrientation should be run before running this function.
 * - \ref VLIB_integralImage8 should be run before running this function.
 * - The list of features passed to this function should NOT be within the border area of the image (w/in 16 pixels * 1.42 of the edge
 *   of the image) since this function uses an orientation independent 32x32 patch size around the feature to compute descriptor.
 *
 * @par Implementation Notes:
 * - This code is compatible with C6XXX fixed point processors.
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 */
CORBResult VLIB_ORB_computeRBrief(const CORBParameters *parameters,
                                  const CORBInput *input,
                                  CORBOutput *output);


/** @} */
#endif /* VLIB_ORB_COMPUTERBRIEF_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_ORB_computeRBrief.h                                  */
/* ======================================================================== */

