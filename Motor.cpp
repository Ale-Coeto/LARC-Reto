#include "Arduino.h"
#include "Motor.h"
#include "Constants.h"
#include "math.h"

Motor::Motor() {};

//Set
void Motor::set(int pwm, int pin1, int pin2) {
  this-> pwmPin = pwm;
  this-> pin1 = pin1;
  this-> pin2 = pin2;
}

void Motor::startMotor() {
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(encA, INPUT);
  pinMode(encB, INPUT);

}

void Motor::setEncoders(int encA, int encB, int sign) {
  this -> encA = encA;
  this -> encB = encB;
  this -> sign = sign;
}

void Motor::forward() {
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
  pid.reset();
}

void Motor::backward() {
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
  pid.reset();
}

void Motor::stop() {
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
}

//Getters
int Motor::getPwmPin() {
  return pwmPin;
}

void Motor::setPwm(int target) {
  analogWrite(pwmPin, target);
}

void Motor::setPwm2(int targetPwm) {
    double error = targetPwm - getSpeed();
    pwm = pid.getPID(error);
    
    pwm = min(255,max(fabs(pwm), 0));
    direction = (int)(error > 0) ? 1*sign : -1*sign;
    analogWrite(pwmPin, pwm);

    Serial.print("PWM: ");
    Serial.println(pwm);
    Serial.print("Speed: ");
    Serial.print(speed);
    Serial.print("\t");
    
}

void Motor::moveMotor() {
    (direction > 0) ? forward() : backward();
}

int Motor::getPin1() {
  return pin1;
}

int Motor::getPin2() {
  return pin2;
}

double Motor::getPwm() {
  return pwm;
}

double Motor::getEncA() {
    return encA;
}

double Motor::getEncB() {
    return encB;
}

void Motor::encoderCallback() {
  encDir = (int)(digitalRead(encB) == HIGH ? 1*sign : -1*sign);
  if (encDir == 1) {
    encValue++;
  } else {
    encValue--;
  }
 // encValue += encDir;
} 



void Motor::resetEncoders() {
  encValue = 0;
}

double Motor::getDisplacement() {
    displacement = (encValue/Constants::kPulsesPerRevolution) * Constants::wheelDiameter * PI;
    return displacement;
}

double Motor::getSpeed() {
    if(millis()-prevTime < sampleTime) {
        return speed;
    }

    double time = (millis() - prevTime);
    double change = encValue - prevValue;
    speed = change/time;
    speed *= 1000;
    speed *= Constants::wheelDiameter * PI /(Constants::kPulsesPerRevolution);
    prevValue = encValue;

    prevTime = millis();

    return speed;
}

void Motor::setDir(int direction) {
    encDir = direction;
}

void Motor::setValue(double val) {
    encValue = val;
}   

double Motor::getValue() {
    return encValue;
}

int Motor::getDir() {
    return encDir;
}