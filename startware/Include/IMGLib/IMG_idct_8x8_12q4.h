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

#ifndef IMG_IDCT_8X8_12Q4_H_
#define IMG_IDCT_8X8_12Q4_H_ 1

/** @defgroup IMG_idct_8x8_12q4 */
/** @ingroup  IMG_idct_8x8_12q4 */
/* @{ */

/**
 * @par Description:
 *  The idct_8x8_12q4 algorithm performs an IEEE-1180 compliant IDCT, complete 
 *  with rounding and saturation to signed 9-bit quantities.  The input 
 *  coefficients are assumed to be signed 16-bit DCT coefficients in 12Q4 format.
 *  
 *  The idct_8x8_12q4 routine accepts a list of 8x8 DCT coeffient blocks and 
 *  performs IDCTs on each.  The array should be aligned to a 64-bit boundary, 
 *  and be laid out as "idct_data[num_idcts][8][8]".  Input data must be in 12Q4       
 *  format.  The routine operates entirely in-place, requiring no additional 
 *  storage for intermediate results.
 *  
 *  Note:  This code guarantees correct operation, even in the case that 
 *  "num_idcts" is zero.  In this case, the function runs for 13 cycles 
 *  (counting 6 cycles of function-call overhead), due to early-exit code. 
 * @par 
 *    @param idct_data  Pointer to 8x8 IDCT coefficient blocks
 *    @param num_idcts  Number of IDCT blocks
 *
 *
 * @par Algorithm:
 *  All levels of looping are collapsed into single loops which are pipelined.  
 *  The outer loop focuses on 8-pt IDCTs, whereas the inner loop controls the 
 *  column-pointer to handle jumps between IDCT blocks.  (The column-pointer 
 *  adjustment is handled by a four-phase rotating "fixup" constant which takes 
 *  the place of the original inner-loop).
 * @par 
 *  For performance, portions of the outer-loop code have been inter-scheduled 
 *  with the prologs and epilogs of both loops.  Finally, cosine term registers 
 *  are reused between the horizontal and vertical loops to save the need for 
 *  reinitialization.       
 * @par 
 *  To save codesize, prolog and epilog collapsing have been performed to the 
 *  extent that performance is not affected.  The remaining prolog and epilog 
 *  code has been interscheduled with code outside the loops to improve 
 *  performance.
 * @par 
 *  Additional section-specific optimization notes are provided below.
 *
 *
 * @par Assumptions:
 *    - The "idct_data" array is laid out as idct_data[num_idcts][8][8]
 *    - The "idct_data" array must be 64-bit aligned 
 *    - This is a LITTLE ENDIAN implementation
 * 
 *
 * @par Implementation Notes:
 *    - This code is fully interruptible and fully reentrant
 *    - This code is compatible with C64x+ processors
 *    - No bank conflicts occur
 *    - The code may perform speculative reads of up to 128 bytes beyond the end 
 *      or before the start of the IDCT array.  The speculatively accessed data 
 *      is ignored
 *
 *
 * @par Benchmarks:
 *  See IMGLIB_Test_Report.html for cycle and memory information.
 *
 */

void IMG_idct_8x8_12q4
(
    short idct_data[],
    unsigned num_idcts
);

/** @} */

#endif

/* ======================================================================== */
/*  End of file:  IMG_idct_8x8_12q4.h                                       */
/* ======================================================================== */
