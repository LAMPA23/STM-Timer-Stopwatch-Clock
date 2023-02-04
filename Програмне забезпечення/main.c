#include "func.h"

int main()
{
	init_PD_14();
	SysTick_Init(systick_init_value);
	init_interrupt();
	lcd_init();
	lcd_print();
	while(1);
}