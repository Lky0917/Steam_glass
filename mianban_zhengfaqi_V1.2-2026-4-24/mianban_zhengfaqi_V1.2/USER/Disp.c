#include "HeadInclude.h"
#include "Disp_const.h"

TYPE_INT IconDisp;
TYPE_INT IconDisp1;
unsigned char RGBModeLast = 0;
unsigned char bflagUp98du = 0;

unsigned char DispAct[6] = {0};
#define LIGHTALL 100
#define LIGHTDARK 30

#define LIGHTHIGHHARD
unsigned char DarkCal[25] = {0}; // 0   ˝¬Îπ‹  1 ”≤∂»  2 ≥˝π∏

byte_def nDark_Flag;
#define bDarkShumaguan nDark_Flag.m_bit.b0
#define bDarkYingdu nDark_Flag.m_bit.b1
#define bDarkChugou nDark_Flag.m_bit.b2
#define bDarkstart nDark_Flag.m_bit.b3
#define bDarkSleep nDark_Flag.m_bit.b4
#define bDarkWaterLow nDark_Flag.m_bit.b5
#define bDarkWaterMid nDark_Flag.m_bit.b6
#define bDarkJian nDark_Flag.m_bit.b7
#define Dark_flag nDark_Flag.m_byte

byte_def nDark_Flag1;
#define bDarkAdd nDark_Flag1.m_bit.b0
#define bDarkMusic nDark_Flag1.m_bit.b1
#define bDarkLED2 nDark_Flag1.m_bit.b2
#define bDarkWaterHigh nDark_Flag1.m_bit.b3
#define bDarkWaterOut nDark_Flag1.m_bit.b4
#define bDarkWaterIn nDark_Flag1.m_bit.b5
#define bDarkWater nDark_Flag1.m_bit.b6
#define bDarkWaterLV1 nDark_Flag1.m_bit.b7

#define Dark_flag1 nDark_Flag1.m_byte

byte_def nDark_Flag2;
#define bDarkWaterLv2 nDark_Flag2.m_bit.b0
#define bDarkTmr nDark_Flag2.m_bit.b1
#define bDarkWaterLv3 nDark_Flag2.m_bit.b2
#define bDarkB2 nDark_Flag2.m_bit.b3
#define bDarkB1 nDark_Flag2.m_bit.b4
#define bDarkYingdu2 nDark_Flag2.m_bit.b5
#define bDarkYingdu3 nDark_Flag2.m_bit.b6
#define bDarkYingdu4 nDark_Flag2.m_bit.b7

#define Dark_flag2 nDark_Flag2.m_byte

void f_Disp_saomiao(void)
{
	char i, Jiantime;
	static unsigned char nCalseg = 0, nCalTime = 0, nCalTimeshumaguan = 0;

	//	for(i=0;i<6;i++)
	//		DispAct[i] = 0xff;
	//	for(i=0;i<25;i++)
	//		DarkCal[i] = 100;

	if ((DispAct[2] & 0x01) && (nCalTime < DarkCal[1])) // yingdu
		LED_HARD1_ON_IO;
	else
		LED_HARD1_OFF_IO;

	if ((DispAct[2] & 0x02) && (nCalTime < DarkCal[2])) // chugou
		LED_CLR_ON_IO;
	else
		LED_CLR_OFF_IO;

	if ((DispAct[2] & 0x04) && (nCalTime < DarkCal[3])) // start
	{
		LED_START_ON_IO;
	}
	else
		LED_START_OFF_IO;

	if ((DispAct[2] & 0x10) && (nCalTime < DarkCal[4])) // sleep
		LED_SLEEP_ON_IO;
	else
		LED_SLEEP_OFF_IO;

	if ((DispAct[2] & 0x40) && (nCalTime < DarkCal[5])) // waterlow
		LED_WATERLOW_ON_IO;
	else
		LED_WATERLOW_OFF_IO;

	if ((DispAct[2] & 0x80) && (nCalTime < DarkCal[6])) // watermid
		LED_WATERMID_ON_IO;
	else
		LED_WATERMID_OFF_IO;

	if ((DispAct[3] & 0x01) && (nCalTime < DarkCal[21])) // yingdu  2
		LED_HARD2_ON_IO;
	else
		LED_HARD2_OFF_IO;

	if ((DispAct[3] & 0x02) && (nCalTime < DarkCal[22])) // yingdu  3
		LED_HARD3_ON_IO;
	else
		LED_HARD3_OFF_IO;

	if ((DispAct[3] & 0x04) && (nCalTime < DarkCal[23])) // yingdu  4
		LED_HARD4_ON_IO;
	else
		LED_HARD4_OFF_IO;

	if ((DispAct[3] & 0x08) && (nCalTime < DarkCal[7])) // jian
		LED_JIAN_ON_IO;
	else
		LED_JIAN_OFF_IO;

	if ((DispAct[3] & 0x10) && (nCalTime < DarkCal[8])) // jia
		LED_ADD_ON_IO;
	else
		LED_ADD_OFF_IO;

	if ((DispAct[3] & 0x20) && (nCalTime < DarkCal[9])) // music
		LED_BLE_ON_IO;
	else
		LED_BLE_OFF_IO;

	if ((DispAct[3] & 0x80) && (nCalTime < DarkCal[10])) // LED2
		LED_220V_ON_IO;
	else
		LED_220V_OFF_IO;

	if ((DispAct[4] & 0x01) && (nCalTime < DarkCal[11])) // waterhigh
		LED_WATERHIGH_ON_IO;
	else
		LED_WATERHIGH_OFF_IO;

	if ((DispAct[4] & 0x02) && (nCalTime < DarkCal[12])) // waterout
		LED_WATEROUT_ON_IO;
	else
		LED_WATEROUT_OFF_IO;

	if ((DispAct[4] & 0x04) && (nCalTime < DarkCal[13])) // waterin
		LED_WATERIN_ON_IO;
	else
		LED_WATERIN_OFF_IO;

	if ((DispAct[4] & 0x08) && (nCalTime < DarkCal[14])) // water
		LED_WATER_ON_IO;
	else
		LED_WATER_OFF_IO;

	if ((DispAct[4] & 0x10) && (nCalTime < DarkCal[15])) // LV1
		LED_TPRLV1_ON_IO;
	else
		LED_TPRLV1_OFF_IO;

	if ((DispAct[4] & 0x20) && (nCalTime < DarkCal[16])) // LV2
		LED_TPRLV2_ON_IO;
	else
		LED_TPRLV2_OFF_IO;

	if ((DispAct[4] & 0x40) && (nCalTime < DarkCal[17])) // tmr
		LED_TPR_ON_IO;
	else
		LED_TPR_OFF_IO;

	if ((DispAct[4] & 0x80) && (nCalTime < DarkCal[18])) // LV3
		LED_TPRLV3_ON_IO;
	else
		LED_TPRLV3_OFF_IO;

	if ((DispAct[5] & 0x01) && (nCalTime < (DarkCal[19]))) // B2
		LED_RGB_ON_IO;
	else
		LED_RGB_OFF_IO;

	if ((DispAct[5] & 0x04) && (nCalTime < DarkCal[20])) // B1
		LED_ZHENGFA_ON_IO;
	else
		LED_ZHENGFA_OFF_IO;

	SEG1_OFF_IO;
	SEG2_OFF_IO;
	SEG3_OFF_IO;
	SEG4_OFF_IO;
	SEG5_OFF_IO;
	SEG6_OFF_IO;
	SEG7_OFF_IO;

	GRID1_OFF_IO;
	GRID2_OFF_IO;
	switch (nCalseg)
	{
	case 0:
		if (nCalTimeshumaguan < DarkCal[0])
		{
			if (DispAct[0] & 0x01)
				SEG1_ON_IO;
			if (DispAct[0] & 0x02)
				SEG2_ON_IO;
			if (DispAct[0] & 0x04)
				SEG3_ON_IO;
			if (DispAct[0] & 0x08)
				SEG4_ON_IO;
			if (DispAct[0] & 0x10)
				SEG5_ON_IO;
			if (DispAct[0] & 0x20)
				SEG6_ON_IO;
			if (DispAct[0] & 0x40)
				SEG7_ON_IO;
		}
		GRID1_ON_IO;
		break;
	case 1:
		if (nCalTimeshumaguan < DarkCal[0])
		{

			if (DispAct[1] & 0x01)
				SEG1_ON_IO;
			if (DispAct[1] & 0x02)
				SEG2_ON_IO;
			if (DispAct[1] & 0x04)
				SEG3_ON_IO;
			if (DispAct[1] & 0x08)
				SEG4_ON_IO;
			if (DispAct[1] & 0x10)
				SEG5_ON_IO;
			if (DispAct[1] & 0x20)
				SEG6_ON_IO;
			if (DispAct[1] & 0x40)
				SEG7_ON_IO;
		}
		GRID2_ON_IO;
		break;

	default:
		break;
	}

	nCalTime++;
	if (nCalTime >= 100)
	{
		nCalTime = 0;
	}
	nCalseg ^= 1;
	//	if(nCalseg > 1)
	//		nCalseg = 0;
	nCalTimeshumaguan++;
	if (nCalTimeshumaguan > 50)
	{
		nCalTimeshumaguan = 0;
	}
}

