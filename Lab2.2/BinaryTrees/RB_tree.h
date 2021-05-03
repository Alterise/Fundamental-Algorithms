#pragma once
#include <vector>
#include "binary_tree.h"

using std::cout;
using std::endl;

template <typename T>
class RB_tree : public binary_tree<T>
{
public:
    explicit RB_tree(strategy<T>* comparator, bool allow_duplicates = true) : binary_tree<T>(comparator, allow_duplicates) {
        _root = nullptr;
    }

    ~RB_tree() {
        node_clear(_root);
        if(_root != nullptr) {
            delete _root;
        }
    }

    void insert(const T& key) override {
        if (_root == nullptr) {
            _root = new node<T>(key, true);
        } else {
            std::vector<node<T>*> route;
            node_insert(_root, key, route);
            tree_fix(route);
            _root->_is_black = true;
//            for (const auto &item : route) {
//                cout << item->_data << " ";
//            }
//            cout << endl;
        }
    }

    void remove(const T& key) override {

    }

    T* search(const T& key) override {
        return node_search(_root, key);
    }

private:
    template <typename J>
    class node {
    public:
        explicit node(const J& data, bool is_black = false, node<J>* left_child = nullptr, node<J>* right_child = nullptr) {
            _data = data;
            _is_black = is_black;
            _left_child = left_child;
            _right_child = right_child;
        }
        J _data;
        node<J>* _left_child;
        node<J>* _right_child;
        bool _is_black;
    };

    node<T>* _root;

    T* node_search(node<T>* current_node, const T& key) {
        if(current_node == nullptr) {
            return nullptr;
        }
        if(this->_comparator->compare(key, current_node->_data) == 0) {
            return &(current_node->_data);
        } else if (this->_comparator->compare(key, current_node->_data) < 0) {
            return node_search(current_node->_left_child, key);
        } else {
            return node_search(current_node->_right_child, key);
        }
    }

    void node_insert(node<T>* current_node, const T& key, std::vector<node<T>*>& route) {
        route.push_back(current_node);
        if(!(this->_allow_duplicates) && (this->_comparator->compare(key, current_node->_data) == 0)) {
            return;
        }
        if (this->_comparator->compare(key, current_node->_data) < 0) {
            if(current_node->_left_child == nullptr) {
                current_node->_left_child = new node<T>(key);
                route.push_back(current_node->_left_child);
            } else {
                node_insert(current_node->_left_child, key, route);
            }
        } else {
            if(current_node->_right_child == nullptr) {
                current_node->_right_child = new node<T>(key);
                route.push_back(current_node->_right_child);
            } else {
                node_insert(current_node->_right_child, key, route);
            }
        }
    }
    void node_clear(node<T>* current_node) {
        if(current_node == nullptr) {
            return;
        } else {
            node_clear(current_node->_left_child);
            node_clear(current_node->_right_child);
            if(current_node->_left_child != nullptr) {
                delete current_node->_left_child;
            }
            if(current_node->_right_child != nullptr) {
                delete current_node->_right_child;
            }
        }
    }
    void tree_fix(std::vector<node<T>*>& route) {
        node<T>* current_node = route.back();
        route.pop_back();
        if(route.empty()) {
            return;
        }
        node<T>* parent_node = route.back();
        route.pop_back();
        node<T>* grandparent_node;
        bool uncle_is_black;
        if(!route.empty()) {
            grandparent_node = route.back();
            route.pop_back();
            if(grandparent_node->_left_child != parent_node) {
                if(grandparent_node->_left_child != nullptr) {
                    uncle_is_black = grandparent_node->_left_child->_is_black;
                } else {
                    uncle_is_black = true;
                }
            } else {
                if(grandparent_node->_right_child != nullptr) {
                    uncle_is_black = grandparent_node->_right_child->_is_black;
                } else {
                    uncle_is_black = true;
                }
            }
        }
        // Case 0: Parent is black
        if (parent_node->_is_black) {
            return;
        }
        // Case 1: Uncle is red
        if(!uncle_is_black) {
            if(grandparent_node->_left_child != parent_node) {
                grandparent_node->_left_child->_is_black = true;
            } else {
                grandparent_node->_right_child->_is_black = true;
            }
            parent_node->_is_black = true;
            grandparent_node->_is_black = false;
            route.push_back(grandparent_node);
            tree_fix(route);
            return;
        }
    }
};
