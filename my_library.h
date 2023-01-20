#ifndef MY_LIBRARY_H
#define MY_LIBRARY_H

#include <Arduino.h>

bool inTolerance(double referenceProportion, int valueToCheck, int benchmark, int percentOfTolerance);

void wrongAttempt(int &firstClap, long &startTime, long &benchmark, int &proportionInArray, int redLED, int yellowLED);

#endif