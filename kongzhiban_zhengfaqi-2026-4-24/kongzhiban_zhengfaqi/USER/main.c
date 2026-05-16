#include "HeadInclude.h"
static void f_CalTm(void);

MCHINF MchInf = {0};
unsigned int i = 0;
unsigned char bfirstOpen = 1;

void f_closeHuilian(void)
{
	memset(Uart1_Inf.TxBuffer, 0, 100);

	Uart1_Inf.LensSendData = sizeof("AT+C400\r\n");
	memcpy(Uart1_Inf.TxBuffer, "AT+C400\r\n", Uart1_Inf.LensSendData);
	f_SendDeal_1(&Uart1_Inf, USART1);
}
void f_closeConnect(void)
{
	memset(Uart1_Inf.TxBuffer, 0, 100);

	Uart1_Inf.LensSendData = sizeof("AT+BA01\r\n");
	memcpy(Uart1_Inf.TxBuffer, "AT+BA01\r\n", Uart1_Inf.LensSendData);
	f_SendDeal_1(&Uart1_Inf, USART1);
}
void f_closeBle(void)
{
	memset(Uart1_Inf.TxBuffer, 0, 100);

	Uart1_Inf.LensSendData = sizeof("AT+B400\r\n");
	memcpy(Uart1_Inf.TxBuffer, "AT+B400\r\n", Uart1_Inf.LensSendData);
	f_SendDeal_1(&Uart1_Inf, USART1);
}

void f_StopBle(void) // 蓝牙不跑后台
{
	memset(Uart1_Inf.TxBuffer, 0, 100);

	Uart1_Inf.LensSendData = sizeof("AT+CG00\r\n");
	memcpy(Uart1_Inf.TxBuffer, "AT+CG00\r\n", Uart1_Inf.LensSendData);
	f_SendDeal_1(&Uart1_Inf, USART1);
}

