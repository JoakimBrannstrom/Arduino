#ifndef _TIMER_h
#define _TIMER_h

#include "Arduino.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void initializeTimer(void (*timerFunc) ());
int getTimerCountForOneSecond();

#endif

