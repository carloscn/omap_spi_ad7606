/****************************************************************************/
/*                                                                          */
/*              广州创龙电子科技有限公司                                    */
/*                                                                          */
/*              Copyright 2015 Tronlong All rights reserved                 */
/*                                                                          */
/****************************************************************************/
/****************************************************************************/
/*                                                                          */
/*              SPI0驱动头文件			                                    */
/*                                                                          */
/*              2015年04月10日                                              */
/*                                                                          */
/****************************************************************************/
#ifndef __SPI0_H_
#define __SPI0_H_

#include "TL6748.h"                 // 创龙 DSP6748 开发板相关声明
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
