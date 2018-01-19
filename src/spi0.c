/****************************************************************************/
/*                                                                          */
/*              SPI FLASH ��д����                                          */
/*                                                                          */
/*              2014��05��19��                                              */
/*                                                                          */
/****************************************************************************/
// ע�⣺DSP ports, Shared RAM, UART0, EDMA, SPI0, MMC/SDs,
//       VPIF, LCDC, SATA, uPP, DDR2/mDDR (bus ports), USB2.0, HPI, PRU
//       ��Щ����ʹ�õ�ʱ����ԴΪ PLL0_SYSCLK2 Ĭ��Ƶ��Ϊ CPU Ƶ�ʵĶ���֮һ
//       ���ǣ�ECAPs, UART1/2, Timer64P2/3, eHRPWMs,McBSPs, McASP0, SPI1
//       ��Щ�����ʱ����Դ������ PLL0_SYSCLK2 �� PLL1_SYSCLK2 ��ѡ��
//       ͨ���޸� System Configuration (SYSCFG) Module
//       �Ĵ��� Chip Configuration 3 Register (CFGCHIP3) ����λ ASYNC3_CLKSRC
//       ����ʱ����Դ
//       ��Ĭ��ֵ�� 0 ��Դ�� PLL0_SYSCLK2
//                  1 ��Դ�� PLL1_SYSCLK2
//       �������Ϊ�˽��͹��ģ��������޸����ֵ������Ӱ��������������ʱ��Ƶ��
#include "global.h"
#include "TL6748.h"                 // ���� DSP6748 �������������

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
/*              �궨��                                                      */
/*                                                                          */
/****************************************************************************/
// SPI �ܽ�����
#define SIMO_SOMI_CLK_CS        0x00000E01
#define CHAR_LENGTH             0x8

// FLASH ��ַ
#define SPI_FLASH_ADDR_MSB1     0x0A
#define SPI_FLASH_ADDR_MSB0     0x00
#define SPI_FLASH_ADDR_LSB      0x00

// ������������
#define SPI_FLASH_SECTOR_ERASE  0xD8

// ҳд������
#define SPI_FLASH_PAGE_WRITE    0x02

// ��״̬�Ĵ�������
#define SPI_FLASH_STATUS_RX     0x05

// дʹ������
#define SPI_FLASH_WRITE_EN      0x06

// ������
#define SPI_FLASH_READ          0x03

// д����ִ����
#define WRITE_IN_PROGRESS       0x01

/****************************************************************************/
/*                                                                          */
/*              ȫ�ֱ���                                                    */
/*                                                                          */
/****************************************************************************/
volatile unsigned int flag = 1;


uint16  spi_data[256];

void init_spi_0( void )
{



}



/****************************************************************************/
/*                                                                          */
/*              SPI �жϳ�ʼ��                                              */
/*                                                                          */
/****************************************************************************/
void SPIInterruptInit(void)
{
    // ע���жϷ�����
    IntRegister(C674X_MASK_INT4, SPIIsr);

    // ӳ���ж��¼�
    IntEventMap(C674X_MASK_INT4, SYS_INT_SPI0_INT);

    // ʹ�ܿ������ж�
    IntEnable(C674X_MASK_INT4);

}


/****************************************************************************/
/*                                                                          */
/*              SPI ��ʼ��                                                 */
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

    // ���� SPI ���ݸ�ʽ
    SPIDataFormatConfig(SPI_DATA_FORMAT0);

    // ���� SPI ���ݸ�ʽ��Ƭѡ�ź�
    SPIDat1Config(SOC_SPI_0_REGS, (SPI_CSHOLD | SPI_DATA_FORMAT0), cs);

    // ӳ���жϵ� INT1
    SPIIntLevelSet(SOC_SPI_0_REGS, (SPI_RECV_INTLVL | SPI_TRANSMIT_INTLVL ));

    // ʹ�� SPI
    SPIEnable(SOC_SPI_0_REGS);
}
/****************************************************************************/
/*                                                                          */
/*              ���� SPI ���ݸ�ʽ                                           */
/*                                                                          */
/****************************************************************************/
void SPIDataFormatConfig(unsigned int dataFormat)
{
    // ���� SPI ʱ��
    SPIConfigClkFormat(SOC_SPI_0_REGS,
                        (SPI_CLK_POL_HIGH | SPI_CLK_OUTOFPHASE ),
                         dataFormat);

    // ���� SPI ����ʱ MSB ����
    SPIShiftMsbFirst(SOC_SPI_0_REGS, dataFormat);

    // �����ַ�����
    SPICharLengthSet(SOC_SPI_0_REGS, 16, dataFormat);
}

/****************************************************************************/
/*                                                                          */
/*              SPI �жϷ�����                                            */
/*                                                                          */
/****************************************************************************/

