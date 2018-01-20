// OMAPL138 & TMS320C674X Project.
/****************************************************************************/
/*                                                                          */
/*  @file       : *_main.c                                                  */
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

/**
 * \brief   This document configures the trigger level type for which an
 *          interrupt is required to occur.
 *
 * \param   baseAdd    The memory address of the GPIO instance being used.
 *
 * \param   pinNumber  The serial number of the GPIO pin.
 *                     The 144 GPIO pins have serial numbers from 1 to 144.
 *
 * \param   intType    This specifies the trigger level type. This can take
 *                     one of the following four values:
 *                     1> GPIO_INT_TYPE_NOEDGE, to not generate any interrupts.
 *                     2> GPIO_INT_TYPE_FALLEDGE, to generate an interrupt on
 *                        the falling edge of a signal on that pin.
 *                     3> GPIO_INT_TYPE_RISEDGE, to generate an interrupt on the
 *                        rising edge of a signal on that pin.
 *                     4> GPIO_INT_TYPE_BOTHEDGE, to generate interrupts on both
 *                        rising and falling edges of a signal on that pin.
 *
 * \return   None.
 *
 * \License  Configuring the trigger level type for generating interrupts is not
 *           enough for the GPIO module to generate interrupts. The user should
 *           also enable the interrupt generation capability for the bank to which
 *           the pin belongs to. Use the function GPIOBankIntEnable() to do the same.
 */

#include "global.h"
#include "main.h"

bool                   adc_complete_flag    =   0;
bool                   leds_flash_flag = 0;
struct ad9833_t        ad9833_dev;
struct ad7606_t        ad7606_dev;
void DELAY_US( uint32 us ) ;
int main( void )
 {
    /*
     * Sample Rate:
     * set value Hz
     * */
    u32 sample_rate  =   500;
    CacheEnableMAR((unsigned int)0xC0000000, (unsigned int)0x8000000);
    CacheEnable(L1DCFG_L1DMODE_32K | L1PCFG_L1PMODE_32K | L2CFG_L2MODE_256K);
    UARTStdioInit();
    UARTPuts("This is uart data.....\r\n", -2);

    PSC_INIT();
    GPIO_INIT();
    INT_INIT();

    /*
     ** Device init.
     */
    AD9833_INIT( &ad9833_dev );
    AD7606_INIT( &ad7606_dev );

    ad7606_dev.set_sample_rate( &ad7606_dev, sample_rate);
    ad9833_dev.set_wave_para( &ad9833_dev, 100000, 0, SIN );
    leds_flash();
    TIMER_INIT( ad7606_dev.config.sample_rate );
   // TIMER_INT_INIT();

    while( 1 ) {
        ad7606_dev.reset( &ad7606_dev );
#if 0
        GPIOPinWrite( SOC_GPIO_0_REGS ,CVA_GPIO_NUMBER, GPIO_PIN_HIGH );
        DELAY_US(50);
        GPIOPinWrite( SOC_GPIO_0_REGS ,CVA_GPIO_NUMBER, GPIO_PIN_LOW );
        DELAY_US(50);
       // GPIOPinWrite( SOC_GPIO_0_REGS ,CVB_GPIO_NUMBER, GPIO_PIN_HIGH );
       // GPIOPinWrite( SOC_GPIO_0_REGS ,CVB_GPIO_NUMBER, GPIO_PIN_LOW );
#endif
        /*
        //leds_flash();
        // ad7606_dev.start_sample( &ad7606_dev );
        // Sample 2500 points flash  once time.
        if( leds_flash_flag == true ) {
            leds_flash();
            leds_flash_flag = false;
        }
        */
    }
}
/**
 * \brief    This function is TIMTER_ISR
 *
 * \offer    Wei Haochen
 *
 * \return   None.
 *
 * \note     start the ADC conversion timer to complete the sampling rate setting.
 */



float rom[ ADC_CYCLE_NUM ];
uint16 count = 0;
void TIMER_ISR(void)
{
    IntEventClear(SYS_INT_T64P2_TINTALL);
    TimerIntStatusClear(SOC_TMR_2_REGS, TMR_INT_TMR12_NON_CAPT_MODE);

   // if( disable_start_adc_flag == false )
        ad7606_dev.start_sample( &ad7606_dev );
    ad7606_dev.save_data( &ad7606_dev );
}
/**
 * \brief    This function is TIMTER_INIT
 *
 * \offer    Wei Haochen
 *
 * \return   None.
 *
 * \note     no detail
 */
void TIMER_INIT(unsigned int period)
{
    u32 TMR_PERIOD_MSB32 = 0;
    TimerConfigure(SOC_TMR_2_REGS, TMR_CFG_64BIT_CLK_INT);
    TimerPeriodSet(SOC_TMR_2_REGS, TMR_TIMER12, period);
    TimerPeriodSet(SOC_TMR_2_REGS, TMR_TIMER34, TMR_PERIOD_MSB32);
    TimerEnable(SOC_TMR_2_REGS, TMR_TIMER12, TMR_ENABLE_CONT);
}
/**
 * \brief    This function is TIMER_INIT_INIT
 *
 * \offer    Wei Haochen
 *
 * \return   None.
 *
 * \note     no detail
 */
