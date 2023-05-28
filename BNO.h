#ifndef BNO_h
  #define BNO_h
  
  #include <Wire.h>
  #include <Adafruit_Sensor.h>
  #include <Adafruit_BNO055.h>
  #include <utility/imumaths.h>
  
  class BNO {
    private:
      double yaw;
      bool right = true;
      Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire);
      double offset = 0;

    public:

      BNO();
      void start();
      void readValues();
      double getYaw();
      void setOffset(double off);
      bool isRight();
      void readValues2();
      void displayCalStatus();
      void iniciar2();
  };

#endif