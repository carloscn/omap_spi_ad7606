/****************************************************************************/
/*                                                                          */
/* 广州创龙电子科技有限公司                                                 */
/*                                                                          */
/* Copyright (C) 2014-2016 Guangzhou Tronlong Electronic Technology Co.,Ltd */
/*                                                                          */
/****************************************************************************/
/****************************************************************************/
/*                                                                          */
/*              OMAPL138 及 DSP C6748 内存空间分配定义                      */
/*                                                                          */
/*              2014年07月05日                                              */
/*                                                                          */
/****************************************************************************/

MEMORY
{
    SHDSPL2ROM   o = 0x11700000  l = 0x00100000      /* 1MB   L2 共享内置 ROM */
    SHDSPL2RAM   o = 0x11800000  l = 0x00040000      /* 256KB L2 共享内置 RAM */

    SHRAM        o = 0x80000000  l = 0x00020000      /* 128KB 共享 RAM */
    DDR2         o = 0xC0000000  l = 0x08000000      /* 128MB DDR2 分配给 DSP */
}

SECTIONS
{
    .text			>  SHDSPL2RAM             		 /* 可执行代码 */
    .stack  		>  SHDSPL2RAM 				     /* 软件系统栈 */

    .cio			>  SHDSPL2RAM                    /* C 输入输出缓存 */
    .vectors		>  SHDSPL2RAM      				 /* 中断向量表 */
    .const			>  SHDSPL2RAM                    /* 常量 */
    .data			>  SHDSPL2RAM                    /* 已初始化全局及静态变量 */
    .switch			>  SHDSPL2RAM                    /* 跳转表 */
    .sysmem			>  SHDSPL2RAM                    /* 动态内存分配区域 */

    .args			>  SHDSPL2RAM
    .ppinfo			>  SHDSPL2RAM
    .ppdata			>  SHDSPL2RAM

    /* TI-ABI 或 COFF */
    .pinit			>  SHDSPL2RAM                    /* C++ 结构表 */
    .cinit			>  SHDSPL2RAM                    /* 初始化表 */

    /* EABI */
    .binit			>  SHDSPL2RAM
    .init_array		>  SHDSPL2RAM
    .fardata		>  SHDSPL2RAM

    .c6xabi.exidx	>  SHDSPL2RAM
    .c6xabi.extab	>  SHDSPL2RAM

	.init_array     >  SHDSPL2RAM

	GROUP(NEARDP_DATA)
	{
	   .neardata
	   .rodata
	   .bss
	}               >  SHDSPL2RAM

    .far			>  SHDSPL2RAM
}
