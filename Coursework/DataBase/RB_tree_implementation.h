#pragma once
#include <iostream>
#include "implementation.h"
#include "RB_tree.h"
#include "document.h"
#include "concrete_generator_factory1.h"
#include "strategy.h"

class RB_tree_implementation : public realisation_class {
private:
    RB_tree<Document>* _tree;
public:
    RB_tree_implementation() {
        _tree = new RB_tree<Document>(new documents_strategy);
    }
    ~RB_tree_implementation() override {
        delete _tree;
    }

    void insert(const Document& current_document) override {
        _tree->insert(current_document);
    }
    Document* search(const Document& current_document, strategy<Document>* comparator) override {
        return _tree->dumb_search(current_document, comparator);
    }
    bool remove(const Document& current_document) override {
        return _tree->remove(current_document);
    }
    void generate(int count) override {
        const auto factory = new generator_factory1;
        const auto generator = factory->create_generator();
        Document* current_document;

        for (int i = 0; i < count; ++i) {
            current_document = generator->generate();
            _tree->insert(*current_document);
            delete current_document;
        }

        delete generator;
        delete factory;
    }
};