#pragma once
#include <random>
#include <ctime>
#include "abstract_generator.h"

class concrete_generator1 : public abstract_generator {
private:
    std::mt19937 random_engine;
public:
    concrete_generator1 () {
        std::mt19937 random_engine_tmp(time(nullptr));
        random_engine = random_engine_tmp;
    }

    Document generate() override {
        Document current_document;
        current_document.id = generate_long_long(100000000000, 999999999999);
        current_document.birth_date = generate_date(1901, 2006);
        current_document.fiscal_year = generate_int(current_document.birth_date.year + 14, 2020);
        current_document.filling_date = generate_date(current_document.fiscal_year + 1, 2021);
        current_document.tax_authority;
        current_document.tax_authority_id = generate_int(1, 2000);
        current_document.surname;
        current_document.name;
        current_document.patronymic;
        current_document.gender = generate_gender();
        current_document.citizenship;
        current_document.passport_id = generate_long_long(1000000000, 9999999999);
        current_document.passport_date_of_issue = generate_date(current_document.birth_date.year + 14, 2021);
        current_document.postal_code = generate_int(100000, 999999);
        current_document.country;
        current_document.region;
        current_document.city;
        current_document.street;
        current_document.house_number = generate_int(1, 200);
        current_document.apartment_number = generate_int(1, 1000);
        return current_document;
    }

private:
    long long generate_long_long(long long left_border, long long right_border) {
        std::uniform_int_distribution<long long> distribution(left_border, right_border);
        return distribution(random_engine);
    }

    int generate_int(int left_border, int right_border) {
        std::uniform_int_distribution<int> distribution(left_border, right_border);
        return distribution(random_engine);
    }

    Date generate_date(int left_year_border, int right_year_border) {
        std::uniform_int_distribution<int> year_distribution(left_year_border, right_year_border);
        std::uniform_int_distribution<int> month_distribution(1, 12);
        Date tmp = {0, month_distribution(random_engine), year_distribution(random_engine)};
        int right_day_border;
        if (tmp.month == 2) {
            right_day_border = 28;
        } else if (tmp.month == 4 || tmp.month == 6 || tmp.month == 9 || tmp.month == 11) {
            right_day_border = 30;
        } else {
            right_day_border = 31;
        }
        std::uniform_int_distribution<int> day_distribution(0, right_day_border);
        tmp.day = day_distribution(random_engine);
    }

    std::string generate_tax_authority() {

    }

    std::string generate_name() {

    }

    std::string generate_surname() {

    }

    std::string generate_patronymic() {

    }

    char generate_gender() {
        std::uniform_int_distribution<int> distribution(0, 1);
        if (distribution(random_engine)) {
            return 'M';
        } else {
            return 'F';
        }
    }

    std::string generate_country() {

    }

    std::string generate_region() {

    }

    std::string generate_city() {

    }

    std::string generate_street() {

    }
};