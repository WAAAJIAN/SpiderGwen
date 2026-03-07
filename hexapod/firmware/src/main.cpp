#include <Arduino.h>
#include "ST3215_servo/ST3215_driver.h"

#define SERIAL_BAUD_RATE 1000000
#define SERIAL_BAUD_RATE_DEBUG 115200
#define RX 18
#define TX 17

ST3215_driver *servo_driver;

void setup() 
{
  servo_driver = new ST3215_driver(Serial1);
  Serial1.begin(SERIAL_BAUD_RATE, SERIAL_8N1, RX, TX);
  Serial.begin(SERIAL_BAUD_RATE_DEBUG);

  while (!Serial) 
  {
    ; // wait for serial port to connect. Needed for native USB
  }

  Serial.println("Starting ST3215 servo driver test...");

  for (uint8_t id = 1; id <= 3; id++) 
  {
    uint8_t load;
    size_t speed;
    if (servo_driver->ping(id)) 
    {

      Serial.print("Servo with ID ");
      Serial.print(id);
      Serial.println(" is present.");
      servo_driver->set_speed(id, 300);
      servo_driver->set_angle(id, 180);
      servo_driver->read_load(id, &load);
      servo_driver->read_speed(id, &speed);
      Serial.print("Current load: ");
      Serial.print(load);
      Serial.print(", Current speed: ");
      Serial.println(speed);
    } 
    else
    {
      Serial.print("Servo with ID ");
      Serial.print(id);
      Serial.println(" is not responding.");
    }
  }

}

void loop() {
  for (uint8_t id = 1; id <= 3; id++) 
  {
    servo_driver->set_angle(id, 160);
    delay(1500);                       
    servo_driver->set_angle(id, 200);
    delay(1500);
    servo_driver->set_angle(id, 180);
    delay(1500);
  }
}
