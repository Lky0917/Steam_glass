#include "HeadInclude.h"
#include "Disp_const.h"

TYPE_INT  IconDisp;
TYPE_INT  IconDisp1;
unsigned char RGBModeLast = 0;
unsigned char bflagUp98du = 0;

unsigned char DispAct[6]= {0};
#define  LIGHTALL     10
#define  LIGHTDARK    5
unsigned char DarkCal[21] = {0};//0  �����  1 Ӳ��  2 ����


byte_def    nDark_Flag;
#define		 bDarkShumaguan		 	 	nDark_Flag.m_bit.b0
#define		 bDarkYingdu				nDark_Flag.m_bit.b1
#define		 bDarkChugou	 	 	 	nDark_Flag.m_bit.b2
#define		 bDarkstart 			 	nDark_Flag.m_bit.b3
#define		 bDarkSleep 				nDark_Flag.m_bit.b4
#define		 bDarkWaterLow  			nDark_Flag.m_bit.b5
#define		 bDarkWaterMid			    nDark_Flag.m_bit.b6 
#define		 bDarkJian  		 	 	nDark_Flag.m_bit.b7
#define      Dark_flag                  nDark_Flag.m_byte

byte_def    nDark_Flag1;
#define		 bDarkAdd   				nDark_Flag1.m_bit.b0
#define		 bDarkMusic 				nDark_Flag1.m_bit.b1
#define		 bDarkLED2  	 	 	 	nDark_Flag1.m_bit.b2
#define		 bDarkWaterHigh			 	nDark_Flag1.m_bit.b3
#define		 bDarkWaterOut 				nDark_Flag1.m_bit.b4
#define		 bDarkWaterIn   			nDark_Flag1.m_bit.b5
#define		 bDarkWater 			    nDark_Flag1.m_bit.b6 
#define		 bDarkWaterLV1 			    nDark_Flag1.m_bit.b7 

#define      Dark_flag1                  nDark_Flag1.m_byte

byte_def    nDark_Flag2;
#define		 bDarkWaterLv2 				nDark_Flag2.m_bit.b0
#define		 bDarkTmr   				nDark_Flag2.m_bit.b1
#define		 bDarKWaterLv3 	 	 	 	nDark_Flag2.m_bit.b2
#define		 bDarkB2    			 	nDark_Flag2.m_bit.b3
#define		 bDarkB1    				nDark_Flag2.m_bit.b4
#define      Dark_flag2                  nDark_Flag2.m_byte


