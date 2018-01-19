/****************************************************************************/
/*                                                                          */
/*              SPI FLASH 读写测试                                          */
/*                                                                          */
/*              2014年05月19日                                              */
/*                                                                          */
/****************************************************************************/
// 注意：DSP ports, Shared RAM, UART0, EDMA, SPI0, MMC/SDs,
//       VPIF, LCDC, SATA, uPP, DDR2/mDDR (bus ports), USB2.0, HPI, PRU
//       这些外设使用的时钟来源为 PLL0_SYSCLK2 默认频率为 CPU 频率的二分之一
//       但是，ECAPs, UART1/2, Timer64P2/3, eHRPWMs,McBSPs, McASP0, SPI1
//       这些外设的时钟来源可以在 PLL0_SYSCLK2 和 PLL1_SYSCLK2 中选择
//       通过修改 System Configuration (SYSCFG) Module
//       寄存器 Chip Configuration 3 Register (CFGCHIP3) 第四位 ASYNC3_CLKSRC
//       配置时钟来源
//       （默认值） 0 来源于 PLL0_SYSCLK2
//                  1 来源于 PLL1_SYSCLK2
//       如果不是为了降低功耗，不建议修改这个值，它会影响所有相关外设的时钟频率
#include "global.h"
#include "TL6748.h"                 // 创龙 DSP6748 开发板相关声明

#include "soc_C6748.h"
#include "hw_psc_C6748.h"

#include "uart.h"
#include "spi.h"
#include "psc.h"

#include "uartStdio.h"

#include "interrupt.h"

#include <string.h>

/****************************************************************************/
/*                                                                          */
/*              宏定义                                                      */
/*                                                                          */
/****************************************************************************/
// SPI 管脚配置
#define SIMO_SOMI_CLK_CS        0x00000E01
#define CHAR_LENGTH             0x8

// FLASH 地址
#define SPI_FLASH_ADDR_MSB1     0x0A
#define SPI_FLASH_ADDR_MSB0     0x00
#define SPI_FLASH_ADDR_LSB      0x00

// 扇区擦除命令
#define SPI_FLASH_SECTOR_ERASE  0xD8

// 页写入命令
#define SPI_FLASH_PAGE_WRITE    0x02

// 读状态寄存器命令
#define SPI_FLASH_STATUS_RX     0x05

// 写使能命令
#define SPI_FLASH_WRITE_EN      0x06

// 读命令
#define SPI_FLASH_READ          0x03

// 写操作执行中
#define WRITE_IN_PROGRESS       0x01

/****************************************************************************/
/*                                                                          */
/*              全局变量                                                    */
/*                                                                          */
/****************************************************************************/
volatile unsigned int flag = 1;


uint16  spi_data[256];

void init_spi_0( void )
{



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

    SPIClkConfigure(SOC_SPI_0_REGS, 228000000, 800000, SPI_DATA_FORMAT0);

    SPIPinControl(SOC_SPI_0_REGS, 0, 0, &val);

    SPIDefaultCSSet(SOC_SPI_0_REGS, dcs);

    // 配置 SPI 数据格式
    SPIDataFormatConfig(SPI_DATA_FORMAT0);

    // 配置 SPI 数据格式及片选信号
    SPIDat1Config(SOC_SPI_0_REGS, (SPI_CSHOLD | SPI_DATA_FORMAT0), cs);

    // 映射中断到 INT1
    SPIIntLevelSet(SOC_SPI_0_REGS, (SPI_RECV_INTLVL | SPI_TRANSMIT_INTLVL ));

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
                        (SPI_CLK_POL_HIGH | SPI_CLK_OUTOFPHASE ),
                         dataFormat);

    // 配置 SPI 发送时 MSB 优先
    SPIShiftMsbFirst(SOC_SPI_0_REGS, dataFormat);

    // 设置字符长度
    SPICharLengthSet(SOC_SPI_0_REGS, 16, dataFormat);
}

/****************************************************************************/
/*                                                                          */
/*              SPI 中断服务函数                                            */
/*                                                                          */
/****************************************************************************/

