//
// Created by miriam on 6/2/23.
//

#include "measures.h"

// Define energy function
void energy(const std::vector<double>& spins, struct Measures &mis ) {
    double sum_cosines = 0.0;

    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            sum_cosines += cos(spins[i+j*L] - spins[((i + 1) % L)+j*L]) +
                           cos(spins[i+j*L] - spins[i+((j + 1)% L)*L]);
        }
    }
    mis.E= -sum_cosines;
}


// Function to calculate magnetization
double magnetization(const std::vector<double>& spins) {
    double M_x = 0.0, M_y = 0.0;
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            M_x += cos(spins[i+j*L]);
            M_y += sin(spins[i+j*L]);
        }
    }
    M_x /= (N);
    M_y /= (N );
    return M_x * M_x + M_y * M_y;
}