#include "leds.h"

byte ledi[] = {A2, A3, A4, A5};     //ledeistä taulukko



void initializeLeds()
{
    pinMode(A2, OUTPUT);    //määritellään pinnit A2, A3, A4 ja A5 output-pinneiksi
    pinMode(A3, OUTPUT);
    pinMode(A4, OUTPUT);
    pinMode(A5, OUTPUT);
}

void setLed(byte ledNumber)
{
    digitalWrite(ledi[ledNumber], HIGH);
}


void clearAllLeds()
{
    for (int i = 0; i < 4; i++)     //käydään läpi kaikki ledit
    {
        digitalWrite(ledi[i], LOW);     //laitetaan ledit pois päältä
    }
}

void setAllLeds()
{
    for (int i = 0; i < 4; i++)     //käydään läpi kaikki ledit
    {
        digitalWrite(ledi[i], HIGH);    //laitetaan ledit päälle
    }
}


void show1()    //näyttää 0 -> 15 binääriluvuin ledeillä
{   //tähän vois myös laittaa jonkun while loopin jos tarvii
    for (int i = 0; i <= 15; i ++){

        clearAllLeds(); //pyyhitään ledit aina ennen uuden binääriluvun näyttöä
        delay(200); //200ms viive ennen seuraavan luvun näyttöä

        switch (i){ //for-silmukka määrää casen

        case 0: //0000, kaikki ledit pois päältä
        break; //poistutaan switchistä

        case 1: //0001
        setLed(0); //sytytetään led 0
        break;

        case 2: //0010
        setLed(1);
        break;

        case 3: //0011
        setLed(0);
        setLed(1);
        break;

        case 4: //0100
        setLed(2);
        break;

        case 5: //0101
        setLed(0);
        setLed(2);
        break;

        case 6: //0110
        setLed(1);
        setLed(2);
        break;

        case 7: //0111
        setLed(0);
        setLed(1);
        setLed(2);
        break;

        case 8: //1000
        setLed(3);
        break;

        case 9: //1001
        setLed(0);
        setLed(3);
        break;

        case 10: //1010
        setLed(1);
        setLed(3);
        break;

        case 11: //1011
        setLed(0);
        setLed(1);
        setLed(3);
        break;

        case 12: //1100
        setLed(2);
        setLed(3);
        break;

        case 13: //1101
        setLed(0);
        setLed(2);
        setLed(3);
        break;

        case 14: //1110
        setLed(1);
        setLed(2);
        setLed(3);
        break;

        case 15: //1111
        setLed(0);
        setLed(1);
        setLed(2);
        setLed(3);
        break;

        }
        delay(500); //näytetään jokaista lukua 500ms
    }
    clearAllLeds(); //valot nollataan for-loopin jälkeen
    delay(2000); //odotetaan 2s ennen kuin seuraava show voi alkaa
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




