/****************************************************************************/
/*                                                                          */
/*              ���ݴ������ӿƼ����޹�˾                                    */
/*                                                                          */
/*              Copyright 2015 Tronlong All rights reserved                 */
/*                                                                          */
/****************************************************************************/
/****************************************************************************/
/*                                                                          */
/*              SPI0����ͷ�ļ�			                                    */
/*                                                                          */
/*              2015��04��10��                                              */
/*                                                                          */
/****************************************************************************/
#ifndef __SPI0_H_
#define __SPI0_H_

#include "TL6748.h"                 // ���� DSP6748 �������������
#include "soc_C6748.h"
#include "hw_psc_C6748.h"
#include "uart.h"
#include "spi.h"
#include "psc.h"
#include "uartStdio.h"
#include "interrupt.h"
#include <string.h>

extern void SPIDataFormatConfig(unsigned int dataFormat);
extern void InterruptInit(void);
extern void SPIInterruptInit(void);
extern void SPIInit(void);
extern void SPIIsr(void);
extern void init_spi_0( void );
#endif /* SPI0_H_ */
