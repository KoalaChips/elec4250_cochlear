#include <stdio.h>
#include <string.h>
#include <math.h>
#include "ElFieldToActivity.h"

int compareData(float source[LENGTH][WIDTH], float result[LENGTH][WIDTH]) {
   int noWrong = 0;
   int displayCount = 0;

   for (int i = 0; i < LENGTH; i++) {
       for (int j = 0; j < WIDTH; j++) {
           if (fabs(source[i][j] - result[i][j]) > 1e-8) {
               noWrong++;
               if (displayCount < 10) {
                   printf("Source: %.64lf\nResult: %.64lf\nDiff:   %.64lf\n\n", source[i][j], result[i][j],fabs(source[i][j] - result[i][j]));
                   displayCount++;
               }
           }
       }
   }

   return noWrong;
}

int readEfData(float efData[LENGTH][WIDTH]) {
   FILE *fp = fopen("C:\\Uni\\ELEC4250\\project\\ElFieldToActivity\\efData.csv", "r");
   if (fp == NULL) {
       perror("Error opening file\n");
       return -1;
   }

   char line[19000];
   int row = 0;
   int col = 0;
   char *token;

   while (fgets(line, sizeof(line), fp) && row < LENGTH) {
       token = strtok(line, ",");
       col = 0;
       while (token != NULL) {
           efData[row][col] = atof(token);
           token = strtok(NULL, ",");
           col++;
       }
       row++;
   }

   fclose(fp);
   return row;
}

int readActivityData(float activity[LENGTH][WIDTH]) {
   FILE *fp = fopen("C:\\Uni\\ELEC4250\\project\\ElFieldToActivity\\activity.csv", "r");
   if (fp == NULL) {
       perror("Error opening file\n");
       return -1;
   }

   char line[19000];
   int row = 0;
   int col = 0;
   char *token;

   while (fgets(line, sizeof(line), fp) && row < LENGTH) {
       token = strtok(line, ",");
       col = 0;
       while (token != NULL) {
           activity[row][col] = atof(token);
           token = strtok(NULL, ",");
           col++;
       }
       row++;
   }

   fclose(fp);
   return row;
}

int writeActivity(float activity[LENGTH][WIDTH]) {
    FILE *fp = fopen("C:\\Uni\\ELEC4250\\project\\ElFieldToActivity\\activityData.csv", "w");
    if (fp == NULL) {
        perror("Error opening file for writing\n");
        return -1;
    }

    for (int row = 0; row < LENGTH; row++) {
        for (int col = 0; col < WIDTH; col++) {
            // Print value, followed by a comma if not the last column
            if (col < WIDTH - 1)
                fprintf(fp, "%.64lf,", activity[row][col]);
            else
                fprintf(fp, "%.64lf", activity[row][col]);
        }
        fprintf(fp, "\n"); // Move to next line
    }

    fclose(fp);
    return 0;
}



int main (void) {
    printf("\nRunning Elfield to Activity conversion\n\n");
    float efData[LENGTH][WIDTH];
    readEfData(efData);
    // printf("%f\n", efData[160][275]);

    float sourceActivity[LENGTH][WIDTH];
    readActivityData(sourceActivity);
    // printf("%f\n", sourceActivity[200][217]);


    float activity[LENGTH][WIDTH];
    int8_t nl = 5;
    float nlExp = 148.4131591025766;
	float normOffset = 0.090909090909090911614;

    ElFieldToActivity(efData, normOffset, nl, nlExp, activity);
    writeActivity(activity);

    int noWrong = compareData(sourceActivity, activity);
    if (noWrong == 0) {
        printf("Test Passed!\n");
        return 0;
    } else {
        printf("Test Failed. Count wrong: %d\n", noWrong);
        return 1;
    }
}
