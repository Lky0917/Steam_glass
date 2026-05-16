#include  "Headinclude.h"

unsigned char idata RceKey[LEN_RECE_DATA] = {0};
unsigned char KeyNum = 0;
unsigned char key_IR = 0;
unsigned char SendData[LEN_SEND_DATA] = {0};
unsigned char SendDataInt[LEN_SEND_DATA] = {0};
unsigned char KeyGetIR = 0;

unsigned int TmInt = 0;

byte_def NECFlag;
#define  bNStartRec      NECFlag.m_bit.b0
#define  bNStartSend     NECFlag.m_bit.b1
#define  bNSucceRce      NECFlag.m_bit.b2
#define  bNSendOverBit   NECFlag.m_bit.b3
#define  nNECFlag		 NECFlag.m_byte


TYPE_INT idata KeyIRFlag;
#define   bKeyIR_Power     KeyIRFlag.int_bit.b0
#define   bKeyIR_Timer     KeyIRFlag.int_bit.b1
#define   bKeyIR_Sleep     KeyIRFlag.int_bit.b2
#define   bKeyIR_CF        KeyIRFlag.int_bit.b3
#define   bKeyIR_LOW       KeyIRFlag.int_bit.b4
#define   bKeyIR_High      KeyIRFlag.int_bit.b5
#define   bKeyIR_Strong    KeyIRFlag.int_bit.b6
#define   bKeyIR_Cool      KeyIRFlag.int_bit.b7
#define   bKeyIR_Dry       KeyIRFlag.int_bit.b8
#define   bKeyIR_Fan       KeyIRFlag.int_bit.b9
#define   bKeyIR_UP        KeyIRFlag.int_bit.b10
#define   bKeyIR_DOWN      KeyIRFlag.int_bit.b11
#define   bKeyIR_SWING     KeyIRFlag.int_bit.b12
#define   bKeyIR_Lock      KeyIRFlag.int_bit.b13
#define   bKeyIR_Mode      KeyIRFlag.int_bit.b14
#define   bKeyIR_FanCtrl   KeyIRFlag.int_bit.b15


#define   nKeyIRFlag       KeyIRFlag.int_byte

TYPE_INT idata KeyIRFlag1;
#define   bKeyIR_Heat     KeyIRFlag1.int_bit.b0
#define   bKeyIR_Auto     KeyIRFlag1.int_bit.b1
#define   bKeyIR_Saving   KeyIRFlag1.int_bit.b2
#define   bKeyIR_SC       KeyIRFlag1.int_bit.b3

#define   nKeyIRFlag1       KeyIRFlag1.int_byte



NECSendSTATE NECSendState;

void f_NECInit(void)
{
	nKeyIRFlag1 = 0;
	nKeyIRFlag = 0;
	nNECFlag = 0;
}

/*
void f_INTREC(void)
{
	static volatile  unsigned char idata index = 0;
	static volatile  unsigned char idata LENRCE = 0;
	if(bNStartRec)
	{
		RceKey[KeyNum] <<= 1;			
		index ++;

		if((TmInt >= 120))// 13.44   
		{
			RceKey[KeyNum] |= 0x01;
		}
		if(index > 7)
		{
			KeyNum ++;
			index = 0;
		}
		if(KeyNum >= 1)//接收一个字节
		{
			if(RceKey[0] == 0x55)
			{
				LENRCE = 9;
				bLcdChoice = 1;
			}
			
			if(KeyNum >= LENRCE)
			{
				bNStartRec = 0;
				bNSucceRce = 1;
				TR3 = 0;
				TmInt = 0;
			}
		}
		
	}
	else
	{
		if(TmInt >= 150)
		{

			bNStartRec = 1;
			for(index = 0;index<LEN_RECE_DATA;index++)
				RceKey[index] = 0;

			index = 0;
			KeyNum = 0;
		}
	}

	TmInt = 0;
}
*/

