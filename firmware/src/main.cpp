#include <main.h>
#include <Arduino.h>

ST3215_driver driver(Serial1, DIR_PIN);

void setup()
{
    Serial.begin(115200);
    delay(100);

    Serial.println("============================");
    Serial.println("  Spider Single Leg Test");
    Serial.println("============================");

    // initialise spider with single leg
    Spider::init(driver, coxa_ids, femur_ids, tibia_ids);

    // enable torque (ensure no limping leg)
    Spider::enable_torque(true);
    delay(500);

    // move to standing position
    Serial.println("[ STANDING ]");
    Spider::stand(1000);
    delay(2000);
}

void loop()
{

}