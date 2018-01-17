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

#ifndef IMG_YCBCR422PL_TO_RGB565_H_
#define IMG_YCBCR422PL_TO_RGB565_H_ 1

/** @defgroup IMG_ycbcr422pl_to_rgb565 */
/** @ingroup  IMG_ycbcr422pl_to_rgb565 */
/* @{ */

/**
 * @par Description:
 *    This kernel performs Y'CbCr to RGB conversion.  From the Color      
 *    FAQ, http://home.inforamp.net/~poynton/ColorFAQ.html:              
 * @par 
 *        Various scale factors are applied to (B'-Y') and (R'-Y')        
 *        for different applications.  The Y'PbPr scale factors are       
 *        optimized for component analog video.  The Y'CbCr scaling       
 *        is appropriate for component digital video, JPEG and MPEG.      
 *        Kodak's PhotoYCC(tm) uses scale factors optimized for the       
 *        gamut of film colors.  Y'UV scaling is appropriate as an        
 *        intermediate step in the formation of composite NTSC or PAL     
 *        video signals, but is not appropriate when the components       
 *        are keps separate.  Y'UV nomenclature is now used rather        
 *        loosely, and it sometimes denotes any scaling of (B'-Y')        
 *        and (R'-Y').  Y'IQ coding is obsolete.                          
 * @par 
 *    This code can perform various flavors of Y'CbCr to RGB              
 *    conversion as long as the offsets on Y, Cb, and Cr are -16,         
 *    -128, and -128, respectively, and the coefficients match the        
 *    pattern shown.                                                      
 * @par 
 *    The kernel implements the following matrix form, which involves 5   
 *    unique coefficients:                                                
 * @verbatim
                                                                          
          [ coeff[0] 0.0000   coeff[1] ]   [ Y' -  16 ]     [ R']         
          [ coeff[0] coeff[2] coeff[3] ] * [ Cb - 128 ]  =  [ G']         
          [ coeff[0] coeff[4] 0.0000   ]   [ Cr - 128 ]     [ B']         
   @endverbatim
 * 
 *    Below are some common coefficient sets, along with the matrix       
 *    equation that they correspond to.   Coefficients are in signed      
 *    Q13 notation, which gives a suitable balance between precision      
 *    and range.                                                          
 * @verbatim
                                                                          
      1.  Y'CbCr -> RGB conversion with RGB levels that correspond to     
          the 219-level range of Y'.  Expected ranges are [16..235] for   
          Y' and [16..240] for Cb and Cr.                                 
                                                                          
          coeff[] = { 0x2000, 0x2BDD, -0x0AC5, -0x1658, 0x3770 };         
                                                                          
          [ 1.0000    0.0000    1.3707 ]   [ Y' -  16 ]     [ R']         
          [ 1.0000   -0.3365   -0.6982 ] * [ Cb - 128 ]  =  [ G']         
          [ 1.0000    1.7324    0.0000 ]   [ Cr - 128 ]     [ B']         
                                                                          
      2.  Y'CbCr -> RGB conversion with the 219-level range of Y'         
          expanded to fill the full RGB dynamic range.  (The matrix       
          has been scaled by 255/219.)  Expected ranges are [16..235]     
          for Y' and [16..240] for Cb and Cr.                             
                                                                          
          coeff[] = { 0x2543, 0x3313, -0x0C8A, -0x1A04, 0x408D };         
                                                                          
          [ 1.1644    0.0000    1.5960 ]   [ Y' -  16 ]     [ R']         
          [ 1.1644   -0.3918   -0.8130 ] * [ Cb - 128 ]  =  [ G']         
          [ 1.1644    2.0172    0.0000 ]   [ Cr - 128 ]     [ B']         
                                                                          
      3.  Y'CbCr -> BGR conversion with RGB levels that correspond to     
          the 219-level range of Y'.  This is equivalent to #1 above,     
          except that the R, G, and B output order in the packed          
          pixels is reversed.  Note:  The 'cr_data' and 'cb_data'         
          input arguments must be exchanged for this example as           
          indicated under USAGE above.                                    
                                                                          
          coeff[] = { 0x2000, 0x3770, -0x1658, -0x0AC5, 0x2BDD };         
                                                                          
          [ 1.0000    0.0000    1.7324 ]   [ Y' -  16 ]     [ B']         
          [ 1.0000   -0.6982   -0.3365 ] * [ Cr - 128 ]  =  [ G']         
          [ 1.0000    1.3707    0.0000 ]   [ Cb - 128 ]     [ R']         
                                                                          
      4.  Y'CbCr -> BGR conversion with the 219-level range of Y'         
          expanded to fill the full RGB dynamic range.  This is           
          equivalent to #2 above, except that the R, G, and B output      
          order in the packed pixels is reversed.  Note:  The             
          'cr_data' and 'cb_data' input arguments must be exchanged       
          for this example as indicated under USAGE above.                
                                                                          
          coeff[] = { 0x2000, 0x408D, -0x1A04, -0x0C8A, 0x3313 };         
                                                                          
          [ 1.0000    0.0000    2.0172 ]   [ Y' -  16 ]     [ B']         
          [ 1.0000   -0.8130   -0.3918 ] * [ Cr - 128 ]  =  [ G']         
          [ 1.0000    1.5960    0.0000 ]   [ Cb - 128 ]     [ R']         
   @endverbatim
 * 
 *    Other scalings of the color differences (B'-Y') and (R'-Y')         
 *    (sometimes incorrectly referred to as U and V) are supported, as    
 *    long as the color differences are unsigned values centered around   
 *    128 rather than signed values centered around 0, as noted above.    
 * @par 
 *    In addition to performing plain color-space conversion, color       
 *    saturation can be adjusted by scaling coeff[1] through coeff[4].    
 *    Similarly, brightness can be adjusted by scaling coeff[0].          
 *    General hue adjustment can not be performed, however, due to the    
 *    two zeros hard-coded in the matrix.                                 
 *                                                                        
 *
 * @par Usage:
 *    This function takes the following parameters:                                                        
 * @par 
 *    @param coeff       Matrix coefficients.          
 *    @param y_data      Luminence data  (Y')          
 *    @param cb_data     Blue color-diff (B'-Y')       
 *    @param cr_data     Red color-diff  (R'-Y')       
 *    @param rgb_data    RGB 5:6:5 packed pixel out.   
 *    @param num_pixels  Number of luma pixels to process   
 * @par 
 *    The 'coeff[]' array contains the color-space-conversion matrix      
 *    coefficients.  The 'y_data', 'cb_data' and 'cr_data' pointers       
 *    point to the separate input image planes.  The 'rgb_data' pointer   
 *    points to the output image buffer.  See below for alignment         
 *    constraints on these buffers.                                       
 * @par 
 *    The kernel is designed to process arbitrary amounts of 4:2:2        
 *    image data, although 4:2:0 image data may be processed as well.     
 *    For 4:2:2 input data, the 'y_data', 'cb_data' and 'cr_data'         
 *    arrays may hold an arbitrary amount of image data, including        
 *    multiple scan lines of image data.                                  
 * @par 
 *    For 4:2:0 input data, only a single scan-line (or portion           
 *    thereof) may be processed at a time.  This is achieved by           
 *    calling the function twice using the same row data for              
 *    'cr_data' and 'cb_data', and providing new row data for             
 *    'y_data'.  This is numerically equivalent to replicating the Cr     
 *    and Cb pixels vertically.                                           
 * @par 
 *    The coefficients in the coeff array must be in signed Q13 form.     
 *    These coefficients correspond to the following matrix equation:     
 * @verbatim
                                                                          
          [ coeff[0] 0.0000   coeff[1] ]   [ Y' -  16 ]     [ R']         
          [ coeff[0] coeff[2] coeff[3] ] * [ Cb - 128 ]  =  [ G']         
          [ coeff[0] coeff[4] 0.0000   ]   [ Cr - 128 ]     [ B']         
   @endverbatim
 * 
 *    The output from this kernel is 16-bit RGB in 5:6:5 format.          
 *    The RGB components are packed into halfwords as shown below.        
 * @verbatim
                                                                          
                      15      11 10       5 4        0                     
                    +----------+----------+----------+                    
                    |   Red    |  Green   |   Blue   |                    
                    +----------+----------+----------+                    
   @endverbatim
 * 
 *    This kernel can also return the red, green, and blue values in      
 *    the opposite order if a particular application requires it.         
 *    This is achieved by exchanging the 'cb_data' and 'cr_data'          
 *    arguments when calling the function, and by reversing the order     
 *    of coefficients in coeff[1] through coeff[4].  This essentially     
 *    implements the following matrix multiply:                           
 * @verbatim
                                                                          
          [ coeff[0] 0.0000   coeff[4] ]   [ Y' -  16 ]     [ B']         
          [ coeff[0] coeff[3] coeff[2] ] * [ Cr - 128 ]  =  [ G']         
          [ coeff[0] coeff[1] 0.0000   ]   [ Cb - 128 ]     [ R']         
   @endverbatim
 * 
 *    The reversed RGB ordering output by this mode is as follows:        
 * @verbatim
                                                                          
                      15      11 10       5 4        0                     
                    +----------+----------+----------+                    
                    |   Blue   |  Green   |   Red    |                    
                    +----------+----------+----------+                    
   @endverbatim
 * 
 *                                                                          
 * @par Assumptions:
 *    - The number of luma samples must to be a multiple of 8
 *    - The input Y array should be 32-bit aligned
 *    - The input Cr and Cb arrays should be 16-bit aligned
 *    - The output image should be 32-bit aligned
 *                                                                          
 *                                                                          
 * @par Implementation Notes:
 *    - This code is fully interruptible and fully reentrant
 *    - This code is compatible with C64x+ processors 
 *
 *
 * @par Benchmarks:
 *  See IMGLIB_Test_Report.html for cycle and memory information.
 *
 */

void IMG_ycbcr422pl_to_rgb565
(
    const short                   coeff[5],  /* Matrix coefficients.          */
    const unsigned char *restrict y_data,    /* Luminence data        (Y')    */
    const unsigned char *restrict cb_data,   /* Blue color-difference (B'-Y') */
    const unsigned char *restrict cr_data,   /* Red color-difference  (R'-Y') */
    unsigned short      *restrict rgb_data,  /* RGB 5:6:5 packed pixel output */
    unsigned                      num_pixels /* # of luma pixels to process.  */
);

/** @} */

#endif

/* ======================================================================== */
/*  End of file:  IMG_ycbcr422pl_to_rgb565.h                                */
/* ======================================================================== */
