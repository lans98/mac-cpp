#include <iostream>
#include <linear_transformation.hpp>

using namespace std;
using namespace mac;

int main() {
    LinearTransformation t(3, 2);

    Matrix transformation_matrix({
        { 1, 0, 1 },
        { 1, 1, 2 }
    });

    t.set_transformation_matrix(transformation_matrix);

    cout << t(CVector({ 2, 3, 1 })) << '\n';
}
