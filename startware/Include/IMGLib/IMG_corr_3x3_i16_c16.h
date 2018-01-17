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

#ifndef  IMG_CORR_3X3_I16_C16_H_
#define  IMG_CORR_3X3_I16_C16_H_ 1

/** @defgroup IMG_corr_3x3_i16_c16 */
/** @ingroup  IMG_corr_3x3_i16_c16 */
/* @{ */

/**
 * @par Description:
 *  The convolution kernel accepts three rows of 'pitch' input pixels 
 *  and produces one row of 'width' output pixels using the 3 pixel
 *  square filter mask provided on input. 
 * @par
 *  The correlation sum is calculated as a point by point multiplication 
 *  of the 3x3 mask with the input image.  The 9 resulting multiplications 
 *  are summed together to produce a 40-bit intermediate sum.  This sum is 
 *  used to produce the 32-bit output value that is subsequently stored in 
 *  the output array.  Overflow and saturation of the accumulated sum are 
 *  not explicitly prevented, however assumptions may be made on filter 
 *  gain to avoid them.
 * @par
 *  The mask is moved one column at a time, advancing the mask over    
 *  the entire image until the entire 'width' is covered. The mask and the 
 *  input image pixels are both provided as 16-bit unsigned values, while 
 *  the output pixels are 32-bit signed. The mask chosen for correlation is 
 *  typically part of the input image or another image.                                      
 * @par
 *    @param imgin_ptr    Pointer to an input image of 16-bit unsigned pixels
 *    @param imgout_ptr   Pointer to an output image of 32-bit pixels         
 *    @param mask_ptr     Pointer to a 16-bit unsigned filter mask             
 *    @param pitch        Number of columns in the image             
 *    @param width        Number of output pixels                    
 *
 *
 * @par Algorithm:
 *  The natural C implementation has no restrictions. The optimized     
 *  intrinsic C code has restrictions as noted in Assumptions below.    
 *
 *
 * @par Assumptions:
 *    - The input array and output array should not overlap  
 *    - The input, output and mask arrays have no alignment requirements
 *    - The image pitch must be greater than or equal to the width 
 *    - The width parameter must be a non-zero multiple of 4
 *
 *
 * @par Implementation Notes:
 *    - This code is fully interruptible
 *    - This code is compatible with C64x+ processors
 *
 *
 * @par Benchmarks:
 *  See IMGLIB_Test_Report.html for cycle and memory information.
 *
 */

void IMG_corr_3x3_i16_c16
(
    const unsigned short           *imgin_ptr, 
          unsigned int    *restrict imgout_ptr, 
    const unsigned short            *mask_ptr, 
          short                     pitch,     
          short                     width     
);

/** @} */

#endif

/* ======================================================================== */
/*  End of file:  IMG_corr_3x3_i16_c16.h                                    */
/* ======================================================================== */

