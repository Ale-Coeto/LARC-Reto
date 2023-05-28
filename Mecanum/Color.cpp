#include "Color.h"
#include "Constants.h"
#include "Arduino.h"

Color::Color() {
}

void Color::start() {
    for (int i = 0; i < 3; i++) {
        averages[FRONT][i] = analogRead(kLineFrontLines[i]);
        averages[BACK][i] = analogRead(kLineBackLines[i]);
        averages[LEFT][i] = analogRead(kLineLeftLines[i]);
        averages[RIGHT][i] = analogRead(kLineRightLines[i]);
    }
  Serial.println("Calibration donde");
}

void Color::checkLines() {
    resetLines();
    for (int i = 0; i < 3; i++) {
        int valF = analogRead(kLineFrontLines[i]);
        int valB = analogRead(kLineBackLines[i]);
        int valR = analogRead(kLineRightLines[i]);
        int valL = analogRead(kLineLeftLines[i]);

        if (averages[FRONT][i] - valF > Constants::colorThreshold) 
            linesDetected[FRONT] = true;
        if (averages[RIGHT][i] - valR > Constants::colorThreshold)
            linesDetected[RIGHT] = true;
        if (averages[LEFT][i] - valL > Constants::colorThreshold)
            linesDetected[LEFT] = true;
        if (averages[BACK][i] - valB > Constants::colorThreshold)
            linesDetected[BACK] = true;
    }
}

void Color::resetLines() {
    for (int i = 0; i < 4; i++) {
        linesDetected[i] = false;
    }
}

bool Color::getDetectionOf(int line) {
    switch(line) {
        case FRONT:
            return linesDetected[FRONT];
            break;
        case BACK:
            return linesDetected[BACK];
            break;
        case RIGHT:
            return linesDetected[RIGHT];
            break;
        case LEFT:
            return linesDetected[LEFT];
            break;
    }
}
int Color::getDetections() {
    checkLines();
    if (linesDetected[FRONT])
        return 180;
    if (linesDetected[BACK])
        return 0;
    if (linesDetected[RIGHT])
        return -90;
    if (linesDetected[LEFT])
        return 90;

    return -1;
}
void Color::printDetections() {
    int valF = 0,valB = 0,valR = 0,valL = 0;
    for (int i = 0; i < 3; i++) {
        valF += analogRead(kLineFrontLines[i]);
        valB += analogRead(kLineBackLines[i]);
        valR += analogRead(kLineRightLines[i]);
        valL += analogRead(kLineLeftLines[i]);
        

        // if (averages[FRONT][i] - valF > 60) 
        //     linesDetected[FRONT] = true;
        // if (averages[RIGHT][i] - valR > 60)
        //     linesDetected[RIGHT] = true;
        // if (averages[LEFT][i] - valL > 60)
        //     linesDetected[LEFT] = true;
        // if (averages[BACK][i] - valB > 60)
        //     linesDetected[BACK] = true;
    }
        Serial.print("Front: ");
        Serial.print(valF/3);
        Serial.print(" \tBack: ");
        Serial.print(valB/3);
        Serial.print(" \tLeft: ");
        Serial.print(valL/3);
        Serial.print(" \tRight: ");
        Serial.println(valR/3);
}