#pragma once

class realisation_class {
public:
    virtual bool insert() = 0;
    virtual bool search() = 0;
    virtual bool remove() = 0;
    virtual bool generate() = 0;
    virtual ~realisation_class() = 0;
};
