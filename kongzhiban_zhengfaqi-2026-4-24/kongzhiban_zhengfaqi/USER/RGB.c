#include "HeadInclude.h"


void f_MCU_OutRGBPWM_1(RGBMODE state) 
{
	unsigned int tempcomp = 500;
	static unsigned int called = 1;
	static unsigned char lastmodestate = 0xff;
//	state = RGB_ZISe;
	

	switch(state)
	{
		case RGB_ZISe://紫色
			TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
			TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
			TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM3,ENABLE);
			TIM_SetCompare1(TIM3,370/called);//PWM工作 		
			TIM_SetCompare2(TIM3,0);//PWM工作 
			TIM_SetCompare3(TIM3,500/called);//PWM工作 
		break;
		case RGB_FENSE://粉色
			TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
			TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
			TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM3,ENABLE);
			TIM_SetCompare1(TIM3,500/called);//PWM工作 		
			TIM_SetCompare2(TIM3,30/called);//PWM工作 
			TIM_SetCompare3(TIM3,306/called);//PWM工作 
		break;
		case RGB_RED://hongse
			TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
			TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
			TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM3,ENABLE);
			TIM_SetCompare1(TIM3,500/called);//PWM工作 		
			TIM_SetCompare2(TIM3,30/called);//PWM工作 
			TIM_SetCompare3(TIM3,0);//PWM工作 
		break;
		case RGB_ORANGE://橙色
			TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
			TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
			TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM3,ENABLE);
			TIM_SetCompare1(TIM3,500/called);//PWM工作 		
			TIM_SetCompare2(TIM3,(500-210)/called);//PWM工作 210
			TIM_SetCompare3(TIM3,0);//PWM工作 
		break;
		case RGB_YELLOW://黄色
			TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
			TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
			TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM3,ENABLE);
			TIM_SetCompare1(TIM3,500/called);//PWM工作 		
			TIM_SetCompare2(TIM3,400/called);//PWM工作 
			TIM_SetCompare3(TIM3,0);//PWM工作 
		break;
		case RGB_GREEN://绿色
			TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
			TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
			TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM3,ENABLE);
			TIM_SetCompare1(TIM3,330/called);//PWM工作 		
			TIM_SetCompare2(TIM3,450/called);//PWM工作 
			TIM_SetCompare3(TIM3,8/called);//PWM工作 
		break;
		case RGB_SKYBLUE://天蓝色
			TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
			TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
			TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM3,ENABLE);
			TIM_SetCompare1(TIM3,4/called);//PWM工作 		
			TIM_SetCompare2(TIM3,420/called);//PWM工作 
			TIM_SetCompare3(TIM3,300/called);//PWM工作 
		break;
		case RGB_BLUE://蓝色
			TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
			TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
			TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM3,ENABLE);
			TIM_SetCompare1(TIM3,1/called);//PWM工作 		
			TIM_SetCompare2(TIM3,266/called);//PWM工作 
			TIM_SetCompare3(TIM3,500/called);//PWM工作 
		break;
		case RGB_WHITE://白色
			TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
			TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
			TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM3,ENABLE);
			
			tempcomp = 499;
//			if(MchInf.bDispDark)
//				tempcomp = 200;
				
			TIM_SetCompare1(TIM3,tempcomp);//PWM工作 		
			TIM_SetCompare2(TIM3,tempcomp);//PWM工作 
			TIM_SetCompare3(TIM3,tempcomp);//PWM工作 
		break;
		case RGB_CLOSE:
			TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Disable);
			TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Disable);
			TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Disable);
			TIM_ARRPreloadConfig(TIM3,ENABLE);
			TIM_SetCompare1(TIM3,0);
			TIM_SetCompare2(TIM3,0);
			TIM_SetCompare3(TIM3,0);
//		TIM_ForcedOC3Config(TIM4, TIM_ForcedAction_InActive);//强制输出低电平
		break;
		default:break;
	}
	

	
//	if(lastmodestate != MchInf.LEDState)
//	{
//		
//		if(lastmodestate == RGB_CLOSE)
//			called = 1;
////		else
////			called = 100;
//		else
//		{
//			called++;
//		
//			if(called >= 30)
//			{
//				lastmodestate = MchInf.LEDState;
//				called = 30;
//			}
//		}
//			
//	}
//	else 	if(called > 1)
//		called--;
		
}
