int outputPin = D7;

long lastTime = 0;
long period = 1000;

int byteLength = 8;
int currBit = byteLength - 1;
bool nextBit;

// 8 bit identifiers
char id = 0b0101010;

void setup()
{
    Serial.begin(9600);

    pinMode(outputPin, OUTPUT);

    lastTime = millis();
}

void loop()
{

    // Update bit being sent once every second.
    if (millis() - lastTime > period)
    {
        char mask = 1 << currBit;
        currBit--;

        nextBit = (bool)(id & mask);
        digitalWrite(outputPin, nextBit);

        // Finished sending byte, reset for next byte.
        if (currBit < 0)
        {
            currBit = byteLength - 1;
        }

        lastTime = millis();
    }
}