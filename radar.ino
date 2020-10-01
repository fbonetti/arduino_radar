#include <Servo.h>
#include <NewPing.h>

#define TRIGGER_PIN  7   // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     7   // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

Servo myservo; // create an object name myservo 

long pos = 0; // variable to store the servo position

void setup() {
  Serial.begin(115200); // starts serial communication at the baud rate of 115200
  myservo.attach(9); // Servo is attached to pin number 9 , you can choose any pin digital pin you want . 
}

void loop() {
  for (pos = 0; pos <= 170; pos += 1) // change the angle of servo from 1 to 170 with the dalay of 15 micro seconds 
  {
    Serial.print(pos);
    Serial.print("|");
    Serial.print(sonar.ping_cm());
    Serial.println();

    myservo.write(pos);
    delay(15);
  } 
  for (pos = 170; pos >= 0; pos -= 1) // changes the angle of servo from 170 to 1 with the delay of 15 micro seconds 
  {
    Serial.print(pos); // prints position/angle of servo on serial monitor 
    Serial.print("|");
    Serial.print(sonar.ping_cm()); // gives us the distance of obstacle in cm 
    Serial.println();

    myservo.write(pos);
    delay(15);// delay of 15 micro seconds , so that every funciton could be performed without any problem 
  }
}
