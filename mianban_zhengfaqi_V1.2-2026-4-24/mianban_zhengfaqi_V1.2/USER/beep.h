#ifndef BEEP_H
#define BEEP_H

#include "SubDefine.h"

#ifdef BEEP_TYPE_PUBLIC
	#define BEEP_TYPE
#else
	#define BEEP_TYPE					extern
#endif

#define POWER_ON		0
#define NORMAL			1				
#define POWER_OFF		2


BEEP_TYPE unsigned char nMusicPos;
BEEP_TYPE unsigned char nMusicDelayTm;//10ms

BEEP_TYPE byte_def BeepFlage;
#define nBeepFlage					BeepFlage.m_byte
#define bDisBeep					BeepFlage.m_bit.b0
#define bDoorAlarmBeepAct			BeepFlage.m_bit.b1
#define bDisDoorAlarmBeep			BeepFlage.m_bit.b2

BEEP_TYPE unsigned char	 nAlarmTm;
BEEP_TYPE unsigned int const* pMusicAddr;
//1

BEEP_TYPE void f_Beep(unsigned char const i_MusicNum);
BEEP_TYPE void f_OutBuz(void);
BEEP_TYPE void f_AlarmBeepDeal(void);
BEEP_TYPE void f_BeepDataInit(void);
BEEP_TYPE void f_InitBuzPara(void);
BEEP_TYPE void f_IncBuzTm(void);
//BEEP_TYPE void f_MCU_OutMusicPWM(unsigned int SetFreqValue); 
#endif



