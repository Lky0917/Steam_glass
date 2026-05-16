/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "HeadInclude.h"

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

#ifdef  ENABLE_TIMER2
void TIM2_IRQHandler(void)
{
	static unsigned char nTimerCnt;
	static unsigned char nTime50ms;
	static unsigned char nTime100ms;
	static unsigned int  nTime500ms;
	static unsigned int  nTime1000ms;
	static unsigned char nTimer10ms;
	static unsigned char nTime200us;

	if(TIM_GetFlagStatus(TIM2,TIM_FLAG_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);//清中断
		f_Disp_saomiao();

		nTime200us++;
		if(nTime200us > 5)
		{
		nTime200us = 0;
		nTimerCnt++;//1ms
		nTime50ms ++;
		nTime100ms ++;
		nTime500ms ++;
		nTime1000ms ++;
		SystemTick_Get_Ticks_ms++;
		
		nTimer10ms++;
		}
	}
	if(nTimer10ms >= 10)
	{
		b10msFlag = true;

		nTimer10ms = 0;
	}
	if(nTimerCnt >= 20)//10ms
	{
		b20msFlag = true;
		//b10msFlag = true;
		nTimerCnt = 0;
	}
	if(nTime50ms >=50)//50ms
	{
		b50msFlag = true;
		b10HzFlag ^= true;
		nTime50ms = 0;
	}
	if(nTime100ms >= 100)
	{
		b100msFlag = true;
		bTIMERtoADFlag = true;
		nTime100ms = 0;
	}
	if(nTime500ms >=500)
	{
		b500msFlag = true;
		b1HzFlag ^= true;
		nTime500ms = 0;
	}
	if(nTime1000ms >= 1000)//1s
	{
		nTime1000ms = 0;
		b1sFlag = true;
		b0d5HzFlag ^= true;

	}
	
}
#endif

#ifdef  ENABLE_TIMER3
void TIM3_IRQHandler(void)
{
//	static uint16_t nCnt;
	if (TIM_GetFlagStatus(TIM3,TIM_FLAG_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM3, TIM_FLAG_Update); //清中断
		

	}
}
#endif

//*****************************************
//*****************************************
#ifdef ENABLE_UART1
void USART1_IRQHandler(void)//9600  pa9 pa10
{
	if(USART_GetITStatus(USART1,USART_IT_TC) != RESET)
	{
		f_Interrupt_SendDeal(&Uart1_Inf,USART1);
		USART_ClearITPendingBit(USART1,USART_IT_TC); 
	}
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!= RESET)
	{	
		f_Interrupt_RceDeal_1(&Uart1_Inf,USART1);
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}

}
#endif
//*****************************************
#ifdef ENABLE_UART2
void USART2_IRQHandler(void)//115200  pa2 pa3
{
	if(USART_GetITStatus(USART2,USART_IT_TC) != RESET)
	{
		f_Interrupt_SendDeal(&Uart2_Inf,USART2);
		USART_ClearITPendingBit(USART2,USART_IT_TC); 
	}
	if(USART_GetITStatus(USART2,USART_IT_RXNE)!= RESET)
	{	
		f_Interrupt_RceDeal(&Uart2_Inf,USART2);
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
	}
}
#endif

#ifdef ENABLE_UART3
void USART3_IRQHandler(void)//115200  pb10 pb11
{
	if(USART_GetITStatus(USART3,USART_IT_TC) != RESET)
	{
		f_Interrupt_SendDeal(&Uart3_Inf,USART3);
		USART_ClearITPendingBit(USART3,USART_IT_TC); 
	}
	if(USART_GetITStatus(USART3,USART_IT_RXNE)!= RESET)
	{	
		f_Interrupt_RceDeal(&Uart3_Inf,USART3);
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);
	}
}
#endif




/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
