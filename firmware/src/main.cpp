#include <main.h>
#include <Arduino.h>

ST3215_driver driver(Serial1, DIR_PIN);

void setup()
{
    Serial.begin(115200);  // UART to RPi
    delay(100);

    Serial.println("============================");
    Serial.println("  SpiderGwen ESP32 Firmware ");
    Serial.println("============================");

    Spider::init(driver, coxa_ids, femur_ids, tibia_ids);
    Spider::enable_torque(true);
    delay(500);

    Serial.println("[ READY ] Waiting for commands from RPi...");
}

void loop()
{
    if (Serial.available())
    {
        String line = Serial.readStringUntil('\n');
        line.trim();

        if (line.length() == 0)
            return;

        // ---- STAND command ----
        // Sent once by RPi at startup. ESP32 runs the full stand sequence.
        if (line == "STAND")
        {
            Serial.println("[ STAND ] Starting stand sequence...");
            Spider::stand(500);
            Serial.println("[ STAND ] Complete.");
            return;
        }

        // ---- Leg position command ----
        // Format: L,leg_id,x,y,z
        // RPi sends this every control tick for each leg.
        if (line.startsWith("L,"))
        {
            int   leg_id;
            float x, y, z;
            int parsed = sscanf(line.c_str(), "L,%d,%f,%f,%f",
                                &leg_id, &x, &y, &z);
            if (parsed == 4)
            {
                Spider::set_foot((uint8_t)leg_id, x, y, z);
                Spider::execute_movements(500);
            }
            else
            {
                Serial.println("[ ERROR ] Bad L command — expected L,leg_id,x,y,z");
            }
            return;
        }

        // ---- E-stop ----
        if (line == "ESTOP")
        {
            Spider::estop();
            return;
        }

        // ---- Unknown command ----
        Serial.print("[ WARN ] Unknown command: ");
        Serial.println(line);
    }
}