void TIMER_INT_INIT(void)
{
    IntRegister(C674X_MASK_INT5, TIMER_ISR);
    IntEventMap(C674X_MASK_INT5, SYS_INT_T64P2_TINTALL);
    IntEnable(C674X_MASK_INT5);
    TimerIntEnable(SOC_TMR_2_REGS, TMR_INT_TMR12_NON_CAPT_MODE);
}
/**
 * \brief    This function is INT_INIT
 *
 * \offer    Wei Haochen
 *
 * \return   None.
 *
 * \note     no detail
 */
void INT_INIT(void)
{
    IntDSPINTCInit();
    IntGlobalEnable();
}
/**
 * \brief    This function is PSC_INIT
 *
 * \offer    Wei Haochen
 *
 * \return   None.
 *
 * \note     no detail
 */
void PSC_INIT(void)
{
    // Enable GPIO set.
    //PSCModuleControl(SOC_PSC_0_REGS, HW_PSC_SPI0, PSC_POWERDOMAIN_ALWAYS_ON, PSC_MDCTL_NEXT_ENABLE);
    PSCModuleControl(SOC_PSC_1_REGS, HW_PSC_GPIO, PSC_POWERDOMAIN_ALWAYS_ON, PSC_MDCTL_NEXT_ENABLE);


}
/**
 * \brief    This function is AD9833 init
 *
 * \offer    Wei Haochen
 *
 * \param    struct ad9833_t (in ad9833.h document)
 *
 * \return   None.
 *
 * \note     no detail
 */
