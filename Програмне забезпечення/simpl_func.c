#include "func.h"

void init_PD_14(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	GPIOD->MODER |= GPIO_MODER_MODE14_0;
	GPIOD->MODER &= ~GPIO_MODER_MODE14_1;
}

void my_delay(unsigned long delay)
{	
	delay_counter = 0;
	for(delay_counter=0;delay_counter<delay;delay_counter++);
}

void PD_14(bool set_reset)
{
	if (set_reset) GPIOD->ODR |= GPIO_ODR_OD14;
	else GPIOD->ODR &= ~GPIO_ODR_OD14;
}

void PE_7(bool set_reset)
{
	if (set_reset) GPIOE->ODR |= GPIO_ODR_OD7;
	else GPIOE->ODR &= ~GPIO_ODR_OD7;
}

void PE_10(bool set_reset)
{
	if (set_reset) GPIOE->ODR |= GPIO_ODR_OD10;
	else GPIOE->ODR &= ~GPIO_ODR_OD10;
}
void PE_11(bool set_reset)
{
	if (set_reset) GPIOE->ODR |= GPIO_ODR_OD11;
	else GPIOE->ODR &= ~GPIO_ODR_OD11;
}
void PE_12(bool set_reset)
{
	if (set_reset) GPIOE->ODR |= GPIO_ODR_OD12;
	else GPIOE->ODR &= ~GPIO_ODR_OD12;
}

void PE_13(bool set_reset)
{
	if (set_reset) GPIOE->ODR |= GPIO_ODR_OD13;
	else GPIOE->ODR &= ~GPIO_ODR_OD13;
}

void PE_14(bool set_reset)
{
	if (set_reset) GPIOE->ODR |= GPIO_ODR_OD14;
	else GPIOE->ODR &= ~GPIO_ODR_OD14;
}

void PE_15(bool set_reset)
{
	if (set_reset) GPIOE->ODR |= GPIO_ODR_OD15;
	else GPIOE->ODR &= ~GPIO_ODR_OD15;
}