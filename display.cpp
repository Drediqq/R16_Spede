#include "display.h"

// 74HC595:n ohjauspinnit
const int resetPin = 12;
const int shiftClockPin = 11;
const int latchClockPin = 10;
const int outEnablePin = 9;
const int serialPin = 8;

// Numerot 0-9 (Common Cathode)
const byte numTable[] =
{
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111, // 9
};

void initializeDisplay(void)
{
  //Alustetaan siirtorekisterin ohjauspinnit ulostuloiksi
  pinMode(resetPin, OUTPUT);
  pinMode(shiftClockPin, OUTPUT);
  pinMode(latchClockPin, OUTPUT);
  pinMode(outEnablePin, OUTPUT);
  pinMode(serialPin, OUTPUT);

  // Poistetaan reset ja sallitaan lähtöjen käyttö
  digitalWrite(resetPin, HIGH);
  digitalWrite(outEnablePin, LOW);
}


void writeByte(uint8_t bits,bool last)
{    //Lähetetään valitun numeron segmenttikuvio siirtorekisteriin sarjamuodossa
    shiftOut(serialPin,
             shiftClockPin,
             MSBFIRST,
             numTable[bits]);
    
    //Päivitetään näytöt vasta viimeisen tavun jälkeen, jotta numerot vaihtuvat yhtäaikaa
    if(last)
    {
        digitalWrite(latchClockPin, LOW);
        digitalWrite(latchClockPin, HIGH);
    }
}


void writeHighAndLowNumber(uint8_t tens,uint8_t ones)
{
  //Kirjoitetaan ensin ykköset ja sitten kymmenet ketjutettuihin siirtorekistereihin
  writeByte(ones, false);
  writeByte(tens, true);
}

void showResult(byte number)
{
  // Erotellaan kaksinumeroisesta luvusta kymmenet ja ykköset
  uint8_t tens = number / 10;
  uint8_t ones = number % 10;
  
  // Näytetään tulos segmenttinäytöillä
  writeHighAndLowNumber(tens, ones);
}

