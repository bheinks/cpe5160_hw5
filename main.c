#include "main.h"
#include "PORT.h"
#include "sEOS.h"

void system_init(void) {
    GREENLED = 0;
}

void main(void) {
    system_init();
    seos_init(1);
    
    while(1) {
        go_to_sleep();
    }
}