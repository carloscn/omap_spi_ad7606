/*******************************************************************************
**+--------------------------------------------------------------------------+**
**|                            ****                                          |**
**|                            ****                                          |**
**|                            ******o***                                    |**
**|                      ********_///_****                                   |**
**|                      ***** /_//_/ ****                                   |**
**|                       ** ** (__/ ****                                    |**
**|                           *********                                      |**
**|                            ****                                          |**
**|                            ***                                           |**
**|                                                                          |**
**|        Copyright (c) 2007 - 2013 Texas Instruments Incorporated          |**
**|                                                                          |**
**|              All rights reserved not granted herein.                     |**
**|                                                                          |**
**|                         Limited License.                                 |**
**|                                                                          |**
**|  Texas Instruments Incorporated grants a world-wide, royalty-free,       |**
**|  non-exclusive license under copyrights and patents it now or            |**
**|  hereafter owns or controls to make, have made, use, import, offer to    |**
**|  sell and sell ("Utilize") this software subject to the terms herein.    |**
**|  With respect to the foregoing patent license, such license is granted   |**
**|  solely to the extent that any such patent is necessary to Utilize the   |**
**|  software alone.  The patent license shall not apply to any              |**
**|  combinations which include this software, other than combinations       |**
**|  with devices manufactured by or for TI ("TI Devices").  No hardware     |**
**|  patent is licensed hereunder.                                           |**
**|                                                                          |**
**|  Redistributions must preserve existing copyright notices and            |**
**|  reproduce this license (including the above copyright notice and the    |**
**|  disclaimer and (if applicable) source code license limitations below)   |**
**|  in the documentation and/or other materials provided with the           |**
**|  distribution                                                            |**
**|                                                                          |**
**|  Redistribution and use in binary form, without modification, are        |**
**|  permitted provided that the following conditions are met:               |**
**|                                                                          |**
**|    *  No reverse engineering, decompilation, or disassembly of this      |**
**|  software is permitted with respect to any software provided in binary   |**
**|  form.                                                                   |**
**|                                                                          |**
**|    *  any redistribution and use are licensed by TI for use only with    |**
**|  TI Devices.                                                             |**
**|                                                                          |**
**|    *  Nothing shall obligate TI to provide you with source code for      |**
**|  the software licensed and provided to you in object code.               |**
**|                                                                          |**
**|  If software source code is provided to you, modification and            |**
**|  redistribution of the source code are permitted provided that the       |**
**|  following conditions are met:                                           |**
**|                                                                          |**
**|    *  any redistribution and use of the source code, including any       |**
**|  resulting derivative works, are licensed by TI for use only with TI     |**
**|  Devices.                                                                |**
**|                                                                          |**
**|    *  any redistribution and use of any object code compiled from the    |**
**|  source code and any resulting derivative works, are licensed by TI      |**
**|  for use only with TI Devices.                                           |**
**|                                                                          |**
**|  Neither the name of Texas Instruments Incorporated nor the names of     |**
**|  its suppliers may be used to endorse or promote products derived from   |**
**|  this software without specific prior written permission.                |**
**|                                                                          |**
**|  DISCLAIMER.                                                             |**
**|                                                                          |**
**|  THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY      |**
**|  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE       |**
**|  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR      |**
**|  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TI AND TI'S LICENSORS BE      |**
**|  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR     |**
**|  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF    |**
**|  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR         |**
**|  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,   |**
**|  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE    |**
**|  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,       |**
**|  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                      |**
**+--------------------------------------------------------------------------+**
*******************************************************************************/

#ifndef _COMMON_VLIB_TYPES_H_
#define _COMMON_VLIB_TYPES_H_ 1

/*  Enables MISRA Compliant code*/
#define MISRA 1

/* It was found during MISRAC violation fixes, that in many cases,
 * when violation 10.1 regarding implicit type conversion was 'fixed'
 * by adding explicit casting, the performance of the DSP optimized
 * code was reduced.  This was because depending on how the casting
 * happened, it restricted the DSP compiler's ability to find performance
 * optimizations.  Therefore, such fixes were made such that performance
 * for 7.4.2 version of the compiler was not lost.  However, this doesn't
 * guarantee that future versions of the compiler would optimize in the
 * same manner.  Therefore, each explicit cast is done using the following
 * macro (mcast()) so that when a new compiler is used, VLIB can be compiled
 * again with the macro disabled to see what the compiler would do without
 * the explicit casting that was added for MISRAC compliance. If a performance
 * degregation due to casting is found, it can be addressed.
 * mcast is short for MISRAC CASTING */
#if MISRA
#define mcast(x) (x)
#else
#define mcast(x)
#endif

#include <stdlib.h>
#include "VLIB_platforms.h"

#define MAXIMG_WIDTH 128
#define MAXIMG_HEIGHT 128

/* VLIB_HOG_cell_f32 */
#define MAXBINS 30
#define MAXBLOCKSIZE 16
#define BLK_WDT (MAXIMG_WIDTH / 2)
#define BLK_HGT (MAXIMG_HEIGHT / 2)

#define VLIB_BINSKEL_MASK_SZ  (3 * 3)

/* C64x+ types */
typedef double          VLIB_D64;  /*!< Double precision floating point */
typedef float           VLIB_F32;  /*!< Single precision floating point */
typedef void           *VLIB_PTR;  /*!< Void pointer */
typedef unsigned long   VLIB_VAL;  /*!< Unsigned long cast value */

/* Fixed point defines */
#define VLIB_MAX_0p16    1
#define VLIB_MAX_4p12    16
#define VLIB_MAX_8p8     256
#define VLIB_MAX_10p5    1024
#define VLIB_MAX_12p4    4096
#define VLIB_MAX_13p2    8192
#define VLIB_MAX_16p16   65536

typedef struct {
    int32_t area;
    int32_t xsum;
    int32_t ysum;

    int32_t xmin;
    int32_t ymin;
    int32_t xmax;
    int32_t ymax;

    int32_t seedx;
    int32_t seedy;

} VLIB_CC;

typedef int32_t VLIB_CCHandle;

typedef enum {
    VLIB_NO_ERROR = 0,
    VLIB_ERR_INPUT_INVALID = 1,
    VLIB_ERR_INPUT_NEGATIVE = 2,
    VLIB_ERR_INPUT_EXCEEDED_RANGE = 3,
    VLIB_ERR_MEMORY_EXCEEDED_BOUNDARY = 4,
    VLIB_ERR_MEMORY_ALLOCATION_FAILURE = 5,
    VLIB_ERR_MEMORY_POINTER_NULL = 6,
    VLIB_ERR_DMA_FAILURE = 7,
    VLIB_ERR_FILE_OPEN_FAILURE = 8,
    VLIB_ERR_FILE_READ_FAILURE = 9,
    VLIB_ERR_FILE_WRITE_FAILURE = 10,
    VLIB_ERR_FILE_CLOSE_FAILURE = 11,
    VLIB_ERR_FILE_FORMAT_FAILURE = 12,
    VLIB_WARNING_LOW_MEMORY = 13,
    VLIB_ERR_NOT_IMPLEMENTED = 14,
    VLIB_ERROR_MAX = 15
} VLIB_STATUS;

#endif /* _COMMON_VLIB_TYPES_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_types.h                                            */
/* ======================================================================== */

