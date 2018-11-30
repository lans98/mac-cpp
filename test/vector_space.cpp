#include <iostream>
#include <vector_space.hpp>

using namespace std;
using namespace mac;

void test1() {
    Matrix vectors = {
        { 1, 0, 0 },
        { 0, 1, 0 },
        { 0, 0, 1 }
    };

    cout << boolalpha << linearly_independents(vectors) << '\n';
}

void test2() {
    Matrix vectors = {
        { 1, 2, 3 },
        { 1, 1, 0 },
        { 1, 3, 6 }
    };

    cout << boolalpha << linearly_independents(vectors) << '\n';
}

void test3() {
    CVector vec({2, 1});

    Matrix base_1 = {
        { 1, 1 },
        { 1, 0 }
    };

    Matrix base_2 = {
        { 1, 0 },
        { 0, -1 }
    };

    cout << coords_in_base(vec, base_1) << '\n';
    cout << coords_in_base(vec, base_2) << '\n';

}

int main() {
    test1();
    test2();
    test3();
}
