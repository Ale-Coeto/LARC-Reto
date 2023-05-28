#ifndef Color_h
    #define Color_h
    #include "Arduino.h"

    class Color {
        private:
            // Order: Middle, Front, Back
            int kLineFrontLines[3] = {A7, A8, A9};
            int kLineBackLines[3] = {A4, A5, A6};
            int kLineLeftLines[3] = {A13, A14, A15};
            int kLineRightLines[3] = {A10, A11, A12};
            int averages[4][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0 ,0 ,0}};
            bool linesDetected[4] = {false, false, false, false}; //f,b,l,r
           

        public:
            Color();
            void start();
            void checkLines();
            void resetLines();
            bool getDetectionOf(int line);
            int getDetections();
            void printDetections();

    };

    enum Line {
                FRONT = 0,
                BACK = 1,
                LEFT = 2,
                RIGHT = 3
    };

#endif