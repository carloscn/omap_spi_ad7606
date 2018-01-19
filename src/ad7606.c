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
 *                     >50ns
 */
void    ad7606_device_reset( struct ad7606_t *self )
{

    reset_low( self );
    self->device_delay( self, 40 );
    reset_high( self );
    self->device_delay( self, 40 );
    reset_low( self );
    self->device_delay( self, 40 );
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
 *               ___________         _________
 *        covst_b           \_______/
 *                         |<------->|
 *                           > 0.5ms
 */
void    ad7606_start_convst( struct ad7606_t *self )
{
    cva_high( self );
    cvb_high( self );
    cva_low( self );

    self->device_delay( self, 20 );             // No details, give 20 us
    cva_high( self );
    // Should hold < 500-us
    cvb_low( self );
    self->device_delay( self, 250 );            // Should hold < 500-us
    // According AD7606 datasheet, this need hold Tconv = 4.15 us time.
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
    // step 2: wait busy signal.
    while( self->device_not_busy( self ) == 0 );
    // step 3: spi transfer
    self->spi_read( self );
    while( self->device_not_busy( self ) == 1 );

    return;

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
    return ( GPIOPinRead( SOC_GPIO_0_REGS , BUSY_GPIO_NUMBER ) ) ?1:0;

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
    self->reset( self );
    self->device_delay( self, 50 );
    self->adc_count     =   0;


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
void        ad7606_spi_read( struct ad7606_t *self )
{
    uint16      cha_data = 0, chb_data = 0;
    uint16    pipe_num, bit_num;
    if( self->is_new_data == false  ) {

        sclk_high( self );
        cs_low( self );

        for( pipe_num = 0; pipe_num < 4; pipe_num ++ ) {

            cha_data    =   0;
            chb_data    =   0;
            for( bit_num = 0; bit_num < 16; bit_num ++  ) {

                cha_data    <<=     1;
                chb_data    <<=     1;
                sclk_low( self );
                cha_data    |=   da_read( self )?1:0;
                chb_data    |=   db_read( self )?1:0;
                sclk_high( self );

            }

            *(self->hw.spi_data + pipe_num )       =     cha_data;
            *(self->hw.spi_data + pipe_num + 4)    =     chb_data;
        }
        cs_high( self );
        self->is_new_data       =   true;
    }else{
        return;
    }

}

void         ad7606_set_sample( struct ad7606_t *self, u32 sample_rate )
{
    if(sample_rate > 510000) sample_rate = 510000;
    self->config.sample_rate = 228000000/sample_rate;
}







