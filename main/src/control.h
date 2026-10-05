#ifndef CONTROL_H
#define CONTROL_H
#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "helpers.h"
#include "logic.h"
#include "settings.h"


void standby();
void logicControl();
void buttonControl(int);

#endif
