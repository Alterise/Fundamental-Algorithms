#pragma once
#include <list>
#include <map>
#include "binary_tree.h"
#include "strategy.h"

const int MAX_ID = 200;

template <typename T>
class relation {
private:
    std::list<T> _data;
    std::map<size_t , binary_tree<T*>*> _trees;
    strategy<T>* _comparator;
public:
    explicit relation(strategy<T>* comparator) {
        _comparator = comparator;
    }
    ~relation() {
        for (const auto& [id, tree] : _trees) {
            delete tree;
        }
    }

    void insert(const T& key) {
        for (const auto &item : _data) {
            if (_comparator->compare(key, item) == 0) {
                return;
            }
        }
        _data.push_back(key);
        for (const auto& [id, tree] : _trees) {
            tree->insert(&(_data.back()));
        }
    }

    void remove(T key) {
        for (const auto& [id, tree] : _trees) {
            tree->remove(&key);
        }
        _data.remove(key);
    }

    T* search(int id, T key) {
        if (_trees.find(id) != _trees.end()) {
            auto elem = _trees[id]->search(&key);
            if (elem != nullptr) {
                return *elem;
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    int insert_tree(binary_tree<T*>* tree) {
        size_t id = rand() % (MAX_ID + 1);
        if (_trees.find(id) == _trees.end()) {
            _trees.emplace(id, tree);
            for (auto &elem : _data) {
                _trees[id]->insert(&elem);
            }
            return (int)id;
        }
        return -1;
    }

    void remove_tree(int id) {
        _trees.erase(id);
    }
};