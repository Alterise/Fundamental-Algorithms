#pragma once
#include "binary_tree.h"

template <typename T>
struct node {
    T data;
    node<T> left_child;
    node<T> right_child;
    bool is_black;
};

template <typename T>
class RB_tree : public binary_tree<T>
{
public:
    explicit RB_tree(strategy<T>* comparator) : binary_tree<T>(comparator) {
        _data = NULL;
        _left_child = nullptr;
        _right_child = nullptr;
        is_black = true;
        RB
    }
    void insert(const T& key) override {

    }

    void remove(const T& key) override {

    }

    bool search(const T& key) override {
        // TODO: переделать под структуры
        if((this->_comparator->compare(this->root, key)) == 0) {
            return true;
        } else if(((this->_comparator->compare(this->_data, key)) < 0) || this->_left_child != nullptr) {
            return this->_left_child->search(key);
        } else if(((this->_comparator->compare(this->_data, key)) < 0) || this->_left_child != nullptr) {
            return this->_right_child->search(key);
        } else {
            return false;
        }
    }

private:
    node<T> _root;
};
