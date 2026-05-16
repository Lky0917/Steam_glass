#define VAR_KEY_DRIVER_GLOBALS
#include "HeadInclude.h"
#include "Lib_KeyDriver_const.h"

//---------------内部声明
void ReadKey(
			unsigned char *GetKeyState,
			unsigned char *ScanStep,
			unsigned int *KeyDelayTime,
			KEY_PRESSED_STATE Key_Get
			);

unsigned int nKeyDownTm;		/*按键按下时间*/
unsigned int nNoKeyTm;			/*无按键按下时间*/
unsigned int nKeyRealDownTm;	/*按键真实按下时间*/
unsigned char nKeyStep;			/*扫描步骤*/

#if 0
说明:调用时修改(1)
#endif
//--------------单键,组合键个数--------------------------------------------(1)
#define KEY_SIG_NUMB	22
#define KEY_COM_NUMB	0

unsigned long nKeyInfBuf;	//获取过来的原始按键信息
unsigned long nKeyInfMask;  //按键信息掩码，用于剔除无效按键。常态全为1
unsigned int nKeyPressErrTm[KEY_SIG_NUMB];//长时间按键按下时间-产生长时间按下故障
unsigned char nKeyReleaseOkTm[KEY_SIG_NUMB];//释放恢复时间

//------将硬件得到的数据转化为适合处理的数据----------------
//=====================KEY===================
#define KEY_1	        GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)	
#define KEY_2   		GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)

#define  HIGH_LEVEL     1
#define  LOW_LEVEL      0
void f_ChangeKeyInf(unsigned long *KeyInfDeal)
{
	
	(*KeyInfDeal) = NO_KEY;

//	if(IO_KEY1 == LOW_LEVEL)
//	{
//		(*KeyInfDeal) |= KEY_SIG_1;
//	}

//	if(IO_KEY2 == LOW_LEVEL)
//	{
//		(*KeyInfDeal) |= KEY_SIG_2;
//	}
//	if(IO_KEY3 == LOW_LEVEL)
//	{
//		(*KeyInfDeal) |= KEY_SIG_3;
//	}

//	if(IO_KEY4 == LOW_LEVEL)
//	{
//		(*KeyInfDeal) |= KEY_SIG_4;
//	}
//	if(IO_KEY5 == LOW_LEVEL)
//	{
//		(*KeyInfDeal) |= KEY_SIG_5;
//	}

//	if(IO_KEY6 == LOW_LEVEL)
//	{
//		(*KeyInfDeal) |= KEY_SIG_6;
//	}
//	if(IO_KEY7 == LOW_LEVEL)
//	{
//		(*KeyInfDeal) |= KEY_SIG_7;
//	}

//	if(IO_KEY8 == LOW_LEVEL)
//	{
//		(*KeyInfDeal) |= KEY_SIG_8;
//	}
//	if(IO_KEY9 == LOW_LEVEL)
//	{
//		(*KeyInfDeal) |= KEY_SIG_9;
//	}

//	if(IO_KEY10 == LOW_LEVEL)
//	{
//		(*KeyInfDeal) |= KEY_SIG_10;
//	}
//	if(IO_KEY11 == LOW_LEVEL)
//	{
//		(*KeyInfDeal) |= KEY_SIG_11;
//	}

//	if(IO_KEY12 == LOW_LEVEL)
//	{
//		(*KeyInfDeal) |= KEY_SIG_12;
//	}
//	if(IO_KEY13 == LOW_LEVEL)
//	{
//		(*KeyInfDeal) |= KEY_SIG_13;
//	}

//	if(IO_KEY14 == LOW_LEVEL)
//	{
//		(*KeyInfDeal) |= KEY_SIG_14;
//	}
//	if(IO_KEY15 == LOW_LEVEL)
//	{
//		(*KeyInfDeal) |= KEY_SIG_15;
//	}


    //缓存按键状态
	nKeyInfBuf = (*KeyInfDeal);

    //长按做无效处理
    (*KeyInfDeal) &= nKeyInfMask;
}
//-----------------以下为内部函数----------------

/*****************************************************************************
 * 函 数 名  : f_LongTmPressCnt
 * 负 责 人  : 
 * 创建日期  : 2016年6月25日
 * 函数功能  : 
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  :100ms时基调用 
 * 其    它  : 
 * 修改日志  : 


*****************************************************************************/
void f_LongTmPressCnt(void)
{
    unsigned char i;

    #define MAX_PRESS_ERR_TM 100//最大按下10S
    #define MAX_RELEASE_OK_TM 50//最小恢复时间5S

    for(i = 0; i < KEY_SIG_NUMB; i ++)
    {
        if(nKeyInfBuf & nTab_KeyHexDef[SIG_BASE + i])//按下
        {
            if(nKeyPressErrTm[i] <= 65530)	//长时间按下时间计数
            {
		        nKeyPressErrTm[i] ++;
            }
            nKeyReleaseOkTm[i] = 0;//恢复时间清除
            
            if(nKeyPressErrTm[i] > MAX_PRESS_ERR_TM)//大于按下最大时间
            {
                //屏蔽该按键
                nKeyInfMask &= ~nTab_KeyHexDef[SIG_BASE + i];
            }
        }
        else//释放
        {
            if(nKeyReleaseOkTm[i] <= 250)	//释放时间计算
            {
		        nKeyReleaseOkTm[i] ++;
            }
             nKeyPressErrTm[i] = 0;//故障时间清除

            if(nKeyReleaseOkTm[i] > MAX_RELEASE_OK_TM)//大于恢复时间
            {
                //恢复该按键
                nKeyInfMask |= nTab_KeyHexDef[SIG_BASE + i];
            }
        }
    }   
}

