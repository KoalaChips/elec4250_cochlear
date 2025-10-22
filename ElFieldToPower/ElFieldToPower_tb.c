#include <stdio.h>
#include <string.h>
#include "ElFieldToPower.h"

int compareData(float source[LENGTH][A_WIDTH], float result[LENGTH][A_WIDTH]) {
    int noWrong = 0;
    int displayCount = 0;

    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < A_WIDTH; j++) {
            if (fabsf(source[i][j] - result[i][j]) > 1e-7) {
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

int compareActivityData(float source[LENGTH][WIDTH], float result[LENGTH][WIDTH]) {
    int noWrong = 0;
    int displayCount = 0;

    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (fabsf(source[i][j] - result[i][j]) > 1e-7) {
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

int readEfData(float efData[LENGTH][WIDTH]) {
    FILE *fp = fopen("C:\\Uni\\ELEC4250\\project\\ElFieldToPower\\efData.csv", "r");
    if (fp == NULL) {
        perror("Error opening file (EfData)\n");
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

int readAudioPwrOut(float audioPwrOut[LENGTH][A_WIDTH]) {
    FILE *fp = fopen("C:\\Uni\\ELEC4250\\project\\ElFieldToPower\\audioPwrOut.csv", "r");
    if (fp == NULL) {
        perror("Error opening file (Audio Power Out)\n");
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

int readAudioPwrIn(float audioPwrIn[LENGTH][A_WIDTH]) {
    FILE *fp = fopen("C:\\Uni\\ELEC4250\\project\\ElFieldToPower\\audioPwrIn.csv", "r");
    if (fp == NULL) {
        perror("Error opening file (Audio Power In)\n");
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

int writeAudioPwr(float audioPwrOut[LENGTH][A_WIDTH]) {
    FILE *fp = fopen("C:\\Uni\\ELEC4250\\project\\ElFieldToPower\\audioPwrOutData.csv", "w");
    if (fp == NULL) {
        perror("Error opening file for writing\n");
        return -1;
    }

    for (int row = 0; row < LENGTH; row++) {
        for (int col = 0; col < WIDTH; col++) {
            // Print value, followed by a comma if not the last column
            if (col < A_WIDTH - 1)
                fprintf(fp, "%.64lf,", audioPwrOut[row][col]);
            else
                fprintf(fp, "%.64lf", audioPwrOut[row][col]);
        }
        fprintf(fp, "\n"); // Move to next line
    }

    fclose(fp);
    return 0;
}

int readActivityData(float activity[LENGTH][WIDTH]) {
    FILE *fp = fopen("C:\\Uni\\ELEC4250\\project\\ElFieldToPower\\activity.csv", "r");
    if (fp == NULL) {
        perror("Error opening file (Activity)\n");
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

int writeActivity(float activity[LENGTH][WIDTH]) {
    FILE *fp = fopen("C:\\Uni\\ELEC4250\\project\\ElFieldToPower\\activityData.csv", "w");
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
    printf("\nRunning Elfield to Power conversion\n\n");
    float efData[LENGTH][WIDTH];
    if (readEfData(efData) == -1) {
        return 1;
    }
    
    float audioPwr[LENGTH][A_WIDTH];
    if (readAudioPwrIn(audioPwr) == -1) {
        return 1;
    }

    float audioPwrSource[LENGTH][A_WIDTH];
    if (readAudioPwrOut(audioPwrSource) == -1) {
        return 1;
    }

    float activitySource[LENGTH][WIDTH];
    if (readActivityData(activitySource) == -1) {
        return 1;
    }

    float normOffset = 0.0909090909090909116141432377844466827809810638427734375000000000;
    int64_t nl = 5;
    float nlExp = 148.4131591025766;
    float alpha = 0.9982016334024256;

    //float activity[LENGTH][WIDTH];

    ElFieldToPower(efData, normOffset, nl, nlExp, alpha, audioPwr);
    // printf("Source: %.64lf\nResult: %.64lf\n\n", audioPwrOutSource[6][6], audioPwr[6][6]);
    writeAudioPwr(audioPwr);
    // writeActivity(activity);

    int noWrong = compareData(audioPwrSource, audioPwr);
    if (noWrong == 0) {
        printf("Test Passed!\n");
        return 0;
    } else {
        printf("Test Failed. Count wrong: %d\n", noWrong);
        return 1;
    }
}
