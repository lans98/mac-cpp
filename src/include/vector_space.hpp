#ifndef MAC_VECTOR_SPACE_HPP
#define MAC_VECTOR_SPACE_HPP

#include <matrix.hpp>

#include <vector>
#include <optional>
#include <functional>

#include <armadillo>

namespace mac {

    using namespace std;
    using namespace arma;

    bool linearly_independents(Matrix const& vectors) {
        if (vectors.empty())
            throw EmptyArgument();

        if (!vectors.is_square())
            throw UnderdeterminedOrOverdetermined();

        auto null_vector = CVector(vectors.n_rows, fill::zeros);
        Matrix system = join_rows(vectors.t(), null_vector);
        
        try {
            auto result = gauss_advanced(system);
            return true;
        } catch (...) { // NoSolutions or InfiniteSolutions
            return false;
        }
    }

    CVector coords_in_base(CVector const& vec, Matrix const& base) {
        if (base.empty() || vec.empty())
            throw EmptyArgument();

        if (!base.is_square())
            throw UnderdeterminedOrOverdetermined();

        Matrix system = join_rows(base.t(), vec);
        return gauss_advanced(system);
    }
}

#endif
