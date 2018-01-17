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


void Delay(volatile unsigned int count);
void AD8568GPIOInit(void);
void InterruptInit(void);
void AD8568Isr(void);
void GPIOPinMuxSetup(void);
void PSCInit(void);
void EMIFAInit(void);
void AD8568Reset(void);
void AD8568Start(void);
void AD8568Init(unsigned int SamplingRate);
void AD8568_WriteReg(unsigned int value);

// 中断服务函数
void TimerIsr(void);
// 定时器 / 计数器初始化
void TimerInit(unsigned int period);
// 定时器 / 计数器中断初始化
void TimerInterruptInit(void);





extern unsigned int TMR_PERIOD_LSB32;
extern unsigned int TMR_PERIOD_MSB32;


typedef struct {

    struct channel_datas {

        float channal_0[ ONE_CHANNEL_BUFFER_MAX ];
        float channal_1[ ONE_CHANNEL_BUFFER_MAX ];
        float channal_2[ ONE_CHANNEL_BUFFER_MAX ];
        float channal_3[ ONE_CHANNEL_BUFFER_MAX ];
        float channal_4[ ONE_CHANNEL_BUFFER_MAX ];
        float channal_5[ ONE_CHANNEL_BUFFER_MAX ];
        float channal_6[ ONE_CHANNEL_BUFFER_MAX ];
        float channal_7[ ONE_CHANNEL_BUFFER_MAX ];
    } ch_data;
    unsigned int converted_flag;
    unsigned int adc_count;

} AllChannelData;

extern void init_ad9833( struct ad9833_t *dev );
#endif /* INCLUDE_MAIN_H_ */
