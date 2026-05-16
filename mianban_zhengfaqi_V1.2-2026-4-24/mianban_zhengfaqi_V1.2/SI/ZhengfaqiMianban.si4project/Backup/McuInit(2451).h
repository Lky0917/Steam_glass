#ifndef  _INIT_H
#define  _INIT_H

#include "stm32f10x.h"
#include "SubDefine.h"


	#define   ENABLE_UART1      1	
	#define   ENABLE_UART2      1

	#define   ENABLE_TIMER3     1
	#define   ENABLE_TIMER2     1

/*
	#define   ENABLE_TIMER4     1
	#define   ENABLE_UART3			1
	#define   ENABLE_JTAG       1  //0   swd  PB3 PB4 需设置为普通IO

	#define   ENABLE_BEEP       1
	#define   ENABLE_DMA        1

	#define   ENABLE_SPI1       1
	#define   ENABLE_ADC        1

	#define  LED_DISP      1
	#define  EPD_DISP      1
	#define  TFTLCD_DISP   1
*/



#define   INTERRUPT_ALL_CLOSE    __set_PRIMASK(1)//关总中断
#define   INTERRUPT_ALL_OPED     __set_PRIMASK(0)//关总中断

#define   IO_KEY1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)
#define   IO_KEY2  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)
#define   IO_KEY3  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)
#define   IO_KEY4  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)
#define   IO_KEY5  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4)
#define   IO_KEY6  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)
#define   IO_KEY7  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)
#define   IO_KEY8  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7)
#define   IO_KEY9  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)
#define   IO_KEY10  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)
#define   IO_KEY11  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10)
#define   IO_KEY12  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11)
#define   IO_KEY13  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)
#define   IO_KEY14  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)
#define   IO_KEY15  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)

#define BEEP_OFF_IO      	GPIO_ResetBits(GPIOB,GPIO_Pin_12)//
#define BEEP_ON_IO     	GPIO_SetBits(GPIOB,GPIO_Pin_12)

#define GRID1_OFF_IO      GPIO_ResetBits(GPIOB,GPIO_Pin_13)//
#define GRID1_ON_IO     	GPIO_SetBits(GPIOB,GPIO_Pin_13)

#define GRID2_OFF_IO      GPIO_ResetBits(GPIOB,GPIO_Pin_14)//
#define GRID2_ON_IO     	GPIO_SetBits(GPIOB,GPIO_Pin_14)

#define GRID3_OFF_IO      GPIO_ResetBits(GPIOA,GPIO_Pin_4)//
#define GRID3_ON_IO     	GPIO_SetBits(GPIOA,GPIO_Pin_4)

#define GRID4_OFF_IO      GPIO_ResetBits(GPIOA,GPIO_Pin_5)//
#define GRID4_ON_IO     	GPIO_SetBits(GPIOA,GPIO_Pin_5)

#define GRID5_OFF_IO      GPIO_ResetBits(GPIOB,GPIO_Pin_1)//
#define GRID5_ON_IO     	GPIO_SetBits(GPIOB,GPIO_Pin_1)

#define GRID6_OFF_IO      GPIO_ResetBits(GPIOB,GPIO_Pin_15)//
#define GRID6_ON_IO     	GPIO_SetBits(GPIOB,GPIO_Pin_15)

#define SEG1_OFF_IO      GPIO_ResetBits(GPIOA,GPIO_Pin_8)//
#define SEG1_ON_IO     	GPIO_SetBits(GPIOA,GPIO_Pin_8)

#define SEG4_OFF_IO      GPIO_ResetBits(GPIOA,GPIO_Pin_12)//
#define SEG4_ON_IO     	GPIO_SetBits(GPIOA,GPIO_Pin_12)

#define SEG5_OFF_IO      GPIO_ResetBits(GPIOA,GPIO_Pin_15)//
#define SEG5_ON_IO     	GPIO_SetBits(GPIOA,GPIO_Pin_15)

#define SEG3_OFF_IO      GPIO_ResetBits(GPIOC,GPIO_Pin_14)//
#define SEG3_ON_IO     	GPIO_SetBits(GPIOC,GPIO_Pin_14)

