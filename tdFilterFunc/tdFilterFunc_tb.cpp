#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>

#include <math.h>

#include "tdFilterFunc.h"

void readFile(bool fileToggle, double ret[DATA_LENGTH]) {
    std::string filename;

    if (fileToggle) {
        filename = "C:\\Uni\\ELEC4250\\project\\tdFilterFunc\\sig_smp_wavIn_tdFilterFunc.csv";
    } else {
        filename = "C:\\Uni\\ELEC4250\\project\\tdFilterFunc\\sig_smp_wavPre_tdFilterFunc.csv";
    }

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;  
    int index = 0;
    while (std::getline(file, line)) {
        ret[index] = (stod(line));
        index++;
    }

    file.close();
}

void writeFile(double data[DATA_LENGTH]) {
    std::ofstream outputFile("output.csv");
    if (outputFile.is_open()) {
        for (int i = 0; i < DATA_LENGTH; i++) {
            outputFile << std::fixed << std::setprecision(15) << data[i] << std::endl;
        }
        outputFile.close();
    }
}

bool doubleCompare(double a, double b) {
    return std::fabs(a - b) <= 1e-14;
    //return std::fabs(a - b) <= std::numeric_limits<double>::epsilon();
}


int main() {
    std::cout << "tdFilterFunc_tb" << std::endl;

    double *outputSource = new double[DATA_LENGTH];
    double *inputSource = new double[DATA_LENGTH];
    readFile(0, outputSource);
    readFile(1, inputSource);

    double coeffNum[COEFF_LENGTH] = {0.7688, -1.5376, 0.7688};
    double coeffDenom[COEFF_LENGTH] = {1, -1.5299, 0.5453};

    double output [DATA_LENGTH];


    tdFilterFunc(coeffNum, coeffDenom, inputSource, output);
    writeFile(output);

    // TESTING
    // Check output is the correct length
    // if (output.size() != outputSource.size()) {
    //     std::cout << "Output vector is the incorrect size" << std::endl;
    //     return 1;
    // }

    
    // Check values are equal
    int wrongCount = 0;
    std::vector<int> indexes;
    for (int i = 0; i < DATA_LENGTH; i++) {
        if (!doubleCompare(outputSource[i], output[i])) {
            wrongCount++;
            indexes.push_back(i);
        }
    }

    

    if (wrongCount != 0) {
        std::cout << "Values were incorrect: " << wrongCount << std::endl;
        return 1;
    }

    std::cout << "Output is correct and all tests passed!" << std::endl;
    delete[] outputSource;
    delete[] inputSource;
    return 0;
}