int main()
{
	f_MCU_InitSfr();
	f_KeyInit();
	for (i = 0; i < 100000; i++)
	{
	}
	f_closeHuilian();
	for (i = 0; i < 100000; i++)
	{
	}
	f_closeBle();
	for (i = 0; i < 100000; i++)
	{
	}
	f_closeConnect();
	for (i = 0; i < 100000; i++)
	{
	}
	f_StopBle();

	while (1)
	{
		f_MCU_FeedDog(); // 喂狗
		f_RceDeal(&Uart2_Inf, USART2);
		f_RceDeal_1(&Uart1_Inf, USART1);
		f_CalTm();
	}
}
//***********************************
void f_CalTm(void)
{
	static unsigned char i = 0, bflag = 0;
	static unsigned int ADValue = 0;
	static unsigned char lastModeRunState = 0xff;
	static unsigned char poweroff_audio_step = 0;
	static unsigned char audio_task_last_step = AUDIO_STEP_IDLE;
	static unsigned char audio_task_timeout = 0;

	if (b100msFlag) // 10ms到
	{
		b100msFlag = false;
		MchInf.WaterLevel = 0;
		if (IO_WATER_LOW == 1)
			MchInf.WaterLevel |= 0x01;

		if (IO_WATER_MID == 1)
			MchInf.WaterLevel |= 0x02;

		if (IO_WATER_HIGH == 1)
			MchInf.WaterLevel |= 0x04;

		if (IO_WATER_LV4 == 1)
			MchInf.WaterLevel |= 0x08;

		if (IO_WATER_LV5 == 1)
			MchInf.WaterLevel |= 0x10;

		if (IO_CHUGOUBENG == 0)
			MchInf.WaterLevel |= 0x20;

		if (IO_TEST == 1)
			MchInf.WaterLevel |= 0x40;

		if (MchInf.bFlagRce)
		{
			MchInf.bFlagRce = 0;
			f_SendDeal(&Uart2_Inf, USART2);
		}
		if (MchInf.ModeRunState != lastModeRunState)
		{
			lastModeRunState = MchInf.ModeRunState;
		}

		if (MchInf.AudioTaskStep != audio_task_last_step)
		{
			audio_task_last_step = MchInf.AudioTaskStep;
			audio_task_timeout = 0;
		}
		else if (MchInf.AudioTaskStep != AUDIO_STEP_IDLE)
		{
			if (audio_task_timeout < 255)
				audio_task_timeout++;

			if (audio_task_timeout >= 10)
			{
				audio_task_timeout = 0;
				if (MchInf.AudioTaskStep == AUDIO_STEP_TF_WAIT_DISCONNECT)
					MchInf.bflagBleConnState = 0;
				else if (MchInf.AudioTaskStep == AUDIO_STEP_TF_WAIT_CM04_OK)
					MchInf.AudioTaskStep = AUDIO_STEP_TF_SEND_AB;
				else if (MchInf.AudioTaskStep == AUDIO_STEP_TF_WAIT_AB_OK)
				{
					MchInf.AudioCurrentTrack = MchInf.AudioTaskTarget;
					MchInf.MusicPlayState = 1;
					MchInf.AudioTaskStep = AUDIO_STEP_IDLE;
					MchInf.bflagbleset = 0;
					MchInf.bflagTF = 0;
				}
				else if (MchInf.AudioTaskStep == AUDIO_STEP_WHITE_WAIT_CB_OK)
					MchInf.AudioTaskStep = AUDIO_STEP_WHITE_SEND_CM01;
				else if (MchInf.AudioTaskStep == AUDIO_STEP_WHITE_WAIT_CM01_OK)
				{
					MchInf.AudioCurrentTrack = 0;
					MchInf.MusicPlayState = 0;
					MchInf.AudioTaskStep = AUDIO_STEP_IDLE;
					MchInf.bflagbleset = 0;
					MchInf.bflagTF = 0;
				}
			}
		}

		if (MchInf.Relay & 0x01) // 加水
			IO_RLY2_ON;
		else
			IO_RLY2_OFF;

		//		if(MchInf.Relay&0x02)//加热
		//		{
		//			IO_RLY9_ON;
		//			IO_RLY10_ON;
		//			IO_RLY11_ON;
		//		}
		//		else
		//		{
		//			IO_RLY9_OFF;
		//			IO_RLY10_OFF;
		//			IO_RLY11_OFF;
		//		}

		if (MchInf.Relay & 0x04) // 排水
		{
			IO_RLY3_ON;
			IO_RLY8_OFF;
		}
		else
		{
			IO_RLY3_OFF;
			IO_RLY8_ON;
		}

		if (MchInf.Relay & 0x08) // LED2
			IO_RLY1_ON;
		else
			IO_RLY1_OFF;

		if (MchInf.Relay & 0x10) // 出蒸汽
			IO_RLY5_ON;
		else
			IO_RLY5_OFF;

		if (MchInf.Relay & 0x20) // 除垢泵开
			IO_RLY6_ON;
		else
			IO_RLY6_OFF;

		if (MchInf.Relay & 0x40)
			IO_RLY7_ON;
		else
			IO_RLY7_OFF;

		// if (MchInf.Relay & 0x80)
		// 	IO_RLY8_ON;
		// else
		// 	IO_RLY8_OFF;

		if (MchInf.Relay & 0x0100)
			IO_RLY9_ON;
		else
			IO_RLY9_OFF;

		if (MchInf.Relay & 0x0200)
			IO_RLY10_ON;
		else
			IO_RLY10_OFF;

		if (MchInf.Relay & 0x0400)
			IO_RLY11_ON;
		else
			IO_RLY11_OFF;

		f_MCU_OutRGBPWM_1(MchInf.LEDState);
		memset(Uart1_Inf.TxBuffer, 0, 100);

		if ((MchInf.Blekey & 0x109) == 0x109) // power off: stop, idle, disconnect
		{
			MchInf.Blekey &= ~0x109;
			Uart1_Inf.LensSendData = sizeof("AT+CB\r\n");
			memcpy(Uart1_Inf.TxBuffer, "AT+CB\r\n", Uart1_Inf.LensSendData);
			f_SendDeal_1(&Uart1_Inf, USART1);

			poweroff_audio_step = 1;
		}

		else if (MchInf.Blekey & 0x01) // bofang
		{
			MchInf.Blekey &= ~0x01;
			Uart1_Inf.LensSendData = sizeof("AT+CB\r\n");
			memcpy(Uart1_Inf.TxBuffer, "AT+CB\r\n", Uart1_Inf.LensSendData);
			f_SendDeal_1(&Uart1_Inf, USART1);

			if (MchInf.MusicPlayState)
				MchInf.MusicPlayState = 0;
			else
				MchInf.MusicPlayState = 1;
		}

		else if (MchInf.Blekey & 0x02) // xiayiqu
		{
			MchInf.Blekey &= ~0x02;
			Uart1_Inf.LensSendData = sizeof("AT+CC\r\n");
			memcpy(Uart1_Inf.TxBuffer, "AT+CC\r\n", Uart1_Inf.LensSendData);
			f_SendDeal_1(&Uart1_Inf, USART1);
		}

		else if (MchInf.Blekey & 0x04) // 蓝牙匹配  软复位
		{
			MchInf.Blekey &= ~0x04;
			Uart1_Inf.LensSendData = sizeof("AT+CZ\r\n");
			memcpy(Uart1_Inf.TxBuffer, "AT+CZ\r\n", Uart1_Inf.LensSendData);
			f_SendDeal_1(&Uart1_Inf, USART1);
		}

		else if (poweroff_audio_step == 1)
		{
			Uart1_Inf.LensSendData = sizeof("AT+CM08\r\n");
			memcpy(Uart1_Inf.TxBuffer, "AT+CM08\r\n", Uart1_Inf.LensSendData);
			f_SendDeal_1(&Uart1_Inf, USART1);

			poweroff_audio_step = 2;
		}
		else if (poweroff_audio_step == 2)
		{
			f_closeConnect();
			poweroff_audio_step = 0;

			MchInf.bflagbleset = 0;
			MchInf.bflagTF = 0;
			MchInf.bflagBLEReset = 0;
			MchInf.AudioCurrentTrack = 0;
			MchInf.AudioTaskTarget = 0;
			MchInf.MusicPlayState = 0;
			MchInf.AudioTaskStep = AUDIO_STEP_IDLE;
		}

		else if (MchInf.Blekey & 0x08) // 空闲模式释放所有资源处于等待连接状态
		{
			MchInf.Blekey &= ~0x08;
			Uart1_Inf.LensSendData = sizeof("AT+CM08\r\n");
			memcpy(Uart1_Inf.TxBuffer, "AT+CM08\r\n", Uart1_Inf.LensSendData);
			f_SendDeal_1(&Uart1_Inf, USART1);
			//			f_closeConnect();
			MchInf.bflagBLEReset = 1;
		}

		else if (MchInf.Blekey & 0x100) // 断开连接
		{
			MchInf.Blekey &= ~0x100;
			f_closeConnect();
		}

		else if ((MchInf.AudioTaskStep != AUDIO_STEP_IDLE) || (MchInf.AudioQueueHead != MchInf.AudioQueueTail))
		{
			if (MchInf.AudioTaskStep == AUDIO_STEP_IDLE)
			{
				MchInf.AudioTaskTarget = MchInf.AudioQueue[MchInf.AudioQueueHead];
				MchInf.AudioQueueHead = (MchInf.AudioQueueHead + 1) & 0x07;

				if (MchInf.AudioTaskTarget == MchInf.AudioCurrentTrack)
				{
					MchInf.bflagbleset = 0;
					MchInf.bflagTF = 0;
				}
				else if (MchInf.AudioTaskTarget == 0)
				{
					if (MchInf.AudioCurrentTrack == 0)
					{
						MchInf.bflagbleset = 0;
						MchInf.bflagTF = 0;
					}
					else
					{
						Uart1_Inf.LensSendData = sizeof("AT+CB\r\n");
						memcpy(Uart1_Inf.TxBuffer, "AT+CB\r\n", Uart1_Inf.LensSendData);
						f_SendDeal_1(&Uart1_Inf, USART1);
						MchInf.AudioTaskStep = AUDIO_STEP_WHITE_WAIT_CB_OK;
						MchInf.bflagbleset = 5;
						MchInf.bflagTF = 0;
					}
				}
				else if (MchInf.AudioCurrentTrack == 0)
				{
					if (MchInf.bflagBleConnState > 0)
					{
						f_closeConnect();
						MchInf.AudioTaskStep = AUDIO_STEP_TF_WAIT_DISCONNECT;
						MchInf.bflagbleset = 1;
						MchInf.bflagTF = 1;
					}
					else
					{
						Uart1_Inf.LensSendData = sizeof("AT+CM04\r\n");
						memcpy(Uart1_Inf.TxBuffer, "AT+CM04\r\n", Uart1_Inf.LensSendData);
						f_SendDeal_1(&Uart1_Inf, USART1);
						MchInf.AudioTaskStep = AUDIO_STEP_TF_WAIT_CM04_OK;
						MchInf.bflagbleset = 2;
						MchInf.bflagTF = 1;
					}
				}
				else
				{
					Uart1_Inf.LensSendData = sizeof("AT+CB\r\n");
					memcpy(Uart1_Inf.TxBuffer, "AT+CB\r\n", Uart1_Inf.LensSendData);
					f_SendDeal_1(&Uart1_Inf, USART1);
					MchInf.AudioTaskStep = AUDIO_STEP_TF_WAIT_CM04_OK;
					MchInf.bflagbleset = 3;
					MchInf.bflagTF = 2;
				}
			}
			else if (MchInf.AudioTaskStep == AUDIO_STEP_TF_WAIT_DISCONNECT)
			{
				if (MchInf.bflagBleConnState == 0)
				{
					Uart1_Inf.LensSendData = sizeof("AT+CM04\r\n");
					memcpy(Uart1_Inf.TxBuffer, "AT+CM04\r\n", Uart1_Inf.LensSendData);
					f_SendDeal_1(&Uart1_Inf, USART1);
					MchInf.AudioTaskStep = AUDIO_STEP_TF_WAIT_CM04_OK;
					MchInf.bflagbleset = 2;
				}
			}
			else if (MchInf.AudioTaskStep == AUDIO_STEP_TF_SEND_AB)
			{
				Uart1_Inf.LensSendData = 0;
				Uart1_Inf.TxBuffer[Uart1_Inf.LensSendData++] = 'A';
				Uart1_Inf.TxBuffer[Uart1_Inf.LensSendData++] = 'T';
				Uart1_Inf.TxBuffer[Uart1_Inf.LensSendData++] = '+';
				Uart1_Inf.TxBuffer[Uart1_Inf.LensSendData++] = 'A';
				Uart1_Inf.TxBuffer[Uart1_Inf.LensSendData++] = 'B';
				Uart1_Inf.TxBuffer[Uart1_Inf.LensSendData++] = MchInf.AudioTaskTarget + 0x30;
				Uart1_Inf.TxBuffer[Uart1_Inf.LensSendData++] = '\r';
				Uart1_Inf.TxBuffer[Uart1_Inf.LensSendData++] = '\n';
				f_SendDeal_1(&Uart1_Inf, USART1);
				MchInf.AudioTaskStep = AUDIO_STEP_TF_WAIT_AB_OK;
				MchInf.bflagbleset = 4;
			}
			else if (MchInf.AudioTaskStep == AUDIO_STEP_WHITE_SEND_CM01)
			{
				Uart1_Inf.LensSendData = sizeof("AT+CM01\r\n");
				memcpy(Uart1_Inf.TxBuffer, "AT+CM01\r\n", Uart1_Inf.LensSendData);
				f_SendDeal_1(&Uart1_Inf, USART1);
				MchInf.AudioTaskStep = AUDIO_STEP_WHITE_WAIT_CM01_OK;
				MchInf.bflagbleset = 6;
			}
		}

		else if (MchInf.Blekey & 0x10) // 音量+
		{
			MchInf.Blekey &= ~0x10;
			Uart1_Inf.LensSendData = sizeof("AT+CE\r\n");
			memcpy(Uart1_Inf.TxBuffer, "AT+CE\r\n", Uart1_Inf.LensSendData);
			f_SendDeal_1(&Uart1_Inf, USART1);
		}

		else if (MchInf.Blekey & 0x20) // 音量-
		{
			MchInf.Blekey &= ~0x20;
			Uart1_Inf.LensSendData = sizeof("AT+CF\r\n");
			memcpy(Uart1_Inf.TxBuffer, "AT+CF\r\n", Uart1_Inf.LensSendData);
			f_SendDeal_1(&Uart1_Inf, USART1);
		}


		f_TmprDeal(CHANNEL_ADC0, 0);
		f_TmprDeal(CHANNEL_ADC1, 1);
	}

	if (b50msFlag)
	{
		b50msFlag = false;
	}

	//	if(b100msFlag)										//100ms meeted
	//	{
	//		b100msFlag = false;
	//
	////		  f_TmprDeal(CHANNEL_ADC0,0);
	////			f_TmprDeal(CHANNEL_ADC1,1);

	//	}

	if (b250msFlag)
	{
		b250msFlag = false;
		//		if((MchInf.bflagbleset == 2)&&(MchInf.ModeRunState == 1))
		//		{
		////			Uart1_Inf.LensSendData = 8;//sizeof("AT+AB1\r\n");
		////			memcpy(Uart1_Inf.TxBuffer,"AT+AB1\r\n",Uart1_Inf.LensSendData);//TF卡播放
		////			Uart1_Inf.LensSendData = sizeof("AT+AF/01/*.???\r\n");
		////			memcpy(Uart1_Inf.TxBuffer,"AT+AF/01/*.???\r\n",Uart1_Inf.LensSendData);
		//			//f_SendDeal_1(&Uart1_Inf,USART1);
		//
		//			Uart1_Inf.LensSendData = 0;
		//			Uart1_Inf.TxBuffer[Uart1_Inf.LensSendData++] ='A';
		//			Uart1_Inf.TxBuffer[Uart1_Inf.LensSendData++] = 'T';
		//			Uart1_Inf.TxBuffer[Uart1_Inf.LensSendData++] = '+';
		//			Uart1_Inf.TxBuffer[Uart1_Inf.LensSendData++] = 'A';
		//			Uart1_Inf.TxBuffer[Uart1_Inf.LensSendData++] = 'B';
		//			Uart1_Inf.TxBuffer[Uart1_Inf.LensSendData++] = '0';
		//			Uart1_Inf.TxBuffer[Uart1_Inf.LensSendData++] = '1';
		//			Uart1_Inf.TxBuffer[Uart1_Inf.LensSendData++] = '\r';
		//			Uart1_Inf.TxBuffer[Uart1_Inf.LensSendData++] = '\n';
		//			f_SendDeal_1(&Uart1_Inf,USART1);
		//		}
		//
	}

	if (b500msFlag) // 500ms meeted
	{
		b500msFlag = false;

		//		if(bflag==0)
		//		{
		//			IO_RLY6_ON;
		//			bflag = 1;
		//		}
		//		else
		//		{
		//			IO_RLY6_OFF;
		//			bflag = 0;
		//		}
	}

	if (b1sFlag) // 1S meeted
	{
		b1sFlag = false;
		//		MchInf.Blekey |= 0x100;
		if (bfirstOpen == 1)
		{
			f_closeHuilian();
			bfirstOpen = 2;
		}
		else if (bfirstOpen == 2)
		{
			f_closeBle();
			bfirstOpen = 3;
		}
		else if (bfirstOpen == 3)
		{
			f_closeConnect();
			bfirstOpen = 4;
		}

		f_Disp();
		// bflagbleset = 1;
	}
}
