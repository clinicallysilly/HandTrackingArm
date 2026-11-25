#include <Servo.h>

#define basePin 3
#define armPin 5
#define wristPin 6
#define gripPin 9

const int baseStart = 0;
const int armStart = 90;
const int wristStart = 60;
const int gripStart = 110;

// Geometry Constants
const double depth = 10.0;
const double arm = 11.0;
const double y_max = sqrt(4*arm*arm - depth*depth);

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

// Create a new function that turns a y value into 2 motor angles
void moveToPos(double x, double y, double grip) {
  double l = sqrt(depth*depth + y*y);
  double phi = atan2(y, depth) * (180/PI);
  double ratio = constrain(0.5*l/arm, -1.0, 1.0);
  double theta = acos(ratio) * (180/PI);

  // Be sure to check the direction and offset for these servos
  double baseAngle = x;
  double armAngle = 180 - (phi + theta);
  double wristAngle = 60 + (phi - theta);

  moveToAngle(baseAngle, armAngle, wristAngle, grip);
}

void setup() {
  Serial.begin(9600);

  baseServo.attach(basePin);
  armServo.attach(armPin);
  wristServo.attach(wristPin);
  gripServo.attach(gripPin);

  moveToAngle(baseStart, armStart, wristStart, gripStart);
}

void loop() {
  if (Serial.available() > 0) {
    // Parse for the x and y position instead of the absolute servo angles
    int baseVal = Serial.parseInt();
    int yVal = Serial.parseInt();
    int gripVal = Serial.parseInt();

    if (Serial.read() == '\n') {
      // Constrain the variables to the correct limits
      baseVal = constrain(baseVal, 0, 180);
      yVal = constrain(yVal, 0, y_max);
      gripVal = constrain(gripVal, 0, 180);

      // Call the position function instead of the angles
      moveToPos(baseVal,yVal,gripVal);
    }
  }
}
