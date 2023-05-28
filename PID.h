#ifndef PID_h
    #define PID_h

    class PID {
        private:
            double kP = 1.5;
            double kD = 0.1;
            double kI = 0.1;
            double I = 0;
            double D = 0;
            double prevError = 0;
            double errorSum = 0;
            long sampleTime = 300;
            double output = 0;
            unsigned long time = 0;
            
        public:
            PID() {
            }

            PID(double kP, double kD, double kI) {
                this->kP = kP;
                this->kD = kD;
                this->kI = kI;
            }      

            double getKP() {
                return kP;
            }

            double getKD() {
                return kD;
            }

            double getKI() {
                return kI;
            }

            double getD() {
                return D;
            }

            double getI() {
                return I;
            }

            double getPID(double error) {
                if(millis()-time < sampleTime) {
                    return output;
                }

                output = error*kP + errorSum*kI + (error-prevError)/(sampleTime)*kD;
                error = prevError;
                errorSum = max(4000 * -1, min(4000, errorSum));

                time = millis();
                return output;
            }

            void reset() {
                prevError = 0;
                errorSum = 0;
            }

    };

#endif