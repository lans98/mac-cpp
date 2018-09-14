#include <inverse.hpp>

using namespace mac;

void test1() {
    cout << "-----------------------------------\n";
    cout << "Arbitrary test\n";

    Matrix matrix = {
        { 1.0, 2.0, 3.0 },
        { 3.0, 2.0, 1.0 },
        { 1.0, 1.0, 0.0 }
    };

    cout << inverse_method1(matrix) << '\n';
}

void test2() {
    cout << "-----------------------------------\n";
    cout << "Arbitrary test\n";

    Matrix matrix = {
        { 1.0, 2.0, 3.0 },
        { 3.0, 2.0, 1.0 },
        { 1.0, 1.0, 0.0 }
    };

    cout << inverse_method2(matrix) << '\n';
}

void test3() {
    cout << "-----------------------------------\n";
    cout << "Arbitrary test\n";

    Matrix matrix = {
        { 1.0, 2.0, 3.0, 1.0 },
        { 3.0, 2.0, 1.0, 1.0 },
        { 1.0, 1.0, 0.0, 1.0 },
        { 1.0, 1.0, 1.0, 1.0 }
    };

    Matrix inv = inverse_method1(matrix);
    cout << inv << '\n';
    cout << matrix * inv << '\n';
}

void test4() {
    cout << "-----------------------------------\n";
    cout << "Arbitrary test\n";

    Matrix matrix = {
        { 1.0, 2.0, 3.0, 1.0 },
        { 3.0, 2.0, 1.0, 1.0 },
        { 1.0, 1.0, 0.0, 1.0 },
        { 1.0, 1.0, 1.0, 1.0 }
    };

    Matrix inv = inverse_method2(matrix);
    cout << inv << '\n';
    cout << matrix * inv << '\n';
}

int main() {
    test1();
    test2();
    test3();
    test4();
}
