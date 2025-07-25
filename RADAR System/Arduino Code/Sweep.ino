#include <Servo.h>

// Ultrasonic Sensor Pins
const int trig = 6;
const int echo = 7;

// Distance Measurement Variables
long duration;
int distance;

// Servo Setup
Servo myservo;
int pos = 0; // variable to store servo position

void setup() {
  // Ultrasonic Sensor Setup
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);

  // Servo Setup
  myservo.attach(12); // Attach servo to pin 12
}

// Function to calculate distance from ultrasonic sensor
int calculateDistance() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}
void loop() {
  for (pos = 15; pos <= 165; pos++) {
    myservo.write(pos);
    delay(20);

    distance = calculateDistance();
    
    // Send angle and distance via Serial in format: angle,distance
    Serial.print(pos);
    Serial.print(",");
    Serial.println(distance);
    Serial.print(".");
  }

  for (pos = 165; pos >= 15; pos--) {
    myservo.write(pos);
    delay(20);

    distance = calculateDistance();

    // Send angle and distance via Serial
    Serial.print(pos);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
  }
}
