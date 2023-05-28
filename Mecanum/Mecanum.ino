#include "BNO.h"
#include "Constants.h"
#include "Drivetrain.h"
#include "Color.h"

//Objects
BNO bno;
Drivetrain drivetrain(8,47,46,7,49,48,9,44,45,6,50,51);
Color lines;

//Variables
int step = 0;
int count = 0;
int distanceX = 0, distanceY = 0;

//Initial values
const int moves = 4;
int path[moves][2] = {{2,1},{2,4},{6,4},{6,5}};

int posInitX = 1, posInitY = 6;
int orientationInit = -90; //-90
int orientFin = -179;

int currentPosition[2] = {posInitY,posInitX}; //5 1

enum t {            //For tests
    LINES = 0,
    MOTORS = 1
};

enum state {        //For state decisions
    MOVE,
    START,
    FORWARD,
    BACKWARD,
    RIGHTMOVE,
    LEFTMOVE,
    STOP,
    TEST
};

state current;

//Setup
void setup () {
    Serial.begin(9600);
    start();
 
}

//Loop
void loop () {

    current = START; //STATE

    //Update sensor value
    updateValues();

    //Check if it needs to move
    if (current == START) {
        if (step >= moves) 
            current = STOP;
        else {
            current = MOVE;
        }
    }


    //Movements according to current and target positions
    if (current == MOVE) {
        distanceX = path[step][1] - currentPosition[1]; //Units to move in X
        distanceY = path[step][0] - currentPosition[0]; //Units to move in Y

        if (abs(distanceY) > 0) //Move in Y
            (distanceY > 0) ? movement(BACKWARD, abs(distanceY)) :  movement(FORWARD, abs(distanceY));
        
        else if (abs(distanceX) > 0)  //Move in X
            (distanceX > 0) ? movement(RIGHTMOVE, abs(distanceX)) : movement(LEFTMOVE, abs(distanceX));

        else 
            current = STOP;
    }


    //Stop when finished
    if (current == STOP) {
        //End correctly oriented
        drivetrain.rotate(orientFin, bno.getYaw(), Constants::speeds);
    }


    //For tests
    if (current == TEST) {
        tests(MOTORS);
    }


    //Print status
    Serial.print(currentPosition[0]);
    Serial.print("\t");
    Serial.println(currentPosition[1]);

    

}


//Move to a given direction for a given distance
void movement(int direction, int distance) {

    switch (direction){
        case FORWARD:
                
            if (drivetrain.getY() < Constants::disV*distance*2) {
                    drivetrain.moveToAngle(0, 0, Constants::speeds, bno.getYaw());
                
            } else {
                count = distance;
                drivetrain.resetOdometry();
            }

        break;
        
        case BACKWARD:
            if (drivetrain.getY() > - Constants::disV*distance*2) {
                    drivetrain.moveToAngle(180, 0, Constants::speeds, bno.getYaw());
            } else {
                count = distance;
                drivetrain.resetOdometry();
            }
        break;

        case RIGHTMOVE:
            
            if (drivetrain.getX() < Constants::disH*distance*2) {
                if (distance > 3)
                    drivetrain.moveToAngle(90, 90, Constants::speeds, bno.getYaw());
                else
                    drivetrain.moveToAngle(90, 0, Constants::speeds, bno.getYaw());
            } else {
                count = distance;
                drivetrain.resetOdometry();
            }
        break;

        case LEFTMOVE:
            if (drivetrain.getX() > -Constants::disH*distance*2) {
                if (distance > 2)
                    drivetrain.moveToAngle(-90, -90, Constants::speeds, bno.getYaw());
                else
                    drivetrain.moveToAngle(-90, 0, Constants::speeds, bno.getYaw());
            } else {
                count = distance;
                drivetrain.resetOdometry();
            }
        break;
    }
    
    if (count == distance) {
        currentPosition[0] = path[step][0];
        currentPosition[1] = path[step][1];
        step++;
        count = 0;

        int l = lines.getDetections();

        if (l != -1) {
            long long time = millis();
            while (millis() - time < 180)
            drivetrain.moveToAngle(l, 0, Constants::speeds - 20, bno.getYaw());
        }
        
        Serial.println("DONE");
        lines.resetLines();
        drivetrain.resetOdometry();
        long long time = millis();

    }

   
}


//Object setup
void start() {
    bno.start();
    drivetrain.start();
    drivetrain.setEncoders(18,17,1,2,5,1,19,16,-1,3,4,1);
    //drivetrain.setInit(posInitX,posInitY,0);
    bno.setOffset(orientationInit);
    lines.start();
    initEncoders();
    updateValues();
    delay(500);
}


//Update values once the loop begins again
void updateValues() {
    bno.readValues();
    drivetrain.updateModel(bno.getYaw());
}


//Encoders
void initEncoders() {
  attachInterrupt(digitalPinToInterrupt(drivetrain.getEncoder(1)), encoderCallbackFR, RISING);
  attachInterrupt(digitalPinToInterrupt(drivetrain.getEncoder(2)), encoderCallbackFL, RISING);
  attachInterrupt(digitalPinToInterrupt(drivetrain.getEncoder(3)), encoderCallbackBR, RISING);
  attachInterrupt(digitalPinToInterrupt(drivetrain.getEncoder(4)), encoderCallbackBL, RISING);

}

void encoderCallbackFR() {
    drivetrain.callback(1);
}

void encoderCallbackFL() {
    drivetrain.callback(2);
}

void encoderCallbackBR() {
    drivetrain.callback(3);
}

void encoderCallbackBL() {
    drivetrain.callback(4);
}

int getOrientation() {
    bno.readValues();
    double yaw = bno.getYaw();
    if (yaw > -10 && yaw < 10) return 0;
    else if (yaw > 80 && yaw < 110) return 90;
    else if (yaw > 170 || yaw < -110) return 180;
    else if (yaw > -100 && yaw < -80) return -90;
}
//Tests
void tests(int test) {
    switch (test) {
    case LINES:
        lines.printDetections();
        break;
    
    case MOTORS:
        drivetrain.pidTest();
        //drivetrain.test();
        break;
    }
    
}