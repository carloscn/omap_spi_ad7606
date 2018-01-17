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

#ifndef IMG_FDCT_8X8_H_
#define IMG_FDCT_8X8_H_ 1

/** @defgroup IMG_fdct_8x8 */
/** @ingroup  IMG_fdct_8x8 */
/* @{ */

/**
 * @par Description:
 *  The fdct_8x8 function implements a Chen FDCT.  Output values are rounded, 
 *  providing improved accuracy.  Input terms are expected to be signed 11Q0 
 *  values, producing signed 15Q0 results.  (A smaller dynamic range may be 
 *  used on the input, producing a correspondingly smaller output range.  
 *  Typical applications include processing signed 9Q0 and unsigned 8Q0 pixel 
 *  data, producing signed 13Q0 or 12Q0 outputs, respectively.)  No saturation 
 *  is performed.
 *  
 *  The fdct routine accepts a list of 8x8 pixel blocks and performs FDCTs on 
 *  each.  The array should be laid out as "fdct_data[num_fdcts][8][8]".  All 
 *  operations in this array are performed  in-place.  Input values must be in 
 *  the range [-512,511].  Larger input values may result in overflow.        
 *                                                                  
 *  Note:  This code guarantees correct operation, even in the case that 
 *  "num_fdcts" is zero.  In this case, the function runs for 13 cycles 
 *  (counting 6 cycles of function-call overhead), due to early-exit code. The 
 *  early-exit case performs one access to the "fdct_data" array and no access 
 *  to the stack.
 * @par 
 *    @param fdct_data  Pointer to 8x8 DCT blocks
 *    @param num_fdcts  Number of DCT blocks
 *
 *
 * @par Algorithm:
 *  The loop nest in the vertical pass has been collapsed into a single-level 
 *  loop.  Both vertical and horizontal loops have been software pipelined.
 * @par 
 *  For performance, portions of the code outside the loops have been inter-
 *  scheduled with the prolog and epilog code of the loops.  Also, twin 
 *  stack-pointers are used to accelerate stack accesses.  Finally, pointer 
 *  values and cosine term registers are reused between the horizontal and 
 *  vertical loops to reduce the impact of pointer and constant reinitialization.
 * @par 
 *  To save code size, prolog and epilog collapsing have been performed to the 
 *  extent that it does not impact performance.                
 * @par 
 *  To reduce register pressure and save some code, the horizontal loop uses the 
 *  same pair of pointer register for both reading and writing.  The pointer 
 *  increments are on the LDs to permit prolog and epilog collapsing, since LDs 
 *  can be speculated.
 *
 *
 * @par Assumptions:
 *    - The stack must be 64-bit aligned 
 *    - The "fdct_data" array is laid out as fdct_data[num_fdcts][8][8]
 *    - Values in "fdct_data" are in the range [-512,511]
 *    - The "fdct_data" array must be 64-bit aligned 
 * 
 *
 * @par Implementation Notes:
 *    - This code is fully interruptible
 *    - This code requires four words of stack for Save-On-Entry registers
 *    - This code is compatible with C64x+ processors
 *
 *
 * @par Benchmarks:
 *  See IMGLIB_Test_Report.html for cycle and memory information.
 *
 */

void IMG_fdct_8x8
(
    short fdct_data[],
    unsigned num_fdcts
);

/** @} */

#endif

/* ======================================================================== */
/*  End of file:  IMG_fdct_8x8.h                                            */
/* ======================================================================== */
