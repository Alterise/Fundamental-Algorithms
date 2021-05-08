#pragma once
#include <string>
#include <algorithm>
#include <cctype>
#include "strategy.h"
#include "messages.h"
#include "documents.h"

class documents_strategy : public strategy<Document> {
public:
    int compare(const Document& lhs, const Document& rhs) override {
        if (lhs.name != rhs.name) {
            return lhs.name < rhs.name ? -1 : 1;
        } else if (lhs.surname != rhs.surname) {
            return lhs.surname < rhs.surname ? -1 : 1;
        } else if (lhs.patronymic != rhs.patronymic) {
            return lhs.patronymic < rhs.patronymic ? -1 : 1;
        } else if (lhs.arrangements.size() != rhs.arrangements.size()) {
            return ((int)lhs.arrangements.size() - (int)rhs.arrangements.size());
        } else {
            for (int i = 0; i < lhs.arrangements.size(); ++i) {
                if (lhs.arrangements[i].cost != rhs.arrangements[i].cost) {
                    return (lhs.arrangements[i].cost - rhs.arrangements[i].cost);
                } else if (lhs.arrangements[i].number != rhs.arrangements[i].number) {
                    return (lhs.arrangements[i].number - rhs.arrangements[i].number);
                } else if (lhs.arrangements[i].start_date != rhs.arrangements[i].start_date) {
                    return ((lhs.arrangements[i].start_date < rhs.arrangements[i].start_date) ? -1 : 1);
                } else if (lhs.arrangements[i].is_finished != lhs.arrangements[i].is_finished) {
                    return lhs.arrangements[i].is_finished ? -1 : 1;
                } else if (lhs.arrangements[i].end_date != rhs.arrangements[i].end_date) {
                    return ((lhs.arrangements[i].end_date < rhs.arrangements[i].end_date) ? -1 : 1);
                }
            }
            return 0;
        }
    }
};

class documents_ptr_strategy : public strategy<Document*> {
public:
    int compare(Document* const &lhs, Document* const &rhs) override {
        if (lhs->name != rhs->name) {
            return lhs->name < rhs->name ? -1 : 1;
        } else if (lhs->surname != rhs->surname) {
            return lhs->surname < rhs->surname ? -1 : 1;
        } else if (lhs->patronymic != rhs->patronymic) {
            return lhs->patronymic < rhs->patronymic ? -1 : 1;
        } else if (lhs->arrangements.size() != rhs->arrangements.size()) {
            return ((int)lhs->arrangements.size() - (int)rhs->arrangements.size());
        } else {
            for (int i = 0; i < lhs->arrangements.size(); ++i) {
                if (lhs->arrangements[i].cost != rhs->arrangements[i].cost) {
                    return (int)(lhs->arrangements[i].cost - rhs->arrangements[i].cost);
                } else if (lhs->arrangements[i].number != rhs->arrangements[i].number) {
                    return (lhs->arrangements[i].number - rhs->arrangements[i].number);
                } else if (lhs->arrangements[i].start_date != rhs->arrangements[i].start_date) {
                    return ((lhs->arrangements[i].start_date < rhs->arrangements[i].start_date) ? -1 : 1);
                } else if (lhs->arrangements[i].is_finished != lhs->arrangements[i].is_finished) {
                    return lhs->arrangements[i].is_finished ? -1 : 1;
                } else if (lhs->arrangements[i].end_date != rhs->arrangements[i].end_date) {
                    return ((lhs->arrangements[i].end_date < rhs->arrangements[i].end_date) ? -1 : 1);
                }
            }
            return 0;
        }
    }
};

class documents_ptr_strategy_id : public strategy<Document*> {
public:
    int compare(Document* const &lhs, Document* const &rhs) override {
        if (lhs->name != rhs->name) {
            return lhs->name < rhs->name ? -1 : 1;
        } else if (lhs->surname != rhs->surname) {
            return lhs->surname < rhs->surname ? -1 : 1;
        } else if (lhs->patronymic != rhs->patronymic) {
            return lhs->patronymic < rhs->patronymic ? -1 : 1;
        } else if (lhs->arrangements.size() != rhs->arrangements.size()) {
            return ((int)lhs->arrangements.size() - (int)rhs->arrangements.size());
        } else {
            for (int i = 0; i < lhs->arrangements.size(); ++i) {
                if (lhs->arrangements[i].number != rhs->arrangements[i].number) {
                    return (lhs->arrangements[i].number - rhs->arrangements[i].number);
                }
            }
            return 0;
        }
    }
};

