#define VAR_KEYDEAL_GLOBALS
#include "HeadInclude.h"

unsigned NUM_key = 0;
unsigned Send_Num_Key = 0;

void f_Key_IntoTestMode(void);

//-----------------处理子函数------------------------------------------(4)
void f_Key1Deal_Poweroff(void)
{
    if (nKeyResultInf & PRESSED_5S)
    {
        bKeyUsedFlag = true;
    }
}

void f_Key3Deal_Poweroff(void)
{
    if (nKeyResultInf & PRESSED_5S)
    {
        bKeyUsedFlag = true;
    }
}

void f_Key4Deal_Poweroff(void)
{
    if (nKeyResultInf & PRESSED)
    {
        bKeyUsedFlag = true;

        // 灯光显示开关
        f_Beep(NORMAL);
    }
}

void f_Key5Deal_Poweroff(void)
{
    if (nKeyResultInf & PRESSED)
    {
        bKeyUsedFlag = true;
    }
}

void f_Key_1_3_Deal_Poweroff(void)
{
    if (nKeyResultInf & PRESSED_2S) // 长按2S
    {
        bKeyUsedFlag = true;
    }
}

void f_KeyBackDisp_Poweroff(void)
{
    if (nKeyResultInf & PRESSED)
    {

        bKeyUsedFlag = true;

        f_Beep(NORMAL);
    }
}

void f_KeyDeal_Standby(void)
{
    switch (KeyPressName)
    {
    case KEY_COM_PRESS_2: // 组合功能+定时
        f_Key_1_3_Deal_Poweroff();
        break;

    case KEY_SIGNAL_PRESS_1: // 模式-配网1
        f_Key1Deal_Poweroff();
        break;

    case KEY_SIGNAL_PRESS_2: // 风速
        f_KeyBackDisp_Poweroff();
        break;

    case KEY_SIGNAL_PRESS_3: // 定时-配网2
        f_Key3Deal_Poweroff();
        break;

    case KEY_SIGNAL_PRESS_4: // 显示开关
        f_Key4Deal_Poweroff();
        break;

    case KEY_SIGNAL_PRESS_5: // 电源
        f_Key5Deal_Poweroff();
        break;

    default:
        break;
    }

    nKeyResultInf = NO_KEY;
}

//===运行==

void f_Key1Deal_Run(void)
{

    if (nKeyResultInf & PRESSED_RE)
    {
        f_Beep(NORMAL);
        bKeyUsedFlag = true;
        NUM_key = 1;
        Send_Num_Key = 1;
    }
    else if (nKeyResultInf & PRESSED_3S) // 配网1
    {
        bKeyUsedFlag = true;
    }
}

void f_Key2Deal_Run(void)
{
    if (nKeyResultInf & PRESSED_RE)
    {
        f_Beep(NORMAL);
        bKeyUsedFlag = true;
        NUM_key = 2;
        Send_Num_Key = 1;
    }
}

void f_Key3Deal_Run(void) // 定时
{

    if (nKeyResultInf & PRESSED_RE)
    {
        bKeyUsedFlag = true;

        NUM_key = 3;
        Send_Num_Key = 1;
    }
}

void f_Key4Deal_Run(void)
{
    if (nKeyResultInf & PRESSED_RE)
    {
        bKeyUsedFlag = true;
        NUM_key = 4;
        Send_Num_Key = 1;
    }
}

void f_Key5Deal_Run(void)
{
    if (nKeyResultInf & PRESSED_RE)
    {
        bKeyUsedFlag = true;

        NUM_key = 5;
        Send_Num_Key = 1;
    }
}

void f_Key6Deal_Run(void)
{
    if (nKeyResultInf & PRESSED_RE)
    {
        bKeyUsedFlag = true;
        NUM_key = 6;
        Send_Num_Key = 1;
    }
}
void f_Key7Deal_Run(void)
{
    if (nKeyResultInf & PRESSED_RE)
    {
        bKeyUsedFlag = true;
        NUM_key = 7;
        Send_Num_Key = 1;
    }
}

void f_Key8Deal_Run(void)
{
    if (nKeyResultInf & PRESSED_RE)
    {
        f_Beep(NORMAL);
        bKeyUsedFlag = true;
        NUM_key = 8;
        Send_Num_Key = 1;
    }
}

void f_Key9Deal_Run(void) // 定时
{

    if (nKeyResultInf & PRESSED_RE)
    {
        bKeyUsedFlag = true;

        NUM_key = 9;
        Send_Num_Key = 1;
    }
}

void f_Key10Deal_Run(void)
{
    if (nKeyResultInf & PRESSED_RE)
    {
        bKeyUsedFlag = true;
        NUM_key = 10;
        Send_Num_Key = 1;
    }
}

