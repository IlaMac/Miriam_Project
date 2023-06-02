//
// Created by miriam on 6/2/23.
//

#ifndef XY_MODEL_MEASURES_H
#define XY_MODEL_MEASURES_H

#include "main.h"

struct Measures {
    double E=0;
    double M=0;

    void reset(){
        *this = Measures();
    }
};

double magnetization(const std::vector<double>& spins);
void energy(const std::vector<double>& spins, struct Measures &mis );


#endif //XY_MODEL_MEASURES_H
