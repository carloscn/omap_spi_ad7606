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

#ifndef  IMG_WAVE_HORZ_H_
#define  IMG_WAVE_HORZ_H_ 1

/** @defgroup IMG_wave_horz */
/** @ingroup  IMG_wave_horz */
/* @{ */

/**
 * @par Description:
 *    This kernel performs a 1D Periodic Orthogonal Wavelet decomposition.
 *    This also performs athe row decomposition in a 2D wavelet            
 *    transform. An in put signal x[n] is first low pass and high pass     
 *    filterd and decimated by two. This results in a reference signal     
 *    r1[n] which is the decimated output obtained by dropping the odd     
 *    samples of the low pass filtered output and a detail signal d[n]     
 *    obtained by dropping the odd samples of the high-pass output. A      
 *    circular convolution algorithm is implemented and hence the wavelet 
 *    transform is periodic. The reference signal and the detail       
 *    signal are half the size of the original signal. The reference       
 *    signal may then be iterated again to perform another scale of        
 *    multi-resolution analysis.                                           
 * @par 
 *    @param iptr       Input row of data                                 
 *    @param qmf        Qmf filter-bank for Low-Pass                      
 *    @param filter     Mirror qmf filter bank for High-pass            
 *    @param optr       Output row of detailed/reference decimated outputs
 *    @param ish_x_dim  Width of the input row
 *
 *
 * @par Algorithm:
 *    The main idea behind the optimized C code is to issue one set of   
 *    reads to the x array and to perform low-pass and high pass filtering  
 *    together and to perfrom the filtering operations together to maximize 
 *    the number of multiplies.  The last 6 elements of the low-pass filter 
 *    and the first 6 elements of the high pass filter use the same input   
 *    This is used to appropraitely change the output pointer to the low    
 *    pass filter after 6 iterations. However for the first six iterations  
 *    pointer wrap-around can occurr and hence this creates a dependency.   
 *    Pre-reading those 6 values outside the array prevents the checks that 
 *    introduce this dependency. In addtion the input data is read as word  
 *    wide quantities and the low-pass and high-pass filter coefficients    
 *    are stored in registers allowing for the input loop to be completely  
 *    unrolled. Thus the intrinsic C code has only one loop. A predication  
 *    register is used to reset the low-pass output pointer after three     
 *    iterations. The merging of the loops in this fashion allows for the   
 *    maximum number of multiplies with the minimum number of reads.        
 *
 *
 * @par Assumptions:
 *    - This kernel places no restrictions on the alignment of its input
 *
 *
 * @par Implementation Notes:
 *    - This kernel uses the Daubechies D4 filter bank for analysis with 4 
 *      vansishing moments. Hence the length of the analyzing low-pass and
 *      high pass filters is 8
 *    - The optimized kernel should not have any bank conflicts
 *    - This code is compatible with C64x+ processors
 *
 *
 * @par Benchmarks:
 *  See IMGLIB_Test_Report.html for cycle and memory information.
 *
 */

void IMG_wave_horz
(
    short *iptr, 
    short *qmf, 
    short *filter,
    short *optr, 
    int   ish_x_dim 
);

/** @} */

#endif

/* ======================================================================== */
/*  End of file:  IMG_wave_horz.h                                           */
/* ======================================================================== */
