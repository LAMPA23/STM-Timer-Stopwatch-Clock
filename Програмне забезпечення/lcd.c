#include "func.h"

void lcd_init(void)
{
	lcd_gpio_init();
	lcd_send_cmd(0x28);	
	lcd_clear();
	lcd_cursor_off();
	lcd_cursor_to_home();
}

void lcd_gpio_init(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
	
	// MODER
	GPIOE->MODER |= GPIO_MODER_MODE7_0;
	GPIOE->MODER &= ~GPIO_MODER_MODE7_1;
	
	GPIOE->MODER |= GPIO_MODER_MODE10_0;
	GPIOE->MODER &= ~GPIO_MODER_MODE10_1;
	
	GPIOE->MODER |= GPIO_MODER_MODE11_0;
	GPIOE->MODER &= ~GPIO_MODER_MODE11_1;
	
	GPIOE->MODER |= GPIO_MODER_MODE12_0;
	GPIOE->MODER &= ~GPIO_MODER_MODE12_1;
	
	GPIOE->MODER |= GPIO_MODER_MODE13_0;
	GPIOE->MODER &= ~GPIO_MODER_MODE13_1;
	
	GPIOE->MODER |= GPIO_MODER_MODE14_0;
	GPIOE->MODER &= ~GPIO_MODER_MODE14_1;
	
	GPIOE->MODER |= GPIO_MODER_MODE15_0;
	GPIOE->MODER &= ~GPIO_MODER_MODE15_1;
	
	// OTYPER
	GPIOE->OTYPER &= ~GPIO_OTYPER_OT7;
	GPIOE->OTYPER &= ~GPIO_OTYPER_OT10;
	GPIOE->OTYPER &= ~GPIO_OTYPER_OT11;
	GPIOE->OTYPER &= ~GPIO_OTYPER_OT12;
	GPIOE->OTYPER &= ~GPIO_OTYPER_OT13;
	GPIOE->OTYPER &= ~GPIO_OTYPER_OT14;
	GPIOE->OTYPER &= ~GPIO_OTYPER_OT15;
	
	// Reset PE10
	PE_10(0);
}

void lcd_cursor_on(void)
{
	lcd_send_cmd(0x0D);
}

void lcd_cursor_off(void)
{
	lcd_send_cmd(0x0C);	
}

void lcd_cursor_to_home(void)
{
	lcd_send_cmd(0x02);	
}

void lcd_clear(void)
{
	lcd_send_cmd(0x01);
}

void lcd_send_cmd(unsigned char sign)
{
	PE_7(0);
	
	PE_11(0);
	
	PE_12(sign & (1<<4));
	PE_13(sign & (1<<5));
	PE_14(sign & (1<<6));
	PE_15(sign & (1<<7));
	
	PE_11(1);
	my_delay(40);
	PE_11(0);
	
	my_delay(40);
	PE_12(sign & (1<<0));
	PE_13(sign & (1<<1));
	PE_14(sign & (1<<2));
	PE_15(sign & (1<<3));
	
	PE_11(1);
	my_delay(40);
	PE_11(0);	
	
	my_delay(40000);
}

void lcd_send_data(unsigned char sign)
{
	PE_7(1);
	
	PE_11(0);
	
	PE_12(sign & (1<<4));
	PE_13(sign & (1<<5));
	PE_14(sign & (1<<6));
	PE_15(sign & (1<<7));
	
	PE_11(1);
	my_delay(40);
	PE_11(0);
	
	my_delay(40);
	PE_12(sign & (1<<0));
	PE_13(sign & (1<<1));
	PE_14(sign & (1<<2));
	PE_15(sign & (1<<3));
	
	PE_11(1);
	my_delay(40);
	PE_11(0);	
	
	my_delay(400);
}

