#pragma once
#include <vector>
#include "binary_tree.h"

template <typename T>
class RB_tree : public binary_tree<T>
{
private:
    template <typename J> class node;
    node<T>* _root;

public:
    explicit RB_tree(strategy<T>* comparator, bool allow_duplicates = true) : binary_tree<T>(comparator, allow_duplicates) {
        _root = nullptr;
    }

    ~RB_tree() {
        node_clear(_root);
        if (_root != nullptr) {
            delete _root;
        }
    }

    bool insert(const T& key) override {
        if (_root == nullptr) {
            _root = new node<T>(key, true);
            return true;
        } else {
            std::vector<node<T>*> route;
            if (node_insert(_root, key, route)) {
                tree_fix_insertion(route);
                _root->_is_black = true;
                return true;
            } else {
                return false;
            }
        }
    }

    bool remove(const T& key) override {
        std::vector<node<T>*> route;
        return node_remove(_root, key, route);
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

    bool node_insert(node<T>* current_node, const T& key, std::vector<node<T>*>& route) {
        route.push_back(current_node);
        if (!(this->_allow_duplicates) && (this->_comparator->compare(key, current_node->_data) == 0)) {
            return false;
        }
        if (this->_comparator->compare(key, current_node->_data) < 0) {
            if (current_node->_left_child == nullptr) {
                current_node->_left_child = new node<T>(key);
                route.push_back(current_node->_left_child);
            } else {
                return node_insert(current_node->_left_child, key, route);
            }
        } else {
            if (current_node->_right_child == nullptr) {
                current_node->_right_child = new node<T>(key);
                route.push_back(current_node->_right_child);
            } else {
                return node_insert(current_node->_right_child, key, route);
            }
        }
    }

    void tree_fix_insertion(std::vector<node<T>*>& route) {
        if (route.size() < 3) {
            return;
        }
        node<T>* current_node = route.back();
        route.pop_back();
        node<T>* parent_node = route.back();
        route.pop_back();
        node<T>* grandparent_node;
        bool uncle_is_black;
        grandparent_node = route.back();
        route.pop_back();
        if (grandparent_node->_left_child != parent_node) {
            if (grandparent_node->_left_child != nullptr) {
                uncle_is_black = grandparent_node->_left_child->_is_black;
            } else {
                uncle_is_black = true;
            }
        } else {
            if (grandparent_node->_right_child != nullptr) {
                uncle_is_black = grandparent_node->_right_child->_is_black;
            } else {
                uncle_is_black = true;
            }
        }
        // Case 0: Parent is black
        if (parent_node->_is_black) {
            return;
        }
        // Case 1: Uncle is red
        if (!uncle_is_black) {
            if (grandparent_node->_left_child != parent_node) {
                grandparent_node->_left_child->_is_black = true;
            } else {
                grandparent_node->_right_child->_is_black = true;
            }
            parent_node->_is_black = true;
            grandparent_node->_is_black = false;
            route.push_back(grandparent_node);
            tree_fix_insertion(route);
            return;
        }
        // Case 2: Uncle is black
        else {
            // Case 2.1: Left parent
            if (grandparent_node->_left_child == parent_node) {
                // Case 2.1.1: Right child
                if (parent_node->_right_child == current_node) {
                    grandparent_node->_left_child = current_node->_right_child;
                    parent_node->_right_child = current_node->_left_child;
                    current_node->_left_child = parent_node;
                    current_node->_right_child = grandparent_node;
                    grandparent_node->_is_black = !grandparent_node->_is_black;
                    current_node->_is_black = !current_node->_is_black;
                    if (!route.empty()) {
                        if (route.back()->_left_child == grandparent_node) {
                            route.back()->_left_child = current_node;
                        } else {
                            route.back()->_right_child = current_node;
                        }
                    }
                    if (_root == grandparent_node) {
                        _root = current_node;
                    }
                }
                // Case 2.1.2: Left child
                else {
                    grandparent_node->_left_child = parent_node->_right_child;
                    parent_node->_right_child = grandparent_node;
                    if (!route.empty()) {
                        if (route.back()->_left_child == grandparent_node) {
                            route.back()->_left_child = parent_node;
                        } else {
                            route.back()->_right_child = parent_node;
                        }
                    }
                    grandparent_node->_is_black = !grandparent_node->_is_black;
                    parent_node->_is_black = !parent_node->_is_black;
                    if (_root == grandparent_node) {
                        _root = parent_node;
                    }
                }
            }
            // Case 2.2: Right parent
            else {
                // Case 2.2.1: Left child
                if (parent_node->_left_child == current_node) {
                    grandparent_node->_right_child = current_node->_left_child;
                    parent_node->_left_child = current_node->_right_child;
                    current_node->_right_child = parent_node;
                    current_node->_left_child = grandparent_node;
                    grandparent_node->_is_black = !grandparent_node->_is_black;
                    current_node->_is_black = !current_node->_is_black;
                    if (!route.empty()) {
                        if (route.back()->_right_child == grandparent_node) {
                            route.back()->_right_child = current_node;
                        } else {
                            route.back()->_left_child = current_node;
                        }
                    }
                    if (_root == grandparent_node) {
                        _root = current_node;
                    }
                }
                // Case 2.2.2: Right child
                else {
                    grandparent_node->_right_child = parent_node->_left_child;
                    parent_node->_left_child = grandparent_node;
                    if (!route.empty()) {
                        if (route.back()->_right_child == grandparent_node) {
                            route.back()->_right_child = parent_node;
                        } else {
                            route.back()->_left_child = parent_node;
                        }
                    }
                    grandparent_node->_is_black = !grandparent_node->_is_black;
                    parent_node->_is_black = !parent_node->_is_black;
                    if (_root == grandparent_node) {
                        _root = parent_node;
                    }
                }
            }
        }
    }

    bool node_remove(node<T>* current_node, const T& key, std::vector<node<T>*>& route) {
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
            // Case 0: Removing root with < 2 children
            if (current_node == _root) {
                delete _root;
                _root = child_node;
                return true;
            }
            node<T>* parent_node = route.back();
            if (parent_node->_left_child == current_node) {
                parent_node->_left_child = child_node;
            } else {
                parent_node->_right_child = child_node;
            }
            bool is_child_black;
            if (child_node != nullptr) {
                is_child_black = child_node->_is_black;
            } else {
                is_child_black = true;
            }
            // Case 1: Different colors of removable node and it's parent
            if (is_child_black != current_node->_is_black) {
                if (child_node != nullptr) {
                    child_node->_is_black = true;
                }
                delete current_node;
                return true;
            }
            // Case 2: Same colors of removable node and it's parent
            else {
                delete current_node;
                route.push_back(child_node);
                tree_fix_deletion(route);
            }
            _root->_is_black = true;
            return true;
        } else if (this->_comparator->compare(key, current_node->_data) < 0) {
            if (current_node->_left_child == nullptr) {
                return false;
            } else {
                node_remove(current_node->_left_child, key, route);
            }
        } else {
            if (current_node->_right_child == nullptr) {
                return false;
            } else {
                node_remove(current_node->_right_child, key, route);
            }
        }
    }