class documents_ptr_strategy_date : public strategy<Document*> {
public:
    int compare(Document* const &lhs, Document* const &rhs) override {
        if (lhs->arrangements.size() != rhs->arrangements.size()) {
            return ((int)lhs->arrangements.size() - (int)rhs->arrangements.size());
        } else {
            for (int i = 0; i < lhs->arrangements.size(); ++i) {
                if (lhs->arrangements[i].start_date != rhs->arrangements[i].start_date) {
                    return ((lhs->arrangements[i].start_date < rhs->arrangements[i].start_date) ? -1 : 1);
                } else if (lhs->arrangements[i].is_finished != lhs->arrangements[i].is_finished) {
                    return lhs->arrangements[i].is_finished ? -1 : 1;
                } else if (lhs->arrangements[i].end_date != rhs->arrangements[i].end_date) {
                    return ((lhs->arrangements[i].end_date < rhs->arrangements[i].end_date) ? -1 : 1);
                }
            }
            return 0;
        }
    }
};

class documents_ptr_strategy_cost : public strategy<Document*> {
public:
    int compare(Document* const &lhs, Document* const &rhs) override {
        if (lhs->name != rhs->name) {
            return lhs->name < rhs->name ? -1 : 1;
        } else if (lhs->surname != rhs->surname) {
            return lhs->surname < rhs->surname ? -1 : 1;
        } else if (lhs->patronymic != rhs->patronymic) {
            return lhs->patronymic < rhs->patronymic ? -1 : 1;
        } else if (lhs->arrangements.size() != rhs->arrangements.size()) {
            return ((int)lhs->arrangements.size() - (int)rhs->arrangements.size());
        } else {
            for (int i = 0; i < lhs->arrangements.size(); ++i) {
                if (lhs->arrangements[i].cost != rhs->arrangements[i].cost) {
                    return (int)(lhs->arrangements[i].cost - rhs->arrangements[i].cost);
                }
            }
            return 0;
        }
    }
};

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

class message_ptr_strategy_date : public strategy<Message*> {
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

class message_ptr_strategy_username : public strategy<Message*> {
public:
    int compare(Message* const &lhs, Message* const &rhs) override {
        if (lhs->name != rhs->name) {
            return lhs->name < rhs->name ? -1 : 1;
        } else {
            return 0;
        }
    }
};

class message_ptr_strategy_data : public strategy<Message*> {
public:
    int compare(Message* const &lhs, Message* const &rhs) override {
        std::string lhs_data = lhs->data;
        std::string rhs_data = rhs->data;
        std::transform(lhs_data.begin(), lhs_data.end(), lhs_data.begin(), tolower);
        std::transform(rhs_data.begin(), rhs_data.end(), rhs_data.begin(), tolower);
        if (lhs_data != rhs_data) {
            return lhs_data < rhs_data ? -1 : 1;
        } else {
            return 0;
        }
    }
};

class message_ptr_strategy_username_date : public strategy<Message*> {
public:
    int compare(Message* const &lhs, Message* const &rhs) override {
        std::string lhs_name = lhs->name;
        std::string rhs_name = rhs->name;
        std::transform(lhs_name.begin(), lhs_name.end(), lhs_name.begin(), tolower);
        std::transform(rhs_name.begin(), rhs_name.end(), rhs_name.begin(), tolower);
        if (lhs_name != rhs_name) {
            return lhs_name < rhs_name ? -1 : 1;
        } else if(lhs->date.year != rhs->date.year) {
            return lhs->date.year - rhs->date.year;
        } else if (lhs->date.month != rhs->date.month) {
            return lhs->date.month - rhs->date.month;
        } else if (lhs->date.day != rhs->date.day) {
            return lhs->date.day - rhs->date.day;
        } else {
            return 0;
        }
    }
};

class int_strategy : public strategy<int> {
    int compare(const int& lhs, const int& rhs) override {
        return lhs - rhs;
    }
};

class int_ptr_strategy : public strategy<int*> {
    int compare(int* const &lhs, int* const &rhs) override {
        return *lhs - *rhs;
    }
};

class int_strategy_reverse : public strategy<int> {
    int compare(const int& lhs, const int& rhs) override {
        return rhs - lhs;
    }
};

class int_ptr_strategy_reverse : public strategy<int*> {
    int compare(int* const &lhs, int* const &rhs) override {
        return *rhs - *lhs;
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
            return *lhs - *rhs;
        } else if (*lhs % 2) {
            return -1;
        } else {
            return 1;
        }
    }
};