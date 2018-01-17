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

#ifndef IMG_HISTOGRAM_8_H_
#define IMG_HISTOGRAM_8_H_ 1

/** @defgroup IMG_histogram_8 */
/** @ingroup IMG_histogram_8 */
/* @{ */

/**
 * @par Description:
 *  This code takes a histogram of an array of n, 8 bit inputs. It returns 
 *  the histogram of 256 bins at 16 bit precision. It can either add-to or 
 *  subtract-from an existing histogram via the 'accumulate' control. The 
 *  implementation requires temporary storage for 4 256-bin histograms
 *  which are summed for the final result.                              
 * @par 
 *    @param image        Input image pointer containing "n" unsigned 8-bit 
 *                        pixels
 *    @param n            Size of image in pixels
 *    @param accumulate   Control to add or subtract from the running 
 *                        histogram.  This control is only defined for the  
 *                        values 1 and -1 for ADD and SUBTRACT respectively 
 *    @param t_hist       Scratch buffer for temporary histogram storage 
 *                        (1024 bytes)
 *    @param hist         Running histogram bins (256)               
 *
 *
 * @par Algorithm:
 *  This code operates on four interleaved histogram bins. The loop is 
 *  divided into two halves. The even half operates on even words of pixels 
 *  and the odd half operates on odd words. Both halves utilize the same 4 
 *  histogram bins. This introduces a memory dependency which would ordinarily 
 *  degrade performance. To break the memory depenencies, the two halves 
 *  forward their results to each other. Exact memory access ordering obviates 
 *  the need to predicate stores.
 * @par 
 *  The algorithm is ordered as follows:                               
 *   -# Load from histogram for even half                              
 *   -# Store odd_bin to histogram for odd half (previous iteration)        
 *   -# IF data_even == previous data_odd THEN increment even_bin by 2      
 *      ELSE increment even_bin by 1, forward to odd                   
 *   -# Load from histogram for odd half (current iteration)
 *   -# Store even_bin to histogram for even half                      
 *   -# IF data_odd == previous data_even THEN increment odd_bin by 2       
 *      ELSE increment odd_bin by 1, forward to even                   
 *   -# Repeat from 1.                                                        
 * @par 
 *  With this particular ordering, forwarding is necessary between the even and
 *  odd halves when pixels in adjacent halves fall in the same bin.  The store 
 *  is never predicated and occurs speculatively as it will be overwritten by 
 *  the next value containing the extra forwarded value.                                              
 * @par 
 *  The four scratch histograms are interleaved with each bin spaced four half 
 *  words apart and each histogram starting in a different memory bank. This 
 *  allows the four histogram accesses to proceed in any order without worrying 
 *  about bank conflicts. The diagram below illustrates this:  (addresses are 
 *  halfword offsets)                                                            
 * @verbatim 
         0       1       2       3       4       5       6   ...        
     | hst 0 | hst 1 | hst 2 | hst 3 | hst 0 | hst 1 | ...   ...        
     | bin 0 | bin 0 | bin 0 | bin 0 | bin 1 | bin 1 | ...   ...        
   @endverbatim 
 *
 *
 * @par Assumptions:
 *    - The temporary array, t_hist, is initialized to zero for the first
 *      call to the routine (for "accumulate")
 *    - The input array of image data is aligned on a 4 byte boundary
 *    - The number of pixels is a non-zero multiple of 8. 
 *    - The maximum bin number is 32767.
 *    - The maximum n is 262143.
 *
 *
 * @par Implementation Notes:
 *    - This code is fully interruptible
 *    - This code is compatible with C64x+ processors
 *    - No bank conflicts should occur in this code
 *
 *
 * @par Benchmarks:
 *  See IMGLIB_Test_Report.html for cycle and memory information.
 *
 */

void IMG_histogram_8
(
    const unsigned char *restrict image,
    int   n,
    short accumulate,
    short *restrict t_hist,
    short *restrict hist
);

/** @} */

#endif

/* =========================================================================*/
/*  End of file:  IMG_histogram_8.h                                         */
/* =========================================================================*/
