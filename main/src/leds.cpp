#include "leds.h"
#include "Arduino.h"
#include "control.h"

void initializeLeds()
{
for(int i = firstLedPin; i <= lastLedPin; i++){
    pinMode(i, OUTPUT);
  }
}

void setLed(byte ledNumber)
{
    digitalWrite(ledNumber+firstLedPin-1, HIGH);
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
    static uint32_t aloitusaika;
    static int edellinen = -1;
    static int luku = 0; //luku on näytettävä numero desimaalilukuna
 
               
            //laitetaan PORTC maskiksi 00111100 ---> '~' eli nollataan PC2, PC3, PC4, PC5. nää bitit vastaa pinnejä 16-19
            //'luku' bittejä pitää siirtää 2 pykälää (PC0 -> PC2), että se ohjaa oikeita ledejä
            PORTC = (PORTC & ~((1 << PC2) | (1 << PC3) | (1 << PC4) | (1 << PC5))) | (luku << 2);

            if(edellinen != luku){
                aloitusaika = millis(); //aloitusaikaan otetaan ohjelman aloittamisesta tähän asti kulunut aika
                edellinen = luku;
            }

            if(millisHelper(aloitusaika, (2 * LEDBLINKTIME))){
                PORTC &= ~((1 << PC2) | (1 << PC3) | (1 << PC4) | (1 << PC5));
                
                if (millisHelper(aloitusaika, LEDBLINKTIME)){
                    PORTC &= ~((1 << PC2) | (1 << PC3) | (1 << PC4) | (1 << PC5)); //nollataan bitit 00111100 shown jälkeen  
            
                    edellinen = luku;
                    luku++; 
                    if(luku > 15){
                        luku = 0;
                    }
                    
                    
            } //kun 2 * 'LEDBLINKTIME' (settings.h) kulunut ---> millisHelper = true jolloin ohjelma jatkuu

            // nollataan bitit 00111100
            
           
            }
            } //kun 'LEDBLINKTIME' kulunut ---> millisHelper = true jolloin ohjelma jatkuu


void show2(int rounds) //vilkuttaa ledejä 0, 1, 2, 3 kiihtyvällä tahdilla
{
    int kaydytkierrokset = 0;
    int odotusaika = 500;

    while (kaydytkierrokset < rounds){      //toistetaan valoshow 'rounds' verran
        for(int i = 1; i <= 4; i++){     //sytytetään ledit yksi kerrallaan
            setLed(i);
            delay(odotusaika);
        }
        clearAllLeds();
        delay(odotusaika);
        odotusaika = odotusaika * 0.85;      //odotusaika pienenee jokaisen käydyn kierroksen jälkeen
        kaydytkierrokset++;
    }
}




