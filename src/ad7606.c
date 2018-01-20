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

uint32      busy_timeout    =    0;
bool        disable_start_adc_flag      =   false;
/**
 * \brief    This function is AD7606_delay_struct function.
 *
 * \offer    Wei Haochen
 *
 * \param    struct ad7606_t (in ad9833.h document)
 *
 * \return   None.
 *
 * \note     Not precise delay
 */
void    DELAY_US( uint32 us ) {
    uint16 i;
    for( i = 0; i < us; i++  ){
        asm( " NOP" );
    }
}


void    ad7606_delay( struct ad7606_t *self , uint32 delay_us )
{
    int i;
    for( i = 0; i < delay_us * 6; i++ );

}
/**
 * \brief    This function is AD7606 reset
 *
 * \offer    Wei Haochen
 *
 * \param    struct ad7606_t (in ad9833.h document)
 *
 * \return   None.
 *
 *                     ____
 * \note     RESET ___/    \____
 *                    |<-->|
 *                      1us
 */
void    ad7606_device_reset( struct ad7606_t *self )
{

    reset_low( self );
    asm( " NOP" );
    reset_high( self );
    asm( " NOP" );
    reset_low( self );
    asm( " NOP" );
}
/**
 * \brief    This function is AD7606 start convst
 *
 * \offer    Wei Haochen
 *
 * \param    struct ad7606_t (in ad9833.h document)
 *
 * \return   None.
 *
 *               ____       __________________
 * \note  covst_a    \_____/
 *               ____       __________________
 *        covst_b    \_____/
 *                   |<--->|
 *                     5us
 */
void    ad7606_start_convst( struct ad7606_t *self )
{
    cva_high( self );
    cvb_high( self );
    cva_low( self );
    cvb_low( self );
    cva_high( self );
    cvb_high( self );
}
/**
 * \brief    This function is AD7606 init
 *
 * \offer    Wei Haochen
 *
 * \param    struct ad7606_t (in ad9833.h document). enum oversample.
 *
 * \return   None.
 *
 * \note     set over sample support filter. In this project don't care.
 *           Please reference the AD7606 datasheet P29.
 */
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
/**
 * \brief    This function is AD7606 set range
 *
 * \offer    Wei Haochen
 *
 * \param    struct ad7606_t (in ad9833.h document)
 *
 * \return   None.
 *
 * \note     no detail
 */
void    ad7606_set_range( struct ad7606_t *self, enum ad7606_enum_range range )
{
    self->config.range  =   range;

    if( self->config.range ) {
        range_high( self );
    }else{
        range_low( self );
    }
}
/**
 * \brief    This function is AD7606 read sample data.
 *
 * \offer    Wei Haochen
 *
 * \param    struct ad7606_t (in ad9833.h document)
 *
 * \return   None.
 *
 * \note     Reference the datasheet P26
 *           1) drive convst a and b.
 *           2) wait busy signal.
 *           3) start spi bus read bits acording to the time.
 */

void    ad7606_read_sample_data( struct ad7606_t *self )
{

    busy_timeout = 0;
    // step 1: Start converst
    self->start_converst( self );
    disable_start_adc_flag      =   true;
    // step 2: wait busy signal.
    while( self->device_not_busy( self ) == 0 ) {
        busy_timeout ++ ;
        if( busy_timeout >= 465535 ){
            busy_timeout = 0;
            self->start_converst( self );
        }
    }
    // step 3: spi transfer
    self->spi_read( self ,0 );
    while( self->device_not_busy( self ) == 1 );
    disable_start_adc_flag      =   false;
}
/**
 * \brief    This function is AD7606 read busy bit.
 *
 * \offer    Wei Haochen
 *
 * \param    struct ad7606_t (in ad9833.h document)
 *
 * \return   None.
 *
 *                        ____________               _____
 * \note     busy _______/            \____________/      |
 *                ...... | can't read |  can read  |......
 */
bool       ad7606_device_not_busy( struct ad7606_t *self )
{
    // When the busy signal pin is high level, the ad7606 is avaible.
    // When the busy signal pin is low level, the AD7606 is convsting the sample data.
    return ( GPIOPinRead( SOC_GPIO_0_REGS , BUSY_GPIO_NUMBER ) );

}

/**
 * \brief    This function is AD7606 init
 *
 * \offer    Wei Haochen
 *
 * \param    struct ad7606_t (in ad9833.h document)
 *
 * \return   None.
 *
 * \note     no detail
 */
