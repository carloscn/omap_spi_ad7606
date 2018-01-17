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

#ifndef IMG_CORR_11X11_I8_C16S_H_
#define IMG_CORR_11X11_I8_C16S_H_ 1

/** @defgroup IMG_corr_11x11_i8_c16s */
/** @ingroup  IMG_corr_11x11_i8_c16s */
/* @{ */

/**
 * @par Description:
 *  The convolution kernel accepts eleven rows of 'pitch' input pixels 
 *  and produces one row of 'width' output pixels using the 11 pixel
 *  square filter mask provided on input. 
 * @par
 *  The correlation sum is calculated as a point by point multiplication 
 *  of the 11x11 mask with the input image.  The 121 resulting multiplications 
 *  are summed together to produce a 32-bit sum.  This 32-bit sum is stored 
 *  in the output array.  Overflow of the accumulated sum is not possible.
 * @par
 *  The mask is moved one column at a time, advancing the mask over    
 *  the entire image until the entire 'width' is covered. The mask is provided 
 *  as 16-bit signed values and the input image pixels are 8-bit unsigned.
 *  The output pixels will be 32-bit signed values.  The mask chosen for 
 *  correlation is typically part of the input image or another image.                                      
 * @par
 *    @param imgin_ptr    Pointer to an input image of 16-bit pixels
 *    @param imgout_ptr   Pointer to an output image of 32-bit pixels         
 *    @param width        Number of output pixels                    
 *    @param pitch        Number of columns in the image             
 *    @param mask_ptr     Pointer to a 16-bit filter mask             
 *
 *
 * @par Algorithm:
 *  The natural C implementation has no restrictions. The optimized     
 *  intrinsic C code has restrictions as noted in Assumptions below.    
 *
 *
 * @par Assumptions:
 *    - The input array and output array should not overlap  
 *    - The output array must be 64-bit aligned
 *    - The mask arrays must be 16-bit aligned
 *    - The input image array has no alignment requirements
 *    - The image pitch must be greater than or equal to the width 
 *    - The width parameter must be a non-zero multiple of 2
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
                                                                       
void IMG_corr_11x11_i8_c16s
(
    const unsigned char    *restrict  imgin_ptr,
                   int     *restrict imgout_ptr,
                   short                  width, 
                   short                  pitch, 
    const          short   *restrict   mask_ptr
);

/** @} */

#endif

/* ======================================================================== */
/*  End of file:  IMG_corr_11x11_i8_c16s.h                                  */
/* ======================================================================== */
