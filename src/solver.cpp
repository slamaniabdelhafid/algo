#include "gaussian.h"

namespace GaussianSolver {
    Vector Solve(const Matrix& A, const Vector& b) {
        Matrix augmented(A.rows(), A.cols() + 1);
        augmented << A, b;
        
        PerformRowOperations(augmented);
        
        Vector x(A.cols());
        BackSubstitution(augmented, x);
        
        return x;
    }

    void PerformRowOperations(Matrix& augmented) {
        for (int col = 0; col < augmented.cols() - 1; ++col) {
            // Partial pivoting
            int max_row = col;
            for (int row = col + 1; row < augmented.rows(); ++row) {
                if (augmented.row(row).lpNorm<Eigen::Infinity>() > 
                    augmented.row(max_row).lpNorm<Eigen::Infinity>()) {
                    max_row = row;
                }
            }
            augmented.row(col).swap(augmented.row(max_row));
            
            // Vectorized elimination
            for (int row = col + 1; row < augmented.rows(); ++row) {
                double factor = augmented(row, col) / augmented(col, col);
                augmented.row(row) -= factor * augmented.row(col);
            }
        }
    }

    void BackSubstitution(Matrix& augmented, Vector& x) {
        for (int row = augmented.rows() - 1; row >= 0; --row) {
            x(row) = augmented(row, augmented.cols() - 1);
            for (int col = row + 1; col < augmented.cols() - 1; ++col) {
                x(row) -= augmented(row, col) * x(col);
            }
            x(row) /= augmented(row, row);
        }
    }
}
