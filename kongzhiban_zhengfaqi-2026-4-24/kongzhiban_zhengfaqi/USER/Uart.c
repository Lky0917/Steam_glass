#include "HeadInclude.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef ENABLE_UART1
UARTINF Uart1_Inf = {0};
#endif

#ifdef ENABLE_UART1
UARTINF Uart2_Inf = {0};
#endif

#ifdef ENABLE_UART1
UARTINF Uart3_Inf = {0};
#endif

MCHINF_RCE MchInf_Rce = {0};
MCHINF_SEND MchInf_Send = {0};

unsigned long SystemTick_Get_Ticks_ms;

#define HEADDATA 0xAA
//*****************************
// 首次发送函数，使其出现发送完成中断
//*****************************
void f_StartSend_Uart(UARTINF *UartInf, USART_TypeDef *USARTx)
{
	UartInf->bSendingFlag = 1;
	UartInf->nCurTxPos = 0;
	USART_SendData(USARTx, UartInf->TxBuffer[UartInf->nCurTxPos]);
	UartInf->nCurTxPos++;
}
// 接收中断服务函数
void f_Interrupt_RceDeal(UARTINF *UartInf, USART_TypeDef *USARTx)
{
	unsigned char UartTemp;
	UartTemp = USART_ReceiveData(USARTx);
	UartInf->nRceTimefromSysTick = SystemTick_Get_Ticks_ms;
	if ((!UartInf->bAnasyingFlag) && (UartTemp == HEADDATA))
	{
		UartInf->nCurRxPos = 0;
		UartInf->bAnasyingFlag = true;
	}

	if (UartInf->bAnasyingFlag)
	{
		UartInf->RxBufferTemp[UartInf->nCurRxPos] = UartTemp;
		if (UartInf->nCurRxPos < (LENS_RX_BUFFER - 1))
			UartInf->nCurRxPos++;
	}
}
#define HEADDATA1 'O'
void f_Interrupt_RceDeal_1(UARTINF *UartInf, USART_TypeDef *USARTx)
{
	unsigned char UartTemp;
	UartTemp = USART_ReceiveData(USARTx);
	UartInf->nRceTimefromSysTick = SystemTick_Get_Ticks_ms;
	if ((!UartInf->bAnasyingFlag) && ((UartTemp == HEADDATA1) || (UartTemp == 'T') || (UartTemp == 'M')))
	{
		UartInf->nCurRxPos = 0;
		UartInf->bAnasyingFlag = true;
	}

	if (UartInf->bAnasyingFlag)
	{
		UartInf->RxBufferTemp[UartInf->nCurRxPos] = UartTemp;
		if (UartInf->nCurRxPos < (LENS_RX_BUFFER - 1))
			UartInf->nCurRxPos++;
	}
}
// 发送中断服务函数
void f_Interrupt_SendDeal(UARTINF *UartInf, USART_TypeDef *USARTx)
{
	if (UartInf->bSendingFlag)
	{
		USART_SendData(USARTx, UartInf->TxBuffer[UartInf->nCurTxPos++]);
		if (UartInf->nCurTxPos >= UartInf->LensSendData)
			UartInf->bSendingFlag = false;
	}
}
// 发送数据
void f_SendDeal(UARTINF *UartInf, USART_TypeDef *USARTx)
{
	unsigned char i;
	UartInf->LensSendData = 0;
	UartInf->TxBuffer[UartInf->LensSendData++] = 0xAA;
	UartInf->TxBuffer[UartInf->LensSendData++] = 0x55;
	UartInf->TxBuffer[UartInf->LensSendData++] = MchInf.WaterLevel;
	UartInf->TxBuffer[UartInf->LensSendData++] = MchInf.Temper[0] & 0xff;
	UartInf->TxBuffer[UartInf->LensSendData++] = MchInf.Temper[1] & 0xff;
	UartInf->TxBuffer[UartInf->LensSendData++] = MchInf.bErrorTemper;
	UartInf->TxBuffer[UartInf->LensSendData++] = MchInf.BleCMDState;
	UartInf->TxBuffer[UartInf->LensSendData++] = MchInf.bFlagRce;
	UartInf->TxBuffer[UartInf->LensSendData++] = MchInf.bflagBleConnState;

	MchInf_Send.CheckSum = 0;
	for (i = 0; i < UartInf->LensSendData; i++)
		MchInf_Send.CheckSum += UartInf->TxBuffer[i];

	UartInf->TxBuffer[UartInf->LensSendData++] = MchInf_Send.CheckSum;

	MchInf.BleCMDState = 0;

	f_StartSend_Uart(UartInf, USARTx);
}

void f_SendDeal_1(UARTINF *UartInf, USART_TypeDef *USARTx)
{
	unsigned char i;

	f_StartSend_Uart(UartInf, USARTx);
}
static void f_audio_queue_clear(void)
{
	MchInf.AudioQueueHead = 0;
	MchInf.AudioQueueTail = 0;
}