void lcd_mod_print(void)
{
	lcd_cursor_to_home();
	lcd_send_data('M');
	lcd_send_data('o');
	lcd_send_data('d');
	lcd_send_data(':');
	lcd_send_data(' ');
	switch(mod)
	{
		case 0: 
			lcd_send_data('S');
			lcd_send_data('t');
			lcd_send_data('o');
			lcd_send_data('p');
			lcd_send_data('w');
			lcd_send_data('a');
			lcd_send_data('t');
			lcd_send_data('c');
			lcd_send_data('h');
		break;
		case 1: 
			lcd_send_data('T');
			lcd_send_data('i');
			lcd_send_data('m');
			lcd_send_data('e');
			lcd_send_data('r');
		break;
		case 2: 
			lcd_send_data('C');
			lcd_send_data('l');
			lcd_send_data('o');
			lcd_send_data('c');
			lcd_send_data('k');
		break;
	}
}

void lcd_time_print(void)
{
	if(!work && !change)
	{
		lcd_send_cmd(0xC2);
		lcd_send_data('=');
		lcd_send_data('=');
	}
	if(!work && change) 
	{
		lcd_send_cmd(0xC0);
	}
		
	if(work && !change) lcd_send_cmd(0xC4);
	
	switch(mod)
	{
		case 0:
			if(counter_mod_0>=100000) 
			{
				counter_mod_0 = 0;
				work = 0;
			}
			lcd_send_data(0x30 + (counter_mod_0 - (counter_mod_0%10000))/10000);
			lcd_send_data(0x30 + ((counter_mod_0 - (counter_mod_0%1000))/1000)%10);
			lcd_send_data(0x30 + ((counter_mod_0 - (counter_mod_0%100))/100)%10);
			lcd_send_data(0x30 + ((counter_mod_0 - (counter_mod_0%10))/10)%10);
			lcd_send_data(0x30 + (counter_mod_0%10));				
		break;
			
		case 1:
			if(counter_mod_1<=0) work = 0;
			second = counter_mod_1 % 60;
			hour = (counter_mod_1 - (counter_mod_1 % 3600)) / 3600;
			minute = ((counter_mod_1 % 3600) - second)/60;
			lcd_send_data(0x30 + ((hour - (hour%10))/10));
			lcd_send_data(0x30 + (hour%10));
			lcd_send_data(0x3A);
			lcd_send_data(0x30 + ((minute - (minute%10))/10));
			lcd_send_data(0x30 + (minute%10));
			lcd_send_data(0x3A);
			lcd_send_data(0x30 + ((second - (second%10))/10));
			lcd_send_data(0x30 + (second%10));
		break;
			
		case 2:
			if(hour>=24)
			{
				hour = 0;
				counter_mod_2 = 0;
				work = 0;
			}
			second = counter_mod_2 % 60;
			hour = (counter_mod_2 - (counter_mod_2 % 3600)) / 3600;
			minute = ((counter_mod_2 % 3600) - second)/60;
			lcd_send_data(0x30 + ((hour - (hour%10))/10));
			lcd_send_data(0x30 + (hour%10));
			lcd_send_data(0x3A);
			lcd_send_data(0x30 + ((minute - (minute%10))/10));
			lcd_send_data(0x30 + (minute%10));
			lcd_send_data(0x3A);
			lcd_send_data(0x30 + ((second - (second%10))/10));
			lcd_send_data(0x30 + (second%10));
		break;
	}
	
	if(!work && change) 
	{
		lcd_send_data(' ');
		lcd_send_data(' ');
		lcd_change_print();
	}
	
	if(!work && !change)
	{
		lcd_send_data('=');
		lcd_send_data('=');
	}
	
}

void lcd_change_print(void)
{
	if(sign_change_value) lcd_send_data('-');
	else lcd_send_data('+');
		
	lcd_send_data(0x30 + (change_value - (change_value%10000))/10000);
	lcd_send_data(0x30 + ((change_value - (change_value%1000))/1000)%10);
	lcd_send_data(0x30 + ((change_value - (change_value%100))/100)%10);
	lcd_send_data(0x30 + ((change_value - (change_value%10))/10)%10);
	lcd_send_data(0x30 + (change_value%10));	
}

void lcd_print()
{
	lcd_clear();
	lcd_mod_print();
	lcd_time_print();
}
	