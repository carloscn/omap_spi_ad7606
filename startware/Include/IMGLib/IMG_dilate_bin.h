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

#ifndef IMG_DILATE_BIN_H_
#define IMG_DILATE_BIN_H_ 1

/** @defgroup IMG_dilate_bin */
/** @ingroup  IMG_dilate_bin */
/* @{ */

/**
 * @par Description:
 *  The function IMG_dilate_bin() implements binary dilation using an  
 *  arbitrary 3x3 mask.  The dilation operator generates output pixels 
 *  by ORing the pixels under the input mask together to generate        
 *  the output pixel.  The input mask specifies whether one or more    
 *  pixels from the input are to be ignored.                           
 * @par 
 *    @param in_data    Input image pointer (packed binary)
 *    @param out_data   Output image pointer (packed binary)
 *    @param mask       Dilation filter mask 
 *    @param cols       Number of columns in the image
 *
 *
 * @par Algorithm:
 *  The filtering operation for a pixel at (x, y) works as illustrated by the
 *  following pseudo-code:
 *
 * <tt>
 *  result = 0;                                                    
 *  if (mask[0][0] != DONT_CARE) result |= input[y + 0][x + 0];    
 *  if (mask[0][1] != DONT_CARE) result |= input[y + 1][x + 1];    
 *  if (mask[0][2] != DONT_CARE) result |= input[y + 2][x + 2];    
 *  if (mask[1][0] != DONT_CARE) result |= input[y + 0][x + 0];    
 *  if (mask[1][1] != DONT_CARE) result |= input[y + 1][x + 1];    
 *  if (mask[1][2] != DONT_CARE) result |= input[y + 2][x + 2];    
 *  if (mask[2][0] != DONT_CARE) result |= input[y + 0][x + 0];    
 *  if (mask[2][1] != DONT_CARE) result |= input[y + 1][x + 1];    
 *  if (mask[2][2] != DONT_CARE) result |= input[y + 2][x + 2];    
 *  output[y][x] = result;                                         
 * </tt>
 * 
 * @par 
 *  For the above code, "DONT_CARE" is specified by a negative value        
 *  in the input mask.  Non-negative values in the mask cause the      
 *  corresponding pixel to be included in the dilation operation.      
 * @par 
 *  Note that this code operates on a bitmap where each pixel is       
 *  represented as a single bit within a byte or word.  Although       
 *  the pseudo-code above operates only on one pixel at a time,        
 *  with a single pixel in each array element, the implementation     
 *  operates on a bitmap which contains 8 binary pixels per byte.         
 * @par 
 *  Pixels are organized within each byte such that the pixel with     
 *  the smallest index is in the LSB, and the pixel with the largest 
 *  index is in the MSB.  (That is, the code assumes a LITTLE ENDIAN 
 *  bit ordering.)                             
 * @par 
 *  Note that the "cols" argument actually specifies the number of     
 *  BYTES in the output, not the number of columns.  The number of     
 *  columns is 8 times this argument.                                  
 * @par 
 *  The 3x3 dilation mask is applied to 32 output pixels simultaneously.  
 *  This is achieved via the 32-bit bitwise operators in the register 
 *  file.  To accomlish this, the code reads in a 34-bit input window, 
 *  and 40-bit operations are used to manipulate the pixels initially.                       
 * @par 
 *  Because the code reads a 34-bit context for each 32-bits of        
 *  output, the input needs to be one byte longer than the output      
 *  in order to make the rightmost two pixels well-defined.            
 * @par 
 *  The natural C implementation has no restrictions. The optimized     
 *  intrinsic C code has restrictions as noted in Assumptions below.    
 *
 *
 * @par Assumptions:
 *    - The input array and output array should not overlap  
 *    - Negative values in the mask specify "DONT_CARE", and non-negative 
 *      values specify that pixels are included in the dilation operation.
 *    - The input image needs to have a multiple of 64 pixels (bits) per row.  
 *      As such, the number of columns (cols) must be a multiple of 8.           
 *
 * @par Implementation Notes:
 *    - This code is fully interruptible
 *    - This code is compatible with C64x+ processors
 *    - This code will work for little endian only
 *
 *
 * @par Benchmarks:
 *  See IMGLIB_Test_Report.html for cycle and memory information.
 *
 */

void IMG_dilate_bin
(
    const unsigned char *restrict in_data, 
          unsigned char *restrict out_data, 
    const          char *restrict mask, 
    int                           cols
);

/** @} */

#endif

/* ======================================================================== */
/*  End of file:  IMG_dilate_bin.h                                          */
/* ======================================================================== */
