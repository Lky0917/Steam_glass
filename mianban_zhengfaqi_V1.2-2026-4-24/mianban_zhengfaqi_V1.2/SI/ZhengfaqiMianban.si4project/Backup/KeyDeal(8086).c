#define VAR_KEYDEAL_GLOBALS
#include "HeadInclude.h"

unsigned NUM_key = 0;
unsigned Send_Num_Key = 0;

KEYINF   KeyInf;


void f_Key_IntoTestMode(void);

//-----------------�����Ӻ���------------------------------------------(4)
void f_Key1Deal_Poweroff(void)
{
    if(nKeyResultInf & PRESSED_7S)
	{
        bKeyUsedFlag = true;


    }
}

void f_Key3Deal_Poweroff(void)
{
    if(nKeyResultInf & PRESSED_7S)
	{
        bKeyUsedFlag = true;


    }
}

void f_Key4Deal_Poweroff(void)
{
    if(nKeyResultInf & PRESSED)
    {
        bKeyUsedFlag = true;
        
        //�ƹ���ʾ����
        f_Beep(NORMAL);



    }
}

void f_Key5Deal_Poweroff(void)
{
    if(nKeyResultInf & PRESSED)
	{
		bKeyUsedFlag = true;


	}
}

void f_Key_1_3_Deal_Poweroff(void)
{
    if(nKeyResultInf & PRESSED_2S)//����2S
	{
		bKeyUsedFlag = true;


    }
}


void f_KeyBackDisp_Poweroff(void)
{
    if(nKeyResultInf & PRESSED)
    {

        bKeyUsedFlag = true;
            
        f_Beep(NORMAL);
    }
}

void f_KeyDeal_Standby(void)
{
	switch(KeyPressName)
	{
        case KEY_COM_PRESS_2://��Ϲ���+��ʱ
            f_Key_1_3_Deal_Poweroff();
            break;
            
        case KEY_SIGNAL_PRESS_1://ģʽ-����1
		    f_Key1Deal_Poweroff();
			break;

        case KEY_SIGNAL_PRESS_2://����
		    f_KeyBackDisp_Poweroff();
			break;

        case KEY_SIGNAL_PRESS_3://��ʱ-����2
		    f_Key3Deal_Poweroff();
			break;
            
        case KEY_SIGNAL_PRESS_4://��ʾ����
		    f_Key4Deal_Poweroff();
			break;
            
		case KEY_SIGNAL_PRESS_5://��Դ
		    f_Key5Deal_Poweroff();
			break;

		default:
			break;
	}

	nKeyResultInf = NO_KEY;
}

//===����==



void f_Key1Deal_Run(void)
{
    
    if(nKeyResultInf & PRESSED_RE)
    {
    if(ModeState == MODERUN)
    	{
        f_Beep(NORMAL);
//        bKeyUsedFlag = true;

		MchInf.TmrLV = 1;//�����¶�level1    36-39��
    	}
    }
    else if(nKeyResultInf & PRESSED_3S)//����1
	{
        bKeyUsedFlag = true;
    }
}


void f_Key2Deal_Run(void)
{
    if(nKeyResultInf & PRESSED_RE)
    {
    if(ModeState == MODERUN)
    	{
        f_Beep(NORMAL);
//        bKeyUsedFlag = true;
		MchInf.TmrLV = 2;//�����¶�level2	  41-44��
    	}
    }
}


void f_Key3Deal_Run(void)//��ʱ
{

    if(nKeyResultInf & PRESSED_RE)
    {
   		if(ModeState == MODERUN)
    	{
    	f_Beep(NORMAL);
//        bKeyUsedFlag = true;
            
		MchInf.TmrLV = 3;//�����¶�level3	  45-48��
    	}
    }
}


