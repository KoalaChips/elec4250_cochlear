#ifndef ELFIELDTOPOWER_H
#define ELFIELDTOPOWER_H

#include <stdint.h>
#include <math.h>

#define LENGTH 300
#define WIDTH 278
#define A_WIDTH 279

void ElFieldToPower(float efData[LENGTH][WIDTH], float normOffset, int8_t nl, float nlExp, float alpha, float audioPwr[LENGTH][A_WIDTH]);



#endif
