#include <AccelStepper.h>

#define TRIGGER_PIN_1 12  // Define the GPIO pin connected to the trigger of sensor 1
#define ECHO_PIN_1 14     // Define the GPIO pin connected to the echo of sensor 1
#define TRIGGER_PIN_2 27  // Define the GPIO pin connected to the trigger of sensor 2
#define ECHO_PIN_2 26     // Define the GPIO pin connected to the echo of sensor 2
#define TRIGGER_PIN_3 25  // Define the GPIO pin connected to the trigger of sensor 3
#define ECHO_PIN_3 33     // Define the GPIO pin connected to the echo of sensor 3
#define TRIGGER_PIN_4 32  // Define the GPIO pin connected to the trigger of sensor 4
#define ECHO_PIN_4 35    // Define the GPIO pin connected to the echo of sensor 4

#define RELAY_PIN 2     // Define the GPIO pin connected to the relay

#define DISTANCE_THRESHOLD 60  // Threshold distance in centimeters
#define STEPS_170_DEGREES 544  // Number of steps for 170 degrees

#define IN1 19  // GPIO pin connected to IN1 on ULN2003 driver
#define IN2 18  // GPIO pin connected to IN2 on ULN2003 driver
#define IN3 5   // GPIO pin connected to IN3 on ULN2003 driver
#define IN4 17  // GPIO pin connected to IN4 on ULN2003 driver

AccelStepper stepper(AccelStepper::FULL4WIRE, IN1, IN3, IN2, IN4);

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  pinMode(TRIGGER_PIN_1, OUTPUT);
  pinMode(ECHO_PIN_1, INPUT);
  pinMode(TRIGGER_PIN_2, OUTPUT);
  pinMode(ECHO_PIN_2, INPUT);
  pinMode(TRIGGER_PIN_3, OUTPUT);
  pinMode(ECHO_PIN_3, INPUT);
  pinMode(TRIGGER_PIN_4, OUTPUT);
  pinMode(ECHO_PIN_4, INPUT);
  pinMode(RELAY_PIN, OUTPUT);

  // Set up the stepper motor
  stepper.setMaxSpeed(1000);  // Set the maximum speed (adjust as needed)
  stepper.setAcceleration(500);  // Set the acceleration (adjust as needed)
}

void loop() {

  // Rotate the stepper motor 170 degrees clockwise
  Serial.println("Rotating 170 degrees clockwise...");
  stepper.moveTo(STEPS_170_DEGREES);
  stepper.runToPosition();
  delay(0);  // Delay before the next rotation

  // Rotate the stepper motor 170 degrees anticlockwise
  Serial.println("Rotating 170 degrees anticlockwise...");
  stepper.moveTo(0);
  stepper.runToPosition();
  delay(0);  // Delay before the next measurement


  // Measure distance for sensor 1
  long duration1, distance1;
  digitalWrite(TRIGGER_PIN_1, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN_1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN_1, LOW);
  duration1 = pulseIn(ECHO_PIN_1, HIGH);
  distance1 = duration1 * 0.034 / 2;

  // Measure distance for sensor 2
  long duration2, distance2;
  digitalWrite(TRIGGER_PIN_2, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN_2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN_2, LOW);
  duration2 = pulseIn(ECHO_PIN_2, HIGH);
  distance2 = duration2 * 0.034 / 2;

  // Measure distance for sensor 3
  long duration3, distance3;
  digitalWrite(TRIGGER_PIN_3, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN_3, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN_3, LOW);
  duration3 = pulseIn(ECHO_PIN_3, HIGH);
  distance3 = duration3 * 0.034 / 2;

  // Measure distance for sensor 4
  long duration4, distance4;
  digitalWrite(TRIGGER_PIN_4, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN_4, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN_4, LOW);
  duration4 = pulseIn(ECHO_PIN_4, HIGH);
  distance4 = duration4 * 0.034 / 2;


  // Print live distances from all sensors
  Serial.print("Distance from sensor 1: ");
  Serial.print(distance1);
  Serial.println(" cm");
  Serial.print("Distance from sensor 2: ");
  Serial.print(distance2);
  Serial.println(" cm");
  Serial.print("Distance from sensor 3: ");
  Serial.print(distance3);
  Serial.println(" cm");
  Serial.print("Distance from sensor 4: ");
  Serial.print(distance4);
  Serial.println(" cm");


  // Check if any distance is less than threshold
  while (distance1 < DISTANCE_THRESHOLD && 
         distance2 < DISTANCE_THRESHOLD && 
         distance3 < DISTANCE_THRESHOLD && 
         distance4 < DISTANCE_THRESHOLD) {
    // If any distance is less than threshold, stop the motor
    stepper.stop();
    Serial.println("Stepper motor stopped");
    digitalWrite(RELAY_PIN, HIGH); // Trigger the relay
    Serial.println("Relay triggered");
    delay(3500); // Keep relay on for 2 seconds
    digitalWrite(RELAY_PIN, LOW); // Turn off the relay


    // Re-measure distances after stopping the motor
    // Measure distance for sensor 1
    digitalWrite(TRIGGER_PIN_1, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER_PIN_1, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN_1, LOW);
    duration1 = pulseIn(ECHO_PIN_1, HIGH);
    distance1 = duration1 * 0.034 / 2;

    // Measure distance for sensor 2
    digitalWrite(TRIGGER_PIN_2, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER_PIN_2, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN_2, LOW);
    duration2 = pulseIn(ECHO_PIN_2, HIGH);
    distance2 = duration2 * 0.034 / 2;

    // Measure distance for sensor 3
    digitalWrite(TRIGGER_PIN_3, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER_PIN_3, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN_3, LOW);
    duration3 = pulseIn(ECHO_PIN_3, HIGH);
    distance3 = duration3 * 0.034 / 2;

    // Measure distance for sensor 4
    digitalWrite(TRIGGER_PIN_4, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER_PIN_4, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN_4, LOW);
    duration4 = pulseIn(ECHO_PIN_4, HIGH);
    distance4 = duration4 * 0.034 / 2;
  }
}
