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

#ifndef  IMG_YC_DEMUX_LE16_8_H_
#define  IMG_YC_DEMUX_LE16_8_H_ 1

/** @defgroup IMG_yc_demux_le16_8 */
/** @ingroup  IMG_yc_demux_le16_8 */
/* @{ */

/**
 * @par Description:
 *    This function reads the byte-oriented pixel data, zero-extends      
 *    it, and then writes it to the appropriate result array.  Both       
 *    the luma and chroma values are expected to be unsigned.             
 * @par
 *    The data is expected to be in an order consistent with reading      
 *    byte oriented data from a word-oriented peripheral that is          
 *    operating in LITTLE ENDIAN mode, while the CPU is in LITTLE         
 *    ENDIAN mode.  This function unpacks the byte-oriented data          
 *    so that further processing may proceed in LITTLE ENDIAN mode.       
 * @par                                                                           
 *    @param n     Number of luma pixels      
 *    @param yc    Interleaved luma/chroma    
 *    @param y     Luma plane (16-bit)        
 *    @param cr    Cr chroma plane (16-bit)   
 *    @param cb    Cb chroma plane (16-bit)   
 *
 *
 * @par Algorithm:
 *    The input array 'yc' is expected to be an interleaved 4:2:2         
 *    video stream.  The input is expected in LITTLE ENDIAN byte          
 *    order within each 4-byte word.  This is consistent with reading     
 *    the video stream from a word-oriented LITTLE ENDIAN device          
 *    while the C6000 device is in a LITTLE ENDIAN configuration.         
 * @par 
 *    In other words, the expected pixel order is:                          
 * @verbatim
                                                                            
                    Word 0           Word 1          Word 2                 
                +---------------+---------------+---------------+--          
          Byte# | 0   1   2   3 | 4   5   6   7 | 8   9  10  11 |...         
                | y0 cr0 y1 cb0 | y2 cr2 y3 cb2 | y4 cr4 y5 cb4 |...         
                +---------------+---------------+---------------+--          
   @endverbatim
 * 
 *      The output arrays 'y', 'cr', and 'cb' are expected to not           
 *      overlap.  The de-interleaved pixels are written as half-words       
 *      in LITTLE ENDIAN order.                                             
 * @par 
 *      Please see the IMGLIB function IMB_yc_demux_be16_8 for code which     
 *      handles input coming from a BIG ENDIAN device.                      
 *                                                                          
 *                                                                          
 * @par Assumptions:
 *    - Input and output arrays should be 32-bit aligned.                      
 *    - The input must be a multiple of 16 luma pixels                   
 *
 *
 * @par Implementation Notes:
 *    - This code is fully interruptible and fully reentrant
 *    - This code is compatible with C64x+ processors 
 *    - The loop has been unrolled a total of 16 times to allow for            
 *      processing 8 pixels in each datapath.                                 
 *
 *
 * @par Benchmarks:
 *  See IMGLIB_Test_Report.html for cycle and memory information.
 *
 */

void IMG_yc_demux_le16_8
(
    int n,                               /* Number of luma pixels    */
    const unsigned char *restrict yc,    /* Interbeaved luma/chroma  */
    short         *restrict y,           /* Luma plane (8-bit)       */
    short         *restrict cr,          /* Cr chroma plane (8-bit)  */
    short         *restrict cb           /* Cb chroma plane (8-bit)  */
);

/** @} */

#endif

/* ======================================================================== */
/*  End of file:  IMG_yc_demux_le16_8.h                                     */
/* ======================================================================== */
