int outputPin = D7;
int inputPin = A4;

long lastTime = 0;
long period = 1000;

int byteLength = 8;
int currBit = byteLength - 1;
bool nextBit;

// 8 bit identifiers
char id = 0;

void setup()
{
    Serial.begin(9600);

    pinMode(outputPin, OUTPUT);

    lastTime = millis();
}

void loop()
{
    // digitalWrite(outputPin, state);
    // float val = analogRead(inputPin);
    // Serial.println(val);
    // delay(1000/freq);
    // Serial.println(nextBit);

    // Update bit being sent once every second.
    if (millis() - lastTime > period)
    {
        char mask = 1 << currBit;
        currBit--;

        nextBit = id & mask;
        Serial.print(nextBit);

        // Finished sending byte, reset for next byte.
        if (currBit < 0)
        {
            currBit = byteLength - 1;
            Serial.println();

            id++;
        }

        lastTime = millis();
    }
}