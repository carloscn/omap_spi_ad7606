// OMAPL138 & TMS320C674X Project.
/****************************************************************************/
/*                                                                          */
/*  @file       : *_ad9833.c                                                */
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
#include "ad9833.h"

// GPIO0_6 ------  DAT
// GPIO0_5 ------  CLK
// GPIO0_0 ------  FSY

void ad9833_gpio_init( void )
{

    GPIOBank0Pin6PinMuxSetup();                 // DAT
    GPIOBank0Pin5PinMuxSetup();                 // CLK
    GPIOBank0Pin0PinMuxSetup();                 // FSY

    GPIODirModeSet(SOC_GPIO_0_REGS, SDI_GPIO_PORT_NUMBER, GPIO_DIR_OUTPUT );
    GPIODirModeSet(SOC_GPIO_0_REGS, CLK_GPIO_PORT_NUMBER, GPIO_DIR_OUTPUT );
    GPIODirModeSet(SOC_GPIO_0_REGS, FSY_GPIO_PORT_NUMBER, GPIO_DIR_OUTPUT );

    GPIOPinWrite( SOC_GPIO_0_REGS, SDI_GPIO_PORT_NUMBER, GPIO_PIN_LOW );
    GPIOPinWrite( SOC_GPIO_0_REGS, CLK_GPIO_PORT_NUMBER, GPIO_PIN_LOW );
    GPIOPinWrite( SOC_GPIO_0_REGS, FSY_GPIO_PORT_NUMBER, GPIO_PIN_LOW );

}

void ad9833_delay( struct ad9833_t *self )
{
    uint16_t delay;
    delay = self->delay;
    while( delay-- );
}

void ad9833_write_reg( struct ad9833_t *self, uint16_t data )
{
    uint8_t i;

    clk_high( self );
    fsy_high( self );
    ad9833_delay( self );
    fsy_low( self );
    for( i = 0; i < 16; i++ ) {
        if( data & 0x8000 )
            sdi_high( self );
        else
            sdi_low( self );
        ad9833_delay( self );
        clk_low( self );

        ad9833_delay( self );
        clk_high( self );
        data = data << 1;
    }
    fsy_high( self );
}

void ad9833_device_init( struct ad9833_t *self )
{
    ad9833_gpio_init();
    ad9833_write_reg( self, AD9833_REG_RESET  );
}

void ad9833_set_para( struct ad9833_t *self, u32 freqs_data, u16 phase, enum ad9833_wavetype_t wave_type )
{
    u32 dds_frequence_data;
    u16 dds_frequence_low;
    u16 dds_frequence_high;
    u16 phase_data;
    phase_data      =   phase | 0xC000;

    dds_frequence_data      =   freqs_data * 10.737;
    dds_frequence_low       =   dds_frequence_data & 0x3FFF;
    dds_frequence_low       |=  0x4000;
    dds_frequence_data      =   dds_frequence_data >> 14;
    dds_frequence_high      =   dds_frequence_data & 0x3FFF;
    dds_frequence_high      |=  0x4000;
    ad9833_write_reg( self, 0x0110 );
    ad9833_write_reg( self, 0x2100 );

    ad9833_write_reg( self,dds_frequence_low );
    ad9833_write_reg( self,dds_frequence_high );
    ad9833_write_reg( self, phase_data );

    if( wave_type == TRI ) {
        ad9833_write_reg( self, 0x2002 );
    }else if( wave_type == SQU ) {
        ad9833_write_reg(  self, 0x2028);
    }else {
        ad9833_write_reg( self, 0x2000 );
    }
}
// 使能REF,设置量程为+-12V
