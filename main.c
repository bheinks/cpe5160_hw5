#include "main.h"
#include "sEOS.h"

void go_to_sleep() {
}

void system_init(void) {
}

void main(void) {
    system_init();
    seos_init(100);
    
    while(1) {
        PCON |= 0x01;
        go_to_sleep();
    }
}