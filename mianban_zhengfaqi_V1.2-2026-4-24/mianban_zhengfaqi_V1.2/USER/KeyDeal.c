#define VAR_KEYDEAL_GLOBALS
#include "HeadInclude.h"

unsigned NUM_key = 0;
unsigned Send_Num_Key = 0;

KEYINF KeyInf;

static void f_KeyTouchVibrateFeedback(void)
{
	if (!(nKeyResultInf & PRESSED_600mS))
		return;

	switch (KeyPressName)
	{
	case KEY_SIGNAL_PRESS_4:
		if (ModeState != MODESLEEP)
			MchInf.bflagzhendong3 = 1;
		break;

	case KEY_SIGNAL_PRESS_5:
		if ((ModeState != MODESLEEP) && (MchInf.bFunChuGouSleep == 0))
			MchInf.bflagzhendong1 = 1;
		break;

	case KEY_SIGNAL_PRESS_7:
		if ((ModeState != MODESLEEP) && (MchInf.bFunChuGouSleep == 0))
			MchInf.bflagzhendong2 = 1;
		break;

	default:
		break;
	}
}

void f_Key_IntoTestMode(void);

//-----------------�����Ӻ���------------------------------------------(4)
void f_Key1Deal_Poweroff(void)
{
	if (nKeyResultInf & PRESSED_7S)
	{
		bKeyUsedFlag = true;
	}
}

void f_Key3Deal_Poweroff(void)
{
	if (nKeyResultInf & PRESSED_7S)
	{
		bKeyUsedFlag = true;
	}
}

void f_Key4Deal_Poweroff(void)
{
	if (nKeyResultInf & PRESSED)
	{
		bKeyUsedFlag = true;

		// �ƹ���ʾ����
		f_Beep(NORMAL);
	}
}

void f_Key5Deal_Poweroff(void)
{
	if (nKeyResultInf & PRESSED)
	{
		bKeyUsedFlag = true;
	}
}

void f_Key_1_3_Deal_Poweroff(void)
{
	if (nKeyResultInf & PRESSED_2S) // ����2S
	{
		bKeyUsedFlag = true;
	}
}

void f_KeyBackDisp_Poweroff(void)
{
	if (nKeyResultInf & PRESSED)
	{

		bKeyUsedFlag = true;

		f_Beep(NORMAL);
	}
}

