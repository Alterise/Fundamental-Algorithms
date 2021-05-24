#pragma once
#include "concrete_generator1.h"
#include "concrete_generator2.h"
#include "abstract_generator_factory.h"

class concrete_generator_factory2 : public abstract_generator_factory {
public:
    abstract_generator* create_generator() const override {
        // concrete_generator2 is NOT implemented
        return new concrete_generator2;
    }
};