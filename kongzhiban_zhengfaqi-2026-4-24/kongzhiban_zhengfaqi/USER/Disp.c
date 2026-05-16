#include "HeadInclude.h"
#include "Disp_const.h"

unsigned int size;
unsigned char HRES,VRES_byte1,VRES_byte2;

#ifdef  LED_DISP
LEDDISP  LED_Disp;

void f_Disp2LED(LEDDISP* LEDDisp)//1s调用
{
	unsigned char i = 0;
	static unsigned char NumCount = 0;

	INTERRUPT_ALL_CLOSE;
	for(i = 0;i < 10;i++)
		LEDDisp->Disp_Buffer[i] = nTab_Number[NumCount];
	INTERRUPT_ALL_OPED;	

	NumCount++;
	if(NumCount > 9)
		NumCount = 0;

}
void f_LED_Close(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_12);
	GPIO_SetBits(GPIOC,GPIO_Pin_1);
	GPIO_SetBits(GPIOC,GPIO_Pin_2);
	GPIO_SetBits(GPIOC,GPIO_Pin_3);
	GPIO_SetBits(GPIOC,GPIO_Pin_10);
	GPIO_SetBits(GPIOC,GPIO_Pin_11);
	GPIO_SetBits(GPIOC,GPIO_Pin_12);
	GPIO_SetBits(GPIOC,GPIO_Pin_13);
	GPIO_SetBits(GPIOC,GPIO_Pin_14);
	GPIO_SetBits(GPIOC,GPIO_Pin_15);
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_3);
	GPIO_ResetBits(GPIOB,GPIO_Pin_4);
	GPIO_ResetBits(GPIOB,GPIO_Pin_5);
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);
	GPIO_ResetBits(GPIOB,GPIO_Pin_9);
	GPIO_ResetBits(GPIOD,GPIO_Pin_2);
}

void LED_SEG_8(unsigned char LED_Seg)
{
	if(LED_Seg & 0x01)
		LED_SEG_A_ON;
	if(LED_Seg & 0x02)
		LED_SEG_B_ON;
	if(LED_Seg & 0x04)
		LED_SEG_C_ON;
	if(LED_Seg & 0x08)
		LED_SEG_D_ON;
	if(LED_Seg & 0x10)
		LED_SEG_E_ON;			
	if(LED_Seg & 0x20)
		LED_SEG_F_ON;
	if(LED_Seg & 0x40)
		LED_SEG_G_ON;
	if(LED_Seg & 0x80)
		LED_SEG_H_ON;

}
void f_Disp_LED(LEDDISP* LEDDisp)//1ms调用
{
	f_LED_Close();

	switch(LEDDisp->Num_State)
	{
		case 0:
			LED_SEG_8(LEDDisp->Disp_Buffer[0]);
			LED_COM1_ON;
			break;
		case 1:
			LED_SEG_8(LEDDisp->Disp_Buffer[1]);
			LED_COM2_ON;
			break;
		case 2:
			LED_SEG_8(LEDDisp->Disp_Buffer[2]);
			LED_COM3_ON;
			break;
		case 3:
			LED_SEG_8(LEDDisp->Disp_Buffer[3]);
			LED_COM4_ON;
			break;
		case 4:
			LED_SEG_8(LEDDisp->Disp_Buffer[4]);
			LED_COM5_ON;
			break;
		case 5:
			LED_SEG_8(LEDDisp->Disp_Buffer[5]);
			LED_COM6_ON;
			break;
		case 6:
			LED_SEG_8(LEDDisp->Disp_Buffer[6]);
			LED_COM7_ON;
			break;
		case 7:
			LED_SEG_8(LEDDisp->Disp_Buffer[7]);
			LED_COM8_ON;
			break;
		case 8:
			LED_SEG_8(LEDDisp->Disp_Buffer[8]);
			LED_COM9_ON;
			break;
		case 9:
			LED_SEG_8(LEDDisp->Disp_Buffer[9]);
			LED_COM10_ON;
			break;
		default:break;
	}
	LEDDisp->Num_State++;
	if(LEDDisp->Num_State > 9)
		LEDDisp->Num_State = 0;
}
#endif






#ifdef  EPD_DISP
void driver_delay_xms(unsigned long xms) //1ms
{	
    unsigned long i = 0 , j=0;

    for(j=0;j<xms;j++)
	{
        for(i=0; i<256; i++);
  }
}


void SPI_Write(unsigned char value)                                    
{                                                           
    unsigned char i;

    for(i=0; i<8; i++)   
    {
        EPD_W21_CLK_0;

        if(value & 0x80)
        	EPD_W21_MOSI_1;
        else
					EPD_W21_MOSI_0;		
        value = (value << 1);
				
        EPD_W21_CLK_1; 
    }
}

void EPD_W21_WriteCMD(unsigned char command)
{
	EPD_W21_CS_0;                   
	EPD_W21_DC_0;
	SPI_Write(command);
	EPD_W21_CS_1;
}
void EPD_W21_WriteDATA(unsigned char command)
{
	EPD_W21_CS_0;                   
	EPD_W21_DC_1;	
	SPI_Write(command);
	EPD_W21_CS_1;
}

void EPD_reset(void)
{
	EPD_W21_RST_0;
	driver_delay_xms(1000);
	EPD_W21_RST_1;
	driver_delay_xms(1000);
}

void Wait_EPD_BUSY(void)
{
	unsigned char busy;
	do
	{
		EPD_W21_WriteCMD(0x71);
		busy = Wait_BUSY_IO;
		busy =!(busy & 0x01);        
	}
	while(busy);   
	driver_delay_xms(200);                       
}

