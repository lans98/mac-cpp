#ifndef MAC_INVERSE_HPP
#define MAC_INVERSE_HPP 

#include <stdexcept>

#include <armadillo>
#include <matrix.hpp>
#include <determinant.hpp>

namespace mac {

    using namespace std;
    using namespace arma;

    Matrix inverse_method1(const Matrix& mat) {
        if (!mat.is_square()) 
            throw logic_error("Matrix is not square!");

        Matrix augmented(mat);
        augmented.insert_cols(mat.n_cols, eye<Matrix>(mat.n_rows, mat.n_cols));


        for (size_t i = 0; i < augmented.n_rows; ++i) {
            if (augmented(i, i) == 0.0) {
                for (auto k = i; k < augmented.n_rows; ++k) {
                    if (augmented(k, i) == 0.0) continue;

                    augmented.swap_rows(i, k);
                    break;
                }

                if (augmented(i, i) == 0.0)
                    throw logic_error("Imposible to find inverse");

            } else if (augmented(i, i) != 1.0) {
                double val = augmented(i, i);
                for (auto j = 0ul; j < augmented.n_cols; ++j) 
                    augmented(i, j) *= (1.0 / val);
            }

            for (auto j = 0ul; j < augmented.n_rows; ++j) {
                if (i == j) continue;

                double val = augmented(j, i);
                for (auto k = 0ul; k < augmented.n_cols; ++k)            
                    augmented(j, k) -= val * augmented(i, k);
            }
        }

        return augmented.submat(0ul, mat.n_cols, augmented.n_rows - 1ul, augmented.n_cols - 1ul);
    }

    Matrix inverse_method2(const Matrix& mat) {
        if (!mat.is_square())
            throw logic_error("Matrix is not square!");

        Matrix cofactors(mat);
        for (auto i = 0ul; i < mat.n_rows; ++i)
            for (auto j = 0ul; j < mat.n_cols; ++j)
                cofactors(i, j) = cofactor(mat, i, j);

        cofactors = cofactors.t();
        return (1 / det_stagger(mat)) * cofactors;
    }
}

#endif
