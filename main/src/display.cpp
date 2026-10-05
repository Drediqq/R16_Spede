#include "display.h"



// 74HC595:n ohjauspinnit

const int shiftClockPin = 13; // siirtorekisterin kellopinni.
const int latchClockPin = 12; // siirtorekisterin lukituspinni. lukitaan LOW->HIGH siirtymä, jolloin siirtorekisterin sisältö kopioidaan lähtöihin.
const int serialPin = 11; // siirtää dataa sarjamuodossa rekisteriin.



// Numerot 0-9 binäärimuodossa (Common Cathode 7-segmenttinäyttöä käytettäessä) 
// Jos halutaan käyttää Common Anode -näyttöä, niin binäärimuodot pitää invertoida (eli 0b00111111 -> 0b11000000 jne.)
const byte numTable[] =
{
    0b10111110, // 0
    0b00000110, // 1
    0b11011010, // 2
    0b11001110, // 3
    0b01100110, // 4
    0b11101100, // 5
    0b11111100, // 6
    0b10000110, // 7
    0b11111110, // 8
    0b11101110, // 9
};


void initializeDisplay(void) // alustetaan siirtorekisterin ohjauspinnit
{
  
  pinMode(shiftClockPin, OUTPUT); // siirtorekisterin kellopinni ulostuloksi, jotta voidaan siirtää dataa rekisteriin
  pinMode(latchClockPin, OUTPUT); // siirtorekisterin lukituspinni ulostuloksi, jotta voidaan kopioida rekisterin sisältö lähtöihin
  pinMode(serialPin, OUTPUT); // siirtorekisterin sarjamuotoinen datalähtö ulostuloksi, jotta voidaan siirtää dataa rekisteriin

  //digitalWrite(resetPin, HIGH);  // vapautetaan siirtorekisteri nollauksesta
  //digitalWrite(outEnablePin, LOW);  // sallitaan siirtorekisterin lähtöjen käyttö
}


void writeByte(uint8_t bits,bool last)  
{ 
   if(bits >= sizeof(numTable)) // Vältetään luvut, jotka ei ole 0-9 välillä, koska numTable sisältää vain luvut 0-9. Jos luku on suurempi kuin 9, ei tehdä mitään.
  {
    return; 
  }
  //Lähetetään valitun numeron segmenttikuvio siirtorekisteriin sarjamuodossa
  shiftOut(serialPin, shiftClockPin, MSBFIRST, numTable[bits]);
    
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
  if (number > 99) 
  {
    number = 99; // Jos luku on suurempi kuin 99, näytetään vain 99
  }

  // Erotellaan kaksinumeroisesta luvusta kymmenet ja ykköset
  uint8_t tens = number / 10;
  uint8_t ones = number % 10;
  
  // Näytetään tulos segmenttinäytöillä
  writeHighAndLowNumber(tens, ones);
}

void countDown(byte steps)
{
  for(int i = steps; i > 0; i--)
  {
    showResult(i);
    delay(1000);
  }
}

void scoreHandler(byte index)
{
  byte score = savedScores[index % ARR_LEN];
  showResult(score);
}
