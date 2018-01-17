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

#ifndef IMG_CLIPPING_16S_H_
#define IMG_CLIPPING_16S_H_ 1

/** @defgroup IMG_clipping_16s */
/** @ingroup  IMG_clipping_16s */
/* @{ */

/**
 * @par Description:
 *  This function truncates elements of an input image to user defined 
 *  maximum and minimum values. Each input and output pixel is 16-bit 
 *  signed and the size of the matrix is defined by the input dimension 
 *  parameters "rows" and "cols". 
 * @par
 *  The output matrix has the same size as the input matrix and each pixel
 *  is clipped to the user defined minimum or maximum values if is less than 
 *  the minimum or greater than the maximum respectively.  Otherwise, the
 *  pixel is passed to the output unchanged.
 * @par 
 *    @param x          Input image of size cols-by-rows
 *    @param rows       Height of the input image                         
 *    @param cols       Width of the input image                 
 *    @param r          Output image pointer 
 *    @param THRES_MAX  User-defined MAX threshold value
 *    @param THRES_MIN  User-defined MIN threshold value
 *
 *
 * @par Algorithm:
 *  The natural C implementation has no restrictions. The optimized     
 *  intrinsic C code has restrictions as noted in Assumptions below.    
 *
 *
 * @par Assumptions:
 *    - The input and output arrays should not overlap  
 *    - The input and output arrays must be 64-bit aligned
 *    - The THRES_MAX parameter must be greater than or equal to THRES_MIN 
 *    - The number of image pixels (cols x rows) must be a multiple of 8
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
                                                                     
void IMG_clipping_16s
(
    const short *restrict x,        /* Input Matrix Pointer                */
    short              rows,        /* Height of input matrix              */
    short              cols,        /* Width of input matrix               */
    short       *restrict r,        /* Output matrix Pointer               */
    short         THRES_MAX,        /* Maximum Threshold Value             */
    short         THRES_MIN         /* Minimum Threshold Value             */
);

/** @} */

#endif

/* ======================================================================= */
/*  End of file:  IMG_clipping_16s.h                                       */
/* ======================================================================= */
