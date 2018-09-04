#ifndef MAC_DETERMINANTE_HPP
#define MAC_DETERMINANTE_HPP

#include <vector>	
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <armadillo>

namespace mac {

    using namespace std;

    using Matrix = arma::mat;

    double determinante2x2(const Matrix& mat) {
        if (!mat.is_square() && (mat.n_rows == 2UL))
            throw logic_error("Matrix is not 2x2!");
            
        return mat(0UL, 0UL) * mat(1UL, 1UL) - mat(0UL, 1UL) * mat(1UL, 0UL);
    }

    double determinante(const Matrix& mat) {
        if (!mat.is_square())
            throw logic_error("Matrix is not square!");
            
        auto n = mat.n_rows;

        if (n == 2UL) 
            return determinante2x2(mat);
        
        double result = 0;
        Matrix new_mat = Matrix(n - 1UL, n - 1UL);

        for (auto k = 0UL; k < n; ++k) {
            for (auto i = 1UL; i < n; ++i) {
                for (auto j = 0UL; j < n; ++j) {
                    if (k == j) continue;
                    
                    new_mat(i - 1, j < k? j : j - 1) = mat(i, j);
                }
            }

            result += pow(-1, k) * mat(0, k) * determinante(new_mat);				
        }

        return result;
    }
}

#endif
