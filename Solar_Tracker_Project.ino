#include <Servo.h>

Servo horizontal; // Horizontal Servo
int servohori = 180;
int servohoriLimitHigh = 175;
int servohoriLimitLow = 5;

Servo vertical; // Vertical Servo
int servovert = 90;
int servovertLimitHigh = 100;
int servovertLimitLow = 1;

// LDR connections
int ldrlt = A0; // Left Top / Bottom Left depending on physical setup
int ldrld = A1;
int ldrrd = A2;
int ldrrt = A3;

void setup() {
  horizontal.attach(2);
  vertical.attach(13);

  horizontal.write(180);
  vertical.write(45);

  delay(2500);
}

void loop() {

  int lt = analogRead(ldrlt);
  int rt = analogRead(ldrrt);
  int ld = analogRead(ldrld);
  int rd = analogRead(ldrrd);

  int dtime = 10;
  int tol = 30;

  // Average light readings
  int avt = (lt + rt) / 2; // Top
  int avd = (ld + rd) / 2; // Bottom
  int avl = (lt + ld) / 2; // Left
  int avr = (rt + rd) / 2; // Right

  // Difference between sides
  int dvert = avt - avd;
  int dhoriz = avl - avr;

  // VERTICAL MOVEMENT
  if (abs(dvert) > tol) {

    if (avt > avd) {
      servovert++;

      if (servovert > servovertLimitHigh) {
        servovert = servovertLimitHigh;
      }

    } else {
      servovert--;

      if (servovert < servovertLimitLow) {
        servovert = servovertLimitLow;
      }
    }

    vertical.write(servovert);
  }

  // HORIZONTAL MOVEMENT
  if (abs(dhoriz) > tol) {

    if (avl > avr) {
      servohori--;

      if (servohori < servohoriLimitLow) {
        servohori = servohoriLimitLow;
      }

    } else {
      servohori++;

      if (servohori > servohoriLimitHigh) {
        servohori = servohoriLimitHigh;
      }
    }

    horizontal.write(servohori);
  }

  delay(dtime);
}
