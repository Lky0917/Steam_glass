#ifndef _FLASH_H
#define _FLASH_H

#include "HeadInclude.h"

#define WRITE_START_ADDR        ((uint32_t)0x08008000)
#define WRITE_END_ADDR          ((uint32_t)0x0800C000)

void Flash_Write(uint32_t Address, uint32_t* Data, uint32_t dataLen);
uint32_t Flash_Read(uint32_t Address);

extern unsigned int eepromdata[20];
void f_Flash_Write(void);
void Flash_Read_Data(uint32_t Address, uint32_t* Data, uint32_t dataLen);
void f_Flash_read(void);
#endif