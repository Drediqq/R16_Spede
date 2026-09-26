#include "Arduino.h"
#include "score.h"
#include "helpers.h"


byte savedScores[ARR_LEN] = {0}; 

// tallentaa tulokset taulukkoon
void saveScore(byte newScore){
    for (int i = 0; i < ARR_LEN; i++) {
        if(newScore == savedScores[i]){
            Serial.println("Score already exists, skip");
            break;
        }
        if (newScore > savedScores[i]) {
        // siirretään häviäjät alemmas
            for (int j = ARR_LEN - 1; j > i; j--) {
                savedScores[j] = savedScores[j - 1];
            }
        // asetetaan uusi score taulukon indeksiin
        savedScores[i] = newScore;
        break;
        }
    }
}
byte ARR_LENmin = ARR_LEN -1;
// tarkistaa tallennetaanko scorea vai ei
void checkScore(byte newScore){
    if(newScore < savedScores[ARR_LEN-1]){
      Serial.println("less than minimum");
    }else{
        saveScore(newScore);
    }
}

// !!!!!!!!!!!!!!
// nää nyt riippuu aika paljo siitä että pitääkö meidän manipuloida 
// sitä EEPROMia manuaalisesti vai mahtaako saada käyttää EEPROM.h kirjastoa
// !!!!!!!!!!!!!!

// päivittää scoret eepromille
void writeEEPROM(){
    // EEPROM.update(...);
}

// lataa scoret eepromilta
void readEEPROM(){
    // EEPROM.get();
}

// tyhjentää eepromin 
// varmaan pitää vaan ajaa bx00000000 * 1024 tai jotain
void clearEEPROM(){
  
}

