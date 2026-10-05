#ifndef BUTTONS_H
#define BUTTONS_H
#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "helpers.h"
#include "settings.h"


extern volatile int buttonNumber; // buttons.cpp:lle että tämä variable on olemassa jossain, tässä tapauksessa .inossa
const byte firstPin = 2; // First PinChangeInterrupt on D-bus
const byte lastPin =  5; // Last PinChangeInterrupt on D-bus


void initButtonsAndButtonInterrupts(void); // alustaa nappulat 
void buttonsHandler(void);  // diilaa nappien kanssa
void buttonPress(uint8_t);  // palauttaa buttonNumber muuttujaan painetun napin arvon

// Intoduce PCINT2_vect Interrupt SeRvice (ISR) function for Pin Change Interrupt.
ISR(PCINT2_vect); 
#endif
