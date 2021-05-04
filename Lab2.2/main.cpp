#include <iostream>
#include "RB_tree.h"
#include "concrete_strategies.h"

int main()
{
    RB_tree<int> tree(new int_strategy);
    tree.insert(3);
    tree.insert(5);
    tree.insert(8);
    tree.insert(9);
    tree.insert(20);
    tree.insert(2);
    tree.insert(1);
    tree.insert(4);
    tree.insert(6);
    tree.insert(16);
    tree.insert(7);
    tree.insert(10);
}