#include "ElFieldToActivity.h"

// B2
//void ElFieldToActivity(double efData[LENGTH][WIDTH], double normOffset[LENGTH], int64_t nl, double nlExp, double activity[LENGTH][WIDTH]) {
//    outer_i: for (int i = 0; i < LENGTH; i++) {
//        inner_j: for (int j = 1; j < WIDTH; j+=1) {
////#pragma HLS PIPELINE
//
//            if (efData[i][j] == 0) {
//                activity[i][j] = 0.0;
//
//            } else {
//                efData[i][j] -= normOffset[i];
//
//                if (efData[i][j] < 0.0) {
//                    activity[i][j] = 0.0;
//                } else {
//                    activity[i][j] = efData[i][j] * 1.25;
//                }
//
//                double temp = exp(nl * activity[i][j]);
//                if (temp > nlExp) {
//                    temp = nlExp;
//                }
//                temp--;
//
//                if (temp < 0) {
//                    temp = 0;
//                }
//
//                activity[i][j] = temp / (nlExp - 1);
//
//            }
//        }
//    }
//}


// // B3
void ElFieldToActivity(float efData[LENGTH][WIDTH], float normOffset, int8_t nl, float nlExp, float activity[LENGTH][WIDTH]) {
	float recep = 1 / (nlExp - 1);
	float premul = 1.25 * nl;

   outer_i: for (int i = 0; i < LENGTH; i++) {
       inner_j: for (int j = 1; j < WIDTH; j+=2) {
#pragma HLS PIPELINE
       	float v1 = efData[i][j];

           if (v1 == 0.0f) {
               activity[i][j] = 0.0f;

           } else {
           	float v2 = v1 - normOffset;
//                efData[i][j] -= normOffset;


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


// void ElFieldToActivity(float efData[LENGTH*WIDTH], float normOffset, int8_t nl, float nlExp, float activity[LENGTH*WIDTH]) {
// 	float recep = 1 / (nlExp - 1);
// 	float premul = 1.25 * nl;

//     outer_i: for (int i = 1; i < LENGTH*WIDTH; i+=2) {
// #pragma HLS PIPELINE
//         	float v1 = efData[i];

//             if (v1 == 0.0f) {
//                 activity[i] = 0.0f;

//             } else {
//             	float v2 = v1 - normOffset;
// //                efData[i][j] -= normOffset;


//                 if (v2 < 0.0f) {
//                     activity[i] = 0.0f;
//                     continue;
//                 }

//                 float v3 = v2 * premul;


//                 float v4 = expf(v3);
//                 float v5 = v4 - 1;
//                 if (v4 > nlExp) {
//                     v5 = nlExp - 1;
//                 }

//                 if (v5 < 0) {
//                 	activity[i] = 0.0f;
// 					continue;
//                 }

//                 activity[i] = v5 * recep;

//             }
//         }
// //    }
// }


