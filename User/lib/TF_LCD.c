#include "TF_LCD.h"
void delayUs(uint32_t us);

void TF_lcdInit(void){
	//4bit operation
	TF_LCD_RS_Reset;
	TF_LCD_RW_Reset;
	TF_LCD_E_Set;
	TF_LCD_RDB7;
	TF_LCD_RDB6;
	TF_LCD_SDB5;
	TF_LCD_RDB4;
	TF_LCD_E_Reset;
	delayUs(40);

	//4bit & 2line & 5*8
	TF_LCD_E_Set;
	TF_LCD_RDB7;
	TF_LCD_RDB6;
	TF_LCD_SDB5;
	TF_LCD_RDB4;
	TF_LCD_E_Reset;
	delayUs(20);
	TF_LCD_E_Set;
	TF_LCD_SDB7;
	TF_LCD_RDB6;
	TF_LCD_RDB5;
	TF_LCD_RDB4;
	TF_LCD_E_Reset;
	delayUs(40);
	TF_LCD_BL_On;
	
	
}

void TF_lcdDisplayControl(void){
	TF_LCD_RS_Reset;
	TF_LCD_RW_Reset;

	//lcd on, cursor on, blink on
	TF_LCD_E_Set;
	TF_LCD_RDB7;
	TF_LCD_RDB6;
	TF_LCD_RDB5;
	TF_LCD_RDB4;
	TF_LCD_E_Reset;
	delayUs(20);
	TF_LCD_E_Set;
	TF_LCD_SDB7;
	TF_LCD_SDB6;
	TF_LCD_SDB5;
	TF_LCD_SDB4;
	TF_LCD_E_Reset;
	delayUs(40);
}

void TF_lcdClear(void){
	TF_LCD_RS_Reset;
	TF_LCD_RW_Reset;

	//clear all
	TF_LCD_E_Set;
	TF_LCD_RDB7;
	TF_LCD_RDB6;
	TF_LCD_RDB5;
	TF_LCD_RDB4;
	TF_LCD_E_Reset;
	delayUs(20);
	TF_LCD_E_Set;
	TF_LCD_RDB7;
	TF_LCD_RDB6;
	TF_LCD_RDB5;
	TF_LCD_SDB4;
	TF_LCD_E_Reset;
	delayUs(50000);
}

void TF_lcdGotoXY(uint8_t row, uint8_t col){
	col--;
	row--;
	switch(row){
		case 0:
			col+=0;
			break;
		case 1:
			col+=64;
			break;
		case 2:
			col+=20;
			break;
		case 3:
			col+=84;
			break;
		default:
			col=0;
			row=0;
	}
	TF_LCD_RS_Reset;
	TF_LCD_RW_Reset;

	//goto xy
	TF_LCD_E_Set;
	TF_LCD_SDB7;
	if(col & (1<<6))
		TF_LCD_SDB6;
	else
		TF_LCD_RDB6;
	if(col & (1<<5))
		TF_LCD_SDB5;
	else
		TF_LCD_RDB5;
	if(col & (1<<4))
		TF_LCD_SDB4;
	else
		TF_LCD_RDB4;
	TF_LCD_E_Reset;
	delayUs(20);
	TF_LCD_E_Set;
		if(col & (1<<3))
		TF_LCD_SDB7;
	else
		TF_LCD_RDB7;
	if(col & (1<<2))
		TF_LCD_SDB6;
	else
		TF_LCD_RDB6;
	if(col & (1<<1))
		TF_LCD_SDB5;
	else
		TF_LCD_RDB5;
	if(col & (1<<0))
		TF_LCD_SDB4;
	else
		TF_LCD_RDB4;
	TF_LCD_E_Reset;
	delayUs(40);
}

void TF_lcdPrintCh(uint8_t ch){
	TF_LCD_RS_Set;
	TF_LCD_RW_Reset;

	TF_LCD_E_Set;
	if(ch & (1<<7))
		TF_LCD_SDB7;
	else
		TF_LCD_RDB7;
	if(ch & (1<<6))
		TF_LCD_SDB6;
	else
		TF_LCD_RDB6;
	if(ch & (1<<5))
		TF_LCD_SDB5;
	else
		TF_LCD_RDB5;
	if(ch & (1<<4))
		TF_LCD_SDB4;
	else
		TF_LCD_RDB4;
	TF_LCD_E_Reset;
	delayUs(20);
	TF_LCD_E_Set;
		if(ch & (1<<3))
		TF_LCD_SDB7;
	else
		TF_LCD_RDB7;
	if(ch & (1<<2))
		TF_LCD_SDB6;
	else
		TF_LCD_RDB6;
	if(ch & (1<<1))
		TF_LCD_SDB5;
	else
		TF_LCD_RDB5;
	if(ch & (1<<0))
		TF_LCD_SDB4;
	else
		TF_LCD_RDB4;
	TF_LCD_E_Reset;
	delayUs(40);
}

void TF_lcdPrint(uint8_t* str){
	for(;*str != '\0';str++)
		TF_lcdPrintCh(*str);
}

