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


#define GRID1_OFF_IO      GPIO_ResetBits(GPIOB,GPIO_Pin_6)//
#define GRID1_ON_IO     	GPIO_SetBits(GPIOB,GPIO_Pin_6)

#define GRID2_OFF_IO      GPIO_ResetBits(GPIOB,GPIO_Pin_5)//
#define GRID2_ON_IO     	GPIO_SetBits(GPIOB,GPIO_Pin_5)


#define SEG1_OFF_IO      GPIO_ResetBits(GPIOA,GPIO_Pin_15)//
#define SEG1_ON_IO     	GPIO_SetBits(GPIOA,GPIO_Pin_15)

#define SEG4_OFF_IO      GPIO_ResetBits(GPIOB,GPIO_Pin_1)//
#define SEG4_ON_IO     	GPIO_SetBits(GPIOB,GPIO_Pin_1)

#define SEG5_OFF_IO      GPIO_ResetBits(GPIOB,GPIO_Pin_15)//
#define SEG5_ON_IO     	GPIO_SetBits(GPIOB,GPIO_Pin_15)

#define SEG3_OFF_IO      GPIO_ResetBits(GPIOC,GPIO_Pin_11)//
#define SEG3_ON_IO     	GPIO_SetBits(GPIOC,GPIO_Pin_11)

#define SEG2_OFF_IO      GPIO_ResetBits(GPIOC,GPIO_Pin_10)//
#define SEG2_ON_IO     	GPIO_SetBits(GPIOC,GPIO_Pin_10)

#define SEG6_OFF_IO      GPIO_ResetBits(GPIOC,GPIO_Pin_6)//
#define SEG6_ON_IO     	GPIO_SetBits(GPIOC,GPIO_Pin_6)

#define SEG7_OFF_IO      GPIO_ResetBits(GPIOC,GPIO_Pin_7)//
#define SEG7_ON_IO     	GPIO_SetBits(GPIOC,GPIO_Pin_7)



#define ZHENDONG1_OFF_IO      GPIO_ResetBits(GPIOB,GPIO_Pin_12)//
#define ZHENDONG1_ON_IO     	GPIO_SetBits(GPIOB,GPIO_Pin_12)

#define ZHENDONG2_OFF_IO      GPIO_ResetBits(GPIOC,GPIO_Pin_13)//
#define ZHENDONG2_ON_IO     	GPIO_SetBits(GPIOC,GPIO_Pin_13)

#define ZHENDONG3_OFF_IO      GPIO_ResetBits(GPIOB,GPIO_Pin_2)//
#define ZHENDONG3_ON_IO     	GPIO_SetBits(GPIOB,GPIO_Pin_2)


#define LED_ZHENGFA_OFF_IO      GPIO_ResetBits(GPIOC,GPIO_Pin_12)//
#define LED_ZHENGFA_ON_IO     	GPIO_SetBits(GPIOC,GPIO_Pin_12)

#define LED_RGB_OFF_IO      GPIO_ResetBits(GPIOB,GPIO_Pin_14)//
#define LED_RGB_ON_IO     	GPIO_SetBits(GPIOB,GPIO_Pin_14)

#define LED_220V_OFF_IO      GPIO_ResetBits(GPIOC,GPIO_Pin_5)//
#define LED_220V_ON_IO     	GPIO_SetBits(GPIOC,GPIO_Pin_5)

#define LED_BLE_OFF_IO      GPIO_ResetBits(GPIOB,GPIO_Pin_13)//
#define LED_BLE_ON_IO     	GPIO_SetBits(GPIOB,GPIO_Pin_13)

#define LED_ADD_OFF_IO      GPIO_ResetBits(GPIOA,GPIO_Pin_5)//
#define LED_ADD_ON_IO     	GPIO_SetBits(GPIOA,GPIO_Pin_5)

#define LED_JIAN_OFF_IO      GPIO_ResetBits(GPIOA,GPIO_Pin_1)//
#define LED_JIAN_ON_IO     	GPIO_SetBits(GPIOA,GPIO_Pin_1)

#define LED_HARD_OFF_IO      GPIO_ResetBits(GPIOA,GPIO_Pin_0)//
#define LED_HARD_ON_IO     	GPIO_SetBits(GPIOA,GPIO_Pin_0)

#define LED_HARD1_OFF_IO      GPIO_ResetBits(GPIOC,GPIO_Pin_4)//
#define LED_HARD1_ON_IO     	GPIO_SetBits(GPIOC,GPIO_Pin_4)

