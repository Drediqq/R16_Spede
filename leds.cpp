#include "leds.h"

void initializeLeds()
{
for(int i = firstLedPin; i <= lastLedPin; i++){
    pinMode(i, OUTPUT);
  }
}

void setLed(byte ledNumber)
{
    digitalWrite(ledNumber, HIGH);
}


void clearAllLeds()
{
    for (int i = firstLedPin; i <= lastLedPin; i++)     //käydään läpi kaikki ledit
    {
        digitalWrite(i, LOW);     //laitetaan ledit pois päältä
    }
}

void setAllLeds()
{
    for (int i = firstLedPin; i <= lastLedPin; i++)     //käydään läpi kaikki ledit
    {
        digitalWrite(i, HIGH);    //laitetaan ledit päälle
    }
}


void show1()    //näyttää 0 -> 15 binääriluvuin ledeillä
{   

    
    
    
    //..-.ö.
    
    /*//tähän vois myös laittaa jonkun while loopin jos tarvii
    for (int i = 0; i <= 15; i ++){

        clearAllLeds(); //pyyhitään ledit aina ennen uuden binääriluvun näyttöä
        delay(200); //200ms viive ennen seuraavan luvun näyttöä

        switch (i){ //for-silmukka määrää casen

        case 0: //0000, kaikki ledit pois päältä
        break; //poistutaan switchistä

        case 1: //0001
        setLed(16); //sytytetään led 0
        break;

        case 2: //0010
        setLed(17);
        break;

        case 3: //0011
        setLed(16);
        setLed(17);
        break;

        case 4: //0100
        setLed(18);
        break;

        case 5: //0101
        setLed(16);
        setLed(18);
        break;

        case 6: //0110
        setLed(17);
        setLed(18);
        break;

        case 7: //0111
        setLed(16);
        setLed(17);
        setLed(18);
        break;

        case 8: //1000
        setLed(19);
        break;

        case 9: //1001
        setLed(16);
        setLed(19);
        break;

        case 10: //1010
        setLed(17);
        setLed(19);
        break;

        case 11: //1011
        setLed(16);
        setLed(17);
        setLed(18);
        break;

        case 12: //1100
        setLed(18);
        setLed(19);
        break;

        case 13: //1101
        setLed(16);
        setLed(18);
        setLed(19);
        break;

        case 14: //1110
        setLed(17);
        setLed(18);
        setLed(19);
        break;

        case 15: //1111
        setLed(16);
        setLed(17);
        setLed(18);
        setLed(19);  
        break;

        }
        delay(500); //näytetään jokaista lukua 500ms
    }
    clearAllLeds(); //valot nollataan for-loopin jälkeen
    delay(2000); //odotetaan 2s ennen kuin seuraava show voi alkaa */
}

void show2(int rounds) //vilkuttaa ledejä 0, 1, 2, 3 kiihtyvällä tahdilla
{
    int kaydytkierrokset = 0;
    int odotusaika = 1000;

    while (kaydytkierrokset < rounds){      //toistetaan valoshow 'rounds' verran
        for(int i = 0; i < 4; i++){     //sytytetään ledit yksi kerrallaan
            setLed(i);
            delay(odotusaika);
        }
        clearAllLeds();
        delay(odotusaika);
        odotusaika = odotusaika * 0.85;      //odotusaika pienenee jokaisen käydyn kierroksen jälkeen
        kaydytkierrokset++;
    }
}




