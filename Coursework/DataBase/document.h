#pragma once
#include <vector>
#include <string>
#include "date.h"

struct document {
    long long ID; // 1
    int fiscal_year;
    std::string tax_authority; // 2
    int tax_authority_id; // 2

    std::string surname; // 3
    std::string name; // 3
    std::string patronymic; // 3
    Date birth_date;
    char gender;

    std::vector<std::string> citizenship;

    int passport_id; // 4
    Date passport_date_of_issue;

    int postal_code;
    std::string country;
    std::string region;
    std::string city;
    std::string street;
    int house_number;
    int apartment_number;

    Date filling_date; // 5
};