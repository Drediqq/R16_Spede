#ifndef BUTTONS_H
#define BUTTONS_H
#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

extern volatile int buttonNumber; // buttons.cpp:lle että tämä variable on olemassa jossain, tässä tapauksessa .inossa
const byte firstPin = 2; // First PinChangeInterrupt on D-bus
const byte lastPin =  5; // Last PinChangeInterrupt on D-bus


void initButtonsAndButtonInterrupts(void);
void buttonsHandler(void);
void buttonPress(uint8_t);

// Intoduce PCINT2_vect Interrupt SeRvice (ISR) function for Pin Change Interrupt.
ISR(PCINT2_vect); 
#endif
