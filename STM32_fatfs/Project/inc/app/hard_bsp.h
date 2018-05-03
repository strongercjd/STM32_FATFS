#ifndef _HARD_BSP_H
#define _HARD_BSP_H 
#include "main.h"
#include "misc.h"
#include "stm32f2xx_usart.h"
#include "stm32f2xx_gpio.h"
#include "stm32f2xx_rcc.h"
#include "stm32f2xx_tim.h"

/*! 
 * 指示灯
 * LED-PB2
 */ 
#define  LED_ODR_OFFSET (GPIOB_BASE+0x14 - PERIPH_BASE)

#define  LED_BitNumber       2
#define  IO_LED_BB           (PERIPH_BB_BASE + (LED_ODR_OFFSET * 32) + (LED_BitNumber * 4))    
#define  IO_LED_DATA_BASE    *(__IO uint32_t *)IO_LED_BB

  
#define   LED_ON()   	IO_LED_DATA_BASE = 0 
#define   LED_OFF()  	IO_LED_DATA_BASE = 1

typedef unsigned char  uint8;                   /* defined for unsigned 8-bits integer variable 	无符号8位整型变量  */
typedef signed   char  int8;                    /* defined for signed 8-bits integer variable		有符号8位整型变量  */
typedef unsigned short uint16;                  /* defined for unsigned 16-bits integer variable 	无符号16位整型变量 */
typedef signed   short int16;                   /* defined for signed 16-bits integer variable 		有符号16位整型变量 */
typedef unsigned int   uint32;                  /* defined for unsigned 32-bits integer variable 	无符号32位整型变量 */
typedef signed   int   int32;                   /* defined for signed 32-bits integer variable 		有符号32位整型变量 */
typedef float          fp32;                    /* single precision floating point variable (32bits) 单精度浮点数（32位长度） */
typedef double         fp64;                    /* double precision floating point variable (64bits) 双精度浮点数（64位长度） */





void LED_Init(void);
void LED_ray_run(void);
void timer4Init(void);
void UART_Init(void);
uint8 SPI_ReadWriteByte(uint8 data);
void  SPIInit(void);
#endif













