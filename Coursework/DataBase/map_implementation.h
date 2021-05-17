#pragma once
#include <map>
#include <iostream>
#include "implementation.h"
#include "document.h"
#include "concrete_generator_factory1.h"
#include "concrete_strategies.h"

class map_realisation : public realisation_class {
private:
    std::map<std::string, Document> _map;
    std::mt19937 _random_engine;
    std::uniform_int_distribution<int> _key_distribution;
    documents_strategy _comparator;
public:
    map_realisation() {
        std::mt19937 random_engine(time(nullptr));
        _random_engine = random_engine;
        std::uniform_int_distribution<int> distribution((int)'a', (int)'z');
        _key_distribution = distribution;
    }
    ~map_realisation() override = default;

    void insert(const Document& current_document) override {
        std::string key;
        do {
            key = key_generator();
        } while (_map.find(key) != _map.end());
        _map.insert({key, current_document});
    }

    Document* search(const Document& current_document, strategy<Document>* comparator) override {
        for (auto &[key, data] : _map) {
            if (comparator->compare(data, current_document) == 0) {
                return &data;
            }
        }
        return nullptr;
    }

    bool remove(const Document& current_document) override {
        for (auto iterator = _map.begin(); iterator != _map.end() ; iterator++) {
            if (_comparator.compare(iterator->second, current_document) == 0) {
                _map.erase(iterator);
                return true;
            }
        }
        return false;
    }

    void generate(int count) override {
        const auto factory = new generator_factory1;
        const auto generator = factory->create_generator();
        Document* current_document;

        for (int i = 0; i < count; ++i) {

            current_document = generator->generate();
            insert(*current_document);
            delete current_document;
        }

        delete generator;
        delete factory;
    }

private:
    std::string key_generator() {
        std::string key;
        for (int i = 0; i < 10; ++i) {
            key += (char)_key_distribution(_random_engine);
        }
        return key;
    }
};