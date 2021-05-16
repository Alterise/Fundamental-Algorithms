#pragma once
#include "abstract_generator.h"

class abstract_generator_factory {
    virtual abstract_generator* create_generator() const = 0;
};