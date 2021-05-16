#pragma once
#include "realisation.h"

class data_base
{
public:
    explicit data_base(realisation_class* realisation) {
        _realisation = realisation;
    }

    ~data_base() {
        delete _realisation;
    }

protected:
    realisation_class* _realisation;
    bool _is_self_realisation;
};