void       ad7606_device_init( struct ad7606_t *self )
{
    self->adc_count             =       0;
    self->is_new_data           =       false;
    self->config.over_sample    =       OVER_SAMPLE_1;
    self->config.range          =       RANGE_10V;
    self->config.delay          =       100;
    self->config.vin            =       3.3;
    self->is_not_busy           =       false;

    self->reset( self );
    self->device_delay( self, 50 );

}
/**
 * \brief    This function is AD7606 spi time.
 *
 * \offer    Wei Haochen
 *
 * \param    struct ad7606_t (in ad9833.h document)
 *
 * \return   None.
 *
 * \note     no detail
 */
void        ad7606_spi_read( struct ad7606_t *self, uint16 mode )
{
    uint16      cha_data = 0, chb_data = 0;
    uint16      pipe_num, bit_num;


    sclk_high( self );
    cs_low( self );

    if( mode == 0) {
        for( pipe_num = 0; pipe_num < 4; pipe_num ++ ) {

            cha_data    =   0;
            chb_data    =   0;

            for( bit_num = 0; bit_num < 16; bit_num ++  ) {
                cha_data    <<=     1;
                chb_data    <<=     1;
                /*
                 *  if no delay time , this freq is : fclk  = 0.05MHz
                 * */
                sclk_low( self );
                cha_data    |=      (da_read( self ) & 0x0001);             // read it need 6us time
                chb_data    |=      (db_read( self ) & 0x0001);             // read it nedd 6us time
                sclk_high( self );
            }
            *(self->hw.spi_data + pipe_num )       =     cha_data;
            *(self->hw.spi_data + pipe_num + 4)    =     chb_data;
        }
    }else {
        for( pipe_num = 0; pipe_num < 8; pipe_num ++ ) {
            cha_data    =   0;
            for( bit_num = 0; bit_num < 16; bit_num ++  ) {

                sclk_low( self );
                cha_data    <<=     1;
                cha_data    |=   da_read( self );
                sclk_high( self );

            }
            *(self->hw.spi_data + pipe_num )       =     cha_data;
        }
    }
    cs_high( self );
}


void        ad7606_save_datas( struct ad7606_t *self ) {

    self->channel.detail.rom_area[ADC_CHANNEL_0][ self->adc_count ] =    self->quantify_data(  self ,self->hw.spi_data[ADC_CHANNEL_0]);
    self->channel.detail.rom_area[ADC_CHANNEL_1][ self->adc_count ] =    self->quantify_data(  self ,self->hw.spi_data[ADC_CHANNEL_1]);
    self->channel.detail.rom_area[ADC_CHANNEL_2][ self->adc_count ] =    self->quantify_data(  self ,self->hw.spi_data[ADC_CHANNEL_2]);
    self->channel.detail.rom_area[ADC_CHANNEL_3][ self->adc_count ] =    self->quantify_data(  self ,self->hw.spi_data[ADC_CHANNEL_3]);
    self->channel.detail.rom_area[ADC_CHANNEL_4][ self->adc_count ] =    self->quantify_data(  self ,self->hw.spi_data[ADC_CHANNEL_4]);
    self->channel.detail.rom_area[ADC_CHANNEL_5][ self->adc_count ] =    self->quantify_data(  self ,self->hw.spi_data[ADC_CHANNEL_5]);
    self->channel.detail.rom_area[ADC_CHANNEL_6][ self->adc_count ] =    self->quantify_data(  self ,self->hw.spi_data[ADC_CHANNEL_6]);
    self->channel.detail.rom_area[ADC_CHANNEL_7][ self->adc_count ] =    self->quantify_data(  self ,self->hw.spi_data[ADC_CHANNEL_7]);

    self->adc_count ++ ;

    if( self->adc_count >= ADC_CYCLE_NUM ) {
        self->adc_count    =   0;
    }

}


void         ad7606_set_sample( struct ad7606_t *self, u32 sample_rate )
{

    self->config.sample_rate = (228000000/(sample_rate*20));
}

uint16  read_da_line( struct ad7606_t *self )
{
    if( da_read( self ) == 1 ) {
        return 1;
    }else{
        return 0;
    }
}

float   ad7606_quantify_data( struct ad7606_t *self, uint16 data )
{
    float range;
    float vin;
    if( self->config.range == RANGE_10V ) {
        range = 10.0f;
    }else {
        range = 5.0f;
    }

    vin = self->config.vin;

    return ((float)data)*range/32768/(vin/vin);
}





