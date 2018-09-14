#ifndef MAC_DETERMINANT_HPP
#define MAC_DETERMINANT_HPP

#include <vector>	
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <armadillo>

#include <matrix.hpp>

namespace mac {

    using namespace std;

    double det_russ2x2(const Matrix& mat) {
        if (!mat.is_square() && (mat.n_rows == 2UL))
            throw logic_error("Matrix is not 2x2!");

        return mat(0UL, 0UL) * mat(1UL, 1UL) - mat(0UL, 1UL) * mat(1UL, 0UL);
    }

    double det_russ(const Matrix& mat) {
        if (!mat.is_square())
            throw logic_error("Matrix is not square!");
            
        auto n = mat.n_rows;

        if (n == 2UL) 
            return det_russ2x2(mat);
        
        double result = 0;
        Matrix new_mat = Matrix(n - 1UL, n - 1UL);

        for (auto k = 0UL; k < n; ++k) {
            for (auto i = 1UL; i < n; ++i) {
                for (auto j = 0UL; j < n; ++j) {
                    if (k == j) continue;
                    
                    new_mat(i - 1, j < k? j : j - 1) = mat(i, j);
                }
            }

            result += pow(-1, k) * mat(0, k) * det_russ(new_mat);				
        }

        return result;
    }

    double det_stagger(const Matrix& mat) {
        if (!mat.is_square())
            throw logic_error("Matrix is not square!");
    
        int no_of_swaps = 0;
        Matrix stagged = stagger_advanced(mat, no_of_swaps);

        double result = 1;
        for (auto i = 0UL; i < stagged.n_rows; ++i)
            result *= stagged(i, i);

        return (no_of_swaps % 2? -result : result);
    }

    double cofactor(const Matrix& mat, size_t i, size_t j) {
        if (!mat.is_square())
            throw logic_error("Matrix is not square!");

        Matrix temp(mat.n_rows - 1, mat.n_cols - 1);

        for (auto r = 0ul; r < mat.n_rows; ++r) {
            if (r == i) continue;
            for (auto c = 0ul; c < mat.n_cols; ++c) {
                if (c == j) continue;

                temp(r < i? r : r - 1, c < j? c : c - 1) = mat(r, c);
            }
        }
    
        return pow(-1.0, i + j) * det_stagger(temp);
    }
}

#endif
