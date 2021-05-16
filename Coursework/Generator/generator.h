#pragma once
#include "document.h"
#include "generator_interface.h"

class generator {
    explicit  generator(generator_interface* current_generator) {
        _current_generator = current_generator;
    }
    ~generator() {
        delete _current_generator;
    }
    Document generate() {
        return _current_generator->generate();
    }
private:
    generator_interface* _current_generator;
};