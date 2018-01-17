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

extern void SPI0Setup(unsigned int csPinNum, unsigned int Charlength);
extern unsigned int SPI0_ReadWriteByte(unsigned int csPinNum, char csHoldFlag,
		unsigned int TxData);


#endif /* SPI0_H_ */
