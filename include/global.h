// OMAPL138 & TMS320C674X Project.
/****************************************************************************/
/*                                                                          */
/*  @file       : *_global.h                                                */
/*  @Copyright  : Lifi.MLT (c) 2018 MULTIBEANS_ORG All rights reserved.     */
/*  @Revision   : Ver 1.0.                                                  */
/*  @Git        : https://github.com/lifimlt/omapl_ads8568_ad9833.git       */
/*  @Data       : 2018.01.16 Realse.                                        */
/*  @Belong     : PROJECT.                                                  */
/*                                                                          */
/*  **code : (GBK/GB2312) in Ubuntu 16.04. CCS v7.4 platform.               */
/****************************************************************************/
/*  @Attention:                                                             */
/*  ---------------------------------------------------------------------   */
/*  |    Data    |  Behavior |     Offer     |          Content         |   */
/*  | 2018.01.16 |   create  |Carlos Wei (M) | ceate the document.      |   */
/*  ---------------------------------------------------------------------   */
/*                                                            MULTIBEANS.   */
/****************************************************************************/
#ifndef INCLUDE_GLOBAL_H_
#define INCLUDE_GLOBAL_H_
#include "type.h"
#include "c6748.h"
#include "c6748_gpio.h"
#include "TL6748.h"
#include "hw_types.h"
#include "hw_syscfg0_C6748.h"
#include "soc_C6748.h"
#include "psc.h"
#include "gpio.h"
#include "interrupt.h"
#include "uartStdio.h"
#include "timer.h"
#include "dspcache.h"
#include "ad9833.h"
#include "led.h"
#include "ad7606.h"
#include "spi0.h"


#define SW_BREAKPOINT     asm(" SWBP 0 ")


#endif /* INCLUDE_GLOBAL_H_ */
