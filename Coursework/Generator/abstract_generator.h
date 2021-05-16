#pragma once
#include "document.h"

class abstract_generator {
public:
    virtual ~abstract_generator() = 0;
    virtual Document* generate() = 0;
};