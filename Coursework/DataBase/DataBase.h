#pragma once
#include "implementation.h"

class data_base
{
public:
    explicit data_base(realisation_class* realisation) {
        _realisation = realisation;
    }

    ~data_base() {
        delete _realisation;
    }

    void insert(const Document& current_document) {
        _realisation->insert(current_document);
    }
    Document* search(const Document& current_document, strategy<Document>* comparator) {
        return _realisation->search(current_document, comparator);
    }
    bool remove(const Document& current_document) {
        return _realisation->remove(current_document);
    }
    void generate(int count) {
        _realisation->generate(count);
    }

protected:
    realisation_class* _realisation;
};