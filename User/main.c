#include "stm32f0xx.h"
#include "TF_LCD.h"
#include <stdio.h>

uint32_t micros;

void SetSysClock(void);
void delayMs(uint32_t ms);
void delayUs(uint32_t us);
void gpio_init(void);
char stringBreaker(int pos, int col);

uint32_t lcd_timer;

const uint8_t numRows = 4;
const uint8_t numCols = 20;
char subtitle[] = "The quick brown fox jumps over the lazy dog :)";
//char subtitle[] = "Hi mi";
int subsize = sizeof(subtitle)-1;
const uint32_t lcdSubDelay = 120000;
uint8_t lcdSubPause = 0;

int main(){
	micros=0; //init delays
	SetSysClock();
	gpio_init();
	SysTick_Config(48);
	TF_lcdInit();
	TF_lcdDisplayControl();
	TF_lcdClear();
	TF_lcdGotoXY(1,1);
	//TF_lcdPrint((uint8_t*) "I'm Taha falahati from thetick");
	int pos=0;
	uint8_t gap = 5;
	lcd_timer = micros;
	
	while(1){
		//debugging
//		TF_lcdGotoXY(1,1);
//		TF_lcdPrintCh('0'+(pos/100)%10);
//		TF_lcdPrintCh('0'+(pos/10)%10);
//		TF_lcdPrintCh('0'+(pos/1)%10);
		
		//subtitle process
		if(lcd_timer+lcdSubDelay < micros){ //for freeing while time
			
			for(int x=0; x<numCols; x++){
				TF_lcdGotoXY(4,x+1);
				char* i;
				char tmp;
				i = subtitle + x + pos - numCols;
				if(i < subtitle){
					tmp = ' ';
				}else if(i >= subtitle+subsize){
					if(i >= subtitle+subsize+gap){
						tmp = *(i - gap - subsize);
					}else
						tmp = ' ';
					if(pos >= subsize+numCols+gap){
						pos=numCols;
					}
				}else{
					tmp = *(i);
				}
				TF_lcdPrintCh(tmp);
			
			}
			if(lcdSubPause == 0)
				pos++;
			lcd_timer = micros;
		}
		
		//key process
		lcdSubPause = 0;
		if(((GPIOA->IDR & (1<<9)) == (1<<9)) && ((GPIOA->IDR & (1<<10)) == (1<<10))){ //both key active
			lcdSubPause = 1; //subtitle stop
			TF_lcdGotoXY(3,1);
			TF_lcdPrint((uint8_t *)"Subtitle pause     ");
		}else if((GPIOA->IDR & (1<<9)) == (1<<9)){ //PA9 key active
			TF_lcdGotoXY(3,1);
			TF_lcdPrint((uint8_t *)"Left Key is active ");
		}else if((GPIOA->IDR & (1<<10)) == (1<<10)){ //PA10 key active
			TF_lcdGotoXY(3,1);
			TF_lcdPrint((uint8_t *)"Right Key is active");
		}else{ //no key active
			TF_lcdGotoXY(3,1);
			TF_lcdPrint((uint8_t *)"no Key is active   ");
		}
				
	}
}

void SysTick_Handler(){
	micros++;
}

static void SetSysClock(void)
{
	FLASH->ACR = FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY;
	RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
	RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE_DIV1;
	RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMUL));
	RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSI_DIV2 | RCC_CFGR_PLLXTPRE_HSE_PREDIV_DIV1 | RCC_CFGR_PLLMUL12);
  RCC->CR |= RCC_CR_PLLON;
  while((RCC->CR & RCC_CR_PLLRDY) == 0);
  RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
  RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;    
  while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)RCC_CFGR_SWS_PLL);
}


void delayMs(uint32_t ms){
	delayUs((ms*1000));
}

void delayUs(uint32_t us){	
	uint32_t i = micros + us;
	while(i > micros);
}

void gpio_init(void){
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->MODER |= 0x5555; //lcd
	GPIOA->PUPDR |= 0xAAAA; //lcd
	GPIOA->OSPEEDR |= 0xFFFF; //high speed lcd pins output
	
	GPIOA->MODER &= ~0x3C0000; //key on A9 & A10
	GPIOA->PUPDR |= 0x280000; //pull down both keys
}

char stringBreaker(int pos, int col){
	
}

