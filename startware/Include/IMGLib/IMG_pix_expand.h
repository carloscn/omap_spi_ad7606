/* ======================================================================== *
 * IMGLIB -- TI Image and Video Processing Library                          *
 *                                                                          *
 *                                                                          *
 * Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/   *
 *                                                                          *
 *                                                                          *
 *  Redistribution and use in source and binary forms, with or without      *
 *  modification, are permitted provided that the following conditions      *
 *  are met:                                                                *
 *                                                                          *
 *    Redistributions of source code must retain the above copyright        *
 *    notice, this list of conditions and the following disclaimer.         *
 *                                                                          *
 *    Redistributions in binary form must reproduce the above copyright     *
 *    notice, this list of conditions and the following disclaimer in the   *
 *    documentation and/or other materials provided with the                *
 *    distribution.                                                         *
 *                                                                          *
 *    Neither the name of Texas Instruments Incorporated nor the names of   *
 *    its contributors may be used to endorse or promote products derived   *
 *    from this software without specific prior written permission.         *
 *                                                                          *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS     *
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT       *
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR   *
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT    *
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   *
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT        *
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,   *
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY   *
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT     *
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE   *
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.    *
 * ======================================================================== */

#ifndef IMG_PIX_EXPAND_H_
#define IMG_PIX_EXPAND_H_ 1

/** @defgroup IMG_pix_expand */
/** @ingroup  IMG_pix_expand */
/* @{ */

/**
 * @par Description:
 *    Reads an array of unsigned 8-bit values and store them to a         
 *    16-bit array.  This step is often used as the first step            
 *    when processing pixels or other low-precision data at 16-bit        
 *    intermediate precision.                                             
 * @par 
 *    @param n            Number of elements
 *    @param in_data      Input data
 *    @param out_data     Output data
 *                                                                          
 *                                                                          
 * @par Assumptions:
 *    - The input array and output arrays should be 64-bit aligned
 *    - The input must be at least 16 elements long and contain a
 *      multiple of 16 elements.                                           
 *
 *
 * @par Implementation Notes:
 *    - This code is fully interruptible
 *    - This code is compatible with C64x+ processors
 *
 *
 * @par Benchmarks:
 *   See IMGLIB_Test_Report.html for cycle and memory information.
 *
 */


void IMG_pix_expand
(
    int n,
    const unsigned char *restrict in_data,
    short               *restrict out_data
);

/** @} */

#endif

/* ======================================================================== */
/*  End of file:  IMG_pix_expand.h                                          */
/* ======================================================================== */
