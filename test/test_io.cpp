#include "gaussian.h"
#include <gtest/gtest.h>

TEST(IO, ReadWriteConsistency) {
    Eigen::MatrixXd original = Eigen::MatrixXd::Random(5, 5);
    GaussianSolver::WriteCSV("test.csv", original);
    auto read = GaussianSolver::ReadCSV("test.csv");
    ASSERT_TRUE(original.isApprox(read));
}
