//
// Created by ilaria on 2023-05-26.
//

#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <cstdlib>
#include <ctime>
#include<fstream>

// Define simulation parameters

extern size_t L;            // Number of spins in each dimension
extern size_t N;
extern size_t n_steps;   // Number of simulation steps
extern double T;        // Temperature
void mc_step(std::vector<double> & spins, double T, int &acc, double thetabox);
double local_energy(const std::vector<double> & spins);


