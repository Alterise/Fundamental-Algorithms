#pragma once
#include <vector>
#include <algorithm>
#include "binary_tree.h"

template <typename T>
class AVL_tree : public binary_tree<T>
{
private:
    template <typename J> class node;
    node<T>* _root;

public:
    explicit AVL_tree(strategy<T>* comparator, bool allow_duplicates = true) : binary_tree<T>(comparator, allow_duplicates) {
        _root = nullptr;
    }

    ~AVL_tree() {
        node_clear(_root);
        if (_root != nullptr) {
            delete _root;
        }
    }

    void insert(const T& key) override {
        if (_root == nullptr) {
            _root = new node<T>(key);
        } else {
            std::vector<node<T>*> route;
            node_insert(_root, key, route);
            tree_fix_insertion(route);
        }
    }

    void remove(const T& key) override {
        std::vector<node<T>*> route;
        node_remove(_root, key, route);
        tree_fix_deletion(route);
    }

    T* search(const T& key) override {
        return node_search(_root, key);
    }

    void print() {
        node_print(_root);
        std::cout << std::endl;
    }

private:
    template <typename J>
    class node {
    public:
        explicit node(const J& data, int height = 1, node<J>* left_child = nullptr, node<J>* right_child = nullptr) {
            _data = data;
            _height = height;
            _left_child = left_child;
            _right_child = right_child;
        }

        J _data;
        node<J>* _left_child;
        node<J>* _right_child;
        int _height;
    };

    T* node_search(node<T>* current_node, const T& key) {
        if (current_node == nullptr) {
            return nullptr;
        }
        if (this->_comparator->compare(key, current_node->_data) == 0) {
            return &(current_node->_data);
        } else if (this->_comparator->compare(key, current_node->_data) < 0) {
            return node_search(current_node->_left_child, key);
        } else {
            return node_search(current_node->_right_child, key);
        }
    }

    void node_insert(node<T>* current_node, const T& key, std::vector<node<T>*>& route) {
        route.push_back(current_node);
        if (!(this->_allow_duplicates) && (this->_comparator->compare(key, current_node->_data) == 0)) {
            return;
        }
        if (this->_comparator->compare(key, current_node->_data) < 0) {
            if (current_node->_left_child == nullptr) {
                current_node->_left_child = new node<T>(key);
                route.push_back(current_node->_left_child);
            } else {
                node_insert(current_node->_left_child, key, route);
            }
            current_node->_height = 1 + std::max(get_height(current_node->_left_child),
                                                 get_height(current_node->_left_child));
        } else {
            if (current_node->_right_child == nullptr) {
                current_node->_right_child = new node<T>(key);
                route.push_back(current_node->_right_child);
            } else {
                node_insert(current_node->_right_child, key, route);
            }
            current_node->_height = 1 + std::max(get_height(current_node->_left_child),
                                                 get_height(current_node->_right_child));
        }
    }


    void left_rotation(node<T>* current_node) {
        node<T>* child = current_node->_right_child;
        node<T>* grandchild = child->_left_child;
        child->_left_child = current_node;
        current_node->_right_child = grandchild;
        current_node->_height = 1 + std::max(get_height(current_node->_right_child),
                                             get_height(current_node->_left_child));
        child->_height = 1 + std::max(get_height(child->_left_child),
                                      get_height(child->_right_child));
    }

    void right_rotation(node<T>* current_node) {
        node<T>* child = current_node->_left_child;
        node<T>* grandchild = child->_right_child;
        child->_right_child = current_node;
        current_node->_left_child = grandchild;
        current_node->_height = 1 + std::max(get_height(current_node->_right_child),
                                             get_height(current_node->_left_child));
        child->_height = 1 + std::max(get_height(child->_left_child),
                                      get_height(child->_right_child));
    }

    int get_height(node<T>* current_node) {
        if (current_node == nullptr) {
            return 0;
        } else {
            return current_node->_height;
        }
    }