void f_KeyDeal_Standby(void)
{
	switch (KeyPressName)
	{
	case KEY_COM_PRESS_2: // ��Ϲ���?��ʱ
		f_Key_1_3_Deal_Poweroff();
		break;

	case KEY_SIGNAL_PRESS_1: // ģʽ-����1
		f_Key1Deal_Poweroff();
		break;

	case KEY_SIGNAL_PRESS_2: // ����
		f_KeyBackDisp_Poweroff();
		break;

	case KEY_SIGNAL_PRESS_3: // ��ʱ-����2
		f_Key3Deal_Poweroff();
		break;

	case KEY_SIGNAL_PRESS_4: // ��ʾ����
		f_Key4Deal_Poweroff();
		break;

	case KEY_SIGNAL_PRESS_5: // ��Դ
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

	if (nKeyResultInf & PRESSED_RE)
	{

		if (ModeState == MODESLEEP)
			return;

		if (ModeState == MODERUN)
		{
			f_Beep(NORMAL);

			bKeyUsedFlag = true;
			MchInf.bFlagWriteFlash = 1;
			MchInf.TmrLV = 1; // �����¶�level1    36-39��
		}
	}
	else if (nKeyResultInf & PRESSED_3S) // ����1
	{
		bKeyUsedFlag = true;
	}
}

void f_Key2Deal_Run(void)
{
	if (nKeyResultInf & PRESSED_RE)
	{
		if (ModeState == MODESLEEP)
			return;
		if (ModeState == MODERUN)
		{
			f_Beep(NORMAL);
			bKeyUsedFlag = true;
			MchInf.bFlagWriteFlash = 1;
			MchInf.TmrLV = 2; // �����¶�level2	  41-44��
		}
	}
}

void f_Key3Deal_Run(void) // ��ʱ
{

	if (nKeyResultInf & PRESSED_RE)
	{
		if (ModeState == MODESLEEP)
			return;
		if (ModeState == MODERUN)
		{
			f_Beep(NORMAL);
			bKeyUsedFlag = true;
			MchInf.bFlagWriteFlash = 1;

			MchInf.TmrLV = 3; // �����¶�level3	  45-48��
		}
	}
}

void f_Deal_B1fun(void)
{
	ModeState = MODERUN;
	MchInf.ModeRunState = 0;
	MchInf.RGBMode = RGB_WHITE;
	MchInf.TmrLV = 1;
	MchInf.TimeZhengQi = 60; //
	MchInf.bFunZhengfa = 1;
	MchInf.bOpenMusic = 0;
	MchInf.nCaltimesAutoChugou = 0;
	MchInf.RGBMode1 = RGB_ZISe;
	MchInf.timePaiShuiCal = 0;
	RGBModeLast = MchInf.RGBMode1;
	MchInf.bFunChuGouEver = 0;
	MchInf.bFunAlamChuGou = 0;
	MchInf.bFunAlamChuGouAgain = 0;
	MchInf.bFunPaiShuiMust = 0;
	MchInf.bFunPaiShui = 0;
}

void f_Key4Deal_Run(void)
{
	static unsigned int longkey4 = 0;
	if (longkey4 < 800)
		longkey4++;

	if (nKeyResultInf & PRESSED_RE)
	{

		if (longkey4 < 30)
		{
			longkey4 = 0;
			bKeyUsedFlag = true;
			if (ModeState == MODESLEEP)
				return;
			f_Beep(NORMAL);
			//   bKeyUsedFlag = true;

			MchInf.bflagzhendong3 = 1;

			if (((ModeState == MODEWAIT) && (MchInf.bDispDark == 1)) || (MchInf.bManuStartChugou)) // ����
			{
				MchInf.timeWaitNoKey = 0;
				MchInf.bDispDark = 0;

				//					return;
			}

			// if(((MchInf.bFunChuGouStart)&&(MchInf.nCaltimesAutoChugou< 2400))||MchInf.bFunChuGouReady)
			if (MchInf.bFunChuGouReady)
			{
				MchInf.ntimeslightZhengfaIcon = 0;

				MchInf.RGBMode = RGB_RED;
			}
			else if (MchInf.bFunAlamChuGou || MchInf.bFunAlamChuGouAgain)
			{
				f_Deal_B1fun();
			}
			else if (ModeState == MODERUN)
			{
				ModeState = MODEZANTING;
				MchInf.RGBMode = RGB_CLOSE;
			}
			else if (ModeState == MODESLEEP)
			{
				ModeState = MODEWAIT;
				MchInf.timeWaitNoKey = 0;
				//					MchInf.bDispDark = 0;
				MchInf.RGBMode1 = RGB_CLOSE;
				if (MchInf.bFunAlamChuGou)
				{
					MchInf.ntimeslighChugouIcon = 0;
					MchInf.nCalTimeChugouIcon = 0;
				}
			}
			else if (ModeState == MODEZANTING)
			{
				ModeState = MODERUN;

				if (MchInf.ModeRunState == 0)
					MchInf.RGBMode = RGB_WHITE;
				else if (MchInf.ModeRunState == 1)
					MchInf.RGBMode = RGB_YELLOW;
				else if (MchInf.ModeRunState == 2)
					MchInf.RGBMode = RGB_BLUE;
				else if (MchInf.ModeRunState == 3)
					MchInf.RGBMode = RGB_ZISe;
			}
			else
			{
				f_Deal_B1fun();
				//					ModeState = MODERUN;
				//					MchInf.ModeRunState = 0;
				//					MchInf.RGBMode = RGB_WHITE;
				//					MchInf.TmrLV = 1;
				//					MchInf.TimeZhengQi = 60;//
				//					MchInf.bFunZhengfa = 1;
				//					MchInf.bOpenMusic = 0;
				//					MchInf.nCaltimesAutoChugou = 0;
				//					MchInf.RGBMode1 = RGB_ZISe;
				//					MchInf.timePaiShuiCal = 0;
				//					RGBModeLast = MchInf.RGBMode1;
				//					MchInf.bFunChuGouEver = 0;
				//					MchInf.bFunAlamChuGou = 0;
				//					MchInf.bFunAlamChuGouAgain = 0;
				//					MchInf.bFunPaiShuiMust =0;
				//					MchInf.bFunPaiShui=0;
			}
		}
		else if (longkey4 >= 60)
		{
			bKeyUsedFlag = true;
			longkey4 = 0;
			if (ModeState == MODERUN)
			{
				MchInf.bflagzhendong3 = 1;
				f_Beep(NORMAL);
				MchInf.ModeRunState++;
				if (MchInf.ModeRunState > 3)
				{
					MchInf.ModeRunState = 0;
					MchInf.MusicOn = 0;
					MchInf.blekey |= 0x80; // 改动�?x80�?x08
										   // MchInf.blekey |= 0x08;
				}
				else
				{
					if (MchInf.ModeRunState == 1)
						MchInf.blekey |= 0x200;
					else if (MchInf.ModeRunState == 2)
						MchInf.blekey |= 0x400;
					else if (MchInf.ModeRunState == 3)
						MchInf.blekey |= 0x800;
					MchInf.MusicOn = 1;
				}

				if (MchInf.ModeRunState == 0)
					MchInf.RGBMode = RGB_WHITE;
				else if (MchInf.ModeRunState == 1)
					MchInf.RGBMode = RGB_YELLOW;
				else if (MchInf.ModeRunState == 2)
					MchInf.RGBMode = RGB_BLUE;
				else if (MchInf.ModeRunState == 3)
					MchInf.RGBMode = RGB_ZISe;

				if (MchInf.RGBMode1 != RGB_CLOSE)
				{
					if (MchInf.ModeRunState == 0)
						MchInf.RGBMode1 = RGB_ZISe;
					else
						MchInf.RGBMode1 = MchInf.RGBMode;
				}

				RGBModeLast = MchInf.RGBMode1;
			}
		}
		else
			longkey4 = 0;
	}
	//	else
	//	{
	//		longkey4++;
	//		//if(nKeyResultInf & PRESSED_600mS)
	//		if((longkey4>=60)
	//		{
	//			bKeyUsedFlag = true;
	//			if(ModeState == MODERUN)
	//			{
	//				f_Beep(NORMAL);
	//						MchInf.ModeRunState++;
	//				if(MchInf.ModeRunState > 3)
	//				{
	//					MchInf.ModeRunState = 0;
	//					MchInf.blekey |= 0x80;
	//				}
	//				else
	//				{
	//					MchInf.blekey |= 0x40;
	//				}
	//
	//				if(MchInf.ModeRunState == 0)
	//					MchInf.RGBMode = RGB_RED;
	//				else if(MchInf.ModeRunState == 1)
	//					MchInf.RGBMode = RGB_YELLOW;
	//				else if(MchInf.ModeRunState == 2)
	//					MchInf.RGBMode = RGB_BLUE;
	//				else if(MchInf.ModeRunState == 3)
	//					MchInf.RGBMode = RGB_ZISe;
	//
	//				//if(MchInf.RGBMode1 != RGB_CLOSE)
	//					MchInf.RGBMode1 = MchInf.RGBMode;

	//			}
	//		}
	//	}
	else if (nKeyResultInf & PRESSED_7S)
	{

		bKeyUsedFlag = true;
		f_Beep(NORMAL);
		MchInf.bFunPaiShuiMust = 1;
	}
}

void f_Key5Deal_Run(void)
{
	static unsigned char RGB_state;
	if (nKeyResultInf & PRESSED_RE)
	{
		bKeyUsedFlag = true;
		if (MchInf.bFunChuGouSleep)
			return;
		if (ModeState == MODESLEEP)
			return;
		//		MchInf.bflagzhendong1 = 1;
		if ((ModeState == MODEWAIT) && (MchInf.bDispDark == 1)) // ����
		{
			MchInf.timeWaitNoKey = 0;
			MchInf.bDispDark = 0;
			//			return;
		}

		//		if(ModeState == MODERUN)
		//		{
		//			f_Beep(NORMAL);

		//			if(MchInf.RGBMode == RGB_CLOSE)
		//			{
		//				MchInf.RGBMode = RGB_ORANGE;
		//				MchInf.ModeRunState = 1;
		//			}
		//			else
		//				MchInf.RGBMode = RGB_CLOSE;
		//		}
		//		else //
		if ((ModeState == MODEWAIT) || (ModeState == MODECHUGOU))
		{
			if (MchInf.RGBMode1 != RGB_CLOSE)
				MchInf.RGBMode1 = RGB_CLOSE;
			else
				MchInf.RGBMode1 = RGB_WHITE;
		}
		else if ((ModeState == MODERUN) || (ModeState == MODEZANTING))
		{
			if (MchInf.RGBMode1 == RGB_CLOSE)
			{
				if (MchInf.ModeRunState == 0)
					MchInf.RGBMode1 = RGB_ZISe;
				else if (MchInf.ModeRunState == 1)
					MchInf.RGBMode1 = RGB_YELLOW;
				else if (MchInf.ModeRunState == 2)
					MchInf.RGBMode1 = RGB_BLUE;
				else if (MchInf.ModeRunState == 3)
					MchInf.RGBMode1 = RGB_ZISe;
			}
			else
				MchInf.RGBMode1 = RGB_CLOSE;
		}
		f_Beep(NORMAL);
		MchInf.bflagzhendong1 = 1;
	}

	else if (nKeyResultInf & PRESSED_600mS)
	{
		bKeyUsedFlag = true;
		MchInf.bflagzhendong1 = 1;

		if ((ModeState == MODERUN) || (ModeState == MODEZANTING))
		{
			f_Beep(NORMAL);

			switch (MchInf.ModeRunState)
			{
			case 0:
				if (MchInf.RGBMode1 > RGB_YELLOW)
					MchInf.RGBMode1--;
				else
					MchInf.RGBMode1 = RGB_GREEN;
				break;
			case 1:
				if (MchInf.RGBMode1 == RGB_YELLOW)
					MchInf.RGBMode1 = RGB_ORANGE;
				else
					MchInf.RGBMode1 = RGB_YELLOW;
				break;
			case 2:
				if (MchInf.RGBMode1 == RGB_BLUE)
					MchInf.RGBMode1 = RGB_SKYBLUE;
				else
					MchInf.RGBMode1 = RGB_BLUE;
				break;
			case 3:
				if (MchInf.RGBMode1 == RGB_ZISe)
					MchInf.RGBMode1 = RGB_GREEN;
				else
					MchInf.RGBMode1 = RGB_ZISe;
				break;
			}
			RGBModeLast = MchInf.RGBMode1;
		}

		else if (ModeState != MODESLEEP)
		{
			MchInf.RGBMode1++;
			if (MchInf.RGBMode1 > RGB_GREEN)
				MchInf.RGBMode1 = RGB_WHITE;
		}
	}
}

void f_Key6Deal_Run(void)
{
	if (nKeyResultInf & PRESSED_RE)
	{
		bKeyUsedFlag = true;
		if (ModeState == MODESLEEP)
			return;
		if (MchInf.bFunChuGouSleep)
			return;
		if ((ModeState == MODEWAIT) && (MchInf.bDispDark == 1)) // ����
		{
			MchInf.timeWaitNoKey = 0;
			MchInf.bDispDark = 0;
			//			return;
		}

		if (ModeState != MODESLEEP)
		{
			f_Beep(NORMAL);
			MchInf.LED2State ^= 1;
		}
	}
}
void f_Key7Deal_Run(void)
{

	if (KeyInf.longtimeKey7 < 1000)
	{
		KeyInf.longtimeKey7++;
		//		if(KeyInf.longtimeKey7 == 3)
		//			MchInf.bflagzhendong2 = 1;
	}

	if (nKeyResultInf & PRESSED_RE)
	{
		if (ModeState == MODESLEEP)
			return;
		if (MchInf.bFunChuGouSleep)
			return;
		if ((ModeState == MODEWAIT) && (MchInf.bDispDark == 1)) // ����
		{
			MchInf.timeWaitNoKey = 0;
			MchInf.bDispDark = 0;
			//				return;
		}
		if ((KeyInf.longtimeKey7 > 700) && (KeyInf.longtimeKey7 < 1000))
		{
			// bKeyUsedFlag = true;
			KeyInf.longtimeKey7 = 0;
			if (ModeState != MODESLEEP)
			{
				f_Beep(NORMAL);
				MchInf.bflagzhendong2 = 1;
				MchInf.blekey |= 0x08;
			}
		}
		else if ((KeyInf.longtimeKey7 > 250) && (KeyInf.longtimeKey7 < 400)) // �������?
		{
			// bKeyUsedFlag = true;
			KeyInf.longtimeKey7 = 0;

			if (ModeState != MODESLEEP)
			{
				f_Beep(NORMAL);
				//					MchInf.bflagzhendong2 = 1;
				MchInf.BLErepair = 1;
				MchInf.BlePairTime = 0;
				MchInf.nCallightblepair = 0;
				MchInf.bflagBleConnState = 0;
				MchInf.blekey |= 0x04;
			}
		}
		else if ((KeyInf.longtimeKey7 > 60))
		{
			// bKeyUsedFlag = true;
			KeyInf.longtimeKey7 = 0;

			if ((ModeState != MODESLEEP))
			{
				if (((ModeState == MODERUN) || (ModeState == MODEZANTING)) && (MchInf.ModeRunState != 0)) // ���и�
					return;

				f_Beep(NORMAL);
				//					MchInf.MusicNext = 1;
				MchInf.blekey |= 0x02;
				//					MchInf.bflagzhendong2 = 1;
			}
		}
		else if (KeyInf.longtimeKey7 < 60)
		{
			bKeyUsedFlag = true;
			KeyInf.longtimeKey7 = 0;
			MchInf.bflagzhendong2 = 1;
			if (ModeState != MODESLEEP)
			{
				f_Beep(NORMAL);

				MchInf.blekey |= 0x01; // send play/pause command; MusicOn follows control-board status
			}
		}
		// else if (KeyInf.longtimeKey7 < 30)
		// {
		// 	bKeyUsedFlag = true;
		// 	KeyInf.longtimeKey7 = 0;
		// 	MchInf.bflagzhendong2 = 1;
		// 	if (ModeState != MODESLEEP)
		// 	{

		// 		f_Beep(NORMAL);
		// 		MchInf.blekey |= 0x01;
		// 		// MchInf.MusicOn ^= 1; // 本地状态翻转，灯立即响�?

		// 		MchInf.MusicOn = 0; // TF ������

		// 		if (MchInf.bflagBleConnState == 1) // ��������
		// 			if (MchInf.MusicOn)
		// 				MchInf.MusicOn = 0;
		// 			else
		// 				MchInf.MusicOn = 1;

		// 		//					if(MchInf.MusicOn == 0)
		// 		//						MchInf.MusicNext = 0;
		// 	}
		// }
		// 	else
		// 		KeyInf.longtimeKey7 = 0;

		// 	//		else if(KeyInf.longtimeKey7 > 250)
		// 	//		{
		// 	//			 bKeyUsedFlag = true;
		// 	//			 KeyInf.longtimeKey7 = 0;
		// 	//			if(ModeState != MODESLEEP)
		// 	//			{
		// 	//				f_Beep(NORMAL);
		// 	//				MchInf.BLEReset = 1;//����ƥ��
		// 	//				MchInf.blekey |= 0x04;
		// 	//			}
		// 	//		}
		// }
		// else
		// {
		// 	//			KeyInf.longtimeKey7 = 0;
	}
}

void f_Key8Deal_Run(void)
{
	if (nKeyResultInf & PRESSED_RE)
	{
		bKeyUsedFlag = true;
		if (MchInf.bFunChuGouSleep)
			return;
		if (ModeState == MODESLEEP)
			return;
		if ((ModeState == MODEWAIT) && (MchInf.bDispDark == 1)) // ����
		{
			MchInf.timeWaitNoKey = 0;
			MchInf.bDispDark = 0;
			//			return;
		}

		KeyInf.longtimeKey8 = 0;
		if ((ModeState != MODESLEEP))
		{
			f_Beep(NORMAL);
			if (MchInf.MusicSound < 100)
				MchInf.MusicSound++;

			MchInf.blekey |= 0x10;
		}
	}
	else
	{
		if (KeyInf.longtimeKey8 < 1000)
			KeyInf.longtimeKey8++;

		if (KeyInf.longtimeKey8 >= 20)
		{
			KeyInf.longtimeKey8 = 0;
			if ((ModeState != MODESLEEP))
			{
				if (MchInf.MusicSound < 100)
					MchInf.MusicSound++;

				MchInf.blekey |= 0x10;
			}
		}
	}
}

void f_Key9Deal_Run(void) // ��ʱ
{

	if (nKeyResultInf & PRESSED_RE)
	{
		bKeyUsedFlag = true;
		if (MchInf.bFunChuGouSleep)
			return;
		if (ModeState == MODESLEEP)
			return;
		if ((ModeState == MODEWAIT) && (MchInf.bDispDark == 1)) // ����
		{
			MchInf.timeWaitNoKey = 0;
			MchInf.bDispDark = 0;
			//			return;
		}

		KeyInf.longtimeKey9 = 0;
		if ((ModeState != MODESLEEP))
		{
			f_Beep(NORMAL);
			if (MchInf.MusicSound > 0)
				MchInf.MusicSound--;

			MchInf.blekey |= 0x20;
		}
	}
	else
	{
		if (KeyInf.longtimeKey9 < 1000)
			KeyInf.longtimeKey9++;

		if (KeyInf.longtimeKey9 >= 20)
		{
			KeyInf.longtimeKey9 = 0;
			if ((ModeState != MODESLEEP))
			{
				if (MchInf.MusicSound > 0)
					MchInf.MusicSound--;
				MchInf.blekey |= 0x20;
			}
		}
	}
}

void f_Key16Deal_Run(void)
{
	if (nKeyResultInf & PRESSED_RE)
	{
		bKeyUsedFlag = true;
		if (ModeState == MODESLEEP)
			return;
		f_Beep(NORMAL);
		if ((MchInf.bFunAlamChuGou) || (MchInf.bFunAlamChuGouAgain))
		{
			MchInf.bFunAlamChuGou = 0;
			MchInf.bFunAlamChuGouAgain = 0;
			MchInf.ntimeslighChugouIcon = 0;
		}
	}
}

void f_Key15Deal_Run(void)
{
	if (nKeyResultInf & PRESSED_RE)
	{
		bKeyUsedFlag = true;
		if (ModeState == MODESLEEP)
			return;
		f_Beep(NORMAL);
		if (MchInf.bFunSetWtHard)
		{
			MchInf.WaterHardState = 1;
			MchInf.timeNoSetWtHard = 0;
			MchInf.bFlagWriteFlash = 1;
		}
	}
}

void f_Key14Deal_Run(void)
{
	if (nKeyResultInf & PRESSED_RE)
	{
		bKeyUsedFlag = true;
		if (ModeState == MODESLEEP)
			return;
		f_Beep(NORMAL);

		if (MchInf.bFunSetWtHard)
		{
			MchInf.WaterHardState = 2;
			MchInf.timeNoSetWtHard = 0;
			MchInf.bFlagWriteFlash = 1;
		}
	}
}
void f_Key13Deal_Run(void)
{
	if (nKeyResultInf & PRESSED_RE)
	{
		bKeyUsedFlag = true;
		if (ModeState == MODESLEEP)
			return;
		f_Beep(NORMAL);
		if (MchInf.bFunSetWtHard)
		{
			MchInf.WaterHardState = 3;
			MchInf.timeNoSetWtHard = 0;
			MchInf.bFlagWriteFlash = 1;
		}
	}
}
void f_Key12Deal_Run(void)
{

	if (nKeyResultInf & PRESSED_RE)
	{

		bKeyUsedFlag = true;
		if (ModeState == MODESLEEP)
			return;

		f_Beep(NORMAL);
		if (MchInf.bFunSetWtHard)
		{
			MchInf.WaterHardState = 4;
			MchInf.timeNoSetWtHard = 0;
			MchInf.bFlagWriteFlash = 1;
		}
	}
	else if (nKeyResultInf & PRESSED_3S) // ����1
	{
		bKeyUsedFlag = true;
	}
}

void f_Key11Deal_Run(void)
{
	if (nKeyResultInf & PRESSED_RE)
	{
		bKeyUsedFlag = true;
		if (ModeState == MODESLEEP)
			return;
		if ((ModeState == MODEWAIT) && (MchInf.bDispDark == 1)) // ����
		{
			//					MchInf.timeWaitNoKey = 0;
			//					MchInf.bDispDark = 0;

			return;
		}

		f_Beep(NORMAL);

		if (MchInf.bFunChuGou)
		{
			if ((MchInf.bPumpChugou) && (MchInf.bChugouYeWei == 0)) // �г�����
			{
				MchInf.nCalTimeChugouIcon = 0;
				MchInf.bYeweiLow = 1;
			}
			else
			{
				MchInf.bYeweiLow = 0;
				MchInf.bFunChuGouReady = 1;
				MchInf.bManuStartChugou = 1;
				MchInf.timeRmdChuGou = 4;
				MchInf.RGBMode = RGB_RED;
				MchInf.ntimeslightZhengfaIcon = 100;
			}
		}
	}
}

void f_Key10Deal_Run(void) // ��ʱ
{

	if (nKeyResultInf & PRESSED_RE)
	{
		bKeyUsedFlag = true;

		if (ModeState == MODERUN)
			return;

		f_Beep(NORMAL);

		if (MchInf.bFunChuGouSleep)
		{
			MchInf.nCalTimeChuGouSleep = 0;
			MchInf.bFunChuGouSleep = 0;
			MchInf.bDispDark = 1;
			return;
		}

		MchInf.RGBMode = RGB_CLOSE;
		MchInf.RGBMode1 = RGB_CLOSE;
		ModeState = MODEWAIT;
		MchInf.bDispDark = 1;
		MchInf.timeWaitNoKey = 0;

		MchInf.ntimeslighChugouIcon = 0;
		MchInf.nCalTimeChugouIcon = 0;

		switch (MchInf.WaterHardState) //????????????
		{
		case 1:
			if (MchInf.zhengqijiworktimesum >= TestModeInf.TIMEHARD1CHUGOUALAMAGAIN)
				MchInf.bFunAlamChuGouAgain = 1;
			else if (MchInf.zhengqijiworktimesum >= TestModeInf.TIMEHARD1CHUGOUALAM)
				MchInf.bFunAlamChuGou = 1;
			break;
		case 2:
			if (MchInf.zhengqijiworktimesum >= TestModeInf.TIMEHARD2CHUGOUALAMAGAIN)
				MchInf.bFunAlamChuGouAgain = 1;
			else if (MchInf.zhengqijiworktimesum >= TestModeInf.TIMEHARD2CHUGOUALAM)
				MchInf.bFunAlamChuGou = 1;
			break;
		case 3:
			if (MchInf.zhengqijiworktimesum >= TestModeInf.TIMEHARD3CHUGOUALAMAGAIN)
				MchInf.bFunAlamChuGouAgain = 1;
			else if (MchInf.zhengqijiworktimesum >= TestModeInf.TIMEHARD3CHUGOUALAM)
				MchInf.bFunAlamChuGou = 1;
			break;
		case 4:
			if (MchInf.zhengqijiworktimesum >= TestModeInf.TIMEHARD4CHUGOUALAMAGAIN)
				MchInf.bFunAlamChuGouAgain = 1;
			else if (MchInf.zhengqijiworktimesum >= TestModeInf.TIMEHARD4CHUGOUALAM)
				MchInf.bFunAlamChuGou = 1;
			break;
		default:
			break;
		}
	}
	else if (nKeyResultInf & PRESSED_3S)
	{
		bKeyUsedFlag = true;
		ModeState = MODESLEEP;

		MchInf.ModeRunState = 0; // ????????
		MchInf.bOpenMusic = 0;	 // ?????????
		MchInf.MusicOn = 0;

		// ????????????????????
		MchInf.blekey |= 0x01;	// AT+CB
		MchInf.blekey |= 0x08;	// AT+CM08
		MchInf.blekey |= 0x100; // AT+BA01

		MchInf.bFunPaiShuiMust = 1;
		MchInf.LED2State = 0;
		MchInf.bFunZhengqiOpen = 0;
		MchInf.bFunAlamChuGou = 0;
		MchInf.bFunAlamChuGouAgain = 0;
		MchInf.ntimeslighChugouIcon = 0;
		MchInf.bManuStartChugou = 0;

		MchInf.RGBMode = RGB_WHITE;
		MchInf.RGBMode1 = RGB_CLOSE;

		MchInf.TimeZhengQi = 0; // ???
		MchInf.bFunZhengfa = 0;
		MchInf.bFunChuGou = 0;
		MchInf.bFunChuGouReady = 0;
		MchInf.timeRmdChuGou = 0;
		MchInf.nCaltimesAutoChugou = 0;
		MchInf.bFunChuGouCal = 0;
		MchInf.bFunChuGouStart = 0;
		MchInf.bFunAlamChuGou = 0;
	}
	// else if (nKeyResultInf & PRESSED_3S)
	// {
	// 	bKeyUsedFlag = true;
	// 	ModeState = MODESLEEP;

	// 	MchInf.ModeRunState = 0; // ????????

	// 	MchInf.blekey |= 0x100; // �Ͽ���������
	// 	MchInf.bFunPaiShuiMust = 1;
	// 	MchInf.LED2State = 0;
	// 	MchInf.MusicOn = 0;
	// 	MchInf.bFunZhengqiOpen = 0;
	// 	MchInf.bFunAlamChuGou = 0;
	// 	MchInf.bFunAlamChuGouAgain = 0;
	// 	MchInf.ntimeslighChugouIcon = 0;
	// 	MchInf.bManuStartChugou = 0;

	// 	//		if(MchInf.bflagBleConnState ==2)
	// 	//		{
	// 	//				MchInf.blekey |= 0x01;
	// 	//				MchInf.MusicOn = 0;
	// 	//		}

	// 	MchInf.RGBMode = RGB_WHITE;
	// 	MchInf.RGBMode1 = RGB_CLOSE;

	// 	MchInf.TimeZhengQi = 0; // ������
	// 	MchInf.bFunZhengfa = 0;
	// 	MchInf.bFunChuGou = 0;

	// 	MchInf.bFunChuGouReady = 0;

	// 	MchInf.timeRmdChuGou = 0;

	// 	MchInf.nCaltimesAutoChugou = 0;
	// 	MchInf.bFunChuGouCal = 0;
	// 	MchInf.bFunChuGouStart = 0;
	// 	MchInf.bFunAlamChuGou = 0;
	// }
}

void f_Key_1_2_Deal_Run(void)
{
	if (nKeyResultInf & PRESSED_3S) // ����3S
	{
		bKeyUsedFlag = true;

		//		if(ModeState != MODERUN)
		//			return;

		f_Beep(NORMAL);

		if (MchInf.bFunChuGou)
		{
			MchInf.bFunChuGou = 0;

			MchInf.bFunChuGouEver = 0;
			MchInf.bFunSetWtHard = 1;
			MchInf.timeNoSetWtHard = 0;
		}
		else
		{
			MchInf.bFunChuGou = 1;
			MchInf.bFunSetWtHard = 0;
			MchInf.bFunZhengfa = 0;
		}
		//			MchInf.WaterHardState = 4;

		MchInf.timeNostartChuGou = 0;
		MchInf.ntimeslight = 0;
		MchInf.timeRmdChuGou = 0;
		//			MchInf.RGBMode = RGB_RED;
		//			ModeState = MODERUN;
		MchInf.timePumpchugouye = 0;
		bflagUp98du = 0;
		MchInf.bFunChuGouStart = 0;
	}
}

void f_Key_5_7_Deal_Run(void)
{
	if (nKeyResultInf & PRESSED_3S) // ����3S
	{
		bKeyUsedFlag = true;

		f_Beep(NORMAL);
		// if(MchInf.bFunWeixiu)
		{
			if (MchInf.bFunWeixiuDisp)
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
void f_Key_8_9_7Deal_Run(void)
{
	if (nKeyResultInf & PRESSED_3S) // ����3S
	{
		bKeyUsedFlag = true;

		f_Beep(NORMAL);
		if (MchInf.bFunWeixiu)
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
	f_KeyTouchVibrateFeedback();
	switch (KeyPressName)
	{
	case KEY_COM_PRESS_3:
		f_Key_8_9_7Deal_Run();
		break;
	case KEY_COM_PRESS_1: // ����о
		f_Key_1_2_Deal_Run();
		break;
	case KEY_COM_PRESS_2: // ����о
		f_Key_5_7_Deal_Run();
		break;

	case KEY_SIGNAL_PRESS_1: // ����
		f_Key1Deal_Run();
		break;

	case KEY_SIGNAL_PRESS_2: // ����
		f_Key2Deal_Run();
		break;

	case KEY_SIGNAL_PRESS_3: // ��ʱ
		f_Key3Deal_Run();
		break;

	case KEY_SIGNAL_PRESS_4: // ָʾ��
		f_Key4Deal_Run();
		break;

	case KEY_SIGNAL_PRESS_5: // �ػ�
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

		//���ٽ�����ɫ��⣬������ȫ��?
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

		if(pFuctionData->selfCheckInf.ucSelfCheckStep == CHECK_STEP_VERSION)//���ٽ�����ɫ���?
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
			if(pFuctionData->selfCheckInf.bIcon_OK)//ͼ�������?
			{
				f_Beep(NORMAL);
				pFuctionData->selfCheckInf.ucSelfCheckStep ++;
				pFuctionData->selfCheckInf.ucCheckCnt = 0;

				pFuctionData->selfCheckInf.keyTuchNumb = 1;
				pFuctionData->selfCheckInf.bKey_5_P = true;
			}
		}
		else if(pFuctionData->selfCheckInf.ucSelfCheckStep == CHECK_STEP_KEY)//��ⰴ��?
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
			&& pFuctionData->selfCheckInf.K4_TouchCnt >= 1)//1S�����ҷ���޹���?�Ұ���������
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
