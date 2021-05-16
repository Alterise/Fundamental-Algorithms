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
};