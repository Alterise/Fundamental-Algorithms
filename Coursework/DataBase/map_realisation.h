#pragma once
#include <map>
#include <iostream>
#include "realisation.h"

class map_realisation : public realisation_class {
    ~map_realisation() {

    }
    bool insert() {
        return true;
    }
    bool search() {
        return true;
    }
    bool remove() {
        return true;
    }
    bool generate() {
        return true;
    }

private:
    std::string key_generator() {
        std::mt19937 random_engine(time(nullptr));
        std::uniform_int_distribution<int> distribution((int)'a', (int)'z');
        std::string key;
        for (int i = 0; i < 10; ++i) {
            key += (char)distribution(random_engine);
        }
        return key;
    }
};