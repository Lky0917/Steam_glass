/*========================================================
* �?�?�? 
* �?   �? 
* 功能描述:	

* 修改日期			修改�?			修改说明
*           	    刘辉				完成基本功能
=========================================================*/
#ifndef __HEADERINCLUDE_H
#define __HEADERINCLUDE_H

#include "stm32f10x.h"
#include "SubDefine.h"
#include "McuInit.h"
#include "Beep.h"
#include "Lib_KeyDriver.h"
#include "Uart.h"
#include "IIC.h"
#include "Disp.h"
#include "KeyDeal.h"
#include "TFTLCD.h"
#include "driver_TM1628.h"

#include "RGB.h"
#include "flash.h"

//#include "KeyDeal.h"
////#include "MCU_EEROM.h"
//#include "PrivateConst.h"
//#include "Display.h"


//#include "Communication.h"
//#include "MyMQTT.h"
//#include "Protocol.h"

extern byte_def    MchFlag;
#define		 bLightFlag		 	 	MchFlag.m_bit.b0

typedef enum
{
	MODESTOP = 0,
	MODESLEEP,
	MODEWAIT,//����
	MODERUN, //����
	MODEZANTING  //��ͣ
}MODE;

extern MODE  ModeState;
typedef enum
{
	RGB_CLOSE = 0,
	RGB_ZISe,
	RGB_FENSE,
	RGB_RED,
	RGB_ORANGE,
	RGB_YELLOW,
	RGB_GREEN,
	RGB_SKYBLUE,
	RGB_BLUE,
	RGB_WHITE
}RGBMODE;

typedef struct
{
	unsigned int TIMERUNCHUGOU;
	unsigned int TIMEZHENGQIONEHOUR;
	unsigned int TIMEAUTOSLEEP;
	unsigned int TIMEWAITNOKEY;//
	unsigned int TIMENOSTARTCHUGOU;//10min
	unsigned int TIMECHUGOUSLEEP;//10min

}TESTMODEINF;
extern TESTMODEINF TestModeInf;



typedef struct
{
	unsigned int KeyState;
	unsigned int KeyState2;
	RGBMODE       RGBMode;  // ������
	RGBMODE       RGBMode1; //LED
	unsigned char ModeRunState;
	unsigned char LED2State;
	unsigned char TmrLV;
	unsigned char MusicOn;
	unsigned char TimeZhengQi;
	
	unsigned char MusicNext;
	unsigned char MusicSound;
	unsigned char BLEReset;
	unsigned char bFunChuGou;
	unsigned char bFunSetWtHard;//����ˮӲ��
	unsigned char bFunChuGouStart;// ��ʼ����
	unsigned char bFunChuGouCal;// ��ʼ������ʱ
	unsigned char TmprWater;//�װ��ȡ�¶�
	unsigned char TmprHouse;
	
	unsigned char WaterLV;//ˮλ
	unsigned char WaterHardState;
	unsigned char LEDDisp[2];
	unsigned char bDispDark;
	unsigned int  timeNostartChuGou;//10min
	unsigned int  ntimeRunChuGou;//
	unsigned int  timeRmdChuGou;//����ʣ��ʱ��
	unsigned int  timeNoSetWtHard;//10min
	unsigned int  timeWaitNoKey;//2min
	unsigned char Dispbuffer[10];
	unsigned int  Relay;
	unsigned char blekey;
	unsigned char bAddWater;// ��ˮ����

	unsigned char  timeRunZhengqi;//1min
	unsigned int  timePaiShuiCal;// 30min
	unsigned char bFunPaiShui;
	unsigned char bFunZhengqiOpen;// ���������趨�¶� ��������
	unsigned char bFunHot;//����

	unsigned char ntimeslight;//��˸
	unsigned char ntimeslightZhengfaIcon;//��˸
	unsigned char nCalTimeZhengfaqiIcon;//
	
	unsigned char bFunChuGouSleep;//����˯��ģʽ
	unsigned int  nCalTimeChuGouSleep;//
	
//��������
	unsigned int  nCaltimesAutoChugou;//自动除垢
	unsigned char ntimeslighChugouIcon;//��˸Ƶ��
	unsigned char nCalTimeChugouIcon;//��˸����
	unsigned int  zhengqijiworktimesum;
	unsigned int  nCalTimeAutoSleep;
	unsigned char BleCMDState;	
	unsigned int  timesAlamChuGouAgain;// 多次提醒次数
	unsigned int  calAlamChugouAgain;//闪烁
	unsigned int  ntimeslightAlamChugouAgain;//闪烁次数
	
unsigned int  timePumpchugouye;	
unsigned char bErrorTmpr;
unsigned char bFunWeixiu							:1;//ά��
unsigned char bFunWeixiuDisp					:1;
unsigned char bPumpChugou							:1;  //�Ƿ��г�����
unsigned char bChugouYeWei							:1;//����Һλ
unsigned char bPumpChugouYe							:1;//����Һbeng
unsigned char btestmode								:1;  //����ģʽ
unsigned char bOpenMusic							:1;	
unsigned char bFunAlamChuGou					:1;//������������
unsigned char bFunAlamChuGouAgain			:1;//������������
unsigned char bErrTmprWaterHigh       :1;
}MCHINF;


extern MCHINF MchInf;


#endif	//__HEADERINCLUDE_H