#define HARDLEDLIGHT 30

void f_Deal_Seg(void)
{
	unsigned char i;
	static unsigned char addwaterstate = 0, nCntTime = 0;

	for (i = 0; i < 10; i++)
		MchInf.Dispbuffer[i] = 0;

	//	nIconDisp = 0;
	//	nIconDisp1 = 0;

	//	bIconLED2 = 1;
	if ((ModeState == MODERUN) && (MchInf.bFunZhengqiOpen == 0) && ((MchInf.bAddWater) || ((MchInf.bFunHot) && (MchInf.TmprWater < 95))) && (!MchInf.bErrGuZhang))
	{
		nCntTime++;
		if (nCntTime >= 30)
		{
			nCntTime = 0;
			addwaterstate++;
			if (addwaterstate > 7)
				addwaterstate = 0;
		}
		switch (addwaterstate)
		{
		case 0:
			MchInf.Dispbuffer[0] |= 0x01;
			break;
		case 1:
			MchInf.Dispbuffer[2] |= 0x01;
			break;
		case 2:
			MchInf.Dispbuffer[2] |= 0x02;
			break;
		case 3:
			MchInf.Dispbuffer[2] |= 0x04;
			break;
		case 4:
			MchInf.Dispbuffer[2] |= 0x08;
			break;
		case 5:
			MchInf.Dispbuffer[0] |= 0x08;
			break;
		case 6:
			MchInf.Dispbuffer[0] |= 0x10;
			break;
		case 7:
			MchInf.Dispbuffer[0] |= 0x20;
			break;
		default:
			break;
		}
	}
	else
	{
		MchInf.Dispbuffer[0] = nTab_Number[MchInf.LEDDisp[0]]; //  1A   2B  4C  8D  10E  20F  40G  80 DP
		MchInf.Dispbuffer[1] = 0x00;
		MchInf.Dispbuffer[2] = nTab_Number[MchInf.LEDDisp[1]]; //  1A   2B  4C  8D  10E  20F  40G  80 DP
		MchInf.Dispbuffer[3] = 0x00;
	}

	if (bIConWaterHard1)
		MchInf.Dispbuffer[4] |= 0x01;
	if (bIConChuGou)
		MchInf.Dispbuffer[4] |= 0x02;
	if (bIConStart)
	{
		MchInf.Dispbuffer[4] |= 0x04;
		MchInf.Dispbuffer[4] |= 0x08;
	}
	if (bIConSleep)
	{
		MchInf.Dispbuffer[4] |= 0x10;
		MchInf.Dispbuffer[4] |= 0x20;
	}
	if (bIconWaterLOW)
		MchInf.Dispbuffer[4] |= 0x40;
	if (bIconWaterMID)
		MchInf.Dispbuffer[4] |= 0x80;

	MchInf.Dispbuffer[5] = 0x00;

	if (bIConWaterHard2)
		MchInf.Dispbuffer[6] |= 0x01;
	if (bIConWaterHard3)
		MchInf.Dispbuffer[6] |= 0x02;

	if (bIConWaterHard4)
		MchInf.Dispbuffer[6] |= 0x04;
	if (bIconJIan)
		MchInf.Dispbuffer[6] |= 0x08;
	if (bIconAdd)
		MchInf.Dispbuffer[6] |= 0x10;
	if (bIconSound)
	{
		MchInf.Dispbuffer[6] |= 0x20;
		MchInf.Dispbuffer[6] |= 0x40;
	}
	if (bIconLED2)
		MchInf.Dispbuffer[6] |= 0x80;

	MchInf.Dispbuffer[7] = 0x00;

	if (bIconWaterHIGH)
		MchInf.Dispbuffer[8] |= 0x01;

	if (bIconOut)
		MchInf.Dispbuffer[8] |= 0x02;
	if (bIconIn)
		MchInf.Dispbuffer[8] |= 0x04;

	if (bIconWater)
		MchInf.Dispbuffer[8] |= 0x08;

	if (bIconLV1)
		MchInf.Dispbuffer[8] |= 0x10;
	if (bIconLV2)
		MchInf.Dispbuffer[8] |= 0x20;
	if (bIconTmr)
		MchInf.Dispbuffer[8] |= 0x40;
	if (bIconLV3)
		MchInf.Dispbuffer[8] |= 0x80;

	//	if(MchInf.RGBMode1 != RGB_CLOSE)

	if (bIconB2)
		MchInf.Dispbuffer[9] |= 0x03;

	//	if(MchInf.bflagB1White)
	if (bIconB1)
		MchInf.Dispbuffer[9] |= 0x0C;

	//	if(MchInf.bDispDark)
	//		TM1620B_work(MchInf.Dispbuffer,TM1628_CMD_DARK);
	//	else
	//		TM1620B_work(MchInf.Dispbuffer,TM1628_CMD_DISP);
	INTERRUPT_ALL_CLOSE;
	//	Dark_flag = 0x0;
	//	Dark_flag1 = 0x0;
	//	Dark_flag2 = 0x0;

	if (bDarkShumaguan)
		DarkCal[0] = 2; // LIGHTDARK;
	else
		DarkCal[0] = 20; // LIGHTALL ;

	if (bDarkYingdu)
		DarkCal[1] = 2; // LIGHTDARK;
	else
		DarkCal[1] = HARDLEDLIGHT; // 60 ;

	if (bDarkYingdu2)
		DarkCal[21] = 2; // LIGHTDARK;
	else
		DarkCal[21] = HARDLEDLIGHT; // 60 ;

	if (bDarkYingdu3)
		DarkCal[22] = 2; // LIGHTDARK;
	else
		DarkCal[22] = HARDLEDLIGHT; // 60 ;
	if (bDarkYingdu4)
		DarkCal[23] = 2; // LIGHTDARK;
	else
		DarkCal[23] = HARDLEDLIGHT; // 60 ;

	if (bDarkChugou)
		DarkCal[2] = 10; // LIGHTDARK;
	else
		DarkCal[2] = LIGHTALL;

	if (bDarkstart)
		DarkCal[3] = 5; // LIGHTDARK;
	else
		DarkCal[3] = LIGHTALL; // LIGHTALL ;

	if (bDarkSleep)
		DarkCal[4] = LIGHTDARK - 2;
	else
		DarkCal[4] = LIGHTALL;

	if (bDarkWaterLow)
		DarkCal[5] = 3; // LIGHTDARK;
	else
		DarkCal[5] = LIGHTALL;

	if (bDarkWaterMid)
		DarkCal[6] = 3; // LIGHTDARK;
	else
		DarkCal[6] = LIGHTALL;

	if (bDarkJian)
		DarkCal[7] = 5;
	else
		DarkCal[7] = 70; // LIGHTALL ;

	if (bDarkAdd)
		DarkCal[8] = 5;
	else
		DarkCal[8] = 70;

	if (bDarkMusic)
		DarkCal[9] = 2;
	else
		DarkCal[9] = 90;

	if (bDarkLED2)
		DarkCal[10] = 4; // LIGHTDARK;
	else
		DarkCal[10] = 50;

	if (bDarkWaterHigh)
		DarkCal[11] = 3; // LIGHTDARK;
	else
		DarkCal[11] = LIGHTALL;

	if (bDarkWaterOut)
		DarkCal[12] = 3; // LIGHTDARK;
	else
		DarkCal[12] = LIGHTALL;

	if (bDarkWaterIn)
		DarkCal[13] = 3; // LIGHTDARK;
	else
		DarkCal[13] = LIGHTALL;

	if (bDarkWater)
		DarkCal[14] = 3; // LIGHTDARK;
	else
		DarkCal[14] = LIGHTALL;

	if (bDarkWaterLV1)
		DarkCal[15] = 3; // LIGHTDARK;
	else
		DarkCal[15] = 50; // 65 ;

	if (bDarkWaterLv2)
		DarkCal[16] = 3; // LIGHTDARK;
	else
		DarkCal[16] = 50; // 65 ;

	if (bDarkTmr)
		DarkCal[17] = 5; // LIGHTDARK;
	else
		DarkCal[17] = 60; // 60 ;

	if (bDarkWaterLv3)
		DarkCal[18] = 3; // LIGHTDARK;
	else
		DarkCal[18] = 50; // 65;

	if (bDarkB2)
		DarkCal[19] = 5;
	else
		DarkCal[19] = 100;

	if (bDarkB1)
		DarkCal[20] = 8;
	else
		DarkCal[20] = 100;

	DispAct[0] = MchInf.Dispbuffer[0];
	DispAct[1] = MchInf.Dispbuffer[2];
	DispAct[2] = MchInf.Dispbuffer[4];
	DispAct[3] = MchInf.Dispbuffer[6];
	DispAct[4] = MchInf.Dispbuffer[8];
	DispAct[5] = MchInf.Dispbuffer[9];
	INTERRUPT_ALL_OPED;
}

