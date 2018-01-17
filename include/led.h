// OMAPL138 & TMS320C674X Project.
/****************************************************************************/
/*                                                                          */
/*  @file       : *_led.h                                                   */
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
#ifndef INCLUDE_LED_H_
#define INCLUDE_LED_H_

#define                     LED1_GPIO_PORT_NUMBER               6
#define                     LED2_GPIO_PORT_NUMBER               2
#define                     LED3_GPIO_PORT_NUMBER               3

#define                     LED1_ON()                             GPIOPinWrite( SOC_GPIO_0_REGS, LED1_GPIO_PORT_NUMBER, GPIO_PIN_HIGH )
#define                     LED2_ON()                             GPIOPinWrite( SOC_GPIO_0_REGS, LED2_GPIO_PORT_NUMBER, GPIO_PIN_HIGH )
#define                     LED3_ON()                             GPIOPinWrite( SOC_GPIO_0_REGS, LED3_GPIO_PORT_NUMBER, GPIO_PIN_HIGH )
#define                     LED1_OFF()                            GPIOPinWrite( SOC_GPIO_0_REGS, LED1_GPIO_PORT_NUMBER, GPIO_PIN_LOW )
#define                     LED2_OFF()                            GPIOPinWrite( SOC_GPIO_0_REGS, LED2_GPIO_PORT_NUMBER, GPIO_PIN_LOW )
#define                     LED3_OFF()                            GPIOPinWrite( SOC_GPIO_0_REGS, LED3_GPIO_PORT_NUMBER, GPIO_PIN_LOW )

extern void led_gpio_init( void );
extern void leds_flash( void );

#endif /* INCLUDE_LED_H_ */
