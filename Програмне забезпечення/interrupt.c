#include "func.h"

void init_GPIO_for_interrupt(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	
	GPIOA->MODER &= ~GPIO_MODER_MODE0_0;
	GPIOA->MODER &= ~GPIO_MODER_MODE0_1;
	GPIOA->MODER &= ~GPIO_MODER_MODE2_0;
	GPIOA->MODER &= ~GPIO_MODER_MODE2_1;
	GPIOA->MODER &= ~GPIO_MODER_MODE3_0;
	GPIOA->MODER &= ~GPIO_MODER_MODE3_1;
	GPIOA->MODER &= ~GPIO_MODER_MODE15_0;
	GPIOA->MODER &= ~GPIO_MODER_MODE15_1;
}

void init_interrupt(void) 
{
	init_GPIO_for_interrupt();
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	init_irq();
	__enable_irq();
}

void init_irq(void)
{	
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI2_PA;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI3_PA;
	SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI15_PA;
	
	EXTI->IMR |= EXTI_IMR_IM0;
	EXTI->IMR |= EXTI_IMR_IM2;
	EXTI->IMR |= EXTI_IMR_IM3;
	EXTI->IMR |= EXTI_IMR_IM15;
	
	EXTI->FTSR |= EXTI_RTSR_TR0;
	EXTI->FTSR |= EXTI_RTSR_TR2;
	EXTI->FTSR |= EXTI_RTSR_TR3;
	EXTI->FTSR |= EXTI_RTSR_TR15;
	
	NVIC_SetPriority(EXTI0_IRQn,1);
	NVIC_SetPriority(EXTI2_IRQn,3);
	NVIC_SetPriority(EXTI3_IRQn,4);
	NVIC_SetPriority(EXTI15_10_IRQn,5);
	
	NVIC_ClearPendingIRQ(EXTI0_IRQn);
	NVIC_ClearPendingIRQ(EXTI2_IRQn);
	NVIC_ClearPendingIRQ(EXTI3_IRQn);
	NVIC_ClearPendingIRQ(EXTI15_10_IRQn);
	
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn);
	NVIC_EnableIRQ(EXTI3_IRQn);
	NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void EXTI0_IRQHandler() 
{
	EXTI->IMR &= ~EXTI_IMR_IM0;
	
	if(!work && !change)
	{
		mod++;
		if(mod>2) mod = 0;
		lcd_print();
	}
	else if(!work && change)
	{
		sign_change_value = !sign_change_value;
	}
	
	EXTI->PR|= EXTI_PR_PR0;
	EXTI->IMR |= EXTI_IMR_IM0;
}

void EXTI2_IRQHandler() 
{
	EXTI->IMR &= ~EXTI_IMR_IM2;
	
	change = 1;
	change_value = change_value*10;
	if(change_value>10000) change_value = 1;
	lcd_time_print();
	
	EXTI->PR|= EXTI_PR_PR2;
	EXTI->IMR |= EXTI_IMR_IM2;
}

void EXTI3_IRQHandler() 
{
	EXTI->IMR &= ~EXTI_IMR_IM3;
	
	if(change) 
	{
		switch(mod)
		{
			case 0:
				if(sign_change_value)counter_mod_0 -= change_value;
				else counter_mod_0 += change_value;
			break;
			
			case 1:
				if(sign_change_value)counter_mod_1 -= change_value;
				else counter_mod_1 += change_value;
			break;
			
			case 2:
				if(sign_change_value)counter_mod_2 -= change_value;
				else counter_mod_2 += change_value;
			break;
		}
	}
	lcd_time_print();
	
	EXTI->PR|= EXTI_PR_PR3;
	EXTI->IMR |= EXTI_IMR_IM3;
}

void EXTI15_10_IRQHandler() 
{
	EXTI->IMR &= ~EXTI_IMR_IM15;

	change = 0;
	change_value = 1;
	work = !work;
	PD_14(work);
	lcd_print();
	
	EXTI->PR|= EXTI_PR_PR15;
	EXTI->IMR |= EXTI_IMR_IM15;
}