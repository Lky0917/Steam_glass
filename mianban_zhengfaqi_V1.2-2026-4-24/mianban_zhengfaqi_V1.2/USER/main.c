#include "HeadInclude.h"
static void f_CalTm(void);

MCHINF MchInf = {0};
byte_def MchFlag;
MODE ModeState;
TESTMODEINF TestModeInf;

void f_deal_test(void)
{
	MchInf.btestmode = 0;
	if (MchInf.btestmode)
	{
		TestModeInf.TIMERUNCHUGOU = 10;
		TestModeInf.TIMEZHENGQIONEHOUR = 10;
		TestModeInf.TIMEAUTOSLEEP = 1000;
		TestModeInf.TIMEWAITNOKEY = 1200;
		TestModeInf.TIMENOSTARTCHUGOU = 6000; // 60s
		TestModeInf.TIMECHUGOUSLEEP = 6000;
		TestModeInf.TIMEPAISHUIZANTING = 3000; // 1min
		TestModeInf.TIMEPAISHUIRUN = 6000;	   // 30s
		TestModeInf.TIMEHARD1CHUGOUALAM = 60 * 6;
		TestModeInf.TIMEHARD2CHUGOUALAM = 23 * 6;
		TestModeInf.TIMEHARD3CHUGOUALAM = 19 * 6;
		TestModeInf.TIMEHARD4CHUGOUALAM = 8 * 6;
		TestModeInf.TIMEHARD1CHUGOUALAMAGAIN = (60 + 3) * 6;
		TestModeInf.TIMEHARD2CHUGOUALAMAGAIN = (23 + 3) * 6;
		TestModeInf.TIMEHARD3CHUGOUALAMAGAIN = (19 + 3) * 6;
		TestModeInf.TIMEHARD4CHUGOUALAMAGAIN = (8 + 3) * 6;
	}
	else
	{

		TestModeInf.TIMEZHENGQIONEHOUR = 3600;
		TestModeInf.TIMEAUTOSLEEP = 3600;
		TestModeInf.TIMEWAITNOKEY = 12000 / 2;

		TestModeInf.TIMEPAISHUIZANTING = 60 * 60 * 100 / 2; // 1h
		TestModeInf.TIMEPAISHUIRUN = 30 * 60 * 100 / 2;		// 30min
#ifdef TEST_SUOSHI
		// ÊµãËØïÁº©Â∞è60ÂÄ?
		TestModeInf.TIMENOSTARTCHUGOU = 6000 / 2;
		TestModeInf.TIMECHUGOUSLEEP = 6000 / 2;
		TestModeInf.TIMEHARD1CHUGOUALAM = 4 * 60;	   // 60*60  /60;
		TestModeInf.TIMEHARD2CHUGOUALAM = 3 * 60;	   // 23*60/60;
		TestModeInf.TIMEHARD3CHUGOUALAM = 2 * 60;	   // 19*60/60;
		TestModeInf.TIMEHARD4CHUGOUALAM = 1 * 60;	   // 8*60/60;
		TestModeInf.TIMEHARD1CHUGOUALAMAGAIN = 5 * 60; //(60+3)* 60/60;
		TestModeInf.TIMEHARD2CHUGOUALAMAGAIN = 4 * 60; //(23+3)*60/60;
		TestModeInf.TIMEHARD3CHUGOUALAMAGAIN = 3 * 60; //(19+3)*60/60;
		TestModeInf.TIMEHARD4CHUGOUALAMAGAIN = 2 * 60; //(8+3)*60/60;
		TestModeInf.TIMERUNCHUGOU = 3600 / 60;
#else
		TestModeInf.TIMENOSTARTCHUGOU = 60000 / 2;
		TestModeInf.TIMECHUGOUSLEEP = 60000 / 2;
		TestModeInf.TIMEHARD1CHUGOUALAM = 60 * 60;			  //  /60;
		TestModeInf.TIMEHARD2CHUGOUALAM = 23 * 60;			  /// 60;
		TestModeInf.TIMEHARD3CHUGOUALAM = 19 * 60;			  /// 60;
		TestModeInf.TIMEHARD4CHUGOUALAM = 8 * 60;			  /// 60;
		TestModeInf.TIMEHARD1CHUGOUALAMAGAIN = (60 + 3) * 60; /// 60;
		TestModeInf.TIMEHARD2CHUGOUALAMAGAIN = (23 + 3) * 60; /// 60;
		TestModeInf.TIMEHARD3CHUGOUALAMAGAIN = (19 + 3) * 60; /// 60;
		TestModeInf.TIMEHARD4CHUGOUALAMAGAIN = (8 + 3) * 60;  /// 60;
		TestModeInf.TIMERUNCHUGOU = 3600;					  /// 60;
#endif
	}
}
void f_Deal_zhendong(void) // 10ms
{
	static unsigned char timezhendong1 = 0, timezhendong2 = 0, timezhendong3 = 0;
	if (MchInf.bflagzhendong1)
	{
		timezhendong1++;
		if (timezhendong1 < 30)
		{
			ZHENDONG1_ON_IO;
		}
		else
		{
			ZHENDONG1_OFF_IO;
			timezhendong1 = 0;
			MchInf.bflagzhendong1 = 0;
		}
	}

	if (MchInf.bflagzhendong2)
	{
		timezhendong2++;
		if (timezhendong2 < 30)
		{
			ZHENDONG2_ON_IO;
		}
		else
		{
			ZHENDONG2_OFF_IO;
			timezhendong2 = 0;
			MchInf.bflagzhendong2 = 0;
		}
	}
	if (MchInf.bflagzhendong3)
	{
		timezhendong3++;
		if (timezhendong3 < 30)
		{
			ZHENDONG3_ON_IO;
		}
		else
		{
			ZHENDONG3_OFF_IO;
			timezhendong3 = 0;
			MchInf.bflagzhendong3 = 0;
		}
	}
}
void f_light(void)
{
	if (bLightFlag == 0)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		bLightFlag = 1;
	}
	else
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		bLightFlag = 0;
	}
}
int main()
{
	unsigned int i = 50000;
	f_MCU_InitSfr();
	f_KeyInit();
	MchInf.MusicSound = 50;
	//	MchInf.RGBMode = RGB_WHITE;
	//	MchInf.RGBMode1 = RGB_WHITE;
	ModeState = MODESLEEP; // ÔøΩÔøΩÔøΩÔøΩ

	f_deal_test();
	MchInf.TmprHouse = 38;
	MchInf.WaterHardState = 4;
	MchInf.TmrLV = 1;

	MchInf.TmprHouse = 38;
	//	MchInf.WaterHardState = 1;
	MchInf.TmrLV = 1;
	MchInf.bFirstOpen = 1;
	f_Flash_read();
	while (i--) // delay yanshi
	{
	}

	MchInf.blekey |= 0x100; // ∂œø™¿∂—¿¡¨Ω”
	while (1)
	{
		f_MCU_FeedDog(); // ŒπÔøΩÔøΩ
		f_RceDeal_1(&Uart1_Inf, USART1);
		f_RceDeal(&Uart2_Inf, USART2);
		f_CalTm();
	}
}
//***********************************
void f_CalTm(void)
{
	if (b10msFlag)
	{
		b10msFlag = 0;
		//		f_IncBuzTm();
		//		f_OutBuz();
		f_AddKeyPressTm();
		f_Deal_zhendong();
		f_KeyScan(); // ÔøΩÔøΩÔøΩÔøΩ…®ÔøΩÔøΩ
		f_KeyDeal();
		//		f_SendDeal(&Uart2_Inf,USART2);
	}

	if (b20msFlag) // 10msÔøΩÔøΩ
	{
		b20msFlag = false;

		// ÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩ ±ÔøΩÔøΩ

		f_Disp();
		f_Deal_Seg();
		f_Deal_PWM();
	}

	if (b50msFlag)
	{
		b50msFlag = false;
		f_SendDeal(&Uart2_Inf, USART2);
	}

	if (b100msFlag) // 100ms meeted
	{
		b100msFlag = false;
		//		f_SendDeal(&Uart1_Inf,USART1);
	}

	if (b250msFlag)
	{
		b250msFlag = false;
	}

	if (b500msFlag) // 500ms meeted
	{
		b500msFlag = false;

		//		f_light();
	}

	if (b1sFlag) // 1S meeted
	{
		b1sFlag = false;

		if (MchInf.bFlagWriteFlash)
		{
			if (ModeState == MODESLEEP)
			{
				MchInf.bFlagWriteFlash = 0;
				f_Flash_Write();
			}
		}

		//		f_deal_test();

		if (MchInf.bFunZhengqiOpen) // ÔøΩÔøΩÔøΩÔøΩ ±
		{
			if (ModeState != MODEZANTING) // ÔøΩÔøΩÔøΩÔøΩ ±ÔøΩÔøΩÕ£
				MchInf.timeRunZhengqi++;
/*
			if((MchInf.bflagBleConnState!= 2)&&(MchInf.bOpenMusic==0))//ÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩ
			{
				MchInf.blekey |= 0x01;
				MchInf.MusicOn = 1;
				MchInf.bOpenMusic = 1;
			}
*/
#ifdef TEST_SUOSHI
			// if(MchInf.timeRunZhengqi >= 5)
			if (MchInf.timeRunZhengqi >= 5)
#else
			if (MchInf.timeRunZhengqi >= 60)				  // 1min
#endif
			{
				MchInf.zhengqijiworktimesum++; // Â∑•‰ΩúÊó∂Èïø

				if (MchInf.zhengqijiworktimesum % 10 == 0)
				{
					MchInf.bFlagWriteFlash = 1;
				}

				MchInf.timeRunZhengqi = 0;
				// MchInf.bFunHot = 0;
				if (MchInf.TimeZhengQi == 0)
				{
					MchInf.bFunZhengqiOpen = 0;
				}
				else
				{
					MchInf.timePaiShuiCal = 0;
					MchInf.TimeZhengQi--;
				}
			}
		}

		if (MchInf.bFunChuGouCal)
		{
			MchInf.ntimeRunChuGou++;
			if (MchInf.ntimeRunChuGou >= TestModeInf.TIMERUNCHUGOU) // 1hour
			{
				MchInf.timeRmdChuGou--;
				MchInf.ntimeRunChuGou = 0;
				if (MchInf.timeRmdChuGou == 0)
					MchInf.bFunChuGouCal = 0;
			}
		}

		if ((MchInf.bFunChuGou == 0) && (MchInf.bFunChuGouEver))
		{
			MchInf.nCalTimeAutoSleep++;
			if (MchInf.nCalTimeAutoSleep == (TestModeInf.TIMEAUTOSLEEP + 120))
			{
				if ((MchInf.LED2State == 0) && (MchInf.bflagBleConnState != 2) && (MchInf.RGBMode1 == RGB_CLOSE))
				{
					ModeState = MODESLEEP;
					MchInf.blekey |= 0x100; // ∂œø™¿∂—¿¡¨Ω”
				}
			}
			if (MchInf.nCalTimeAutoSleep == TestModeInf.TIMEAUTOSLEEP)
			{
				MchInf.RGBMode1 = RGB_CLOSE;
				MchInf.LED2State = 0;
				if ((MchInf.MusicOn == 1) || (MchInf.bflagBleConnState == 2))
					MchInf.blekey |= 0x01; // ÔøΩÔøΩÕ£
			}
		}
	}
}
