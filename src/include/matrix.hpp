#ifndef MAC_MATRIX_HPP
#define MAC_MATRIX_HPP

#include <armadillo>

namespace mac {

    using namespace std;

    using Matrix = arma::mat;

    Matrix stagger_simple(const Matrix& matrix) {
        Matrix result(matrix);

        for (auto rr = 0; rr < matrix.n_rows; ++rr) {
            auto pivot_elm = result(rr, rr); // elm -> element
            for (auto ii = rr + 1; ii < matrix.n_rows; ++ii) {
                auto temp_elm = result(ii, rr);

                auto m = temp_elm/pivot_elm;
                for (auto jj = 0; jj < matrix.n_cols; ++jj)
                    result(ii, jj) -= m * result(rr, jj);
            }
        }

        return result;
    }

    Matrix stagger_advanced(const Matrix& matrix, int& count) {
        count = 0;
        Matrix result(matrix);


        for (auto rr = 0; rr < result.n_rows; ++rr) {
            
            // Search for the greatest element in the column rr
            auto max_rr = rr; // index of the maximum element
            auto max_el = fabs(result(rr, max_rr));
            for (auto ii = max_rr + 1; ii < result.n_rows; ++ii) {
                if (fabs(result(ii, rr)) > max_el) {
                    max_rr = ii;
                    max_el = fabs(result(ii, rr));
                }
            }

            if (max_el == 0.0) continue;
            if (max_rr != rr) {
                count += 1;
                result.swap_rows(rr, max_rr);
            }

            // Classical algorithm starts here
            auto pivot_elm = result(rr, rr); // elm -> element
            for (auto ii = rr + 1; ii < result.n_rows; ++ii) {
                auto temp_elm = result(ii, rr);

                auto m = temp_elm/pivot_elm;
                for (auto jj = 0; jj < result.n_cols; ++jj)
                    result(ii, jj) -= m * result(rr, jj);
            }
        }

        return result;
    }

}

#endif