void f_Key4Deal_Run(void)
{
    if(nKeyResultInf & PRESSED_RE)
    {
    	f_Beep(NORMAL);
        bKeyUsedFlag = true;

		if((ModeState ==MODEWAIT)&&(MchInf.bDispDark == 1))//����
		{
			MchInf.timeWaitNoKey = 0;
			MchInf.bDispDark = 0;
			return;
		}
		
		if(MchInf.bFunChuGouStart)
		{
			MchInf.ntimeslightZhengfaIcon = 0;
			MchInf.RGBMode = RGB_RED;			
		}
		else if(ModeState == MODERUN)
		{
			ModeState = MODEZANTING;
			MchInf.RGBMode = RGB_CLOSE;
		}
		else if(ModeState == MODESLEEP)
		{
			ModeState = MODEWAIT;
			MchInf.timeWaitNoKey = 0;
			MchInf.bDispDark = 0;
			MchInf.RGBMode1 = RGB_WHITE;
		}
		else if(ModeState == MODEZANTING)
		{
			ModeState = MODERUN; 
			MchInf.RGBMode = RGBModeLast;			
		}
		else
		{	
			ModeState = MODERUN;   
			MchInf.ModeRunState = 0;
			MchInf.RGBMode = RGB_RED;
			MchInf.TmrLV = 1;			
			MchInf.TimeZhengQi = 60;//
			MchInf.bOpenMusic = 0;
			MchInf.nCaltimesAutoChugou = 0;
		}
    }
	else if(nKeyResultInf & PRESSED_600mS)
	{
		bKeyUsedFlag = true;
		if(ModeState == MODERUN)
		{
			f_Beep(NORMAL);
      		MchInf.ModeRunState++;  	
			if(MchInf.ModeRunState > 3)
			{
				MchInf.ModeRunState = 0;
				MchInf.blekey |= 0x80;
			}
			else	
			{
				MchInf.blekey |= 0x40;
			}				
			
			if(MchInf.ModeRunState == 0)
				MchInf.RGBMode = RGB_RED;
			else if(MchInf.ModeRunState == 1)
				MchInf.RGBMode = RGB_YELLOW;
			else if(MchInf.ModeRunState == 2)
				MchInf.RGBMode = RGB_BLUE;
			else if(MchInf.ModeRunState == 3)
				MchInf.RGBMode = RGB_ZISe;

		}
	}
}


void f_Key5Deal_Run(void)
{
	static unsigned char RGB_state;
    if(nKeyResultInf & PRESSED_RE)
    {
        bKeyUsedFlag = true;
			if(MchInf.bFunChuGouSleep)
				return;

		if((ModeState ==MODEWAIT)&&(MchInf.bDispDark == 1))//����
		{
			MchInf.timeWaitNoKey = 0;
			MchInf.bDispDark = 0;
			return;
		}

		if(ModeState == MODERUN)
		{
			f_Beep(NORMAL);

			if(MchInf.RGBMode == RGB_CLOSE)
				MchInf.RGBMode = RGB_ORANGE;
			else
				MchInf.RGBMode = RGB_CLOSE;
		}
		else if(ModeState == MODEWAIT)
		{
			if(MchInf.RGBMode1 != RGB_CLOSE)
				MchInf.RGBMode1 = RGB_CLOSE;
			else
				MchInf.RGBMode1 = RGB_WHITE;
			f_Beep(NORMAL);
		}

    }
	else if(nKeyResultInf & PRESSED_600mS)
	{
		 bKeyUsedFlag = true;
		
		
			if(ModeState == MODERUN)
			{
				f_Beep(NORMAL);
				MchInf.RGBMode1 = RGB_ORANGE;
				switch(MchInf.ModeRunState)
				{
					case 0:
						if(MchInf.RGBMode == RGB_RED)
							MchInf.RGBMode = RGB_FENSE;
						else if(MchInf.RGBMode == RGB_FENSE)
							MchInf.RGBMode = RGB_RED;
						break;
					case 1:
						if(MchInf.RGBMode == RGB_YELLOW)
							MchInf.RGBMode = RGB_ORANGE;
						else if(MchInf.RGBMode == RGB_ORANGE)
							MchInf.RGBMode = RGB_YELLOW;
						break;
					case 2:
						if(MchInf.RGBMode == RGB_BLUE)
							MchInf.RGBMode = RGB_SKYBLUE;
						else if(MchInf.RGBMode == RGB_SKYBLUE)
							MchInf.RGBMode = RGB_BLUE;
						break;
					case 3:
						if(MchInf.RGBMode == RGB_ZISe)
							MchInf.RGBMode = RGB_GREEN;
						else if(MchInf.RGBMode == RGB_GREEN)
							MchInf.RGBMode = RGB_ZISe;
						break;
	
				}

			}
			else if(ModeState == MODEWAIT)
			{
				MchInf.RGBMode1++;
				if(MchInf.RGBMode1 > RGB_WHITE)
					MchInf.RGBMode1 = RGB_ZISe;

			}
	}
}

