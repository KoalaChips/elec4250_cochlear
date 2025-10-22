#include "ElFieldToPower.h"
#include <hls_stream.h>



void ElFieldToActivity(float efData[LENGTH][WIDTH], float normOffset, int8_t nl, float nlExp, float activity[LENGTH][WIDTH]) {
	float recep = 1 / (nlExp - 1);
	float premul = 1.25 * nl;

    inner_j: for (int j = 1; j < WIDTH; j+=2) {
    	outer_i: for (int i = 0; i < LENGTH; i++) {
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
	#pragma HLS DATAFLOW

    static float activity[LENGTH][WIDTH];
//#pragma HLS RESOURCE variable=activity core=RAM_2P_BRAM
	#pragma HLS STREAM variable=activity depth=512 dim=1

    ElFieldToActivity(efData, normOffset, nl, nlExp, activity);

    ActivityToPower(activity, alpha, audioPwr);
}


