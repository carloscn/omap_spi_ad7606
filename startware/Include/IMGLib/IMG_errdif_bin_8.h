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

#ifndef  IMG_ERRDIF_BIN_8_H_
#define  IMG_ERRDIF_BIN_8_H_ 1

/** @defgroup IMG_errdif_bin_8 */
/** @ingroup  IMG_errdif_bin_8 */
/* @{ */

/**
 * @par Description:
 *  The code implements the Binary Floyd-Steinberg error diffusion    
 *  filter.  The filter kernel used is illustrated below:                      
 * @verbatim
 
                                   +---+                                 
                                 P | 7 |                                 
                           +---+---+---+                                 
                           | 3 | 5 | 1 |                                 
                           +---+---+---+                                 
   @endverbatim
 * 
 * @par 
 *  Pixels are processed from left-to-right, top-to-bottom.  Each   
 *  pixel is compared against a user-defined threshold.  Pixels     
 *  that are larger than the threshold are set to 255, and pixels   
 *  that are smaller or equal to the threshold are set to 0.  The   
 *  error value for the pixel (eg. the difference between the       
 *  thresholded pixel and its original grey level) is propagated to 
 *  the neighboring pixels according to the filter above.  This     
 *  error propagation diffuses the error over a larger area, hence  
 *  the term "error diffusion."                                     
 * @par 
 *    @param errdif_data  Pointer to an input/output image 
 *    @param cols         Number of columns (Width) 
 *    @param rows         Number of rows    (Height) 
 *    @param err_buf      Row-to-row error buffer
 *    @param thresh       Threshold in range [0x00, 0xFF]
 *
 *
 * @par Algorithm:
 *  The processing of the filter itself is inverted so that the    
 *  errors from previous pixels "propagate into" a given pixel at  
 *  the time the pixel is processed, rather than "accumulate into" 
 *  a pixel as its neighbors are processed.  This allows us to     
 *  keep our image as an 8-bit image, and reduces the number of    
 *  accesses to the image array.  The inverted filter kernel       
 *  performs identically to the kernel's original form.  In this   
 *  form, the weights specify the weighting assigned to the errors 
 *  coming from the neighboring pixels.                            
 * @verbatim
 
                           +---+---+---+                           
                           | 1 | 5 | 3 |                           
                           +---+---+---+                           
                           | 7 | P                                 
                           +---+                                   
   @endverbatim
 * 
 *
 *
 * @par Assumptions:
 *    - "err_buf" must be initialized to zeros for the first call and  
 *      the returned err_buf should be used for any subsequent calls
 *    - The size of "err_buf" should be (cols+1) bytes
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

void IMG_errdif_bin_8
(
    unsigned char *restrict errdif_data, /* Input/Output image ptr       */
    int           cols,                  /* Number of columns (Width)    */
    int           rows,                  /* Number of rows    (Height)   */
    short         *restrict err_buf,     /* row-to-row error buffer.     */
    unsigned char thresh                 /* Threshold from [0x00, 0xFF]  */
);

/** @} */

#endif

/* ======================================================================== */
/*  End of file:  IMG_errdif_bin_8.h                                        */
/* ======================================================================== */
