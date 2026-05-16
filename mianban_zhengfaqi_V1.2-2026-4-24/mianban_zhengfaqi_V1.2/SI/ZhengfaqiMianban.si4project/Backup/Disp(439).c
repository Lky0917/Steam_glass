#include "HeadInclude.h"
#include "Disp_const.h"

TYPE_INT  IconDisp;
TYPE_INT  IconDisp1;
unsigned char RGBModeLast = 0;

void f_Deal_Seg(void)
{
	unsigned char i;
	static unsigned char addwaterstate = 0,nCntTime = 0;

	for(i = 0;i< 10;i++)
		MchInf.Dispbuffer[i] = 0;



	if((MchInf.bAddWater)||((MchInf.bFunHot)&&(MchInf.TmprWater < 95)))
	{
		nCntTime++;
		if(nCntTime >= 30)
		{
			nCntTime = 0;
			addwaterstate++;
			if(addwaterstate > 7)
				addwaterstate = 0;
		}
		switch(addwaterstate)
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
			default:break;

		}
	}
	else
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
	
	MchInf.Dispbuffer[9] = 0x00;

	if(MchInf.bDispDark)
		TM1620B_work(MchInf.Dispbuffer,TM1628_CMD_DARK);
	else
		TM1620B_work(MchInf.Dispbuffer,TM1628_CMD_DISP);


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
void f_Disp(void)
{
	static unsigned char SoundLast = 50,delaytime = 10;//
	static unsigned int  timelightB1 = 0;
	static unsigned char CalChuGouLight = 0;
	unsigned char temp;
	nIconDisp = 0;
	nIconDisp1 = 0;
	
//		MchInf.WaterLV = 0x03;
//		MchInf.TmprWater = 96;
//		MchInf.TmprHouse = 38;

	if(ModeState == MODESLEEP)
	{
		MchInf.bDispDark = 1;
		bIConSleep = 1;
		bIconZhengqi = 1;
		MchInf.RGBMode = RGB_WHITE;
		MchInf.RGBMode1 = RGB_CLOSE;
		MchInf.LEDDisp[0]  = LEDCLOSE;
		MchInf.LEDDisp[1]  = LEDCLOSE;
		MchInf.bFunHot = 0;//����ֹͣ			
		MchInf.bAddWater = 0;//��ˮֹͣ
		MchInf.LED2State = 0;//�ص�
		MchInf.MusicOn = 0;
		


		if(MchInf.bFunPaiShui)
		{
			bIconOut = 1;
			bIconWater = 1;
			f_Disp_WaterLV();
		}
	}
	else if(ModeState == MODEWAIT)
	{

		bIconLED = 1;
		if(MchInf.LED2State)
			bIconLED2 = 1;
//		MchInf.RGBMode = RGB_WHITE;
	
		bIconZhengqi = 1;
		bIconSound = 1;
		bIconAdd = 1;
		bIconJIan = 1;
		bIconLED2 = 1;
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
				if(MchInf.timeWaitNoKey >= 1000)
					MchInf.bDispDark = 1;
			}
		}
			
	}
	else if((ModeState == MODERUN)||(ModeState == MODEZANTING))
	{
		MchInf.LEDDisp[0] = MchInf.TimeZhengQi/10;
		MchInf.LEDDisp[1] = MchInf.TimeZhengQi%10;	
		
		bIconLED = 1;
		bIconZhengqi = 1;
		bIconSound = 1;
//		bIconAdd = 1;
//		bIconJIan = 1;
		bIconLED2 = 1;

		if(MchInf.LED2State)
			bIconLED2 = 1;

		if(MchInf.MusicOn)
			bIconSound = 1;

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

		bIconWater = 1;
		
		f_Disp_WaterLV();

		if(ModeState == MODERUN)
		{
			RGBModeLast = ModeState;
			MchInf.bDispDark = 0;

			if(MchInf.TimeZhengQi !=0)
			{
				if(MchInf.WaterLV == 0)//  ��ˮ
				{
					MchInf.bAddWater = 1;
					MchInf.bFunHot = 0;
					
				}
				else if(MchInf.WaterLV == 0x07)//���и߶���
				{
					MchInf.bAddWater = 0;			
				}
				
				if(MchInf.bAddWater)
				{
					bIconIn = 1;
					
				}			
				if(MchInf.bAddWater == 0)//�¶ȵ�ֹͣ����
				{
					MchInf.bFunHot = 1; //����
					if(MchInf.TmprWater >= 95)
					{
							MchInf.bFunZhengqiOpen = 1;
					}

					
					
					if(((MchInf.TmrLV == 1)&&(MchInf.TmprHouse >= 36)&&(MchInf.TmprHouse <= 39))||//36~39du
						((MchInf.TmrLV == 2)&&(MchInf.TmprHouse >= 41)&&(MchInf.TmprHouse <= 44))||//41~44du
						((MchInf.TmrLV == 3)&&(MchInf.TmprHouse >= 45)&&(MchInf.TmprHouse <= 48)))//45~48du
					{
						//MchInf.bFunZhengqiOpen = 0;//������ֹͣ����
						MchInf.bDispDark = 1;
						MchInf.bFunHot = 0;
					}			
				}
			}
			else 
			{
				if(MchInf.timePaiShuiCal <30*60*101)
						MchInf.timePaiShuiCal ++;	
				if(MchInf.timePaiShuiCal >= 30*60*100)
				{
					MchInf.bFunPaiShui = 1;
					if((MchInf.WaterLV&0x07) ==0)
					{
						MchInf.bFunPaiShui = 0;
						ModeState = MODEWAIT;	
						MchInf.RGBMode = RGB_WHITE;						
					}
				}
			}
		}
		
		if(ModeState == MODEZANTING)
		{
			MchInf.bDispDark = 1;			
			bIconWater = 0;
			MchInf.bFunHot = 0;//����ֹͣ			
			MchInf.bAddWater = 0;//��ˮֹͣ
			timelightB1++;
			if(timelightB1 > 50)
				MchInf.RGBMode = RGB_CLOSE;
			if(timelightB1 > 100)
			{
				MchInf.RGBMode = RGBModeLast;
				timelightB1 = 0;
			}
			
			if(MchInf.timePaiShuiCal <60*60*101)
				MchInf.timePaiShuiCal ++;	
			if(MchInf.timePaiShuiCal >= 60*60*100)
			{
				MchInf.bFunPaiShui = 1;
				if((MchInf.WaterLV&0x07) == 0)
				{
					MchInf.bFunPaiShui = 0;
					ModeState = MODEWAIT;	
					MchInf.RGBMode = RGB_WHITE;					
				}
			}

			if((MchInf.TmprHouse >=36)&&(MchInf.TmprHouse <=39))
				MchInf.TmrLV =1;
			else if((MchInf.TmprHouse >=41)&&(MchInf.TmprHouse <=44))
				MchInf.TmrLV =2;
			else if((MchInf.TmprHouse >=45)&&(MchInf.TmprHouse <=48))
				MchInf.TmrLV =3;
				
		}
		
		if((MchInf.bFunPaiShui)&&((MchInf.WaterLV&0x07) == 0))
		{
			MchInf.bFunPaiShui = 0;
			
			switch(MchInf.WaterHardState)//排水完成判断是否提醒除垢
				{
					case 1: 
							if(MchInf.zhengqijiworktimesum >= (60+3)*60)
								MchInf.bFunAlamChuGouAgain = 1;
							else if(MchInf.zhengqijiworktimesum >= 60*60)
								MchInf.bFunAlamChuGou = 1;
							break;
					case 2: 
							if(MchInf.zhengqijiworktimesum >= (23+3)*60)
								MchInf.bFunAlamChuGouAgain = 1;
							else if(MchInf.zhengqijiworktimesum >= 23*60)
								MchInf.bFunAlamChuGou = 1;
							break;
					case 3: if(MchInf.zhengqijiworktimesum >= (19+3)*60)
								MchInf.bFunAlamChuGouAgain = 1;
							else if(MchInf.zhengqijiworktimesum >= 19*60)
								MchInf.bFunAlamChuGou = 1;
							break;
					case 4: if(MchInf.zhengqijiworktimesum >= (8+3)*60)
								MchInf.bFunAlamChuGouAgain = 1;
							else if(MchInf.zhengqijiworktimesum >= 8*60)
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
		if(MchInf.bFunSetWtHard)
		{
				bIConStart = 0;
				bIConChuGou = 1;
				MchInf.timeNoSetWtHard++;
				if(MchInf.timeNoSetWtHard >= 1000)
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
		else if(MchInf.bFunChuGou)
		{
			bIConStart = 1;
			bIConChuGou = 1;
			MchInf.LEDDisp[0] = MchInf.timeRmdChuGou;
			MchInf.LEDDisp[1] = LED_ZIMU_h;

			if(MchInf.bFunChuGouStart == 0)
			{
				MchInf.LEDDisp[0] = LEDCLOSE;
				MchInf.LEDDisp[1] = LEDCLOSE;
				MchInf.timeNostartChuGou++;
				if(MchInf.timeNostartChuGou >= TestModeInf.TIMENOSTARTCHUGOU)//10min
					MchInf.bFunChuGou = 0;	

				if(MchInf.bPumpChugou)//有除垢泵
					{
						if(MchInf.bChugouYeWei == 0)
						{
						
							CalChuGouLight++;
							if(CalChuGouLight > 100)
							{
								CalChuGouLight = 0;
								if(MchInf.ntimeslight<10)
									MchInf.ntimeslight++;
							}
							
							if((CalChuGouLight < 50)&&(MchInf.ntimeslight  < 3))
							{
								bIConStart = 0;
								bIConChuGou = 0;
								MchInf.LEDDisp[0]  = LEDCLOSE;
								MchInf.LEDDisp[1]  = LEDCLOSE;
							}
							else
							{
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
					}			
			}
			else
			{
				MchInf.timeNostartChuGou = 0;

				if(MchInf.ntimeslightZhengfaIcon < 3)
				{
					if(MchInf.nCalTimeZhengfaqiIcon < 50)
						MchInf.RGBMode = RGB_CLOSE;
					else if(MchInf.nCalTimeZhengfaqiIcon < 100)
						MchInf.RGBMode = RGB_RED;
					MchInf.nCalTimeZhengfaqiIcon++;
					if(MchInf.nCalTimeZhengfaqiIcon > 100)
					{
						MchInf.nCalTimeZhengfaqiIcon = 0;
						MchInf.ntimeslightZhengfaIcon++;
					}
				}
				else
					MchInf.RGBMode = RGB_RED;			
				

				if(MchInf.timeRmdChuGou == 0)
				{
					MchInf.bFunPaiShui = 1;
					if((MchInf.WaterLV&0x07) ==0)
					{
						MchInf.bFunPaiShui = 0;
						MchInf.bFunChuGou = 0; //  �ع���
						MchInf.bFunChuGouStart = 0;
					}
				}
				else
				{
					bIConStart = 0;
					if(MchInf.bFunChuGouCal == 0)
					{
						if(MchInf.WaterLV <=1)
						{
							MchInf.bAddWater = 1;
							MchInf.timePumpchugouye = 0;
						}
						else if(MchInf.WaterLV == 0x07)
						{
								MchInf.bAddWater = 0;
								MchInf.bFunHot = 1;
								
						}
						
						if((MchInf.TmprWater >= 90)&&(MchInf.bAddWater == 0))
						{
							MchInf.bFunHot = 0;
							MchInf.bFunChuGouCal = 1;
							MchInf.nCalTimeChuGouSleep = 0;
							MchInf.bPumpChugouYe = 1;
						}
					}				
				}
			}
				
			if(MchInf.bPumpChugouYe)
			{
				if(MchInf.timePumpchugouye < 1200)
					MchInf.timePumpchugouye++;
				if(MchInf.timePumpchugouye >=1000)
					MchInf.bPumpChugouYe = 0;
			}
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
				bIconLED2 = 1;
				bIconSound = 1;	
			}
		}

		if(MchInf.bFunAlamChuGou)
		{
			MchInf.LEDDisp[0]  = LEDCLOSE;
			MchInf.LEDDisp[1]  = LEDCLOSE;
			//��˸30s
			if(MchInf.nCalTimeChugouIcon < 30)
			{
				MchInf.ntimeslighChugouIcon++;
				if(MchInf.ntimeslighChugouIcon < 50)
					bIConChuGou = 1;
				else
					bIConChuGou = 0;
				if(MchInf.ntimeslighChugouIcon > 100)
				{
					MchInf.ntimeslighChugouIcon = 0;
					MchInf.nCalTimeChugouIcon++;
				}
			}
			else
				bIConChuGou = 1;
			
			//有除垢泵自动除垢
			if(MchInf.bPumpChugou)//有除垢泵
			{
				if(MchInf.nCaltimesAutoChugou< 3600*110)
					MchInf.nCaltimesAutoChugou++;
				if(MchInf.nCaltimesAutoChugou == 3600*100)//1hour
				{
					MchInf.bFunChuGou = 1;
					MchInf.timeNostartChuGou = 0;
					MchInf.ntimeslight = 0;
					MchInf.timeRmdChuGou = 4;
					MchInf.bFunAlamChuGou = 0;
				
					if(MchInf.bChugouYeWei == 1)
					{							
						if(MchInf.bFunChuGouStart==0)
						{
							MchInf.nCaltimesAutoChugou = 0;
							f_Flash_Write();
							MchInf.bFunChuGouStart = 1;
						}					
					}
				}				
			}
		}
		if(MchInf.bFunAlamChuGouAgain)
		{
			//������˸1min
			if(MchInf.nCalTimeChugouIcon < 120)
			{
				MchInf.ntimeslighChugouIcon++;
				if(MchInf.ntimeslighChugouIcon < 20)
				{
					bIConChuGou = 1;
					MchInf.LEDDisp[0]  = LED_ZIMU_C;
					MchInf.LEDDisp[1]  = LED_ZIMU_L;
				}
				else
				{
					bIConChuGou = 0;
					MchInf.LEDDisp[0]  = LEDCLOSE;
					MchInf.LEDDisp[1]  = LEDCLOSE;
				}
				if(MchInf.ntimeslighChugouIcon > 50)
				{
					MchInf.ntimeslighChugouIcon = 0;
					MchInf.nCalTimeChugouIcon++;
				}
			}
			else
			{
				bIConChuGou = 1;
				MchInf.LEDDisp[0]  = LED_ZIMU_C;
				MchInf.LEDDisp[1]  = LED_ZIMU_L;
			}
		}
			//��˯��״̬�²���ʾ
		if(MchInf.TmprHouse < ERR_LOWTEMPER)
		{
			MchInf.LEDDisp[0]  = LED_FUHAO;
			MchInf.LEDDisp[1]  = LED_ZIMU_L;
//				MchInf.bAddWater = 0;
		}
		else if(MchInf.TmprHouse > ERR_HIGHTEMPER)
		{
			MchInf.LEDDisp[0]  = LED_FUHAO;
			MchInf.LEDDisp[1]  = LED_ZIMU_H;
//				MchInf.bAddWater = 0;
		}	
		if(MchInf.TmprWater > ERR_WATERTEMPER)
		{

			MchInf.bErrTmprWaterHigh = 1;
		}
		else if(MchInf.TmprWater <100)
			MchInf.bErrTmprWaterHigh = 0;
			
		if(MchInf.bErrTmprWaterHigh)
		{
			MchInf.LEDDisp[0]  = 0;
			MchInf.LEDDisp[1]  = LED_ZIMU_H;
			MchInf.bFunHot = 0;
		}
			
	}




	if(MchInf.bFunWeixiuDisp)
	{
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


	
	MchInf.Relay = 0;

	if(MchInf.bAddWater)
		MchInf.Relay |= 0x01;

	if(MchInf.bFunHot)
		MchInf.Relay |= 0x02;

	if(MchInf.bFunPaiShui)
	{		
		if((MchInf.WaterLV&0x07) ==0)
			MchInf.bFunPaiShui = 0;
		else
			MchInf.Relay |= 0x04;
	}

	if(MchInf.LED2State)
		MchInf.Relay |= 0x08;
	
	if(MchInf.bFunZhengqiOpen)
		MchInf.Relay |= 0x10;

	if(MchInf.bPumpChugouYe)
		MchInf.Relay |= 0x20;	
	f_Deal_Seg();
}

