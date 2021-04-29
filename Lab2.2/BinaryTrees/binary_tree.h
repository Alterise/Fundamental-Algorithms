#pragma once
#include "../Strategies/strategy.h"

template<typename T>
class binary_tree
{
public:
	explicit binary_tree(strategy<T>& comparator) {
		_comparator = comparator;
	}

	virtual void insert(const T& key, const strategy<T>& comparator) = 0;
	virtual void remove(const T& key, const strategy<T>& comparator) = 0;
	virtual binary_tree& search(const T& key, const strategy<T>& comparator) = 0;

protected:
	strategy<T> _comparator;
};