/* =========================================================
* 函 数 名: f_AddKeyPressTm
* 功能描述: 按键累加时间
* 全局变量: nKeyDownTm
* 输    入: 
* 返    回: 无
* 处理过程: 
* 注	意：10ms中断或时基中调用
* 修改日期			修改人				修改说明
* 2014-4-12			刘辉   			完成基本功能
 =========================================================*/
void f_AddKeyPressTm(void)
{
	if(nKeyDownTm <= 65530)
		nKeyDownTm ++;

	if(nNoKeyTm <= 65530)	//按键释放时间
		nNoKeyTm ++;
	
	if(nKeyRealDownTm <= 65530)	//按键真正按下时间
		nKeyRealDownTm ++;

	if(nKeyReleseTm <= 65530)	//按键释放时间
		nKeyReleseTm ++;
}

/* =========================================================
* 函 数 名: KeyScan
* 功能描述: 按键扫描函数
* 全局变量: nKeyDownTm,nKeyInf,KeyPressState,nKeyStep及每种按键信息变量
* 输    入: 
* 返    回: 无
* 处理过程: 
* 注	意：一般在while(1)中调用,也可在定时时基内调用
* 修改日期			修改人				修改说明
* 2014-4-12			liuhui 			完成基本功能
 =========================================================*/
void f_KeyScan(void)
{
	#define SIG_FUNCTION 0
	#define COM_FUNCTION 1
	unsigned char 	keyName;

	static unsigned char nLastScanInf = 0;
	f_ChangeKeyInf(&nKeyInf);
	if((nKeyInf & KEY_ALL) == NO_KEY)//按键释放
	{
		if(nNoKeyTm >= KEY_DELAY_TIME)//释放去抖
		{
			//按键信息清除
			nKeyResultInf = NO_KEY;

			if(bKeyUsedFlag == false 
			&& bKeyFirstRelse == false)//释放短按判断(前面键结果无使用)
			{
				nKeyResultInf |= PRESSED_RE;//短按释放
				bKeyFirstRelse = true;
			}
			
			//按键参数清零
			if(nKeyResultInf == NO_KEY)//释放信息已被清除
			{
				KeyPressName = KEY_FREE;
				nKeyStep = 0;
				bKeyPressFlag = false;
				bKeyUsedFlag = false;
				bLongPressFlag = false;
				nLastScanInf = SIG_FUNCTION;
			}
		}
	}
	else 
	{
		nNoKeyTm = 0;
		nKeyReleseTm = 0;
		bKeyFirstRelse = false;
		if(bKeyUsedFlag)//已经有按键响应
		{
			nKeyStep = MAX_STEP;//直接等待释放
			return;
		}
		
		for(keyName = 0; keyName < KEY_COM_NUMB; keyName ++)//组合按键扫描处理
		{
			if(((nKeyInf & KEY_ALL) == nTab_KeyHexDef[keyName]) \
			&& bKeyUsedFlag == false)
			{
				if(bKeyUsedFlag == false && nLastScanInf == SIG_FUNCTION)//由单键转组合
				{
					nLastScanInf = COM_FUNCTION;
					nKeyStep = 0;
				}
				
				ReadKey(
						&nKeyResultInf,
						&nKeyStep,
						&nKeyDownTm,
						keyName + 1
						);
				return;
			}
		}

		for(keyName  = SIG_BASE; keyName < SIG_BASE + KEY_SIG_NUMB; keyName ++)//单按键扫描处理
		{
			if(((nKeyInf & KEY_ALL) == nTab_KeyHexDef[keyName]) \
			&& bKeyUsedFlag == false)
			{
				if(bKeyUsedFlag == false && nLastScanInf == COM_FUNCTION)//由组合转单键
				{
					bKeyUsedFlag = true;//直接等待释放
					nKeyStep = MAX_STEP;//直接等待释放
				}
				nLastScanInf = SIG_FUNCTION;
				
				ReadKey(
						&nKeyResultInf,
						&nKeyStep,
						&nKeyDownTm,
						keyName + 1
						);
				return;
			}
		}

		if(nKeyInf && (~(KEY_TOTAL_COM)))//所有无效组合
		{
			bKeyFirstRelse = true;//无释放消息
		}

		//数据清除
		nKeyStep = MAX_STEP;//直接等待释放
	}
}


/* =========================================================
* 函 数 名: ReadKey
* 功能描述: 根据硬件按键信息,获取各种按键结果
* 全局变量: KeyPressState
* 输    入: 
* 返    回: 无
* 处理过程: 
* 注	意：
* 修改日期			修改人				修改说明
* 2014-4-12			liuhui 			完成基本功能
 =========================================================*/
void ReadKey(
			unsigned char *GetKeyState,
			unsigned char *ScanStep,
			unsigned int *KeyDelayTime,
			KEY_PRESSED_STATE Key_Get
			)
{	
	switch(*ScanStep)
	{
		case 0: 
			
			*KeyDelayTime = 0;
			nKeyRealDownTm = 0;
			*GetKeyState = NO_KEY;
			(*ScanStep) = 1;
			break;
				
		case MAX_STEP://等待结束 
				;
				break;
				
		default: 
			
			if(*KeyDelayTime >= GetTime((*ScanStep) - 1))
			{
				if(SetTimeInf((*ScanStep) - 1) != 0xff)
				{
					(*GetKeyState) |= SetTimeInf((*ScanStep) - 1);
					KeyPressName = Key_Get;
					bKeyPressFlag = true; //按键按下标志
					(*ScanStep) ++;
				}
				else
				{
					(*ScanStep) = MAX_STEP;
				}		
			}
			break;
	}
}

//按键初始化
void f_KeyInit(void)
{

    nKeyInfMask = KEY_ALL;


}
