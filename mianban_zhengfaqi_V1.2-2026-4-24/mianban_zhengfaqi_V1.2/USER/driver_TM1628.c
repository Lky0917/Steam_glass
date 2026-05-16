
#include "HeadInclude.h"

#define  DELAYTIME  5


void  TM1628_OUT2IN(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}
void  TM1628_IN2OUT(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

void f_Delay(unsigned char nTm)
{
	unsigned char i;
	for(i=0;i<nTm;i++)
	{
//		_asm("NOP");
	}
}

//**************************
void TM1620B_start(void)
{	
	TM1628_STB_1;
	TM1628_CLK_1;
	TM1628_DIO_1;
}

void TM1620B_write(unsigned char data_1620)
{
	unsigned char i;
	TM1628_STB_0;
	f_Delay(DELAYTIME);
	for(i = 0; i < 8;i++)
	{
		TM1628_CLK_0;
		f_Delay(DELAYTIME);

		if(data_1620 & 0x01)
		    TM1628_DIO_1;
		else
		    TM1628_DIO_0;
		
		data_1620 >>= 1;
		
		TM1628_CLK_1;		
		
	}
}
//***********************
unsigned char TM1620B_read(void)
{ 
	unsigned char i = 0,j = 0,key_read = 0; 
    unsigned char key[5] = {0};

	TM1620B_start();
	TM1620B_write(Mode_read);//读命令

	TM1628_STB_0;

	TM1628_OUT2IN();//释放DIO为输入
	
	for(j= 0;j<5;j++)
	{
		for(i=0;i<8;i++)
		{
			TM1628_CLK_0;
			
			key[j] = key[j]>>1;

			TM1628_CLK_1;
			
			if(TM1628_DIO_IN == 1)
			{
				key[j] = key[j] | 0x80;
			}
			
		}
    }
	TM1628_STB_1;
	TM1628_IN2OUT();

	if((key[0] & 0x10) == 0x10)
		key_read |= 0x04;
	if((key[1] & 0x02) == 0x02)
		key_read |= 0x40;
	if((key[0] & 0x02) == 0x02)
		key_read |= 0x10;
	if((key[0] & 0x01) == 0x01)
		key_read |= 0x20;
	if((key[0] & 0x08) == 0x08)
		key_read |= 0x08;
	if((key[1] & 0x01) == 0x01)
		key_read |= 0x01;
	if((key[2] & 0x08) == 0x08)
		key_read |= 0x02;

	return key_read;
}

void TM1620B_work(unsigned char *Data_Disp,unsigned char CMD_DISP)
{
	unsigned char i;

	TM1620B_start();   //初始化	
	TM1620B_write(Disp_5w9d); //5位9段

	TM1628_STB_1;
	TM1620B_write(Mode_data); //数据命令

	TM1628_STB_1;
	TM1620B_write(addr_start);//起始地址
  for(i = 0;i < 11;i++)
		TM1620B_write(Data_Disp[i]);//连续写入地址全部写一遍

	TM1628_STB_1;
	TM1620B_write(CMD_DISP);//14/16 开
	TM1620B_start();   //初始化	
} 



