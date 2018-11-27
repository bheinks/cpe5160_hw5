#include "main.h"
#include "PORT.h"
#include "delay.h"

void DELAY_1ms_T0(uint16_t duration) {
   // Configure Timer 0 as a 16-bit timer 
   TMOD &= 0xF0; // Clear all T0 bits (T1 left unchanged)
   TMOD |= 0x01; // Set required T0 bits (T1 left unchanged) 
      
   ET0 = 0;  // No interupts
      
   do {
     // Values for 1 ms delay
      TH0 = TIMER_RELOAD_TH;  // Timer 0 initial value (High Byte)
      TL0 = TIMER_RELOAD_TL;  // Timer 0 initial value (Low Byte)

      TF0 = 0;          // Clear overflow flag
      TR0 = 1;          // Start timer 0

      while (TF0 == 0); // Loop until Timer 0 overflows (TF0 == 1)

      TR0 = 0;          // Stop Timer 0
      duration--;
    } while(duration > 0);
}