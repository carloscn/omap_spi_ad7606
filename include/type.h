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
#define BOOL bool
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

