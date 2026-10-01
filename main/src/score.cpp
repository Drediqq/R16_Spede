#include "Arduino.h"
#include "settings.h"
#include "score.h"
#include "helpers.h"
#include "EEPROM.h"


/*
if(checkScore(...)){
    saveScore(...);    
} 
*/

// tallentaa tulokset taulukkoon
void saveScore(byte newScore){
    for (int i = 0; i < ARR_LEN; i++) {
        if (newScore > savedScores[i]) {
            // siirretään häviäjät alemmas
            for (int j = ARR_LEN - 1; j > i; j--) {
                savedScores[j] = savedScores[j - 1];
            }
        // asetetaan uusi score taulukon indeksiin
        savedScores[i] = newScore;
        updateEEPROM();
        break;
        }
    }
}

// tarkistaa tallennetaanko scorea vai ei
bool checkScore(byte newScore){
    // tallennetaan vain jos score on suurempi, ei tallenneta jos yhtäsuuri tai pienempi
    byte lastScore = savedScores[ARR_LEN-1];
    byte firstScore = savedScores[0];

    // jos newScore on suurempi kuin eka, mennään suoraan tallentamaan
    if(compareValuesHelper(newScore, firstScore) == 1){
        return 1;
    }
    // jos arvo on sama tai pienempi kuin pienin
    if(compareValuesHelper(newScore, lastScore) <= 0){
        return 0;
    }
    // tarkistetaan muut arvot, jos eka tarkistus meni läpi
    for(int i = ARR_LEN-2; i >= 0; i--) {
        if (compareValuesHelper(newScore, savedScores[i]) == 0) {
            return 0; // jos löytyy duplicate poistutaan
        }
    }

    return 1;
}



// Note: An EEPROM write takes 3.3 ms to complete. 
// The EEPROM memory has a specified life of 100,000 write/erase cycles, 
// so you may need to be careful about how often you write to it.

// osoite 0 kannattaa vissiin laittaa joku random luku eli ns. magicbyte, vaikka 0xDF = 223
// esim vaikka osoite 1 = 8 bittiä eli saa asetettua arvon 0-255
// jos päätetään käyttää 16bittisiä niin sitten oletan että se vie sit osoitteet 1 ja 2
// ja arvo on 0-65535

// kirjoittaa scoret eepromille
void writeEEPROM(){
    byte check = 0xDF;
    byte valid = 0;
    EEPROM.get(0, valid);

    if(check != valid)
    {
        EEPROM.put(0, 0xDF);
    }


    EEPROM.put(0, 0xDF);
}
// päivittää scoret eepromille, käytetään kun sinne eepromille on jo kirjoitettu jotain
void updateEEPROM(){  
    for(int i = 1; i < ARR_LEN; i++)
    {
        EEPROM.update(i, savedScores[i-1]);
    }
}
// lataa scoret eepromilta
void readEEPROM(){
    for(int i = 1; i < ARR_LEN; i++)
    {
        EEPROM.get(i, savedScores[i-1]);
    }
}

// tyhjentää eepromin 
void clearEEPROM(){ 
    // voi olla et kannattaa alottaa ykkösestä nii ei mee magicbyte hukkaan
    for(int i = 1; i < EEPROM.length(); i++) { 
        EEPROM.write(i, 0); 
    }
}

