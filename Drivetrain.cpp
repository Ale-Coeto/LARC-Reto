#include "Arduino.h"
#include "Drivetrain.h"
#include "Constants.h"


Drivetrain::Drivetrain(int FRpwm, int FR1, int FR2, int FLpwm, int FL1, int FL2, int BRpwm, int BR1, int BR2, int BLpwm, int BL1, int BL2) {
  motorFR.set(FRpwm, FR1, FR2);
  motorFL.set(FLpwm, FL1, FL2);
  motorBR.set(BRpwm, BR1, BR2);
  motorBL.set(BLpwm, BL1, BL2);

}

void Drivetrain::setEncoders(int en1, int en2, int s1, int en3, int en4, int s2, int en5, int en6, int s3, int en7, int en8, int s4) {
    motorFR.setEncoders(en1, en2, s1);
    motorFL.setEncoders(en3, en4, s2);
    motorBR.setEncoders(en5, en6, s3);
    motorBL.setEncoders(en7, en8, s4);
}

int Drivetrain::getEncoder(int num) {
    switch(num) {
        case 1:
            return motorFR.getEncA();
        case 2:
            return motorFL.getEncA();
        case 3:
            return motorBR.getEncA();
        case 4:
            return motorBL.getEncA();
    }
}

void Drivetrain::callback(int num) {
    switch(num) {
        case 1:
            motorFR.encoderCallback();
            break;
        case 2:
            motorFL.encoderCallback();
            break;
        case 3:
            motorBR.encoderCallback();
            break;
        case 4:
            motorBL.encoderCallback();
            break;
    }
}


void Drivetrain::start() {
  motorFR.startMotor();
  motorFL.startMotor();
  motorBR.startMotor();
  motorBL.startMotor();
}

void Drivetrain::resetOdometry() {
    x = 0;
    y = 0;
    motorFR.resetEncoders();
    motorFL.resetEncoders();
    motorBL.resetEncoders();
    motorBR.resetEncoders();

}

void Drivetrain::moveToAngle(int angle, int targetOrientation, int speed, double yaw) {
     angle = angle - yaw;
     double rad = angle * PI / 180;
     double vx = cos(rad);
     double vy = sin(rad);
     double norm = max(abs(vx+vy), abs(vx-vy));
     double k = Constants::kMovement;
     double error = k* (yaw - targetOrientation);

     int vFR = (speed*(vx - vy)/norm + error);
     int vFL = (speed*(vx + vy)/norm - error);
     int vBR  = (speed*(vx + vy)/norm + error);
     int vBL = (speed*(vx - vy)/norm - error);

     setSpeeds(vFR, vFL, vBR, vBL);

    if (vFR > 0)  motorFR.forward();
    else  motorFR.backward();
    
    if (vFL > 0)  motorFL.forward();
    else  motorFL.backward();

    if (vBR > 0)  motorBR.forward();
    else  motorBR.backward();

    if (vBL > 0)  motorBL.forward();
    else  motorBL.backward();

}


void Drivetrain::rotate(double target, double cur, int speed) {
  
  double k = Constants::kRotation;
  double error = (target - cur)*k;
  speed = min(255,abs(error));

  setAllSpeeds(speed);
  Serial.print(cur);
  Serial.print("\t");
  Serial.println(error);

  if (abs(target-cur) < 3) {
    stop();
  } else if (error < 0) {
    motorFR.forward();
    motorFL.backward();
    motorBR.forward();
    motorBL.backward();
  } else {
    motorFR.backward();
    motorFL.forward();
    motorBR.backward();
    motorBL.forward();
  }

}

