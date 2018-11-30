#ifndef MAC_MATRIX_HPP
#define MAC_MATRIX_HPP

#include <armadillo>

#include <except.hpp>

namespace mac {

    using namespace std;
    using namespace arma;

    using Matrix = arma::mat;
    using CVector = arma::colvec;
    using RVector = arma::rowvec;

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

    Matrix stagger_advanced(const Matrix& matrix) {
        int swaps;
        return stagger_advanced(matrix, swaps);
    }

    auto lu_decomposition(const Matrix& matrix) {
        Matrix L(matrix.n_rows, matrix.n_rows, fill::eye);
        Matrix U(matrix);

        for (auto rr = 0; rr < U.n_rows; ++rr) {
            auto& pivot_elm = U(rr, rr); // elm -> element
            for (auto ii = rr + 1; ii < U.n_rows; ++ii) {
                auto& temp_elm = U(ii, rr);

                if (pivot_elm == 0.0)
                    throw runtime_error("This matrix doesn't have LU decomposition");

                auto m = temp_elm/pivot_elm;
                L(ii, rr) = m;
                for (auto jj = 0; jj < U.n_cols; ++jj)
                    U(ii, jj) -= m * U(rr, jj);
            }
        }

        return make_tuple(L, U);
    }

    auto plu_decompotition(const Matrix& matrix) {
        Matrix P(matrix.n_rows, matrix.n_rows, fill::eye);
        Matrix L(matrix.n_rows, matrix.n_rows, fill::zeros);
        Matrix U(matrix);

        for (auto rr = 0; rr < U.n_rows; ++rr) {
            // Search for the greatest element in the column rr
            auto max_rr = rr; // index of the maximum element
            auto max_el = fabs(U(rr, max_rr));
            for (auto ii = max_rr + 1; ii < U.n_rows; ++ii) {
                if (fabs(U(rr, ii)) > max_el) {
                    max_rr = ii;
                    max_el = fabs(U(rr, ii));
                }
            }

            if (max_rr != rr) {
                 U.swap_rows(rr, max_rr);
                 P.swap_rows(rr, max_rr);
                 L.swap_rows(rr, max_rr);
             }

            // Classical algorithm starts here
            auto& pivot_elm = U(rr, rr); // elm -> element
            for (auto ii = rr + 1; ii < U.n_rows; ++ii) {
                auto& temp_elm = U(ii, rr);

                auto m = temp_elm/pivot_elm;
                L(ii, rr) = m;
                for (auto jj = 0; jj < U.n_cols; ++jj)
                    U(ii, jj) -= m * U(rr, jj);
            }
        }

        return make_tuple(P, L + Matrix(matrix.n_rows, matrix.n_rows, fill::eye), U);
    }


    CVector regressive_sub(const Matrix& matrix) {
        CVector solutions(matrix.n_rows, fill::zeros);

        for (long ii = matrix.n_rows - 1L; ii >= 0L; --ii) {
            double sumation = 0;
            for (long jj = solutions.n_rows - 1L; jj > ii; --jj) 
                sumation += solutions(jj) * matrix(ii, jj);

            double numerator = matrix(ii, matrix.n_cols - 1) - sumation;
            if (matrix(ii, ii) == 0.0) {
                if (numerator != 0.0)
                    throw NoSolutions();
                else 
                    throw InfiniteSolutions();
            }

            auto solution = numerator / matrix(ii,ii);
            solutions(ii) = solution;
        }

        return solutions;
    }

    CVector progressive_sub(const Matrix& matrix) {
        CVector solutions(matrix.n_rows, fill::zeros);

        for (auto ii = 0; ii < matrix.n_rows; ++ii) {
            double sumation = 0;
            for (auto jj = 0; jj < solutions.size(); ++jj)
                sumation += solutions(jj) * matrix(ii, jj);

            double numerator = matrix(ii, matrix.n_cols - 1) - sumation;
            if (matrix(ii, ii) == 0.0) {
                if (numerator != 0.0)
                    throw NoSolutions();
                else 
                    throw InfiniteSolutions();
            }

            auto solution = numerator / matrix(ii,ii);
            solutions(ii) = solution;
        }

        return solutions;
    }

    CVector gauss_simple(const Matrix& a, const Matrix& b) {
        auto eq_system = join_rows(a, b);
        return regressive_sub(stagger_simple(eq_system));
    }

    CVector gauss_simple(const Matrix& eq_system) {
        return regressive_sub(stagger_simple(eq_system));
    }

    CVector gauss_advanced(const Matrix& a, const Matrix& b) {
        auto eq_system = join_rows(a, b);
        return regressive_sub(stagger_advanced(eq_system));
    }

    CVector gauss_advanced(const Matrix& eq_system) {
        return regressive_sub(stagger_advanced(eq_system));
    }

    CVector lu_method(const Matrix& a, const Matrix& b) {
        auto lu = lu_decomposition(a);
        auto& L = get<0>(lu);
        auto& U = get<1>(lu);

        auto y_vec = progressive_sub(join_rows(L, b));
        auto y_mat = Matrix(y_vec.size(), 1);

        for (auto cc = 0; cc < y_vec.size(); ++cc)
            y_mat(cc, 0) = y_vec[cc];

        return regressive_sub(join_rows(U, y_mat));
    }

    CVector plu_method(const Matrix& a, const Matrix& b) {
        auto plu = plu_decompotition(a);
        auto &P  = get<0>(plu);
        auto &L  = get<1>(plu);
        auto &U  = get<2>(plu);

        auto y_vec = progressive_sub(join_rows(L, P * b));
        auto y_mat = Matrix(y_vec.size(), 1);

        for (auto cc = 0; cc < y_vec.size(); ++cc)
            y_mat(cc, 0) = y_vec[cc];

        return regressive_sub(join_rows(U, y_mat));
    }
}

#endif
