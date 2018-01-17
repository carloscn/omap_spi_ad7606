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

#ifndef  IMG_WAVE_VERT_H_
#define  IMG_WAVE_VERT_H_ 1

/** @defgroup IMG_wave_vert */
/** @ingroup  IMG_wave_vert */
/* @{ */

/**
 * @par Description:
 *    The benchmark performs the vertical pass of 2D wavelet          
 *    transform It performs a vertical filter on 8 rows which are     
 *    pointed to by the pointers contained in an array of pointers.   
 *    It produces two lines worth of output, one being the low-pass   
 *    and the other being the high pass result. Instead of performing 
 *    a transpose on the column and re-using the wave_horz kernel,    
 *    the vertical filter is traversed over the entire width of the   
 *    line and the low pass and high pass filtering kernels are       
 *    performed together.                                             
 * @par 
 *    This implies that the low-pass and highpass filters be          
 *    overlapped in execution so that the input data array may be     
 *    loaded once and both filters can be exceuted in parallel.       
 * @par 
 *    @param in_data    Array of (8) row pointers 
 *    @param qmf        Low pass QMF filter   
 *    @param mqmf       High pass QMF filter  
 *    @param out_ldata  Low pass output data  
 *    @param out_hdata  High pass output data 
 *    @param cols       Length of rows to process 
 *
 *                                                                       
 * @par Algorithm:
 *    The inner loop that advances along each filter tap is totally    
 *    optimized by unrolling.  Double-word loads are performed, and    
 *    paired multiplies are used to perform four iterations of         
 *    low-pass filter in parallel.                                     
 * @par 
 *    For the high-pass kernel, the same loop is reused, in order      
 *    to save codesize.  This is done by loading the filter            
 *    coefficients in a special order.                                 
 * @par 
 *    The kernels assume that the number of filter taps is exactly     
 *    8.  In addition data that is loaded for producing out_ldata[0]   
 *    and out_hdata[0] is not identical. The data loaded for           
 *    producing out_hdata[0] produces results at the location          
 * @verbatim
            out_lstart = o_im + ((rows >> 1) - 3) * cols                 
            out_hstart = o_im +  (rows >> 1) * cols                       
                                                                        
   @endverbatim
 *                                                                       
 *    Where o_im is start of output image, rows is the number of rows in the    
 *    input image, and cols is the number of columns in the output image.          
 * @par 
 *    The following table illustrates how ylptr and yhptr need to be   
 *    updated at the start of each call to this function:              
 * @verbatim
        Call#        out_ldata                  out_hdata                
          1          out_lstart                 out_hstart               
          2          out_lstart + cols          out_hstart + cols        
          3          out_lstart + 2*cols        out_hstart + 2*cols      
                                                                        
   @endverbatim
 *                                                                       
 *    At this point ylptr wraps around to become o_im, while yhptr     
 *    proceeds as usual:                                               
 * @verbatim
          4          o_im                       out_hstart + 3*cols      

   @endverbatim
 *                                                                         
 *    In addition the kernel accepts a pointer to an array of          
 *    pointers for each input line so that a working buffer of 10      
 *    lines can be used to effectively mix DMA's and processing as     
 *    illustrated below:                                                     
 * @verbatim
        ihptr                        LINE BUFFER                         
        ptr0   ---->|-------------------------------------------------|  
        ptr1   ---->|-------------------------------------------------|  
        ...                                                              
        ptr7   ---->|-------------------------------------------------|  
   @endverbatim
 *                                                                         
 *    At the start of the kernel 8 input lines are filled to the       
 *    first 8 lines and processing begins.  In the background the next 
 *    two lines are fetched.  The pointers are moved up by 2 namely    
 *    ptr[i] = ptr[i+2] and the last two lines now point to lines 9    
 *    and 10 and processing starts again.  In the background the next  
 *    two lines are brought in the first two lines of the line         
 *    buffer.  Pointers move up again by 2 but now the last two        
 *    pointers to line 0 and 1.  This pattern then repeats.            
 * @par 
 *    The first line to begin filtering is always obtained from        
 *    ptr[0], the next from ptr[1] and so on.                          
 *                                                                       
 *                                                                       
 * @par Assumptions:
 *    - The input image dimensions (rows and cols) are assumed to be powers of 2
 *    - The input filters qmf and mqmf are assumed to be word aligned    
 *      and have exactly 8 taps.                                         
 *    - The output data and input data on any line is assumed to be      
 *      double-word aligned.                                                   
 * 
 *                                                                       
 * @par Implementation Notes:
 *    - This code is a LITTLE ENDIAN implementation
 *    - In order to eliminate bank conflicts succesive lines in the      
 *      line buffer or the pointers to these lines are seperated by      
 *      exactly two banks (one word) so that loads to any succesive      
 *      lines may be parallelized together
 *    - This code is compatible with C64x+ processors
 *
 *
 * @par Benchmarks:
 *  See IMGLIB_Test_Report.html for cycle and memory information.
 *
 */

void IMG_wave_vert
(
    const short *restrict
                *restrict in_data,   /* Array of row pointers */
    const short *restrict qmf,       /* Low pass QMF filter   */
    const short *restrict mqmf,      /* High pass QMF filter  */
    short       *restrict out_ldata, /* Low pass output data  */
    short       *restrict out_hdata, /* High pass output data */
    int cols                     /* Length of rows to process */
);

/** @} */

#endif

/* ======================================================================== */
/*  End of file:  IMG_wave_vert.h                                           */
/* ======================================================================== */
