#pragma once
#include <string>

using namespace std;

class TeX_convertible
{
	virtual string convert() const = 0;
};