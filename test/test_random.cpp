#include "gaussian.h"
#include <gtest/gtest.h>

TEST(Random, Reproducibility) {
    auto sys1 = GaussianSolver::GenerateRandomSystem(10, 42);
    auto sys2 = GaussianSolver::GenerateRandomSystem(10, 42);
    ASSERT_TRUE(sys1.isApprox(sys2));
}

TEST(Random, ValidSystem) {
    auto system = GaussianSolver::GenerateRandomSystem(100, 123);
    ASSERT_EQ(system.rows(), 100);
    ASSERT_EQ(system.cols(), 101);
}
