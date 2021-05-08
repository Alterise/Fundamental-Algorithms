#pragma once
#include "date.h"

struct Arrangement {
    int number;
    Date start_date;
    Date end_date;
    double cost;
    bool is_finished;
};

struct Document {
    std::string name;
    std::string surname;
    std::string patronymic;
    std::vector<Arrangement> arrangements;
};