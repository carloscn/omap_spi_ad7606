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

#ifndef IMG_SAD_8X8_H_
#define IMG_SAD_8X8_H_ 1

/** @defgroup IMG_sad_8x8 */
/** @ingroup  IMG_sad_8x8 */
/* @{ */

/**
 * @par Description:
 *    The algorithm takes the difference between the pixel values in      
 *    the source image block and the corresponding pixels in the          
 *    reference image.  It then takes the absolute values of these        
 *    differences, and accumulates them over the entire 8x8 region.       
 *    It returns the final accumulation.                                  
 * @par 
 *    @param srcImg         Source 8x8 image block
 *    @param refImg         Reference image to search
 *    @param pitch          Width of reference image
 * @par 
 *    The code accepts a pointer to the 8x8 source block (srcImg),        
 *    and a pointer to the upper-left corner of a target position in      
 *    a reference image (refImg).  The width of the reference image       
 *    is given by the pitch argument.                                     
 * @par 
 *    The function returns the sum of the absolute differences            
 *    between the source block and the 8x8 region pointed to in the       
 *    reference image.                                                    
 *                                                                          
 *                                                                          
 * @par Assumptions:
 *    - srcImg should be 32-bit aligned
 *                                                                          
 *                                                                          
 * @par Implementation Notes:
 *    - This code is compatible with C64x+ processors 
 *    - No bank conflicts occur for this kernel
 *    - This code suppresses interrupts for 25 cycles
 *    - This kernel is Endian neutral
 *
 *
 * @par Benchmarks:
 *  See IMGLIB_Test_Report.html for cycle and memory information.
 *
 */

unsigned IMG_sad_8x8
(
    const unsigned char *restrict srcImg,  /* 8x8 source block   */
    const unsigned char *restrict refImg,  /* Reference image    */
    int pitch                              /* Width of ref image */
);

/** @} */

#endif

/* ======================================================================== */
/*  End of file:  IMG_sad_8x8.h                                             */
/* ======================================================================== */
