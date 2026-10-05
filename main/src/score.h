#ifndef SCORE_H
#define SCORE_H
#include <Arduino.h>
#include "settings.h"
#include "helpers.h"
#include "EEPROM.h"

extern byte savedScores[];


void saveScore(byte newScore);
bool checkScore(byte newScore);

void writeEEPROM();
void updateEEPROM();
void readEEPROM();
void clearEEPROM();
#endif