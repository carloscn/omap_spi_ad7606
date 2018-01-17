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

#ifndef IMG_MAD_16X16_H_
#define IMG_MAD_16X16_H_ 1

/** @defgroup IMG_mad_16x16 */
/** @ingroup  IMG_mad_16x16 */
/* @{ */

/**
 * @par Description:
 *    This routine returns the location of the minimum absolute           
 *    difference between a 16x16 search block and some block in a         
 *    (h + 16) x (v + 16) search area. h and v are the sizes of the       
 *    search space for the top left coordinate of the search block.       
 *    refImg points to the top left pixel of the search area.             
 * @verbatim
  
            (0,0)          (h,0)      (h+16,0)                             
              ;--------------+--------;                                    
              ;    search    |        ;                                    
              ;    space     |        ;                                    
              ;              |        ;        search area                 
              ;--------------+        ;        within reference image      
            (0,v)          (h,v)      ;                                    
              ;                       ;                                    
              ;-----------------------;                                    
            (0, v+16)                 (v+16,h+16)                          
   @endverbatim
 * 
 *    The location is returned relative to the above coordinate system    
 *    as x and y packed in two 16-bit quantities in a 32-bit word:        
 * @verbatim
 
                  31             16 15             0                      
                  +----------------+----------------+                     
        match[0]:  |       x        |       y        |                     
                  +----------------+----------------+                     
                                                                          
                  31                               0                      
                  +---------------------------------+                     
        match[1]:  |   SAD value at location x, y    |                     
                  +---------------------------------+                     
   @endverbatim
 * 
 * @par 
 *    @param refImg          Reference image
 *    @param srcImg          16x16 block image to look for
 *    @param pitch           Width of reference image
 *    @param h               Horizontal size of search area
 *    @param v               Vertical size of search area (must be 
 *                            a multiple of 2)
 *    @param match           Result:
 *                               match[0] is packed x, y
 *                               match[1] is MAD value
 *
 *
 * @par Assumptions:
 *    - srcImg and refImg do not alias in memory
 *    - The routine is written for Little Endian configuration
 *    - Two MADS are performed together and hence it is assumed that the vertical 
 *      dimension is a multiple of 2
 *                                                                          
 *                                                                          
 * @par Implementation Notes:
 *    The two outer loops are merged, the two inner loops are merged.     
 *    The inner loop process 2 lines of 2 search locations in parallel.   
 *    The search is performed in top-to-bottom, left-to-right order,      
 *    with the earliest match taking precedence in the case of ties.      
 *    Further use is made of C64x specific instructions such as SUBABS4   
 *    and DOTPU4. The SUBABS4 takes the absolute difference on four 8     
 *    bit quantities packed into a 32 bit word. The DOTPU4 performs four  
 *    8 bit wide multiplies and adds the results together.                
 * @par 
 *    - This code is fully interruptible and fully reentrant
 *    - This code is compatible with C64x+ processors 
 *
 *
 * @par Benchmarks:
 *  See IMGLIB_Test_Report.html for cycle and memory information.
 *
 */
                                                                            
void IMG_mad_16x16
(
    const unsigned char *restrict refImg,
    const unsigned char *restrict srcImg,
    int                 pitch,
    int                 h,
    int                 v,
    unsigned            *restrict match
);

/** @} */

#endif

/* ======================================================================== */
/*  End of file:  IMG_mad_16x16.h                                           */
/* ======================================================================== */
