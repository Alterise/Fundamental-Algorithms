#include <iostream>
#include <random>
#include "RB_tree.h"
#include "concrete_strategies.h"

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(-50, 50);
    RB_tree<int> tree(new int_strategy);
    for (int i = 0; i < 25; ++i) {
        tree.insert(distr(gen));
    }
    tree.print();
}