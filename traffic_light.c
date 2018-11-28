#include "traffic_light.h"
#include "PORT.h"
#include "delay.h"

void set_lights(bit green, bit amber, bit yellow, bit red, bit blue) {
    GREENLED = ~green;
    AMBERLED = ~amber;
    YELLOWLED = ~yellow;
    REDLED = ~red;
    BLUELED = ~blue;
}

void traffic_light_isr(void) interrupt TIMER_2_OVERFLOW {
    TF2 = 0; // clear interrupt flag
    TIMER++; // increment timer
    
    switch (SYSTEM_STATE) {
        case MAIN_GREEN:
            set_lights(1, 0, 0, 0, 0);
        
            if (!SW1) {
                SYSTEM_STATE = MAIN_YELLOW_SIDE;
            }
            else if (!SW2) {
                SYSTEM_STATE = MAIN_YELLOW_CROSS;
                TIMER = 0;
                
            }
        
            break;
        case MAIN_YELLOW_CROSS:
            set_lights(0, 0, 1, 0, 0);
        
            if (TIMER >= 2000) {
                SYSTEM_STATE = MAIN_RED_CROSS;
                TIMER = 0;
            }
        
            break;
        case MAIN_YELLOW_SIDE:
            set_lights(0, 0, 1, 0, 0);
        
            if (TIMER >= 2000) {
                SYSTEM_STATE = MAIN_RED_SIDE;
                TIMER = 0;
            }
        
            break;
        case MAIN_RED_CROSS:
            set_lights(0, 0, 0, 1, 0);
        
            if (TIMER >= 1000) {
                SYSTEM_STATE = WALK;
                TIMER = 0;
            }
        
            break;
        case MAIN_RED_SIDE:
            set_lights(0, 0, 0, 1, 0);
        
            if (TIMER >= 1000) {
                SYSTEM_STATE = SIDE_GREEN;
                TIMER = 0;
            }
        
            break;
        case SIDE_BUTTON_RELEASE:
            set_lights(1, 0, 0, 1, 0);
            
            if (TIMER >= 5000){
                SYSTEM_STATE = SIDE_YELLOW;
                TIMER = 0;
            }
        case SIDE_RED:
            set_lights(0, 0, 0, 1, 0);
        
            if (TIMER >= 1000) {
                SYSTEM_STATE = MAIN_GREEN;
                TIMER = 0;
            }
            break;
        case SIDE_YELLOW:
            set_lights(0, 0, 1, 1, 0);
        
            if (TIMER >= 2000) {
                SYSTEM_STATE = SIDE_RED;
                TIMER = 0;
            }
            break;
        case SIDE_GREEN:
            set_lights(1, 0, 0, 1, 0);
        
            if (TIMER >= 30000){
                SYSTEM_STATE = SIDE_YELLOW;
                TIMER = 0;
            }
            else if (SW1){
                SYSTEM_STATE = SIDE_BUTTON_RELEASE;
                TIMER = 0;
            }
            
            break;
        case WALK:
            set_lights(0, 0, 0, 1, 1);
        
            if (TIMER >= 5000) {
                SYSTEM_STATE = NO_WALK_ON;
                TIMER = 0;
            }
        
            break;
        case NO_WALK_ON:
            set_lights(0, 1, 0, 1, 0);
        
            if (TIMER >= 5000) {
                SYSTEM_STATE = MAIN_GREEN;
            }
            if (FLASH_TIMER >= 500) {
                SYSTEM_STATE = NO_WALK_OFF;
                FLASH_TIMER = 0;
            }
        
            break;
        case NO_WALK_OFF:
            set_lights(0, 0, 0, 1, 0);
        
            if (TIMER >= 5000) {
                SYSTEM_STATE = MAIN_GREEN;
            }
            if (FLASH_TIMER >= 500) {
                SYSTEM_STATE = NO_WALK_ON;
                FLASH_TIMER = 0;
            }
        
            break;
    }
}