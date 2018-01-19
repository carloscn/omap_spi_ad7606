// OMAPL138 & TMS320C674X Project.
/****************************************************************************/
/*                                                                          */
/*  @file       : *_ad7606.h                                                */
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
#ifndef INCLUDE_AD7606_H_
#define INCLUDE_AD7606_H_


#include "type.h"
#include "spi.h"

#define                         OS0_GPIO_NUMBER                     131
#define                         OS1_GPIO_NUMBER                     130
#define                         OS2_GPIO_NUMBER                     24
#define                         CVA_GPIO_NUMBER                     31
#define                         CVB_GPIO_NUMBER                     30
#define                         RANGE_GPIO_NUMBER                   0
#define                         RESET_GPIO_NUMBER                   136
#define                         BUSY_GPIO_NUMBER                    29
#define                         FIRST_GPIO_NUMBER                   28
#define                         CS_GPIO_NUMBER                      23
#define                         SCLK_GPIO_NUMBER                    25
#define                         DA_GPIO_NUMBER                      135
#define                         DB_GPIO_NUMBER                      134
#define                         os0_high(self)          (    GPIOPinWrite( SOC_GPIO_0_REGS , self->hw.ctrl_line_os0,GPIO_PIN_HIGH )  )
#define                         os1_high(self)          (    GPIOPinWrite( SOC_GPIO_0_REGS , self->hw.ctrl_line_os1,GPIO_PIN_HIGH )  )
#define                         os2_high(self)          (    GPIOPinWrite( SOC_GPIO_0_REGS , self->hw.ctrl_line_os2,GPIO_PIN_HIGH )  )
#define                         cva_high(self)          (    GPIOPinWrite( SOC_GPIO_0_REGS , self->hw.ctrl_line_cva,GPIO_PIN_HIGH )  )
#define                         cvb_high(self)          (    GPIOPinWrite( SOC_GPIO_0_REGS , self->hw.ctrl_line_cvb,GPIO_PIN_HIGH )  )
#define                         reset_high(self)        (    GPIOPinWrite( SOC_GPIO_0_REGS , self->hw.ctrl_line_reset,GPIO_PIN_HIGH )  )
#define                         range_high(self)        (    GPIOPinWrite( SOC_GPIO_0_REGS , self->hw.ctrl_line_range,GPIO_PIN_HIGH )  )
#define                         cs_high(self)           (    GPIOPinWrite( SOC_GPIO_0_REGS , self->hw.cs,GPIO_PIN_HIGH )  )
#define                         sclk_high(self)         (    GPIOPinWrite( SOC_GPIO_0_REGS , self->hw.clk,GPIO_PIN_HIGH )  )
#define                         os0_low(self)           (    GPIOPinWrite( SOC_GPIO_0_REGS , self->hw.ctrl_line_os0,GPIO_PIN_LOW )  )
#define                         os1_low(self)           (    GPIOPinWrite( SOC_GPIO_0_REGS , self->hw.ctrl_line_os1,GPIO_PIN_LOW )  )
#define                         os2_low(self)           (    GPIOPinWrite( SOC_GPIO_0_REGS , self->hw.ctrl_line_os2,GPIO_PIN_LOW )  )
#define                         cva_low(self)           (    GPIOPinWrite( SOC_GPIO_0_REGS , self->hw.ctrl_line_cva,GPIO_PIN_LOW )  )
#define                         cvb_low(self)           (    GPIOPinWrite( SOC_GPIO_0_REGS , self->hw.ctrl_line_cvb,GPIO_PIN_LOW )  )
#define                         reset_low(self)         (    GPIOPinWrite( SOC_GPIO_0_REGS , self->hw.ctrl_line_reset,GPIO_PIN_LOW )  )
#define                         range_low(self)         (    GPIOPinWrite( SOC_GPIO_0_REGS , self->hw.ctrl_line_range,GPIO_PIN_LOW )  )
#define                         cs_low(self)            (    GPIOPinWrite( SOC_GPIO_0_REGS , self->hw.cs, GPIO_PIN_LOW )  )
#define                         sclk_low(self)          (    GPIOPinWrite( SOC_GPIO_0_REGS , self->hw.clk, GPIO_PIN_LOW )  )
#define                         da_read(self)           GPIOPinRead( (SOC_GPIO_0_REGS ), self->hw.da )
#define                         db_read(self)           GPIOPinRead( (SOC_GPIO_0_REGS ), self->hw.db )
#define                         ADC_CYCLE_NUM           2500
#define                         ADC_CHANNEL_0           0
#define                         ADC_CHANNEL_1           1
#define                         ADC_CHANNEL_2           2
#define                         ADC_CHANNEL_3           3
#define                         ADC_CHANNEL_4           4
#define                         ADC_CHANNEL_5           5
#define                         ADC_CHANNEL_6           6
#define                         ADC_CHANNEL_7           7


