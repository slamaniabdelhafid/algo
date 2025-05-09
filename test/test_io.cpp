#include "gaussian.h"
#include <gtest/gtest.h>

TEST(IO, ReadWriteConsistency) {
    // Use a simpler matrix for testing
    Eigen::MatrixXd original(2, 2);
    original << 1.0, 2.0,
                3.0, 4.0;
    
    GaussianSolver::WriteCSV("test.csv", original);
    auto read = GaussianSolver::ReadCSV("test.csv");
    
    // Use more tolerant comparison for floating-point
    ASSERT_TRUE(original.isApprox(read, 1e-10)) 
        << "Original:\n" << original << "\nRead:\n" << read;
}

TEST(IO, PrecisionHandling) {
    // Test with numbers that need precision
    Eigen::MatrixXd original(1, 3);
    original << 1.23456789, 0.000000001234, 123456789.0;
    
    GaussianSolver::WriteCSV("test_precision.csv", original);
    auto read = GaussianSolver::ReadCSV("test_precision.csv");
    
    ASSERT_TRUE(original.isApprox(read, 1e-10))
        << "Original:\n" << original << "\nRead:\n" << read;
}
