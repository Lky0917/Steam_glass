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

// 接收中断服务函数
void f_Interrupt_RceDeal_1(UARTINF *UartInf, USART_TypeDef *USARTx)
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

	//	MchInf.Relay = 0x55AA;
	UartInf->TxBuffer[UartInf->LensSendData++] = MchInf.Relay & 0xff;
	UartInf->TxBuffer[UartInf->LensSendData++] = (MchInf.Relay >> 8) & 0xff;
	UartInf->TxBuffer[UartInf->LensSendData++] = MchInf.blekey;
	UartInf->TxBuffer[UartInf->LensSendData++] = (MchInf.blekey >> 8) & 0xff;
	//	if(MchInf.RGBMode1 == RGB_WHITE)
	//		UartInf->TxBuffer[UartInf->LensSendData++] = 0;
	//	else
	UartInf->TxBuffer[UartInf->LensSendData++] = MchInf.RGBMode1;

	UartInf->TxBuffer[UartInf->LensSendData++] = MchInf.ModeRunState;
	MchInf_Send.CheckSum = 0;
	for (i = 0; i < UartInf->LensSendData; i++)
		MchInf_Send.CheckSum += UartInf->TxBuffer[i];

	UartInf->TxBuffer[UartInf->LensSendData++] = MchInf_Send.CheckSum;

	f_StartSend_Uart(UartInf, USARTx);
	MchInf.blekey = 0;
}

// 接收数据
void f_RceDeal(UARTINF *UartInf, USART_TypeDef *USARTx)
{
	unsigned char i, checksum = 0;
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

		MchInf.WaterLV = UartInf->RxBufferTemp[2];
		MchInf.TmprWater = UartInf->RxBufferTemp[3]; // 水温
		MchInf.TmprHouse = UartInf->RxBufferTemp[4]; // 室温
		MchInf.bErrorTmpr = UartInf->RxBufferTemp[5];
		MchInf.BleCMDState = UartInf->RxBufferTemp[6];
		MchInf.bflagBleConnState = UartInf->RxBufferTemp[8]; // 蓝牙状态
		MchInf.MusicOn = (MchInf.bflagBleConnState == 2) ? 1 : 0;


		if (MchInf.WaterLV & 0x20)
			MchInf.bPumpChugou = 1;
		else
			MchInf.bPumpChugou = 0;

		if (MchInf.WaterLV & 0x40)
			MchInf.bFunChugouAutoOrManu = 1; // 断开手动   闭合自动
		else
			MchInf.bFunChugouAutoOrManu = 0;

		if (MchInf.WaterLV & 0x10)
			MchInf.bChugouYeWei = 1;
		else
			MchInf.bChugouYeWei = 0;

		MchInf.WaterLV &= 0x07;

		if ((MchInf.WaterLV != 0x07) && (MchInf.WaterLV != 0x03) && (MchInf.WaterLV != 0x01) && (MchInf.WaterLV != 0))
			MchInf.bErrWaterLv = 1;
		else
			MchInf.bErrWaterLv = 0;

		//		MchInf.bErrorTmpr = 0;
		//		MchInf.TmprHouse = 30;
		//		MchInf.TmprWater = 99;
	}
}

// 接收数据
void f_RceDeal_1(UARTINF *UartInf, USART_TypeDef *USARTx)
{
	unsigned char i, checksum = 0;
	if ((UartInf->bAnasyingFlag) &&
		((SystemTick_Get_Ticks_ms - UartInf->nRceTimefromSysTick) > UARTDELAYTIME))
	{
		for (i = 0; i < (UartInf->nCurRxPos - 1); i++)
		{
			checksum += UartInf->RxBufferTemp[i];
		}
		UartInf->bAnasyingFlag = false;

		if (checksum != UartInf->RxBufferTemp[UartInf->nCurRxPos - 1])
		{
			MchInf.bGetKeyOK = 0;
			return;
		}
		MchInf.KeyState = (unsigned int)(UartInf->RxBufferTemp[3] + (UartInf->RxBufferTemp[4] << 8) + (UartInf->RxBufferTemp[5] << 16) + (UartInf->RxBufferTemp[6] << 24));

		MchInf.bGetKeyOK = 1;
	}
}