static unsigned char CalChuGouLight = 0;

void f_Disp_yewei(void)
{
	if (MchInf.bChugouYeWei == 0) // Êó†Èô§Âû¢Ê∂≤Èó?ÁÉ?
	{

		CalChuGouLight++;
		if (CalChuGouLight > 100 / 2)
		{
			CalChuGouLight = 0;
			if (MchInf.ntimeslight < 10 / 2)
				MchInf.ntimeslight++;
		}

		if ((CalChuGouLight < 50 / 2) && (MchInf.ntimeslight < 30))
		{
			//								bIConStart = 0;
			//								bIConChuGou = 0;
			MchInf.LEDDisp[0] = LEDCLOSE;
			MchInf.LEDDisp[1] = LEDCLOSE;
		}
		else
		{
			// bIConStart = 1;
			//								bIConChuGou = 1;
			MchInf.LEDDisp[0] = LED_ZIMU_L;
			MchInf.LEDDisp[1] = 0;
		}

		if (MchInf.ntimeslight > 30)
		{
			bIConStart = 0;
			bIConChuGou = 0;
			MchInf.LEDDisp[0] = LED_ZIMU_L;
			MchInf.LEDDisp[1] = 0;
		}
	}
	//						else//ÊúâÈô§Âû¢Ê∂≤
	//						{
	//								bIConStart = 1;
	//								bIConChuGou = 1;
	//						}
}

void f_B1Light(void) // B1À¯∂®…¡À∏
{
	bIconB1 = 0; // πÿ±’
	// B1 Èó?ÁÉ? 3 Ê¨?
	if (MchInf.ntimeslightZhengfaIcon < 3) // shanshuo
	{
		if (MchInf.nCalTimeZhengfaqiIcon < 50 / 2)
			MchInf.RGBMode = RGB_CLOSE;
		else if (MchInf.nCalTimeZhengfaqiIcon < 100 / 2)
			MchInf.RGBMode = RGB_RED;
		MchInf.nCalTimeZhengfaqiIcon++;
		if (MchInf.nCalTimeZhengfaqiIcon > 100 / 2)
		{
			MchInf.nCalTimeZhengfaqiIcon = 0;
			MchInf.ntimeslightZhengfaIcon++;
		}
	}
	else
		MchInf.RGBMode = RGB_RED;
}

void f_Disp_WaterLV(void)
{
	unsigned char temp;

	temp = MchInf.WaterLV & 0x07;

	if (temp == 1)
		bIconWaterLOW = 1;
	else if (temp == 3)
	{
		bIconWaterLOW = 1;
		bIconWaterMID = 1;
	}
	else if (temp == 7)
	{
		bIconWaterLOW = 1;
		bIconWaterMID = 1;
		bIconWaterHIGH = 1;
	}
}

