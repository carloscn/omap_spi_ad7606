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

#ifndef IMG_CORR_GEN_I16S_C16S_H_
#define IMG_CORR_GEN_I16S_C16S_H_ 1

/** @defgroup IMG_corr_gen_i16s_c16s */
/** @ingroup  IMG_corr_gen_i16s_c16s */
/* @{ */

/**
 * @par Description:
 *  This routine performs a generalized correlation with a 1 by M tap  
 *  filter. It can be called repetitively to form an arbitrary MxN 2D   
 *  generalized correlation kernel. The correlation sum is stored as      
 *  half words. The input pixel and mask coefficient are assumed to be
 *  in signed 16-bit format.  No restrictions apply to 'pitch' and 'M'.                         
 * @par
 *    @param x        Pointer to an input image of 16-bit pixels
 *    @param h        Pointer to a 16-bit linear (1xM) filter mask             
 *    @param y        Output correlation sum(s)
 *    @param m        Length of linear filter (taps)         
 *    @param pitch    Number of columns in input image
 *
 *
 * @par Algorithm:
 *  The natural C implementation has no restrictions. The optimized     
 *  intrinsic C code has restrictions as noted in Assumptions below.    
 *
 *
 * @par Assumptions:
 *    - The input array and output array should not overlap  
 *    - The input array must be 32-bit aligned
 *    - The output array must be 64-bit aligned
 *    - The mask array must be 16-bit aligned
 *    - The internal accuracy is 16 bits. The convloution sum should not    
 *      exceed 16 bits (signed).                                       
 *    - The output array size must have at least (pitch - M + 8) elements
 *    - The pitch parameter must be greater than the filter length (M)
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

void IMG_corr_gen_i16s_c16s
(
    short *restrict x, 
    short *restrict h,
	  short *restrict y, 
    int             m, 
    int             pitch
);

/** @} */

#endif

/* ======================================================================== */
/*  End of file:  IMG_corr_gen_i16s_c16s.h                                  */
/* ======================================================================== */
