/****************************************************************************/
/*                                                                          */
/*              PRU 驱动                                                   								    */
/*                                                                          */
/*              2015年11月20日                                                                                                                                   */
/*                                                                          */
/****************************************************************************/
#include "hw_types.h"				// 宏命令
#include "hw_syscfg0_C6748.h"	    // 系统配置模块寄存器
#include "soc_C6748.h"			    // DSP C6748 外设寄存器
#include "psc.h"			        // 电源与睡眠控制宏及设备抽象层函数声明


#define DATARAM0_PHYS_BASE            0x01C30000
#define DATARAM1_PHYS_BASE            0x01C32000
#define INTC_PHYS_BASE                0x01C34000
#define PRU0CONTROL_PHYS_BASE         0x01C37000
#define PRU0DEBUG_PHYS_BASE           0x01C37400
#define PRU1CONTROL_PHYS_BASE         0x01C37800
#define PRU1DEBUG_PHYS_BASE           0x01C37C00
#define PRU0IRAM_PHYS_BASE            0x01C38000
#define PRU1IRAM_PHYS_BASE            0x01C3C000


void PruDisable(unsigned char pruNum)
{
	if (pruNum == 0)
    {
		// 禁用 PRU0 CYCLECNT 计数 | PRU 停止取指
		HWREG(PRU0CONTROL_PHYS_BASE) = (0<<3) | (0<<1);
    }
	else if(pruNum == 1)
	{
		// 禁用 PRU1 CYCLECNT 计数 | PRU 停止取指
		HWREG(PRU1CONTROL_PHYS_BASE) = (0<<3) | (0<<1);
	}
	// 禁用 PRU
//	PSCModuleControl(SOC_PSC_0_REGS, HW_PSC_PRU, PSC_POWERDOMAIN_ALWAYS_ON, PSC_MDCTL_NEXT_DISABLE);
}

void PruEnable(unsigned char pruNum)
{
	if (pruNum == 0)
	{
		// 使能PRU
		PSCModuleControl(SOC_PSC_0_REGS, HW_PSC_PRU, PSC_POWERDOMAIN_ALWAYS_ON, PSC_MDCTL_NEXT_ENABLE);
		// 复位 PRU0
		HWREG(PRU0CONTROL_PHYS_BASE) = 0;
	}
	else if(pruNum == 1)
	{
		// 使能PRU
		PSCModuleControl(SOC_PSC_0_REGS, HW_PSC_PRU, PSC_POWERDOMAIN_ALWAYS_ON, PSC_MDCTL_NEXT_ENABLE);
		// 复位 PRU1
		HWREG(PRU1CONTROL_PHYS_BASE) = 0;
	}
}

unsigned int PruLoad(unsigned char pruNum, unsigned int* pruCode, unsigned int codeSizeInWords)
{
	  unsigned int *pruIram;
	  unsigned int i;

	  if (pruNum == 0)
	  {
	    pruIram = (unsigned int *) PRU0IRAM_PHYS_BASE;
	  }
	  else if (pruNum == 1)
	  {
	    pruIram = (unsigned int *) PRU1IRAM_PHYS_BASE;
	  }
	  else
	  {
	    return FALSE;
	  }

	  PruEnable(pruNum);

	  // Copy dMAX code to its instruction RAM
	  for(i=0; i<codeSizeInWords; i++)
	  {
	    pruIram[i] = pruCode[i];
	  }

	  return TRUE;
}

unsigned int PruRun (unsigned char pruNum)
{
	if (pruNum == 0)
	{
		HWREG(PRU0CONTROL_PHYS_BASE) = (1<<3) | (1<<1);
	}
	else if (pruNum == 1)
	{
		HWREG(PRU1CONTROL_PHYS_BASE) = (1<<3) | (1<<1);
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}

unsigned int PruWaitForHalt (unsigned char pruNum, int timeout)
{
	int cnt = timeout;

	if (pruNum == 0)
	{
		while( HWREG(PRU0CONTROL_PHYS_BASE) & (1 << 15))
		{
			if (cnt>0)
			{
				cnt--;
			}
			if (cnt == 0)
			{
				return FALSE;
			}
		}
	}
	else if (pruNum == 1)
	{
		while( HWREG(PRU1CONTROL_PHYS_BASE) & (1 << 15))
		{
			if (cnt>0)
			{
				cnt--;
			}
			if (cnt == 0)
			{
				return FALSE;
			}
		}
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}
