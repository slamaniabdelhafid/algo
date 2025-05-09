#include "gaussian.h"
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input.csv> <output.csv>\n";
        return 1;
    }

    try {
        auto system = GaussianSolver::ReadCSV(argv[1]);
        auto A = system.leftCols(system.cols() - 1);
        auto b = system.rightCols(1);
        
        auto x = GaussianSolver::Solve(A, b);
        GaussianSolver::WriteCSV(argv[2], x);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
