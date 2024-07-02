#include "STM_Config.h"

#define FLASH_CLEAR_BYTE 0
#define FLASH_SET_BYTE   0xFF
#define OPERATION_TIMEOUT  0xFFFFF


void FLASH_Unlock(uint8 ival)
{
    if (ival == FLASH_MEMTYPE_PROG)  //prog
    {
        FLASH_PUKR = FLASH_RASS_KEY1;
        FLASH_PUKR = FLASH_RASS_KEY2;
    }
    else  //data
    {
        FLASH_DUKR = FLASH_RASS_KEY2;
        FLASH_DUKR = FLASH_RASS_KEY1;
    }   
}

void FLASH_Lock(uint8 ival)
{
  FLASH_IAPSR &= ival;
}


void FLASH_ProgramOptionByte(uint16 Address, uint8 Data)
{
 
    // Enable write access to option bytes 
    FLASH_CR2 |= (1<<7);
    FLASH_NCR2 &= ~(1<<7);

    // check if the option byte to program is ROP
    if (Address == 0x4800)
    {
       // Program option byte
       *((NEAR uint8*)Address) = Data;
    }
    else
    {
       // Program option byte and his complement 
       *((NEAR uint8*)Address) = Data;
       *((NEAR uint8*)((uint16)(Address + 1))) = (uint8)(~Data);
    }
    FLASH_WaitForLastOperation(FLASH_MEMTYPE_PROG);

    // Disable write access to option bytes 
    FLASH_CR2 &= ~(1<<7);
    FLASH_NCR2 |= (1<<7);
    
}

void FLASH_EraseOptionByte(uint16 Address)
{

    // Enable write access to option bytes 
    FLASH_CR2 |= (1<<7);
    FLASH_NCR2 &= ~(1<<7);

     /* check if the option byte to erase is ROP */
     if (Address == 0x4800)
    {
       /* Erase option byte */
       *((NEAR uint8*)Address) = FLASH_CLEAR_BYTE;
    }
    else
    {
       /* Erase option byte and his complement */
       *((NEAR uint8*)Address) = FLASH_CLEAR_BYTE;
       *((NEAR uint8*)((uint16)(Address + (uint16)1 ))) = FLASH_SET_BYTE;
    }
    FLASH_WaitForLastOperation(FLASH_MEMTYPE_PROG);

    // Disable write access to option bytes 
    FLASH_CR2 &= ~(1<<7);
    FLASH_NCR2 |= (1<<7);
}


uint8 FLASH_WaitForLastOperation(uint8 FLASH_MemType) 
{
    uint8 flagstatus = 0x00;
    uint32 timeout = 0;
    
    timeout = OPERATION_TIMEOUT;
    
    /* Wait until operation completion or write protection page occurred */
#if defined (STM8S208) || defined(STM8S207) || defined(STM8S007) || defined(STM8S105) || \
    defined(STM8S005) || defined(STM8AF52Ax) || defined(STM8AF62Ax) || defined(STM8AF626x)  
    if (FLASH_MemType == FLASH_MEMTYPE_PROG)
    {
        while ((flagstatus == 0x00) && (timeout != 0x00))
        {
            flagstatus = FLASH_IAPSR & ( (1<<2)|(1<<0) );
            timeout--;
        }
    }
    else
    {
        while ((flagstatus == 0x00) && (timeout != 0x00))
        {
            flagstatus = FLASH_IAPSR & ( (1<<6)|(1<<0) );
            timeout--;
        }
    }
#else /*STM8S103, STM8S903*/
    while ((flagstatus == 0x00) && (timeout != 0x00))
    {
        flagstatus = FLASH_IAPSR & ( (1<<2)|(1<<0) );
        timeout--;
    }

#endif /* STM8S208, STM8S207, STM8S105, STM8AF52Ax, STM8AF62Ax, STM8AF262x */
    
    if (timeout == 0x00 )
    {
        flagstatus = FLASH_STATUS_TIMEOUT;
    }

    return(flagstatus);
}