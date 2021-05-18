#pragma once
#include "implementation.h"
#include "statistics.h"
#include "concrete_generator_factory1.h"
#include "concrete_strategies.h"

class data_base
{
public:
    statistics_table statistics;
private:
    realisation_class* _realisation;
    Document* _buffered_element;
public:
    explicit data_base(realisation_class* realisation) {
        _realisation = realisation;
    }

    ~data_base() {
        delete _realisation;
    }

    void insert(const Document& current_document) {
        _realisation->insert(current_document);
        statistics.insert(current_document);
    }

    Document* search(const Document& current_document, strategy<Document>* comparator) {
        _buffered_element = _realisation->search(current_document, comparator);
        return _buffered_element;
    }

    bool remove(const Document& current_document) {
        auto tmp = _realisation->remove(current_document);
        if (tmp) {
            statistics.remove(current_document);
        }
        return tmp;
    }

    bool remove_buffered() {
        if (_buffered_element == nullptr) {
            return false;
        } else {
            statistics.remove(*_buffered_element);
            auto tmp = _realisation->remove(*_buffered_element);
            _buffered_element = nullptr;
            return tmp;
        }
    }

    Document* get_buffered() {
        return _buffered_element;
    }

    void generate(int count) {
        const auto factory = new generator_factory1;
        const auto generator = factory->create_generator();
        Document* current_document;
        for (int i = 0; i < count; ++i) {
            current_document = generator->generate();
            insert(*current_document);
            statistics.insert(*current_document);
            delete current_document;
        }
        delete generator;
        delete factory;
    }
};