#define SEG2_OFF_IO      GPIO_ResetBits(GPIOC,GPIO_Pin_15)//
#define SEG2_ON_IO     	GPIO_SetBits(GPIOC,GPIO_Pin_15)

#define SEG6_OFF_IO      GPIO_ResetBits(GPIOB,GPIO_Pin_3)//
#define SEG6_ON_IO     	GPIO_SetBits(GPIOB,GPIO_Pin_3)

#define SEG7_OFF_IO      GPIO_ResetBits(GPIOB,GPIO_Pin_7)//
#define SEG7_ON_IO     	GPIO_SetBits(GPIOB,GPIO_Pin_7)

#define SEG8_OFF_IO      GPIO_ResetBits(GPIOB,GPIO_Pin_8)//
#define SEG8_ON_IO     	GPIO_SetBits(GPIOB,GPIO_Pin_8)

#define ZHENDONG1_OFF_IO      GPIO_ResetBits(GPIOB,GPIO_Pin_4)//
#define ZHENDONG1_ON_IO     	GPIO_SetBits(GPIOB,GPIO_Pin_4)

#define ZHENDONG2_OFF_IO      GPIO_ResetBits(GPIOB,GPIO_Pin_5)//
#define ZHENDONG2_ON_IO     	GPIO_SetBits(GPIOB,GPIO_Pin_5)

#define ZHENDONG3_OFF_IO      GPIO_ResetBits(GPIOB,GPIO_Pin_6)//
#define ZHENDONG3_ON_IO     	GPIO_SetBits(GPIOB,GPIO_Pin_6)

extern byte_def    nTime_Flag;
#define		 b10msFlag		 	 	nTime_Flag.m_bit.b0
#define		 b50msFlag				nTime_Flag.m_bit.b1
#define		 b100msFlag	 	 	 	nTime_Flag.m_bit.b2
#define		 b250msFlag			 	nTime_Flag.m_bit.b3
#define		 b500msFlag				nTime_Flag.m_bit.b4
#define		 bTIMERtoADFlag			nTime_Flag.m_bit.b5
#define		 b20msFlag    			nTime_Flag.m_bit.b5

extern byte_def    nFreq_Flag;
#define		 b0d5HzFlag				nFreq_Flag.m_bit.b0//1/2HZ
#define		 b1HzFlag				nFreq_Flag.m_bit.b1//1HZ
#define		 b1sFlag			 	nFreq_Flag.m_bit.b2
#define		 b2HzFlag			 	nFreq_Flag.m_bit.b3
#define		 b4HzFlag			 	nFreq_Flag.m_bit.b4
#define		 b10HzFlag			 	nFreq_Flag.m_bit.b5


//*******************************************************************

#define LED_BBB_ON        GPIO_SetBits(GPIOB,GPIO_Pin_1)//bbb  open
#define LED_BBB_OFF       GPIO_ResetBits(GPIOB,GPIO_Pin_1)//BBB close
#define LED_GGG_ON        GPIO_SetBits(GPIOB,GPIO_Pin_0)//GGG open
#define LED_GGG_OFF       GPIO_ResetBits(GPIOB,GPIO_Pin_0)//GGG close
#define LED_RRR_ON        GPIO_SetBits(GPIOA,GPIO_Pin_5)//RRR  open
#define LED_RRR_OFF       GPIO_ResetBits(GPIOA,GPIO_Pin_5)//RRR close

extern unsigned char uart2_data_temp1[2048];
extern unsigned char uart2_data_temp2[2048];


void f_GPIO_Config(void);
void f_Time4_Config(void);
void f_Time3_Config(void);
void f_Time2_Config(void);
void f_NVIC_Config(void);
void RCC_Configuration(void);
u16 f_Get_Adc(u8 ch) ;
void f_MCU_InitSfr(void);
void f_IWDG_Init(u8 prer,u16 rlr);
void f_MCU_FeedDog(void);
void f_InitUart(void);
void f_InitDMA(void);

#endif

