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


#include "global.h"
#include "main.h"

bool                    leds_flash_flag = 0;
struct ad9833_t        ad9833_dev;
AllChannelData         all_channel_datas;


int main( void )
{
    all_channel_datas.adc_count = 0;
    all_channel_datas.converted_flag = 0;
	CacheEnableMAR((unsigned int)0xC0000000, (unsigned int)0x8000000);
	CacheEnable(L1DCFG_L1DMODE_32K | L1PCFG_L1PMODE_32K | L2CFG_L2MODE_256K);
	UARTStdioInit();
    UARTPuts("This is uart data.....\r\n", -2);
    PSCInit();
    led_gpio_init();
    init_ad9833( &ad9833_dev );
    ad9833_dev.set_wave_para( &ad9833_dev, 100000, 0, SIN );
    InterruptInit();

	while(1) {
	    if( leds_flash_flag == 1 ) {
	        leds_flash();
	        leds_flash_flag = 0;
	    }
	}
}

void TimerIsr(void)
{
    IntEventClear(SYS_INT_T64P2_TINTALL);
    TimerIntStatusClear(SOC_TMR_2_REGS, TMR_INT_TMR12_NON_CAPT_MODE);
    ads8568_start_convert();
    all_channel_datas.ch_data.channal_0[ all_channel_datas.adc_count ] = ( ((float)( ((short *)SOC_EMIFA_CS2_ADDR)[1] )  +  8000.0)/3200.0  );
    all_channel_datas.ch_data.channal_1[ all_channel_datas.adc_count ] = ( ((float)( ((short *)SOC_EMIFA_CS2_ADDR)[2] )  +  8000.0)/3200.0  );
    all_channel_datas.ch_data.channal_2[ all_channel_datas.adc_count ] = ( ((float)( ((short *)SOC_EMIFA_CS2_ADDR)[3] )  +  8000.0)/3200.0  );
    all_channel_datas.ch_data.channal_3[ all_channel_datas.adc_count ] = ( ((float)( ((short *)SOC_EMIFA_CS2_ADDR)[4] )  +  8000.0)/3200.0  );
    all_channel_datas.ch_data.channal_4[ all_channel_datas.adc_count ] = ( ((float)( ((short *)SOC_EMIFA_CS2_ADDR)[5] )  +  8000.0)/3200.0  );
    all_channel_datas.ch_data.channal_5[ all_channel_datas.adc_count ] = ( ((float)( ((short *)SOC_EMIFA_CS2_ADDR)[6] )  +  8000.0)/3200.0  );
    all_channel_datas.ch_data.channal_6[ all_channel_datas.adc_count ] = ( ((float)( ((short *)SOC_EMIFA_CS2_ADDR)[7] )  +  8000.0)/3200.0  );
    all_channel_datas.ch_data.channal_7[ all_channel_datas.adc_count ] = ( ((float)( ((short *)SOC_EMIFA_CS2_ADDR)[8] )  +  8000.0)/3200.0  );

    all_channel_datas.adc_count ++;
    if( all_channel_datas.adc_count >= ONE_CHANNEL_BUFFER_MAX ) {
        all_channel_datas.adc_count = 0;
        leds_flash_flag = 1;
    }
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


