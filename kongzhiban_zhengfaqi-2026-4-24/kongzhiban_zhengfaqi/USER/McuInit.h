#ifndef  _INIT_H
#define  _INIT_H

#include "stm32f10x.h"
#include "SubDefine.h"


	#define   ENABLE_UART1      1	
	#define   ENABLE_UART2      1

	#define   ENABLE_ADC        1
	#define   ENABLE_TIMER2     1
	#define   ENABLE_TIMER3     1
	
/*

	#define   ENABLE_UART3			1
	#define   ENABLE_JTAG       1  //0   swd  PB3 PB4 需设置为普通IO

	#define   ENABLE_BEEP       1
	#define   ENABLE_DMA        1

	#define   ENABLE_SPI1       1

	#define   ENABLE_TIMER3     1
	#define   ENABLE_TIMER4     1
	#define  LED_DISP      1
	#define  EPD_DISP      1
	#define  TFTLCD_DISP   1
*/



#define   INTERRUPT_ALL_CLOSE    __set_PRIMASK(1)//关总中断
#define   INTERRUPT_ALL_OPED     __set_PRIMASK(0)//关总中断

#define   IO_WATER_LV5      GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)
#define   IO_WATER_LV4      GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)
#define   IO_WATER_HIGH      GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)
#define   IO_WATER_MID      GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)
#define   IO_WATER_LOW      GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)
#define   IO_CHUGOUBENG      GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)
#define   IO_TEST            GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)


#define   IO_RLY11_ON        GPIO_SetBits(GPIOB,GPIO_Pin_14)//
#define   IO_RLY11_OFF       GPIO_ResetBits(GPIOB,GPIO_Pin_14)//

#define   IO_RLY10_ON        GPIO_SetBits(GPIOB,GPIO_Pin_15)//
#define   IO_RLY10_OFF       GPIO_ResetBits(GPIOB,GPIO_Pin_15)//

#define   IO_RLY9_ON        GPIO_SetBits(GPIOA,GPIO_Pin_8)//
#define   IO_RLY9_OFF       GPIO_ResetBits(GPIOA,GPIO_Pin_8)//

#define   IO_RLY8_ON        GPIO_SetBits(GPIOA,GPIO_Pin_11)//
#define   IO_RLY8_OFF       GPIO_ResetBits(GPIOA,GPIO_Pin_11)//

#define   IO_RLY7_ON        GPIO_SetBits(GPIOA,GPIO_Pin_12)//
#define   IO_RLY7_OFF       GPIO_ResetBits(GPIOA,GPIO_Pin_12)//

#define   IO_RLY6_ON        GPIO_SetBits(GPIOA,GPIO_Pin_15)//
#define   IO_RLY6_OFF       GPIO_ResetBits(GPIOA,GPIO_Pin_15)//

#define   IO_RLY5_ON        GPIO_SetBits(GPIOB,GPIO_Pin_3)//
#define   IO_RLY5_OFF       GPIO_ResetBits(GPIOB,GPIO_Pin_3)//

#define   IO_RLY4_ON        GPIO_SetBits(GPIOB,GPIO_Pin_4)//
#define   IO_RLY4_OFF       GPIO_ResetBits(GPIOB,GPIO_Pin_4)//

#define   IO_RLY3_ON        GPIO_SetBits(GPIOB,GPIO_Pin_5)//
#define   IO_RLY3_OFF       GPIO_ResetBits(GPIOB,GPIO_Pin_5)//

#define   IO_RLY2_ON        GPIO_SetBits(GPIOB,GPIO_Pin_6)//
#define   IO_RLY2_OFF       GPIO_ResetBits(GPIOB,GPIO_Pin_6)//

#define   IO_RLY1_ON        GPIO_SetBits(GPIOB,GPIO_Pin_7)//
#define   IO_RLY1_OFF       GPIO_ResetBits(GPIOB,GPIO_Pin_7)//

#define   IO_BLKEY4_H        GPIO_SetBits(GPIOB,GPIO_Pin_8)//
#define   IO_BLKEY4_L        GPIO_ResetBits(GPIOB,GPIO_Pin_8)//

#define   IO_BLKEY3_H        GPIO_SetBits(GPIOB,GPIO_Pin_9)//
#define   IO_BLKEY3_L        GPIO_ResetBits(GPIOB,GPIO_Pin_9)//

#define   IO_BLKEY2_H        GPIO_SetBits(GPIOC,GPIO_Pin_13)//
#define   IO_BLKEY2_L        GPIO_ResetBits(GPIOC,GPIO_Pin_13)//

#define   IO_BLKEY1_H        GPIO_SetBits(GPIOC,GPIO_Pin_14)//
#define   IO_BLKEY1_L        GPIO_ResetBits(GPIOC,GPIO_Pin_14)//

#define   IO_BLMUTE_H        GPIO_SetBits(GPIOC,GPIO_Pin_15)//
#define   IO_BLMUTE_L        GPIO_ResetBits(GPIOC,GPIO_Pin_15)//

extern byte_def    nTime_Flag;
#define		 b10msFlag		 	 	nTime_Flag.m_bit.b0
#define		 b50msFlag				nTime_Flag.m_bit.b1
#define		 b100msFlag	 	 	 	nTime_Flag.m_bit.b2
#define		 b250msFlag			 	nTime_Flag.m_bit.b3
#define		 b500msFlag				nTime_Flag.m_bit.b4
#define		 bTIMERtoADFlag			nTime_Flag.m_bit.b5


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

