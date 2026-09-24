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
    while(!gameOn){

        for(int luku = 0; luku <=15; luku++){ //luku on näytettävä numero desimaalilukuna

            if(gameOn){
                //kun peli alkaa, nollataan 00111100 bitit ja poistutaan showsta
                PORTC &= ~((1 << PC2) | (1 << PC3) | (1 << PC4) | (1 << PC5));
                return;
            }

            //laitetaan PORTC maskiksi 00111100 ---> '~' eli nollataan PC2, PC3, PC4, PC5. nää bitit vastaa pinnejä 16-19
            //'luku' bittejä pitää siirtää 2 pykälää (PC0 -> PC2), että se ohjaa oikeita ledejä
            PORTC = (PORTC & ~((1 << PC2) | (1 << PC3) | (1 << PC4) | (1 << PC5))) | (luku << 2);
            delay(400); //numero näkyy 400ms

            // nollataan bitit 00111100
            PORTC &= ~((1 << PC2) | (1 << PC3) | (1 << PC4) | (1 << PC5));
            delay(200); //pidetään ledejä nollattuna 200ms

        }
        PORTC &= ~((1 << PC2) | (1 << PC3) | (1 << PC4) | (1 << PC5)); //nollataan bitit 00111100 shown jälkeen   
    
    }
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




