/****************************************************************************/
/*                                                                          */
/*  @file       : *type.h                                                   */
/*  @Copyright  : Lifi.MLT (c) 2015 MULTIBEANS_ORG All rights reserved.     */
/*  @Revision   : Ver 1.0.                                                  */
/*  @Data       : 2015.07.28 Realse.                                        */
/*  @Belong     : PROJECT.                                                  */
/*                                                                          */
/*  **code : (GBK/GB2312) in Windows 7                                      */
/****************************************************************************/
/*  @Attention:                                                             */
/*  ---------------------------------------------------------------------   */
/*  |    Data    |  Behavior |     Offer     |          Content         |   */
/*  | 2015.01.16 |   create  |Carlos Wei (M) | ceate the document.      |   */
/*  ---------------------------------------------------------------------   */
/*                                                            MULTIBEANS.   */
/****************************************************************************/


#ifndef TYPE_H
#define TYPE_H

#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint8_t bool;

#define   boolean bool

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;


typedef uint8_t __u8;
typedef uint16_t __u16;

typedef int32_t __s32;
typedef uint32_t __u32;

typedef int8_t  s8;

typedef unsigned char BYTE;
typedef BYTE *PBYTE;
typedef unsigned int WORD;
typedef WORD *PWORD;
typedef unsigned long DWORD;
typedef DWORD *PDWORD;

typedef unsigned long ULONG;
typedef ULONG *PULONG;
typedef unsigned short USHORT;
typedef USHORT *PUSHORT;
typedef unsigned char UCHAR;
typedef UCHAR *PUCHAR;
typedef struct timer_t TIMER;

#ifndef UINT64
        typedef unsigned  long long UINT64;
#endif

#ifndef SINT64
        typedef signed    long long SINT64;
#endif

#ifndef FLOAT32
        typedef float               FLOAT32;
#endif

#ifndef UINT32
        typedef unsigned  int       UINT32;
#endif

#ifndef SINT32
        typedef int                 SINT32;
#endif

#ifndef UINT16
        typedef unsigned  short     UINT16;
#endif

#ifndef SINT16
        typedef short int           SINT16;
#endif

#ifndef UINT8
        typedef unsigned  char      UINT8 ;
#endif

#ifndef SINT8
        typedef signed  char        SINT8;
#endif

#ifndef VUINT32
        typedef volatile UINT32     VUINT32;
#endif

#ifndef VUINT16
        typedef volatile UINT16     VUINT16;
#endif


#ifndef VUINT8
        typedef volatile UINT8      VUINT8;
#endif

#ifndef false
    #define false             (UINT8)0
#endif
#ifndef true
    #define true              (UINT8)1
#endif
#define FALSE     0
#define TRUE      1


#define code

#define bit u8
#define idata

// math
#ifndef min
#define min(a,b) (((a)<(b))? (a):(b))
#endif

#ifndef max
#define max(a,b) (((a)>(b))? (a):(b))
#endif


#endif

