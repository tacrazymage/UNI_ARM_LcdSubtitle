#ifndef TF_LCD_H
#define TF_LCD_H
#include "stm32f0xx.h"


#define GPIO_Pin_0	((uint16_t)0x0001)
#define GPIO_Pin_1	((uint16_t)0x0002)
#define GPIO_Pin_2	((uint16_t)0x0004)
#define GPIO_Pin_3	((uint16_t)0x0008)
#define GPIO_Pin_4	((uint16_t)0x0010)
#define GPIO_Pin_5	((uint16_t)0x0020)
#define GPIO_Pin_6	((uint16_t)0x0040)
#define GPIO_Pin_7	((uint16_t)0x0080)


/*
PA0 --> DB4
PA1 --> DB5
PA2 --> DB6
PA3 --> DB7
PA4 --> BLA
PA5 --> RS
PA6 --> RW
PA7 --> E
*/


#define TF_LCD_RS_Set	(GPIOA->ODR |= GPIO_Pin_5) //data
#define TF_LCD_RS_Reset	(GPIOA->ODR &= ~GPIO_Pin_5) //intraction
#define TF_LCD_RW_Set	(GPIOA->ODR |= GPIO_Pin_6) //read
#define TF_LCD_RW_Reset	(GPIOA->ODR &= ~GPIO_Pin_6) //write
#define TF_LCD_E_Set	(GPIOA->ODR |= GPIO_Pin_7)
#define TF_LCD_E_Reset	(GPIOA->ODR &= ~GPIO_Pin_7)

#define TF_LCD_SDB4	(GPIOA->ODR |= GPIO_Pin_0)
#define TF_LCD_RDB4	(GPIOA->ODR &= ~GPIO_Pin_0)
#define TF_LCD_SDB5	(GPIOA->ODR |= GPIO_Pin_1)
#define TF_LCD_RDB5	(GPIOA->ODR &= ~GPIO_Pin_1)
#define TF_LCD_SDB6	(GPIOA->ODR |= GPIO_Pin_2)
#define TF_LCD_RDB6	(GPIOA->ODR &= ~GPIO_Pin_2)
#define TF_LCD_SDB7	(GPIOA->ODR |= GPIO_Pin_3)
#define TF_LCD_RDB7	(GPIOA->ODR &= ~GPIO_Pin_3)

#define TF_LCD_BL_On	(GPIOA->ODR |= GPIO_Pin_4)
#define TF_LCD_BL_Off	(GPIOA->ODR &= ~GPIO_Pin_4)


void TF_lcdInit(void);
void TF_lcdDisplayControl(void);
void TF_lcdClear(void);
void TF_lcdGotoXY(uint8_t x, uint8_t y);
void TF_lcdPrintCh(uint8_t ch);
void TF_lcdPrint(uint8_t* str);
#endif
