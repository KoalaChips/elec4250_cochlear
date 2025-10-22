#include "ElFieldToPower.h"



void ElFieldToActivity(float efData[LENGTH][WIDTH], float normOffset, int8_t nl, float nlExp, float activity[LENGTH][WIDTH]) {
	float recep = 1 / (nlExp - 1);
	float premul = 1.25 * nl;

   outer_i: for (int i = 0; i < LENGTH; i++) {
       inner_j: for (int j = 1; j < WIDTH; j+=2) {
#pragma HLS PIPELINE II=1
       	float v1 = efData[i][j];

           if (v1 == 0.0f) {
               activity[i][j] = 0.0f;

           } else {
           	float v2 = v1 - normOffset;

               if (v2 < 0.0f) {
                   activity[i][j] = 0.0f;
                   continue;
               }

               float v3 = v2 * premul;


               float v4 = expf(v3);
               float v5 = v4 - 1;
               if (v4 > nlExp) {
                   v5 = nlExp - 1;
               }

               if (v5 < 0) {
               	activity[i][j] = 0.0f;
					continue;
               }

               activity[i][j] = v5 * recep;

           }
       }
   }
}



void ActivityToPower(float activity[LENGTH][WIDTH], float alpha, float audioPwr[LENGTH][A_WIDTH]) {
	float inv = 1 - alpha;

	for (int j = 1; j <= A_WIDTH; j++) {
		for (int i = 0; i < LENGTH; i++) {
#pragma HLS PIPELINE

			if (j != A_WIDTH) {
				float pwr = audioPwr[i][j-1];
				float act = activity[i][j-1];
				float val = pwr * alpha + act * inv;

				if (val > act) {
					audioPwr[i][j] = val;
				} else {
					audioPwr[i][j] = act;
				}
			} else {
				audioPwr[i][0] = audioPwr[i][A_WIDTH - 1];
			}
        }
    }
}









void ElFieldToPower(float efData[LENGTH][WIDTH], float normOffset, int8_t nl, float nlExp, float alpha, float audioPwr[LENGTH][A_WIDTH]) {
//	#pragma HLS DATAFLOW

    float activity[LENGTH][WIDTH];
//	#pragma HLS STREAM variable=activity depth=512 dim=1

    // Stage 1: Compute activity values for all efData
    ElFieldToActivity(efData, normOffset, nl, nlExp, activity);

    // Stage 2: Compute smoothed power from activity
    ActivityToPower(activity, alpha, audioPwr);
}













//double exp_hls(float x) {
//#pragma HLS INLINE
//
//
//	return 1.0f + x + 0.5f * x * x;

//    double sum = 1.0;   // start with 1 (the 0th term)
//    double term = 1.0;  // term_n = x^n / n!
//
//    taylor:for (int n = 1; n < 15; n++) { // 20 terms gives decent precision
//        term *= x / n;
//        sum += term;
//    }
//    return sum;
//}


//void ElFieldToPower(float efData[LENGTH][WIDTH], float normOffset, int8_t nl, float nlExp, float alpha, float audioPwr[LENGTH][A_WIDTH]) {
//
//    float activity = 0.0;
//    outer_i: for (int i = 0; i < LENGTH; i++) {
//        inner_j: for (int j = 0; j < A_WIDTH; j++) {
//#pragma HLS PIPELINE II=13
//
//
//            // Convert the Activity to Power
//            if (j != 0) {
//                float audioPwrVal = audioPwr[i][j - 1] * alpha + activity * (1 - alpha);
//                if (audioPwrVal > activity) {
//                    audioPwr[i][j] = audioPwrVal;
//                } else {
//                    audioPwr[i][j] = activity;
//                }
//            }
//
//
//            // Convert the Electric Field to Activity
//            activity = 0.0;
//            if (j != A_WIDTH - 1) {
//
//                if (efData[i][j] != 0) {
//                    efData[i][j] -= normOffset;
//
//                    if (efData[i][j] > 0.0) {
//                        activity = efData[i][j] * 1.25;
//                    }
//
//                    float temp = expf(nl * activity);
//                    if (temp > nlExp) {
//                        temp = nlExp;
//                    }
//                    temp--;
//
//                    if (temp < 0) {
//                        temp = 0;
//                    }
//
//                    activity = temp / (nlExp - 1);
//                }
//            }
//
//        }
//        audioPwr[i][0] = audioPwr[i][A_WIDTH-1];
//    }
//}


//void ElFieldToPower(float efData[LENGTH][WIDTH], float normOffset, int8_t nl, float nlExp, float alpha, float audioPwr[LENGTH][A_WIDTH]) {
//
//	//float activity[LENGTH][WIDTH];
//
//    float activity = 0.0;
//    outer_i: for (int i = 0; i < LENGTH; i++) {
//        inner_j: for (int j = 0; j < A_WIDTH; j++) {
////#pragma HLS PIPELINE II=11
//
//
//            // Convert the Activity to Power
//            if (j != 0) {
//                float audioPwrVal = audioPwr[i][j - 1] * alpha + activity * (1 - alpha);
//                if (audioPwrVal > activity) {
//                    audioPwr[i][j] = audioPwrVal;
//                } else {
//                    audioPwr[i][j] = activity;
//                }
//            }
//
//
//            // Convert the Electric Field to Activity
//            activity = 0.0;
//            if (j != A_WIDTH - 1) {
//            	float v1 = efData[i][j];
//                if (v1 != 0) {
//
//
//                	// Line 1: efData = (efData-normOffset)
//                	v1 -= normOffset;
//
//
//                	// Line 2: electricField = np.maximum(0,efData)
//                	// Line 3: electricField = electricField / 0.4 * 0.5
//					float v2;
//                    if (v1 > 0.0) {
//                    	v2 = v1 * 1.25;
//                    }
//
//
//
//                    float v3 = exp(nl * v2);
//                    if (v3 > nlExp) {
//                    	v3 = nlExp;
//                    }
//                    float v4 = v3 - 1.0f;
//
//                    if (v4 < 0) {
//                        v4 = 0;
//                    }
//
//                    activity = v4 / (nlExp - 1);
//                }
//            }
//
//        }
//        audioPwr[i][0] = audioPwr[i][A_WIDTH-1];
//    }
//}
