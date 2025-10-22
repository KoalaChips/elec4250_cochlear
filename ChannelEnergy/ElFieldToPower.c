#include "ElFieldToPower.h"

//double exp_hls(double x) {
//    double sum = 1.0;   // start with 1 (the 0th term)
//    double term = 1.0;  // term_n = x^n / n!
//
//    taylor:for (int n = 1; n < 15; n++) { // 20 terms gives decent precision
//        term *= x / n;
//        sum += term;
//    }
//    return sum;
//}


void ElFieldToPower(float efData[LENGTH][WIDTH], float normOffset, int8_t nl, float nlExp, float alpha, float audioPwr[LENGTH][A_WIDTH]) {

    float activity = 0.0;
    outer_i: for (int i = 0; i < LENGTH; i++) {
        inner_j: for (int j = 0; j < A_WIDTH; j++) {
		#pragma HLS PIPELINE II=10

            // Convert the Activity to Power
            if (j != 0) {
                float audioPwrVal = audioPwr[i][j - 1] * alpha + activity * (1 - alpha);
                if (audioPwrVal > activity) {
                    audioPwr[i][j] = audioPwrVal;
                } else {
                    audioPwr[i][j] = activity;
                }
            }
            

            // Convert the Electric Field to Activity
            activity = 0.0;
            if (j != A_WIDTH - 1) {
                if (efData[i][j] != 0) {
                    efData[i][j] -= normOffset;

                    if (efData[i][j] > 0.0) {
                        activity = efData[i][j] * 1.25;
                    }

                    float temp = exp(nl * activity);
                    if (temp > nlExp) {
                        temp = nlExp;
                    }
                    temp--;

                    if (temp < 0) {
                        temp = 0;
                    }

                    activity = temp / (nlExp - 1);
                }
            }
            
        }
        audioPwr[i][0] = audioPwr[i][A_WIDTH-1];
    }
}
