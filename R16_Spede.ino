#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"

// Use these 2 volatile variables for communicating between
// loop() function and interrupt handlers
volatile int buttonNumber = -1;          // for buttons interrupt handler
volatile bool newTimerInterrupt = false; // for timer interrupt handler
byte matchedCount;                       // kuinka monta lediä pelaaja on painanut oikein putkeen
volatile byte sequence[20];              // 20 ledin jälkeen ilman painallusta = häviö
volatile byte litCount;                  // kuinka monta lediä on yhteensä syttynyt

void setup()
{
  /*
    Initialize here all modules
  */
}

void loop()
{
  if (buttonNumber == 4)
  {
    // start the game if buttonNumber == 4
    // check the game if 0<=buttonNumber<4
  }

  if (newTimerInterrupt == true)
  {
    // new random number must be generated
    // and corresponding let must be activated
  }
}

void initializeTimer(void)
{
  // see requirements for the function from SpedenSpelit.h
  noInterrupts();          // keskeytykset pois päältä

  TCCR1A = 0;              // tyhjätään ohjaus rekisterit
  TCCR1B = 0;
  TCNT1  = 0;              // nollataan laskuri

  // asetetaan rekisteri 1 Hz taajuuteen 16 MHz:illä
  // 16MHz / (esiskaalaaja * haluttu taajuus)
  // (16,000,000 / (1024 * 1)) - 1 = 15624
  OCR1A = 15624;

  TCCR1B |= (1 << WGM12);  // CTC
  TCCR1B |= (1 << CS12) | (1 << CS10); // esiskaalaaja -> 1024
  TIMSK1 |= (1 << OCIE1A); // Timer1 enable <- tämä pitää disablettaa sitten jossain kun peli loppuu -> TIMSK1 &= ~(1 << OCIE1A);

  interrupts();             // keskeytykset päälle
}
ISR(TIMER1_COMPA_vect)
{
  /*
  Communicate to loop() that it's time to make new random number.
  Increase timer interrupt rate after 10 interrupts.
  */
}

void checkGame(byte nbrOfButtonPush)
{
  // see requirements for the function from SpedenSpelit.h
}

void initializeGame()
{
  litCount = 0;
  matchedCount = 0;
  buttonNumber = -1;
  newTimerInterrupt = false;
  randomSeed(analogRead(A1));
}

void startTheGame()
{
  //valoshow pitää jotenki lopettaa joko täs tai sitte sielä ite valoshowssa
  //gameOn = true; // jos halutaan se näin ratkasta esimerkiks
  
  initializeGame();
  initializeTimer();

}
