#include <Servo.h>
#include <NewPing.h>

#define TRIGGER_PIN  7   // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     7   // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

Servo myservo;

long pos = 0; // variable to store the servo position

void setup() {
  Serial.begin(115200);
  myservo.attach(9);
}

void loop() {
  for (pos = 0; pos <= 170; pos += 1)
  {
    Serial.print(pos);
    Serial.print("|");
    Serial.print(sonar.ping_cm());
    Serial.println();

    myservo.write(pos);
    delay(15);
  }
  for (pos = 170; pos >= 0; pos -= 1)
  {
    Serial.print(pos);
    Serial.print("|");
    Serial.print(sonar.ping_cm());
    Serial.println();

    myservo.write(pos);
    delay(15);
  }
}
