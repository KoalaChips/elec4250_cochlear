#include "ElFieldToActivity.h"


void ElFieldToActivity(float efData[LENGTH][WIDTH], float normOffset, int8_t nl, float nlExp, float activity[LENGTH][WIDTH]) {
#pragma HLS INTERFACE m_axi port=efData offset=slave bundle=INPUT_AXI
#pragma HLS INTERFACE m_axi port=activity offset=slave bundle=OUTPUT_AXI
#pragma HLS INTERFACE s_axilite port=normOffset bundle=CTRL
#pragma HLS INTERFACE s_axilite port=nl bundle=CTRL
#pragma HLS INTERFACE s_axilite port=nlExp bundle=CTRL
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL

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