void f_NEC_Rec(void)
{
	static volatile  unsigned char idata RecState = 0;
	static volatile  unsigned char idata RecStateLast = 0;
	static volatile  unsigned char idata Tm_IO = 0,index = 0;
	static volatile  unsigned char idata LENRCE = 0;

	if(pIRReceive)
		RecState = 1;
	else
		RecState = 0;
	Tm_IO ++;

	if(bNStartRec)
	{
		if((RecState != RecStateLast)&&(RecState == 0))
		{		
			RceKey[KeyNum] <<= 1;			
			index ++;

			if((Tm_IO >= 8))//&&(Tm_IO <= 16))// 13.44   
			{
				RceKey[KeyNum] |= 0x01;
			}
			if(index > 7)
			{
				KeyNum ++;
				index = 0;
			}
			if(KeyNum >= 1)//接收一个字节
			{
			/*	if(RceKey[0] == 0x08)//四个字节
				{
					LENRCE = 4;
					bLcdChoice = 0;
				}
				else 
			*/
				if(RceKey[0] == 0x55)
				{
					LENRCE = 9;
					bLcdChoice = 1;
				}
			
				if(KeyNum >= LENRCE)
				{
					bNStartRec = 0;
					bNSucceRce = 1;
				}
			}
		}
	}
	else
	{
		if((RecState != RecStateLast)&&(RecState == 0)&&(Tm_IO>=35)&&(Tm_IO <=45))//1ms  16   36 下降沿
		{
			Tm_IO = 0;
			bNStartRec = 1;
			for(index = 0;index<LEN_RECE_DATA;index++)
				RceKey[index] = 0;

			index = 0;
			KeyNum = 0;
		}
	}
	if(RecState != RecStateLast)
		Tm_IO = 0;
	
	RecStateLast = RecState;

}
/*
unsigned char TimeNECSend = 0;

void f_NEC_Send(void)
{
	
	static unsigned char indexSendByte = 0;
	static unsigned char indexSendBit = 0;
	#define  TIME_IO_1    8
	#define  TIME_IO_0    4
	
	if(bNStartSend)
	{
		TimeNECSend ++;
		SET_BANK0();
		switch(NECSendState)
		{
			case NEC_SEND_START:
				IO_SEND = 0;//低电平 1ms
				if(TimeNECSend > 32)
				{
					TimeNECSend = 0;
					NECSendState = NEC_SEND_INT;
					indexSendBit = 0;
					indexSendByte = 0;
				}
				break;
			case NEC_SEND_INT:
				IO_SEND = 1;
				if(TimeNECSend > TIME_IO_0)//125us
				{
					TimeNECSend = 0;
					NECSendState = NEC_SEND_DATA;
					bNSendOverBit = 0;
				}
				break;
				
			case NEC_SEND_DATA:				
				IO_SEND = 0;
				if(SendData[indexSendByte] & 0x01)
				{
					if(TimeNECSend > TIME_IO_1)
					{
						bNSendOverBit = 1;						
					}
				}
				else if(TimeNECSend > TIME_IO_0)
				{
					bNSendOverBit = 1;
				}
				
				if(bNSendOverBit)
				{
					bNSendOverBit = 0;
					TimeNECSend = 0;
					NECSendState = NEC_SEND_INT;
					indexSendBit++;
					SendData[indexSendByte] >>= 1;
					if(indexSendBit >= 8)//一个字节
					{
						indexSendBit = 0;
						indexSendByte ++;
						if(indexSendByte > LEN_SEND_DATA)//over
						{
							NECSendState = NEC_SEND_STOP;
						}
					}
				}				
				break;
			case NEC_SEND_STOP:
				IO_SEND = 1;
				bNStartSend = 0;
				break;
			default:break;
		}
	}
	else
		IO_SEND = 1;
}

void f_NECStart(void)
{
	unsigned char i;
	for(i = 1;i <4;i++)
		SendDataInt[i-1] = SendData[i];
	
	TimeNECSend = 0;
	bNStartSend = 1;
	NECSendState = NEC_SEND_START;
	
}

void f_IRKeyGet(void)
{
	if(bNSucceRce)
	{
		bNSucceRce = 0;
		nKeyIRFlag = 0;
		nKeyIRFlag1 = 0;
		switch(key_IR )
		{
			case 0x00://power
				bKeyIR_Power = 1;
				break;
			case 0x80://timer
				bKeyIR_Timer = 1;
				break;
			case 0xA0://sleep
				bKeyIR_Sleep = 1;
				break;
			case 0x20://CF
				bKeyIR_CF = 1;
				break;
			case 0x50://low
				bKeyIR_LOW = 1;
				break;
			case 0x70://strong
				bKeyIR_Strong = 1;
				break;
			case 0x68://high
				bKeyIR_High = 1;
				break;
			case 0x60:// swing
				bKeyIR_SWING = 1;
				break;
			case 0x28://cool
				bKeyIR_Cool= 1;
				break;
			case 0x30://dry
				bKeyIR_Dry = 1;
				break;
			case 0x10://Fan
				bKeyIR_Fan = 1;
				break;
			case 0xA8://up
				bKeyIR_UP = 1;
				break;
			case 0xB0://down
				bKeyIR_DOWN = 1;
				break;

			default:break;
		}
		key_IR = 0;
	}
}
*/