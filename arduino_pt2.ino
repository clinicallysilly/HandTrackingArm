#include <Servo.h>

#define basePin 3
#define armPin 5
#define wristPin 6
#define gripPin 9

// Set up a starting position to run on startup
const int baseStart = 0;
const int armStart = 90;
const int wristStart = 60;
const int gripStart = 110;

Servo baseServo;
Servo armServo;
Servo wristServo;
Servo gripServo;

void moveToAngle(double baseAngle, double armAngle, double wristAngle, double gripAngle) {
  baseServo.write(constrain(baseAngle, 0, 180));
  armServo.write(constrain(armAngle, 0, 180));
  wristServo.write(constrain(wristAngle, 0, 180));
  gripServo.write(constrain(gripAngle, 0, 180));

  Serial.print(baseAngle); Serial.print(", ");
  Serial.print(armAngle); Serial.print(", ");
  Serial.print(wristAngle); Serial.print(", ");
  Serial.println(gripAngle); Serial.print("\n");
}

void setup() {
  Serial.begin(9600);

  baseServo.attach(basePin);
  armServo.attach(armPin);
  wristServo.attach(wristPin);
  gripServo.attach(gripPin);

  // call the function to startup position
  moveToAngle(baseStart, armStart, wristStart, gripStart);
}

void loop() {
  if (Serial.available() > 0) {
    int baseVal = Serial.parseInt();
    int armVal = Serial.parseInt();
    int wristVal = Serial.parseInt();
    int gripVal = Serial.parseInt();

       if (Serial.read() == '\n') {
      baseVal = constrain(baseVal, 0, 180);
      armVal = constrain(armVal, 0, 180);
      wristVal = constrain(wristVal, 0, 180);
      gripVal = constrain(gripVal, 0, 180);

      moveToAngle(baseVal,armVal,wristVal,gripVal);
    }
  }
}

