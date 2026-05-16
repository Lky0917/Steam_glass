#define BEEP_TYPE_PUBLIC
#define BEEP_CONST_TYPE_PUBLIC
#include "HeadInclude.h"
#include "Beep_const.h"



void f_MCU_OutMusicPWM(unsigned int SetFreqValue) 
{
	if(SetFreqValue)
	{
/*		#ifdef MUSIC_BEEP
			TIM2_ARRH = SetFreqValue/256;				//周期
			TIM2_ARRL = SetFreqValue%256;
			TIM2_CCR1H = (SetFreqValue/256)*BEEP_VOICE/100;		//占空比,声音大小
			TIM2_CCR1L = (SetFreqValue%256)*BEEP_VOICE/100;				

			TIM2_CCMR1=0x68;//通道1 开启预装载， PWM模式1 向上计数时 <CCR 有效电平
			OUT_MUSIC_CTRL = OUT_MUSIC_ON;
		#else
			TIM2_CCMR1=0x68;//通道1 开启预装载， PWM模式1 向上计数时 <CCR 有效电平
			//TIM2_CCMR1 = 0x58;//强制输出有效电平 高电平
		#endif
*/
	TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM4,ENABLE);	
	TIM_SetCompare3(TIM4,250);//PWM工作 



	}
	else
	{
/*       #ifdef MUSIC_BEEP
             TIM2_CCMR1 = 0x48;//强制输出无效电平 低电平
    		OUT_MUSIC_CTRL = OUT_MUSIC_OFF;
    	#else	
		   TIM2_CCMR1 = 0x48;//强制输出无效电平 低电平
		   //TIM2_CCMR1 = 0x58;//强制输出有效电平 高电平
		#endif
*/
		TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Disable);
		TIM_SetCompare3(TIM4,0);
//		TIM_ForcedOC3Config(TIM4, TIM_ForcedAction_InActive);//强制输出低电平
	
	}
}

/* =========================================================
* 函 数 名: f_MCU_ChkADValue(void)
* 功能描述: 
* 调用方法: 
* 输出变量: 
========================================================= */
void f_Beep(unsigned char const i_MusicNum)
{

	nMusicPos = 1;
	nMusicDelayTm = 0;
}
/* =========================================================
* 函 数 名: f_MCU_ChkADValue(void)
* 功能描述: 
* 调用方法: 
* 输出变量: 
========================================================= */
void f_OutBuz(void)
{
	if(nMusicPos)
	{	
		if(nMusicDelayTm<=250)
			nMusicDelayTm++;	
		
		if(nMusicDelayTm >= 20)
		{
			nMusicDelayTm = 0;
//			BEEP_OFF_IO;
			nMusicPos = 0;
		}	
//		else
//			BEEP_ON_IO;			
	}
}

	
void f_AlarmBeepDeal(void)
{
//	uchar i;
//	uchar noErrCnt = 0;
	//===判断=========
	//检修
	

}

//10ms
void f_IncBuzTm(void)
{	

}

void f_InitBuzPara(void)
{
	nBeepFlage = 0;
	nMusicDelayTm = 0;
	nMusicPos = 0;
}
