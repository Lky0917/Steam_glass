#include "HeadInclude.h"




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
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//打开时钟
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
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//打开时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
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
		SCL_SC12A_Low;	
		Delay_us(DELAYTIME);
		if((sendbyte & 0x80) == 0x80)
			SDA_SC12A_OUT_H;
		else
			SDA_SC12A_OUT_L;
		Delay_us(DELAYTIME);
		SCL_SC12A_High;//置高，通知开始接收数据
		Delay_us(DELAYTIME);
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
		Delay_us(DELAYTIME);
		SCL_SC12A_High;
		Delay_us(DELAYTIME);
		if(SDA_SC12A_IN)
			readdata |= 0x01;
	}
	SCL_SC12A_Low;
	//SDA输入转输出
	I2C_setSDAin2out();
	SDA_SC12A_OUT_H;
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
	SDA_SC12A_OUT_H;
	//SDA为输入读取数据
	I2C_setSDAout2in();

	while(i--)
	{
		readdata <<= 1;
		SCL_SC12A_Low;
		Delay_us(DELAYTIME);
		SCL_SC12A_High;
		Delay_us(DELAYTIME);
		
		if(SDA_SC12A_IN)
			readdata |= 0x01;
		else
			readdata &= 0xFE;
	}
	SCL_SC12A_Low;
	Delay_us(DELAYTIME);
	//SDA输入转输出
	I2C_setSDAin2out();
	SDA_SC12A_OUT_H;
	Delay_us(DELAYTIME);
	
	SCL_SC12A_High;
//	Delay_us(DELAYTIME);
//	SCL_SC12A_Low;
//	Delay_us(DELAYTIME);
//	SDA_SC12A_OUT_L;
//	Delay_us(DELAYTIME);
//	SCL_SC12A_High;
//	Delay_us(DELAYTIME);
	return (readdata^0xffff);
}
//***********************
//函数名称：I2C_waitack
//函数功能：等待ACK
//入口参数：
//出口参数：无
//***********************
void I2C_waitack(void)
{
	unsigned int i = 1000;

	
	//SDA输出转输入
	I2C_setSDAout2in();
	SCL_SC12A_Low;
	Delay_us(DELAYTIME);
	//
	SCL_SC12A_High;
	Delay_us(DELAYTIME);
	while(!SDA_SC12A_IN)
	{
		i--;
		if(i==0)
			break;
	}
//	SCL_SC12A_Low;
	//SDA输入回复输出
//	I2C_setSDAin2out();

	Delay_us(DELAYTIME);

}
//***********************
//函数名称：SC12A_work()
//函数功能：启动SC12A 送入数据正常显示
//入口参数：
//出口参数：无
//***********************

void SC12A_work(void)
{	
	//送cmd
	I2C_start();	
//	I2C_sendbyte(SLAVEADDRESS);
	I2C_sendbyte(CMD_READ);
	MchInf.KeyState = I2C_readWord();
	I2C_stop();
}



//**********************第二组
//***********************
//函数名称：I2C_setSDAout2in
//函数功能：输出转输入
//入口参数：state  //需要输出转输入的通讯口
//出口参数：无
//***********************
void I2C_setSDAout2in_1(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);//打开时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
}
//***********************
//函数名称：I2C_setSDAin2out
//函数功能：输入转输出
//入口参数：state  //需要输入转输出的通讯口
//出口参数：无
//***********************

