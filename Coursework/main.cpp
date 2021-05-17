#include <iostream>
#include "concrete_generator_factory1.h"

int main() {
    const auto factory = new generator_factory1;
    const auto generator = factory->create_generator();
    auto current_document = generator->generate();

    delete current_document;
    delete generator;
    delete factory;
    return 0;
}