#pragma once
#include <string>
#include "strategy.h"

struct message {
	std::string date;
	std::string name;
	std::string data;
};
template <typename T>
class messages_strategy : public strategy<T>
{

};