void f_Key11Deal_Run(void)
{
    if (nKeyResultInf & PRESSED_RE)
    {
        bKeyUsedFlag = true;

        NUM_key = 11;
        Send_Num_Key = 1;
    }
}

void f_Key12Deal_Run(void)
{
    if (nKeyResultInf & PRESSED_RE)
    {
        bKeyUsedFlag = true;
        NUM_key = 12;
        Send_Num_Key = 1;
    }
}
void f_Key13Deal_Run(void)
{
    if (nKeyResultInf & PRESSED_RE)
    {
        bKeyUsedFlag = true;
        NUM_key = 13;
        Send_Num_Key = 1;
    }
}
void f_Key14Deal_Run(void)
{

    if (nKeyResultInf & PRESSED_RE)
    {
        f_Beep(NORMAL);
        bKeyUsedFlag = true;
        NUM_key = 14;
        Send_Num_Key = 1;
    }
    else if (nKeyResultInf & PRESSED_3S) // 配网1
    {
        bKeyUsedFlag = true;
    }
}

void f_Key15Deal_Run(void)
{
    if (nKeyResultInf & PRESSED_RE)
    {
        f_Beep(NORMAL);
        bKeyUsedFlag = true;
        NUM_key = 15;
        Send_Num_Key = 1;
    }
}

void f_Key16Deal_Run(void) // 定时
{

    if (nKeyResultInf & PRESSED_RE)
    {
        bKeyUsedFlag = true;

        NUM_key = 16;
        Send_Num_Key = 1;
    }
}

void f_Key17Deal_Run(void)
{
    if (nKeyResultInf & PRESSED_RE)
    {
        bKeyUsedFlag = true;
        NUM_key = 17;
        Send_Num_Key = 1;
    }
}

void f_Key18Deal_Run(void)
{
    if (nKeyResultInf & PRESSED_RE)
    {
        bKeyUsedFlag = true;

        NUM_key = 18;
        Send_Num_Key = 1;
    }
}

void f_Key19Deal_Run(void)
{
    if (nKeyResultInf & PRESSED_RE)
    {
        bKeyUsedFlag = true;
        NUM_key = 19;
        Send_Num_Key = 1;
    }
}
void f_Key20Deal_Run(void)
{
    if (nKeyResultInf & PRESSED_RE)
    {
        bKeyUsedFlag = true;
        NUM_key = 20;
        Send_Num_Key = 1;
    }
}

void f_Key21Deal_Run(void)
{
    if (nKeyResultInf & PRESSED_RE)
    {
        f_Beep(NORMAL);
        bKeyUsedFlag = true;
        NUM_key = 21;
        Send_Num_Key = 1;
    }
}

void f_Key22Deal_Run(void) // 定时
{

    if (nKeyResultInf & PRESSED_RE)
    {
        bKeyUsedFlag = true;

        NUM_key = 22;
        Send_Num_Key = 1;
    }
}

void f_Key_1_2_Deal_Run(void)
{
    if (nKeyResultInf & PRESSED_3S) // 长按3S
    {
        bKeyUsedFlag = true;

        f_Beep(RESET);
    }
}

void f_KeyDeal_Run(void)
{
    switch (KeyPressName)
    {
    case KEY_COM_PRESS_1: // 清滤芯
        f_Key_1_2_Deal_Run();
        break;

    case KEY_SIGNAL_PRESS_1: // 功能
        f_Key1Deal_Run();
        break;

    case KEY_SIGNAL_PRESS_2: // 风速
        f_Key2Deal_Run();
        break;

    case KEY_SIGNAL_PRESS_3: // 定时
        f_Key3Deal_Run();
        break;

    case KEY_SIGNAL_PRESS_4: // 指示灯
        f_Key4Deal_Run();
        break;

    case KEY_SIGNAL_PRESS_5: // 关机
        f_Key5Deal_Run();
        break;
    case KEY_SIGNAL_PRESS_6:
        f_Key6Deal_Run();
        break;

    case KEY_SIGNAL_PRESS_7:
        f_Key7Deal_Run();
        break;

    case KEY_SIGNAL_PRESS_8:
        f_Key8Deal_Run();
        break;

    case KEY_SIGNAL_PRESS_9:
        f_Key9Deal_Run();
        break;

    case KEY_SIGNAL_PRESS_10:
        f_Key10Deal_Run();
        break;
    case KEY_SIGNAL_PRESS_11:
        f_Key11Deal_Run();
        break;

    case KEY_SIGNAL_PRESS_12:
        f_Key12Deal_Run();
        break;

    case KEY_SIGNAL_PRESS_13:
        f_Key13Deal_Run();
        break;

    case KEY_SIGNAL_PRESS_14:
        f_Key14Deal_Run();
        break;

    case KEY_SIGNAL_PRESS_15:
        f_Key15Deal_Run();
        break;

    case KEY_SIGNAL_PRESS_16:
        f_Key16Deal_Run();
        break;

    case KEY_SIGNAL_PRESS_17:
        f_Key17Deal_Run();
        break;

    case KEY_SIGNAL_PRESS_18:
        f_Key18Deal_Run();
        break;

    case KEY_SIGNAL_PRESS_19:
        f_Key19Deal_Run();
        break;

    case KEY_SIGNAL_PRESS_20:
        f_Key20Deal_Run();
        break;

    case KEY_SIGNAL_PRESS_21:
        f_Key21Deal_Run();
        break;

    case KEY_SIGNAL_PRESS_22:
        f_Key22Deal_Run();
        break;

    default:
        break;
    }

    nKeyResultInf = NO_KEY;
}