void f_Key6Deal_Run(void)
{
    if(nKeyResultInf & PRESSED_RE)
    {
        bKeyUsedFlag = true;
			if(MchInf.bFunChuGouSleep)
				return;
		if((ModeState ==MODEWAIT)&&(MchInf.bDispDark == 1))//����
		{
			MchInf.timeWaitNoKey = 0;
			MchInf.bDispDark = 0;
			return;
		}

		if(ModeState != MODESLEEP)
		{
			f_Beep(NORMAL);
			MchInf.LED2State ^= 1;
		}
    }
}
void f_Key7Deal_Run(void)
{
	if(KeyInf.longtimeKey7 < 1000)
		KeyInf.longtimeKey7++;

    if(nKeyResultInf & PRESSED_RE)
    {
			if(MchInf.bFunChuGouSleep)
				return;
		if((ModeState ==MODEWAIT)&&(MchInf.bDispDark == 1))//����
		{
			MchInf.timeWaitNoKey = 0;
			MchInf.bDispDark = 0;
			return;
		}

    	if(KeyInf.longtimeKey7 < 30)
    	{
	        bKeyUsedFlag = true;
			KeyInf.longtimeKey7 = 0;

			if(ModeState != MODESLEEP)
			{
				f_Beep(NORMAL);
				MchInf.blekey |= 0x01;
				MchInf.MusicOn ^= 1;
				if(MchInf.MusicOn == 0)
					MchInf.MusicNext = 0;
			}
    	}

//		else if(KeyInf.longtimeKey7 > 250)
//		{
//			 bKeyUsedFlag = true;
//			 KeyInf.longtimeKey7 = 0;
//			if(ModeState != MODESLEEP)
//			{
//				f_Beep(NORMAL);
//				MchInf.BLEReset = 1;//����ƥ��
//				MchInf.blekey |= 0x04;
//			}
//		}
				else if(KeyInf.longtimeKey7 > 60)
		{
			bKeyUsedFlag = true;
			KeyInf.longtimeKey7 = 0;
			if(ModeState != MODESLEEP)
			{
				f_Beep(NORMAL);
				MchInf.MusicNext = 1;
				MchInf.blekey |= 0x02;
			}
		}
   }
}

void f_Key8Deal_Run(void)
{
    if(nKeyResultInf & PRESSED_RE)
    {
		 bKeyUsedFlag = true;
		if(MchInf.bFunChuGouSleep)
				return;
		 if((ModeState ==MODEWAIT)&&(MchInf.bDispDark == 1))//����
		{
			MchInf.timeWaitNoKey = 0;
			MchInf.bDispDark = 0;
			return;
		}
		 
		 KeyInf.longtimeKey8 = 0;
		if((ModeState != MODESLEEP))
		{
			f_Beep(NORMAL);
			if(MchInf.MusicSound < 100)
				MchInf.MusicSound++;

			MchInf.blekey |= 0x10;
		}
    }
	else 
	{
		if(KeyInf.longtimeKey8 < 1000)
			KeyInf.longtimeKey8++;

		if(KeyInf.longtimeKey8 >= 300)
		{
			KeyInf.longtimeKey8 = 250;
			if((ModeState != MODESLEEP))
			{
				if(MchInf.MusicSound < 100)
					MchInf.MusicSound++;
		
				MchInf.blekey |= 0x10;
			}
		}
	}
}


