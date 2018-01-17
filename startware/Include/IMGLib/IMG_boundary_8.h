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

#ifndef IMG_BOUNDARY_8_H_
#define IMG_BOUNDARY_8_H_ 1

/** @defgroup IMG_boundary_8 */
/** @ingroup  IMG_boundary_8 */
/* @{ */

/**
 * @par Description:
 *  This routine scans an image looking for non-zero pixels.   
 *  The locations of those pixels are stored out to the o_coord array
 *  as packed Y/X pairs, with Y in the upper 16-bits, and X in    
 *  the lower 16-bits.  The associated grey levels are stored in the 
 *  o_grey array in parallel.                           
 * @par 
 *    @param i_data   Input image of size cols-by-rows
 *    @param rows     Height of the input image                         
 *    @param cols     Width of the input image                 
 *    @param o_coord  Array to write output coordinates to     
 *    @param o_grey   Array to write output grey levels to      
 *
 *
 * @par Algorithm:
 *  Outer and inner loops are merged.                              
 * @par 
 *  "Inner loop" is unrolled to process four pixels per iteration. 
 * @par 
 *  Packed coordinate value is updated directly, rather than       
 *  by repacking x, y every time it's needed.                      
 * @par 
 *  The natural C implementation has no restrictions. The optimized     
 *  intrinsic C code has restrictions as noted in Assumptions below.    
 *
 *
 * @par Assumptions:
 *    - The input and output arrays should not overlap  
 *    - Input and both output arrays must be 32-bit aligned
 *    - Output buffers o_coord and o_grey start in different banks
 *    - The cols parameter must be a non-zero multiple of 4 less than 32767
 *    - The rows parameter must be non-zero and less than or equal to 32767
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

void IMG_boundary_8
(
    const unsigned char *restrict i_data,
    int rows, int cols,
    int *restrict o_coord,
    int *restrict o_grey
);

/** @} */

#endif

/* ======================================================================== */
/*  End of file:  IMG_boundary_8.h                                          */
/* ======================================================================== */
