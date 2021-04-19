#include "TeX_convertible.h"
#include "Matrix.h"
#include "Parser.h"

#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
    ifstream ifile("input.txt");
    ofstream ofile("output.txt");
    parse(ifile, ofile);
}