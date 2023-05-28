// #include <iostream>
// #include <math.h>
// #include <queue>
// using namespace std;
// double const PI = 3.141592653589793;

// double vx = 0;
// double vy = 0;
// double w = 0;

// //pasar -> orientación, angulo al que quiero ir, velocidad, yaw
// // void moveToAngle(int angle, int orientation, int speed, double yaw) {
// //      double rad = angle * PI / 180 + orientation * PI / 180;
// //      //double orientationR = angle * PI / 180;
// //      double vx = cos(rad);
// //      double vy = sin(rad);
// //      double norm = max(abs(vx+vy), abs(vx-vy));
// //      double k = 0.7;
// //      double error = k* (yaw - orientation);

// //      double vFR = speed*(vx - vy)/norm + error;
// //      double vFL = speed*(vx + vy)/norm - error;
// //      double vBR  = speed*(vx + vy)/norm + error;
// //      double vBL = speed*(vx - vy)/norm - error;

// //      cout << vFL << "\t " << vFR << " \n" << vBL << "\t " << vBR << endl;
// // }

// void moveToAngle(int angle, int targetOrientation, int speed, double yaw) {
//      angle = angle - yaw;
//      double rad = angle * PI / 180;
//      //double orientationR = angle * PI / 180;
//      double vx = cos(rad);
//      double vy = sin(rad);
//      double norm = max(abs(vx+vy), abs(vx-vy));
//      double k = 0.7;
//      double error = k* (yaw - targetOrientation);

//      double vFR = speed*(vx - vy)/norm + error;
//      double vFL = speed*(vx + vy)/norm - error;
//      double vBR  = speed*(vx + vy)/norm + error;
//      double vBL = speed*(vx - vy)/norm - error;
//     // cout << (vFL + error) << "\t " << (vFR - error) << " \n" << (vBL + error) << "\t " << (vBR - error) << endl;
//      cout << vFL << "\t " << vFR << " \n" << vBL << "\t " << vBR << endl;
// }



// void kinematics(int angle, int w) {
//     double rad = angle * PI / 180;
//     double vx = cos(rad);
//     double vy = sin(rad);
//     double r = 0.4;
//     int Lx = 10;
//     int Ly = 10;
    
//     double u[3] = {vx,vy,w};
//     int model[4][3] = {{1, -1, -Lx - Ly},
//                        {1, 1, Lx + Ly},
//                        {1, -1, Lx + Ly},
//                        {1, 1, -Lx - Ly}};

//     double ws[4];
//     memset(ws,0,4);

//     for(int i = 0; i < 4; i++) {
//         vx += ws[i] * model[0][i]/4;
//         vy += ws[i] * model[1][i]/4;
//         w += ws[i] * model[2][i]/4;
//     }   

//     cout << ws[3] << " " << ws[0] << " \n" << ws[2]<< " "  << ws[1];
// }

// void updateModel(double v1, double v2, double v3, double v4) { //fr, br, bl, fl
//     int r = 1;
//     int model[3][4] = {{-1, 1, -1, 1},   //vx
//                        {1, 1, 1, 1},     //vy
//                        {-1, -1, 1, 1}};  //w
//                        //FR, BR, BL, FL 

//     int ws[4] = {v1,v2,v3,v4};
//     int res[3] = {0,0,0};

//      for(int i = 0; i < 4; i++) {
//         vx += ws[i] * model[0][i]/4;
//         vy += ws[i] * model[1][i]/4;
//         w += ws[i] * model[2][i]/4;
//     }    
//     //cout << vx << " " << vy << " " << w << endl;
// }

// double getOrientation() {
//     return w;
// }

// double getVx() {
//     return vx;
// }

// double getVy() {
//     return vy;
// }
// int getAngle(int yaw, int offset) {

//   if (offset == 180) {
//     yaw = (yaw > 0) ? (180 - yaw) * -1 : (-180 - yaw) * -1;
//   } else {
//     if (abs(yaw) < 90)
//         yaw = offset + yaw;
//     else
//         if (offset == 90)
//             yaw = (yaw > 0) ? (yaw + offset - 360) : (yaw + offset);
//         else    
//             yaw = (yaw > 0) ? (yaw - 90) : (360 - (yaw + offset));
//   }

//   return yaw;
// }
// int main() {
//     int angle;
//     //cin >> angle;
//     //moveToAngle(0, 0, 200, 90);
//     //pasar -> orientación, angulo al que quiero ir, velocidad, yaw
//     // queue<pair<int,int>> q;

//     cout << getAngle(50,-90);

//     // updateModel(210,210,200,200);
//     // updateModel(100,100,-100,-100);
//     // updateModel(-100,100,-100,100);
//     // cout << getVx() << " " << getVy() << " " << getOrientation() << endl;


//     ////kinematics(0,0);

//     //1 rotar para ver de frente al camino largo
//     return 0;
// }