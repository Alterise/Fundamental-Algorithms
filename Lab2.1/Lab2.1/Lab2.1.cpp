#include "TeX_convertible.h"
#include "Matrix.h"

#include <iostream>
#include <exception>
#include <vector>

using namespace std;

int main()
{
    Matrix matr, matr2(7, 671), matr3(7, 5.25);
    matr.print();
    matr2.print();
    matr3.print();
    Matrix matr4(matr3);
    cout << endl;
    matr4.print();
    cout << endl;

    matr4 = matr2 + matr3;
    matr4.print();
    try {
        Matrix matr6(-3);
    } catch (exception& ex) {
        cout << "Exception caught: " << ex.what() << endl;
        return 0;
    }
}