void f_Key9Deal_Run(void)//��ʱ
{

    if(nKeyResultInf & PRESSED_RE)
    {
		 bKeyUsedFlag = true;
		if(MchInf.bFunChuGouSleep)
				return;
		 if((ModeState ==MODEWAIT)&&(MchInf.bDispDark == 1))//����
		{
			MchInf.timeWaitNoKey = 0;
			MchInf.bDispDark = 0;
			return;
		}
		 
			KeyInf.longtimeKey9 = 0;
		if((ModeState != MODESLEEP))
		{
			f_Beep(NORMAL);
			if(MchInf.MusicSound > 0)
				MchInf.MusicSound--;
			
			MchInf.blekey |= 0x20;
		}
    }
	else 
	{
		if(KeyInf.longtimeKey9 < 1000)
			KeyInf.longtimeKey9++;

		if(KeyInf.longtimeKey9 >= 300)
		{
			KeyInf.longtimeKey9 = 250;
			if((ModeState != MODESLEEP))
			{
				if(MchInf.MusicSound > 0)
					MchInf.MusicSound--;
				MchInf.blekey |= 0x20;
			}
		}
	}

}


void f_Key16Deal_Run(void)
{
    if(nKeyResultInf & PRESSED_RE)
    {
        bKeyUsedFlag = true;
			if((MchInf.bFunAlamChuGou)||(MchInf.bFunAlamChuGouAgain))
			{
				MchInf.bFunAlamChuGou = 0;
				MchInf.bFunAlamChuGouAgain = 0;
				MchInf.ntimeslighChugouIcon = 0;

			}
    }
}


void f_Key15Deal_Run(void)
{
    if(nKeyResultInf & PRESSED_RE)
    {
      bKeyUsedFlag = true;
			f_Beep(NORMAL);
		if(MchInf.bFunSetWtHard)
		{
			MchInf.WaterHardState = 1;
			MchInf.timeNoSetWtHard = 0;
		}

    }
}

void f_Key14Deal_Run(void)
{
    if(nKeyResultInf & PRESSED_RE)
    {
			f_Beep(NORMAL);
        bKeyUsedFlag = true;
		if(MchInf.bFunSetWtHard)
		{
			MchInf.WaterHardState = 2;
			MchInf.timeNoSetWtHard = 0;
		}


    }
}
void f_Key13Deal_Run(void)
{
    if(nKeyResultInf & PRESSED_RE)
    {
        bKeyUsedFlag = true;
			f_Beep(NORMAL);
		if(MchInf.bFunSetWtHard)
		{
			MchInf.WaterHardState = 3;
			MchInf.timeNoSetWtHard = 0;
		}

    }
}
void f_Key12Deal_Run(void)
{
    
    if(nKeyResultInf & PRESSED_RE)
    {
        f_Beep(NORMAL);
        bKeyUsedFlag = true;
		if(MchInf.bFunSetWtHard)
		{
			MchInf.WaterHardState = 4;
			MchInf.timeNoSetWtHard = 0;
		}

    }
    else if(nKeyResultInf & PRESSED_3S)//����1
	{
        bKeyUsedFlag = true;
    }
}


void f_Key11Deal_Run(void)
{
    if(nKeyResultInf & PRESSED_RE)
    {
        f_Beep(NORMAL);
        bKeyUsedFlag = true;
		if(MchInf.bFunChuGou)
		{
			if((MchInf.bPumpChugou)&&(MchInf.bChugouYeWei == 0))//�г�����
			{
			}
			else
			{
			MchInf.bFunChuGouStart = 1;
			MchInf.timeRmdChuGou = 4;
			MchInf.RGBMode = RGB_RED;
			MchInf.ntimeslightZhengfaIcon = 100;
			}
			
		}

    }
}


void f_Key10Deal_Run(void)//��ʱ
{

    if(nKeyResultInf & PRESSED_RE)
    {
        bKeyUsedFlag = true;
				if(MchInf.bFunChuGouSleep)
				{
					MchInf.nCalTimeChuGouSleep = 0;
					MchInf.bFunChuGouSleep = 0;
					MchInf.bDispDark = 1;
					return;
				}
		
        MchInf.RGBMode1 = RGB_WHITE;    
		ModeState = MODEWAIT;
		MchInf.bDispDark = 1;
		MchInf.timeWaitNoKey = 0;
    }
	else if(nKeyResultInf & PRESSED_3S)
	{
		bKeyUsedFlag = true;
		ModeState = MODESLEEP;
		MchInf.bFunPaiShui = 1;
		MchInf.LED2State = 0;
		MchInf.MusicOn = 0;
		MchInf.bFunZhengqiOpen = 0;
		

	}
}





