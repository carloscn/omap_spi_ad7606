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


// all_channel_datas.ch_data.channal_0
// J3
// P1( SPI0_CLK )                   RD
// P3( SPI0_SOMI )                  DB7
// P5( SPI0_SIMO )                  DB15( please ensure)
// P7( SPI0_EN )                    CS

// P2( GPIO_8_2 )                   OS0
// P4( GPIO_8_1 )                   OS1
// P6( GPIO_1_7 )                   OS2
// P8( GPIO_1_6 )                   RAGE


// J4
// P1( GPIO_1_14 )                  CVA
// P3( GPIO_1_13 )                  CVB
// P5( GPIO_8_7 )                   RST
// P7( GPIO_1_12 )                  BUSY
// P9( GPIO_1_11 )                  FIRST

#include "global.h"
#include "main.h"

              // DSP C6748 ÍâÉè¼Ä´æÆ÷
bool                    leds_flash_flag = 0;
struct ad9833_t        ad9833_dev;
struct ad7606_t        ad7606_dev;


int main( void )
{

	CacheEnableMAR((unsigned int)0xC0000000, (unsigned int)0x8000000);
	CacheEnable(L1DCFG_L1DMODE_32K | L1PCFG_L1PMODE_32K | L2CFG_L2MODE_256K);
	UARTStdioInit();
	/* Baud rate: 57600 uart2 */
    UARTPuts("This is uart data.....\r\n", -2);
    PSCInit();
    //GPIOBankPinInit();
    GPIO_INIT();
    //init_ad9833( &ad9833_dev );
    //ad9833_dev.set_wave_para( &ad9833_dev, 100000, 0, SIN );
    InterruptInit();
    int j = 0;
    int i;
	while(1) {


        GPIO_setOutput(GPIO_BANK0, GPIO_PIN5, 1);
        GPIO_setOutput(GPIO_BANK0, GPIO_PIN0, 1);
        GPIO_setOutput(GPIO_BANK0, GPIO_PIN1, 1);
        GPIO_setOutput(GPIO_BANK0, GPIO_PIN2, 1);
        for( i = 0; i < 65535; i ++ ){
            for( j = 0; j < 65; j ++);
        }
        //leds_flash();
        GPIO_setOutput(GPIO_BANK0, GPIO_PIN5, 0);
        GPIO_setOutput(GPIO_BANK0, GPIO_PIN0, 0);
        GPIO_setOutput(GPIO_BANK0, GPIO_PIN1, 0);
        GPIO_setOutput(GPIO_BANK0, GPIO_PIN2, 0);
        for( i = 0; i < 65535; i ++ ){
            for( j = 0; j < 65; j ++);
        }
	    UARTPuts("LED flash once \n", -2);
	    if( leds_flash_flag == 1 ) {

	        leds_flash_flag = 0;
	    }
	}
}

void TimerIsr(void)
{
    IntEventClear(SYS_INT_T64P2_TINTALL);
    TimerIntStatusClear(SOC_TMR_2_REGS, TMR_INT_TMR12_NON_CAPT_MODE);
}

void InterruptInit(void)
{
	IntDSPINTCInit();
	IntGlobalEnable();
}


void PSCInit(void)
{
    // Enable GPIO set.
    PSCModuleControl(SOC_PSC_1_REGS, HW_PSC_GPIO, PSC_POWERDOMAIN_ALWAYS_ON, PSC_MDCTL_NEXT_ENABLE);
    // Enable EMIFA (ADS8568 connected) set.
    PSCModuleControl(SOC_PSC_0_REGS, HW_PSC_EMIFA, PSC_POWERDOMAIN_ALWAYS_ON, PSC_MDCTL_NEXT_ENABLE);
}

void init_ad9833( struct ad9833_t *dev )
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
 * struct ad7887_chip_info - chip specifc information
 * @int_vref_mv:    the internal reference voltage
 * @channel:        channel specification
 */

