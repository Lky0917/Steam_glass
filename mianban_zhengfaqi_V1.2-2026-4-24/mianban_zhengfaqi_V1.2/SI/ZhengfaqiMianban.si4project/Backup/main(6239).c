#include "HeadInclude.h"
static void f_CalTm(void);

MCHINF  MchInf = {0};
byte_def MchFlag;
MODE  ModeState;
TESTMODEINF TestModeInf;

void f_deal_test(void)
{
		if(MchInf.btestmode)
		{
			TestModeInf.TIMERUNCHUGOU = 10;
			TestModeInf.TIMEZHENGQIONEHOUR = 10;
			TestModeInf.TIMEAUTOSLEEP = 10;
			TestModeInf.TIMEWAITNOKEY = 1200;
			TestModeInf.TIMENOSTARTCHUGOU = 6000;//60s
			TestModeInf.TIMECHUGOUSLEEP = 6000;
		}
		else
		{
			TestModeInf.TIMERUNCHUGOU = 3600;
			TestModeInf.TIMEZHENGQIONEHOUR = 3600;
			TestModeInf.TIMEAUTOSLEEP = 3600;
			TestModeInf.TIMEWAITNOKEY = 12000;
			TestModeInf.TIMENOSTARTCHUGOU = 60000;
			TestModeInf.TIMECHUGOUSLEEP = 60000;
		}

}

int main()
{
	f_MCU_InitSfr();
	f_KeyInit();
	MchInf.MusicSound = 50;
	MchInf.RGBMode = RGB_WHITE;
	MchInf.RGBMode1 = RGB_WHITE;
	ModeState = MODEWAIT;//����
	MchInf.bDispDark = 1;
	f_deal_test();
	f_Flash_read();
	MchInf.TmprHouse = 38;
	MchInf.WaterHardState = 4;
	MchInf.TmrLV =1;
    while(1)
    {
		f_MCU_FeedDog();								//ι��
		f_RceDeal(&Uart2_Inf,USART2);
		f_CalTm();
    }
}
//***********************************
void f_CalTm(void)
{
	static unsigned char i = 0;
	static unsigned int  ADValue = 0;


	if(b10msFlag)										//10ms��
	{
		b10msFlag = false;
		f_IncBuzTm();
		f_OutBuz();
		f_AddKeyPressTm();//��������ʱ��
		f_KeyScan();				//����ɨ��
		f_KeyDeal();
		f_Disp();
		f_Deal_PWM();
		f_SendDeal(&Uart2_Inf,USART2);
	}
		
	if(b50msFlag)
	{
		b50msFlag = false;

	}
	
	if(b100msFlag)										//100ms meeted
	{
		b100msFlag = false;
//		f_SendDeal(&Uart1_Inf,USART1);		
	}

	if(b250msFlag)
	{
		b250msFlag = false;
		
	}
	
	if(b500msFlag)				//500ms meeted
	{
		b500msFlag = false;

//		if(bLightFlag==0)
		if((MchInf.KeyState == 0)&&(MchInf.KeyState2 == 0))
		{
			GPIO_SetBits(GPIOC,GPIO_Pin_13);
			bLightFlag = 1;
		}
		else 
		{
			GPIO_ResetBits(GPIOC,GPIO_Pin_13);
			bLightFlag = 0;
		}
	}
	
	if(b1sFlag)										//1S meeted
	{
		b1sFlag = false;
		
		f_deal_test();
		
		if(MchInf.bFunZhengqiOpen)//����ʱ
		{
			if(ModeState != MODEZANTING)//����ʱ��ͣ
				MchInf.timeRunZhengqi++;
			
			if(MchInf.bOpenMusic == 0)//������
			{
				MchInf.blekey |= 0x01;
				MchInf.MusicOn = 1;
				MchInf.bOpenMusic = 1;
			}
			if(MchInf.timeRunZhengqi >= 60)//1min
			{
				MchInf.zhengqijiworktimesum++;//工作时长

				if(MchInf.zhengqijiworktimesum%10 == 0)
				{
					f_Flash_Write();
				}

				MchInf.timeRunZhengqi = 0;
				MchInf.bFunHot = 0;
				if(MchInf.TimeZhengQi == 0)
				{
					MchInf.bFunZhengqiOpen = 0;
				}
				else
				{
						MchInf.timePaiShuiCal = 0;	
						MchInf.TimeZhengQi --;
					
				}
			}
		}

		if(MchInf.bFunChuGouCal)
		{
			MchInf.ntimeRunChuGou++;
			if(MchInf.ntimeRunChuGou >= TestModeInf.TIMERUNCHUGOU)//1hour
			{
				MchInf.timeRmdChuGou --;
				MchInf.ntimeRunChuGou = 0;
				if(MchInf.timeRmdChuGou == 0)
					MchInf.bFunChuGouCal = 0;
			}
		}



		 if(MchInf.bFunChuGou == 0)
		{
			MchInf.nCalTimeAutoSleep++;
			if(MchInf.nCalTimeAutoSleep == (TestModeInf.TIMEAUTOSLEEP+120))
			{
				ModeState = MODESLEEP;
			}			
			if(MchInf.nCalTimeAutoSleep == TestModeInf.TIMEAUTOSLEEP)
			{
				MchInf.RGBMode1 = RGB_CLOSE;
				MchInf.LED2State = 0;
				if(MchInf.MusicOn == 1)
					MchInf.blekey |= 0x01;//��ͣ
			}
		}
	}
}

