#include "timer.h"
#include "settings.h"

// Asettaa prescalerin annetun arvon perusteella
// Ottaa vastaan kokonaisluvun 0, 1, 8, 64, 256, 1024, 
// jos luku ei ole yksi näistä, palauttaa virheen eikä aseta prescaleria
void prescalerHelper(uint16_t prescaling) {
// PRESCALER        CS12   CS11   CS10      TCCR1B   
// ──────────────────────────────────────────────────
// 0                [ 0 ]  [ 0 ]  [ 0 ]     0bxxx000  
// 1                [ 0 ]  [ 0 ]  [ 1 ]     0bxxx001  
// 8                [ 0 ]  [ 1 ]  [ 0 ]     0bxxx010        
// 64               [ 0 ]  [ 1 ]  [ 1 ]     0bxxx011       
// 256              [ 1 ]  [ 0 ]  [ 0 ]     0bxxx100        
// 1024             [ 1 ]  [ 0 ]  [ 1 ]     0bxxx101        
  uint8_t scalerBits = 0;

  switch (prescaling) {                 //  cs12 cs11 cs10
    case 0:     scalerBits = 0; break;  //  [ 0 ][ 0 ][ 0 ]  = 0
    case 1:     scalerBits = 1; break;  //  [ 0 ][ 0 ][ 1 ]  = 1
    case 8:     scalerBits = 2; break;  //  [ 0 ][ 1 ][ 0 ]  = 2
    case 64:    scalerBits = 3; break;  //  [ 0 ][ 1 ][ 1 ]  = 3
    case 256:   scalerBits = 4; break;  //  [ 1 ][ 0 ][ 0 ]  = 4
    case 1024:  scalerBits = 5; break;  //  [ 1 ][ 0 ][ 1 ]  = 5
    default:
      Serial.println("Invalid scaler");
      return;
  }
  // Syötetään bittiarvo ja asetetaan haluttu scaleri
  TCCR1B = (TCCR1B & ~((1 << CS12) | (1 << CS11) | (1 << CS10))) | scalerBits;
}

// Asettaa ajastimelle tarpeelliset bitit oikeisiin asentoihin
void initializeTimer() {
  noInterrupts();  // Keskeytykset pois päältä

// TCCR1A
// [COM1A1] [COM1A0] [COM1B1] [COM1B0] [-----] [-----] [WGM11] [WGM10]   | TCCR1A   
// ----------------------------------------------------------------------|------------
// [ 0 ]    [ 0 ]    [ 0 ]    [ 0 ]    [ 0 ]   [ 0 ]   [ 0 ]   [ 0 ]     | 0b00000000  
//   Tyhjätään ohjausrekisteri                                           |
// -----------------------------------------------------------------------------------
  TCCR1A = 0;  
// -----------------------------------------------------------------------------------

// TCCR1B
// [ICNC1]  [ICES1]  [-----]  [WGM13]  [WGM12] [CS12]  [CS11]  [CS10]    | TCCR1B   
// ----------------------------------------------------------------------|------------
// [ 0 ]    [ 0 ]    [ 0 ]    [ 0 ]    [ 0 ]   [ 0 ]   [ 0 ]   [ 0 ]     | 0b00000000  
//   Asetetaan prescaler pois eli cs10,11,12 -> 000                      |
// -----------------------------------------------------------------------------------
  TCCR1B = 0;
// -----------------------------------------------------------------------------------

// TCNT1 (16-bit Laskuri)
// [ BIT15 . . . . . . . . . . . . . BIT0 ]     | TCNT1
// --------------------------------------------------------
// [ 0 0 0 0 0 0 0 0   0 0 0 0 0 0 0 0          | 0x0000
//   Nollataan laskurirekisteri
// --------------------------------------------------------  
  TCNT1 = 0;
// ---------------------------------------------------------

  OCR1A = OCR1AVALUE;  // Asetetaan vertailuarvo, jossa keskeytys tapahtuu

// TCCR1B
// [ICNC1] [ICES1] [-----] [WGM13] [WGM12] [CS12] [CS11] [CS10]    | TCCR1B
// ----------------------------------------------------------------|------------
// [ x ]   [ x ]   [ x ]   [ x ]   [ 1 ]   [ 1 ]  [ 0 ]  [ 1 ]     | 0bxxxx1101  
//                                  CTC      |      |      |       |
//                                           (esim 1024=101)
// ------------------------------------------------------------------------------
  TCCR1B |= (1 << WGM12);  // CTC (Clear Timer on Compare Match)
  prescalerHelper(PRESCALER); // Muutettavissa toisaalla
// ---------------------------------------------------------------------------------

// TIMSK1
// [-----] [-----] [ICIE1] [-----] [-----] [OCIE1B] [OCIE1A] [TOIE1]    | TIMSK1
// ---------------------------------------------------------------------|------------
// [ x ]   [ x ]   [ x ]   [ x ]   [ x ]   [ x ]    [ 1 ]    [ x ]      | 0bxxxxxx1x  
//                                                    |                 |                  
//                                          (TIMER1_COMPA_vect)            
// -----------------------------------------------------------------------------------                               
  TIMSK1 |= (1 << OCIE1A);  // Timer1 Output Compare A Interrupt Enable
// -----------------------------------------------------------------------------------         

  interrupts();  // Keskeytykset takaisin päälle
}

