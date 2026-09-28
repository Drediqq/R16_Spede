#ifndef SCORE_H
#define SCORE_H
#include <Arduino.h>

void saveScore(byte newScore);
bool checkScore(byte newScore);

void writeEEPROM();
void updateEEPROM();
void readEEPROM();
void clearEEPROM();
#endif