void EPD_init(void)
{
	  HRES=0x98;						//152  0x98
	  VRES_byte1=0x01;			//296  0x128
	  VRES_byte2=0x28;
		
		EPD_reset();
	
		EPD_W21_WriteCMD(0x06);     //boost soft start
		EPD_W21_WriteDATA (0x17);		//A
		EPD_W21_WriteDATA (0x17);		//B
		EPD_W21_WriteDATA (0x17);		//C       

		EPD_W21_WriteCMD(0x04);  
		Wait_EPD_BUSY();//waiting for the electronic paper IC to release the idle signal

		EPD_W21_WriteCMD(0x00);			//panel setting
		EPD_W21_WriteDATA(0xc7);

		EPD_W21_WriteCMD(0x61);			//resolution setting
		EPD_W21_WriteDATA (HRES);        	 
		EPD_W21_WriteDATA (VRES_byte1);		
		EPD_W21_WriteDATA (VRES_byte2);

		EPD_W21_WriteCMD(0X50);			//VCOM AND DATA INTERVAL SETTING			
		EPD_W21_WriteDATA(0x77);		//WBmode:VBDF 17|D7 VBDW 97 VBDB 57		WBRmode:VBDF F7 VBDW 77 VBDB 37  VBDR B7
}

void EPD_refresh(void)
{
		EPD_W21_WriteCMD(0x12);			//DISPLAY REFRESH 	
		driver_delay_xms(100);	        //!!!The delay here is necessary, 200uS at least!!!     
		Wait_EPD_BUSY();
}	
void EPD_sleep(void)
{
		EPD_W21_WriteCMD(0X02);  	//power off
		Wait_EPD_BUSY();//waiting for the electronic paper IC to release the idle signal
		EPD_W21_WriteCMD(0X07);  	//deep sleep
		EPD_W21_WriteDATA(0xA5);
}



void EPD_BLACK_REFLASH(int xs,int xe,int ys,int ye)
{
	int i,j;
	EPD_W21_WriteCMD(0x13);	       //Transfer old data
	for(i=0;i<296;i++)	     
	{
			for(j=0;j<19;j++)	     
			{
					if (j>=ys && j<ye && i>=xs && i<xe)EPD_W21_WriteDATA(0xff);
					else EPD_W21_WriteDATA(0x00);
			}
	}
}


void EPD_BLACK(const unsigned char* data)
{
    unsigned int i;
		EPD_W21_WriteCMD(0x10);	       //Transfer old data
	  for(i=0;i<5624;i++)	     
	{
	  EPD_W21_WriteDATA(data[i]);
	}
}

void EPD_RED(const unsigned char* data)
{
    unsigned int i;
		EPD_W21_WriteCMD(0x13);	       //Transfer old data
	  for(i=0;i<5624;i++)	     
	{
	  EPD_W21_WriteDATA(0xff);
	}
}


void f_Disp(void)
{
	EPD_init(); 
	EPD_BLACK(gImage_data);
//	EPD_RED(gImage_data);
		
	EPD_refresh();	
	EPD_sleep();
}
#endif

void f_Disp(void)
{
	unsigned  int i,temp;
	static unsigned int temp1;
		for(i = 0;i<10;i++)
			MchInf.Dispbuffer[i] = 0x00;
	

		if((MchInf.WaterLevel &0x08) == 0x08)
		{
			if((MchInf.bErrorTemper&0x03 )==0)
			{
			temp1 = MchInf.ADCActValue[0];
			MchInf.Dispbuffer[0] = nTab_Number[temp1/100];
	
			temp = temp1/10;
			temp = temp%10;
			
			MchInf.Dispbuffer[2] = nTab_Number[temp];
		
			temp = temp1%10;

			MchInf.Dispbuffer[4] = nTab_Number[temp];
			}
			else if((MchInf.bErrorTemper&0x03 )==0x01)
			{
				MchInf.Dispbuffer[0] = nTab_Number[2];//E
				MchInf.Dispbuffer[2] = nTab_Number[24];
				MchInf.Dispbuffer[4] = nTab_Number[21];
			}
			else if((MchInf.bErrorTemper&0x03 )==0x02)
			{
				MchInf.Dispbuffer[0] = nTab_Number[31];//E
				MchInf.Dispbuffer[2] = nTab_Number[0];
				MchInf.Dispbuffer[4] = nTab_Number[18];
			}
		}
		else
		{
			if((MchInf.bErrorTemper&0x30 )==0)
			{
			temp1 = MchInf.ADCActValue[1];
			MchInf.Dispbuffer[0] = nTab_Number[temp1/100];
	
			temp = temp1/10;
			temp = temp%10;
			
			MchInf.Dispbuffer[2] = nTab_Number[temp];
		
			temp = temp1%10;

			MchInf.Dispbuffer[4] = nTab_Number[temp];
			}
			else if((MchInf.bErrorTemper&0x30 )==0x10)
			{
				MchInf.Dispbuffer[0] = nTab_Number[1];//E
				MchInf.Dispbuffer[2] = nTab_Number[24];
				MchInf.Dispbuffer[4] = nTab_Number[21];
			}
			else if((MchInf.bErrorTemper&0x30 )==0x20)
			{
				MchInf.Dispbuffer[0] = nTab_Number[31];//E
				MchInf.Dispbuffer[2] = nTab_Number[24];
				MchInf.Dispbuffer[4] = nTab_Number[18];
			}
		}
		

	//		MchInf.Dispbuffer[0] = 0x40;//1A  2B 3C 4D 5E 6F 7G
	//	if(MchInf.bDispDark)
	//		TM1620B_work(MchInf.Dispbuffer,TM1628_CMD_DARK);
	//	else
			TM1620B_work(MchInf.Dispbuffer,TM1628_CMD_DISP);	
}
