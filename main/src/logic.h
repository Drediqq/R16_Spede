#ifndef logic_h
#define logic_h
#include <Arduino.h>

extern volatile int buttonNumber;
extern volatile bool newTimerInterrupt;
extern byte matchedCount;
extern volatile byte sequence[20];
extern volatile int litCount;
extern bool gameOn;

void checkGame(byte);
void initializeGame(void);
void startTheGame(void);
void endGame(void);

#endif