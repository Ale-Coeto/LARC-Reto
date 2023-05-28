#ifndef Motor_h
  #define Motor_h
  #include "PID.h"
  #pragma once
  
  class Motor {
    private:
      int pwmPin;
      int pin1;
      int pin2;
      int encA;
      int encB;
      double encValue = 0;
      int encDir = 1;
      int sign = 1;

      long long prevTime = 0;
      double speed = 0;
      double displacement = 0;

      double prevValue = 0;
      double pwm = 0;
      PID pid;
      int direction = 1;
      long long curTime = 0;
      long sampleTime = 100;

  
    public:

      Motor();
      void set(int pwmPin, int pin1, int pin2);
      void setEncoders(int encA, int encB, int sign);
      void startMotor();
      void forward();
      void backward();
      void stop();
      int getPwmPin();
      double getSpeed();
      void setPwm(int speed);
      void setPwm2(int speed);
      int getPin1();
      int getPin2();
      double getEncA();
      double getEncB();
      double getEncValue();
      void encoderCallback();
      void startEncoders();
      void resetEncoders();
      double getDisplacement();
      void setDir(int dir);
      void setValue(double val);
      double getValue();
      int getDir();
      double getPwm();
      void moveMotor();
          
  };

#endif