//-----自检处理---------
/*
void f_Key1Deal_SC(BIG_STRUCT *pFuctionData)
{
    if(nKeyResultInf & PRESSED)
    {
        bKeyUsedFlag = true;

        if(pFuctionData->selfCheckInf.bKey_1_P == false \
        && pFuctionData->selfCheckInf.ucSelfCheckStep == CHECK_STEP_KEY)
        {
            f_Beep(NORMAL);
            pFuctionData->selfCheckInf.bKey_1_P = true;
            pFuctionData->selfCheckInf.keyTuchNumb ++;
        }
        else if(pFuctionData->selfCheckInf.ucSelfCheckStep == CHECK_STEP_VERSION)//进入wifi产测
        {
            f_Beep(NORMAL);
            pFuctionData->selfCheckInf.ucSelfCheckStep = CHECK_STEP_WIFI;
            pFuctionData->selfCheckInf.ucCheckCnt = 0;

            pFuctionData->selfCheckInf.bWifiSendCMD = false;
        }
    }
}

void f_Key2Deal_SC(BIG_STRUCT *pFuctionData)
{
    if(nKeyResultInf & PRESSED)
    {
        bKeyUsedFlag = true;

        //快速进入颜色检测，且正面全亮
        if(pFuctionData->selfCheckInf.ucSelfCheckStep == CHECK_STEP_VERSION)
        {
            f_Beep(NORMAL);
            pFuctionData->selfCheckInf.ucSelfCheckStep = CHECK_STEP_LED_R;
            pFuctionData->selfCheckInf.bOnlyTest_LED = true;//仅检测led
            pFuctionData->selfCheckInf.bShowAll = true;//正面全亮
            pFuctionData->selfCheckInf.bCheckLed = true;//检测正面led
        }
        else if(pFuctionData->selfCheckInf.bKey_2_P == false \
        && pFuctionData->selfCheckInf.ucSelfCheckStep == CHECK_STEP_KEY)
        {
            f_Beep(NORMAL);
            pFuctionData->selfCheckInf.bKey_2_P = true;
            pFuctionData->selfCheckInf.keyTuchNumb ++;
        }
    }
}

void f_Key3Deal_SC(BIG_STRUCT *pFuctionData)
{
    if(nKeyResultInf & PRESSED)
    {
        bKeyUsedFlag = true;

        if(pFuctionData->selfCheckInf.bKey_3_P == false \
        && pFuctionData->selfCheckInf.ucSelfCheckStep == CHECK_STEP_KEY)
        {
            f_Beep(NORMAL);
            pFuctionData->selfCheckInf.bKey_3_P = true;
            pFuctionData->selfCheckInf.keyTuchNumb ++;
        }
    }
}

void f_Key4Deal_SC(BIG_STRUCT *pFuctionData)
{
    if(nKeyResultInf & PRESSED)
    {
        bKeyUsedFlag = true;

        if(pFuctionData->selfCheckInf.ucSelfCheckStep == CHECK_STEP_VERSION)//快速进入颜色检测
        {
            f_Beep(NORMAL);
            pFuctionData->selfCheckInf.ucSelfCheckStep = CHECK_STEP_LED_R;
            pFuctionData->selfCheckInf.bOnlyTest_LED = true;//仅检测led
        }
        else if(pFuctionData->selfCheckInf.bKey_4_P == false \
        && pFuctionData->selfCheckInf.ucSelfCheckStep == CHECK_STEP_KEY)
        {
            f_Beep(NORMAL);
            pFuctionData->selfCheckInf.bKey_4_P = true;
            pFuctionData->selfCheckInf.keyTuchNumb ++;
        }
        else if(pFuctionData->selfCheckInf.ucSelfCheckStep == CHECK_STEP_LOAD)
        {
            f_Beep(NORMAL);
            //负离子
            pFuctionData->sysAssistFlag.bAnionSw ^= true;

            if(pFuctionData->selfCheckInf.K4_TouchCnt <= 200)
                pFuctionData->selfCheckInf.K4_TouchCnt ++;
        }
    }
}

void f_Key5Deal_SC(BIG_STRUCT *pFuctionData)//电源键
{
    if(nKeyResultInf & PRESSED)
    {
        bKeyUsedFlag = true;


        if(pFuctionData->selfCheckInf.ucSelfCheckStep == CHECK_STEP_VERSION)
        {
            f_Beep(NORMAL);
            pFuctionData->selfCheckInf.ucSelfCheckStep ++;
            pFuctionData->selfCheckInf.ucCheckCnt = 0;
        }
        else if(pFuctionData->selfCheckInf.ucSelfCheckStep == CHECK_STEP_NUMB)
        {
            if(pFuctionData->selfCheckInf.ucCheckCnt >= 100)
            {
                f_Beep(NORMAL);
                pFuctionData->selfCheckInf.ucSelfCheckStep ++;
                pFuctionData->selfCheckInf.ucCheckCnt = 0;
            }
        }
        else if(pFuctionData->selfCheckInf.ucSelfCheckStep == CHECK_STEP_ICON_LED)
        {
            if(pFuctionData->selfCheckInf.bIcon_OK)//图标检测完成
            {
                f_Beep(NORMAL);
                pFuctionData->selfCheckInf.ucSelfCheckStep ++;
                pFuctionData->selfCheckInf.ucCheckCnt = 0;

                pFuctionData->selfCheckInf.keyTuchNumb = 1;
                pFuctionData->selfCheckInf.bKey_5_P = true;
            }
        }
        else if(pFuctionData->selfCheckInf.ucSelfCheckStep == CHECK_STEP_KEY)//检测按键
        {
            if(pFuctionData->selfCheckInf.keyTuchNumb == 5)//所有按键按下
            {
                f_Beep(NORMAL);
                pFuctionData->selfCheckInf.ucSelfCheckStep ++;
                pFuctionData->selfCheckInf.ucCheckCnt = 0;
            }
        }
        else if(pFuctionData->selfCheckInf.ucSelfCheckStep <= CHECK_STEP_LED_B)//显示背景灯
        {
            f_Beep(NORMAL);
            pFuctionData->selfCheckInf.ucSelfCheckStep ++;
            pFuctionData->selfCheckInf.ucCheckCnt = 0;
            pFuctionData->selfCheckInf.K4_TouchCnt = 0;

            if(pFuctionData->selfCheckInf.bOnlyTest_LED \
            && pFuctionData->selfCheckInf.ucSelfCheckStep == CHECK_STEP_LOAD)//仅检测led
            {
                pFuctionData->selfCheckInf.ucSelfCheckStep = CHECK_STEP_LED_R;
            }

            if(pFuctionData->selfCheckInf.bCheckLed)
            {
                pFuctionData->selfCheckInf.bShowAll ^= true;
            }
        }
        else if(pFuctionData->selfCheckInf.ucSelfCheckStep == CHECK_STEP_LOAD)
        {
            if(pFuctionData->selfCheckInf.ucCheckCnt >= 10 \
            && pFuctionData->fanSysInf.bFanErr == false \
            && pFuctionData->selfCheckInf.K4_TouchCnt >= 1)//1S以上且风机无故障,且按过负离子
            {
                f_Beep(NORMAL);
                pFuctionData->selfCheckInf.ucSelfCheckStep ++;
                pFuctionData->selfCheckInf.ucCheckCnt = 0;
            }
        }
    }
}


void f_KeyDeal_SC(BIG_STRUCT *pFuctionData)
{
    switch(KeyPressName)
    {
        case KEY_SIGNAL_PRESS_1://功能
            f_Key1Deal_SC(pFuctionData);
            break;

        case KEY_SIGNAL_PRESS_2://风速
            f_Key2Deal_SC(pFuctionData);
            break;

        case KEY_SIGNAL_PRESS_3://定时
            f_Key3Deal_SC(pFuctionData);
            break;

        case KEY_SIGNAL_PRESS_4://指示灯
            f_Key4Deal_SC(pFuctionData);
            break;

        case KEY_SIGNAL_PRESS_5://关机
            f_Key5Deal_SC(pFuctionData);
            break;

        default:
            break;
    }

    nKeyResultInf = NO_KEY;
}


void f_KeyDeal(void)
{

    switch(pFuctionData->SystemCurState)
    {
        case PowerOff_STATE:
            f_KeyDeal_Standby();
            break;

        case RUNNING_STATE:
            f_KeyDeal_Run();
            break;

        case SELFCHECK_STATE://自检
            f_KeyDeal_SC();
            break;

        default:
            break;
    }
}*/

void f_SendKeyNum(void)
{
    if (Send_Num_Key != 0)
    {
        f_SendDeal(&Uart1_Inf, USART1);
        Send_Num_Key = 0;
    }
}
void f_KeyDeal(void)
{
    f_KeyDeal_Run();
    f_SendKeyNum();
}
