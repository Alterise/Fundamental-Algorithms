#include "TeX_convertible.h"
#include "Matrix.h"

#include <iostream>
#include <exception>
#include <vector>
#include <sstream>

using namespace std;

int main()
{
    stringstream my_stream("[[1, 2, 3], [4, 55, 6], [7, 8, 9]]");
    Matrix matr(7, 10000), matr2(3, 3), matr3(3, 5);

    cout << matr2 << endl;
    cout << matr3 << endl;
    Matrix matr4 = matr2 * matr3;
    cout << matr2 << endl;
    cout << matr4 << endl;
    matr4 *= 4;
    cout << 4 * matr4 << endl;
    try {
        my_stream >> matr2;
    } catch (exception& ex) {
        cout << "Exception caught: " << ex.what() << endl;
        return 0;
    }
    cout << matr2 << endl;
    cout << transpose(matr2) << endl;
    cout << determinant(matr2) << endl;
    cout << (matr2 != matr2) << endl;
    int a = 1;
    int b = 1;
    cout << matr2[{a, b}] << endl;
    my_stream.clear();
    my_stream.str("[[1, 2, -0], [0, 1, -0], [3, -0, 1]]");
    cout << my_stream.str() << endl;
    Matrix matr5(3);
    try {
        my_stream >> matr5;
    }
    catch (exception& ex) {
        cout << "Exception caught: " << ex.what() << endl;
        return 0;
    }
    cout << matr5;
    cout << reversed(matr5);
}