static void f_audio_queue_push(unsigned char mode)
{
	unsigned char last = 0;

	if (MchInf.AudioCurrentTrack == mode)
		return;

	if (MchInf.AudioTaskStep != AUDIO_STEP_IDLE)
	{
		if (MchInf.AudioTaskTarget == mode)
			return;

		f_audio_queue_clear();
		MchInf.AudioQueue[0] = mode;
		MchInf.AudioQueueHead = 0;
		MchInf.AudioQueueTail = 1;
		return;
	}

	if (MchInf.AudioQueueHead != MchInf.AudioQueueTail)
	{
		last = (MchInf.AudioQueueTail - 1) & 0x07;
		if (MchInf.AudioQueue[last] == mode)
			return;

		f_audio_queue_clear();
	}

	MchInf.AudioQueue[0] = mode;
	MchInf.AudioQueueHead = 0;
	MchInf.AudioQueueTail = 1;
}
// 接收数据
void f_RceDeal(UARTINF *UartInf, USART_TypeDef *USARTx)
{
	unsigned char i, checksum = 0, rxMode = 0;
	unsigned int rxBlekey = 0;
	if ((UartInf->bAnasyingFlag) &&
		((SystemTick_Get_Ticks_ms - UartInf->nRceTimefromSysTick) > UARTDELAYTIME))
	{
		for (i = 0; i < (UartInf->nCurRxPos - 1); i++)
		{
			checksum += UartInf->RxBufferTemp[i];
		}
		UartInf->bAnasyingFlag = false;

		if (checksum != UartInf->RxBufferTemp[UartInf->nCurRxPos - 1])
			return;

		MchInf.Relay = UartInf->RxBufferTemp[2];
		MchInf.Relay |= UartInf->RxBufferTemp[3] << 8;
		rxBlekey = UartInf->RxBufferTemp[4];
		rxBlekey |= (UartInf->RxBufferTemp[5] << 8);
		rxMode = UartInf->RxBufferTemp[7];
		MchInf.Blekey = rxBlekey & ~(0x40 | 0x80 | 0x200 | 0x400 | 0x800);
		MchInf.LEDState = UartInf->RxBufferTemp[6];
		MchInf.ModeRunState = rxMode; // 程序0 1 2 3
		if ((rxBlekey & 0x109) == 0x109)
		{
			f_audio_queue_clear();
			MchInf.AudioTaskStep = AUDIO_STEP_IDLE;
			MchInf.AudioTaskTarget = 0;
		}
		else if (rxBlekey & 0x80)
		{
			f_audio_queue_push(0);
		}
		else if (rxBlekey & 0x200)
		{
			f_audio_queue_push(1);
		}
		else if (rxBlekey & 0x400)
		{
			f_audio_queue_push(2);
		}
		else if (rxBlekey & 0x800)
		{
			f_audio_queue_push(3);
		}
		MchInf.bFlagRce = 1;
	}
}
void f_RceDeal_1(UARTINF *UartInf, USART_TypeDef *USARTx)
{
	unsigned char i, checksum = 0;
	if ((UartInf->bAnasyingFlag) &&
		((SystemTick_Get_Ticks_ms - UartInf->nRceTimefromSysTick) > UARTDELAYTIME))
	{
		UartInf->bAnasyingFlag = false;
		if ((UartInf->RxBufferTemp[0] == 'O') && (UartInf->RxBufferTemp[1] == 'K'))
		{
			if (MchInf.AudioTaskStep == AUDIO_STEP_TF_WAIT_CM04_OK)
			{
				MchInf.AudioTaskStep = AUDIO_STEP_TF_SEND_AB;
			}
			else if (MchInf.AudioTaskStep == AUDIO_STEP_TF_WAIT_AB_OK)
			{
				MchInf.AudioTaskStep = AUDIO_STEP_IDLE;
				MchInf.AudioCurrentTrack = MchInf.AudioTaskTarget;
				MchInf.bflagBleConnState = 2;
				MchInf.bflagbleset = 0;
				MchInf.bflagTF = 0;
			}
			else if (MchInf.AudioTaskStep == AUDIO_STEP_WHITE_WAIT_CB_OK)
			{
				MchInf.AudioTaskStep = AUDIO_STEP_WHITE_SEND_CM01;
			}
			else if (MchInf.AudioTaskStep == AUDIO_STEP_WHITE_WAIT_CM01_OK)
			{
				MchInf.AudioTaskStep = AUDIO_STEP_IDLE;
				MchInf.AudioCurrentTrack = 0;
				MchInf.bflagBleConnState = 1;
				MchInf.bflagbleset = 0;
				MchInf.bflagTF = 0;
			}
		}
		else if ((UartInf->RxBufferTemp[0] == 'T') && (UartInf->RxBufferTemp[1] == 'S'))
		{
			if (UartInf->RxBufferTemp[4] == '0')
				MchInf.bflagBleConnState = 0; // 未连接成功
			else if (UartInf->RxBufferTemp[4] == '1')
				MchInf.bflagBleConnState = 1; // 已连接成功但未播放音乐
			else if (UartInf->RxBufferTemp[4] == '2')
				MchInf.bflagBleConnState = 2; // 正在播放音乐
		}
		else if ((UartInf->RxBufferTemp[0] == 'T') && (UartInf->RxBufferTemp[1] == 'L'))
		{
			if ((UartInf->RxBufferTemp[4] == '0') || (UartInf->RxBufferTemp[4] == '1'))
				MchInf.bflagBleConnState = 0; // 未连接成功
			else if (UartInf->RxBufferTemp[4] == '3')
				MchInf.bflagBleConnState = 1; // 已连接成功但未播放音乐
											  //			else 	if(UartInf->RxBufferTemp[4] == '2')
											  //				MchInf.bflagBleConnState = 2;//正在播放音乐
		}

		memset(UartInf->RxBufferTemp, 0, 100);
	}
}
