#include "main.h"

void delay_ms(uint32_t ms)
{
	SysTick_Config(SystemCoreClock/1000);
	for(int i = 0; i < ms; i++)
	{
		while(!((SysTick->CTRL) & (1<<16)));
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void delay_us(uint32_t us)
{
	SysTick_Config(SystemCoreClock/1000000);
	for(int i = 0; i < us; i++)
	{
		while(!((SysTick->CTRL) & (1<<16)));
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}
