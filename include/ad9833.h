// OMAPL138 & TMS320C674X Project.
/****************************************************************************/
/*                                                                          */
/*  @file       : *_ad9833.h                                                */
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
#ifndef INCLUDE_AD9833_H_
#define INCLUDE_AD9833_H_

#include "type.h"

#define                         SDI_GPIO_PORT_NUMBER                7
#define                         CLK_GPIO_PORT_NUMBER                6
#define                         FSY_GPIO_PORT_NUMBER                1

#define                         clk_high(self)                      ( GPIOPinWrite( SOC_GPIO_0_REGS, self->hw.clk, GPIO_PIN_HIGH ) )
#define                         clk_low(self)                       ( GPIOPinWrite( SOC_GPIO_0_REGS, self->hw.clk, GPIO_PIN_LOW ) )
#define                         sdi_high(self)                      ( GPIOPinWrite( SOC_GPIO_0_REGS, self->hw.sdi, GPIO_PIN_HIGH ) )
#define                         sdi_low(self)                       ( GPIOPinWrite( SOC_GPIO_0_REGS, self->hw.sdi, GPIO_PIN_LOW ) )
#define                         fsy_high(self)                      ( GPIOPinWrite( SOC_GPIO_0_REGS, self->hw.fsy, GPIO_PIN_HIGH ) )
#define                         fsy_low(self)                       ( GPIOPinWrite( SOC_GPIO_0_REGS, self->hw.fsy, GPIO_PIN_LOW ) )


#define                         AD9833_REG_RESET                    0x0100

#define                         AD9833_FREQ0_REG                    0
#define                         AD9833_FREQ1_REG                    1
#define                         SAMPLE_RATE_KHZ                         1000
#define                         ONE_CHANNEL_BUFFER_MAX                  2500

enum ad9833_wavetype_t{
    SIN,SQU,TRI
};

struct ad9833_hw_t {

    uint16 clk;
    uint16 sdi;
    uint16 fsy;
};

struct ad9833_t {

    struct ad9833_hw_t hw;
    struct ad9833_t *self;
    enum ad9833_wavetype_t wave_type;

    u16 delay;

    void (*write_reg)( struct ad9833_t *self, u16 reg_value);
    void (*init_device)( struct ad9833_t *self );
    //void (*set_wave_freq)( struct ad9833_t *self , float freqs_data);
    //void (*set_wave_type)( struct ad9833_t *self, enum ad9833_wavetype_t wave_type );
    //void (*set_wave_phase)( struct ad9833_t *self, u16 phase );
    void (*set_wave_para)( struct ad9833_t *self, u32 freqs_data, u16 phase, enum ad9833_wavetype_t wave_type );
};

extern void ad9833_set_para( struct ad9833_t *self,u32 freqs_data, u16 phase, enum ad9833_wavetype_t wave_type );
extern void ad9833_device_init( struct ad9833_t *self );
extern void ad9833_write_reg( struct ad9833_t *self, uint16_t data );
extern void ad9833_delay( struct ad9833_t *self );
extern void ad9833_gpio_init( void );

#endif /* INCLUDE_AD9833_H_ */
