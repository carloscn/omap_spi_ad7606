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

#include "TL6748.h"
#include "hw_types.h"
#include "hw_syscfg0_C6748.h"
#include "soc_C6748.h"
#include "psc.h"
#include "gpio.h"
#include "interrupt.h"
#include "emifa.h"
#include "uartStdio.h"
#include "timer.h"
#include "dspcache.h"
#include "type.h"
#include "ad9833.h"
#include "led.h"
#include "../include/EMIFAPinmuxSetup.h"




#define PINMUX11_BUSY_ENABLE     (SYSCFG_PINMUX11_PINMUX11_19_16_GPIO5_11 << \
                                    SYSCFG_PINMUX11_PINMUX11_19_16_SHIFT)

#define PINMUX11_CONVST_ENABLE   (SYSCFG_PINMUX11_PINMUX11_11_8_GPIO5_13 << \
                                    SYSCFG_PINMUX11_PINMUX11_11_8_SHIFT)

#define PINMUX11_RESRT_ENABLE    (SYSCFG_PINMUX11_PINMUX11_15_12_GPIO5_12 << \
                                    SYSCFG_PINMUX11_PINMUX11_15_12_SHIFT)

#define SW_BREAKPOINT     asm(" SWBP 0 ")


#endif /* INCLUDE_GLOBAL_H_ */
