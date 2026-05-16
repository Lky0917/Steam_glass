#ifndef  _DRIVER_H
#define  _DRIVER_H

#include "Headinclude.h"

#define   Mode_disp     0x00	//00 000000显示模式设置
#define   Mode_data		0x40	//01 000000数据命令设置
#define   Mode_cond		0x80	//10 000000显示控制命令
#define	  Mode_addr		0xc0	//11 000000地址命令设置
#define   Mode_read     0x42    //01 000010读数据命令
#define   addr_start    0xc0	//11 000000起始地址

#define   Disp_4w10d		0x00	//4位9段,下同
#define   Disp_5w9d	  	0x01
#define   Disp_6w8d		  0x02

#define   Data_cmd      0x40	//自动地址增加写数据普通模式
#define	  disp_open     0x88	//显示开 脉冲宽度12/16
#define   TM1628_CMD_DISP      0x8f
#define   TM1628_CMD_DARK      0x89
#endif

#define  Bit_SET    	1
#define  Bit_RESET      0

#define TM1628_STB_0    	GPIO_ResetBits(GPIOB,GPIO_Pin_13)//
#define TM1628_STB_1    	GPIO_SetBits(GPIOB,GPIO_Pin_13)
#define TM1628_DIO_0    	GPIO_ResetBits(GPIOB,GPIO_Pin_15)//
#define TM1628_DIO_1    	GPIO_SetBits(GPIOB,GPIO_Pin_15)
#define TM1628_CLK_0    	GPIO_ResetBits(GPIOB,GPIO_Pin_14)//
#define TM1628_CLK_1    	GPIO_SetBits(GPIOB,GPIO_Pin_14)

#define  TM1628_DIO_IN    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)

unsigned char TM1620B_read(void);

void f_TM1628_All(void);
void TM1620B_work(unsigned char *Data_Disp,unsigned char CMD_DISP);

