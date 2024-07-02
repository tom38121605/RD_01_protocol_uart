
//#include "Public.h"


//#define OPT_BaseAddress         0x4800
#define GPIOA_BaseAddress       0x5000
#define GPIOB_BaseAddress       0x5005
#define GPIOC_BaseAddress       0x500A
#define GPIOD_BaseAddress       0x500F
#define GPIOE_BaseAddress       0x5014
#define GPIOF_BaseAddress       0x5019
//#define GPIOG_BaseAddress       0x501E
//#define GPIOH_BaseAddress       0x5023
//#define GPIOI_BaseAddress       0x5028
//#define FLASH_BaseAddress       0x505A
//#define EXTI_BaseAddress        0x50A0
//#define RST_BaseAddress         0x50B3
//#define CLK_BaseAddress         0x50C0
//#define WWDG_BaseAddress        0x50D1
//#define IWDG_BaseAddress        0x50E0
//#define AWU_BaseAddress         0x50F0
//#define BEEP_BaseAddress        0x50F3
//#define SPI_BaseAddress         0x5200
//#define I2C_BaseAddress         0x5210
//#define UART1_BaseAddress       0x5230
//#define UART2_BaseAddress       0x5240
//#define UART3_BaseAddress       0x5240
//#define TIM1_BaseAddress        0x5250
//#define TIM2_BaseAddress        0x5300
//#define TIM3_BaseAddress        0x5320
//#define TIM4_BaseAddress        0x5340
//#define TIM5_BaseAddress        0x5300
//#define TIM6_BaseAddress        0x5340
//#define ADC1_BaseAddress        0x53E0
//#define ADC2_BaseAddress        0x5400
//#define CAN_BaseAddress         0x5420
//#define CFG_BaseAddress         0x7F60
//#define ITC_BaseAddress         0x7F70
//#define DM_BaseAddress          0x7F90

#define     __I     volatile const   //!< defines 'read only' permissions     
#define     __O     volatile         //!< defines 'write only' permissions    
#define     __IO    volatile         //!< defines 'read / write' permissions  


typedef struct GPIO_struct
{
  __IO unsigned char ODR; //!< Output Data Register 
  __IO unsigned char IDR; //!< Input Data Register 
  __IO unsigned char DDR; //!< Data Direction Register 
  __IO unsigned char CR1; //!< Configuration Register 1 
  __IO unsigned char CR2; //!< Configuration Register 2 
}
GPIO_TypeDef;


#define GPIOA ((GPIO_TypeDef *) GPIOA_BaseAddress)
#define GPIOB ((GPIO_TypeDef *) GPIOB_BaseAddress)
#define GPIOC ((GPIO_TypeDef *) GPIOC_BaseAddress)
#define GPIOD ((GPIO_TypeDef *) GPIOD_BaseAddress)
#define GPIOE ((GPIO_TypeDef *) GPIOE_BaseAddress)
#define GPIOF ((GPIO_TypeDef *) GPIOF_BaseAddress)





#ifdef RAM_EXECUTION
 #ifdef _COSMIC_
   #define IN_RAM(a) a
 #elif defined (_RAISONANCE_) // __RCST7__ 
   #define IN_RAM(a) a inram
 #else //_IAR_
  #define IN_RAM(a) __ramfunc a
 #endif // _COSMIC_ 
#else 
  #define IN_RAM(a) a
#endif // RAM_EXECUTION 

#ifdef _COSMIC_
 #define FAR  @far
 #define NEAR @near
 #define TINY @tiny
 #define EEPROM @eeprom
 #define CONST  const
#elif defined (_RAISONANCE_) // __RCST7__ 
 #define FAR  far
 #define NEAR data
 #define TINY page0
 #define EEPROM eeprom
 #define CONST  code
 #if defined (STM8S208) || defined (STM8S207) || defined (STM8S007) || defined (STM8AF52Ax) || \
     defined (STM8AF62Ax)
   //!< Used with memory Models for code higher than 64K 
  #define MEMCPY fmemcpy
 #else // STM8S903, STM8S103, STM8S003, STM8S105, STM8AF626x 
 //!< Used with memory Models for code less than 64K 
  #define MEMCPY memcpy
 #endif // STM8S208 or STM8S207 or STM8S007 or STM8AF62Ax or STM8AF52Ax  
#else //_IAR_
 #define FAR  __far
 #define NEAR __near
 #define TINY __tiny
 #define EEPROM __eeprom
 #define CONST  const
#endif /* __CSMC__ */


/*typedef enum {
#if defined (STM8S208) || defined(STM8S207) || defined(STM8S007) || defined(STM8S105) || \
    defined(STM8S005) || defined (STM8AF52Ax) || defined (STM8AF62Ax) || defined(STM8AF626x)		
		FLASH_STATUS_END_HIGH_VOLTAGE           = (uint8)0x40, //!< End of high voltage 
#endif //STM8S208, STM8S207, STM8S105, STM8AF62Ax, STM8AF52Ax, STM8AF626x 
		FLASH_STATUS_SUCCESSFUL_OPERATION       = (uint8)0x04, //!< End of operation flag 
		FLASH_STATUS_TIMEOUT = (uint8)0x02, //!< Time out error 
    FLASH_STATUS_WRITE_PROTECTION_ERROR     = (uint8)0x01 //!< Write attempted to protected page 
} FLASH_Status_TypeDef;
*/


#ifdef _COSMIC_
 #define INTERRUPT @far @interrupt
#elif defined(_IAR_)
 #define INTERRUPT __interrupt
#endif // _COSMIC_ 



