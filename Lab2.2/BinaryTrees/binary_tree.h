#pragma once
#include "../Strategies/strategy.h"

template<typename T>
class binary_tree
{
public:
	explicit binary_tree(strategy<T>* comparator) {
		_comparator = comparator;
	}

	virtual void insert(const T&) = 0;
	virtual void remove(const T&) = 0;
	virtual bool search(const T&) = 0;

protected:
	strategy<T>* _comparator;
};