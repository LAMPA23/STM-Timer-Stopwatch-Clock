#include <stm32f407xx.h>
#include <stdbool.h>

typedef unsigned long unit32;

extern volatile bool work;
extern volatile bool change;
extern volatile bool sign_change_value;
extern volatile unit32 change_value;
extern volatile unit32 systick_init_value; // 0x008F0D18 = 500ms = 9 375 000
extern volatile unit32 counter_mod_0_buff;
extern volatile unit32 counter_mod_0; // Clock
extern volatile unit32 counter_mod_1; // Timer
extern volatile unit32 counter_mod_2; // Stopwatch
extern volatile unit32 mod;
extern volatile unit32 delay_counter;
extern volatile unit32 hour;
extern volatile unit32 minute;
extern volatile unit32 second;


//*************************************************
void my_delay(unsigned long delay);
void init_PD_14(void);
void PD_14(bool set_reset);
void PE_7(bool set_reset);
void PE_10(bool set_reset);
void PE_11(bool set_reset);
void PE_12(bool set_reset);
void PE_13(bool set_reset);
void PE_14(bool set_reset);
void PE_15(bool set_reset);
//*************************************************


//*************************************************
void AHB_prescale_set_2(void);
void SysTick_Init (unit32 ticks);
void SysTick_Handler(void);
//*************************************************


//*************************************************
void init_GPIO_for_interrupt(void);				
void init_interrupt(void);						
void init_irq(void);																		
void EXTI0_IRQHandler(void);										
void EXTI2_IRQHandler(void);					
void EXTI3_IRQHandler(void);					
void EXTI15_10_IRQHandler(void);				
//*************************************************


//*************************************************
void lcd_init(void);
void lcd_gpio_init(void);
void lcd_cursor_on(void);
void lcd_cursor_off(void);
void lcd_cursor_to_home(void);
void lcd_clear(void);
void lcd_send_cmd(unsigned char sign);
void lcd_send_data(unsigned char sign);
void lcd_print(void);
void lcd_mod_print(void);
void lcd_time_print(void);
void lcd_change_print(void);
//*************************************************