    int get_balance_factor(node<T>* current_node) {
        return get_height(current_node->_left_child) - get_height(current_node->_right_child);
    }

    void tree_fix_insertion(std::vector<node<T>*>& route) {
        if (route.size() < 3) {
            return;
        }
        while (route.size() >= 3) {
            if (get_balance_factor(route[route.size() - 3]) > 1 ||
                get_balance_factor(route[route.size() - 3]) < -1) {
                node<T>* grandchild_node = route.back();
                route.pop_back();
                node<T>* child_node = route.back();
                route.pop_back();
                node<T>* current_node = route.back();
                route.pop_back();
                //CASE 1: LEFT
                if (child_node == current_node->_left_child) {
                    //CASE 1.1: LEFT LEFT
                    if (grandchild_node == child_node->_left_child) {
                        if (_root == current_node) {
                            _root = child_node;
                        } else {
                            if (route.back()->_left_child == current_node) {
                                route.back()->_left_child = child_node;
                            } else {
                                route.back()->_right_child = child_node;
                            }
                        }
                        right_rotation(current_node);
                    }
                    //CASE 1.2: LEFT RIGHT
                    else {
                        if (_root == current_node) {
                            _root = grandchild_node;
                        } else {
                            if (route.back()->_left_child == current_node) {
                                route.back()->_left_child = grandchild_node;
                            } else {
                                route.back()->_right_child = grandchild_node;
                            }
                        }
                        left_rotation(child_node);
                        current_node->_left_child = grandchild_node;
                        right_rotation(current_node);
                    }
                }
                //CASE 2: RIGHT
                else {
                    //CASE 2.1: RIGHT LEFT
                    if (grandchild_node == child_node->_left_child) {
                        if (_root == current_node) {
                            _root = grandchild_node;
                        } else {
                            if (route.back()->_left_child == current_node) {
                                route.back()->_left_child = grandchild_node;
                            } else {
                                route.back()->_right_child = grandchild_node;
                            }
                        }
                        right_rotation(child_node);
                        current_node->_right_child = grandchild_node;
                        left_rotation(current_node);
                    }
                    //CASE 2.2: RIGHT RIGHT
                    else {
                        if (_root == current_node) {
                            _root = child_node;
                        } else {
                            if (route.back()->_left_child == current_node) {
                                route.back()->_left_child = child_node;
                            } else {
                                route.back()->_right_child = child_node;
                            }
                        }
                        left_rotation(current_node);
                    }
                }
                break;
            } else {
                route.pop_back();
            }
        }

        while (!route.empty()) {
            route.back()->_height = 1 + std::max(get_height(route.back()->_right_child),
                                                 get_height(route.back()->_left_child));
            route.pop_back();
        }
    }

    void node_remove(node<T>* current_node, const T& key, std::vector<node<T>*>& route) {
        route.push_back(current_node);
        if (this->_comparator->compare(key, current_node->_data) == 0) {
            route.pop_back();
            if ((current_node->_left_child != nullptr) && (current_node->_right_child != nullptr)) {
                node<T>* node_to_replace = current_node;
                route.push_back(current_node);
                current_node = current_node->_left_child;
                while (current_node->_right_child != nullptr) {
                    route.push_back(current_node);
                    current_node = current_node->_right_child;
                }
                node_to_replace->_data = current_node->_data;
            }
            node<T>* child_node;
            if (current_node->_left_child != nullptr) {
                child_node = current_node->_left_child;
            } else if (current_node->_right_child != nullptr) {
                child_node = current_node->_right_child;
            } else {
                child_node = nullptr;
            }

            if (current_node == _root) {
                delete _root;
                _root = child_node;
                return;
            } else {
                if (route.back()->_left_child == current_node) {
                    route.back()->_left_child = child_node;
                } else {
                    route.back()->_right_child = child_node;
                }
                delete current_node;
            }

//            for (node<T>* &item : route) {
//                item->_height = 1 + std::max(get_height(item->_left_child),
//                                             get_height(item->_left_child));
//            }
            for(int i = route.size() - 1; i >= 0; --i) {
                route[i]->_height = 1 + std::max(get_height(route[i]->_left_child),
                                               get_height(route[i]->_right_child));
            }
        } else if (this->_comparator->compare(key, current_node->_data) < 0) {
            if (current_node->_left_child == nullptr) {
                return;
            } else {
                node_remove(current_node->_left_child, key, route);
            }
        } else {
            if (current_node->_right_child == nullptr) {
                return;
            } else {
                node_remove(current_node->_right_child, key, route);
            }
        }
    }

