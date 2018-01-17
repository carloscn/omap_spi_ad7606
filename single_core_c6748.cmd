/****************************************************************************/
/*                                                                          */
/* ���ݴ������ӿƼ����޹�˾                                                 */
/*                                                                          */
/* Copyright (C) 2014-2016 Guangzhou Tronlong Electronic Technology Co.,Ltd */
/*                                                                          */
/****************************************************************************/
/****************************************************************************/
/*                                                                          */
/*              OMAPL138 �� DSP C6748 �ڴ�ռ���䶨��                      */
/*                                                                          */
/*              2014��07��05��                                              */
/*                                                                          */
/****************************************************************************/

MEMORY
{
    SHDSPL2ROM   o = 0x11700000  l = 0x00100000      /* 1MB   L2 �������� ROM */
    SHDSPL2RAM   o = 0x11800000  l = 0x00040000      /* 256KB L2 �������� RAM */

    SHRAM        o = 0x80000000  l = 0x00020000      /* 128KB ���� RAM */
    DDR2         o = 0xC0000000  l = 0x08000000      /* 128MB DDR2 ����� DSP */
}

SECTIONS
{
    .text			>  SHDSPL2RAM             		 /* ��ִ�д��� */
    .stack  		>  SHDSPL2RAM 				     /* ���ϵͳջ */

    .cio			>  SHDSPL2RAM                    /* C ����������� */
    .vectors		>  SHDSPL2RAM      				 /* �ж������� */
    .const			>  SHDSPL2RAM                    /* ���� */
    .data			>  SHDSPL2RAM                    /* �ѳ�ʼ��ȫ�ּ���̬���� */
    .switch			>  SHDSPL2RAM                    /* ��ת�� */
    .sysmem			>  SHDSPL2RAM                    /* ��̬�ڴ�������� */

    .args			>  SHDSPL2RAM
    .ppinfo			>  SHDSPL2RAM
    .ppdata			>  SHDSPL2RAM

    /* TI-ABI �� COFF */
    .pinit			>  SHDSPL2RAM                    /* C++ �ṹ�� */
    .cinit			>  SHDSPL2RAM                    /* ��ʼ���� */

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
