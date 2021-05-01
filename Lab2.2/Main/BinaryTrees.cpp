#include <iostream>
#include "RB_tree.h"

int main()
{
    Date d1 = {22, 02, 2001};
    Date d2 = {31, 12, 1990};
    std::cout << (d2 < d1);
}