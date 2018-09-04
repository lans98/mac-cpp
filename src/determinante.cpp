#include <determinante.hpp>

using namespace mac;

void test1() {
    Matrix matrix = {
        { 1.0, 2.0, 1.0 },
        { 3.0, 1.5, 4.0 },
        { 5.0, 2.0, 1.0 }
    };

    double det = determinante(matrix);
    cout << det << '\n';
}

int main() {
    test1();
}
