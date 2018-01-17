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

#ifndef IMG_QUANTIZE_H_
#define IMG_QUANTIZE_H_ 1

/** @defgroup IMG_quantize */
/** @ingroup  IMG_quantize */
/* @{ */

/**
 * @par Description:
 *    The function quantize() quantizes matrices by multiplying their     
 *    contents with a second matrix that contains reciprocals of the      
 *    quantization terms.  This step corresponds to the quantization      
 *    that is performed in 2-D DCT-based compression techniques,          
 *    although quantize() may be used on any signed 16-bit data using     
 *    signed 16-bit quantization terms.                                   
 * @par
 *    quantize() multiplies the contents of the quantization matrix       
 *    with the data being quantized.  Therefore, it may be used for       
 *    inverse quantization as well, by setting the Q-point                
 *    appropriately.                                                      
 * @par
 *    The assembly code does not explicitly disable interrupts.  On entry to the function,  
 *    interrupts are masked by branch delay slots for a maximum of 16     
 *    cycles.                                                             
 * @par 
 *    @param data          Data to be quantized
 *    @param num_blks      Number of blocks to process
 *    @param blk_size      Block size (multiple of 16)
 *    @param recip_tbl     Quant. values (reciprocals)
 *    @param q_pt          Q-point of Quant values
 *
 *
 * @par Algorithm:
 *    The outer loop is unrolled 16 times to allow greater amounts        
 *    of work to be performed in the inner loop.  The resulting loop-     
 *    nest was then collapsed and pipelined as a single loop, since       
 *    the code is not bottlenecked on bandwidth.                          
 * @par 
 *    Reciprocals and data terms are loaded in groups of four using       
 *    double-word loads, making best use of the available memory          
 *    bandwidth.                                                          
 *                                                                        
 *                                                                          
 * @par Assumptions:
 *    - The recip_tbl[] and data[] must be double-word aligned
 *    - The block size, blk_size, must be a multiple of 16 and at least 32
 *    - The number of blocks, num_blks, may be zero
 *    - The Q-point, q_pt, must be in the range 0 <= q_pt <= 31.            
 *    - The data[] array must be 'num_blks * blk_size' elements
 *    - The recip_tbl[] array must be 'blk_size' elements
 *                                                                          
 *                                                                          
 * @par Implementation Notes:
 *    - This code is fully interruptible and fully reentrant
 *    - This code is compatible with C64x+ processors 
 *    - Twin stack pointers have been used to speed up stack accesses
 *    - SSHVR is used in the M-unit to avoid an S-unit bottleneck
 *    - No bank conflicts occur regardless of the relative orientation     
 *      of recip_tbl[] and data[]
 *    - Six words of stack frame are used for Save-On-Entry registers
 *
 *
 * @par Benchmarks:
 *  See IMGLIB_Test_Report.html for cycle and memory information.
 *
 */
 
void IMG_quantize
(
    short           *data,      /* Data to be quantized.        */
    unsigned short  num_blks,   /* Number of blocks to process. */
    unsigned short  blk_size,   /* Block size (multiple of 16);. */
    const short     *recip_tbl, /* Quant. values (reciprocals);. */
    int             q_pt        /* Q-point of Quant values.     */
);

/** @} */

#endif

/* ======================================================================== */
/*  End of file:  IMG_quantize.h                                            */
/* ======================================================================== */
