int signalPin = A0;
int touchPin = A1;

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
    Serial.println("1000,%f,%f", truthVal, touchVal);
}