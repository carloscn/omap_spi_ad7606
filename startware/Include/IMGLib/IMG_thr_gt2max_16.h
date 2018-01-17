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

#ifndef IMG_THR_GT2MAX_16_H_
#define IMG_THR_GT2MAX_16_H_ 1

/** @defgroup IMG_thr_gt2max_16 */
/** @ingroup  IMG_thr_gt2max_16 */
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
 *  16-bit value (65535) in the output image.                
 * @par 
 *    @param in_data    Input image pointer
 *    @param out_data   Output image pointer
 *    @param cols       Number of columns in the image
 *    @param rows       Number of rows in the image
 *    @param threshold  The (unsigned 16-bit) threshold
 *
 *
 * @par Algorithm:
 *  The thresholding function is illustrated in the transfer function diagram
 *  below:
 * @verbatim

              65535_|          _________                               
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
                    0        th       65535                            
                                                                       
                            INPUT                                      
   @endverbatim
 * 
 * @par 
 *  The main thresholding loop is unrolled sixteen times.  Packed-data 
 *  processing techniques allow us to process all 16 pixels in parallel.                    
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
                                                                       
void IMG_thr_gt2max_16
(
    const unsigned short *restrict in_data,      /*  Input image data    */
          unsigned short *restrict out_data,     /*  Output image data   */
                   short           cols,         /*  Image columns       */ 
                   short           rows,         /*  Image rows          */
          unsigned short           threshold     /*  Threshold value     */
);

/** @} */

#endif

/*========================================================================= */
/*   End of file:  IMG_thr_gt2max_16.h                                      */
/* ======================================================================== */

