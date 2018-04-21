#include "stm32f0xx.h"
#include "TF_LCD.h"

uint32_t micros;

void SetSysClock(void);
void delayMs(uint32_t ms);
void delayUs(uint32_t us);
void gpio_init(void);

const uint8_t rows = 4;
const uint8_t cols = 20;

int main(){
	micros=0;
	SetSysClock();
	gpio_init();
	SysTick_Config(48);
	TF_lcdInit();
	TF_lcdDisplayControl();
	TF_lcdClear();
	TF_lcdGotoXY(1,1);
	TF_lcdPrint((uint8_t*) "I'm Taha falahati from thetick");
	TF_lcdClear();
	while(1){
		
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
	GPIOA->MODER |= 0x5555;
	GPIOA->PUPDR |= 0xAAAA;
}

