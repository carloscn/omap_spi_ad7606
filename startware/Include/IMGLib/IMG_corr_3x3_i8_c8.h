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

#ifndef IMG_CORR_3X3_I8_C8_H_
#define IMG_CORR_3X3_I8_C8_H_ 1

/** @defgroup IMG_corr_3x3_i8_c8 */
/** @ingroup  IMG_corr_3x3_i8_c8 */
/* @{ */

/**
 * @par Description:
 *  The convolution kernel accepts three rows of 'pitch' input pixels 
 *  and produces one row of 'width' output pixels using the 3 pixel
 *  square filter mask provided on input. 
 * @par
 *  The correlation sum is calculated as a point by point multiplication 
 *  of the 3x3 mask with the input image.  The 9 resulting multiplications 
 *  are summed together to produce a 32-bit sum.  This 32-bit sum is rounded 
 *  using the input rounding constant and shifted before being stored to the 
 *  output array.  
 * @par
 *  The mask is moved one column at a time, advancing the mask over    
 *  the entire image until the entire 'width' is covered. When 'width' is 
 *  larger than 'pitch', multiple rows are processed.  An application may 
 *  call this kernel once per row to calculate the correlation for an entire 
 *  image, or the kernel may be invoked for multiple rows at simultaneously.
 *  In the latter case, the two outputs at the end of each row will have 
 *  meaningless values and the application will have to account for this 
 *  when interpreting the results.       
 * @par
 *  The mask and input image are provided as 8-bit unsigned values.  
 *  The output pixels will be 32-bit signed values.  The mask chosen for 
 *  correlation is typically part of the input image or another image.
 * @par
 *    @param imgin_ptr    Pointer 8-bit input image 
 *    @param imgout_ptr   Pointer 32-bit output image 
 *    @param width        Number of output pixels                    
 *    @param pitch        Number of columns in the image             
 *    @param mask_ptr     Pointer to 8-bit filter mask  
 *    @param shift        User specified right shift on sum
 *    @param round        User specified round value
 *
 *
 * @par Algorithm:
 *  The natural C implementation has no restrictions. The optimized     
 *  intrinsic C code has restrictions as noted in Assumptions below.    
 *
 *
 * @par Assumptions:
 *    - The input array and output array should not overlap  
 *    - The mask array has no alignment requirements
 *    - The input and output image arrays have no alignment requirements
 *    - The image pitch must must be a multiple of 2 greater than 2
 *    - The width parameter must be a non-zero multiple of 4
 *    - The image pitch must be greater than or equal to the width 
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

void IMG_corr_3x3_i8_c8
(
    const unsigned char           *imgin_ptr,  
          int           *restrict imgout_ptr,  
          short                   width,       
          short                   pitch,       
    const unsigned char           *mask_ptr,
          short                   shift,
          int                     round         
);

/** @} */

#endif

/* ======================================================================== */
/*  End of file:  IMG_corr_3x3_i8_c8.h                                      */
/* ======================================================================== */
