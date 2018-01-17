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

#ifndef IMG_MAD_8X8_H_
#define IMG_MAD_8X8_H_ 1

/** @defgroup IMG_mad_8x8 */
/** @ingroup  IMG_mad_8x8 */
/* @{ */

/**
 * @par Description:
 *    This routine locates the position in a reference image which        
 *    most closely matches an 8x8 block from a source image, using        
 *    the Minimum Absolute Difference metric.  Searches over a range      
 *    that is 'sx' pixels wide and 'sy' pixels tall within a reference    
 *    image that is 'pitch' pixels wide.                                  
 * @par
 *    The search is performed in top-to-bottom, left-to-right order,      
 *    with the earliest match taking precedence in the case of ties.      
 * @par
 *    The match location as well as the Minimum Absolute Difference       
 *    metric for the match are returned in the 'match' array.             
 *    The first element contains the packed horizontal and vertical       
 *    coordinates of the match, with the X coordinate in the upper        
 *    halfword and the Y coordinate in the lower halfword.  The           
 *    second element contains the MAD value for this match location.      
 * @par
 *    The reference image is an image of width 'pitch'.  The mad_8x8      
 *    routine searches a (sx,sy) window within the image.                 
 * @par
 *    The source image is an 8x8 block of pixels which contain the        
 *    image block that is being searched for.                             
 * @par
 *    The match[] array is where the best match location and MAD value    
 *    for the best match are stored.  The best match position and its     
 *    absolute difference are returned in match, packed as follows:       
 * @verbatim
                      31             16 15             0                   
                      +----------------+----------------+                  
          match[0]:  |    X offset    |    Y offset    |                  
                      +----------------+----------------+                  
                                                                          
                      31                               0                   
                      +---------------------------------+                  
          match[1]:  |   Minimum Absolute Difference    |                  
                      +---------------------------------+                  
   @endverbatim
 * 
 * @par 
 *    @param ref_data        Reference image to search
 *    @param src_data        Source 8x8 image block
 *    @param pitch           Width of reference image
 *    @param sx              Horizontal size of search area
 *    @param sy              Vertical size of search area (must be 
 *                            a multiple of 2)
 *    @param match           Result:
 *                               match[0] is packed x, y
 *                               match[1] is MAD value
 *                                                                          
 *                                                                          
 * @par Assumptions:
 *    - Src_data and match must be 16-bit aligned
 *    - The routine is written for Little Endian configuration
 *    - Two MADS are performed together and hence it is assumed that the vertical 
 *      dimension is a multiple of 2
 *                                                                          
 *                                                                          
 * @par Implementation Notes:
 *    The inner loops that perform the 8x8 mads are completely            
 *    unrolled and the outer two loops are collpaesd together. In         
 *    addition all source image data is pre-loaded into registers.        
 * @par 
 *    The data required for any one row is brought in using               
 *    non-aligned loads. SUBABS4 and DOTPU4 are used together to do       
 *    the MAD computation.                                                
 * @par 
 *    To save instructions and fit within an 8 cycle loop, the            
 *    precise location of a given match is not stored.  Rather,           
 *    the loop iteration that it was encountered on is stored.            
 *    A short divide loop after the search loop converts this             
 *    value into X and Y coordinates for the location.                    
 * @par 
 *    - This code is fully interruptible and fully reentrant
 *    - This code is compatible with C64x+ processors 
 *    - No bank conflicts occur for this kernel
 *    - No alignment is required for ref_data
 *    - This code suppresses interrupts for the entire duration of the call
 *    - This kernel is Little Endian only
 *
 *
 * @par Benchmarks:
 *  See IMGLIB_Test_Report.html for cycle and memory information.
 *
 */
 
void IMG_mad_8x8
(
    const unsigned char *ref_data,  /* Ref. image to search     */
    const unsigned char *src_data,  /* Source 8x8 block         */
    int                 pitch,      /* Width of ref image       */
    int                 sx,         /* Search window horz size  */
    int                 sy,         /* Search window vert size  */
    unsigned int        *match      /* Result                   */
);

/** @} */

#endif

/* ======================================================================== */
/*  End of file:  IMG_mad_8x8.h                                             */
/* ======================================================================== */
