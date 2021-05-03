#include <iostream>
#include "RB_tree.h"
#include "concrete_strategies.h"

int main()
{
    RB_tree<int> tree(new int_strategy);
    tree.insert(3);
//    auto a = tree.search(5);
//    if(a != nullptr) {
//        std::cout << *a;
//    } else {
//        std::cout << "Nan";
//    }
//    std::cout << std::endl;
    tree.insert(5);
    tree.insert(8);
    tree.insert(5);
    tree.insert(2);
    tree.insert(1);
//    a = tree.search(5);
//    if(a != nullptr) {
//        std::cout << *a;
//    } else {
//        std::cout << "Nan";
//    }
}