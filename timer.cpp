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

// TCCR1B
// [ICNC1] [ICES1] [-----] [WGM13] [WGM12] [CS12] [CS11] [CS10]    | TCCR1B
// ----------------------------------------------------------------|------------
// [ x ]   [ x ]   [ x ]   [ x ]   [ x ]   [ 0 ]  [ 1 ]  [ 1 ]     | 0bxxxxx011 
//                                           |      |      |       |
//                                           (esim 64 = 011 = 3)
// -----------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------
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



/*
  kirjotan tän ehkä uusiks emt, se on aika psk
*/

// Funktio nostaa tai laskee annetun luvun arvoa n% määrällä
// step: potenssi, inputValue: manipuloitava arvo, stepSize: montako prosenttia arvoa nostetaan, decrease: lasketaanko vai nostetaanko
int percentStepHelper(int step, int inputValue = OCR1AVALUE, int stepSize = SPEEDUPVALUE, bool decrease = 1) {
  // näillä lasketaan stepSize% nosto
  float base = 1 + (stepSize * 0.01);  // 1 + (stepSize * 0.01),  esim. 1 + 10(%) * 0.01 = 1.1
  float multiplier = pow(base, step);       // base^step,              esim. 1.1² (²=step)


  // Palautetaan stepSize% alennettu arvo, jos decrease on 1
  return decreaseByPercentage(inputValue, multiplier);
}



// Nollaa timerin
void resetTimer(){
// TCNT1 (16-bit Laskuri)
// [ BIT15 . . . . . . . . . . . . . BIT0 ]     | TCNT1
// --------------------------------------------------------
// [ 0 0 0 0 0 0 0 0   0 0 0 0 0 0 0 0          | 0x0000
//   Nollataan laskurirekisteri
// --------------------------------------------------------  
  TCNT1 = 0;  
// --------------------------------------------------------
}

// Pysäyttää timer1
void stopTimer() {
// TIMSK1
// [-----] [-----] [ICIE1] [-----] [-----] [OCIE1B] [OCIE1A] [TOIE1]    | TIMSK1
// ---------------------------------------------------------------------|------------
// [ x ]   [ x ]   [ x ]   [ x ]   [ x ]   [ x ]    [ 0 ]    [ x ]      | 0bxxxxxx0x  
//                                                    |                 |                  
//                                          (TIMER1_COMPA_vect)            
// ----------------------------------------------------------------------------------  
  TIMSK1 &= ~(1 << OCIE1A);  // asetetaan andilla ja notilla timerpinni hiljaseksi
// ----------------------------------------------------------------------------------
  
// TCCR1B
// [ICNC1] [ICES1] [-----] [WGM13] [WGM12] [CS12] [CS11] [CS10]    | TCCR1B
// ----------------------------------------------------------------|------------
// [ x ]   [ x ]   [ x ]   [ x ]   [ x ]   [ 0 ]  [ 0 ]  [ 0 ]     | 0bxxxxx000  
//                                           |      |      |       |
//                                           (      0      )
// -----------------------------------------------------------------------------
  prescalerHelper(0);     // asettaa ajastimen kokonaan pois päältä
// -----------------------------------------------------------------------------

// TIFR1
// [-----] [-----] [ICF1]  [-----] [-----] [OCF1B]  [OCF1A]  [TOV1]    | TIFR1
// ---------------------------------------------------------------------|----------------
// [ x ]   [ x ]   [ x ]   [ x ]   [ x ]   [ x ]    [ 1 ]    [ x ]      | 0bxxxxxx1x  
//                                                    |                 |                  
//                                              (keskeytys flagi)       
// --------------------------------------------------------------------------------------
  TIFR1 |= (1 << OCF1A);    // nollataan tulevat keskeytykset
// --------------------------------------------------------------------------------------
}

/*
  nämä pitänee siirtää johonki muualle .h tai .ino ? ehkä oma vars.h kaikille ?
  timercounteria vois varmaan käyttää tälleen:
  
  timerCounter++ kun painaa nappia tai timer tickka
  jos checkValue palauttaa true (timerCounter >= 10) => timerSpeedUp

  */
volatile uint8_t timerCounter = 0; 
volatile uint8_t timerPotency = 0;

/*
varmaan pitää toi potenssi vielä hirttää ettei se pääse karkuun
*/
// nopeuttaa ajastinta asetettujen arvojen verran
void timerSpeedUp(uint8_t potency, int maxValue = 150){
  uint16_t value = percentStepHelper(potency);
    
  if (isValueUnderN(value, maxValue) == true) { 
    value = maxValue; // 
  }
    
  OCR1A = value; // Asetetaan laskettu arvo
}


/*
emt pitäskö näille matikkafunktioillekki tehä vaan joku oma tiedostonsa
*/

// palauttaa true/false jos arvo on yli maksimiarvon
bool isValueOverN(int value, int maxValue){ //10 tilalle vois ehkä lisätä oman "asetuksen" jos huvittaa
  return value >= maxValue; // palauttaa true/false riippuen lopputuloksesta
}
// palauttaa true/false jos arvo on alle max
bool isValueUnderN(int value, int maxValue){ //10 tilalle vois ehkä lisätä oman "asetuksen" jos huvittaa
  return value <= maxValue; // palauttaa true/false riippuen lopputuloksesta
}

int decreaseByPercentage(uint16_t value, float multiplier) {
  return value / multiplier;
}

ISR(TIMER1_COMPA_vect) {
  timerCounter++; // Timer pyörinyt +1 kertaa
  newTimerInterrupt = true; 

  if(isValueOverN(timerCounter, 10) == true){
    timerCounter = 0;
    timerPotency++;
    timerSpeedUp(timerPotency);
    resetTimer(); // Nollaa ajastin ettei tapahdu kummallisuuksia
  }
}