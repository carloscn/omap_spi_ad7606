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

#ifndef IMG_CORR_GEN_IQ_H_
#define IMG_CORR_GEN_IQ_H_ 1

/** @defgroup IMG_corr_gen_iq */
/** @ingroup  IMG_corr_gen_iq */
/* @{ */

/**
 * @par Description:
 *  The routine performs a generalized correlation with a 1 by M tap   
 *  filter. It can be called N times repetitively to form an arbitrary 
 *  MxN 2D generalized correlation kernel. Input image data, mask data 
 *  and output data are all in Q-format as specified by the inputs
 *  x_qpt, h_qpt and y_qpt respectively. The input image and output 
 *  array are both 32-bit data and the mask array is 16-bit. The 
 *  intermediate correlation sum is accumulated as a 64-bit value in an     
 *  intermediate Q-format. This sum is shifted to get the final output 
 *  in the specified output Q-format. For an imput image with 'pitch' 
 *  columns and a mask of length 'm' the output array must be allocated
 *  for at least (pitch - m) elements.    
 * @par
 *  Overflow may occur while accumulating the intermediate sum in 64-  
 *  bits or while converting the intermediate sum to the final 32-bit sum. 
 *  In either case, no saturation is performed by the routine.                                                      
 * @par
 *    @param x        Pointer to one row of image pixels
 *    @param h        Pointer to a 16-bit linear (1xM) filter mask             
 *    @param y        Output correlation sum(s)
 *    @param m        Length of linear filter (taps)         
 *    @param pitch    Number of columns in input image
 *    @param x_qpt    Q-format of input image array
 *    @param h_qpt    Q-format of mask array
 *    @param y_qpt    Q-format of output array
 *
 *
 * @par Algorithm:
 *  The natural C implementation has no restrictions. The optimized     
 *  intrinsic C code has restrictions as noted in Assumptions below.    
 *
 *
 * @par Assumptions:
 *    - The input, output and mask arrays should not overlap  
 *    - The input, output and mask arrays should be 64-bit aligned
 *    - The input and output Q-formats should follow the relation:
 *      <tt>x_qpt + h_qpt >= y_qpt</tt>
 *    - The length of the filter mask (m) must be a positive multiple of 2
 *    - The number of columns in the input image (pitch) must satisfy
 *      the relation:  <tt>pitch >= m + 2</tt>
 *    - Internal accuracy of the computations is 64-bit. To ensure     
 *      correctness on 32-bit input data, the maximum permissible     
 *      filter gain in terms of bits is 32 (i.e. the cumulative     
 *      sum of the absolute values of the filter coefficients should    
 *      not exceed 2^32 - 1)                                            
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

void IMG_corr_gen_iq
(                             
    const int   *restrict x,  
    const short *restrict h,  
    int         *restrict y,  
    int                   m,  
    int               pitch,  
    int               x_qpt,  
    int               h_qpt,  
    int               y_qpt   
);   

/** @} */

#endif

/* ======================================================================== */
/*  End of file:  IMG_corr_gen_iq.h                                         */
/* ======================================================================== */
