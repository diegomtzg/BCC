#include "cppQueue.h"

#define SLIDING_WINDOW_SIZE 30

float runningMean = 0;
int signalPin = A0;
int touchPin = A5;
long lastTime = 0;

cppQueue queue(sizeof(float), SLIDING_WINDOW_SIZE, FIFO);

void setup() {
  Serial.begin(9600);
  pinMode(signalPin, INPUT);
  pinMode(touchPin, INPUT);
}

void loop() {
  float truthVal = analogRead(signalPin);
  float touchVal = analogRead(touchPin);

  if (queue.isFull()) {
      float oldVal;
      queue.pop(&oldVal);
      runningMean -= oldVal / SLIDING_WINDOW_SIZE;
  }
  
  queue.push(&touchVal);
  runningMean += touchVal / SLIDING_WINDOW_SIZE;

  plotData(touchVal, runningMean);
}

void plotData(float val1, float val2) {
  Serial.print("100,");
  Serial.print(val1);
  Serial.print(",");
  Serial.print(val2);
  Serial.println();
}
