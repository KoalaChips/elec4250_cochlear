#include "tdFilterFunc.h"



void tdFilterFunc(double b[COEFF_LENGTH], double a[COEFF_LENGTH], double x[DATA_LENGTH], double y[DATA_LENGTH]) {
    double d0 = 0.0;
    double d1 = 0.0;

    

    main_loop:for (int i = 0; i < DATA_LENGTH - 1; i++) {
        y[i] = b[0] * x[i] + d0;

        d0 = b[1] * x[i] - a[1] * y[i] + d1;
        d1 = b[2] * x[i] - a[2] * y[i];
    }
}
