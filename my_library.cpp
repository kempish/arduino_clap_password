#include "my_library.h"

bool inTolerance(double referenceProportion, int valueToCheck, int benchmark, int percentOfTolerance) {

  // convert all long and int values into double
  double valueToCheckDouble       = valueToCheck;       // e.g. 1128 ms → 1128.00
  double benchmarkDouble          = benchmark;          // ↑
  double percentOfToleranceDouble = percentOfTolerance;
  double base                     = 1;
  double baseUpperDeviation       = base + base*(percentOfToleranceDouble/100); // + tolerance
  double baseLowerDeviation       = base - base*(percentOfToleranceDouble/100); // - tolerance

  /*
    explanation on simple case:
    benchmark is 1000 ms and referenceProportion (rythm value) is 2.00
    therefore real space between two claps should be 2000 ms +/- tolerance (10%)

    if value to check is 2108 ms we need to adjust benchmark value as well:
    
    value to check / (benchmark * reference proportion)
    2108 / (1000 * 2.00) = 1.05 → which is realProportion

    if realProportion is between base(1) +/- tolerance(10%) [which is respectively 1.1 and 0.9]
    ↓
    return true;
    
    otherwise:
    return false;

    in this case tolerance is 10% and 2108 ms/2000 ms = 1.05 also it is in range (0.9 - 1.1)
  */

  double realProportion = valueToCheckDouble / (benchmarkDouble * referenceProportion);

  bool result = (realProportion > baseUpperDeviation || realProportion < baseLowerDeviation)?false:true;


  return result;
  
}

void wrongAttempt(int &firstClap, long &startTime, long &benchmark, int &proportionInArray, int redLED, int yellowLED) {

  /*
    (occures if rythm pattern is incorrect)
    turn off yellow diod, turn of red diod
    reset benchmark and wait 3 sec to make a fresh start
  */
  
  // reset benchmark and related data
  firstClap = 0;
  startTime = 0;
  benchmark = 0;
  proportionInArray = 1;

  // turn off yellow diod, turn on red diod for 3 sec
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, HIGH);
  delay(3000);
  digitalWrite(redLED, LOW);

};



