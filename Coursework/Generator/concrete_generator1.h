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

    Document* generate() override {
        auto current_document = new Document;
        current_document->id = generate_long_long(100000000000, 999999999999);
        current_document->birth_date = generate_date(1901, 2006);
        current_document->fiscal_year = generate_int(current_document->birth_date.year + 14, 2020);
        current_document->filling_date = generate_date(current_document->fiscal_year + 1, 2021);
        current_document->tax_authority = generate_tax_authority();
        current_document->tax_authority_id = generate_int(1, 5000);
        current_document->surname = generate_type<std::string>({"Smith", "Johnson", "Williams", "Brown", "Jones",
                                                                       "Davis", "Taylor", "Martin", "Lee", "Lewis",
                                                                       "Walker", "Moore", "Jackson", "Robinson", "Thompson"});
        current_document->gender = generate_type<char>({'M', 'F'});
        if (current_document->gender == 'M') {
            current_document->name = generate_type<std::string>({"James", "Robert", "John", "Michael", "William",
                                                                 "David", "Richard", "Joseph", "Thomas", "Charles",
                                                                 "Christopher", "Daniel", "Matthew", "Anthony", "Mark"});
        } else {
            current_document->name = generate_type<std::string>({"Mary", "Patricia", "Jennifer", "Linda", "Elizabeth",
                                                                 "Barbara", "Susan", "Jessica", "Sarah", "Karen",
                                                                 "Nancy", "Lisa", "Betty", "Margaret", "Sandra"});
        }
        current_document->patronymic = generate_type<std::string>({"James", "Robert", "John", "Michael", "William",
                                                                   "David", "Richard", "Joseph", "Thomas", "Charles",
                                                                   "Christopher", "Daniel", "Matthew", "Anthony", "Mark"});
        if (current_document->gender == 'M') {
            current_document->patronymic += "ovich";
        } else {
            current_document->patronymic += "ovna";
        }
        current_document->citizenship = generate_citizenship({"Ambrosia", "Avalon", "Narnia", "Atlantis", "El Dorado",
                                                              "Laputa", "Loompaland", "Neverland", "Utopia", "Val Verde",
                                                              "Wonderland", "Zubrovka", "Wakanda", "Vulgaria", "Tazbekistan",
                                                              "San Serriffe", "Shangri-La", "Qumar", "Isle of Naboombu", "Costaguana"});
        current_document->passport_id = generate_long_long(1000000000, 9999999999);
        current_document->passport_date_of_issue = generate_date(current_document->birth_date.year + 14, 2021);
        current_document->postal_code = generate_int(100000, 999999);
        current_document->country = generate_type<std::string>({"Ambrosia", "Avalon", "Narnia", "Atlantis", "El Dorado",
                                                                       "Laputa", "Loompaland", "Neverland", "Utopia", "Val Verde",
                                                                       "Wonderland", "Zubrovka", "Wakanda", "Vulgaria", "Tazbekistan",
                                                                       "San Serriffe", "Shangri-La", "Qumar", "Isle of Naboombu", "Costaguana"});
        current_document->region = generate_type<std::string>({"North", "South", "East", "West",
                                                                      "North-East", "North-West", "South-East", "South-West"});
        current_document->city = generate_type<std::string>({"Springfield", "Gotham", "Twin Peaks", "Midgar", "Valhalla",
                                                             "Metropolis", "Mordor", "Hell", "Bikini Bottom", "Myst",
                                                             "Bluffington", "Arkham", "New New York", "Atlantis", "Hogsmeade",
                                                             "Wellsville", "Vice City", "Silent Hill", "New Vegas", "Venusville"});
        current_document->street = generate_street();
        current_document->house_number = generate_int(1, 200);
        current_document->apartment_number = generate_int(1, 1000);
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
        std::uniform_int_distribution<int> day_distribution(1, right_day_border);
        tmp.day = day_distribution(random_engine);
        return tmp;
    }

    std::string generate_tax_authority() {
        std::uniform_int_distribution<int> distribution(0, 15);
        std::string authority;
        std::vector<std::string> first_part = {"Office", "Department", "Bureau", "House", "Affiliate"};
        std::vector<std::string> second_part = {"Something", "Anything", "Everything", "Nothing"};
        std::vector<std::string> third_part = {"Amazing", "Awful", "Important", "Terrifying", "International",
                                               "Annoying", "Depressing", "Evil", "Mysterious", "Stupid", "Tiring"};
        authority = "The " + first_part[distribution(random_engine) % first_part.size()] + " of " +
                    second_part[distribution(random_engine) % second_part.size()] + " " +
                    third_part[distribution(random_engine) % third_part.size()];
        return authority;
    }

    std::string generate_street() {
        std::uniform_int_distribution<int> distribution(0, 15);
        std::string street;
        std::vector<std::string> first_part = {"Airport", "Water", "Barn", "Bay", "Bus",
                                               "Central", "China", "Corn", "Delta", "Dimitri",
                                               "Democracy", "Technology", "Flower", "Forest", "Gateway",
                                               "Greenpark", "Impressionist", "Innovation", "Industry", "Museum",
                                               "Old Port", "Plaza", "River", "Shopping", "Swamp"};
        std::vector<std::string> second_part = {"Street", "Avenue", "Road", "Lane", "Drive"};
        street = first_part[distribution(random_engine) % first_part.size()] + " " +
                 second_part[distribution(random_engine) % second_part.size()];
        return street;
    }

    template<typename T>
    T generate_type(const std::vector<T>& options) {
        std::uniform_int_distribution<int> distribution(0, (int)options.size() - 1);
        return options[distribution(random_engine)];
    }

    std::vector<std::string> generate_citizenship(const std::vector<std::string>& options) {
        std::vector<std::string> citizenship;
        std::uniform_int_distribution<int> distribution(0, (int)options.size() - 1);
        std::uniform_int_distribution<int> count_distribution(1, 100);
        auto count_checker = count_distribution(random_engine);
        if (count_checker > 0) {
            int a, b, c;
            do {
                a = distribution(random_engine);
                b = distribution(random_engine);
                c = distribution(random_engine);
            } while (a == b || a == c || c == b);
            citizenship.push_back(options[a]);
            citizenship.push_back(options[b]);
            citizenship.push_back(options[c]);
        } else if (count_checker > 80) {
            int a, b;
            do {
                a = distribution(random_engine);
                b = distribution(random_engine);
            } while (a == b);
            citizenship.push_back(options[a]);
            citizenship.push_back(options[b]);
        } else {
            citizenship.push_back(options[distribution(random_engine)]);
        }
        return citizenship;
    }
};