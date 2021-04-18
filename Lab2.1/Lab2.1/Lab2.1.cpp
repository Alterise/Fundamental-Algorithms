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
    Matrix matr(3, 25);

    cout << matr << endl;
    cout << matr * matr << endl;
    cout << matr * 4 << endl;
    try {
        my_stream >> matr;
    } catch (exception& ex) {
        cout << "Exception caught: " << ex.what() << endl;
        return 0;
    }
    cout << matr << endl;
    cout << transpose(matr) << endl;
    cout << determinant(matr) << endl;
    cout << trace(matr) << endl;
    cout << (matr != matr) << endl;
    cout << exponential(matr);
    int a = 1;
    int b = 1;
    cout << matr[{a, b}] << endl;
    my_stream.clear();
    my_stream.str("[[1, 2], [0, 1]]");
    try {
        my_stream >> matr;
    }
    catch (exception& ex) {
        cout << "Exception caught: " << ex.what() << endl;
        return 0;
    }
    cout << matr;
    cout << reversed(matr);
}