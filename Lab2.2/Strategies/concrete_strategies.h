#pragma once
#include <string>
#include "strategy.h"

struct Date {
    int day;
    int month;
    int year;

    bool operator<(const Date& rhs) const {
        if(year != rhs.year) {
            return year < rhs.year;
        } else if(month != rhs.month) {
            return month < rhs.month;
        } else {
            return day < rhs.day;
        }
    }
    bool operator==(const Date& rhs) const {
        if(year != rhs.year) {
            return false;
        } else if(month != rhs.month) {
            return false;
        } else {
            return day == rhs.day;
        }
    }
    bool operator>(const Date& rhs) const {
        if(*this == rhs) {
            return false;
        } else {
            return !(*this < rhs);
        }
    }
    bool operator!=(const Date& rhs) const {
        return !(*this == rhs);
    }
};

struct Message {
    Date date;
	std::string name;
	std::string data;
};

class messages_strategy : public strategy<Message> {
public:
    int compare(const Message& lhs, const Message& rhs) override {
        if(lhs.date.year != rhs.date.year) {
            return lhs.date.year - rhs.date.year;
        } else if (lhs.date.month != rhs.date.month) {
            return lhs.date.month - rhs.date.month;
        } else if (lhs.date.day != rhs.date.day) {
            return lhs.date.day - rhs.date.day;
        } else if (lhs.name != rhs.name) {
            return lhs.name < rhs.name ? -1 : 1;
        } else if (lhs.data != rhs.data) {
            return lhs.data < rhs.data ? -1 : 1;
        } else {
            return 0;
        }
    }
};

template <typename T>
class number_strategy : strategy<T> {
    int compare(const T& lhs, const T& rhs) override {
        return lhs - rhs;
    }
};