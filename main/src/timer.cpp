#include "timer.h"

/*
###############################
###### Prescaler Helper ######
#############################
*/
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

  switch (prescaling) { //  cs12 cs11 cs10
  case 0:
    scalerBits = 0;
    break; //  [ 0 ][ 0 ][ 0 ]  = 0
  case 1:
    scalerBits = 1;
    break; //  [ 0 ][ 0 ][ 1 ]  = 1
  case 8:
    scalerBits = 2;
    break; //  [ 0 ][ 1 ][ 0 ]  = 2
  case 64:
    scalerBits = 3;
    break; //  [ 0 ][ 1 ][ 1 ]  = 3
  case 256:
    scalerBits = 4;
    break; //  [ 1 ][ 0 ][ 0 ]  = 4
  case 1024:
    scalerBits = 5;
    break; //  [ 1 ][ 0 ][ 1 ]  = 5
  default:
    Serial.println("Invalid scaler");
    return;
  }

  // TCCR1B
  // [ICNC1] [ICES1] [-----] [WGM13] [WGM12] [CS12] [CS11] [CS10]    | TCCR1B
  // ----------------------------------------------------------------|------------
  // [ x ]   [ x ]   [ x ]   [ x ]   [ x ]   [ 0 ]  [ 1 ]  [ 1 ]     |
  // 0bxxxxx011
  //                                           |      |      |       |
  //                                           (esim 64 = 011 = 3)
  // -----------------------------------------------------------------------------
  // Syötetään bittiarvo ja asetetaan haluttu scaleri
  TCCR1B = (TCCR1B & ~((1 << CS12) | (1 << CS11) | (1 << CS10))) | scalerBits;
}

/*
###############################
###### Initialize Timer ######
#############################
*/
// Asettaa ajastimelle tarpeelliset bitit oikeisiin asentoihin
void initializeTimer() {
  noInterrupts(); // Keskeytykset pois päältä

  // TCCR1A
  // [COM1A1] [COM1A0] [COM1B1] [COM1B0] [-----] [-----] [WGM11] [WGM10]   |
  // TCCR1A
  // ----------------------------------------------------------------------|------------
  // [ 0 ]    [ 0 ]    [ 0 ]    [ 0 ]    [ 0 ]   [ 0 ]   [ 0 ]   [ 0 ]     |
  // 0b00000000
  //   Tyhjätään ohjausrekisteri                                           |
  // -----------------------------------------------------------------------------------
  TCCR1A = 0;
  // -----------------------------------------------------------------------------------

  // Asetetaan prescaler pois eli cs10,11,12 -> 000
  prescalerHelper(0);

  // Nollataan laskurirekisteri
  resetTimer();

  OCR1A = OCR1AVALUE; // Asetetaan vertailuarvo, jossa keskeytys tapahtuu

  // TCCR1B
  // [ICNC1] [ICES1] [-----] [WGM13] [WGM12] [CS12] [CS11] [CS10]    | TCCR1B
  // ----------------------------------------------------------------|------------
  // [ x ]   [ x ]   [ x ]   [ x ]   [ 1 ]   [ 1 ]  [ 0 ]  [ 1 ]     |
  // 0bxxxx1101
  //                                  CTC      |      |      |       |
  //                                           (esim 1024=101)
  // -----------------------------------------------------------------------------
  TCCR1B |= (1 << WGM12);     // CTC (Clear Timer on Compare Match)
  prescalerHelper(PRESCALER); // Muutettavissa toisaalla
  // ---------------------------------------------------------------------------------

  // käynnistetään ajastin
  timerControl(1);

  interrupts(); // Keskeytykset takaisin päälle
}

// Nollaa timerin
void resetTimer() {
  // TCNT1 (16-bit Laskuri)
  // [ BIT15 . . . . . . . . . . . . . BIT0 ]     | TCNT1
  // --------------------------------------------------------
  // [ 0 0 0 0 0 0 0 0   0 0 0 0 0 0 0 0          | 0x0000
  //   Nollataan laskurirekisteri
  // --------------------------------------------------------
  TCNT1 = 0;
  // --------------------------------------------------------
}