void f_Disp_saomiao(void)
{
	unsigned char i;
static unsigned char nCalseg = 0,nCalTime = 0;

  SEG1_OFF_IO;
  SEG2_OFF_IO;
  SEG3_OFF_IO;
  SEG4_OFF_IO;
  SEG5_OFF_IO;
  SEG6_OFF_IO;
  SEG7_OFF_IO;
  SEG8_OFF_IO;

  GRID1_OFF_IO;
  GRID2_OFF_IO;
  GRID3_OFF_IO;
  GRID4_OFF_IO;
  GRID5_OFF_IO;
  GRID6_OFF_IO;
//	for(i=0;i<6;i++)
//		DispAct[i] = 0xff;
	
  switch(nCalseg)
  {
	case 0:
		if(nCalTime < DarkCal[0])
		{
			if(DispAct[0]&0x01)
				SEG1_ON_IO;
			if(DispAct[0]&0x02)
				SEG2_ON_IO;
	 		if(DispAct[0]&0x04)
		 		SEG3_ON_IO;
	  		if(DispAct[0]&0x08)
		  		SEG4_ON_IO;
			if(DispAct[0]&0x10)
		  		SEG5_ON_IO;
	  		if(DispAct[0]&0x20)
		  		SEG6_ON_IO;
	  		if(DispAct[0]&0x40)
		  		SEG7_ON_IO;
	  		if(DispAct[0]&0x80)
		  		SEG8_ON_IO;
		}
		GRID1_ON_IO;
		break;
  case 1:
	if(nCalTime < DarkCal[0])
	{
  		
	  if(DispAct[1]&0x01)
		  SEG1_ON_IO;
	  if(DispAct[1]&0x02)
		  SEG2_ON_IO;
	  if(DispAct[1]&0x04)
		  SEG3_ON_IO;
	  if(DispAct[1]&0x08)
		  SEG4_ON_IO;
	  if(DispAct[1]&0x10)
		  SEG5_ON_IO;
	  if(DispAct[1]&0x20)
		  SEG6_ON_IO;
	  if(DispAct[1]&0x40)
		  SEG7_ON_IO;
	  if(DispAct[1]&0x80)
		  SEG8_ON_IO;
	}
	  GRID2_ON_IO;
	  break;
  case 2: 
	  if((DispAct[2]&0x01)&&(nCalTime < DarkCal[1]))//yingdu
		  SEG1_ON_IO;
	  if((DispAct[2]&0x02)&&(nCalTime < DarkCal[2]))//chugou
		  SEG2_ON_IO;
	  if((DispAct[2]&0x04)&&(nCalTime < DarkCal[3]))//start
	  {
	  		SEG3_ON_IO;
	  //if(DispAct[2]&0x08)
		  SEG4_ON_IO;
	  }
	  if((DispAct[2]&0x10)&&(nCalTime < DarkCal[4]))//sleep
	  {	  
	      SEG5_ON_IO;
	  //if(DispAct[2]&0x20)
		  SEG6_ON_IO;
	  }
	  if((DispAct[2]&0x40)&&(nCalTime < DarkCal[5]))//waterlow
		  SEG7_ON_IO;
	  if((DispAct[2]&0x80)&&(nCalTime < DarkCal[6]))//watermid
		  SEG8_ON_IO;
	  GRID3_ON_IO;
	  break;
  case 3: 
	  if((DispAct[3]&0x01)&&(nCalTime < DarkCal[1]))//yingdu  2
		  SEG1_ON_IO;
	  if((DispAct[3]&0x02)&&(nCalTime < DarkCal[1]))
		  SEG2_ON_IO;
	  if((DispAct[3]&0x04)&&(nCalTime < DarkCal[1]))
	   	  SEG3_ON_IO;
	  if((DispAct[3]&0x08)&&(nCalTime < DarkCal[7]))//jian
		  SEG4_ON_IO;

	  if((DispAct[3]&0x10)&&(nCalTime < DarkCal[8]))//jia
	   	  SEG5_ON_IO;
	  if((DispAct[3]&0x20)&&(nCalTime < DarkCal[9]))//music
	  {	  
	  	  SEG6_ON_IO;	  
		  SEG7_ON_IO;
	  }
	  if((DispAct[3]&0x80)&&(nCalTime < DarkCal[10]))//LED2
		  SEG8_ON_IO;
	  GRID4_ON_IO;
	  break;
  case 4: 
	  if((DispAct[4]&0x01)&&(nCalTime < DarkCal[11]))//waterhigh
		  SEG1_ON_IO;
	  if((DispAct[4]&0x02)&&(nCalTime < DarkCal[12]))//waterout
		  SEG2_ON_IO;
	  if((DispAct[4]&0x04)&&(nCalTime < DarkCal[13]))//waterin
		  SEG3_ON_IO;
	  if((DispAct[4]&0x08)&&(nCalTime < DarkCal[14]))//water
		  SEG4_ON_IO;
	  if((DispAct[4]&0x10)&&(nCalTime < DarkCal[15]))//LV1
		  SEG5_ON_IO;
	  if((DispAct[4]&0x20)&&(nCalTime < DarkCal[16]))//LV2
		  SEG6_ON_IO;
	  if((DispAct[4]&0x40)&&(nCalTime < DarkCal[17]))//tmr
		  SEG7_ON_IO;
	  if((DispAct[4]&0x80)&&(nCalTime < DarkCal[18]))//LV3
		  SEG8_ON_IO;
	  GRID5_ON_IO;
	  break;
  case 5: 
	  if((DispAct[5]&0x01)&&(nCalTime < DarkCal[19]))//B2
	  {	  SEG1_ON_IO;
	  //if(DispAct[5]&0x02)
		  SEG2_ON_IO;
	  }
	  if((DispAct[5]&0x04)&&(nCalTime < DarkCal[20]))//B1
	  {
	  	SEG3_ON_IO;
	  //if(DispAct[5]&0x08)
		  SEG4_ON_IO;
	  	}
	  GRID6_ON_IO;
	  break;
	default:break;
  }
  nCalseg++;
  if(nCalseg > 5)
  	nCalseg = 0;
  nCalTime++;
  if(nCalTime >= 10)
  	nCalTime = 0;
}

