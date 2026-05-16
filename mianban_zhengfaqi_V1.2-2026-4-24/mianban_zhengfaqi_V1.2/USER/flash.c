#include "HeadInclude.h"

#define FLASH_USER_START_ADDR  WRITE_START_ADDR   /* Start @ of user Flash area */
#define FLASH_USER_END_ADDR    WRITE_END_ADDR   /* End @ of user Flash area */


unsigned int eepromdata[20] = {0};

void Flash_Write(uint32_t Address, uint32_t* Data, uint32_t dataLen)
{
    FLASH_Status status;
    unsigned char i;
    /* Unlock the Flash Program Erase controller */
    FLASH_Unlock();

    /* Clear all pending flags */
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);

    /* Erase the user Flash area */
    status = FLASH_ErasePage(FLASH_USER_START_ADDR);
    if (status != FLASH_COMPLETE)
    {
        /* Error occurred while page erase */
        while(1);
    }
    for(i = 0; (i < dataLen)&&(status == FLASH_COMPLETE); i++)
    {
        status = FLASH_ProgramWord(Address, Data[i]);                                     // 写入一个字�?2位）的数据入指定地址
        Address = Address + 4;                                                                  // 地址偏移4个字�?
    }

    /* Program the user Flash area word by word */
   // status = FLASH_ProgramWord(Address, Data);
    if (status != FLASH_COMPLETE)
    {
        /* Error occurred while writing data in Flash memory */
        while(1);
    }

    /* Lock the Flash Program Erase controller */
    FLASH_Lock();
}

uint32_t Flash_Read(uint32_t Address)
{
    return (*(__IO uint32_t*)Address);
}

void Flash_Read_Data(uint32_t Address, uint32_t* Data, uint32_t dataLen)
{
    uint32_t i;
    for(i = 0; i < dataLen; i++)
    {
        Data[i] = Flash_Read(Address);
        Address += 4;
    }
}

void f_Flash_Write(void)
{
    eepromdata[0] = 0x55;
    eepromdata[1] = 0xaa;
    eepromdata[2] = MchInf.WaterHardState;
    eepromdata[3] = MchInf.zhengqijiworktimesum;
	eepromdata[4] = MchInf.timesAlamChuGouAgain;
    eepromdata[5] = MchInf.TmrLV;
    Flash_Write(FLASH_USER_START_ADDR, eepromdata, 20);
}
void f_Flash_read(void)
{
    Flash_Read_Data(FLASH_USER_START_ADDR, eepromdata, 20);
    if(eepromdata[0] == 0x55 && eepromdata[1] == 0xaa)
    {
        MchInf.WaterHardState = eepromdata[2];
        MchInf.zhengqijiworktimesum = eepromdata[3];
		MchInf.timesAlamChuGouAgain = eepromdata[4];
		MchInf.TmrLV = eepromdata[5];
    }
}
