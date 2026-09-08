#include "buttons.h"
#include "Arduino.h"
#include <avr/io.h>



// 6  Pin Change Interrupt Request 2 (pins D0 to D7)  (PCINT2_vect)

/* 
  initButtonsAndButtonInterrupts subroutine is called from Setup() function
  during the initialization of Speden Spelit. This function does the following:
  1) Initializes 4 button pins for the game = Arduino pins 2,3,4,5
  2) Initializes 1 button pin for starting the game = Aruino pin 6
  3) Enables PinChangeInterrupt on D-bus in a way that interrupt
     is generated whenever some of pins 2,3,4,5,6 is connected to LOW state

*/

// asettaa keskeytykset oikeisiin osoitteisiin riippuen siitä mikä pinni on kyseessä
void arduinoInterruptHelper(uint8_t pin){
  if(pin <= 7){
    PCICR |= (1 << PCIE2);
    PCMSK2 |= (1 << pin);
  }else if(pin <= 13){
    PCICR |= (1 << PCIE0);
    PCMSK0 |= (1 << pin);
  }else if(pin <= 19){
    PCICR |= (1 << PCIE1);
    PCMSK1 |= (1 << pin);
  }
}

void initButtonsAndButtonInterrupts(void)
{
  // alustaa pinnit ja niiden interruptit
  for(int i = firstPin; i <= lastPin; i++){
    pinMode(i, INPUT_PULLUP);
    arduinoInterruptHelper(i);
  }
}

  // See requirements for this function from buttons.h
ISR(PCINT2_vect) {
    // 18 = D2 = 0
   if (!(PIND & (1 << PCINT18))) {
    buttonNumber = 0;
    
    // 19 = D3 = 1
  } else if (!(PIND & (1 << PCINT19))) {
    buttonNumber = 1;
    
    // 20 = D4 = 2
  } else if (!(PIND & (1 << PCINT20))) {
    buttonNumber = 2;
    
    // 21 = D5 = 3
  }else if(!(PIND & (1 << PCINT21))){
    buttonNumber = 3;

    // turha?
  }else {
    buttonNumber = -1;
  }
   /*
     Here you implement logic for handling
	 interrupts from 2,3,4,5 pins for Game push buttons
	 and for pin 6 for start Game push button.
   */
}