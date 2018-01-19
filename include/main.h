// OMAPL138 & TMS320C674X Project.
/****************************************************************************/
/*                                                                          */
/*  @file       : *_main.h                                                  */
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

#ifndef INCLUDE_MAIN_H_
#define INCLUDE_MAIN_H_


void TIMER_INIT(unsigned int period);
void TIMER_INT_INIT(void);
void INT_INIT(void);
void PSC_INIT(void);
void AD9833_INIT( struct ad9833_t *dev );
void AD7606_INIT( struct ad7606_t *dev );
void GPIO_INIT(void);

extern void C6748_pinmuxConfig(UINT32 in_reg, UINT32 in_mask, UINT32 in_val);

#endif /* INCLUDE_MAIN_H_ */
