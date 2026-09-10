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


void show1()    //kesken
{
    for (int i = 0; i < 15; i ++){
        
    }

    
}

void show2(int rounds)
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




