#pragma once
#include "concrete_generator1.h"
#include "concrete_generator2.h"
#include "abstract_generator_factory.h"

class generator_factory1 : public abstract_generator_factory {
public:
    abstract_generator* create_generator() const override {
        return new concrete_generator1;
    }
};