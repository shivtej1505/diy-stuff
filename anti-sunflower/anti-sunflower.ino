#include <Servo.h>

Servo antiSunFlower;
int servoPin = 13;
int angle = 0;

void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);

  Serial.begin(9600);

  antiSunFlower.attach(servoPin);
  antiSunFlower.write(angle);
}

void loop() {
  int left, right, center;
  left = analogRead(A0);
  center = analogRead(A1);
  right = analogRead(A2);

  //Serial.println(left);
  //Serial.println(center);
  //Serial.println(right);
  //Serial.println("-----");

  delay(1000);

  angle = getAngle(left, center, right, angle);
  // wrote this angle to servo
  Serial.println(angle);
  antiSunFlower.write(angle);
}

int getAngle(int left, int center, int right, int currAngle) {
  left = map(left, 0, 1023, 0, 100);
  center = map(center, 0, 1023, 0, 100);
  right = map(right, 0, 1023, 0, 100);
  
  int tmp = max(left, max(center, right));
  
  if (tmp == left) {
    if (left-center <= 10){
      return 150;
    }
    return 180;
  } else if (tmp == center) {
    if (center-left <= 10){
      return 120;
    } else if (center-right <= 10){
      return 60;
    }
    return 90;
  } else if (tmp == right) {
    if (right-center <= 10){
      return 30;
    }
    return 0;
  }
}