    void tree_fix_deletion(std::vector<node<T>*>& route) {
        if (route.size() < 2) {
            return;
        }
        node<T>* current_node = route.back();
        route.pop_back();
        node<T>* parent_node = route.back();
        route.pop_back();
        node<T>* sibling_node;
        if (parent_node->_left_child == current_node) {
            sibling_node = parent_node->_right_child;
        } else {
            sibling_node = parent_node->_left_child;
        }
        bool is_sibling_has_red_child = false;
        bool is_left_child_red = false;
        bool is_right_child_red = false;
        if (sibling_node->_left_child != nullptr) {
            if (!sibling_node->_left_child->_is_black) {
                is_sibling_has_red_child = true;
                is_left_child_red = true;
            }
        }
        if (sibling_node->_right_child != nullptr) {
            if (!sibling_node->_right_child->_is_black) {
                is_sibling_has_red_child = true;
                is_right_child_red = true;
            }
        }
        //Case 2.1: Sibling is black and at least on of it's children is red
        if (is_sibling_has_red_child) {
            // Case 2.1.1: Left sibling
            if (parent_node->_right_child == current_node) {
                // Case 2.1.1.1: Left child
                if (is_left_child_red) {
                    if (!sibling_node->_left_child->_is_black) {
                        parent_node->_left_child = sibling_node->_right_child;
                        sibling_node->_right_child = parent_node;
                        sibling_node->_left_child->_is_black = true;
                        if(!parent_node->_is_black) {
                            parent_node->_is_black = true;
                            sibling_node->_is_black = false;
                        }
                        if (_root == parent_node) {
                            _root = sibling_node;
                        } else {
                            if (route.back()->_right_child == parent_node) {
                                route.back()->_right_child = sibling_node;
                            } else {
                                route.back()->_left_child = sibling_node;
                            }
                        }
                    }
                }
                // Case 2.1.1.2: Right child
                else {
                    parent_node->_left_child = sibling_node->_right_child->_right_child;
                    sibling_node->_right_child->_right_child = parent_node;
                    node<T>* tmp = sibling_node->_right_child->_left_child;
                    sibling_node->_right_child->_left_child = sibling_node;
                    if(parent_node->_is_black) {
                        sibling_node->_right_child->_is_black = true;
                    } else {
                        parent_node->_is_black = true;
                    }
                    parent_node->_is_black = true;
                    if (_root == parent_node) {
                        _root = sibling_node->_right_child;
                    } else {
                        if (route.back()->_right_child == parent_node) {
                            route.back()->_right_child = sibling_node->_right_child;
                        } else {
                            route.back()->_left_child = sibling_node->_right_child;
                        }
                    }
                    sibling_node->_right_child = tmp;
                }
            }
            // Case 2.1.2: Right sibling
            else {
                // Case 2.1.2.1: Right child
                if (is_right_child_red) {
                    parent_node->_right_child = sibling_node->_left_child;
                    sibling_node->_left_child = parent_node;
                    sibling_node->_right_child->_is_black = true;
                    if(!parent_node->_is_black) {
                        parent_node->_is_black = true;
                        sibling_node->_is_black = false;
                    }
                    if (_root == parent_node) {
                        _root = sibling_node;
                    } else {
                        if (route.back()->_left_child == parent_node) {
                            route.back()->_left_child = sibling_node;
                        } else {
                            route.back()->_right_child = sibling_node;
                        }
                    }
                }
                // Case 2.1.2.2: Left child
                else {
                    parent_node->_right_child = sibling_node->_left_child->_left_child;
                    sibling_node->_left_child->_left_child = parent_node;
                    node<T>* tmp = sibling_node->_left_child->_right_child;
                    sibling_node->_left_child->_right_child = sibling_node;
                    if(parent_node->_is_black) {
                        sibling_node->_left_child->_is_black = true;
                    } else {
                        parent_node->_is_black = true;
                    }
                    if (_root == parent_node) {
                        _root = sibling_node->_left_child;
                    } else {
                        if (route.back()->_left_child == parent_node) {
                            route.back()->_left_child = sibling_node->_left_child;
                        } else {
                            route.back()->_right_child = sibling_node->_left_child;
                        }
                    }
                    sibling_node->_left_child = tmp;
                }
            }
            return;
        }
        // Case 2.2: Sibling is black and it's both children are black
        else if (sibling_node->_is_black) {
            sibling_node->_is_black = false;
            if (parent_node->_is_black) {
                route.push_back(parent_node);
                tree_fix_deletion(route);
            } else {
                parent_node->_is_black = true;
            }
            return;
        }
        // Case 2.3: Sibling is red
        else {
            // Case 2.3.1: Left sibling
            if (parent_node->_right_child == current_node) {
                parent_node->_left_child = sibling_node->_right_child;
                sibling_node->_right_child = parent_node;
                sibling_node->_is_black = true;
                parent_node->_is_black = false;
                if (!route.empty()) {
                    if (route.back()->_right_child == parent_node) {
                        route.back()->_right_child = sibling_node;
                    } else {
                        route.back()->_left_child = sibling_node;
                    }
                } else {
                    _root = sibling_node;
                }
                route.push_back(sibling_node);
                route.push_back(parent_node);
                route.push_back(current_node);
                tree_fix_deletion(route);
            }
            // Case 2.3.2: Right sibling
            else {
                parent_node->_right_child = sibling_node->_left_child;
                sibling_node->_left_child = parent_node;
                sibling_node->_is_black = true;
                parent_node->_is_black = false;
                if (!route.empty()) {
                    if (route.back()->_left_child == parent_node) {
                        route.back()->_left_child = sibling_node;
                    } else {
                        route.back()->_right_child = sibling_node;
                    }
                } else {
                    _root = sibling_node;
                }
                route.push_back(sibling_node);
                route.push_back(parent_node);
                route.push_back(current_node);
                tree_fix_deletion(route);
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