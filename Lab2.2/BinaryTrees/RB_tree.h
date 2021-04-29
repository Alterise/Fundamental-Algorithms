#pragma once
#include "binary_tree.h"

template <typename T>
class RB_tree : public binary_tree<T>
{
public:
    void insert(const int &key) override;
    RB_tree<T>& search(const int &key) override;
    void remove(const int &key) override;
};