void f_Key_1_2_Deal_Run(void)
{
    if(nKeyResultInf & PRESSED_3S)//����3S
	{
		bKeyUsedFlag = true;

     f_Beep(NORMAL);
		if(MchInf.bFunChuGou)
		{
				MchInf.bFunChuGou = 0;
				MchInf.bFunSetWtHard = 1;

		}
		else
		{
			MchInf.bFunChuGou = 1;
			MchInf.bFunSetWtHard = 0;

		}
//			MchInf.WaterHardState = 4;
			MchInf.timeNostartChuGou = 0;
			MchInf.ntimeslight = 0;
			MchInf.timeRmdChuGou = 4;
	}
}

void f_Key_5_7_Deal_Run(void)
{
    if(nKeyResultInf & PRESSED_3S)//����3S
	{
		bKeyUsedFlag = true;

     	f_Beep(NORMAL);
		//if(MchInf.bFunWeixiu)
		{
			if(MchInf.bFunWeixiuDisp)
			{
				MchInf.bFunWeixiuDisp = 0;
			}
			else
			{
				MchInf.bFunWeixiuDisp = 1;
			}
		}

	}
}
void f_Key_4_5_7Deal_Run(void)
{
	if(nKeyResultInf & PRESSED_3S)//����3S
	{
		bKeyUsedFlag = true;

     f_Beep(NORMAL);
		if(MchInf.bFunWeixiu)
		{
			MchInf.bFunWeixiu = 0;
		}
		else
		{
			MchInf.bFunWeixiu = 1;
			MchInf.ntimeslightAlamChugouAgain = 0;
			MchInf.calAlamChugouAgain = 0;
		}

	}
}



void f_KeyDeal_Run(void)
{
	switch(KeyPressName)
	{
		case  KEY_COM_PRESS_3:
			f_Key_4_5_7Deal_Run();
			break;
        case KEY_COM_PRESS_1://����о
			f_Key_1_2_Deal_Run();
			break;
		 case KEY_COM_PRESS_2://����о
			f_Key_5_7_Deal_Run();
			break;
        
		case KEY_SIGNAL_PRESS_1://����
			f_Key1Deal_Run();
			break;

		case KEY_SIGNAL_PRESS_2://����
			f_Key2Deal_Run();
			break;

		case KEY_SIGNAL_PRESS_3://��ʱ
			f_Key3Deal_Run();
			break;

		case KEY_SIGNAL_PRESS_4://ָʾ��
			f_Key4Deal_Run();
			break;

		case KEY_SIGNAL_PRESS_5://�ػ�
			f_Key5Deal_Run();
			break;
		case KEY_SIGNAL_PRESS_6:
			f_Key6Deal_Run();
			break;

		case KEY_SIGNAL_PRESS_7:
			f_Key7Deal_Run();
			break;

		case KEY_SIGNAL_PRESS_8:
			f_Key8Deal_Run();
			break;

		case KEY_SIGNAL_PRESS_9:
			f_Key9Deal_Run();
			break;

		case KEY_SIGNAL_PRESS_10:
			f_Key10Deal_Run();
			break;
		case KEY_SIGNAL_PRESS_11:
			f_Key11Deal_Run();
			break;

		case KEY_SIGNAL_PRESS_12:
			f_Key12Deal_Run();
			break;

		case KEY_SIGNAL_PRESS_13:
			f_Key13Deal_Run();
			break;

		case KEY_SIGNAL_PRESS_14:
			f_Key14Deal_Run();
			break;

		case KEY_SIGNAL_PRESS_15:
			f_Key15Deal_Run();
			break;
		case KEY_SIGNAL_PRESS_16:
			f_Key16Deal_Run();
			break;
		default:
			break;
	}

    nKeyResultInf = NO_KEY;
}




