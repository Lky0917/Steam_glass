#include "HeadInclude.h"


//SC12A
#define SCL_SC12A_High        GPIO_SetBits(GPIOA,GPIO_Pin_11)//SCL H
#define SCL_SC12A_Low         GPIO_ResetBits(GPIOA,GPIO_Pin_11)//SCL L
#define SDA_SC12A_OUT_H       GPIO_SetBits(GPIOA,GPIO_Pin_12)//SDA H
#define SDA_SC12A_OUT_L       GPIO_ResetBits(GPIOA,GPIO_Pin_12)//SDA l

#define SDA_SC12A_IN          GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_12)

#define IIC_HIGH				 1
#define IIC_LEVEL        0


#define  CMD_READ			    0x81
#define  SLAVEADDRESS     0x40			//0b11100000	从设备地址


#define  DELAYTIME		5

void Delay_1us(void)//16M
{
	unsigned char i;
	for(i = 0;i<8;i++);
}
void Delay_us(unsigned char us)
{
	unsigned char i;
	for(i = 0;i < us;i++)
	{
		Delay_1us();
	}
}
//***********************
//函数名称：I2C_setSDAout2in
//函数功能：输出转输入
//入口参数：state  //需要输出转输入的通讯口
//出口参数：无
//***********************
void I2C_setSDAout2in(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}
//***********************
//函数名称：I2C_setSDAin2out
//函数功能：输入转输出
//入口参数：state  //需要输入转输出的通讯口
//出口参数：无
//***********************

void  I2C_setSDAin2out(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}
//***********************
//函数名称：I2C_start
//函数功能：初始化总线
//入口参数：
//出口参数：无
//***********************
void I2C_start(void)
{
	SDA_SC12A_OUT_H;	//起始数据信号
	Delay_us(DELAYTIME);
	SCL_SC12A_High;
	Delay_us(DELAYTIME);
	SDA_SC12A_OUT_L;
	Delay_us(DELAYTIME);
	SCL_SC12A_Low;
	Delay_us(DELAYTIME);
}
//***********************
//函数名称：I2C_stop
//函数功能：结束总线
//入口参数：
//出口参数：无
//***********************
void I2C_stop(void)
{
	SDA_SC12A_OUT_L;	//数据结束
	Delay_us(DELAYTIME);
	SCL_SC12A_High;
	Delay_us(DELAYTIME);
	SDA_SC12A_OUT_H;
	Delay_us(DELAYTIME);
}

//***********************
//函数名称：I2C_sendbyte
//函数功能：I2C送入数据
//入口参数：数据sendbyte
//出口参数：无
//***********************
void I2C_sendbyte(unsigned char sendbyte)
{
	unsigned char BitCnt;
	for(BitCnt = 0; BitCnt < 8; BitCnt++)
	{
		if((sendbyte & 0x80) == 0x80)
			SDA_SC12A_OUT_H;
		else
			SDA_SC12A_OUT_L;
		Delay_us(DELAYTIME);
		SCL_SC12A_High;//置高，通知开始接收数据
		Delay_us(DELAYTIME);
		SCL_SC12A_Low;	
		sendbyte <<= 1;
	}
	I2C_waitack();
}

//***********************
//函数名称：I2C_readbyte
//函数功能：读取数据
//入口参数：
//出口参数：无
//***********************
unsigned char I2C_readbyte(void)
{
	unsigned char readdata = 0;
	unsigned char i = 8;
	//SDA为输入读取数据
	I2C_setSDAout2in();

	while(i--)
	{
		readdata <<= 1;
		SCL_SC12A_Low;
		Delay_1us();
		SCL_SC12A_High;
		Delay_1us();
		if(SDA_SC12A_IN)
			readdata |= 0x01;
	}
	SCL_SC12A_Low;
	//SDA输入转输出
	I2C_setSDAin2out();
	
	return readdata;
}
//***********************
//函数名称：I2C_readbyte
//函数功能：读取数据
//入口参数：
//出口参数：无
//***********************
unsigned int I2C_readWord(void)
{
	unsigned int readdata = 0;
	unsigned char i = 16;
	//SDA为输入读取数据
	I2C_setSDAout2in();

	while(i--)
	{
		readdata <<= 1;
		SCL_SC12A_Low;
		Delay_1us();
		SCL_SC12A_High;
		Delay_1us();
		if(SDA_SC12A_IN)
			readdata |= 0x01;
	}
	SCL_SC12A_Low;
	//SDA输入转输出
	I2C_setSDAin2out();
	
	return readdata;
}
//***********************
//函数名称：I2C_waitack
//函数功能：等待ACK
//入口参数：
//出口参数：无
//***********************
void I2C_waitack(void)
{
	unsigned int i = 5000;

	SCL_SC12A_Low;
	//SDA输出转输入
	I2C_setSDAout2in();
	//
	SCL_SC12A_High;
	Delay_us(DELAYTIME);
	while(SDA_SC12A_IN)
	{
		i--;
		if(i==0)
			break;
	}
	SCL_SC12A_Low;
	//SDA输入回复输出
	I2C_setSDAin2out();

	Delay_us(DELAYTIME);

}
//***********************
//函数名称：SC12A_work()
//函数功能：启动SC12A 送入数据正常显示
//入口参数：
//出口参数：无
//***********************







