//ÑÓÊ±Ä£¿é
#ifndef __FLASH_H
#define __FLASH_H


#define FLASH_MEMTYPE_PROG 0xFD 
#define FLASH_MEMTYPE_DATA 0xF7 

#define FLASH_RASS_KEY1  0x56  // First RASS key 
#define FLASH_RASS_KEY2  0xAE  // Second RASS key 

#define HSE_CLOCK_STARTUP_ADDRESS  0x4809
#define FLASH_WAIT_STATES_ADDRESS 0x480D

#define FLASH_STATUS_TIMEOUT 0x02


void FLASH_Unlock(uint8 ival);
void FLASH_Lock(uint8 ival);

void FLASH_ProgramOptionByte(uint16 Address, uint8 Data);
void FLASH_EraseOptionByte(uint16 Address);

uint8 FLASH_WaitForLastOperation(uint8 FLASH_MemType);


#endif
