int signalPin = A0;
int touchPin = A5;

long lastTime = 0;
long period = 10;
int freq = 100;

void setup()
{
    Serial.begin(9600);
    pinMode(signalPin, INPUT);
    pinMode(touchPin, INPUT);
}

void loop()
{
    float truthVal = analogRead(signalPin);
    float touchVal = analogRead(touchPin);
    Serial.print("1000,");
    Serial.print(truthVal);
    Serial.print(",");
    Serial.print(touchVal);
    Serial.println();
}