    void tree_fix_deletion(std::vector<node<T>*>& route) {
        if (route.size() < 3) {
            return;
        }
        while (route.size() >= 3) {
            if (get_balance_factor(route[route.size() - 3]) > 1 ||
                get_balance_factor(route[route.size() - 3]) < -1) {
                node<T> *grandchild_node = route.back();
                route.pop_back();
                node<T> *child_node = route.back();
                route.pop_back();
                node<T> *current_node = route.back();
                route.pop_back();
                //CASE 1: LEFT
                if (child_node == current_node->_left_child) {
                    //CASE 1.1: LEFT LEFT
                    if (grandchild_node == child_node->_left_child) {
                        if (_root == current_node) {
                            _root = child_node;
                        } else {
                            if (route.back()->_left_child == current_node) {
                                route.back()->_left_child = child_node;
                            } else {
                                route.back()->_right_child = child_node;
                            }
                        }
                        right_rotation(current_node);
                        route.push_back(child_node);
                        route.push_back(current_node);
                    }
                        //CASE 1.2: LEFT RIGHT
                    else {
                        if (_root == current_node) {
                            _root = grandchild_node;
                        } else {
                            if (route.back()->_left_child == current_node) {
                                route.back()->_left_child = grandchild_node;
                            } else {
                                route.back()->_right_child = grandchild_node;
                            }
                        }
                        left_rotation(child_node);
                        current_node->_left_child = grandchild_node;
                        right_rotation(current_node);
                        route.push_back(grandchild_node);
                        route.push_back(child_node);
                    }
                }
                    //CASE 2: RIGHT
                else {
                    //CASE 2.1: RIGHT LEFT
                    if (grandchild_node == child_node->_left_child) {
                        if (_root == current_node) {
                            _root = grandchild_node;
                        } else {
                            if (route.back()->_left_child == current_node) {
                                route.back()->_left_child = grandchild_node;
                            } else {
                                route.back()->_right_child = grandchild_node;
                            }
                        }
                        right_rotation(child_node);
                        current_node->_right_child = grandchild_node;
                        left_rotation(current_node);
                        route.push_back(grandchild_node);
                        route.push_back(child_node);
                    }
                        //CASE 2.2: RIGHT RIGHT
                    else {
                        if (_root == current_node) {
                            _root = child_node;
                        } else {
                            if (route.back()->_left_child == current_node) {
                                route.back()->_left_child = child_node;
                            } else {
                                route.back()->_right_child = child_node;
                            }
                        }
                        left_rotation(current_node);
                        route.push_back(child_node);
                        route.push_back(current_node);
                    }
                }
                route.back()->_height = 1 + std::max(get_height(route.back()->_left_child),
                                                     get_height(route.back()->_left_child));
            } else {
                route.pop_back();
            }
        }
    }

    void node_clear(node<T>* current_node) {
        if (current_node == nullptr) {
            return;
        } else {
            node_clear(current_node->_left_child);
            node_clear(current_node->_right_child);
            if (current_node->_left_child != nullptr) {
                delete current_node->_left_child;
            }
            if (current_node->_right_child != nullptr) {
                delete current_node->_right_child;
            }
        }
    }

    void node_print(node<T>* current_node) {
        if (current_node == nullptr) {
            return;
        }
        node_print(current_node->_left_child);
        std::cout << current_node->_data << " ";
        node_print(current_node->_right_child);
    }
};