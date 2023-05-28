#ifndef Drivetrain_h
  #define Drivetrain_h
    
  #pragma once
  #include "Motor.h"
  #include "Arduino.h"
  
  class Drivetrain {

    private:
      Motor motorFR;
      Motor motorFL;
      Motor motorBR;
      Motor motorBL;
    //   double vx;
    //   double vy;
      double w;
      double x;
      double y;
      double t;
      unsigned long long prevT;
      int xI;
      int yI;

    public:
      Drivetrain(int FRpwm, int FR1, int FR2, int FLpwm, int FL1, int FL2, int BRpwm, int BR1, int BR2, int BLpwm, int BL1, int BL2);
      void setEncoders(int en1, int en2, int s1, int en3, int en4, int s2, int en5, int en6, int s3, int en7, int en8, int s4);
      int getEncoder(int num);
      void callback(int num);
      void resetOdometry();

      void moveToAngle(int angle, int orientation, int speed, double yaw);
      void moveToAngle2(int angle, int orientation, int speed, double yaw);
      void start();

      void setAllSpeeds(int allSpeed);
      void setSpeeds(int v1, int v2, int v3, int v4);

      void stop();
      void rotate(double target, double cur, int speed);
      void test();
      void setInit(double x, double y, double w);
      void encoderValues(double yaw);
      void encoderCallback();
      void pidTest();

      void updateModel(double yaw);
      double getOrientation();

      double getX();
      double getY(); 
  
  };

#endif