#define LED_HARD2_OFF_IO      GPIO_ResetBits(GPIOC,GPIO_Pin_15)//
#define LED_HARD2_ON_IO     	GPIO_SetBits(GPIOC,GPIO_Pin_15)

#define LED_HARD3_OFF_IO      GPIO_ResetBits(GPIOC,GPIO_Pin_14)//
#define LED_HARD3_ON_IO     	GPIO_SetBits(GPIOC,GPIO_Pin_14)

#define LED_HARD4_OFF_IO      GPIO_ResetBits(GPIOC,GPIO_Pin_3)//
#define LED_HARD4_ON_IO     	GPIO_SetBits(GPIOC,GPIO_Pin_3)

#define LED_START_OFF_IO      GPIO_ResetBits(GPIOC,GPIO_Pin_1)//
#define LED_START_ON_IO     	GPIO_SetBits(GPIOC,GPIO_Pin_1)

#define LED_SLEEP_OFF_IO      GPIO_ResetBits(GPIOC,GPIO_Pin_0)//
#define LED_SLEEP_ON_IO     	GPIO_SetBits(GPIOC,GPIO_Pin_0)

#define LED_WATER_OFF_IO      GPIO_ResetBits(GPIOC,GPIO_Pin_8)//
#define LED_WATER_ON_IO     	GPIO_SetBits(GPIOC,GPIO_Pin_8)

#define LED_WATERIN_OFF_IO      GPIO_ResetBits(GPIOA,GPIO_Pin_8)//
#define LED_WATERIN_ON_IO     	GPIO_SetBits(GPIOA,GPIO_Pin_8)

#define LED_WATEROUT_OFF_IO      GPIO_ResetBits(GPIOA,GPIO_Pin_11)//
#define LED_WATEROUT_ON_IO     	GPIO_SetBits(GPIOA,GPIO_Pin_11)

#define LED_WATERLOW_OFF_IO      GPIO_ResetBits(GPIOB,GPIO_Pin_8)//
#define LED_WATERLOW_ON_IO     	GPIO_SetBits(GPIOB,GPIO_Pin_8)

#define LED_WATERMID_OFF_IO      GPIO_ResetBits(GPIOA,GPIO_Pin_12)//
#define LED_WATERMID_ON_IO     	GPIO_SetBits(GPIOA,GPIO_Pin_12)

#define LED_WATERHIGH_OFF_IO      GPIO_ResetBits(GPIOC,GPIO_Pin_9)//
#define LED_WATERHIGH_ON_IO     	GPIO_SetBits(GPIOC,GPIO_Pin_9)

#define LED_TPRLV1_OFF_IO      GPIO_ResetBits(GPIOB,GPIO_Pin_4)//
#define LED_TPRLV1_ON_IO     	GPIO_SetBits(GPIOB,GPIO_Pin_4)

#define LED_TPRLV2_OFF_IO      GPIO_ResetBits(GPIOB,GPIO_Pin_7)//
#define LED_TPRLV2_ON_IO     	GPIO_SetBits(GPIOB,GPIO_Pin_7)

#define LED_TPRLV3_OFF_IO      GPIO_ResetBits(GPIOB,GPIO_Pin_3)//
#define LED_TPRLV3_ON_IO     	GPIO_SetBits(GPIOB,GPIO_Pin_3)

#define LED_TPR_OFF_IO      GPIO_ResetBits(GPIOD,GPIO_Pin_2)//
#define LED_TPR_ON_IO     	GPIO_SetBits(GPIOD,GPIO_Pin_2)

#define LED_CLR_OFF_IO      GPIO_ResetBits(GPIOA,GPIO_Pin_0)//
#define LED_CLR_ON_IO     	GPIO_SetBits(GPIOA,GPIO_Pin_0)

extern byte_def    nTime_Flag;
#define		 b10msFlag		 	 	nTime_Flag.m_bit.b0
#define		 b50msFlag				nTime_Flag.m_bit.b1
#define		 b100msFlag	 	 	 	nTime_Flag.m_bit.b2
#define		 b250msFlag			 	nTime_Flag.m_bit.b3
#define		 b500msFlag				nTime_Flag.m_bit.b4
#define		 bTIMERtoADFlag			nTime_Flag.m_bit.b5
#define		 b20msFlag    			nTime_Flag.m_bit.b6

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

