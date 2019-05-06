#ifndef MAC_LINEAR_TRANSFORMATION_HPP
#define MAC_LINEAR_TRANSFORMATION_HPP

#include <matrix.hpp>
#include <except.hpp>

namespace mac {

    using namespace std;

    class LinearTransformation {
    private:
        size_t dimension_in;
        size_t dimension_out;
        Matrix transformation_matrix;

        bool configured = false;

    public:
        LinearTransformation(size_t dimension_in, size_t dimension_out, Matrix matrix = Matrix()):
            dimension_in(dimension_in),
            dimension_out(dimension_out)
        {
            set_transformation_matrix(matrix);
        }

        void set_transformation_matrix(Matrix matrix) {
            if (matrix.n_rows != dimension_out || matrix.n_cols != dimension_in)
                throw IncorrectDimensionParameter();

            transformation_matrix = matrix;   
            configured = true;
        }

        void set_dimensions_parameters(size_t dimension_in, size_t dimension_out) {
            this->dimension_in = dimension_in;
            this->dimension_out = dimension_out;
            configured = false;
        }

        CVector operator()(CVector const& input) {
            if (!configured)
                throw NotConfigured();

            if (input.n_rows != dimension_in)
                throw IncorrectDimensionParameter();

            return transformation_matrix * input;
        }

        RVector operator()(RVector const& input) {
            if (!configured)
                throw NotConfigured();

            if (input.n_cols != dimension_in)
                throw IncorrectDimensionParameter();

            return transformation_matrix * CVector(input);
        }
    };
}

#endif 
