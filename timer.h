#ifndef TIMER_H
#define TIMER_H
#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

extern volatile bool newTimerInterrupt;

void initializeTimer(void);

ISR(TIMER1_COMPA_vect); 
#endif