void f_Deal_Seg(void)
{
	unsigned char i;
	static unsigned char addwaterstate = 0,nCntTime = 0;

	for(i = 0;i< 10;i++)
		MchInf.Dispbuffer[i] = 0;

//	nIconDisp = 0;
//	nIconDisp1 = 0;
	
//	bIconLED2 = 1;
	{
		MchInf.Dispbuffer[0] = nTab_Number[MchInf.LEDDisp[0]];  //  1A   2B  4C  8D  10E  20F  40G  80 DP
		MchInf.Dispbuffer[1] = 0x00;
		MchInf.Dispbuffer[2] = nTab_Number[MchInf.LEDDisp[1]];  //  1A   2B  4C  8D  10E  20F  40G  80 DP
		MchInf.Dispbuffer[3] = 0x00;
	}

	if(bIConWaterHard1)
		MchInf.Dispbuffer[4] |= 0x01;
	if(bIConChuGou)
		MchInf.Dispbuffer[4] |= 0x02;
	if(bIConStart)
	{
		MchInf.Dispbuffer[4] |= 0x04;
		MchInf.Dispbuffer[4] |= 0x08;
	}
	if(bIConSleep)
	{
		MchInf.Dispbuffer[4] |= 0x10;
		MchInf.Dispbuffer[4] |= 0x20;
	}
	if(bIconWaterLOW)
		MchInf.Dispbuffer[4] |= 0x40;
	if(bIconWaterMID)
		MchInf.Dispbuffer[4] |= 0x80;

	MchInf.Dispbuffer[5] = 0x00;

	if(bIConWaterHard2)
		MchInf.Dispbuffer[6] |= 0x01;
	if(bIConWaterHard3)
		MchInf.Dispbuffer[6] |= 0x02;
	
	if(bIConWaterHard4)
		MchInf.Dispbuffer[6] |= 0x04;
	if(bIconJIan)
		MchInf.Dispbuffer[6] |= 0x08;	
	if(bIconAdd)
		MchInf.Dispbuffer[6] |= 0x10;
	if(bIconSound)
	{	
		MchInf.Dispbuffer[6] |= 0x20;
		MchInf.Dispbuffer[6] |= 0x40;
	}
	if(bIconLED2)
		MchInf.Dispbuffer[6] |= 0x80;

	
	MchInf.Dispbuffer[7] = 0x00;

	if(bIconWaterHIGH)
		MchInf.Dispbuffer[8] |= 0x01;
	
	if(bIconOut)
		MchInf.Dispbuffer[8] |= 0x02;	
	if(bIconIn)
		MchInf.Dispbuffer[8] |= 0x04;

	if(bIconWater)
		MchInf.Dispbuffer[8] |= 0x08;

	if(bIconLV1)
		MchInf.Dispbuffer[8] |= 0x10;	
	if(bIconLV2)
		MchInf.Dispbuffer[8] |= 0x20;	
	if(bIconTmr)
		MchInf.Dispbuffer[8] |= 0x40;
	if(bIconLV3)
		MchInf.Dispbuffer[8] |= 0x80;
	
	if(MchInf.RGBMode1 != RGB_CLOSE)
		MchInf.Dispbuffer[9] |= 0x03;
	
	if(MchInf.bflagB1White)
		MchInf.Dispbuffer[9] |= 0x0C;
	
	

//	if(MchInf.bDispDark)
//		TM1620B_work(MchInf.Dispbuffer,TM1628_CMD_DARK);
//	else
//		TM1620B_work(MchInf.Dispbuffer,TM1628_CMD_DISP);
INTERRUPT_ALL_CLOSE;
	if(bDarkShumaguan)
		DarkCal[0] = LIGHTDARK;
	else
		DarkCal[0] = LIGHTALL ;

	if(bDarkYingdu)
		DarkCal[1] = LIGHTDARK;
	else
		DarkCal[1] = LIGHTALL ;

	if(bDarkChugou)
		DarkCal[2] = LIGHTDARK;
	else
		DarkCal[2] = LIGHTALL ;

	if(bDarkstart)
		DarkCal[3] = LIGHTDARK;
	else
		DarkCal[3] = LIGHTALL ;	

	if(bDarkSleep)
		DarkCal[4] = LIGHTDARK;
	else
		DarkCal[4] = LIGHTALL ;	

	if(bDarkWaterLow)
		DarkCal[5] = LIGHTDARK;
	else
		DarkCal[5] = LIGHTALL ;	

	if(bDarkWaterMid)
		DarkCal[6] = LIGHTDARK;
	else
		DarkCal[6] = LIGHTALL ;	

	if(bDarkJian)
		DarkCal[7] = LIGHTDARK;
	else
		DarkCal[7] = LIGHTALL ;	

	if(bDarkAdd)
		DarkCal[8] = LIGHTDARK;
	else
		DarkCal[8] = LIGHTALL ;	

	if(bDarkMusic)
		DarkCal[9] = LIGHTDARK;
	else
		DarkCal[9] = LIGHTALL ;	

	if(bDarkLED2)
		DarkCal[10] = LIGHTDARK;
	else
		DarkCal[10] = LIGHTALL ;	

	if(bDarkWaterHigh)
		DarkCal[11] = LIGHTDARK;
	else
		DarkCal[11] = LIGHTALL ;

	if(bDarkWaterOut)
		DarkCal[12] = LIGHTDARK;
	else
		DarkCal[12] = LIGHTALL ;

	if(bDarkWaterIn)
		DarkCal[13] = LIGHTDARK;
	else
		DarkCal[13] = LIGHTALL ;	

	if(bDarkWater)
		DarkCal[14] = LIGHTDARK;
	else
		DarkCal[14] = LIGHTALL ;	

	if(bDarkWaterLV1)
		DarkCal[15] = LIGHTDARK;
	else
		DarkCal[15] = LIGHTALL ;	

	if(bDarkWaterLv2)
		DarkCal[16] = LIGHTDARK;
	else
		DarkCal[16] = LIGHTALL ;	

	if(bDarkTmr)
		DarkCal[17] = LIGHTDARK;
	else
		DarkCal[17] = LIGHTALL ;	

	if(bDarKWaterLv3)
		DarkCal[18] = LIGHTDARK;
	else
		DarkCal[18] = LIGHTALL ;	

	if(bDarkB2)
		DarkCal[19] = LIGHTDARK;
	else
		DarkCal[19] = LIGHTALL ;	

	if(bDarkB1)
		DarkCal[20] = LIGHTDARK;
	else
		DarkCal[20] = LIGHTALL ;	

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
						if(MchInf.bChugouYeWei == 0)//无除垢液闪烁
						{
						
							CalChuGouLight++;
							if(CalChuGouLight > 100/2)
							{
								CalChuGouLight = 0;
								if(MchInf.ntimeslight<10/2)
									MchInf.ntimeslight++;
							}
							
							if((CalChuGouLight < 50/2)&&(MchInf.ntimeslight  < 30))
							{
//								bIConStart = 0;
//								bIConChuGou = 0;
								MchInf.LEDDisp[0]  = LEDCLOSE;
								MchInf.LEDDisp[1]  = LEDCLOSE;
							}
							else
							{
								//bIConStart = 1;
//								bIConChuGou = 1;
								MchInf.LEDDisp[0]  = LED_ZIMU_L;
								MchInf.LEDDisp[1]  = 0;
							}
						
							if(MchInf.ntimeslight  > 30)
							{
								bIConStart = 0;
								bIConChuGou = 0;
								MchInf.LEDDisp[0]  = LED_ZIMU_L;
								MchInf.LEDDisp[1]  = 0;
							}
						}
//						else//有除垢液
//						{
//								bIConStart = 1;
//								bIConChuGou = 1;
//						}

}
void f_Disp_WaterLV(void)
{
	unsigned char temp;

	temp = MchInf.WaterLV&0x07 ;
			
	if(temp== 1)
		bIconWaterLOW = 1;
	else if(temp == 3 )
	{
		bIconWaterLOW = 1;
		bIconWaterMID = 1;
	}
	else if(temp == 7 )
	{
		bIconWaterLOW = 1;
		bIconWaterMID = 1;
		bIconWaterHIGH = 1;
	}
}

