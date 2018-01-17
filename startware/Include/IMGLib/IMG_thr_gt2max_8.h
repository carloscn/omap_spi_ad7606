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

#ifndef IMG_THR_GT2MAX_8_H_
#define IMG_THR_GT2MAX_8_H_ 1

/** @defgroup IMG_thr_gt2max_8 */
/** @ingroup  IMG_thr_gt2max_8 */
/* @{ */

/**
 * @par Description:
 *  This kernel performs a thresholding operation on the input image "in_data" 
 *  with dimensions as specified by the input arguments "cols" and "rows". The 
 *  thresholded pixels are written to the output image pointed to by "out_data".  
 *  The input and output images are of the same dimensions.
 * @par 
 *  Pixels with values equal-to or below the threshold are passed out unmodified. 
 *  Pixels with values greater than the threshold are set to the maximum unsigned 
 *  8-bit value (255) in the output image.                
 * @par 
 *    @param in_data    Input image pointer
 *    @param out_data   Output image pointer
 *    @param cols       Number of columns in the image
 *    @param rows       Number of rows in the image
 *    @param threshold  The (unsigned 8-bit) threshold
 *
 *
 * @par Algorithm:
 *  The thresholding function is illustrated in the transfer function diagram
 *  below:
 * @verbatim

                 255_|          _________                              
                     |         |                                       
                     |         |                                       
            O        |         |                                       
            U        |         |                                       
            T    th _|. . . . .|                                       
            P        |        /.                                       
            U        |      /  .                                       
            T        |    /    .                                       
                     |  /      .                                       
                   0_|/________.__________                             
                     |         |        |                              
                     0        th       255                             
                                                                     
                             INPUT                                     
   @endverbatim
 * 
 * @par 
 *  The main thresholding loop is manually unrolled four times.  The compiler is
 *  instructed to unroll by an additional factor of four, yielding a total unroll       
 *  factor of 16.  
 * @par 
 *  A packed-data processing techniques is used to allow the processing of four 
 *  pixels in parallel.  The _amem4_const() intrinsic brings in four pixels,
 *  designated p0 thru p3.  These pixels are packed into an unsigned integer 
 *  variable p3p2p1p0 as illustrated below:                              
 * @verbatim
                                                                     
                         31  24   16    8    0                        
                         +----+----+----+----+                       
                p3p2p1p0 | p3 | p2 | p1 | p0 |                       
                         +----+----+----+----+                       
   @endverbatim
 * @par 
 *  (Note that this illustration assumes a little endian memory configuration).
 *  We compare this packed word to a (4x) packed copy of the threshold.  
 *  The packed threshold contains four copies of the threshold value, one per 
 *  byte:                                  
 * @verbatim
                                                                   
                       31  24   16    8    0                       
                         +----+----+----+----+                      
                thththth | th | th | th | th |                      
                         +----+----+----+----+
   @endverbatim
 * @par 
 *  We compare using the intrinsic _cmpgtu4().  The comparison results are 
 *  then expanded to masks using _xpnd4().  The result is a four-byte mask
 *  (x3210) which contains 0xFF in bytes that are greater than the threshold, 
 *  and 0x00 in bytes that are less than or equal to the threshold.                       
 * @par 
 *  To complete the thresholding process, we compute the logical OR  
 *  between our original pixel values and the mask.  This forces     
 *  values above the threshold to 0xFF, and leaves the other values  
 *  unmodified.  The four pixels are then written with a single _amem4().
 * @par 
 *  In this version of the code, we rely on the compiler to unroll   
 *  the loop 4x (as noted above), and convert the _amem4_const() and 
 *  _amem4() calls into _amemd8_const()/_amemd8() as part of its     
 *  automatic optimizations.                                         
 * @par 
 *  The natural C implementation has no restrictions. The optimized     
 *  intrinsic C code has restrictions as noted in Assumptions below.    
 *
 *
 * @par Assumptions:
 *    - The input array and output array should not overlap  
 *    - Both input and output arrays must be 64-bit aligned
 *    - The number of image pixels (cols x rows) must be a multiple of 16
 *
 *
 * @par Implementation Notes:
 *    - This code is fully interruptible
 *    - This code is compatible with C64x+ processors
 *    - This code is endian neutral
 *
 *
 * @par Benchmarks:
 *  See IMGLIB_Test_Report.html for cycle and memory information.
 *
 */

void IMG_thr_gt2max_8
(
    const unsigned char *in_data,                /*  Input image data    */
    unsigned char       *restrict out_data,      /*  Output image data   */
    short cols, short rows,                      /*  Image dimensions    */
    unsigned char       threshold                /*  Threshold value     */
);

/** @} */

#endif

/* ======================================================================== */
/*  End of file:  IMG_thr_gt2max_8.h                                        */
/* ======================================================================== */
