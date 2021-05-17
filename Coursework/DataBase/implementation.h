#pragma once
#include "strategy.h"
#include "document.h"

class realisation_class {
public:
    virtual void insert(const Document&) = 0;
    virtual Document* search(const Document&, strategy<Document>*) = 0;
    virtual bool remove(const Document&) = 0;
    virtual void generate(int) = 0;
    virtual ~realisation_class() = default;
};