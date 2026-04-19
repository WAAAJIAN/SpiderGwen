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

// the code in this loop is a simplified version to receive foot position commands from the serial monitor and execute them
// commands should be in the format: L,leg,x,y,z
// commands are sent over from RPI through UART
void loop()
{
    if (Serial.available())
    {
        String line = Serial.readStringUntil('\n');
        line.trim();

        // Expected: L,leg,x,y,z
        if (line.startsWith("L"))
        {
            int leg;
            float x, y, z;

            int parsed = sscanf(line.c_str(), "L,%d,%f,%f,%f", &leg, &x, &y, &z);

            if (parsed == 4)
            {
                Spider::set_foot(leg, x, y, z);
                Spider::execute_movements(500); // speed
            }
            else
            {
                Serial.println("Parse error");
            }
        }
    }
}