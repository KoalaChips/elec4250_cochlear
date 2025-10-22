#ifndef ELFIELDTOACTIVITY_H
#define ELFIELDTOACTIVITY_H

#include <stdint.h>
#include <math.h>

#define LENGTH 300
#define WIDTH 278

// void ElFieldToActivity(double efData[LENGTH][WIDTH], double normOffset[LENGTH], int64_t nl, double nlExp, double activity[LENGTH][WIDTH]);
void ElFieldToActivity(float efData[LENGTH][WIDTH], float normOffset, int8_t nl, float nlExp, float activity[LENGTH][WIDTH]);


#endif
