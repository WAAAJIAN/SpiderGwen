#include "main.h"

ST3215_driver *servo_driver = nullptr;

void setup()
{
    Serial.begin(SERIAL_BAUD_RATE_DEBUG);
    uint32_t t = millis();
    while (!Serial && (millis() - t) < 3000)
        ;

    servo_driver = new ST3215_driver(Serial1);

    // TODO: init other peripherals

    // TODO: start threads
}

void loop()
{
    // TODO: control loop
}
