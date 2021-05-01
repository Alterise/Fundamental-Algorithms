#pragma once
#include <string>

struct Date {
    unsigned int day;
    unsigned int month;
    unsigned int year;

    bool operator<(const Date& rhs) {
        if(year != rhs.year) {
            return year < rhs.year;
        } else if(month != rhs.month) {
            return month < rhs.month;
        } else if(day != rhs.day) {
            return day < rhs.day;
        } else {
            return false;
        }
    }
};

struct Message {
    Date date;
	std::string name;
	std::string data;
};

class messages_strategy
{
public:
    bool compare(const Message& lhs, const Message& rhs) {
        return true;
    }
};