/*
###########################
###### timerControl ######
#########################
*/
// asettaa ajastimen päälle tai pois syötetyn boolin perusteella
void timerControl(bool state) {
  if (state) {
    // TIMSK1
    // [-----] [-----] [ICIE1] [-----] [-----] [OCIE1B] [OCIE1A] [TOIE1]    |
    // TIMSK1
    // ---------------------------------------------------------------------|------------
    // [ x ]   [ x ]   [ x ]   [ x ]   [ x ]   [ x ]    [ 1 ]    [ x ]      |
    // 0bxxxxxx1x
    //                                                    |                 |
    //                                          (TIMER1_COMPA_vect)
    // -----------------------------------------------------------------------------------
    TIMSK1 |= (1 << OCIE1A); // Timer1 Output Compare A Interrupt Enable
    // -----------------------------------------------------------------------------------
  } else {
    // TIMSK1
    // [-----] [-----] [ICIE1] [-----] [-----] [OCIE1B] [OCIE1A] [TOIE1]    |
    // TIMSK1
    // ---------------------------------------------------------------------|------------
    // [ x ]   [ x ]   [ x ]   [ x ]   [ x ]   [ x ]    [ 0 ]    [ x ]      |
    // 0bxxxxxx0x
    //                                                    |                 |
    //                                          (TIMER1_COMPA_vect)
    // ----------------------------------------------------------------------------------
    TIMSK1 &= ~(1 << OCIE1A); // asetetaan timer pin 0
    // ----------------------------------------------------------------------------------
  }
}

/*
########################
###### stopTimer ######
######################
*/
// Pysäyttää timerin kokonaan
void stopTimer() {
  timerControl(0);

  // TCCR1B
  // [ICNC1] [ICES1] [-----] [WGM13] [WGM12] [CS12] [CS11] [CS10]    | TCCR1B
  // ----------------------------------------------------------------|------------
  // [ x ]   [ x ]   [ x ]   [ x ]   [ x ]   [ 0 ]  [ 0 ]  [ 0 ]     |
  // 0bxxxxx000
  //                                           |      |      |       |
  //                                           (      0      )
  // -----------------------------------------------------------------------------
  prescalerHelper(0); // asettaa ajastimen kokonaan pois päältä
  // -----------------------------------------------------------------------------

  // TIFR1
  // [-----] [-----] [ICF1]  [-----] [-----] [OCF1B]  [OCF1A]  [TOV1]    | TIFR1
  // ---------------------------------------------------------------------|----------------
  // [ x ]   [ x ]   [ x ]   [ x ]   [ x ]   [ x ]    [ 1 ]    [ x ]      |
  // 0bxxxxxx1x
  //                                                    |                 |
  //                                              (keskeytys flagi)
  // --------------------------------------------------------------------------------------
  TIFR1 |= (1 << OCF1A); // nollataan tulevat keskeytykset
  // --------------------------------------------------------------------------------------

  timerPotency = 0; // asettaa nopeuskertoimen 0
}

/*
###########################
###### timerSpeedUp ######
#########################
*/
// nopeuttaa ajastinta
// ottaa vastaan potenssin ja minimiarvon
void timerSpeedUp(uint8_t potency, int minValue) {
  float multiplier = multiplierHelper(SPEEDUPVALUE * difficulty, potency);
  uint16_t value = percentReductionHelper(OCR1AVALUE, multiplier);

  //
  if (value < minValue) {
    value = minValue;
  }

  OCR1A = value; // Asetetaan laskettu arvo
}

/*
#######################
###### IsItTime ######
#####################
*/
// nostaa nopeutta jos litcount % SPEEDUPINTERVAL == 0
void isItTime(int value) {
  if (value != 0) {
    if ((value % SPEEDUPINTERVAL) == 0) {
      timerPotency++;
      timerSpeedUp(timerPotency, MAXSPEED);
      resetTimer(); // Nollaa ajastin ettei tapahdu kummallisuuksia
    }
  }
}

/*
################################
###### Interrupt service ######
##############################
*/
ISR(TIMER1_COMPA_vect) {
  if (newTimerInterrupt != true) {
    newTimerInterrupt = true;
  }
}