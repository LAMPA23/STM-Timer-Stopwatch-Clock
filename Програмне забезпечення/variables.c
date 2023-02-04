#include "func.h"

volatile bool work = 0;
volatile bool change = 0;
volatile bool sign_change_value = 0; // if 0 then positive 


volatile unit32 systick_init_value = 0x007AFAE1; //   9 371 648  8 059 617,28 7A FAE1
volatile unit32 change_value = 1;
volatile unit32 mod = 0;

volatile unit32 counter_mod_0 = 0; // Clock
volatile unit32 counter_mod_1 = 0; // Timer
volatile unit32 counter_mod_2 = 0; // Stopwatch

volatile unit32 delay_counter = 0;

volatile unit32 hour;
volatile unit32 minute;
volatile unit32 second;