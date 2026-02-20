#include <Arduino.h>
#include "ST3215_driver.h"

#define SERIAL_BAUD_RATE 1000000
#define SERIAL_BAUD_RATE_DEBUG 115200
#define RX 18
#define TX 17

ST3215_driver servo_driver(Serial1);

void setup() {
    Serial1.begin(SERIAL_BAUD_RATE, SERIAL_8N1, RX, TX);
    Serial.begin(SERIAL_BAUD_RATE_DEBUG);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB
    }

    Serial.println("Starting ST3215 servo driver test...");
    
}

void loop() {
    bool anyResponding = false;

    if (servo_driver.ping(1))
    {
        Serial.println("Servo with ID 1 is present.");
        anyResponding = true;
    } 
    if (servo_driver.ping(2))
    {
        Serial.println("Servo with ID 2 is present.");
        anyResponding = true;
    } 
    if (servo_driver.ping(3))
    {
        Serial.println("Servo with ID 3 is present.");
        anyResponding = true;
    }

    if (!anyResponding)
    {
        Serial.println("No servos are responding.");
    }

    delay(500); // repeat every 500ms
}