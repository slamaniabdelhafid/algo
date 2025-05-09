#include "gaussian.h"
#include <gtest/gtest.h>

TEST(Solver, SimpleSystem) {
    Eigen::MatrixXd A(2, 2);
    A << 2, 1, 
         1, 1;
    Eigen::VectorXd b(2);
    b << 3, 2;
    
    auto x = GaussianSolver::Solve(A, b);
    Eigen::VectorXd expected(2);
    expected << 1, 1;
    
    ASSERT_TRUE(x.isApprox(expected, 1e-8));
}

TEST(Solver, RandomSystem) {
    auto system = GaussianSolver::GenerateRandomSystem(10, 42);
    Eigen::MatrixXd A = system.leftCols(10);
    Eigen::VectorXd b = system.rightCols(1);
    Eigen::VectorXd x = GaussianSolver::Solve(A, b);
    
    Eigen::VectorXd computed_b = A * x;
    ASSERT_TRUE(computed_b.isApprox(b, 1e-6));
}
