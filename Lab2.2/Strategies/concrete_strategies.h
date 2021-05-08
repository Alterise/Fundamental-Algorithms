#pragma once
#include <string>
#include <algorithm>
#include <cctype>
#include "strategy.h"
#include "messages.h"

class message_strategy : public strategy<Message> {
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

class message_strategy_date : public strategy<Message*> {
public:
    int compare(Message* const &lhs, Message* const &rhs) override {
        if(lhs->date.year != rhs->date.year) {
            return lhs->date.year - rhs->date.year;
        } else if (lhs->date.month != rhs->date.month) {
            return lhs->date.month - rhs->date.month;
        } else if (lhs->date.day != rhs->date.day) {
            return lhs->date.day - rhs->date.day;
        } else if (lhs != rhs) {
            return 1;
        } else {
            return 0;
        }
    }
};

//class message_strategy_username : public strategy<Message> {
//public:
//    int compare(const Message& lhs, const Message& rhs) override {
//        if (lhs.name != rhs.name) {
//            return lhs.name < rhs.name ? -1 : 1;
//        } else {
//            return 0;
//        }
//    }
//};
//
//class message_strategy_data : public strategy<Message> {
//public:
//    int compare(const Message& lhs, const Message& rhs) override {
//        std::string lhs_data = lhs.data;
//        std::string rhs_data = rhs.data;
//        std::transform(lhs_data.begin(), lhs_data.end(), lhs_data.begin(), tolower);
//        std::transform(rhs_data.begin(), rhs_data.end(), rhs_data.begin(), tolower);
//        if (lhs_data != rhs_data) {
//            return lhs_data < rhs_data ? -1 : 1;
//        } else {
//            return 0;
//        }
//    }
//};
//
//class message_strategy_username_date : public strategy<Message> {
//public:
//    int compare(const Message& lhs, const Message& rhs) override {
//        std::string lhs_name = lhs.name;
//        std::string rhs_name = rhs.name;
//        std::transform(lhs_name.begin(), lhs_name.end(), lhs_name.begin(), tolower);
//        std::transform(rhs_name.begin(), rhs_name.end(), rhs_name.begin(), tolower);
//        if (lhs_name != rhs_name) {
//            return lhs_name < rhs_name ? -1 : 1;
//        } else if(lhs.date.year != rhs.date.year) {
//            return lhs.date.year - rhs.date.year;
//        } else if (lhs.date.month != rhs.date.month) {
//            return lhs.date.month - rhs.date.month;
//        } else if (lhs.date.day != rhs.date.day) {
//            return lhs.date.day - rhs.date.day;
//        } else {
//            return 0;
//        }
//    }
//};

class int_strategy : public strategy<int> {
    int compare(const int& lhs, const int& rhs) override {
        return lhs - rhs;
    }
};

class int_ptr_strategy : public strategy<int*> {
    int compare(int* const &lhs, int* const &rhs) override {
        if ((*lhs - *rhs) == 0) {
            if (lhs == rhs) {
                return 0;
            } else {
                return 1;
            }
        } else {
            return *lhs - *rhs;
        }
    }
};

class int_strategy_reverse : public strategy<int> {
    int compare(const int& lhs, const int& rhs) override {
        return rhs - lhs;
    }
};

class int_ptr_strategy_reverse : public strategy<int*> {
    int compare(int* const &lhs, int* const &rhs) override {
        if ((*rhs - *lhs) == 0) {
            if (rhs == lhs) {
                return 0;
            } else {
                return 1;
            }
        } else {
            return *rhs - *lhs;
        }
    }
};

class int_strategy_odd_first : public strategy<int> {
    int compare(const int& lhs, const int& rhs) override {
        if ((lhs % 2) == (rhs % 2)) {
                return lhs - rhs;
        } else if (lhs % 2) {
            return -1;
        } else {
            return 1;
        }
    }
};

class int_ptr_strategy_odd_first : public strategy<int*> {
    int compare(int* const &lhs, int* const &rhs) override {
        if ((*lhs % 2) == (*rhs % 2)) {
            if ((*lhs - *rhs) == 0) {
                if (lhs == rhs) {
                    return 0;
                } else {
                    return 1;
                }
            } else {
                return *lhs - *rhs;
            }
        } else if (*lhs % 2) {
            return -1;
        } else {
            return 1;
        }
    }
};