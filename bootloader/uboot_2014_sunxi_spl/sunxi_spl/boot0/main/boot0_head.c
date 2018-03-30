/*
************************************************************************************************************************
*                                                         eGON
*                                         the Embedded GO-ON Bootloader System
*
*                             Copyright(C), 2006-2008, SoftWinners Microelectronic Co., Ltd.
*											       All Rights Reserved
*
* File Name : Boot0_head.c
*
* Author : Gary.Wang
*
* Version : 1.1.0
*
* Date : 2007.11.06
*
* Description : This file defines the file head part of Boot0, which contains some important
*             infomations such as magic, platform infomation and so on, and MUST be allocted in the
*             head of Boot0.
*
* Others : None at present.
*
*
* History :
*
*  <Author>        <time>       <version>      <description>
*
* Gary.Wang       2007.11.06      1.1.0        build the file
*
************************************************************************************************************************
*/
#include "common.h"
#include <private_boot0.h>

extern char uboot_hash_value[64];


const boot0_file_head_t  BT0_head = 
{
    {
        /* jump_instruction */         
        ( 0xEA000000 | ( ( ( sizeof( boot0_file_head_t ) + sizeof(uboot_hash_value) + sizeof( int ) - 1 ) / sizeof( int ) - 2 ) & 0x00FFFFFF ) ),
        BOOT0_MAGIC,
        STAMP_VALUE,
#ifdef ALIGN_SIZE_8K
        0x2000,
#else
        0x4000,
#endif
        sizeof( boot_file_head_t ),
        BOOT_PUB_HEAD_VERSION,
        CONFIG_BOOT0_RET_ADDR,
        CONFIG_BOOT0_RUN_ADDR,
        0,
        {
		//brom modify: nand-4bytes sdmmc-2bytes
		0, 0,0,0, '4','.','0',0
        },
    },

    {
        //__u32 prvt_head_size;
        0,
        //char prvt_head_vsn[4];      
        8,      /* debug */
        0,		/* power_mode */
        {0},	/* reserver[2]  */
        //unsigned int                dram_para[32] ; 
        {
            0x00000000, 0x00000007, 0x003B3BFB, 0x00000031,
            0x000030FA, 0x04000000, 0x00001C70, 0x00000040,
            0x00000018, 0x00000001, 0x00000000, 0x00000400,
            0x00000848, 0x0048A192, 0x01B1A94B, 0x00061043,
            0x78787896, 0x00000000, 0x00000000, 0x09090900,
            0x4D462A3E, 0x00000000, 0x00000000, 0x00000000,
            0x00440000, 0x00000000, 0x00000000, 0x00000000,
        },
        //__s32			     uart_port;   
        0x00000000,
        //normal_gpio_cfg       uart_ctrl[2];  
        {
		{ 0x08, 0x00, 0x02, 0x01, 0xff, 0xff, {0}},//PB8: 4--RX
		{ 0x08, 0x01, 0x02, 0x01, 0xff, 0xff, {0}},//PB9: 4--TX
        },
        //__s32                         enable_jtag;  
        0x00000001,
        //normal_gpio_cfg	      jtag_gpio[5];   
        {
            {0x04, 0x17, 0x05, 0xFF, 0xFF, 0xFF, {0}},
            {0x04, 0x18, 0x05, 0xFF, 0xFF, 0xFF, {0}},
            {0x04, 0x19, 0x05, 0xFF, 0xFF, 0xFF, {0}},
            {0x04, 0x1A, 0x05, 0xFF, 0xFF, 0xFF, {0}},
            {0},
        },
        //normal_gpio_cfg        storage_gpio[32]; 
        {
            {0x06, 0x02, 0x02, 0x01, 0x02, 0xFF, {0}},//PF0-5: 2--SDC
            {0x06, 0x03, 0x02, 0x01, 0x02, 0xFF, {0}},
            {0x06, 0x01, 0x02, 0x01, 0x02, 0xFF, {0}},
            {0x06, 0x00, 0x02, 0x01, 0x02, 0xFF, {0}},
            {0x06, 0x05, 0x02, 0x01, 0x02, 0xFF, {0}},
            {0x06, 0x04, 0x02, 0x01, 0x02, 0xFF, {0}},
            {0}, 
        },
        //char                             storage_data[512 - sizeof(normal_gpio_cfg) * 32]; 
        {0}
    }

};



/*******************************************************************************
*
*                  关于Boot_file_head中的jump_instruction字段
*
*  jump_instruction字段存放的是一条跳转指令：( B  BACK_OF_Boot_file_head )，此跳
*转指令被执行后，程序将跳转到Boot_file_head后面第一条指令。
*
*  ARM指令中的B指令编码如下：
*          +--------+---------+------------------------------+
*          | 31--28 | 27--24  |            23--0             |
*          +--------+---------+------------------------------+
*          |  cond  | 1 0 1 0 |        signed_immed_24       |
*          +--------+---------+------------------------------+
*  《ARM Architecture Reference Manual》对于此指令有如下解释：
*  Syntax :
*  B{<cond>}  <target_address>
*    <cond>    Is the condition under which the instruction is executed. If the
*              <cond> is ommitted, the AL(always,its code is 0b1110 )is used.
*    <target_address>
*              Specified the address to branch to. The branch target address is
*              calculated by:
*              1.  Sign-extending the 24-bit signed(wro's complement)immediate
*                  to 32 bits.
*              2.  Shifting the result left two bits.
*              3.  Adding to the contents of the PC, which contains the address
*                  of the branch instruction plus 8.
*
*  由此可知，此指令编码的最高8位为：0b11101010，低24位根据Boot_file_head的大小动
*态生成，所以指令的组装过程如下：
*  ( sizeof( boot_file_head_t ) + sizeof( int ) - 1 ) / sizeof( int )
*                                              求出文件头占用的“字”的个数
*  - 2                                         减去PC预取的指令条数
*  & 0x00FFFFFF                                求出signed-immed-24
*  | 0xEA000000                                组装成B指令
*
*******************************************************************************/