// Funktio nostaa tai laskee annetun luvun arvoa n% määrällä
// step: potenssi, inputValue: manipuloitava arvo, stepSize: montako prosenttia arvoa nostetaan, decrease: lasketaanko vai nostetaanko
int percentStepHelper(int step, int inputValue = 15624, int stepSize = 10, bool decrease = 1) {
  // näillä lasketaan stepSize% nosto
  float base = 1 + (stepSize * 0.01);  // 1 + (stepSize * 0.01),  esim. 1 + 10(%) * 0.01 = 1.1
  float value = pow(base, step);       // base^step,              esim. 1.1² (²=step)


  // Palautetaan stepSize% alennettu arvo, jos decrease on 1
  if (decrease != 0) {
    uint16_t rVal = inputValue / value;  //esim. 15624 / 1.1² = 15624 / 1.21 = 12912 = -20%
    return rVal;

  // Palautetaan stepSize% nostettu arvo, jos decrease on 0
  } else {
    uint16_t rVal = inputValue * value;
    return rVal;
  }
}
// Nollaa timerin
void resetTimer(){
  TCNT1 = 0;  
}
// Pysäyttää timer1
void stopTimer() {
  TIMSK1 &= ~(1 << OCIE1A);         // asetetaan andilla ja notilla timerpinni -> 0, jotta se on hiljaa
  prescalerHelper(0);   // asettaa ajastimen kokonaan pois päältä
  TIFR1 |= (1 << OCF1A);           // nollataan tulevat keskeytykset vielä tai oikeastaan ykköstetään :D
}

// Mahdollisesti staticeiksi nämä katsotaan tarvitaanko niitä muualla
uint8_t timerCounter = 0; 
uint8_t timerMultiplier = 0; 

ISR(TIMER1_COMPA_vect) {
/*
voi olla että saa koko sisällön tehdä erilliseksi funktioksi
*/

  timerCounter++; // Timer pyörinyt +1 kertaa
  // --- led bool => true ---


  if (timerCounter >= 10) {
    timerCounter = 0;
    
  /*

    Tämän varmaan vois vielä eritellä funktioksi että voi kutsua samaa funkkaria napin painalluksella
    samasta syystä saattaa tarvita myös yllä olevia muuttujia

  */
    timerMultiplier++; // Nostojen määrä, toimii samalla potenssina percentStepHelper funktiolle

    uint16_t speed = percentStepHelper(timerMultiplier, OCR1AVALUE, SPEEDUPVALUE);
    
    if (speed < 150) { 
      speed = 150; // Speed minimi on 150, ettei se vahingossakaan pääse 0
    }
    
    OCR1A = speed; // Asetetaan laskettu arvo
    resetTimer(); // Nollaa ajastin ettei tapahdu kummallisuuksia
  }
  /*
  Communicate to loop() that it's time to make new random number.
  Increase timer interrupt rate after 10 interrupts.
  */
}