void  I2C_setSDAin2out_1(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);//打开时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
}
//***********************
//函数名称：I2C_start
//函数功能：初始化总线
//入口参数：
//出口参数：无
//***********************
void I2C_start_1(void)
{
	SDA_SC12A_OUT_H_1;	//起始数据信号
	Delay_us(DELAYTIME);
	SCL_SC12A_High_1;
	Delay_us(DELAYTIME);
	SDA_SC12A_OUT_L_1;
	Delay_us(DELAYTIME);
	SCL_SC12A_Low_1;
	Delay_us(DELAYTIME);
}
//***********************
//函数名称：I2C_stop
//函数功能：结束总线
//入口参数：
//出口参数：无
//***********************
void I2C_stop_1(void)
{
	SDA_SC12A_OUT_L_1;	//数据结束
	Delay_us(DELAYTIME);
	SCL_SC12A_High_1;
	Delay_us(DELAYTIME);
	SDA_SC12A_OUT_H_1;
	Delay_us(DELAYTIME);
}
//***********************
//函数名称：I2C_waitack
//函数功能：等待ACK
//入口参数：
//出口参数：无
//***********************
void I2C_waitack_1(void)
{
	unsigned int i = 5000;

	
	//SDA输出转输入
	I2C_setSDAout2in_1();
	SCL_SC12A_Low_1;
	Delay_us(DELAYTIME);
	//
	SCL_SC12A_High_1;
	Delay_us(DELAYTIME);
	while(!SDA_SC12A_IN_1)
	{
		i--;
		if(i==0)
			break;
	}
//	SCL_SC12A_Low;
	//SDA输入回复输出
//	I2C_setSDAin2out();

	Delay_us(DELAYTIME);

}
//***********************
//函数名称：I2C_sendbyte
//函数功能：I2C送入数据
//入口参数：数据sendbyte
//出口参数：无
//***********************
void I2C_sendbyte_1(unsigned char sendbyte)
{
	unsigned char BitCnt;
	for(BitCnt = 0; BitCnt < 8; BitCnt++)
	{
		SCL_SC12A_Low_1;	
		Delay_us(DELAYTIME);
		if((sendbyte & 0x80) == 0x80)
			SDA_SC12A_OUT_H_1;
		else
			SDA_SC12A_OUT_L_1;
		Delay_us(DELAYTIME);
		SCL_SC12A_High_1;//置高，通知开始接收数据
		Delay_us(DELAYTIME);
		sendbyte <<= 1;
	}
	I2C_waitack_1();
}

//***********************
//函数名称：I2C_readbyte
//函数功能：读取数据
//入口参数：
//出口参数：无
//***********************
unsigned char I2C_readbyte_1(void)
{
	unsigned char readdata = 0;
	unsigned char i = 8;
	//SDA为输入读取数据
	I2C_setSDAout2in_1();

	while(i--)
	{
		readdata <<= 1;
		SCL_SC12A_Low_1;
		Delay_us(DELAYTIME);
		SCL_SC12A_High_1;
		Delay_us(DELAYTIME);
		if(SDA_SC12A_IN_1)
			readdata |= 0x01;
	}
	SCL_SC12A_Low_1;
	//SDA输入转输出
	I2C_setSDAin2out_1();
	SDA_SC12A_OUT_H_1;
	return readdata;
}
//***********************
//函数名称：I2C_readbyte
//函数功能：读取数据
//入口参数：
//出口参数：无
//***********************
unsigned int I2C_readWord_1(void)
{
	unsigned int readdata = 0;
	unsigned char i = 16;
	SDA_SC12A_OUT_H_1;
	//SDA为输入读取数据
	I2C_setSDAout2in_1();

	while(i--)
	{
		readdata <<= 1;
		SCL_SC12A_Low_1;
		Delay_us(DELAYTIME);
		SCL_SC12A_High_1;
		Delay_us(DELAYTIME);
		
		if(SDA_SC12A_IN_1)
			readdata |= 0x01;
		else
			readdata &= 0xFE;
	}
	SCL_SC12A_Low_1;
	Delay_us(DELAYTIME);
	//SDA输入转输出
	I2C_setSDAin2out_1();
	SDA_SC12A_OUT_H_1;
	Delay_us(DELAYTIME);
	
	SCL_SC12A_High;
//	Delay_us(DELAYTIME);
//	SCL_SC12A_Low;
//	Delay_us(DELAYTIME);
//	SDA_SC12A_OUT_L;
//	Delay_us(DELAYTIME);
//	SCL_SC12A_High;
//	Delay_us(DELAYTIME);
	return (readdata^0xffff);
}

//***********************
//函数名称：SC12A_work()
//函数功能：启动SC12A 送入数据正常显示
//入口参数：
//出口参数：无
//***********************

void SC12A_work_1(void)
{	
	//送cmd
	I2C_start_1();	
//	I2C_sendbyte(SLAVEADDRESS);
	I2C_sendbyte_1(CMD_READ);
	MchInf.KeyState2 = I2C_readWord_1();
	I2C_stop_1();
}