enum    ad7606_enum_over_sample {

    OVER_SAMPLE_1       =   0x0,            //  000
    OVER_SAMPLE_2       =   0x1,            //  001
    OVER_SAMPLE_4       =   0x2,            //  010
    OVER_SAMPLE_8       =   0x3,            //  011
    OVER_SAMPLE_16      =   0x4,            //  100
    OVER_SAMPLE_32      =   0x5,            //  101
    OVER_SAMPLE_64      =   0x6             //  110

};

enum    ad7606_enum_range {

    RANGE_5V            =   0,
    RANGE_10V           =   1

};
struct ad7606_hw_t {

    uint8   ctrl_line_range;
    uint8   ctrl_line_os0;
    uint8   ctrl_line_os1;
    uint8   ctrl_line_os2;
    uint8   ctrl_line_cva;
    uint8   ctrl_line_cvb;
    uint8   signal_line_busy;
    uint8   input_line_firstdata;
    uint8   ctrl_line_reset;
    uint8   da;
    uint8   db;
    uint8   cs;
    uint8   clk;
    uint16  spi_data[8];

};

struct ad7606_channels_data_t {

    uint8   channel_num;
    bool    convst_complete;
    struct {
        float   rom_area[ 8 ][ ADC_CYCLE_NUM ];
    } detail;

};

struct ad7606_config_t {

    enum    ad7606_enum_over_sample over_sample;
    enum    ad7606_enum_range range;
    u16                 delay;
    u32     sample_rate;

};

struct ad7606_t {

    struct ad7606_hw_t                  hw;
    struct ad7606_t                     *self;
    struct ad7606_channels_data_t       channel;
    struct ad7606_config_t              config;
    bool    is_not_busy;
    bool    is_new_data;
    bool    adc_count;

    void    ( *init )                   ( struct ad7606_t *self );
    void    ( *spi_read)                ( struct ad7606_t *self );
    void    ( *start_converst )         ( struct ad7606_t *self );
    void    ( *reset )                  ( struct ad7606_t *self );
    void    ( *sleep )                  ( struct ad7606_t *self );
    bool    ( *device_not_busy )        ( struct ad7606_t *self );
    void    ( *start_sample )           ( struct ad7606_t *self );
    void    ( *delay )                  ( struct ad7606_t *self,    u16 delay );
    void    ( *device_delay )           ( struct ad7606_t *self ,   u32 delay_time );
    void    ( *set_sample_rate )        ( struct ad7606_t *self,    u32 u32_sample_rate );
    void    ( *set_over_sample )        ( struct ad7606_t *self,    enum ad7606_enum_over_sample );

};

extern void    ad7606_read_sample_data  ( struct ad7606_t *self );
extern void    ad7606_start_convst      ( struct ad7606_t *self );
extern void    ad7606_device_reset      ( struct ad7606_t *self );
extern bool    ad7606_device_not_busy   ( struct ad7606_t *self );
extern void    ad7606_device_init       ( struct ad7606_t *self );
extern void    ad7606_spi_read          ( struct ad7606_t *self );
extern void    ad7606_delay             ( struct ad7606_t *self ,   u32 delay_time );
extern void    ad7606_set_sample        ( struct ad7606_t *self,    u32 sample_rate );
extern void    ad7606_set_range         ( struct ad7606_t *self,    enum ad7606_enum_range range );
extern void    ad7606_set_over_sample   ( struct ad7606_t *self,    enum ad7606_enum_over_sample over_sample);

#endif /* INCLUDE_AD7606_H_ */
