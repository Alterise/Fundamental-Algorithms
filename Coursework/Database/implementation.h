#pragma once
#include "strategy.h"
#include "document.h"

class implementation_class {
public:
    virtual void insert(const Document&) = 0;
    virtual Document* search(const Document&, strategy<Document>*) = 0;
    virtual bool remove(const Document&) = 0;
    virtual ~implementation_class() = default;
};