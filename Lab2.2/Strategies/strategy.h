#pragma once
#include "current_strategies.h"

template<typename T>
class strategy
{
public:
    virtual bool compare(const T&, const T&) = 0;
};