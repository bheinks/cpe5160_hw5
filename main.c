/*
	CpE 5160 Homework 5
	Brett Heinkel
	Michael Proemsey
	Ian Piskulic
*/

#include "main.h"
#include "PORT.h"
#include "sEOS.h"

void main(void) {
    seos_init(1); // initialize sEOS interrupt at 1ms
    
    while(1) {
        go_to_sleep(); // enter idle mode
    }
}