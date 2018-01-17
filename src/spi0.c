#include "global.h"
#include "spi0.h"


#define SIMO_SOMI_CLK_CS        0x00000E01






void SPIIsr(void);
volatile unsigned int spi_read_over_flag = 1;
unsigned int tx_len;
unsigned int rx_len;
unsigned char vrf_data[260];
unsigned char tx_data[260];
unsigned char rx_data[260];
unsigned char *p_tx;
unsigned char *p_rx;
unsigned int flag;
void spi_write( void )
{
    SPIDat1Config(SOC_SPI_0_REGS, (SPI_CSHOLD | SPI_DATA_FORMAT0), 0x1);

    SPIIntEnable(SOC_SPI_0_REGS, (SPI_RECV_INT | SPI_TRANSMIT_INT));
    while(flag);
    flag = 1;

    SPIDat1Config(SOC_SPI_0_REGS, SPI_DATA_FORMAT0, 0x1);

}

/****************************************************************************/
/*                                                                          */
/*              SPI 中断初始化                                              */
/*                                                                          */
/****************************************************************************/
void SPIInterruptInit(void)
{

    // 注册中断服务函数
    IntRegister(C674X_MASK_INT4, SPIIsr);

    // 映射中断事件
    IntEventMap(C674X_MASK_INT4, SYS_INT_SPI0_INT);

    // 使能可屏蔽中断
    IntEnable(C674X_MASK_INT4);
}

/****************************************************************************/
/*                                                                          */
/*              SPI 初始化                                                 */
/*                                                                          */
/****************************************************************************/
void SPIInit(void)
{
    unsigned char cs  = 0x01;
    unsigned char dcs = 0x01;
    unsigned int  val = SIMO_SOMI_CLK_CS;

    SPIReset(SOC_SPI_0_REGS);

    SPIOutOfReset(SOC_SPI_0_REGS);

    SPIModeConfigure(SOC_SPI_0_REGS, SPI_MASTER_MODE);

    SPIClkConfigure(SOC_SPI_0_REGS, 228000000, 2000000, SPI_DATA_FORMAT0);

    SPIPinControl(SOC_SPI_0_REGS, 0, 0, &val);

    SPIDefaultCSSet(SOC_SPI_0_REGS, dcs);

    // 配置 SPI 数据格式
    SPIDataFormatConfig(SPI_DATA_FORMAT0);

    // 配置 SPI 数据格式及片选信号
    SPIDat1Config(SOC_SPI_0_REGS, (SPI_CSHOLD | SPI_DATA_FORMAT0), cs);

    // 映射中断到 INT1
    SPIIntLevelSet(SOC_SPI_0_REGS, SPI_RECV_INTLVL | SPI_TRANSMIT_INTLVL);

    // 使能 SPI
    SPIEnable(SOC_SPI_0_REGS);
}
/****************************************************************************/
/*                                                                          */
/*              配置 SPI 数据格式                                           */
/*                                                                          */
/****************************************************************************/

void SPIDataFormatConfig(unsigned int dataFormat)
{
    // 配置 SPI 时钟
    SPIConfigClkFormat(SOC_SPI_0_REGS,
                        (SPI_CLK_POL_HIGH | SPI_CLK_INPHASE),
                         dataFormat);

    // 配置 SPI 发送时 MSB 优先
    SPIShiftMsbFirst(SOC_SPI_0_REGS, dataFormat);

    // 设置字符长度
    SPICharLengthSet(SOC_SPI_0_REGS, 0x8, dataFormat);
}


void spi_read_format_config( uint16 byte_length   )
{
    // 配置 SPI 时钟
    SPIConfigClkFormat(SOC_SPI_0_REGS,
                        (SPI_CLK_POL_HIGH | SPI_CLK_INPHASE),
                        SPI_DATA_FORMAT0);

    // 配置 SPI 发送时 MSB 优先
    SPIShiftMsbFirst(SOC_SPI_0_REGS, SPI_DATA_FORMAT0);

    // 设置字符长度
    SPICharLengthSet(SOC_SPI_0_REGS, byte_length, SPI_DATA_FORMAT0);
}

/****************************************************************************/
/*                                                                          */
/*              SPI 传输                                                    */
/*                                                                          */
/****************************************************************************/
void SpiTransfer(void)
{
    p_tx = &tx_data[0];
    p_rx = &rx_data[0];
    SPIIntEnable(SOC_SPI_0_REGS, (SPI_RECV_INT | SPI_TRANSMIT_INT));
    while(flag);
    flag = 1;

    SPIDat1Config(SOC_SPI_0_REGS, SPI_DATA_FORMAT0, 0x1);
}

/****************************************************************************/
/*                                                                          */
/*              SPI 中断服务函数                                            */
/*                                                                          */
/****************************************************************************/
uint16  spi_data;
void SPIIsr(void)
{
    unsigned int int_vect_code = 0;

    IntEventClear( SYS_INT_SPI0_INT );
    int_vect_code = SPIInterruptVectorGet( SOC_SPI_0_REGS );

    while ( int_vect_code ) {

        if( int_vect_code == SPI_TX_BUF_EMPTY ) {
            tx_len--;
            SPITransmitData1( SOC_SPI_0_REGS, *p_tx );
            p_tx++;
            if ( !tx_len ) {
                SPIIntDisable(SOC_SPI_0_REGS, SPI_TRANSMIT_INT);
            }
        }
        // rec data;
        if( int_vect_code == SPI_RECV_FULL ) {

             spi_data = (uint16)SPIDataReceive(SOC_SPI_0_REGS);

        }
        int_vect_code = SPIInterruptVectorGet(SOC_SPI_0_REGS);
    }

}
