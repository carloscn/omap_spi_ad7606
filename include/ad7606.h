/*
 * ad7606.h
 *
 *  Created on: 2018Äê1ÔÂ17ÈÕ
 *      Author: root
 */

#ifndef INCLUDE_AD7606_H_
#define INCLUDE_AD7606_H_


#include "type.h"
#include "spi.h"

#define                         OS0_GPIO_NUMBER                     131
#define                         OS1_GPIO_NUMBER                     130
#define                         OS2_GPIO_NUMBER                     24
#define                         CVA_GPIO_NUMBER                     31
#define                         CVB_GPIO_NUMBER                     30
#define                         RANGE_GPIO_NUMBER                   23
#define                         RESET_GPIO_NUMBER                   136
#define                         BUSY_GPIO_NUMBER                    29
#define                         FIRST_GPIO_NUMBER                   28


#define                         os0_high(self)          (    GPIOPinWrite( SOC_GPIO_0_REGS , self->hw.ctrl_line_os0,GPIO_PIN_HIGH )  )
#define                         os1_high(self)          (    GPIOPinWrite( SOC_GPIO_0_REGS , self->hw.ctrl_line_os1,GPIO_PIN_HIGH )  )
#define                         os2_high(self)          (    GPIOPinWrite( SOC_GPIO_0_REGS , self->hw.ctrl_line_os2,GPIO_PIN_HIGH )  )
#define                         cva_high(self)          (    GPIOPinWrite( SOC_GPIO_0_REGS , self->hw.ctrl_line_cvb,GPIO_PIN_HIGH )  )
#define                         cvb_high(self)          (    GPIOPinWrite( SOC_GPIO_0_REGS , self->hw.ctrl_line_cva,GPIO_PIN_HIGH )  )
#define                         reset_high(self)        (    GPIOPinWrite( SOC_GPIO_0_REGS , self->hw.ctrl_line_reset,GPIO_PIN_HIGH )  )
#define                         range_high(self)        (    GPIOPinWrite( SOC_GPIO_0_REGS , self->hw.ctrl_line_range,GPIO_PIN_HIGH )  )
#define                         convst_high(self)       (    GPIOPinWrite( SOC_GPIO_0_REGS , self->hw.ctrl_line_convst,GPIO_PIN_HIGH )  )



#define                         os0_low(self)           (    GPIOPinWrite( SOC_GPIO_0_REGS , self->hw.ctrl_line_os0,GPIO_PIN_LOW )  )
#define                         os1_low(self)           (    GPIOPinWrite( SOC_GPIO_0_REGS , self->hw.ctrl_line_os1,GPIO_PIN_LOW )  )
#define                         os2_low(self)           (    GPIOPinWrite( SOC_GPIO_0_REGS , self->hw.ctrl_line_os2,GPIO_PIN_LOW )  )
#define                         cva_low(self)           (    GPIOPinWrite( SOC_GPIO_0_REGS , self->hw.ctrl_line_cva,GPIO_PIN_LOW )  )
#define                         cvb_low(self)           (    GPIOPinWrite( SOC_GPIO_0_REGS , self->hw.ctrl_line_cvb,GPIO_PIN_LOW )  )
#define                         reset_low(self)         (    GPIOPinWrite( SOC_GPIO_0_REGS , self->hw.ctrl_line_reset,GPIO_PIN_LOW )  )
#define                         range_low(self)         (    GPIOPinWrite( SOC_GPIO_0_REGS , self->hw.ctrl_line_range,GPIO_PIN_LOW )  )
#define                         convst_low(self)        (    GPIOPinWrite( SOC_GPIO_0_REGS , self->hw.ctrl_line_convst,GPIO_PIN_LOW )  )

#define                         busy_read( self )       (    )

#define                         ADC_CYCLE_NUM                       2500

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
    uint8   ctrl_line_convst;
    uint8   input_line_firstdata;
    uint8   ctrl_line_stby;
    uint8   ctrl_line_reset;

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
};


struct ad7606_t {

    struct ad7606_hw_t                  hw;
    struct ad7606_t                    *self;
    struct ad7606_channels_data_t    channel;
    struct ad7606_config_t            config;


    void ( *init )              ( struct ad7606_t *self );
    u16  ( *spi_read)           ( struct ad7606_t *self );
    void ( *set_over_sample )   ( struct ad7606_t *self,    enum ad7606_enum_over_sample );
    void ( *start_converst )    ( struct ad7606_t *self );
    void ( *reset )             ( struct ad7606_t *self );
    void ( *sleep )             ( struct ad7606_t *self );
    void ( *set_sample_rate )   ( struct ad7606_t *self,    u32 u32_sample_rate );
    void ( *delay )             ( struct ad7606_t *self,    u16 delay );
};




#endif /* INCLUDE_AD7606_H_ */
