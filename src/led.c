// OMAPL138 & TMS320C674X Project.
/****************************************************************************/
/*                                                                          */
/*  @file       : *_led.c                                                  */
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

#include "global.h"
#include "led.h"

void leds_flash( void )
{
    int i;
    LED1_ON();
    LED2_ON();
    LED3_ON();
    LED4_ON();
    for( i = 0; i < 64534; i ++ );
    LED1_OFF();
    LED2_OFF();
    LED3_OFF();
    LED4_OFF();


}
