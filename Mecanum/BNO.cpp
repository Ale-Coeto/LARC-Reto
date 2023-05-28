#include "Arduino.h"
#include "BNO.h"

BNO::BNO() {
}

void BNO::start() {
  if (!bno.begin(OPERATION_MODE_IMUPLUS)) {
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }

  //NUevo
  bno.setExtCrystalUse(true);
}

void BNO::iniciar2() {
  if (!bno.begin(OPERATION_MODE_NDOF_FMC_OFF)) {
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }

  bno.setExtCrystalUse(true);
}


void BNO::readValues() {
  sensors_event_t event;
  bno.getEvent(&event);

  yaw = (double)event.orientation.x;
  yaw = (yaw > 180) ? -1 * (360 - yaw) : yaw;

  //Set offset
  if (offset == 180) {
    yaw = (yaw > 0) ? (180 - yaw) * -1 : (-180 - yaw) * -1;
  } else if (offset != 0) {
    if (abs(yaw) < 90)
        yaw = offset + yaw;
    else
        if (offset == 90)
            yaw = (yaw > 0) ? (yaw + offset - 360) : (yaw + offset);
        else    
            yaw = (yaw > 0) ? (yaw - 90) : (360 - (yaw + offset));
  }

  right = (yaw < 0) ? true : false;

}

void BNO::displayCalStatus()
{

  uint8_t system, gyro, accel, mag;
  system = gyro = accel = mag = 0;
  bno.getCalibration(&system, &gyro, &accel, &mag);

   Serial.print("\t");
    Serial.print("Sys:");
    Serial.print(system, DEC);
    Serial.print(" G:");
    Serial.print(gyro, DEC);
    Serial.print(" A:");
    Serial.print(accel, DEC);
    Serial.print(" M:");
    Serial.println(mag, DEC);
}


double BNO::getYaw() {
  return yaw;
}

void BNO::setOffset(double off) {
  offset = off;
}

bool BNO::isRight() {
  return right;
}