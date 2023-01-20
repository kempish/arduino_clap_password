/*
  https://youtu.be/TVf06RCl4q0
*/

#include "my_library.h"

// PINS
const int GREEN_LED   = 7;
const int YELLOW_LED  = 8;
const int RED_LED     = 10;
#define soundPin 5

// VARIABLES
long startTime;           // first clap → start measuring time
long stopTime;            // second clap → stop measuring time → (stop-time)=benchmark
long benchmark;           // difference between first and second clap - tolerance and rythm pattern proportions base on it
long sincePreviousClap;   // to measure time between two claps
long currentClap;
const int RYTHM_LENGHT = 6;
double rythmPattern[RYTHM_LENGHT] = {1.00, 0.50, 0.50, 1.00, 2.00, 1.00};   // proportion between two claps and benchmark (eg. clap|clap=2000ms, benchmark=1000ms → proportion=2.00) 
int proportionInArray = 1;                      // to iterate through rythm array (start from 1 → 0 is benchmark)
const int PERCENT_OF_BENCHMARK_TOLERANCE = 30;  // 30% = 0.70 - 1.30 according to proportion
int firstClap = 0;
const int SAMPLE = 50;      // sound sample
const int SHORT_DELAY = 5;


void setup() {
  Serial.begin(9600);
  pinMode(soundPin, INPUT);  
  pinMode(GREEN_LED, OUTPUT);  
  pinMode(YELLOW_LED, OUTPUT);  
  pinMode(RED_LED, OUTPUT);
}


void loop() {

  int soundData = digitalRead(soundPin);

  // if it is a first clap → start measuring benchmark (necessary to follow tempo of rythm) + turn on yellow diod
  if (soundData == HIGH && firstClap == 0) {
    firstClap ++;
    digitalWrite(YELLOW_LED, HIGH);
    startTime = millis();
  }

  // if second clap → determine benchmark if not determined before
  if (soundData == HIGH && millis() - startTime >= SAMPLE && benchmark == 0) {
    stopTime = millis();
    benchmark = stopTime-startTime;
    sincePreviousClap = millis();
    delay(SHORT_DELAY);
  }

  // if benchmark is determined → follow next claps and check their proportion compare to previous clap (according to rythm pattern in array)
  else if (benchmark!=0 && soundData == HIGH && millis() - startTime >= SAMPLE) {
    
    // take next proportion from rythm array
    double perfectProportion = rythmPattern[proportionInArray];
    
    // time since last clap
    currentClap = millis() - sincePreviousClap;

    // check if clap is align with rythm pattern (proportions)
    bool clapCorrect = inTolerance(perfectProportion, currentClap, benchmark, PERCENT_OF_BENCHMARK_TOLERANCE);

    // if clap is not align with rythm pattern → stop, reset values and start from scratch | otherwise → continue to follow next clap
    if (!clapCorrect) {
      wrongAttempt(firstClap, startTime, benchmark, proportionInArray, RED_LED, YELLOW_LED);
    }
    else{
      delay(SHORT_DELAY);
      sincePreviousClap = millis();   // reset time since last clap
      proportionInArray ++;
    }
  
    // if end of rythm pattern and sound password is correct (= all claps are in proportion) → turn off yellow and turn on green diod
    if (proportionInArray == RYTHM_LENGHT) {
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);
    }

  }

}






