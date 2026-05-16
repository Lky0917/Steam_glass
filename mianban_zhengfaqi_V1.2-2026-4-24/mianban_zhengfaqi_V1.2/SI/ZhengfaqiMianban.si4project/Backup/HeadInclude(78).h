/*========================================================
* ï¿?ï¿?ï¿? 
* ï¿?   ï¿? 
* åŠŸèƒ½æè¿°:	

* ä¿®æ”¹æ—¥æœŸ			ä¿®æ”¹ï¿?			ä¿®æ”¹è¯´æ˜
*           	    åˆ˜è¾‰				å®ŒæˆåŸºæœ¬åŠŸèƒ½
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



#define  TEST_SUOSHI      1
typedef enum
{
	MODESTOP = 0,
	MODESLEEP,
	MODEWAIT,//ï¿½ï¿½ï¿½ï¿½
	MODERUN, //ï¿½ï¿½ï¿½ï¿½
	MODEZANTING  //ï¿½ï¿½Í£
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
	unsigned int TIMEPAISHUIZANTING;
	unsigned int TIMEPAISHUIRUN;
	unsigned int TIMEHARD4CHUGOUALAM;
	unsigned int TIMEHARD3CHUGOUALAM;
	unsigned int TIMEHARD2CHUGOUALAM;
	unsigned int TIMEHARD1CHUGOUALAM;
	unsigned int TIMEHARD4CHUGOUALAMAGAIN;
	unsigned int TIMEHARD3CHUGOUALAMAGAIN;
	unsigned int TIMEHARD2CHUGOUALAMAGAIN;
	unsigned int TIMEHARD1CHUGOUALAMAGAIN;


}TESTMODEINF;
extern TESTMODEINF TestModeInf;



typedef struct
{
	unsigned int KeyState;
	unsigned int KeyState2;
	RGBMODE       RGBMode;  // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
	RGBMODE       RGBMode1; //LED
	unsigned char ModeRunState;
	unsigned char TmrLV;
	unsigned char MusicOn;
	unsigned char TimeZhengQi;
	
	unsigned char MusicNext;
	unsigned char MusicSound;
	unsigned char BLEReset;
	unsigned char bFunChuGou;
	unsigned char bFunChuGouEver;//³ı¹¸Ôø¿ªÆô¹ı
	unsigned char bFunSetWtHard;//ï¿½ï¿½ï¿½ï¿½Ë®Ó²ï¿½ï¿½
	unsigned char bFunChuGouStart;// ï¿½ï¿½Ê¼ï¿½ï¿½ï¿½ï¿½
	unsigned char bFunChuGouMau;//ÊÖ¶¯³ı¹¸¿ªÊ¼
	unsigned char bFunChuGouCal;// ï¿½ï¿½Ê¼ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ê±
	unsigned char TmprWater;//ï¿½×°ï¿½ï¿½È¡ï¿½Â¶ï¿?
	unsigned char TmprHouse;
	
	unsigned char WaterLV;//Ë®Î»
	unsigned char WaterHardState;
	unsigned char LEDDisp[2];
	unsigned char bDispDark;
	unsigned int  timeNostartChuGou;//10min
	unsigned int  ntimeRunChuGou;//
	unsigned int  timeRmdChuGou;//ï¿½ï¿½ï¿½ï¿½Ê£ï¿½ï¿½Ê±ï¿½ï¿½
	unsigned int  timeNoSetWtHard;//10min
	unsigned int  timeWaitNoKey;//2min
	unsigned char Dispbuffer[10];
	unsigned int  Relay;
	unsigned char blekey;
	unsigned char bAddWater;// ï¿½ï¿½Ë®ï¿½ï¿½ï¿½ï¿½

	unsigned char  timeRunZhengqi;//1min
	unsigned int  timePaiShuiCal;// 30min
	unsigned char bFunPaiShui;
	unsigned char bFunPaiShuiMust;//Ç¿ÖÆÅÅË®
	unsigned int  CalPaiShuiMust;//2min30sµÍË®Î»ÏÂÅÅË®
	unsigned char bFunZhengqiOpen;// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½è¶¨ï¿½Â¶ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
	unsigned char bFunHot;//ï¿½ï¿½ï¿½ï¿½

	unsigned char ntimeslight;//ï¿½ï¿½Ë¸
	unsigned char ntimeslightZhengfaIcon;//ï¿½ï¿½Ë¸
	unsigned char nCalTimeZhengfaqiIcon;//
	
	unsigned char bFunChuGouSleep;//ï¿½ï¿½ï¿½ï¿½Ë¯ï¿½ï¿½Ä£Ê½
	unsigned int  nCalTimeChuGouSleep;//
	
//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
	unsigned int  nCaltimesAutoChugou;//è‡ªåŠ¨é™¤å¢
	unsigned char ntimeslighChugouIcon;//ï¿½ï¿½Ë¸Æµï¿½ï¿½
	unsigned char nCalTimeChugouIcon;//ï¿½ï¿½Ë¸ï¿½ï¿½ï¿½ï¿½
	unsigned int  zhengqijiworktimesum;
	unsigned int  nCalTimeAutoSleep;
	unsigned char BleCMDState;	
	unsigned int  timesAlamChuGouAgain;// å¤šæ¬¡æé†’æ¬¡æ•°
	unsigned int  calAlamChugouAgain;//é—ªçƒ
	unsigned int  ntimeslightAlamChugouAgain;//é—ªçƒæ¬¡æ•°
	unsigned char bflagBleConnState;//À¶ÑÀ×´Ì¬
unsigned int  timePumpchugouye;	
unsigned char bErrorTmpr;
unsigned char bFunWeixiu							:1;//Î¬ï¿½ï¿½
unsigned char bFunWeixiuDisp					:1;
unsigned char bPumpChugou							:1;  //ÓĞÎŞ³ı¹¸±Ã
unsigned char bChugouYeWei							:1;//ï¿½ï¿½ï¿½ï¿½ÒºÎ»
unsigned char bPumpChugouYe							:1;//ï¿½ï¿½ï¿½ï¿½Òºbeng
unsigned char btestmode								:1;  //ï¿½ï¿½ï¿½ï¿½Ä£Ê½
unsigned char bOpenMusic							:1;	
unsigned char bFunAlamChuGou					:1;//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
unsigned char bFunAlamChuGouAgain			:1;//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
unsigned char bErrTmprWaterHigh       :1;
unsigned char bFlagWriteFlash			:1;
unsigned char bFirstOpen          :1;
unsigned char bErrWaterLv         :1;
unsigned char bErrGuZhang         :1;//ÎÂ¶È·¶Î§¹ÊÕÏ
unsigned char bCloseB2RGB         :1;
unsigned char bFunChugouAutoOrManu:1; //0 ×Ô¶¯  1 ÊÖ¶¯
unsigned char bFunZhengfa         :1;//Õô·¢Æ÷¹¦ÄÜ

unsigned char LED2State      :1;//
unsigned char bPressLED2      :1;

//zhendong
unsigned char bflagzhendong1   :1;
unsigned char bflagzhendong2   :1;
unsigned char bflagzhendong3   :1;
unsigned char bflagB1White   :1;
}MCHINF;


extern MCHINF MchInf;


#endif	//__HEADERINCLUDE_H
