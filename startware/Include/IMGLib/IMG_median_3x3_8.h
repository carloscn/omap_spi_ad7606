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

#ifndef IMG_MEDIAN_3X3_8_H_
#define IMG_MEDIAN_3X3_8_H_ 1

/** @defgroup IMG_median_3x3_8 */
/** @ingroup  IMG_median_3x3_8 */
/* @{ */

/**
 * @par Description:
 *  This kernel performs a 3x3 median filter operation on 8-bit        
 *  unsigned image pixels. The median filter comes under the class       
 *  of non-linear signal processing algorithms.
 * @par 
 *  Rather than replace the grey level at a pixel by a weighted     
 *  average of the nine pixels including and surrounding it, the    
 *  grey level at each pixel is replaced by the median of the nine  
 *  values.  The median of a set of nine numbers is the middle      
 *  element so that half of the elements in the list are larger and 
 *  half are smaller.  Median filters remove the effects of extreme 
 *  values from data, such as salt and pepper noise. Using a large
 *  set of values may result in unacceptable blurring of sharp edges 
 *  in the original image.                                             
 * @par 
 *    @param i_data   Input image containing 3 rows (i.e., size of 3 x n)
 *    @param n        Width of input image in pixels                              
 *    @param o_data   Output image containing 1 row (i.e., size of 1 x n)
 *
 *
 * @par Algorithm:
 *  This implementation uses an incremental sorting technique to        
 *  greatly reduce the number of compares and exchanges necessary       
 *  to sort the image pixels.
 * @par 
 *  The main loop reads three new pixels from the input image each      
 *  iteration.  These three pixels form the right edge of the filter    
 *  mask.  The filter data from the previous iteration is "slid         
 *  over" by one pixel to form the complete 3x3 mask.
 * @par 
 *  Each 3-pixel "column" is sorted as it is read in from the image,    
 *  resulting in a "lo", "medium" and "hi" pixel value for the          
 *  column.  This results in a 3x3 filter mask with sorted columns      
 *  or three rows -- a row of "minimums", a row of "middle values",     
 *  and a row of "maximums".
 * @par 
 *  The median filter operates from this partially ordered mask.        
 *  It finds the smallest element in the row of "maximums",             
 *  the middle element in the row of "middle values", and               
 *  the largest element in the row of "minimums".  The median           
 *  value of these three values is the median for the entire 3x3        
 *  mask.
 * @par 
 *  This process minimizes compares, as the whole mask does not         
 *  need to be sorted between iterations.  Rather, the partial          
 *  ordering for two of the three columns from one iteration is         
 *  used directly for the next iteration.
 * @par 
 *  The natural C implementation has no restrictions. The optimized     
 *  intrinsic C code has restrictions as noted in Assumptions below.    
 *
 *
 * @par Assumptions:
 *    - The input array and output array should not overlap  
 *    - Both input and output arrays must be 32-bit aligned
 *    - The minimum value for width of input image 'n' is 4  
 *    - The width of input image 'n' must be a multiple of 4
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

void IMG_median_3x3_8
(
    const unsigned char *restrict i_data,
    int                                n,
    unsigned char       *restrict o_data
);

/** @} */

#endif

/* ======================================================================== */
/*  End of file:  IMG_median_3x3_8.h                                        */
/* ------------------------------------------------------------------------ */