void GPIO_INIT( void )
{
    C6748_pinmuxConfig( 0 , 0x44000000, 0x44000000);
    C6748_pinmuxConfig( 1 , 0x88888888, 0x88888888);
    C6748_pinmuxConfig( 2 , 0x44444440, 0x44444440);
    C6748_pinmuxConfig( 3 , 0x44001111, 0x44001111);
    C6748_pinmuxConfig( 4 , 0x00220044, 0x00220044);

    GPIO_setDir( GPIO_BANK0, GPIO_PIN5, GPIO_OUTPUT );
    GPIO_setDir( GPIO_BANK0, GPIO_PIN0, GPIO_OUTPUT );
    GPIO_setDir( GPIO_BANK0, GPIO_PIN1, GPIO_OUTPUT );
    GPIO_setDir( GPIO_BANK0, GPIO_PIN2, GPIO_OUTPUT );
    // P2( GPIO_8_2 )                   OS0
    // P4( GPIO_8_1 )                   OS1
    // P6( GPIO_1_7 )                   OS2
    // P8( GPIO_1_6 )                   RAGE


    // J4
    // P1( GPIO_1_14 )                  CVA
    // P3( GPIO_1_13 )                  CVB
    // P5( GPIO_8_7 )                   RST
    // P7( GPIO_1_12 )                  BUSY
    // P9( GPIO_1_11 )                  FIRST





}


void GPIOBankPinInit(void)
{

   // ·¶Î§ 1-144
   // GPIO0[0] 1
   // GPIO1[0] 17
   // GPIO2[0] 33
   // GPIO3[0] 49
   // GPIO4[0] 65
   // GPIO5[0] 81
   // GPIO6[0] 97
   // GPIO7[0] 113
   // GPIO8[0] 129
#if 0
    // 1. GPIOs of AD7606 configure.
    GPIOBank8Pin2PinMuxSetup();
    GPIOBank8Pin1PinMuxSetup();
    GPIOBank1Pin7PinMuxSetup();
    GPIOBank1Pin6PinMuxSetup();
    GPIOBank1Pin14PinMuxSetup();
    GPIOBank1Pin13PinMuxSetup();
    GPIOBank8Pin7PinMuxSetup();
    GPIOBank1Pin12PinMuxSetup();
    GPIOBank1Pin11PinMuxSetup();
#endif
    GPIODirModeSet( SOC_GPIO_0_REGS , OS0_GPIO_NUMBER, GPIO_DIR_OUTPUT);
    GPIODirModeSet( SOC_GPIO_0_REGS , OS1_GPIO_NUMBER, GPIO_DIR_OUTPUT);
    GPIODirModeSet( SOC_GPIO_0_REGS , OS2_GPIO_NUMBER, GPIO_DIR_OUTPUT);
    GPIODirModeSet( SOC_GPIO_0_REGS , RANGE_GPIO_NUMBER, GPIO_DIR_OUTPUT);
    GPIODirModeSet( SOC_GPIO_0_REGS , CVA_GPIO_NUMBER, GPIO_DIR_OUTPUT);
    GPIODirModeSet( SOC_GPIO_0_REGS , CVB_GPIO_NUMBER, GPIO_DIR_OUTPUT);
    GPIODirModeSet( SOC_GPIO_0_REGS , RESET_GPIO_NUMBER, GPIO_DIR_INPUT);
    GPIODirModeSet( SOC_GPIO_0_REGS , BUSY_GPIO_NUMBER, GPIO_DIR_INPUT);
    GPIODirModeSet( SOC_GPIO_0_REGS , FIRST_GPIO_NUMBER, GPIO_DIR_INPUT);
#if 1
    // 2. GPIOs of LED configure.
    GPIOBank0Pin5PinMuxSetup();
    GPIOBank0Pin0PinMuxSetup();
    GPIOBank0Pin1PinMuxSetup();
    GPIOBank0Pin2PinMuxSetup();
#endif

    GPIODirModeSet( SOC_GPIO_0_REGS , LED1_GPIO_NUMBER , GPIO_DIR_OUTPUT);
    GPIODirModeSet( SOC_GPIO_0_REGS , LED2_GPIO_NUMBER , GPIO_DIR_OUTPUT);
    GPIODirModeSet( SOC_GPIO_0_REGS , LED3_GPIO_NUMBER , GPIO_DIR_OUTPUT);
    GPIODirModeSet( SOC_GPIO_0_REGS , LED4_GPIO_NUMBER , GPIO_DIR_OUTPUT);

    //3. GPIOs of Other

}

