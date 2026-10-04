#ifndef logic_h
#define logic_h
#include <Arduino.h>

extern volatile int buttonNumber;
extern volatile bool newTimerInterrupt;
extern int matchedCount;
extern byte sequence[20];
extern int litCount;
extern bool gameOn;

void checkGame(byte);
void initializeGame(void);
void startTheGame(void);
void endGame(void);

#endif