//-----�Լ촦��---------
/*
void f_Key1Deal_SC(BIG_STRUCT *pFuctionData)
{
    if(nKeyResultInf & PRESSED)
    {
        bKeyUsedFlag = true;

        if(pFuctionData->selfCheckInf.bKey_1_P == false \
        && pFuctionData->selfCheckInf.ucSelfCheckStep == CHECK_STEP_KEY)
        {
            f_Beep(NORMAL);
            pFuctionData->selfCheckInf.bKey_1_P = true;  
            pFuctionData->selfCheckInf.keyTuchNumb ++;
        }
        else if(pFuctionData->selfCheckInf.ucSelfCheckStep == CHECK_STEP_VERSION)//����wifi����
        {
            f_Beep(NORMAL);
            pFuctionData->selfCheckInf.ucSelfCheckStep = CHECK_STEP_WIFI;
            pFuctionData->selfCheckInf.ucCheckCnt = 0;

            pFuctionData->selfCheckInf.bWifiSendCMD = false;
        }
    }
}

void f_Key2Deal_SC(BIG_STRUCT *pFuctionData)
{
    if(nKeyResultInf & PRESSED)
    {
        bKeyUsedFlag = true;

        //���ٽ�����ɫ��⣬������ȫ��
        if(pFuctionData->selfCheckInf.ucSelfCheckStep == CHECK_STEP_VERSION)
        {
            f_Beep(NORMAL);
            pFuctionData->selfCheckInf.ucSelfCheckStep = CHECK_STEP_LED_R;
            pFuctionData->selfCheckInf.bOnlyTest_LED = true;//�����led
            pFuctionData->selfCheckInf.bShowAll = true;//����ȫ��
            pFuctionData->selfCheckInf.bCheckLed = true;//�������led
        }
        else if(pFuctionData->selfCheckInf.bKey_2_P == false \
        && pFuctionData->selfCheckInf.ucSelfCheckStep == CHECK_STEP_KEY)
        {
            f_Beep(NORMAL);
            pFuctionData->selfCheckInf.bKey_2_P = true;  
            pFuctionData->selfCheckInf.keyTuchNumb ++;
        }
    }
}

void f_Key3Deal_SC(BIG_STRUCT *pFuctionData)
{
    if(nKeyResultInf & PRESSED)
    {
        bKeyUsedFlag = true;

        if(pFuctionData->selfCheckInf.bKey_3_P == false \
        && pFuctionData->selfCheckInf.ucSelfCheckStep == CHECK_STEP_KEY)
        {
            f_Beep(NORMAL);
            pFuctionData->selfCheckInf.bKey_3_P = true;  
            pFuctionData->selfCheckInf.keyTuchNumb ++;
        }
    }
}

void f_Key4Deal_SC(BIG_STRUCT *pFuctionData)
{
    if(nKeyResultInf & PRESSED)
    {
        bKeyUsedFlag = true;

        if(pFuctionData->selfCheckInf.ucSelfCheckStep == CHECK_STEP_VERSION)//���ٽ�����ɫ���
        {
            f_Beep(NORMAL);
            pFuctionData->selfCheckInf.ucSelfCheckStep = CHECK_STEP_LED_R;
            pFuctionData->selfCheckInf.bOnlyTest_LED = true;//�����led
        }
        else if(pFuctionData->selfCheckInf.bKey_4_P == false \
        && pFuctionData->selfCheckInf.ucSelfCheckStep == CHECK_STEP_KEY)
        {
            f_Beep(NORMAL);
            pFuctionData->selfCheckInf.bKey_4_P = true;  
            pFuctionData->selfCheckInf.keyTuchNumb ++;
        }
        else if(pFuctionData->selfCheckInf.ucSelfCheckStep == CHECK_STEP_LOAD)
        {
            f_Beep(NORMAL);
            //������
            pFuctionData->sysAssistFlag.bAnionSw ^= true;

            if(pFuctionData->selfCheckInf.K4_TouchCnt <= 200)
                pFuctionData->selfCheckInf.K4_TouchCnt ++;
        }
    }
}

void f_Key5Deal_SC(BIG_STRUCT *pFuctionData)//��Դ��
{
    if(nKeyResultInf & PRESSED)
    {
        bKeyUsedFlag = true;
        

        if(pFuctionData->selfCheckInf.ucSelfCheckStep == CHECK_STEP_VERSION)
        {
            f_Beep(NORMAL);
            pFuctionData->selfCheckInf.ucSelfCheckStep ++;
            pFuctionData->selfCheckInf.ucCheckCnt = 0;
        }
        else if(pFuctionData->selfCheckInf.ucSelfCheckStep == CHECK_STEP_NUMB)
        {
            if(pFuctionData->selfCheckInf.ucCheckCnt >= 100)
            {
                f_Beep(NORMAL);
                pFuctionData->selfCheckInf.ucSelfCheckStep ++;
                pFuctionData->selfCheckInf.ucCheckCnt = 0;
            }
        }
        else if(pFuctionData->selfCheckInf.ucSelfCheckStep == CHECK_STEP_ICON_LED)
        {
            if(pFuctionData->selfCheckInf.bIcon_OK)//ͼ�������
            {
                f_Beep(NORMAL);
                pFuctionData->selfCheckInf.ucSelfCheckStep ++;
                pFuctionData->selfCheckInf.ucCheckCnt = 0;
                
                pFuctionData->selfCheckInf.keyTuchNumb = 1;
                pFuctionData->selfCheckInf.bKey_5_P = true;
            }
        }
        else if(pFuctionData->selfCheckInf.ucSelfCheckStep == CHECK_STEP_KEY)//��ⰴ��
        {
            if(pFuctionData->selfCheckInf.keyTuchNumb == 5)//���а�������
            {
                f_Beep(NORMAL);
                pFuctionData->selfCheckInf.ucSelfCheckStep ++;
                pFuctionData->selfCheckInf.ucCheckCnt = 0;
            }
        }
        else if(pFuctionData->selfCheckInf.ucSelfCheckStep <= CHECK_STEP_LED_B)//��ʾ������
        {
            f_Beep(NORMAL);
            pFuctionData->selfCheckInf.ucSelfCheckStep ++;
            pFuctionData->selfCheckInf.ucCheckCnt = 0;
            pFuctionData->selfCheckInf.K4_TouchCnt = 0;

            if(pFuctionData->selfCheckInf.bOnlyTest_LED \
            && pFuctionData->selfCheckInf.ucSelfCheckStep == CHECK_STEP_LOAD)//�����led
            {
                pFuctionData->selfCheckInf.ucSelfCheckStep = CHECK_STEP_LED_R;
            }

            if(pFuctionData->selfCheckInf.bCheckLed)
            {
                pFuctionData->selfCheckInf.bShowAll ^= true;
            }
        }
        else if(pFuctionData->selfCheckInf.ucSelfCheckStep == CHECK_STEP_LOAD)
        {
            if(pFuctionData->selfCheckInf.ucCheckCnt >= 10 \
            && pFuctionData->fanSysInf.bFanErr == false \
            && pFuctionData->selfCheckInf.K4_TouchCnt >= 1)//1S�����ҷ���޹���,�Ұ���������
            {
                f_Beep(NORMAL);
                pFuctionData->selfCheckInf.ucSelfCheckStep ++;
                pFuctionData->selfCheckInf.ucCheckCnt = 0;    
            }
        }
    }  
}


void f_KeyDeal_SC(BIG_STRUCT *pFuctionData)
{
	switch(KeyPressName)
	{
		case KEY_SIGNAL_PRESS_1://����
			f_Key1Deal_SC(pFuctionData);
			break;

		case KEY_SIGNAL_PRESS_2://����
			f_Key2Deal_SC(pFuctionData);
			break;

		case KEY_SIGNAL_PRESS_3://��ʱ
			f_Key3Deal_SC(pFuctionData);
			break;

		case KEY_SIGNAL_PRESS_4://ָʾ��
			f_Key4Deal_SC(pFuctionData);
			break;

		case KEY_SIGNAL_PRESS_5://�ػ�
			f_Key5Deal_SC(pFuctionData);
			break;

		default:
			break;
	}

    nKeyResultInf = NO_KEY;
}


void f_KeyDeal(void)
{
	
	switch(pFuctionData->SystemCurState)
	{
		case PowerOff_STATE:
			f_KeyDeal_Standby();
			break;
			
		case RUNNING_STATE:
			f_KeyDeal_Run();
			break;

		case SELFCHECK_STATE://�Լ�
		    f_KeyDeal_SC();
			break;
			
		default:
			break;	
	}
}*/

void f_KeyDeal(void)
{
	f_KeyDeal_Run();
}