void f_Disp_TprLV(void)
{
	bIconLV3 = 1;
	bIconLV2 = 1;
	bIconLV1 = 1;
	bIconTmr = 1;

	if (MchInf.bFunHot == 0)
		bDarkTmr = 1;

	if (MchInf.TmrLV == 1)
	{
		bDarkWaterLv2 = 1;
		bDarkWaterLv3 = 1;
	}
	else if (MchInf.TmrLV == 2)
	{
		bDarkWaterLv3 = 1;
	}
	else if (MchInf.TmrLV == 3)
	{
	}
}
static unsigned char bAutoChugou = 0;
void f_Deal_ChugouStart(void)
{

	static unsigned char bflagAddWater = 0; // ‘¯æ≠º”ÀÆ

	bAutoChugou = 1;

	//  ÷∂Ø”–±√                                         //0 Ëá?Âä?  1 ÊâãÂä®
	//			if(((MchInf.bPumpChugou)&&(MchInf.bFunChugouAutoOrManu))||(MchInf.bFunChugouAutoOrManu==0))//ÊúâÈô§Âû¢Ê≥µ
	{
		if (MchInf.nCaltimesAutoChugou < 3600 * 110)
			MchInf.nCaltimesAutoChugou++;
#ifdef TEST_SUOSHI
		if (MchInf.nCaltimesAutoChugou >= 1200) // 2min  //3600*100/2)//1hour
#else
		if (MchInf.nCaltimesAutoChugou >= 3600 * 100 / 2) // 1hour
#endif
		{
			if (((MchInf.bChugouYeWei == 0) && (MchInf.bFunChugouAutoOrManu == 0)) || (MchInf.bFunChugouAutoOrManu))
			{
				ModeState = MODEWAIT;
				MchInf.timeWaitNoKey = 0;
				return;
			}
			MchInf.bManuStartChugou = 0;
			MchInf.bYeweiLow = 0;
			MchInf.bFunChuGouReady = 1;
			// MchInf.bFunChuGouMau = 1;
			MchInf.timeRmdChuGou = 4;
			MchInf.RGBMode = RGB_RED;
			MchInf.ntimeslightZhengfaIcon = 100;

			MchInf.nCaltimesAutoChugou = 0;
			MchInf.bFunChuGou = 1;
			//					MchInf.bFunChuGouStart = 1;
			MchInf.bFunAlamChuGou = 0;
			MchInf.bFunAlamChuGouAgain = 0;
		}
		else
			MchInf.RGBMode = RGB_WHITE;
		/*
							MchInf.timeNostartChuGou = 0;
							MchInf.ntimeslight = 0;
							MchInf.timeRmdChuGou = 4;
							MchInf.RGBMode = RGB_WHITE;


							if((MchInf.bFunChugouAutoOrManu==0))//◊‘∂Ø”–≥˝π∏“∫
							{
								if(MchInf.bChugouYeWei == 1)
								{
									MchInf.nCaltimesAutoChugou = 0;
									//MchInf.bFlagWriteFlash = 1;
									MchInf.bPumpChugouYe  = 1;
									MchInf.bFunChuGou = 1;
									MchInf.bFunChuGouStart = 1;
									MchInf.bFunChuGouReady = 1;
									MchInf.bFunAlamChuGou = 0;
									MchInf.RGBMode = RGB_RED;
								}
							}
							else// ÷∂Ø
							{
								if(((MchInf.WaterLV&0x07) == 0)||((MchInf.WaterLV&0x07) == 0x01)||((MchInf.WaterLV&0x07) == 0x03))// ‰Ωé‰∫éÈ´òÊ∞¥‰Ωç‰ª•‰∏ãÂ∞±Âä†Ê∞¥
								{
									MchInf.bAddWater = 1;
									MchInf.bFunHot = 0;
									bflagAddWater = 1;

								}
								else if(MchInf.WaterLV == 0x07)//ÔøΩÔøΩÔøΩ–∏ﬂ∂ÔøΩÔøΩÔøΩ
								{
									MchInf.bAddWater = 0;
									MchInf.bFunHot = 1;
								}
								else
								{
										MchInf.bAddWater = 0;
										MchInf.bFunHot = 0;
								}

								if(((MchInf.WaterLV&0x07) == 0x03)||((MchInf.WaterLV&0x07) == 0x07))//÷–ÀÆŒª“‘…œº”»»
								{
										MchInf.bFunHot = 1;
										if(MchInf.TmprWater >= 90)
										{
												if((MchInf.bChugouYeWei == 1)&&(MchInf.bPumpChugou)&&bflagAddWater)
												{
													MchInf.bPumpChugouYe  = 1;
												}
													MchInf.nCaltimesAutoChugou = 0;
													MchInf.bFunChuGou = 1;
													MchInf.bFunChuGouStart = 1;
													MchInf.bFunAlamChuGou = 0;
													bflagAddWater	 = 0;
										}
								}

							}


						}	*/
	}
	//			else
	//			{
	////				if(MchInf.bFunChuGouStart==0)
	//				{
	//						MchInf.nCaltimesAutoChugou = 0;
	////						MchInf.bFlagWriteFlash = 1;
	////						MchInf.bFunChuGouStart = 1;
	//				}
	//			}
}
void f_Disp(void)
{
	static unsigned char SoundLast = 50, delaytime = 20; //
	static unsigned int timelightB1 = 0;

	static unsigned int nCal5sDisp = 0;
	static unsigned int nCal30sBleConn = 0, Calblecontime = 0;
	unsigned char temp;
	static unsigned char bflagEverChugou = 0; // once chugou panduan
	static unsigned char Delaytime = 0;
	nIconDisp = 0;
	nIconDisp1 = 0;
	MchInf.Relay = 0;
	Dark_flag = 0;
	Dark_flag1 = 0;
	Dark_flag2 = 0;

	//		MchInf.WaterLV = 0x03;
	//		MchInf.TmprWater = 96;
	//		MchInf.TmprHouse = 38;

	if (ModeState == MODESLEEP)
	{
		MchInf.bDispDark = 1;
		bIConSleep = 1;
		// bIconSound = 1; // ∂‘”¶ Dispbuffer[6] µƒ 0x20 ∫Õ 0x40£®LED17/18£©
		// bDarkMusic = 0; // ‘›Õ£ ±’‚¡Ωø≈µ∆∞¥°∞¡¡°±¡¡∂» ‰≥ˆ

		//		bIconZhengqi = 1;
		//		MchInf.RGBMode = RGB_CLOSE;
		//		MchInf.RGBMode1 = RGB_CLOSE;
		MchInf.LEDDisp[0] = LEDCLOSE;
		MchInf.LEDDisp[1] = LEDCLOSE;
		MchInf.bFunHot = 0;	  // ÔøΩÔøΩÔøΩÔøΩÕ£÷π
		MchInf.bAddWater = 0; // ÔøΩÔøΩÀÆÕ£÷π
		MchInf.LED2State = 0; // ÔøΩÿµÔøΩ
		MchInf.MusicOn = 0;
		bDarkSleep = 1;
		MchInf.bflagB1White = 0;

		//		if(MchInf.bFunPaiShui)
		//		{
		//			bIconOut = 1;
		//			bIconWater = 1;
		////			f_Disp_WaterLV();
		//		}
	}
	else
	{

		//		if(MchInf.LED2State)
		//			MchInf.bflagB1White = 1;

		//			MchInf.RGBMode = RGB_WHITE;
		//			MchInf.RGBMode1 = RGB_WHITE;

		if ((MchInf.RGBMode == RGB_CLOSE) && (ModeState != MODEZANTING))
		{
			bIconB1 = 1;
			bDarkB1 = 1;
		}

		bIconB2 = 1;

		bIconSound = 1;
		bIconAdd = 1;
		bIconJIan = 1;
		bIConSleep = 1;
		bIconLED2 = 1;

		bDarkAdd = 1;
		bDarkJian = 1;

		bDarkSleep = 1;

		if (MchInf.RGBMode1 == RGB_CLOSE)
			bDarkB2 = 1;

		if (MchInf.LED2State == 0)
		{
			bDarkLED2 = 1;
		}

		if (MchInf.BLErepair) // 0  Œ¥¡¨Ω”≥…π¶  1  ¡¨Ω”≥…π¶Œ¥≤•∑≈“Ù¿÷   2  ≤•∑≈“Ù¿÷
		{
			if (MchInf.bflagBleConnState == 0)
			{
				MchInf.BlePairTime++;
				if (MchInf.BlePairTime < 30 * 50)
				{
					MchInf.nCallightblepair++;
					if (MchInf.nCallightblepair < 25)
						bIconSound = 1;
					else if (MchInf.nCallightblepair < 50)
						bIconSound = 0;
					else
						MchInf.nCallightblepair = 0;
				}
				else
				{
					MchInf.BlePairTime = 0;
					MchInf.BLErepair = 0;
				}
			}
			else
			{
				MchInf.BlePairTime = 0;
				MchInf.BLErepair = 0;
			}
		}

		else if (MchInf.MusicOn) // ≤•∑≈¡¡£¨‘›Õ£∞µ£®≤ª‘Ÿ“¿¿µ¿∂—¿¡¨Ω”◊¥Ã¨£©
		{
			bDarkMusic = 0; // ¡¡
		}
		else
		{
			bDarkMusic = 1; // ∞µ
		}

		// if ((MchInf.bflagBleConnState != 2) && (MchInf.MusicOn == 0))
		// {
		// 	bDarkMusic = 1;
		// }
		// else
		// {
		// 	bDarkMusic = 0;
		// }
		if (MchInf.MusicSound != SoundLast)
		{
			if (MchInf.MusicSound > SoundLast)
				bDarkAdd = 0;
			else if (MchInf.MusicSound < SoundLast)
				bDarkJian = 0;

			delaytime--;
			if (delaytime == 0)
			{
				delaytime = 20;
				SoundLast = MchInf.MusicSound;
			}
		}
	}

	if (ModeState == MODEWAIT)
	{

		MchInf.LEDDisp[0] = LEDCLOSE;
		MchInf.LEDDisp[1] = LEDCLOSE;

		if ((MchInf.LED2State == 0) && (MchInf.bflagBleConnState != 2) && (MchInf.RGBMode1 == RGB_CLOSE) && (MchInf.MusicOn == 0))
		{
			if (MchInf.timeWaitNoKey > TestModeInf.TIMEWAITNOKEY) // 2min  12000
			{
				ModeState = MODESLEEP;
				MchInf.blekey |= 0x100; // ∂œø™¿∂—¿¡¨Ω”
			}
			else
			{
				MchInf.timeWaitNoKey++;
				if (MchInf.timeWaitNoKey >= 1000 / 2)
				{
					Dark_flag = 0xff;
					Dark_flag1 = 0xff;
					Dark_flag2 = 0xff;
				}
			}
		}
		else
			MchInf.timeWaitNoKey = 0;
	}
	else if ((ModeState == MODERUN) || (ModeState == MODEZANTING))
	{

		MchInf.LEDDisp[0] = MchInf.TimeZhengQi / 10;
		MchInf.LEDDisp[1] = MchInf.TimeZhengQi % 10;
		bDarkB1 = 0;
		/*
				if((MchInf.bflagBleConnState > 0)&&(MchInf.ModeRunState < 3))
				{
					Delaytime++;
					if(Delaytime == 1)
					{
						MchInf.blekey |= 0x40;
						MchInf.MusicOn = 1;
					}
				}

				*/
		if (ModeState == MODERUN)
		{
			//			RGBModeLast = ModeState;
			MchInf.bDispDark = 0;

			{

				if (MchInf.TimeZhengQi != 0)
				{
					MchInf.bFunZhengfa = 1; // Ëí∏Ê±ΩÂ∑•‰Ωú‰∏?
					if ((MchInf.bFunPaiShui == 0) && (MchInf.bFunPaiShuiMust == 0))
					{
						if (((MchInf.WaterLV & 0x07) == 0) || ((MchInf.WaterLV & 0x07) == 0x01) || ((MchInf.WaterLV & 0x07) == 0x03)) // ‰Ωé‰∫éÈ´òÊ∞¥‰Ωç‰ª•‰∏ãÂ∞±Âä†Ê∞¥
						{
							MchInf.bAddWater = 1;
							MchInf.bFunHot = 0;
						}
						else if (MchInf.WaterLV == 0x07) // ÔøΩÔøΩÔøΩ–∏ﬂ∂ÔøΩÔøΩÔøΩ
						{
							MchInf.bAddWater = 0;
						}
						else
						{
							MchInf.bAddWater = 0;
							MchInf.bFunHot = 0;
						}
					}
					else
					{
						MchInf.bAddWater = 0;
					}
					//				MchInf.bFunZhengqiOpen = 1;//Áõ¥Êé•ËÆ°Êó∂
					//				if(MchInf.bAddWater)
					//				{
					//					bIconIn = 1;
					//				}
					if ((MchInf.WaterLV == 3) || (MchInf.WaterLV == 7)) // ‰∏?Ê∞¥‰Ωç‰ª•‰??
					{

						if (MchInf.TmprWater >= 95)
						{
							MchInf.bFunZhengqiOpen = 1;
						}
						MchInf.bFunPaiShui = 0;
						MchInf.timePaiShuiCal = 0;
						MchInf.nCalTimeChugouIcon = 0;
						MchInf.bFunChuGouEver = 0;

						if (MchInf.bErrorTmpr == 0)
						{
							MchInf.bFunHot = 1; // ÔøΩÔøΩÔøΩÔøΩ
							if (MchInf.TmrLV == 1)
								temp = 36;
							else if (MchInf.TmrLV == 2)
								temp = 41;
							else if (MchInf.TmrLV == 3)
								temp = 45;

							if (MchInf.TmprHouse <= temp)
								MchInf.Relay |= 0x700;
							else if (MchInf.TmprHouse == (temp + 1))
								MchInf.Relay |= 0x300;
							else if (MchInf.TmprHouse == (temp + 2))
								MchInf.Relay |= 0x100;
						}

						//					if(((MchInf.TmrLV == 1)&&(MchInf.TmprHouse >= 36))||//36~39du
						//						((MchInf.TmrLV == 2)&&(MchInf.TmprHouse >= 41))||//41~44du
						//						((MchInf.TmrLV == 3)&&(MchInf.TmprHouse >= 45)))//45~48du
						//					{
						//						//MchInf.bFunZhengqiOpen = 0;//ÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÕ£÷πÔøΩÔøΩÔøΩÔøΩ
						//						MchInf.bDispDark = 1;
						//						MchInf.bFunHot = 0;
						//					}
					}
				}
				else // ÁªìÊùü
				{
					MchInf.bFunZhengfa = 0;
					MchInf.bAddWater = 0;
					MchInf.bFunHot = 0;

					MchInf.LEDDisp[0] = LEDCLOSE;
					MchInf.LEDDisp[1] = LEDCLOSE;

					if (MchInf.timePaiShuiCal < 30 * 60 * 101)
						MchInf.timePaiShuiCal++;

#ifdef TEST_SUOSHI
					if (MchInf.timePaiShuiCal >= 30 * 100 / 2) // TestModeInf.TIMEPAISHUIRUN)
#else
					if (MchInf.timePaiShuiCal >= TestModeInf.TIMEPAISHUIRUN)
#endif
					{

#ifdef TEST_SUOSHI
						if (MchInf.timePaiShuiCal == (30 * 100 / 2 + 5))
#else
						if (MchInf.timePaiShuiCal >= (TestModeInf.TIMEPAISHUIRUN + 5))
#endif
							MchInf.bFunPaiShui = 1;

						if (((MchInf.WaterLV & 0x07) == 0) && (MchInf.bFunChuGouEver == 0))
						{
							// MchInf.bFunPaiShui = 0;
							// ModeState = MODEWAIT;
							MchInf.RGBMode = RGB_WHITE;
							MchInf.bFunChuGouEver = 1; // ÊéíÊ∞¥ÊéíÂÆå
							bflagEverChugou = 1;
						}
					}
				}
			}
		}
		else if (ModeState == MODEZANTING)
		{
			MchInf.bDispDark = 1;
			bDarkShumaguan = 1;
			bIconWater = 0;
			MchInf.bFunHot = 0;	  // ÔøΩÔøΩÔøΩÔøΩÕ£÷π
			MchInf.bAddWater = 0; // ÔøΩÔøΩÀÆÕ£÷π

			timelightB1++;
			if (timelightB1 < 100 / 2)
				MchInf.RGBMode = RGB_CLOSE;
			else if (timelightB1 < 200 / 2)
			{
				if (MchInf.ModeRunState == 0)
				{
					MchInf.RGBMode = RGB_WHITE;
					bIconB1 = 1;
					bDarkB1 = 0;
				}
				else if (MchInf.ModeRunState == 1)
					MchInf.RGBMode = RGB_YELLOW;
				else if (MchInf.ModeRunState == 2)
					MchInf.RGBMode = RGB_BLUE;
				else if (MchInf.ModeRunState == 3)
					MchInf.RGBMode = RGB_ZISe;
			}
			else
				timelightB1 = 0;

			if (MchInf.timePaiShuiCal < 60 * 60 * 101)
				MchInf.timePaiShuiCal++;
#ifdef TEST_SUOSHI
			if (MchInf.timePaiShuiCal >= 30 * 100 / 2) //)
#else
			if (MchInf.timePaiShuiCal >= TestModeInf.TIMEPAISHUIZANTING)
#endif
			{

#ifdef TEST_SUOSHI
				if (MchInf.timePaiShuiCal == (30 * 100 / 2 + 5))
#else
				if (MchInf.timePaiShuiCal >= (TestModeInf.TIMEPAISHUIZANTING + 5))
#endif
					MchInf.bFunPaiShui = 1;

				if (((MchInf.WaterLV & 0x07) == 0) && (MchInf.bFunChuGouEver == 0))
				{
					// MchInf.bFunPaiShui = 0;
					// ModeState = MODEWAIT;
					MchInf.RGBMode = RGB_WHITE;
					MchInf.bFunChuGouEver = 1; // ÊéíÊ∞¥ÊéíÂÆå
					bflagEverChugou = 1;
				}
			}

			if ((MchInf.TmprHouse >= 36) && (MchInf.TmprHouse <= 39))
				MchInf.TmrLV = 1;
			else if ((MchInf.TmprHouse >= 41) && (MchInf.TmprHouse <= 44))
				MchInf.TmrLV = 2;
			else if ((MchInf.TmprHouse >= 45) && (MchInf.TmprHouse <= 48))
				MchInf.TmrLV = 3;
		}

		if ((MchInf.bFunChuGouEver) && (bflagEverChugou))
		{
			//			MchInf.bFunChuGouEver = 0;
			bflagEverChugou = 0;
			bflagUp98du = 0;
			MchInf.nCalTimeChugouIcon = 0;

			switch (MchInf.WaterHardState) // ÊéíÊ∞¥ÂÆåÊàêÂà§Êñ≠Êò?Âê¶ÊèêÈÜíÈô§Âû?
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
			if (MchInf.bFunAlamChuGouAgain == 1)
				MchInf.timesAlamChuGouAgain++;

			if ((MchInf.bFunAlamChuGou == 0) && (MchInf.bFunAlamChuGouAgain == 0))
			{
				ModeState = MODEWAIT;
				MchInf.timeWaitNoKey = 0;
			}
		}
		if (MchInf.bFunChuGouEver == 0)
			f_Disp_TprLV();
	}

	if (ModeState != MODESLEEP)
	{
		// ËÆæÁΩÆÁ°?Â∫?
		if (MchInf.bFunSetWtHard)
		{
			bIConStart = 0;
			bIConChuGou = 1;
			bDarkChugou = 1;
			MchInf.timeNoSetWtHard++;
			if (MchInf.timeNoSetWtHard >= 1000 / 2)
			{
				MchInf.bFunSetWtHard = 0;
			}
			bIConWaterHard1 = 1;
			bIConWaterHard2 = 1;
			bIConWaterHard3 = 1;
			bIConWaterHard4 = 1;
			if (MchInf.WaterHardState == 1)
			{
				//					bIConWaterHard1 = 1;
				bDarkYingdu2 = 1;
				bDarkYingdu3 = 1;
				bDarkYingdu4 = 1;
			}
			else if (MchInf.WaterHardState == 2)
			{
				bDarkYingdu3 = 1;
				bDarkYingdu4 = 1;
			}
			else if (MchInf.WaterHardState == 3)
			{
				bDarkYingdu4 = 1;
			}
			else if (MchInf.WaterHardState == 4)
			{
				//					bIConWaterHard1 = 1;
				//					bIConWaterHard2 = 1;
				//					bIConWaterHard3 = 1;
				//					bIConWaterHard4 = 1;
			}
			ModeState = MODECHUGOU;
		}
		else if ((MchInf.bFunChuGou) && (MchInf.bFunZhengfa == 0))
		{
			bIConStart = 1;
			bIConChuGou = 1;
			MchInf.LEDDisp[0] = MchInf.timeRmdChuGou;
			MchInf.LEDDisp[1] = LED_ZIMU_h;
			bDarkShumaguan = 1;

			ModeState = MODECHUGOU;

			if (MchInf.bFunChuGouStart == 0)
			{
				if (MchInf.bFunChuGouReady == 0)
				{
					MchInf.timeNostartChuGou++;
					if (MchInf.timeNostartChuGou >= TestModeInf.TIMENOSTARTCHUGOU) // 10min Êú?ÂºÄÂß?
					{
						MchInf.bFunChuGou = 0;
						MchInf.LEDDisp[0] = LEDCLOSE;
						MchInf.LEDDisp[1] = LEDCLOSE;
						ModeState = MODEWAIT;
						MchInf.timeWaitNoKey = 0;
					}
				}
				if ((MchInf.bPumpChugou) && (MchInf.bChugouYeWei == 0)) // …¡À∏Ã·–—
				{
					MchInf.RGBMode = RGB_WHITE;
					if (MchInf.nCalTimeChugouIcon < 3)
					{
						MchInf.ntimeslighChugouIcon++;
						if (MchInf.ntimeslighChugouIcon < 50 / 2)
						{
							bIConChuGou = 1;
							bIConStart = 1;
							MchInf.LEDDisp[0] = LED_ZIMU_L;
							MchInf.LEDDisp[1] = 0;
						}
						else
						{
							bIConChuGou = 0;
							bIConStart = 0;
							MchInf.LEDDisp[0] = LEDCLOSE;
							MchInf.LEDDisp[1] = LEDCLOSE;
						}
						if (MchInf.ntimeslighChugouIcon > 100 / 2)
						{
							MchInf.ntimeslighChugouIcon = 0;
							MchInf.nCalTimeChugouIcon++;
						}
					}
					else
					{
						bIConChuGou = 0;
						bIConStart = 0;
						MchInf.LEDDisp[0] = LED_ZIMU_L;
						MchInf.LEDDisp[1] = 0;
					}
				}
				else
				{
					MchInf.LEDDisp[0] = LEDCLOSE;
					MchInf.LEDDisp[1] = LEDCLOSE;
					bDarkstart = 1;
					bDarkChugou = 1;
					MchInf.RGBMode = RGB_WHITE;
				}
			}
			else
			{
				MchInf.timeNostartChuGou = 0;
				f_B1Light();
			}

			if (MchInf.bFunChuGouReady == 1)
			{
				if (MchInf.timeRmdChuGou == 0)
				{
					MchInf.bFunPaiShui = 1;
					if ((MchInf.WaterLV & 0x07) == 0) // Ê∞¥ÊéíÂÆ?
					{

						MchInf.bFunChuGou = 0; //
						MchInf.bFunChuGouStart = 0;
						MchInf.bFunChuGouReady = 0;
						ModeState = MODEWAIT;
						MchInf.timeWaitNoKey = 0;
						MchInf.zhengqijiworktimesum = 0;
						MchInf.bFunAlamChuGou = 0;
						MchInf.bFunAlamChuGouAgain = 0;
						// MchInf.timesAlamChuGouAgain = 0;
						MchInf.bFlagWriteFlash = 1;
					}
					bIConStart = 0;
					MchInf.LEDDisp[0] = LEDCLOSE;
					MchInf.LEDDisp[1] = LEDCLOSE;
					bIconB1 = 1;
					bDarkB1 = 1;
					MchInf.RGBMode = RGB_WHITE;
				}
				else
				{
					bIConStart = 0;

					MchInf.LEDDisp[0] = MchInf.timeRmdChuGou;
					MchInf.LEDDisp[1] = LED_ZIMU_h;

					if (MchInf.bManuStartChugou)
					{ // MchInf.RGBMode = RGB_RED;
						f_B1Light();
					}

					if ((MchInf.bFunPaiShui == 0) && (MchInf.bFunPaiShuiMust == 0))
					{
						/*						if(((MchInf.WaterLV&0x07) == 0)||((MchInf.WaterLV&0x07) == 0x01)||((MchInf.WaterLV&0x07) == 0x03))
												{
													MchInf.bAddWater = 1;
												}
												else */
						if ((MchInf.WaterLV & 0x07) == 0x07)
						{
							MchInf.bAddWater = 0;
							// MchInf.Relay |= 0x700;
						}
						else
							MchInf.bAddWater = 1;

						if ((bflagUp98du == 0) && (MchInf.TmprWater < 98) && ((MchInf.WaterLV & 0x07) >= 0x03)) // ‰∏?Ê∞¥‰Ωç‰ª•‰∏äÂä†Á??
						{
							MchInf.Relay |= 0x700;
						}
						else if ((MchInf.TmprWater >= 98) && ((MchInf.WaterLV & 0x07) >= 0x03) && (bflagUp98du == 0)) // 98
						{
							//							MchInf.bFunHot = 0;
							MchInf.Relay &= ~0x700;

							MchInf.nCalTimeChuGouSleep = 0;

							if (MchInf.bFunChugouAutoOrManu == 0) // ◊‘∂Ø”–≥˝π∏“∫
							{
								if (MchInf.bChugouYeWei == 1)
								{
									MchInf.nCaltimesAutoChugou = 0;
									// MchInf.bFlagWriteFlash = 1;
									MchInf.bPumpChugouYe = 1;
									MchInf.bFunChuGou = 1;
									MchInf.bFunChuGouStart = 1;
									MchInf.bFunChuGouReady = 1;
									MchInf.bFunAlamChuGou = 0;
									MchInf.RGBMode = RGB_RED;
								}
							}
							else if ((MchInf.bPumpChugou) && (MchInf.bChugouYeWei) && (MchInf.bFunChuGouCal == 0))
								MchInf.bPumpChugouYe = 1;

							MchInf.bFunChuGouStart = 1;
							MchInf.bFunChuGouCal = 1;

							bAutoChugou = 0;

							MchInf.RGBMode = RGB_RED;

							bflagUp98du = 1;
						}
						else if ((bflagUp98du) && (MchInf.TmprWater < 90))
						{
							//							bflagUp98du = 0;
						}
					}
				}
			}

			//			if(MchInf.bPumpChugouYe)
			//			{
			//				if(MchInf.timePumpchugouye < 1200)
			//					MchInf.timePumpchugouye++;
			//				if(MchInf.timePumpchugouye >=1000/2)//10s
			//				{
			//					MchInf.bPumpChugouYe = 0;
			//					MchInf.timePumpchugouye = 0;
			//				}
			//			}
			//			if(MchInf.bFunChuGouCal)
			{
				if ((MchInf.LED2State == 0) && (MchInf.bflagBleConnState != 2) && (MchInf.RGBMode1 == RGB_CLOSE))
				{
					if (MchInf.nCalTimeChuGouSleep < TestModeInf.TIMECHUGOUSLEEP) // 10min
						MchInf.nCalTimeChuGouSleep++;
					else
						MchInf.bFunChuGouSleep = 1;
				}
				else
					MchInf.nCalTimeChuGouSleep = 0;
			}

			if (MchInf.bFunChuGouSleep)
			{
				MchInf.RGBMode1 = RGB_CLOSE;
				//				MchInf.RGBMode = RGB_RED;
				bIconAdd = 0;
				bIconJIan = 0;
				bIconLED2 = 0;
				bIconSound = 0;
				bIConStart = 0;
				bIconB2 = 0;
				bIconB1 = 0;
				bDarkShumaguan = 0;
				bDarkSleep = 0;
			}
			else
			{
				//				MchInf.RGBMode1 = RGB_WHITE;
				//				bIconAdd = 1;
				//				bIconJIan = 1;
				//				bIconSound = 1;
				//
				//				if(MchInf.LED2State)
				//					bIconLED2 = 1;
			}
		}
		else if ((MchInf.bFunAlamChuGou) && (MchInf.bFunZhengfa == 0)) // Ê≠£Âú®Èô§Âû¢‰∏çÊèêÈÜ?
		{
			MchInf.LEDDisp[0] = LEDCLOSE;
			MchInf.LEDDisp[1] = LEDCLOSE;

			f_Disp_yewei();
			f_Deal_ChugouStart();

			// ÔøΩÔøΩÀ∏30s
			if (MchInf.nCalTimeChugouIcon < 30)
			{
				MchInf.ntimeslighChugouIcon++;
				if (MchInf.ntimeslighChugouIcon < 50 / 2)
					bIConChuGou = 1;
				else
					bIConChuGou = 0;
				if (MchInf.ntimeslighChugouIcon > 100 / 2)
				{
					MchInf.ntimeslighChugouIcon = 0;
					MchInf.nCalTimeChugouIcon++;
				}
			}
			else
			{
				if ((MchInf.bFunChuGouReady == 0) && (MchInf.bFunChugouAutoOrManu)) //  ÷∂Ø≥˝π∏30s≤ªø™ ºΩ¯»Î¥˝ª˙
				{
					MchInf.bFunAlamChuGou = 0;
					ModeState = MODEWAIT;
					MchInf.timeWaitNoKey = 0;
				}
				bIConChuGou = 0;
			}
		}
		else if ((MchInf.bFunAlamChuGouAgain) && (MchInf.bFunZhengfa == 0))
		{

			f_Deal_ChugouStart();

			// ÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÀ∏1min
			if (MchInf.nCalTimeChugouIcon < 60 / 2)
			{
				MchInf.ntimeslighChugouIcon++;
				if (MchInf.ntimeslighChugouIcon < 25 / 2)
				{
					bIConChuGou = 1;
					MchInf.LEDDisp[0] = LED_ZIMU_C;
					MchInf.LEDDisp[1] = LED_ZIMU_L;
				}
				else if (MchInf.ntimeslighChugouIcon < 50 / 2)
				{
					bIConChuGou = 0;
					MchInf.LEDDisp[0] = LEDCLOSE;
					MchInf.LEDDisp[1] = LEDCLOSE;
				}
				else if (MchInf.ntimeslighChugouIcon < 100 / 2)
				{
					bIConChuGou = 1;
					MchInf.LEDDisp[0] = LED_ZIMU_L;
					MchInf.LEDDisp[1] = 0;
				}
				else if (MchInf.ntimeslighChugouIcon < 150 / 2)
				{
					bIConChuGou = 0;
					MchInf.LEDDisp[0] = LEDCLOSE;
					MchInf.LEDDisp[1] = LEDCLOSE;
				}
				else if (MchInf.ntimeslighChugouIcon > 200 / 2)
				{
					MchInf.ntimeslighChugouIcon = 0;
					MchInf.nCalTimeChugouIcon++;
				}
			}
			else
			{
				f_Disp_yewei();
				//				bIConChuGou = 1;
				//				MchInf.LEDDisp[0]  = LED_ZIMU_C;
				//				MchInf.LEDDisp[1]  = LED_ZIMU_L;
				//				MchInf.bFunAlamChuGouAgain = 0;
			}
		}
	}

	//***********************************
	MchInf.bErrGuZhang = 0;
	if ((MchInf.TmprHouse < ERR_LOWTEMPER) || (MchInf.bErrorTmpr & 0x01))
	{
		MchInf.LEDDisp[0] = LED_FUHAO;
		MchInf.LEDDisp[1] = LED_ZIMU_L;
		MchInf.Relay &= ~0x700; // ÂÖ≥Âä†ÁÉ?
		MchInf.bErrGuZhang = 1;
	}
	else if ((MchInf.TmprHouse > ERR_HIGHTEMPER) || (MchInf.bErrorTmpr & 0x02))
	{
		MchInf.LEDDisp[0] = LED_FUHAO;
		MchInf.LEDDisp[1] = LED_ZIMU_H;
		MchInf.Relay &= ~0x700; // ÂÖ≥Âä†ÁÉ?
		//				MchInf.bAddWater = 0;
		MchInf.bErrGuZhang = 1;
	}
	if ((MchInf.TmprWater > ERR_WATERTEMPER) || (MchInf.bErrorTmpr & 0x0C))
	{

		MchInf.bErrTmprWaterHigh = 1;
		MchInf.bErrGuZhang = 1;
	}
	else if (MchInf.TmprWater < 100)
		MchInf.bErrTmprWaterHigh = 0;

	if (MchInf.bErrTmprWaterHigh)
	{
		MchInf.LEDDisp[0] = 0;
		MchInf.LEDDisp[1] = LED_ZIMU_H;
		MchInf.bFunHot = 0;
		MchInf.Relay &= ~0x700; // ÂÖ≥Âä†ÁÉ?
		MchInf.bErrGuZhang = 1;
	}

	if (MchInf.bFunWeixiuDisp)
	{
		//		MchInf.bDispDark =1;
		//		f_Disp_WaterLV();
		//		bIconWaterLOW = 1;
		//		bIconWaterMID = 1;
		//		bIconWaterHIGH = 1;
		//		bIconWater = 1;

		if ((MchInf.WaterLV & 0x07) == 1)
		{
			bIconWaterLOW = 1;
			bDarkWaterLow = 1;
		}
		else if ((MchInf.WaterLV & 0x07) == 3)
		{
			bIconWaterLOW = 1;
			bIconWaterMID = 1;
			bDarkWaterMid = 1;
			bDarkWaterLow = 1;
		}
		else if ((MchInf.WaterLV & 0x07) == 7)
		{
			bIconWaterLOW = 1;
			bIconWaterMID = 1;
			bIconWaterHIGH = 1;
			bDarkWaterHigh = 1;
			bDarkWaterMid = 1;
			bDarkWaterLow = 1;
		}

		f_Disp_TprLV();

		//	bIconOut = 1;
		//	bIconWater = 1;
		//	bIconIn = 1;

		if ((MchInf.bFunPaiShui) || (MchInf.bFunPaiShuiMust))
		{
			bIconOut = 1;
			bIconWater = 1;
			bDarkWater = 1;
			bDarkWaterOut = 1;
		}
		if (MchInf.bAddWater || MchInf.bFirstOpen)
		{
			bIconIn = 1;
			bDarkWaterIn = 1;
			bIconWater = 1;
			bDarkWater = 1;
		}

		if (MchInf.bFunZhengfa == 0)
		{
			bIconLV3 = 0;
			bIconLV2 = 0;
			bIconLV1 = 0;
			bIconTmr = 0;
			bDarkTmr = 0;
		}
		/*
				if((!MchInf.bFunPaiShui)&&(!MchInf.bFunPaiShuiMust)&&(!MchInf.bAddWater))
				{
					bDarkWaterOut= 1;
					bDarkWaterIn= 1;
					bDarkWater= 1;
				}
		*/
	}
	else if (MchInf.bFunWeixiu)
	{

		MchInf.RGBMode = RGB_WHITE;
		if (MchInf.ntimeslightAlamChugouAgain < 3)
		{
			MchInf.calAlamChugouAgain++;
			if (MchInf.calAlamChugouAgain < 50)
			{
				MchInf.LEDDisp[0] = LED_ZIMU_C;
				MchInf.LEDDisp[1] = LED_ZIMU_L;
			}
			else if (MchInf.calAlamChugouAgain < 100)
			{
				MchInf.LEDDisp[0] = MchInf.timesAlamChuGouAgain / 10;
				MchInf.LEDDisp[1] = MchInf.timesAlamChuGouAgain % 10;
			}
			else
			{
				MchInf.ntimeslightAlamChugouAgain++;
				MchInf.calAlamChugouAgain = 0;
			}
		}
		else
			MchInf.bFunWeixiu = 0;
	}

	//	MchInf.Relay = 0;

	if (MchInf.bErrWaterLv)
		return;

	if (MchInf.bFirstOpen == 1)
	{

		if ((MchInf.WaterLV & 0x07) == 0x07)
		{
			MchInf.bFirstOpen = 0;
		}
		else if (((MchInf.WaterLV & 0x07) == 0x00) || ((MchInf.WaterLV & 0x07) == 0x01) || ((MchInf.WaterLV & 0x07) == 0x03))
		{
			MchInf.Relay |= 0x01;
		}
	}
	else if (MchInf.bAddWater)
	{
		if ((MchInf.WaterLV & 0x07) == 0x07) // º”µΩ∏ﬂÀÆŒª«ø÷∆Õ£÷πº”ÀÆ
		{
			MchInf.bAddWater = 0;
			MchInf.Relay &= ~0x01;
		}
		else
			MchInf.Relay |= 0x01;
	}

	//	if((MchInf.bFunHot)&&(MchInf.bErrorTmpr == 0))
	//		MchInf.Relay |= 0x02;

	if (MchInf.bFunPaiShui || MchInf.bFunPaiShuiMust)
	{
		MchInf.Relay &= ~0x01;
		MchInf.bAddWater = 0;
		bIconLV3 = 0;
		bIconLV2 = 0;
		bIconLV1 = 0;
		bIconTmr = 0;
		bDarkTmr = 0;
		bIConChuGou = 0;
		bDarkB1 = 1;
		//		bIconB1 = 1;
		MchInf.LEDDisp[0] = LEDCLOSE;
		MchInf.LEDDisp[1] = LEDCLOSE;

		if ((MchInf.WaterLV & 0x07) == 0)
		{
			MchInf.Relay |= 0x04;
			if (MchInf.CalPaiShuiMust < 16000)
				MchInf.CalPaiShuiMust++;
#ifdef TEST_SUOSHI
			if (MchInf.CalPaiShuiMust > 1000) // 150*100/2)
#else
			if (MchInf.CalPaiShuiMust > 150 * 100 / 2)
#endif
			{
				MchInf.bFunPaiShuiMust = 0;
				MchInf.CalPaiShuiMust = 0;
				MchInf.bFunPaiShui = 0;
				//				if((MchInf.LED2State == 0)&&(MchInf.bflagBleConnState != 2)&&(MchInf.RGBMode1 == RGB_CLOSE))
				//				{
				//					ModeState = MODESLEEP;
				//					MchInf.blekey |=0x100;
				//				}

				//				MchInf.RGBMode = RGB_WHITE;	//
				MchInf.Relay &= ~0x04;
			}
		}
		else
		{
			MchInf.Relay |= 0x04;
			MchInf.Relay &= ~0x701;
			//			MchInf.Relay &= ~0x01;
			MchInf.CalPaiShuiMust = 0;
		}
	}

	if (MchInf.LED2State)
		MchInf.Relay |= 0x08;

	//	if(MchInf.bFunZhengqiOpen)
	//		MchInf.Relay |= 0x10;

	if (MchInf.bPumpChugouYe)
	{
		if (MchInf.timePumpchugouye < 1200)
			MchInf.timePumpchugouye++;
		if (MchInf.timePumpchugouye >= 1000 / 2) // 10s
		{
			MchInf.bPumpChugouYe = 0;
			MchInf.timePumpchugouye = 0;
		}
	}

	if (MchInf.bPumpChugouYe)
		MchInf.Relay |= 0x20;

	if ((MchInf.bErrGuZhang == 0) && ((MchInf.LEDDisp[1] == LED_FUHAO) || (MchInf.LEDDisp[1] == LED_ZIMU_H)))
	{
		//		MchInf.Relay &= ~0x700;//ÂÖ≥Âä†ÁÉ?
		MchInf.LEDDisp[0] = LEDCLOSE;
		MchInf.LEDDisp[1] = LEDCLOSE;
	}
}
