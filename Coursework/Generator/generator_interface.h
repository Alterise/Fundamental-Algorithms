#pragma once
#include "document.h"

class generator_interface {
    virtual ~generator_interface() = 0;
    virtual Document generate() = 0;
};