void AD9833_INIT( struct ad9833_t *dev )
{
    dev->delay            =   100;
    dev->set_wave_para    =   &ad9833_set_para;
    dev->init_device      =   &ad9833_device_init;
    dev->write_reg        =   &ad9833_write_reg;
    dev->hw.clk           =   CLK_GPIO_PORT_NUMBER;
    dev->hw.fsy           =   FSY_GPIO_PORT_NUMBER;
    dev->hw.sdi           =   SDI_GPIO_PORT_NUMBER;

    dev->init_device( dev );

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
void AD7606_INIT( struct ad7606_t *dev )
{

    dev->hw.ctrl_line_cva           =   CVA_GPIO_NUMBER;
    dev->hw.ctrl_line_cvb           =   CVB_GPIO_NUMBER;
    dev->hw.ctrl_line_os0           =   OS0_GPIO_NUMBER;
    dev->hw.ctrl_line_os1           =   OS1_GPIO_NUMBER;
    dev->hw.ctrl_line_os2           =   OS2_GPIO_NUMBER;
    dev->hw.ctrl_line_range         =   RANGE_GPIO_NUMBER;
    dev->hw.ctrl_line_reset         =   RESET_GPIO_NUMBER;
    dev->hw.input_line_firstdata    =   FIRST_GPIO_NUMBER;
    dev->hw.signal_line_busy        =   BUSY_GPIO_NUMBER;
    dev->hw.clk                     =   SCLK_GPIO_NUMBER;
    dev->hw.cs                      =   CS_GPIO_NUMBER;
    dev->hw.da                      =   DA_GPIO_NUMBER;
    dev->hw.db                      =   DB_GPIO_NUMBER;

    dev->device_delay               =   &ad7606_delay;
    dev->set_over_sample            =   &ad7606_set_over_sample;
    dev->start_converst             =   &ad7606_start_convst;
    dev->reset                      =   &ad7606_device_reset;
    dev->device_not_busy            =   &ad7606_device_not_busy;
    dev->init                       =   &ad7606_device_init;
    dev->spi_read                   =   &ad7606_spi_read;
    dev->start_sample               =   &ad7606_read_sample_data;
    dev->set_sample_rate            =   &ad7606_set_sample;
    dev->quantify_data              =   &ad7606_quantify_data;
    dev->save_data                  =   &ad7606_save_datas;

    dev->init( dev );
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
 * \note     // J3
 * P1( SPI0_CLK /GPIO_1_8 )                       RD
 * P3( SPI0_SOMI/GPIO_8_6 )                      DB7
 * P5( SPI0_SIMO/GPIO_8_5 )                        DB8
 * P8( SPI0_Sn0 /GPIO_1_6 )                       CS
 * P2( GPIO_8_2 )                   OS0
 * P4( GPIO_8_1 )                   OS1
 * P6( GPIO_1_7 )                   OS2
 * P10( GND )                       RAGE
 * J4
 * P1( GPIO_1_14 )                  CVA
 * P3( GPIO_1_13 )                  CVB
 * P5( GPIO_8_7 )                   RST
 * P7( GPIO_1_12 )                  BUSY
 * P9( GPIO_1_11 )                  FIRST
 */

void GPIO_INIT(void)
{

    C6748_pinmuxConfig( 0 , 0x44000000, 0x44000000);
    C6748_pinmuxConfig( 1 , 0x88800800, 0x88800800);
    C6748_pinmuxConfig( 2 , 0x40044440, 0x40044440);
    C6748_pinmuxConfig( 3 , 0x44444404, 0x44444404);
    C6748_pinmuxConfig( 4 , 0x00220044, 0x00220044);

    GPIODirModeSet( SOC_GPIO_0_REGS , OS0_GPIO_NUMBER, GPIO_DIR_OUTPUT);
    GPIODirModeSet( SOC_GPIO_0_REGS , OS1_GPIO_NUMBER, GPIO_DIR_OUTPUT);
    GPIODirModeSet( SOC_GPIO_0_REGS , OS2_GPIO_NUMBER, GPIO_DIR_OUTPUT);
    GPIODirModeSet( SOC_GPIO_0_REGS , RANGE_GPIO_NUMBER, GPIO_DIR_OUTPUT);
    GPIODirModeSet( SOC_GPIO_0_REGS , CVA_GPIO_NUMBER, GPIO_DIR_OUTPUT);
    GPIODirModeSet( SOC_GPIO_0_REGS , CVB_GPIO_NUMBER, GPIO_DIR_OUTPUT);
    GPIODirModeSet( SOC_GPIO_0_REGS , RESET_GPIO_NUMBER, GPIO_DIR_OUTPUT);
    GPIODirModeSet( SOC_GPIO_0_REGS , BUSY_GPIO_NUMBER, GPIO_DIR_INPUT);
    GPIODirModeSet( SOC_GPIO_0_REGS , FIRST_GPIO_NUMBER, GPIO_DIR_INPUT);
    GPIODirModeSet( SOC_GPIO_0_REGS , CS_GPIO_NUMBER, GPIO_DIR_OUTPUT);
    GPIODirModeSet( SOC_GPIO_0_REGS , SCLK_GPIO_NUMBER, GPIO_DIR_OUTPUT);
    GPIODirModeSet( SOC_GPIO_0_REGS , DA_GPIO_NUMBER, GPIO_DIR_INPUT);
    GPIODirModeSet( SOC_GPIO_0_REGS , DB_GPIO_NUMBER, GPIO_DIR_INPUT);
    GPIODirModeSet( SOC_GPIO_0_REGS , LED1_GPIO_NUMBER , GPIO_DIR_OUTPUT);
    GPIODirModeSet( SOC_GPIO_0_REGS , LED2_GPIO_NUMBER , GPIO_DIR_OUTPUT);
    GPIODirModeSet( SOC_GPIO_0_REGS , LED3_GPIO_NUMBER , GPIO_DIR_OUTPUT);
    GPIODirModeSet( SOC_GPIO_0_REGS , LED4_GPIO_NUMBER , GPIO_DIR_OUTPUT);

    GPIOPinWrite( SOC_GPIO_0_REGS ,RESET_GPIO_NUMBER, GPIO_PIN_LOW );
    GPIOPinWrite( SOC_GPIO_0_REGS ,CS_GPIO_NUMBER, GPIO_PIN_HIGH );
    GPIOPinWrite( SOC_GPIO_0_REGS ,CVA_GPIO_NUMBER, GPIO_PIN_HIGH );
    GPIOPinWrite( SOC_GPIO_0_REGS ,CVB_GPIO_NUMBER, GPIO_PIN_HIGH );
    GPIOPinWrite( SOC_GPIO_0_REGS ,SCLK_GPIO_NUMBER, GPIO_PIN_HIGH );


}

#if 0
uint16 count = 0;
extern uint16 spi_data[256];
extern bool flag;
uint16 txcount = 0;
UINT16 mcount = 0;
void SPIIsr(void)
{

    unsigned int intCode = 0;
    IntEventClear(SYS_INT_SPI0_INT);
    intCode = SPIInterruptVectorGet(SOC_SPI_0_REGS);

    while (intCode) {



        if(intCode == SPI_RECV_FULL) {

            datass = *( spi_data + count )  = SPIDataReceive(SOC_SPI_0_REGS);
            //printf("current spi data: %d \n", datass );
            count ++;

            if( mcount >= 4  ) {
                mcount = 0;
                flag = 0;
                SPIIntDisable(SOC_SPI_0_REGS, SPI_RECV_INT);
            }
            if( count >= 255  ) {
                count =0;
            }
            mcount ++;
        }
#if 1
        if(intCode == SPI_TX_BUF_EMPTY)
        {

            txcount ++;
            SPITransmitData1(SOC_SPI_0_REGS, *(spi_data + txcount));

            if( mcount >= 4){
                SPIIntDisable(SOC_SPI_0_REGS, SPI_TRANSMIT_INT);
                mcount = 0;
            }
            if( txcount >= 255  )  txcount = 0;
        }
#endif
        intCode = SPIInterruptVectorGet(SOC_SPI_0_REGS);
    }
}
#endif
