#pragma once
#include "document.h"

class abstract_generator {
public:
    virtual ~abstract_generator() = default;
    virtual Document generate() = 0;
};