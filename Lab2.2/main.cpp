#include <iostream>
#include "RB_tree.h"
#include "concrete_strategies.h"

int main()
{
    RB_tree<int> tree(new int_strategy);
    std::cout << tree.get_value();
}