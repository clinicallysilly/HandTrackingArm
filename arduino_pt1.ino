// Including the servo library
#include <Servo.h>


// Set your pins to the right servos
#define basePin 3
#define armPin 5
#define wristPin 6
#define gripPin 9


// Declaring each servo with a different name
Servo baseServo;
Servo armServo;
Servo wristServo;
Servo gripServo;

// Making a function that lets you move all 4 servos with one command
void moveToAngle(double baseAngle, double armAngle, double wristAngle, double gripAngle) {
  baseServo.write(constrain(baseAngle, 0, 180)); // constrain() keeps the values within the safe limits of the motor in case you accidentally type a bigger number or send bad data
  armServo.write(constrain(armAngle, 0, 180));
  wristServo.write(constrain(wristAngle, 0, 180));
  gripServo.write(constrain(gripAngle, 0, 180));

  // output the angles to the serial monitor for debugging
  Serial.print(baseAngle); Serial.print(", ");
  Serial.print(armAngle); Serial.print(", ");
  Serial.print(wristAngle); Serial.print(", ");
  Serial.println(gripAngle); Serial.print("\n");
}

// setup() runs once when you upload the code
void setup() {
  Serial.begin(9600); // establish a connection with the serial monitor

  // attach all of the servos to their respective pins
  baseServo.attach(basePin);
  armServo.attach(armPin);
  wristServo.attach(wristPin);
  gripServo.attach(gripPin);
}

// loop runs continuously until you unplug the arduino
void loop() {
  if (Serial.available() > 0) {
    // Each of these commands searches for the next integer that hasn't already been found, so the first number it sees will be the baseVal and so on
    int baseVal = Serial.parseInt();
    int armVal = Serial.parseInt();
    int wristVal = Serial.parseInt();
    int gripVal = Serial.parseInt();


    // \n is a newline character, which we are defining as the end of a command
    if (Serial.read() == '\n') {
      // again constraining our values for safety
      baseVal = constrain(baseVal, 0, 180);
      armVal = constrain(armVal, 0, 180);
      wristVal = constrain(wristVal, 0, 180);
      gripVal = constrain(gripVal, 0, 180);


      // After defining our function, we have to call it, so we do that here when the serial monitor detects a new line
      moveToAngle(baseVal,armVal,wristVal,gripVal);
    }
  }
}
