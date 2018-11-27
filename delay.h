#ifndef _DELAY_H
#define _DELAY_H

#include "main.h"

#define one_msec (1)

#define TIMER_RELOAD (65536-((OSC_FREQ*one_msec)/(1020*OSC_PER_INST)))  
#define TIMER_RELOAD_TH (TIMER_RELOAD>>8)
#define TIMER_RELOAD_TL (TIMER_RELOAD&0xFF)


// ------ Public function prototypes -------------------------------


void DELAY_1ms_T0(uint16_t duration);



#endif