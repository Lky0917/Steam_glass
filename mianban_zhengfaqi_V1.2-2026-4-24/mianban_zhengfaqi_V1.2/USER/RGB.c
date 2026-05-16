#include "HeadInclude.h"

static unsigned int called = 500;

void f_MCU_OutRGBPWM_0(void) 
{
//if(MchInf.RGBMode1 == RGB_CLOSE)	
//	state = RGB_CLOSE;
//else
//	state = RGB_WHITE;
//	
//	switch(state)
//		{
//			case RGB_ZISe://紫色
//				TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
//				TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
//				TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);
//				TIM_ARRPreloadConfig(TIM4,ENABLE);
//				TIM_SetCompare1(TIM4,400/called);//PWM工作		
//				TIM_SetCompare2(TIM4,0);//PWM工作 
//				TIM_SetCompare3(TIM4,490/called);//PWM工作 
//			break;
//			case RGB_FENSE://粉色
//				TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
//				TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
//				TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);
//				TIM_ARRPreloadConfig(TIM4,ENABLE);
//				TIM_SetCompare1(TIM4,500/called);//PWM工作		
//				TIM_SetCompare2(TIM4,30/called);//PWM工作 
//				TIM_SetCompare3(TIM4,306/called);//PWM工作 
//			break;
//			case RGB_RED://hongse
//				TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
//				TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
//				TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);
//				TIM_ARRPreloadConfig(TIM4,ENABLE);
//				TIM_SetCompare1(TIM4,500/called);//PWM工作		
//				TIM_SetCompare2(TIM4,30/called);//PWM工作 
//				TIM_SetCompare3(TIM4,0);//PWM工作 
//			break;
//			case RGB_ORANGE://橙色
//				TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
//				TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
//				TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);
//				TIM_ARRPreloadConfig(TIM4,ENABLE);
//				TIM_SetCompare1(TIM4,500/called);//PWM工作		
//				TIM_SetCompare2(TIM4,210/called);//PWM工作 
//				TIM_SetCompare3(TIM4,0);//PWM工作 
//			break;
//			case RGB_YELLOW://黄色
//				TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
//				TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
//				TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);
//				TIM_ARRPreloadConfig(TIM4,ENABLE);
//				TIM_SetCompare1(TIM4,500/called);//PWM工作		
//				TIM_SetCompare2(TIM4,400/called);//PWM工作 
//				TIM_SetCompare3(TIM4,0);//PWM工作 
//			break;
//			case RGB_GREEN://绿色
//				TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
//				TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
//				TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);
//				TIM_ARRPreloadConfig(TIM4,ENABLE);
//				TIM_SetCompare1(TIM4,330/called);//PWM工作		
//				TIM_SetCompare2(TIM4,450/called);//PWM工作 
//				TIM_SetCompare3(TIM4,8);//PWM工作 
//			break;
//			case RGB_SKYBLUE://天蓝色
//				TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
//				TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
//				TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);
//				TIM_ARRPreloadConfig(TIM4,ENABLE);
//				TIM_SetCompare1(TIM4,4/called);//PWM工作 		
//				TIM_SetCompare2(TIM4,420/called);//PWM工作 
//				TIM_SetCompare3(TIM4,300/called);//PWM工作 
//			break;
//			case RGB_BLUE://蓝色
//				TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
//				TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
//				TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);
//				TIM_ARRPreloadConfig(TIM4,ENABLE);
//				TIM_SetCompare1(TIM4,0);//PWM工作 		
//				TIM_SetCompare2(TIM4,266/called);//PWM工作 
//				TIM_SetCompare3(TIM4,500/called);//PWM工作 
//			break;
//			case RGB_WHITE://白色
//				TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
//				TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
//				TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);
//				TIM_ARRPreloadConfig(TIM4,ENABLE);
//				tempcomp = 500;
//				if(MchInf.bDispDark)
//					tempcomp = 200;
//				TIM_SetCompare1(TIM4,tempcomp);//PWM工作 		
//				TIM_SetCompare2(TIM4,tempcomp);//PWM工作 
//				TIM_SetCompare3(TIM4,tempcomp);//PWM工作 
//			break;
//			case RGB_CLOSE:
//				TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Disable);
//				TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Disable);
//				TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Disable);
//				TIM_ARRPreloadConfig(TIM4,ENABLE);
//				TIM_SetCompare1(TIM4,0);
//				TIM_SetCompare2(TIM4,0);
//				TIM_SetCompare3(TIM4,0);
//	//		TIM_ForcedOC3Config(TIM4, TIM_ForcedAction_InActive);//强制输出低电平
//			default:break;
//		}

}

