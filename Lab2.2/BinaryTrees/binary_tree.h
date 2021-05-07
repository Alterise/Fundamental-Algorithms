#pragma once
#include "strategy.h"

template<typename T>
class binary_tree
{
public:
	explicit binary_tree(strategy<T>* comparator, bool allow_duplicates) {
		_comparator = comparator;
		_allow_duplicates = allow_duplicates;
	}

    ~binary_tree() {
	    delete _comparator;
	}

	virtual void insert(const T&) = 0;
	virtual void remove(const T&) = 0;
	virtual T* search(const T&) = 0;

protected:
	strategy<T>* _comparator;
	bool _allow_duplicates;
};