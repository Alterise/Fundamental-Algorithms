#pragma once
#include "binary_tree.h"

template <typename T>
class RB_tree : public binary_tree<T>
{
public:
//    using binary_tree<T>::binary_tree;
    explicit RB_tree(strategy<T>* comparator) : binary_tree<T>(comparator) {}
    void insert(const T&) override;
    void remove(const T&) override;
    bool search(const T&) override;
};
