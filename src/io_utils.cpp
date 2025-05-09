#include "gaussian.h"
#include <fstream>
#include <sstream>

namespace GaussianSolver {
    Matrix ReadCSV(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) throw std::runtime_error("Cannot open file: " + filename);

        std::vector<std::vector<double>> data;
        std::string line;
        
        while (std::getline(file, line)) {
            std::vector<double> row;
            std::stringstream ss(line);
            std::string cell;
            
            while (std::getline(ss, cell, ',')) {
                row.push_back(std::stod(cell));
            }
            data.push_back(row);
        }

        Matrix mat(data.size(), data[0].size());
        for (int i = 0; i < data.size(); ++i) {
            mat.row(i) = Eigen::VectorXd::Map(&data[i][0], data[i].size());
        }

        return mat;
    }

    void WriteCSV(const std::string& filename, const Matrix& data) {
        std::ofstream file(filename);
        if (!file) throw std::runtime_error("Cannot open file: " + filename);
        
        for (int i = 0; i < data.rows(); ++i) {
            for (int j = 0; j < data.cols(); ++j) {
                file << data(i, j);
                if (j < data.cols() - 1) file << ",";
            }
            file << "\n";
        }
    }
}