void f_MCU_OutRGBPWM_1(void) 
{
	called  = 1;
	
	if(MchInf.RGBMode == RGB_WHITE)
	{
			MchInf.RGBMode = RGB_CLOSE;
		MchInf.bflagB1White = 1;
	}
	else if(MchInf.RGBMode != RGB_CLOSE)
	{
		MchInf.bflagB1White = 0;
	}
//	MchInf.RGBMode = RGB_ZISe;
	switch(MchInf.RGBMode)
	{
		case RGB_ZISe://紫色
			TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
			TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
			TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM3,ENABLE);
			TIM_SetCompare1(TIM3,400/called);//PWM工作 		
			TIM_SetCompare2(TIM3,0);//PWM工作 
			TIM_SetCompare3(TIM3,490/called);//PWM工作 
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
			TIM_SetCompare2(TIM3,210/called);//PWM工作 
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
			TIM_SetCompare1(TIM3,0);//PWM工作 		
			TIM_SetCompare2(TIM3,266/called);//PWM工作 
			TIM_SetCompare3(TIM3,500/called);//PWM工作 
		break;
		case RGB_WHITE://白色
//			TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
//			TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
//			TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
//			TIM_ARRPreloadConfig(TIM3,ENABLE);
//			
////			tempcomp = 500;
////			if(MchInf.bDispDark)
////				tempcomp = 200;
//				
//			TIM_SetCompare1(TIM3,tempcomp);//PWM工作 		
//			TIM_SetCompare2(TIM3,tempcomp);//PWM工作 
//			TIM_SetCompare3(TIM3,tempcomp);//PWM工作 
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
		default:break;
	}

}


void f_Deal_PWM(void)
{
//	if(ModeState == MODERUN)
//	{
		f_MCU_OutRGBPWM_1();
//		f_MCU_OutRGBPWM_0();
/*					
		if(called > 1)
			called--;
		
		if((MchInf.RGBMode == RGB_WHITE)||(MchInf.RGBMode == RGB_CLOSE))
			return;
		
		caltime30s++;
		if(caltime30s >= 3000)
		{
			caltime30s = 0;

			called = 100;
		
				switch(MchInf.ModeRunState)
				{
					case 0:
//						if(MchInf.RGBMode == RGB_RED)
//							MchInf.RGBMode = RGB_FENSE;
//						else if(MchInf.RGBMode == RGB_FENSE)
//							MchInf.RGBMode = RGB_RED;
					
					if(MchInf.RGBMode >= RGB_BLUE)
						MchInf.RGBMode = RGB_ZISe;
					else
						MchInf.RGBMode++;
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
				
			if(MchInf.RGBMode1 != RGB_CLOSE)//非关闭状态
				MchInf.RGBMode1 = MchInf.RGBMode;
*/				
//if((MchInf.RGBMode1 == RGB_WHITE)||(MchInf.RGBMode1 == RGB_CLOSE))
//			return;
//		
//				switch(MchInf.ModeRunState)
//				{
//					case 0:
//						if(MchInf.RGBMode == RGB_RED)
//							MchInf.RGBMode1 = RGB_RED;
//						else if(MchInf.RGBMode == RGB_FENSE)
//							MchInf.RGBMode1 = RGB_FENSE;
//						break;
//					case 1:
//						if(MchInf.RGBMode == RGB_YELLOW)
//							MchInf.RGBMode1 = RGB_YELLOW;
//						else if(MchInf.RGBMode == RGB_ORANGE)
//							MchInf.RGBMode1 = RGB_ORANGE;
//						break;
//					case 2:
//						if(MchInf.RGBMode == RGB_BLUE)
//							MchInf.RGBMode1 = RGB_BLUE;
//						else if(MchInf.RGBMode == RGB_SKYBLUE)
//							MchInf.RGBMode1 = RGB_SKYBLUE;
//						break;
//					case 3:
//						if(MchInf.RGBMode == RGB_ZISe)
//							MchInf.RGBMode1 = RGB_ZISe;
//						else if(MchInf.RGBMode == RGB_GREEN)
//							MchInf.RGBMode1 = RGB_GREEN;
//						break;	
//				}
//			}
//	}


}
