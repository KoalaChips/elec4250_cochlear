#include "ActivityToPower.h"

//void ActivityToPower(float audioPwr[LENGTH][WIDTH], float alpha, float activity[LENGTH][WIDTH]) {
//	float inv = 1 - alpha;
//
//    for (int i = 0; i < LENGTH; i++) {
//        for (int j = 1; j < WIDTH; j++) {
////			#pragma HLS PIPELINE
//        	float pwr = audioPwr[i][j-1];
//        	float act = activity[i][j-1];
//            float val = pwr * alpha + act * inv;
//
//            if (val > act) {
//                audioPwr[i][j] = val;
//            } else {
//                audioPwr[i][j] = act;
//            }
//        }
//        audioPwr[i][0] = audioPwr[i][WIDTH - 1];
//    }
//}


void ActivityToPower(float audioPwr[LENGTH][WIDTH], float alpha, float activity[LENGTH][WIDTH]) {
	float inv = 1 - alpha;

	for (int j = 1; j <= WIDTH; j++) {
		for (int i = 0; i < LENGTH; i++) {
#pragma HLS PIPELINE

			if (j != WIDTH) {
				float pwr = audioPwr[i][j-1];
				float act = activity[i][j-1];
				float val = pwr * alpha + act * inv;

				if (val > act) {
					audioPwr[i][j] = val;
				} else {
					audioPwr[i][j] = act;
				}
			} else {
				audioPwr[i][0] = audioPwr[i][WIDTH - 1];
			}
        }
    }

//	for (int i = 0; i < LENGTH; i++) {
//#pragma HLS PIPELINE
//
//	}
}
