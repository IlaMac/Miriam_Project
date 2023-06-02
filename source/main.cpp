//
// Created by ilaria on 2023-05-26.
//

#include "main.h"
#include "measures.h"

// Initialize random spin directions
std::vector<double> spins;
size_t L, N, n_steps;
double T;
// Function to generate random double between min and max
double randomDouble(double min, double max) {
    return min + (max - min) * (double)rand() / RAND_MAX;
}

int main(int argc, char *argv[]) {
    //srand(time(NULL));
    srand(static_cast<unsigned int>(time(NULL)));

    L= static_cast<size_t>(std::atoi(argv[1]));
    n_steps= static_cast<size_t>(std::atoi(argv[2]));
    T=std::atof(argv[3]);
    N=L*L;
    spins.resize(N);
    std::cout<< L << std::endl;
    std::cout<< n_steps << std::endl;
    std::cout<< T << std::endl;
    // Initialize random spin directions
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            spins[i+j*L] = randomDouble(0, 2 * M_PI);
        }
    }

    //Create an output file in order to write the results
    std::ofstream outputFile ("/home/miriam/KTH/Miriam_Project/Output/results.txt");

    // Check if the file is opened successfully
    if (!outputFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }
    // Run simulation --->> void mainloop()
    double thetabox = M_PI/4.;
    std::vector<double> magnetization_values;
    double acc_ideal = 0.5;
    double acc;
    Measures mis;

    for (size_t step = 0; step < n_steps; step++) {
        int acc_rate = 0;
        for (size_t n_up = 0; n_up < N; n_up++) {
            mc_step(spins, T, acc_rate, thetabox);
        }

        //std::cout<<spins[0]<<std::endl;
        mis.reset();
        energy(spins, mis);
        std::cout<<mis.E<<std::endl;
        outputFile << step << " " << mis.E << std::endl;

//        energies.push_back(energy(spins));
//        magnetization_values.push_back(magnetization(spins));

//        acc = (acc_rate) / ((double)N);
//        double new_dthetabox = 2*thetabox*(0.5 * (acc / acc_ideal));
//        thetabox+=new_dthetabox;
//        thetabox/=2.;
//        std::cout <<  (0.5 * (acc / acc_ideal)) << " " << thetabox << " "<< new_dthetabox<< std::endl;
    }

    //Close the file
    outputFile.close();

    return 0;
}

// Define Monte Carlo step
void mc_step(std::vector<double> & spins, double T, int &acc, double thetabox) {
    int i = rand() % L;
    int j = rand() % L;
    double d_spin = randomDouble(-thetabox, thetabox);
    std::vector<double> spins_new = spins;
    spins_new[i+j*L] += d_spin;
    double delta_e = local_energy(spins_new) - local_energy(spins); //make a local energy function
    if (delta_e < 0) {
        spins[i+j*L] = spins_new[i+j*L] ;
        acc += 1;
    } else {
        if (exp(-delta_e / T) > randomDouble(0, 1)) {
            spins[i+j*L] = spins_new[i+j*L] ;
            acc += 1;
        }
    }
}

double local_energy(const std::vector<double>& spins) {
    double sum_cosines = 0.0;

    for (size_t i = 0; i < L; i++) {
        for (size_t j = 0; j < L; j++) {
            sum_cosines += cos(spins[i+j*L] - spins[((i + 1) % L)+j*L]) +
                           cos(spins[i+j*L] - spins[i+((j + 1)% L)*L]);
        }
    }
    return -sum_cosines;
}


