#include "func.h"

void AHB_prescale_set_2(void)
{
	RCC->CFGR |= 0x00000080;
	RCC->CFGR &= ~0x00000040;
	RCC->CFGR &= ~0x00000020;
	RCC->CFGR &= ~0x00000010;
}

void SysTick_Init (unit32 ticks)
{
	AHB_prescale_set_2();
	SysTick->CTRL = 0;
	SysTick->LOAD = ticks - 1;
	NVIC_SetPriority(SysTick_IRQn, (1 << __NVIC_PRIO_BITS) - 1);
	SysTick->VAL = 0;
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk; 
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;	
}

void SysTick_Handler()
{
	if(work)
	{
		switch(mod)
		{
			case 0:
				counter_mod_0++;
			break;
			
			case 1:
				counter_mod_1--;
			break;
			
			case 2:
				counter_mod_2++;
			break;
		}
	}
	PD_14(work);
	lcd_time_print();
}


