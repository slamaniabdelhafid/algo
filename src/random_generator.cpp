#include "gaussian.h"
#include <random>

namespace GaussianSolver {
    Matrix GenerateRandomSystem(int size, unsigned seed) {
        std::mt19937_64 gen(seed);
        std::uniform_real_distribution<double> dist(-10.0, 10.0);
        
        Matrix system(size, size + 1);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size + 1; ++j) {
                system(i, j) = dist(gen);
            }
        }
        return system;
    }
}
