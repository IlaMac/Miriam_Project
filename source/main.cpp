//
// Created by ilaria on 2023-05-26.
//

#include "main.h"

// Initialize random spin directions
std::vector<std::vector<double>> spins(N, std::vector<double>(N));

// Function to generate random double between min and max
double randomDouble(double min, double max) {
    return min + (max - min) * (double)rand() / RAND_MAX;
}

// Define energy function
double energy(const std::vector<std::vector<double>>& spins) {
    double sum_cosines = 0.0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            sum_cosines += cos(spins[i][j] - spins[(i + 1) % N][j]) +
                           cos(spins[i][j] - spins[i][(j + 1) % N]);
        }
    }
    return -sum_cosines;
}

// Define Monte Carlo step
std::pair<std::vector<std::vector<double>>, int> mc_step(const std::vector<std::vector<double>>& spins,
                                                         double T, int acc, double thetabox) {
    int i = rand() % N;
    int j = rand() % N;
    double d_spin = randomDouble(-thetabox, thetabox);
    std::vector<std::vector<double>> spins_new = spins;
    spins_new[i][j] += d_spin;
    double delta_e = energy(spins_new) - energy(spins);
    if (delta_e < 0) {
        spins_new[i][j] = spins[i][j] + d_spin;
        acc += 1;
    } else {
        if (exp(-delta_e / T) > randomDouble(0, 1)) {
            spins_new[i][j] = spins[i][j] + d_spin;
            acc += 1;
        }
    }
    return std::make_pair(spins_new, acc);
}

// Function to calculate magnetization
double magnetization(const std::vector<std::vector<double>>& spins) {
    double M_x = 0.0, M_y = 0.0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            M_x += cos(spins[i][j]);
            M_y += sin(spins[i][j]);
        }
    }
    M_x /= (N * N);
    M_y /= (N * N);
    return M_x * M_x + M_y * M_y;
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    int L;
    L=std::atoi(argv[1]);
    std::cout<< L << std::endl;
    // Initialize random spin directions
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            spins[i][j] = randomDouble(0, 2 * M_PI);
        }
    }

    // Run simulation
    std::vector<double> energies;
    std::vector<double> magnetization;
    double acc_ideal = 0.5;
    for (int step = 0; step < n_steps; step++) {
        int acc_rate = 0;
        for (int n_up = 0; n_up < N * N; n_up++) {
            std::pair<std::vector<std::vector<double>>, int> result = mc_step(spins, T, acc_rate, thetabox);
            spins = result.first;
            acc_rate = result.second;
        }
        energies.push_back(energy(spins));
        //magnetization.push_back(magnetization(spins));
        //double acc = static_cast<double>(acc_rate) / (N * N);
        //thetabox = thetabox * (0.5 + 0.5 * (acc / acc_ideal));
        //std::cout << acc << " " << thetabox << std::endl;
    }

    // No plot

    return 0;
}
