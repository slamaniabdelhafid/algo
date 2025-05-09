#pragma once
#include <Eigen/Dense>
#include <string>
#include <random>

namespace GaussianSolver {
    using Matrix = Eigen::MatrixXd;
    using Vector = Eigen::VectorXd;

    Matrix ReadCSV(const std::string& filename);
    void WriteCSV(const std::string& filename, const Matrix& data);
    
    Matrix GenerateRandomSystem(int size, unsigned seed);
    
    Vector Solve(const Matrix& A, const Vector& b);
    void PerformRowOperations(Matrix& augmented);
    void BackSubstitution(Matrix& augmented, Vector& x);
}
