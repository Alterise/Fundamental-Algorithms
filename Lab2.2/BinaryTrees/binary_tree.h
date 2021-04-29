#pragma once
#include "../Strategies/strategy.h"

template<typename T>
class binary_tree
{
public:
	binary_tree(strategy<T>& comparator) {
		_comparator = comparator;
	}

	virtual void insert(const T& key) = 0;
	virtual void remove(const T& key) = 0;
	virtual binary_tree& search(const T& key) = 0;
private:
	strategy<T> _comparator;
};