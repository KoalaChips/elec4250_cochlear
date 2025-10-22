#ifndef ACTIVITYTOPOWER_H
#define ACTIVITYTOPOWER_H

#include <stdint.h>
#include <math.h>

#define LENGTH 300
#define WIDTH 279


void ActivityToPower(float audioPwr[LENGTH][WIDTH], float alpha, float activity[LENGTH][WIDTH]);


#endif
