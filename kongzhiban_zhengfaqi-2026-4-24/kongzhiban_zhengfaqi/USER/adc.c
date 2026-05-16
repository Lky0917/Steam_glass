
#include  "Headinclude.h"
#include  "sensor_const.h"

//#define   VAR_ADC_GLOBALS

//unsigned char index = 0;//下标
//unsigned int ADC_Value[10] = {0};

unsigned int ADC_Value[4][10] = {0},index[4] = {0},CntTmprtemplast = 0;
/************************
 函数名称：NTC_CheckTab()
 函数说明：二分法查温度的值
**************************/
unsigned char f_NTC_CheckTab(unsigned int ADC_Data)
{
	unsigned int cTabBottom,cTabTop;
	unsigned int ADC_tmp;
	unsigned int lens;
	unsigned int tmp;

	lens = 101;

	if(ADC_Data < Tmper[0])
		return 0;
	if(ADC_Data > Tmper[119])
		return 119;

	cTabBottom = 0;
	cTabTop = 119;
	tmp = (cTabTop+cTabBottom)/2;

	while((cTabTop-cTabBottom)!=1)
	{
		if(ADC_Data < Tmper[tmp])
		{
			cTabTop = tmp;
			tmp = (cTabTop+cTabBottom)/2;
		}
		else if(ADC_Data > Tmper[tmp])
		{
			cTabBottom = tmp;
			tmp = (cTabTop+cTabBottom)/2;
		}
		else
		{
			return tmp;
		}
	}
//需要根据上拉还是下拉决定上一个数据还是下一个数据
	ADC_tmp = (Tmper[tmp+1]+Tmper[tmp])/2;
	if(ADC_Data > ADC_tmp)
		tmp += 1;

	if(tmp >= 119)
		tmp = 119;

	return tmp;//下标即温度
}
//***************************************
//滤波算法,对数组进行排序去掉最大最小取平均值
//***************************************
unsigned int f_FilterMeanValue(unsigned int *ADC_Value)
{
	unsigned int lens = 10;
	unsigned int i,j,temp;
	for(i = 0;i < lens;i++)//冒泡排序
	{
		for(j = i;j < lens;j++)
		{
			if(ADC_Value[i] > ADC_Value[j])
			{
				temp = ADC_Value[i];
				ADC_Value[i] = ADC_Value[j];
				ADC_Value[j] = temp;
			}
		}
	}
	temp = (ADC_Value[3]+ADC_Value[4]+ADC_Value[5]+ADC_Value[6])>>2;
	return temp;
}

//****************************************
//查湿度表,根据温度值
//入口参数: 温度     湿度的AD转换值
//****************************************
unsigned int f_Hmdy_CheckTab(unsigned char Tmper,unsigned int ADC_Hmdy)
{
	unsigned int HmdyValue;
	unsigned char group,list,i;//查表数组的组和列
	unsigned char steplong = 0;
	//选定行数
	if(Tmper <=7 )
		group = 0;
	else if(Tmper <= 12)
		group = 1;
	else if(Tmper <= 17)
		group = 2;
	else if(Tmper <= 22)
		group = 3;
	else if(Tmper <= 27)
		group = 4;
	else if(Tmper <= 32)
		group = 5;
	else if(Tmper <= 37)
		group = 6;
	else if(Tmper <= 42)
		group = 7;
	else 
		group = 8;

	//查找列

	if(ADC_Hmdy > Hmdy[group][0])//超表范围
	{
		steplong = (4096 - Hmdy[group][0])/10;//数据分成十份
		for(i = 0;i < 10;i++)
		{
			if(ADC_Hmdy > (Hmdy[group][0]+i*steplong))
				break;
		}
		HmdyValue = 90+i;
	}
	else if(ADC_Hmdy < Hmdy[group][12])//超表
	{
		steplong = (Hmdy[group][12]/30);//分成30份
		for(i = 0;i < 30;i++)
		{
			if(ADC_Hmdy >(Hmdy[group][12] - i*steplong))
				break;
		}
		HmdyValue = 30-i;
	}
	else //表格处理
	{
		for(list = 0;list < 13;list++)
		{
			if(ADC_Hmdy >Hmdy[group][list])
			break;
		}
		
		HmdyValue = 90 - (list-1)*5;//大致范围，表格中基准，以下为细分
		steplong = (Hmdy[group][list-1] - Hmdy[group][list])/5;
		for(i=0;i<5;i++)
		{
			if(ADC_Hmdy > (Hmdy[group][list-1]-i*steplong))
				break;
		}
		HmdyValue -=i;
	}

	return HmdyValue;
}

//MchInf.ADCValue[0][MchInf.ADCIndex[0]++] = f_Get_Adc(ADC_Channel_0);
//if(MchInf.ADCIndex[0] >= 10)
//{
//	MchInf.ADCActValue[0] =  f_FilterMeanValue(MchInf.ADCValue[0]);
//	MchInf.Temper[0] = f_NTC_CheckTab(MchInf.ADCActValue[0]);
//}

void f_TmprDeal(unsigned char CHANNEL,unsigned char Num)//100ms调用一次
{
	
	unsigned int ADCValue = 0;
	unsigned int CntTmprtemp;

	ADC_Value[Num][index[Num]++] = f_Get_Adc(CHANNEL);
	if(index[Num] > 9)
	{
		index[Num] = 0;
		ADCValue = f_FilterMeanValue(ADC_Value[Num]);
		if(ADCValue < 50)//断路
		{
			  if(Num == 0)
					MchInf.bErrorTemper |= 0x01;
				else if(Num == 1)
					MchInf.bErrorTemper |= 0x10;

		}
		else if(ADCValue >= 4000)//短路
		{
				if(Num == 0)
					MchInf.bErrorTemper |= 0x02;
				else if(Num == 1)
					MchInf.bErrorTemper |= 0x20;
		}
		else
		{	
			  if(Num == 0)
					MchInf.bErrorTemper &= ~0x03;
				else if(Num == 1)
					MchInf.bErrorTemper &= ~0x30;
			
			CntTmprtemp = f_NTC_CheckTab(ADCValue);
			MchInf.ADCActValue[Num] = CntTmprtemp;
			MchInf.Temper[Num] = CntTmprtemp;

		}

		
	}
}