void Drivetrain::updateModel(double yaw) {
    double v1 = motorFR.getDisplacement();
    double v2 = motorBR.getDisplacement();
    double v3 = motorBL.getDisplacement();
    double v4 = motorFL.getDisplacement();

    int r = 1;
    int model[3][4] = {{-1, 1, -1, 1},   //vx
                       {1, 1, 1, 1},     //vy
                       {-1, -1, 1, 1}};  //w
                       //FR, BR, BL, FL 

    double ws[4] = {v1,v2,v3,v4};
    int res[3] = {0,0,0};
    double xR = 0;
    double yR = 0;
    double wR = 0;

     for(int i = 0; i < 4; i++) {
        xR += ws[i] * model[0][i];
        yR += ws[i] * model[1][i];
        wR += ws[i] * model[2][i];
    }    

    xR /= 4;
    yR /= 4;
    wR /= 4;

    if (yaw > -45 && yaw < 45) yaw = 0;
    else if (yaw >= 45 && yaw < 135) yaw =  PI * 1 / 2;
    else if (yaw >= 135 || yaw < -135) yaw = PI;
    else yaw = - PI * 1 / 2;

    x = xR * cos(yaw) + yR * sin(yaw);
    y = xR * sin(yaw) + yR * cos(yaw);
   
}

double Drivetrain::getX() {
    return x + xI;
}

double Drivetrain::getY() {
    return y + yI;
}

double Drivetrain::getOrientation() {
    return w;
}

void Drivetrain::setInit(double x, double y, double w) {
    xI = x*30-30;
    yI = y*30-30;
    this -> w = w;
}

void Drivetrain::setSpeeds(int v1, int v2, int v3, int v4) { 
    v1 = min(abs(v1),255);
    v2 = min(abs(v2),255);
    v3 = min(abs(v3),255);
    v4 = min(abs(v4),255);

    motorFR.setPwm(v1);
    motorFL.setPwm(v2);
    motorBR.setPwm(v3);
    motorBL.setPwm(v4);
}



void Drivetrain::setAllSpeeds(int allSpeed) {
  motorFR.setPwm(allSpeed);
  motorFL.setPwm(allSpeed);
  motorBR.setPwm(allSpeed);
  motorBL.setPwm(allSpeed);

}

void Drivetrain::stop() {
  motorFR.stop();
  motorFL.stop();
  motorBR.stop();
  motorBL.stop();
}

void Drivetrain::test() {
    motorFR.forward();
    delay(500);
    motorFL.forward();
    delay(500);
    motorBR.forward();
    delay(500);
    motorBL.forward();
}

void Drivetrain::encoderValues(double yaw) {
    Serial.print("\tFR ");
    Serial.print(motorFR.getDisplacement());
    Serial.print("\tFL ");
    Serial.print(motorFL.getDisplacement());
    Serial.print("\t BR");
    Serial.print(motorBR.getDisplacement());
    Serial.print("\t BL");
    Serial.print(motorBL.getDisplacement());
    Serial.print("\t X ");
    Serial.print(x);
    Serial.print("\t\t Y ");
    Serial.print(y);
    Serial.print("\t\t YAW ");
    Serial.println(yaw);


}

void Drivetrain::pidTest() {
    motorBR.setPwm2(150);
    motorBR.moveMotor();
}


// void Drivetrain::moveToAngle2(int angle, int targetOrientation, int speed, double yaw) {
//      angle = angle - yaw;
//      double rad = angle * PI / 180;
//      //double orientationR = angle * PI / 180;
//      double vx = cos(rad);
//      double vy = sin(rad);
//      double norm = max(abs(vx+vy), abs(vx-vy));
//      double k = Constants::kMovement;
//      double error = k* (yaw - targetOrientation);

//      int vFR = (speed*(vx - vy)/norm + error);
//      int vFL = (speed*(vx + vy)/norm - error);
//      int vBR  = (speed*(vx + vy)/norm + error);
//      int vBL = (speed*(vx - vy)/norm - error);

//      setSpeeds2(vFR, vFL, vBR, vBL);
//     // cout << (vFL + error) << "\t " << (vFR - error) << " \n" << (vBL + error) << "\t " << (vBR - error) << endl;
//     // cout << vFL << "\t " << vFR << " \n" << vBL << "\t " << vBR << endl;

//     if (vFR > 0)  motorFR.setDir(1);
//     else  motorFR.setDir(-1);
    
//     if (vFL > 0)  motorFL.forward();
//     else  motorFL.backward();

//     if (vBR > 0)  motorBR.forward();
//     else  motorBR.backward();

//     if (vBL > 0)  motorBL.forward();
//     else  motorBL.backward();

//     motorFR.moveMotor();
//     motorFL.moveMotor();
//     motorBR.moveMotor();
//     motorBL.moveMotor();

// }