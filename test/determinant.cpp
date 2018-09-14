#include <determinant.hpp>

using namespace mac;

void test1() {
    cout << "-----------------------------------\n";
    cout << "Arbitrary test\n";
    Matrix matrix = {
        { 1.0, 2.0, 1.0 },
        { 3.0, 1.5, 4.0 },
        { 5.0, 2.0, 1.0 }
    };

    double det = det_russ(matrix);
    cout << "A: \n" << matrix << '\n';
    cout << "Determinant: " << det << '\n';
}

void test2() {
    cout << "-----------------------------------\n";
    cout << "Property 7\n";

    Matrix a = {
        { 1.0, 1.0, 0.0 },
        { 1.0, 1.0, 1.0 },
        { 2.0, 0.0, 1.0 }
    };

    Matrix b = {
        { 1.0, 1.0, 0.0 },
        { 0.0, 0.0, 1.0 },
        { 2.0, 0.0, 1.0 }
    };

    cout << "A: \n" << a << '\n';
    cout << "B: \n" << b << '\n';

    Matrix c = {
        { 1.0, 1.0, 0.0 },
        { 1.0, 1.0, 2.0 },
        { 2.0, 0.0, 1.0 }
    };

    cout << "C: \n" << c << '\n';

    double det = det_russ(c);
    cout << "Determinant: " << det << '\n';
}

void test3() {
    cout << "-----------------------------------\n";
    cout << "Proposed property\n";

    Matrix original = {
        { 1, 2, 0, 0 },
        { 3, 4, 0, 0 },
        { 1, 1, 1, 1 },
        { 2, 10, 1, 4 }
    };

    cout << "A: \n" << original << '\n';
    double det = det_russ(original);
    cout << "Determinant: " << det << '\n';
}

void test4() {
    cout << "-----------------------------------\n";
    cout << "Det stagger test 1\n";

    Matrix a {
        { 3, 4, 5, 0, 0 },
        { 1, 1, 3, 0, 0 },
        { 0, 0, 1, 0, 0 },
        { 1, 1, 3, 1, 2 },
        { -1, -1, 4,  1, 1 }
    };

    cout << "A: \n" << a << '\n';
    double det1 = det_russ(a);
    double det2 = det_stagger(a);
    cout << "Determinant: " << det1 << '\n';
    cout << "Determinant: " << det2 << '\n';
}

void test5() {
    cout << "-----------------------------------\n";
    cout << "Det stagger test 2\n";

    Matrix a {
        { 0, 0, 1, 10 },
        { 0, 10, 1, 1 },
        { 1, 3, 4, 4 },
        { 2, 1, 1, 1 }
    };

    cout << "A: \n" << a << '\n';
    double det1 = det_russ(a);
    double det2 = det_stagger(a);
    cout << "Determinant: " << det1 << '\n';
    cout << "Determinant: " << det2 << '\n';
}

void test6() {
    cout << "-----------------------------------\n";
    cout << "Det stagger test 3\n";

    Matrix a {
        { 0, 0, 3, 1 },
        { 0, 0, 3, 1 },
        { 0, 1, 1, 1 },
        { 0, 2, 3, 1 }
    };

    cout << "A: \n" << a << '\n';
    double det1 = det_russ(a);
    double det2 = det_stagger(a);
    cout << "Determinant: " << det1 << '\n';
    cout << "Determinant: " << det2 << '\n';
}

int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
}
