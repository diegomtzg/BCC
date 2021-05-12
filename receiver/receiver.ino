#include "cppQueue.h"

#define SLIDING_WINDOW_SIZE 20
#define BIT_THRESHOLD 7

enum Mode { synchronizing, reading };

float runningMean = 0;
int touchPin = A5;
long lastTime = 0;
long lastTick = 0;
long period = 1000;

Mode currMode;
float lastVal = 0;
char readVal = 0;

cppQueue queue(sizeof(float), SLIDING_WINDOW_SIZE, FIFO);

void setup() {
  Serial.begin(9600);
  pinMode(touchPin, INPUT);
  
  lastTime = millis();
  currMode = synchronizing;
}

void loop() {
  if (currMode == synchronizing) {
    if (bitChanged(lastVal, runningMean)) {
      // Since bit changed, we are synchronized with signal and can begin reading.
      currMode = reading;
      lastTick = millis();
    }
  }

  if (currMode == reading) {
    long currTime = millis();
    if (currTime - lastTick > period) {
      // A full period has passed, read new value.
      lastTick = currTime; 
      
      // Update read value
      readVal = (char) readVal << 1;  
      if (runningMean > BIT_THRESHOLD) {
        readVal = readVal | 1; // Add a one to the end of the value.
      }

      Serial.println(readVal);
    }
  }

  // Raw input reading and averaging.
  float currVal = analogRead(touchPin);
  if (queue.isFull()) {
      float oldVal;
      queue.pop(&oldVal);
      lastVal = runningMean;
      runningMean -= oldVal / SLIDING_WINDOW_SIZE;
  }
  queue.push(&currVal);
  lastVal = runningMean;
  runningMean += currVal / SLIDING_WINDOW_SIZE;
  
//  plotData(currVal, runningMean);
}

bool bitChanged(float oldVal, float currVal) {
  return (oldVal < BIT_THRESHOLD && currVal >= BIT_THRESHOLD) || (oldVal > BIT_THRESHOLD && currVal <= BIT_THRESHOLD);
}

// Logic
// If value changed, start period timer (synchronize signals)
// Then, after each period, check value to read bits.
// Accumulate bits and check until it's M or A.

void plotData(float val1, float val2) {
  Serial.print("50,");
  Serial.print(val1);
  Serial.print(",");
  Serial.print(val2);
  Serial.println();
}
