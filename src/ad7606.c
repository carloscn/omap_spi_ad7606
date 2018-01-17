// OMAPL138 & TMS320C674X Project.
/****************************************************************************/
/*                                                                          */
/*  @file       : *_ad7606.c                                                */
/*  @Copyright  : Lifi.MLT (c) 2018 MULTIBEANS_ORG All rights reserved.     */
/*  @Revision   : Ver 1.0.                                                  */
/*  @Git        : https://github.com/lifimlt/omapl_ads8568_ad9833.git       */
/*  @Data       : 2018.01.17 Realse.                                        */
/*  @Belong     : PROJECT.                                                  */
/*                                                                          */
/*  **code : (GBK/GB2312) in Ubuntu 16.04. CCS v7.4 platform.               */
/****************************************************************************/
/*  @Attention:                                                             */
/*  ---------------------------------------------------------------------   */
/*  |    Data    |  Behavior |     Offer     |          Content         |   */
/*  | 2018.01.17 |   create  |Carlos Wei (M) | ceate the document.      |   */
/*  ---------------------------------------------------------------------   */
/*                                                            MULTIBEANS.   */
/****************************************************************************/

//  This document is AD7606
#include "global.h"
#include "ad7606.h"


extern uint16 spi_data;
extern uint16 spi_read_over_flag;

void    ad7606_device_reset( struct ad7606_t *self )
{
    reset_high( self );

    reset_low( self );

}

void    ad7606_start_convst( struct ad7606_t *self )
{
    cva_high( self );
    cva_low( self );
    cva_high( self );
    cvb_high( self );
    cvb_low( self );
}

void    ad7606_set_over_sample( struct ad7606_t *self, enum ad7606_enum_over_sample over_sample)
{
    self->config.over_sample = over_sample;

    if( self->config.over_sample & 0x01 )
        os0_high(self);
    else
        os0_low(self);

    if( ( self->config.over_sample & 0x02 ) >> 1 )
        os1_high( self );
    else
        os1_low( self );

    if( ( self->config.over_sample & 0x04 ) >> 2 )
        os2_high( self );
    else
        os2_low( self );

}

void    ad7606_set_range( struct ad7606_t *self, enum ad7606_enum_range range )
{
    self->config.range  =   range;

    if( self->config.range ) {
        range_high( self );
    }else{
        range_low( self );
    }
}

float    ad7606_read_sample_data( struct ad7606_t *self, uint8 channel_num )
{
    float adc_sample_data;
    self->channel.channel_num    =      channel_num;
    adc_sample_data     =   (float)self->spi_read( self );
    return adc_sample_data;
}

uint16    ad7606_spi_read_block( struct ad7606_t *self )
{
    uint16 i,counter = 0;
    // configrue the spi recv interrupt .
    SPIIntEnable(SOC_SPI_0_REGS, SPI_RECV_INT);
    // wait spi interrupt rec data;
    while( !spi_read_over_flag ) {
        counter ++;
        if( counter == 65535 )
            return 0;
    }
    return spi_data;

}










