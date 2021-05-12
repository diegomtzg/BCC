#define PERIOD 1000

int outputPin = 8;

long lastTime = 0;

int byteLength = 8;
int currBit = byteLength - 1;
bool nextBit;

// 8 bit identifiers
char id = 'A'; // TODO: Change id as necessary

void setup()
{
    Serial.begin(9600);

    pinMode(outputPin, OUTPUT);

    lastTime = millis();
}

void loop()
{

    // Update bit being sent once every second.
    if (millis() - lastTime > PERIOD)
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
