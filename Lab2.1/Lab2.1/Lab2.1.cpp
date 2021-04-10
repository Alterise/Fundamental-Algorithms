#include "TeX_convertible.h"
#include "Matrix.h"

#include <iostream>
#include <exception>
#include <vector>

using namespace std;

int main()
{
    //Matrix matr, matr2(5), matr3(7, 5.25);
    //matr.print();
    //matr2.print();
    //matr3.print();
    try {
        Matrix matr(-3);
    } catch (exception& ex) {
        cout << "Exception caught: " << ex.what() << endl;
        return 0;
    }
}