void f_Disp_TprLV(void)
{
		if(MchInf.TmrLV ==1)
		{
			bIconLV1 = 1;
			bIconTmr = 1;
		}
		else if(MchInf.TmrLV == 2)
		{
			bIconLV2 = 1;
			bIconLV1 = 1;
			bIconTmr = 1;

		}
		else if(MchInf.TmrLV == 3)
		{
			bIconLV3 = 1;	
			bIconLV2 = 1;
			bIconLV1 = 1;
			bIconTmr = 1;
		}
}
void f_Deal_ChugouStart(void)
{
			//有除垢泵自动除垢                                           //0 自动  1 手动
			if(((MchInf.bPumpChugou)&&(MchInf.bFunChugouAutoOrManu))||(MchInf.bFunChugouAutoOrManu==0))//有除垢泵
			{
				if(MchInf.nCaltimesAutoChugou< 3600*110)
					MchInf.nCaltimesAutoChugou++;
				if(MchInf.nCaltimesAutoChugou >= 2400)//1min  //3600*100/2)//1hour
				{

					MchInf.timeNostartChuGou = 0;
					MchInf.ntimeslight = 0;
					MchInf.timeRmdChuGou = 4;
					
				
					//if(MchInf.bChugouYeWei == 1)
					{							
					//	if(MchInf.bFunChuGouStart==0)
						{
							MchInf.nCaltimesAutoChugou = 0;
							//MchInf.bFlagWriteFlash = 1;
							MchInf.bPumpChugouYe  = 1;
						}					
					}
					
					if(MchInf.bChugouYeWei == 1)
					{
							MchInf.bFunChuGou = 1;
							MchInf.bFunChuGouStart = 1;
							MchInf.bFunAlamChuGou = 0;
							MchInf.bPumpChugouYe = 0;
					}

						
				}				
			}
			else
			{
				if(MchInf.bFunChuGouStart==0)
				{
						MchInf.nCaltimesAutoChugou = 0;
						MchInf.bFlagWriteFlash = 1;
						MchInf.bFunChuGouStart = 1;
				}				
			}
}
void f_Disp(void)
{
	static unsigned char SoundLast = 50,delaytime = 10;//
	static unsigned int  timelightB1 = 0;

	static unsigned int  nCal5sDisp = 0;
	static unsigned int  nCal30sBleConn = 0,Calblecontime = 0;
	unsigned char temp;
	nIconDisp = 0;
	nIconDisp1 = 0;
	MchInf.Relay = 0;
	Dark_flag = 0;
	Dark_flag1 = 0;
	Dark_flag2 = 0;
	
//		MchInf.WaterLV = 0x03;
//		MchInf.TmprWater = 96;
//		MchInf.TmprHouse = 38;

	if(ModeState == MODESLEEP)
	{
		MchInf.bDispDark = 1;
		bIConSleep = 1;
//		bIconZhengqi = 1;
		MchInf.RGBMode = RGB_CLOSE;
		MchInf.RGBMode1 = RGB_CLOSE;
		MchInf.LEDDisp[0]  = LEDCLOSE;
		MchInf.LEDDisp[1]  = LEDCLOSE;
		MchInf.bFunHot = 0;//����ֹͣ			
		MchInf.bAddWater = 0;//��ˮֹͣ
		MchInf.LED2State = 0;//�ص�
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
	else if(ModeState == MODEWAIT)
	{

		bIconLED = 1;
//		if(MchInf.LED2State)
		MchInf.bflagB1White = 1;	
		
		MchInf.RGBMode = RGB_WHITE;
//		MchInf.RGBMode1 = RGB_WHITE;
	
		bIconZhengqi = 1;
		bIconSound = 1;
		bIconAdd = 1;
		bIconJIan = 1;
		bIConSleep = 1;

		bDarkB1 = 1;
		bDarkMusic = 1;
		bDarkAdd = 1;
		bDarkJian = 1;
		bDarkSleep = 1;
		bDarkB2 = 1;
		
		
		if((MchInf.LED2State==0))
		{
			bIconLED2 = 1;
			bDarkLED2 = 1;

		}
		else
		{
			bIconLED2 = 1;
		}
		
		MchInf.LEDDisp[0]  = LEDCLOSE;
		MchInf.LEDDisp[1]  = LEDCLOSE;

		if((MchInf.LED2State == 0)&&(MchInf.MusicOn == 0)&&(MchInf.RGBMode1 == RGB_WHITE)&&(MchInf.RGBMode == RGB_WHITE))
		{
			if(MchInf.timeWaitNoKey > TestModeInf.TIMEWAITNOKEY)//2min  12000
			{
				ModeState = MODESLEEP;
				
			}
			else
			{	
				MchInf.timeWaitNoKey ++;
				if(MchInf.timeWaitNoKey >= 1000/2)
					MchInf.bDispDark = 1;
			}
		}
			
	}
	else if((ModeState == MODERUN)||(ModeState == MODEZANTING))
	{
//		nCal5sDisp++;

//		if(nCal5sDisp < 500/2)
		{
		MchInf.LEDDisp[0] = MchInf.TimeZhengQi/10;
		MchInf.LEDDisp[1] = MchInf.TimeZhengQi%10;	
		}
//		else if(nCal5sDisp < 1000/2)
//		{
//		MchInf.LEDDisp[0] = MchInf.TmprHouse/10;
//		MchInf.LEDDisp[1] = MchInf.TmprHouse%10;		
//		}
//		else
//			nCal5sDisp = 0;
		
		bIconLED = 1;
		bIconZhengqi = 1;
		

		bIconSound = 1;
//		bIconAdd = 1;
//		bIconJIan = 1;
		
		bIconLED2 = 1;

		if(MchInf.LED2State==0)
			bIconLED2 = 0;
		else
			bIconLED2 = 1;
/*  //B4闂�?
		if(MchInf.MusicOn)
		{
			Calblecontime++;
			if(Calblecontime < 50/2)
				bIconSound = 1;
			else if(Calblecontime < 100/2)
			{
				if(MchInf.bflagBleConnState == 0)//
					bIconSound = 0;
			}
			else
				Calblecontime = 0;
				
		}
		else
			Calblecontime = 0;
*/
		if(MchInf.MusicSound != SoundLast)
		{
			if(MchInf.MusicSound > SoundLast)
				bIconAdd =1;
			else if(MchInf.MusicSound < SoundLast)
				bIconJIan = 1;
			delaytime--;
			if(delaytime == 0)
			{
				delaytime = 10;
				SoundLast = MchInf.MusicSound;
			}
		}

//		bIconWater = 1;		
//		f_Disp_WaterLV();

		if(ModeState == MODERUN)
		{
//			RGBModeLast = ModeState;
			MchInf.bDispDark = 0;

			if(MchInf.TimeZhengQi !=0)
			{
				MchInf.bFunZhengfa = 1;//蒸汽工作�?
				if((MchInf.bFunPaiShui==0)&&(MchInf.bFunPaiShuiMust==0))
				{
					if(MchInf.WaterLV < 7)// 低于高水位以下就加水
					{
						MchInf.bAddWater = 1;
						MchInf.bFunHot = 0;
						
					}
					else if(MchInf.WaterLV == 0x07)//���и߶���
					{
						MchInf.bAddWater = 0;			
					}
				}
				else
				{
					MchInf.bAddWater = 0;	
				}
				MchInf.bFunZhengqiOpen = 1;//直接计时
//				if(MchInf.bAddWater)
//				{
//					bIconIn = 1;					
//				}			
				if(MchInf.WaterLV >= 3)//中水位以�?
				{
					
//					if(MchInf.TmprWater >= 95)
//					{
//							MchInf.bFunZhengqiOpen = 1;
//					}		
					MchInf.bFunPaiShui = 0;	
					
					if(MchInf.bErrorTmpr == 0)
					{
							MchInf.bFunHot = 1; //����
							if(MchInf.TmrLV==1)
								temp = 36;
							else if(MchInf.TmrLV==2)
								temp = 41;
							else 	if(MchInf.TmrLV==3)
								temp = 45;

							if(MchInf.TmprHouse<=temp)
								MchInf.Relay |= 0x700;
							else if(MchInf.TmprHouse ==(temp+1))
								MchInf.Relay |= 0x300;
							else if(MchInf.TmprHouse ==(temp+2))
								MchInf.Relay |= 0x100;
						}

					
//					if(((MchInf.TmrLV == 1)&&(MchInf.TmprHouse >= 36))||//36~39du
//						((MchInf.TmrLV == 2)&&(MchInf.TmprHouse >= 41))||//41~44du
//						((MchInf.TmrLV == 3)&&(MchInf.TmprHouse >= 45)))//45~48du
//					{
//						//MchInf.bFunZhengqiOpen = 0;//������ֹͣ����
//						MchInf.bDispDark = 1;
//						MchInf.bFunHot = 0;
//					}			
				}
			}
			else//结束
			{
				MchInf.bFunZhengfa = 0;
				if(MchInf.timePaiShuiCal <30*60*101)
						MchInf.timePaiShuiCal ++;	
				
#ifdef TEST_SUOSHI
				if(MchInf.timePaiShuiCal >= 30*100/2)//TestModeInf.TIMEPAISHUIRUN)
#else
				if(MchInf.timePaiShuiCal >= TestModeInf.TIMEPAISHUIRUN)
#endif
				{
					MchInf.bFunPaiShui = 1;
					if((MchInf.WaterLV&0x07) ==0)
					{
						//MchInf.bFunPaiShui = 0;
						//ModeState = MODEWAIT;	
						MchInf.RGBMode = RGB_WHITE;	
						MchInf.bFunChuGouEver	 = 1;//排水排完						
					}
				}
			}
		}
		else	if(ModeState == MODEZANTING)
		{
			MchInf.bDispDark = 1;			
			bIconWater = 0;
			MchInf.bFunHot = 0;//����ֹͣ			
			MchInf.bAddWater = 0;//��ˮֹͣ
			timelightB1++;
			if(timelightB1 > 50/2)
				MchInf.RGBMode = RGB_CLOSE;
			if(timelightB1 > 100/2)
			{
				MchInf.RGBMode = RGB_RED;
				timelightB1 = 0;
			}
	
			if(MchInf.timePaiShuiCal <60*60*101)
				MchInf.timePaiShuiCal ++;	
#ifdef  TEST_SUOSHI		
			if(MchInf.timePaiShuiCal >= 30*100/2)//)
#else
			if(MchInf.timePaiShuiCal >= TestModeInf.TIMEPAISHUIZANTING)
#endif
			{
				MchInf.bFunPaiShui = 1;
				if((MchInf.WaterLV&0x07) == 0)
				{
//					MchInf.bFunPaiShui = 0;
//					ModeState = MODEWAIT;	
//					MchInf.RGBMode = RGB_WHITE;	
//					MchInf.RGBMode1 = RGB_CLOSE;						
					MchInf.timePaiShuiCal	 = 0;		
					MchInf.bFunChuGouEver	 = 1;//排水排完				
				}
			}

			if((MchInf.TmprHouse >=36)&&(MchInf.TmprHouse <=39))
				MchInf.TmrLV =1;
			else if((MchInf.TmprHouse >=41)&&(MchInf.TmprHouse <=44))
				MchInf.TmrLV =2;
			else if((MchInf.TmprHouse >=45)&&(MchInf.TmprHouse <=48))
				MchInf.TmrLV =3;
				
		}
		
		if(MchInf.bFunChuGouEver)
		{
			MchInf.bFunChuGouEver = 0;
			MchInf.nCalTimeChugouIcon = 0;
			bflagUp98du = 0;
			switch(MchInf.WaterHardState)//排水完成判断是否提醒除垢
				{
					case 1: 
							if(MchInf.zhengqijiworktimesum >= TestModeInf.TIMEHARD1CHUGOUALAMAGAIN)
								MchInf.bFunAlamChuGouAgain = 1;
							else if(MchInf.zhengqijiworktimesum >= TestModeInf.TIMEHARD1CHUGOUALAM)
								MchInf.bFunAlamChuGou = 1;
							break;
					case 2: 
							if(MchInf.zhengqijiworktimesum >= TestModeInf.TIMEHARD2CHUGOUALAMAGAIN)
								MchInf.bFunAlamChuGouAgain = 1;
							else if(MchInf.zhengqijiworktimesum >=TestModeInf.TIMEHARD2CHUGOUALAM)
								MchInf.bFunAlamChuGou = 1;
							break;
					case 3: 
						  if(MchInf.zhengqijiworktimesum >= TestModeInf.TIMEHARD3CHUGOUALAMAGAIN)
								MchInf.bFunAlamChuGouAgain = 1;
							else if(MchInf.zhengqijiworktimesum >= TestModeInf.TIMEHARD3CHUGOUALAM)
								MchInf.bFunAlamChuGou = 1;
							break;
					case 4: 
							if(MchInf.zhengqijiworktimesum >= TestModeInf.TIMEHARD4CHUGOUALAMAGAIN)
								MchInf.bFunAlamChuGouAgain = 1;
							else if(MchInf.zhengqijiworktimesum >= TestModeInf.TIMEHARD4CHUGOUALAM)
								MchInf.bFunAlamChuGou = 1;
							break;
					default:break;
				}
				if(MchInf.bFunAlamChuGouAgain == 1)
					MchInf.timesAlamChuGouAgain++;
		}

		f_Disp_TprLV();

	}

	if(ModeState != MODESLEEP)
	{
		//设置硬度
		if(MchInf.bFunSetWtHard)
		{
				bIConStart = 0;
				bIConChuGou = 1;
				MchInf.timeNoSetWtHard++;
				if(MchInf.timeNoSetWtHard >= 1000/2)
				{
					MchInf.bFunSetWtHard = 0;
				}
				if(MchInf.WaterHardState == 1)
				{
					bIConWaterHard1 = 1;
				}
				else if(MchInf.WaterHardState == 2)
				{
					bIConWaterHard1 = 1;
					bIConWaterHard2 = 1;
				}
				else if(MchInf.WaterHardState == 3)
				{
					bIConWaterHard1 = 1;
					bIConWaterHard2 = 1;
					bIConWaterHard3 = 1;
				}
				else if(MchInf.WaterHardState == 4)
				{
					bIConWaterHard1 = 1;
					bIConWaterHard2 = 1;
					bIConWaterHard3 = 1;
					bIConWaterHard4 = 1;
				}
		}	
		else if((MchInf.bFunChuGou)&&(MchInf.bFunZhengfa ==0))
		{
			bIConStart = 1;
			bIConChuGou = 1;
			MchInf.LEDDisp[0] = MchInf.timeRmdChuGou;
			MchInf.LEDDisp[1] = LED_ZIMU_h;
//			MchInf.bFunChuGouEver = 1;

			if(MchInf.bFunChuGouStart == 0)
			{
				MchInf.LEDDisp[0] = LEDCLOSE;
				MchInf.LEDDisp[1] = LEDCLOSE;
				MchInf.timeNostartChuGou++;
				if(MchInf.timeNostartChuGou >= TestModeInf.TIMENOSTARTCHUGOU)//10min 未开�?
					MchInf.bFunChuGou = 0;	

/*
						if(MchInf.bChugouYeWei == 0)//无除垢液闪烁
						{
						
							CalChuGouLight++;
							if(CalChuGouLight > 100/2)
							{
								CalChuGouLight = 0;
								if(MchInf.ntimeslight<10/2)
									MchInf.ntimeslight++;
							}
							
							if((CalChuGouLight < 50/2)&&(MchInf.ntimeslight  < 3))
							{
								bIConStart = 0;
								bIConChuGou = 0;
								MchInf.LEDDisp[0]  = LEDCLOSE;
								MchInf.LEDDisp[1]  = LEDCLOSE;
							}
							else
							{
								bIConStart = 1;
								bIConChuGou = 1;
								MchInf.LEDDisp[0]  = LED_ZIMU_L;
								MchInf.LEDDisp[1]  = 0;
							}
						
							if(MchInf.ntimeslight  > 3)
							{
								bIConStart = 0;
								bIConChuGou = 0;
							}
						}
						else//有除垢液
						{
								bIConStart = 1;
								bIConChuGou = 1;
						}
*/								
			}
			else
			{
				MchInf.timeNostartChuGou = 0;

				//B1 闪烁 3 �?
				if(MchInf.ntimeslightZhengfaIcon < 3)//shanshuo
				{
					if(MchInf.nCalTimeZhengfaqiIcon < 50/2)
						MchInf.RGBMode = RGB_CLOSE;
					else if(MchInf.nCalTimeZhengfaqiIcon < 100/2)
						MchInf.RGBMode = RGB_RED;
					MchInf.nCalTimeZhengfaqiIcon++;
					if(MchInf.nCalTimeZhengfaqiIcon > 100/2)
					{
						MchInf.nCalTimeZhengfaqiIcon = 0;
						MchInf.ntimeslightZhengfaIcon++;
					}
				}
				else
					MchInf.RGBMode = RGB_RED;			
			}

			if(MchInf.bFunChuGouStart == 1)
			{
				if(MchInf.timeRmdChuGou == 0)
				{
					MchInf.bFunPaiShui = 1;
					if((MchInf.WaterLV&0x07) ==0)//水排�?
					{

						MchInf.bFunChuGou = 0; //
						MchInf.bFunChuGouStart = 0;
						
						 MchInf.zhengqijiworktimesum = 0;
						MchInf.bFunAlamChuGou = 0;
						MchInf.bFunAlamChuGouAgain = 0;
						//MchInf.timesAlamChuGouAgain = 0;
						MchInf.bFlagWriteFlash = 1;
					}
				}
				else
				{
					bIConStart = 0;

					if((MchInf.bFunPaiShui == 0)&&(MchInf.bFunPaiShuiMust == 0))
					{
						if(MchInf.WaterLV < 7)
						{
							MchInf.bAddWater = 1;
						}
						else if((MchInf.WaterLV&0x07) == 0x07)
						{
								MchInf.bAddWater = 0;
								//MchInf.Relay |= 0x700;
								
						}
						
						if((bflagUp98du == 0)&&(MchInf.TmprWater < 98)&&((MchInf.WaterLV&0x07) >= 0x03))//中水位以上加�?
						{
							MchInf.Relay |= 0x700;

						}						
						else if((MchInf.TmprWater >= 98)&&((MchInf.WaterLV&0x07) >= 0x03)&&(bflagUp98du==0))//98
						{
//							MchInf.bFunHot = 0;
							MchInf.Relay &= ~0x700;
							MchInf.bFunChuGouCal = 1;
							MchInf.nCalTimeChuGouSleep = 0;
//							MchInf.bPumpChugouYe = 1;
							bflagUp98du = 1;
						}
						else if((bflagUp98du)&&(MchInf.TmprWater < 90))
						{
							bflagUp98du = 0;
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
			if(MchInf.bFunChuGouCal)
			{
				if((MchInf.LED2State == 0)&&(MchInf.MusicOn == 0)&&(MchInf.RGBMode1 == RGB_WHITE))
				{
					if(MchInf.nCalTimeChuGouSleep < TestModeInf.TIMECHUGOUSLEEP)//10min
						MchInf.nCalTimeChuGouSleep++;
					else
						MchInf.bFunChuGouSleep = 1;
				}
			}

			if(MchInf.bFunChuGouSleep)
			{
				MchInf.RGBMode1 = RGB_CLOSE;
				bIconAdd = 0;
				bIconJIan = 0;
				bIconLED2 = 0;
				bIconSound = 0;
				bIConStart = 0;
			}
			else
			{
				MchInf.RGBMode1 = RGB_WHITE;
				bIconAdd = 1;
				bIconJIan = 1;
				bIconSound = 1;	
				
				if(MchInf.LED2State)
					bIconLED2 = 1;
				
			}
		}
		else if((MchInf.bFunAlamChuGou)&&(MchInf.bFunZhengfa ==0))//正在除垢不提�?
		{
			MchInf.LEDDisp[0]  = LEDCLOSE;
			MchInf.LEDDisp[1]  = LEDCLOSE;
			
			f_Disp_yewei();
			f_Deal_ChugouStart();	
			
			//��˸30s
			if(MchInf.nCalTimeChugouIcon < 30)
			{
				MchInf.ntimeslighChugouIcon++;
				if(MchInf.ntimeslighChugouIcon < 50/2)
					bIConChuGou = 1;
				else
					bIConChuGou = 0;
				if(MchInf.ntimeslighChugouIcon > 100/2)
				{
					MchInf.ntimeslighChugouIcon = 0;
					MchInf.nCalTimeChugouIcon++;
				}
			}
			else
				bIConChuGou = 1;
			
		}
		else
		if((MchInf.bFunAlamChuGouAgain)&&(MchInf.bFunZhengfa ==0))
		{
			
			f_Deal_ChugouStart();

			//������˸1min
			if(MchInf.nCalTimeChugouIcon < 60/2)
			{
				MchInf.ntimeslighChugouIcon++;
				if(MchInf.ntimeslighChugouIcon < 25/2)
				{
					bIConChuGou = 1;
					MchInf.LEDDisp[0]  = LED_ZIMU_C;
					MchInf.LEDDisp[1]  = LED_ZIMU_L;
				}
				else if(MchInf.ntimeslighChugouIcon < 50/2)
				{
					bIConChuGou = 0;
					MchInf.LEDDisp[0]  = LEDCLOSE;
					MchInf.LEDDisp[1]  = LEDCLOSE;
				}
				else if(MchInf.ntimeslighChugouIcon < 100/2)
				{
					bIConChuGou = 1;
					MchInf.LEDDisp[0]  = LED_ZIMU_L;
					MchInf.LEDDisp[1]  = 0;
				}
				else if(MchInf.ntimeslighChugouIcon < 150/2)
				{
					bIConChuGou = 0;
					MchInf.LEDDisp[0]  = LEDCLOSE;
					MchInf.LEDDisp[1]  = LEDCLOSE;
				}
				else	if(MchInf.ntimeslighChugouIcon > 200/2)
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
		if((MchInf.TmprHouse < ERR_LOWTEMPER)||(MchInf.bErrorTmpr&0x01))
		{
			MchInf.LEDDisp[0]  = LED_FUHAO;
			MchInf.LEDDisp[1]  = LED_ZIMU_L;
			MchInf.Relay &= ~0x700;//关加�?
			MchInf.bErrGuZhang = 1;
		}
		else if((MchInf.TmprHouse > ERR_HIGHTEMPER)||(MchInf.bErrorTmpr&0x02))
		{
			MchInf.LEDDisp[0]  = LED_FUHAO;
			MchInf.LEDDisp[1]  = LED_ZIMU_H;
			MchInf.Relay &= ~0x700;//关加�?
//				MchInf.bAddWater = 0;
			MchInf.bErrGuZhang = 1;
		}	
		if((MchInf.TmprWater > ERR_WATERTEMPER)||(MchInf.bErrorTmpr&0x0C))
		{

			MchInf.bErrTmprWaterHigh = 1;
			MchInf.bErrGuZhang = 1;
		}
		else if(MchInf.TmprWater <100)
			MchInf.bErrTmprWaterHigh = 0;
			
		if(MchInf.bErrTmprWaterHigh)
		{
			MchInf.LEDDisp[0]  = 0;
			MchInf.LEDDisp[1]  = LED_ZIMU_H;
			MchInf.bFunHot = 0;
			MchInf.Relay &= ~0x700;//关加�?
			MchInf.bErrGuZhang = 1;
		}

	if(MchInf.bFunWeixiuDisp)
	{
		MchInf.bDispDark =1;
		f_Disp_WaterLV();
		f_Disp_TprLV();
		if(MchInf.bFunPaiShui)
		{
			bIconOut = 1;
			bIconWater = 1;
		}
		else if(MchInf.bAddWater)
		{
			bIconIn = 1;
			bIconWater = 1;
		}
			
	}
	else if(MchInf.bFunWeixiu)
	{

		MchInf.RGBMode = RGB_WHITE;
		if(MchInf.ntimeslightAlamChugouAgain < 3)
		{		
			MchInf.calAlamChugouAgain++;
			if(MchInf.calAlamChugouAgain < 50)
			{
				MchInf.LEDDisp[0]  = LED_ZIMU_C;
				MchInf.LEDDisp[1]  = LED_ZIMU_L;
			}
			else if(MchInf.calAlamChugouAgain < 100)
			{
				MchInf.LEDDisp[0] = MchInf.timesAlamChuGouAgain/10;
				MchInf.LEDDisp[1]  = MchInf.timesAlamChuGouAgain%10;
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
	
	if(MchInf.bErrWaterLv)
		return;

	if(MchInf.bFirstOpen == 1)
	{
		MchInf.Relay |= 0x01;
		if(MchInf.WaterLV == 0x07)
			MchInf.bFirstOpen = 0;
	}
	else	if(MchInf.bAddWater)
		MchInf.Relay |= 0x01;

//	if((MchInf.bFunHot)&&(MchInf.bErrorTmpr == 0))
//		MchInf.Relay |= 0x02;

	if(MchInf.bFunPaiShui||MchInf.bFunPaiShuiMust)
	{		
		if((MchInf.WaterLV&0x07) ==0)
		{
			MchInf.Relay |= 0x04;
			if(MchInf.CalPaiShuiMust< 16000)
				MchInf.CalPaiShuiMust++;
#ifdef TEST_SUOSHI			
			if(MchInf.CalPaiShuiMust > 1000)//150*100/2)
#else
			if(MchInf.CalPaiShuiMust >150*100/2)
#endif
			{
				MchInf.bFunPaiShuiMust = 0;
				MchInf.CalPaiShuiMust = 0;
				MchInf.bFunPaiShui = 0;
				ModeState = MODEWAIT;
				MchInf.RGBMode = RGB_WHITE;	
				MchInf.Relay &=~0x04;
			}
		}
		else
		{
			MchInf.Relay |= 0x04;
			MchInf.Relay &= ~0x700;
			MchInf.Relay &= ~0x01;
			MchInf.CalPaiShuiMust = 0;
		}
	}

	if(MchInf.LED2State)
		MchInf.Relay |= 0x08;
	
	if(MchInf.bFunZhengqiOpen)
		MchInf.Relay |= 0x10;

	
	if(MchInf.bPumpChugouYe)
	{
		if(MchInf.timePumpchugouye < 1200)
			MchInf.timePumpchugouye++;
		if(MchInf.timePumpchugouye >=1000/2)//10s
		{
			MchInf.bPumpChugouYe = 0;
			MchInf.timePumpchugouye = 0;
		}
	}
	
	if(MchInf.bPumpChugouYe)
		MchInf.Relay |= 0x20;	

	if(MchInf.bErrGuZhang)
	{
		MchInf.Relay &= ~0x700;//关加�?
	}
}

