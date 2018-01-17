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

#ifndef IMG_PERIMETER_16_H_
#define IMG_PERIMETER_16_H_ 1

/** @defgroup IMG_perimeter_16 */
/** @ingroup  IMG_perimeter_16 */
/* @{ */

/**
 * @par Description:
 *  This function returns the boundary pixels of an image. Each call of this 
 *  function calculates one new line of output from a three line window of 
 *  input.                                
 * @par 
 *  The input pointer "in" points to the middle line of a three-line window 
 *  of the image.  The perimeter function scans this window looking for 
 *  pixels in the middle row which are on the perimeter of the image.  A 
 *  pixel is considered to be on the perimeter of the image if the pixel 
 *  itself is non-zero, but one of its neighbors is zero. The function 
 *  returns the total count of perimeter pixels identified.                
 * @par 
 *  This particular implementation evaluates four neighbors for the perimeter 
 *  test:  The neighbors to the left, right, top and bottom.                                                   
 * @par 
 *  Perimeter pixels retain their original grey level in the output.  
 *  Non-perimeter pixels are set to zero in the output. Pixels on the far left 
 *  and right edges of a row are defined *not* being on the perimeter and, as
 *  such, are always forced to zero.                                                        
 * @par 
 *    @param in       Pointer to middle row of three-row input image data
 *    @param cols     Width of the input image data
 *    @param out      Output data pointer 
 *
 *
 * @par Algorithm:
 *  The natural C implementation has no restrictions. The optimized     
 *  intrinsic C code has restrictions as noted in Assumptions below.    
 *
 *
 * @par Assumptions:
 *    - The input and output arrays should not overlap  
 *    - The input and output images must be 64-bit aligned.
 *    - The cols parameter must be a non-zero multiple of 8
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

int IMG_perimeter_16
(
    const unsigned short *restrict in,  /* Input image    */
    int cols,                           /* Width of input */
    unsigned short       *restrict out  /* Output image   */
);

/** @} */

#endif

/* ======================================================================== */
/*  End of file:  IMG_perimeter_16.h                                        */
/* ======================================================================== */
