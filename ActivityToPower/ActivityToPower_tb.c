#include <stdio.h>
#include <string.h>
#include <math.h>
#include "ActivityToPower.h"

int compareData(float source[LENGTH][WIDTH], float result[LENGTH][WIDTH]) {
    int noWrong = 0;
    int displayCount = 0;

    for (int i = 0; i < LENGTH; i++) {
       for (int j = 0; j < WIDTH; j++) {
            if (fabsf(source[i][j] - result[i][j]) > 1e-8) {
                noWrong++;
                if (displayCount < 10) {
                    printf("i: [%d]\tj:[%d]\nSource: %.64lf\nResult: %.64lf\nDiff:   %.64lf\n\n", i, j, source[i][j], result[i][j],fabsf(source[i][j] - result[i][j]));
                    displayCount++;
                }
            }
       }
    }

    return noWrong;
}

int readAudioPwrIn(float audioPwrIn[LENGTH][WIDTH]) {
    FILE *fp = fopen("C:\\Uni\\ELEC4250\\project\\ActivityToPower\\audioPwrIn.csv", "r");
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
            audioPwrIn[row][col] = atof(token);
            token = strtok(NULL, ","); 
            col++; 
        }
        row++;
    }

    fclose(fp);
    return row;
}

int readAudioPwrOut(float audioPwrOut[LENGTH][WIDTH]) {
    FILE *fp = fopen("C:\\Uni\\ELEC4250\\project\\ActivityToPower\\audioPwrOut.csv", "r");
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
            audioPwrOut[row][col] = atof(token);
            token = strtok(NULL, ","); 
            col++; 
        }
        row++;
    }

    fclose(fp);
    return row;
}

int readActivityData(float activity[LENGTH][WIDTH]) {
    FILE *fp = fopen("C:\\Uni\\ELEC4250\\project\\ActivityToPower\\activityData.csv", "r");
    if (fp == NULL) {
        perror("Error opening file\n");
        return -1;
    }

    char line[18627]; 
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

int writeAudioPwr(float audioPwrOut[LENGTH][WIDTH]) {
    FILE *fp = fopen("C:\\Uni\\ELEC4250\\project\\ActivityToPower\\audioPwrOutData.csv", "w");
    if (fp == NULL) {
        perror("Error opening file for writing\n");
        return -1;
    }

    for (int row = 0; row < LENGTH; row++) {
        for (int col = 0; col < WIDTH; col++) {
            // Print value, followed by a comma if not the last column
            if (col < WIDTH - 1)
                fprintf(fp, "%.64lf,", audioPwrOut[row][col]);
            else
                fprintf(fp, "%.64lf", audioPwrOut[row][col]);
        }
        fprintf(fp, "\n"); // Move to next line
    }

    fclose(fp);
    return 0;
}

int main (void) {
    float audioPwr[LENGTH][WIDTH];
    readAudioPwrIn(audioPwr);

    float pwrSource[LENGTH][WIDTH];
    readAudioPwrOut(pwrSource);
    
    
    float activity[LENGTH][WIDTH];
    readActivityData(activity);


    float alpha = 0.9982016334024256;

    ActivityToPower(audioPwr, alpha, activity);
    writeAudioPwr(audioPwr);

    int noWrong = compareData(pwrSource, audioPwr);
    if (noWrong == 0) {
        printf("Test Passed!\n");
        return 0;
    } else {
        printf("Test Failed. Count wrong: %d\n", noWrong);
        return 1;
    }
}
