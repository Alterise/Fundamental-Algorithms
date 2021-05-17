#pragma once
#include "abstract_generator.h"

class concrete_generator2 : public abstract_generator {
    Document* generate() override {
        auto current_document = new Document;
        // Put your implementation here
        return current_document;
    }
};