#pragma once
#include "abstract_generator.h"

class abstract_generator_factory {
public:
    virtual ~abstract_generator_factory() = default;
    virtual abstract_generator* create_generator() const = 0;
};