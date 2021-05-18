#pragma once
#include <map>
#include <vector>
#include <algorithm>
#include "document.h"
#include "date.h"

template<typename T>
struct stat_elem {
    T data;
    int abs_count;
    double rel_count;

    bool operator<(const stat_elem<T>& rhs) const {
        if(abs_count < rhs.abs_count) {
            return true;
        } else {
            return false;
        }
    }
};

class statistics_table {
private:
    int _count;
    std::map<long long, int> id_stat;
    std::map<int, int> fiscal_year_stat;
    std::map<std::string, int> tax_authority_stat;
    std::map<int, int> tax_authority_id_stat;
    std::map<std::string, int> surname_stat;
    std::map<std::string, int> name_stat;
    std::map<std::string, int> patronymic_stat;
    std::map<Date, int> birth_date_stat;
    std::map<char, int> gender_stat;
    std::map<std::string, int> citizenship_stat;
    std::map<long long, int> passport_id_stat;
    std::map<Date, int> passport_date_of_issue_stat;
    std::map<int, int> postal_code_stat;
    std::map<std::string, int> country_stat;
    std::map<std::string, int> region_stat;
    std::map<std::string, int> city_stat;
    std::map<std::string, int> street_stat;
    std::map<int, int> house_number_stat;
    std::map<int, int> apartment_number_stat;
    std::map<Date, int> filling_date_stat;
public:
    void insert(const Document& current_document) {
        _count++;
        if (id_stat.find(current_document.id) != id_stat.end()) {
            id_stat[current_document.id]++;
        } else {
            id_stat.insert({current_document.id, 0});
        }

        if (fiscal_year_stat.find(current_document.fiscal_year) != fiscal_year_stat.end()) {
            fiscal_year_stat[current_document.fiscal_year]++;
        } else {
            fiscal_year_stat.insert({current_document.fiscal_year, 0});
        }

        if (tax_authority_stat.find(current_document.tax_authority) != tax_authority_stat.end()) {
            tax_authority_stat[current_document.tax_authority]++;
        } else {
            tax_authority_stat.insert({current_document.tax_authority, 0});
        }

        if (tax_authority_id_stat.find(current_document.tax_authority_id) != tax_authority_id_stat.end()) {
            tax_authority_id_stat[current_document.tax_authority_id]++;
        } else {
            tax_authority_id_stat.insert({current_document.tax_authority_id, 0});
        }

        if (surname_stat.find(current_document.surname) != surname_stat.end()) {
            surname_stat[current_document.surname]++;
        } else {
            surname_stat.insert({current_document.surname, 0});
        }

        if (name_stat.find(current_document.name) != name_stat.end()) {
            name_stat[current_document.name]++;
        } else {
            name_stat.insert({current_document.name, 0});
        }

        if (patronymic_stat.find(current_document.patronymic) != patronymic_stat.end()) {
            patronymic_stat[current_document.patronymic]++;
        } else {
            patronymic_stat.insert({current_document.patronymic, 0});
        }

        if (birth_date_stat.find(current_document.birth_date) != birth_date_stat.end()) {
            birth_date_stat[current_document.birth_date]++;
        } else {
            birth_date_stat.insert({current_document.birth_date, 0});
        }

        if (gender_stat.find(current_document.gender) != gender_stat.end()) {
            gender_stat[current_document.gender]++;
        } else {
            gender_stat.insert({current_document.gender, 0});
        }

        for (const auto &item : current_document.citizenship) {
            if (citizenship_stat.find(item) != citizenship_stat.end()) {
                citizenship_stat[item]++;
            } else {
                citizenship_stat.insert({item, 0});
            }
        }

        if (passport_id_stat.find(current_document.passport_id) != passport_id_stat.end()) {
            passport_id_stat[current_document.passport_id]++;
        } else {
            passport_id_stat.insert({current_document.passport_id, 0});
        }

        if (passport_date_of_issue_stat.find(current_document.passport_date_of_issue) != passport_date_of_issue_stat.end()) {
            passport_date_of_issue_stat[current_document.passport_date_of_issue]++;
        } else {
            passport_date_of_issue_stat.insert({current_document.passport_date_of_issue, 0});
        }

        if (postal_code_stat.find(current_document.postal_code) != postal_code_stat.end()) {
            postal_code_stat[current_document.postal_code]++;
        } else {
            postal_code_stat.insert({current_document.postal_code, 0});
        }

        if (country_stat.find(current_document.country) != country_stat.end()) {
            country_stat[current_document.country]++;
        } else {
            country_stat.insert({current_document.country, 0});
        }

        if (region_stat.find(current_document.region) != region_stat.end()) {
            region_stat[current_document.region]++;
        } else {
            region_stat.insert({current_document.region, 0});
        }

        if (city_stat.find(current_document.city) != city_stat.end()) {
            city_stat[current_document.city]++;
        } else {
            city_stat.insert({current_document.city, 0});
        }

        if (street_stat.find(current_document.street) != street_stat.end()) {
            street_stat[current_document.street]++;
        } else {
            street_stat.insert({current_document.street, 0});
        }

        if (house_number_stat.find(current_document.house_number) != house_number_stat.end()) {
            house_number_stat[current_document.house_number]++;
        } else {
            house_number_stat.insert({current_document.house_number, 0});
        }

        if (apartment_number_stat.find(current_document.apartment_number) != apartment_number_stat.end()) {
            apartment_number_stat[current_document.apartment_number]++;
        } else {
            apartment_number_stat.insert({current_document.apartment_number, 0});
        }

        if (filling_date_stat.find(current_document.filling_date) != filling_date_stat.end()) {
            filling_date_stat[current_document.filling_date]++;
        } else {
            filling_date_stat.insert({current_document.filling_date, 0});
        }
    }

    void remove(const Document& current_document) {
        _count--;
        if (id_stat[current_document.id] == 1) {
            id_stat.erase(current_document.id);
        } else {
            id_stat[current_document.id]--;
        }

        if (fiscal_year_stat[current_document.fiscal_year] == 1) {
            fiscal_year_stat.erase(current_document.fiscal_year);
        } else {
            fiscal_year_stat[current_document.fiscal_year]--;
        }

        if (tax_authority_stat[current_document.tax_authority] == 1) {
            tax_authority_stat.erase(current_document.tax_authority);
        } else {
            tax_authority_stat[current_document.tax_authority]--;
        }

        if (tax_authority_id_stat[current_document.tax_authority_id] == 1) {
            tax_authority_id_stat.erase(current_document.tax_authority_id);
        } else {
            tax_authority_id_stat[current_document.tax_authority_id]--;
        }

        if (surname_stat[current_document.surname] == 1) {
            surname_stat.erase(current_document.surname);
        } else {
            surname_stat[current_document.surname]--;
        }

        if (name_stat[current_document.name] == 1) {
            name_stat.erase(current_document.name);
        } else {
            name_stat[current_document.name]--;
        }

        if (patronymic_stat[current_document.patronymic] == 1) {
            patronymic_stat.erase(current_document.patronymic);
        } else {
            patronymic_stat[current_document.patronymic]--;
        }

        if (birth_date_stat[current_document.birth_date] == 1) {
            birth_date_stat.erase(current_document.birth_date);
        } else {
            birth_date_stat[current_document.birth_date]--;
        }

        if (gender_stat[current_document.gender] == 1) {
            gender_stat.erase(current_document.gender);
        } else {
            gender_stat[current_document.gender]--;
        }

        for (const auto &item : current_document.citizenship) {
            if (citizenship_stat[item] == 1) {
                citizenship_stat.erase(item);
            } else {
                citizenship_stat[item]--;
            }
        }

        if (passport_id_stat[current_document.passport_id] == 1) {
            passport_id_stat.erase(current_document.passport_id);
        } else {
            passport_id_stat[current_document.passport_id]--;
        }

        if (passport_date_of_issue_stat[current_document.passport_date_of_issue] == 1) {
            passport_date_of_issue_stat.erase(current_document.passport_date_of_issue);
        } else {
            passport_date_of_issue_stat[current_document.passport_date_of_issue]--;
        }

        if (postal_code_stat[current_document.postal_code] == 1) {
            postal_code_stat.erase(current_document.postal_code);
        } else {
            postal_code_stat[current_document.postal_code]--;
        }

        if (country_stat[current_document.country] == 1) {
            country_stat.erase(current_document.country);
        } else {
            country_stat[current_document.country]--;
        }

        if (region_stat[current_document.region] == 1) {
            region_stat.erase(current_document.region);
        } else {
            region_stat[current_document.region]--;
        }

        if (city_stat[current_document.city] == 1) {
            city_stat.erase(current_document.city);
        } else {
            city_stat[current_document.city]--;
        }

        if (street_stat[current_document.street] == 1) {
            street_stat.erase(current_document.street);
        } else {
            street_stat[current_document.street]--;
        }

        if (house_number_stat[current_document.house_number] == 1) {
            house_number_stat.erase(current_document.house_number);
        } else {
            house_number_stat[current_document.house_number]--;
        }

        if (apartment_number_stat[current_document.apartment_number] == 1) {
            apartment_number_stat.erase(current_document.apartment_number);
        } else {
            apartment_number_stat[current_document.apartment_number]--;
        }

        if (filling_date_stat[current_document.filling_date] == 1) {
            filling_date_stat.erase(current_document.filling_date);
        } else {
            filling_date_stat[current_document.filling_date]--;
        }
    }

    std::vector<stat_elem<long long>> get_id_stat() {
        std::vector<stat_elem<long long>> stat_vector;
        for (auto &[data, count] : id_stat) {
            stat_vector.push_back({data, count, (double)count/(double)_count});
        }
        sort(stat_vector.begin(), stat_vector.end());
        return stat_vector;
    }

    std::vector<stat_elem<int>> get_fiscal_year_stat() {
        std::vector<stat_elem<int>> stat_vector;
        for (auto &[data, count] : fiscal_year_stat) {
            stat_vector.push_back({data, count, (double)count/(double)_count});
        }
        sort(stat_vector.begin(), stat_vector.end());
        return stat_vector;
    }

    std::vector<stat_elem<std::string>> get_tax_authority_stat() {
        std::vector<stat_elem<std::string>> stat_vector;
        for (auto &[data, count] : tax_authority_stat) {
            stat_vector.push_back({data, count, (double)count/(double)_count});
        }
        sort(stat_vector.begin(), stat_vector.end());
        return stat_vector;
    }

    std::vector<stat_elem<int>> get_tax_authority_id_stat() {
        std::vector<stat_elem<int>> stat_vector;
        for (auto &[data, count] : tax_authority_id_stat) {
            stat_vector.push_back({data, count, (double)count/(double)_count});
        }
        sort(stat_vector.begin(), stat_vector.end());
        return stat_vector;
    }

    std::vector<stat_elem<std::string>> get_surname_stat() {
        std::vector<stat_elem<std::string>> stat_vector;
        for (auto &[data, count] : surname_stat) {
            stat_vector.push_back({data, count, (double)count/(double)_count});
        }
        sort(stat_vector.begin(), stat_vector.end());
        return stat_vector;
    }

    std::vector<stat_elem<std::string>> get_name_stat() {
        std::vector<stat_elem<std::string>> stat_vector;
        for (auto &[data, count] : name_stat) {
            stat_vector.push_back({data, count, (double)count/(double)_count});
        }
        sort(stat_vector.begin(), stat_vector.end());
        return stat_vector;
    }

    std::vector<stat_elem<std::string>> get_patronymic_stat() {
        std::vector<stat_elem<std::string>> stat_vector;
        for (auto &[data, count] : patronymic_stat) {
            stat_vector.push_back({data, count, (double)count/(double)_count});
        }
        sort(stat_vector.begin(), stat_vector.end());
        return stat_vector;
    }

    std::vector<stat_elem<Date>> get_birth_date_stat() {
        std::vector<stat_elem<Date>> stat_vector;
        for (auto &[data, count] : birth_date_stat) {
            stat_vector.push_back({data, count, (double)count/(double)_count});
        }
        sort(stat_vector.begin(), stat_vector.end());
        return stat_vector;
    }

    std::vector<stat_elem<char>> get_gender_stat() {
        std::vector<stat_elem<char>> stat_vector;
        for (auto &[data, count] : gender_stat) {
            stat_vector.push_back({data, count, (double)count/(double)_count});
        }
        sort(stat_vector.begin(), stat_vector.end());
        return stat_vector;
    }

    std::vector<stat_elem<std::string>> get_citizenship_stat() {
        std::vector<stat_elem<std::string>> stat_vector;
        for (auto &[data, count] : citizenship_stat) {
            stat_vector.push_back({data, count, (double)count/(double)_count});
        }
        sort(stat_vector.begin(), stat_vector.end());
        return stat_vector;
    }

    std::vector<stat_elem<long long>> get_passport_id_stat() {
        std::vector<stat_elem<long long>> stat_vector;
        for (auto &[data, count] : passport_id_stat) {
            stat_vector.push_back({data, count, (double)count/(double)_count});
        }
        sort(stat_vector.begin(), stat_vector.end());
        return stat_vector;
    }

    std::vector<stat_elem<Date>> get_passport_date_of_issue_stat() {
        std::vector<stat_elem<Date>> stat_vector;
        for (auto &[data, count] : passport_date_of_issue_stat) {
            stat_vector.push_back({data, count, (double)count/(double)_count});
        }
        sort(stat_vector.begin(), stat_vector.end());
        return stat_vector;
    }

    std::vector<stat_elem<int>> get_postal_code_stat() {
        std::vector<stat_elem<int>> stat_vector;
        for (auto &[data, count] : postal_code_stat) {
            stat_vector.push_back({data, count, (double)count/(double)_count});
        }
        sort(stat_vector.begin(), stat_vector.end());
        return stat_vector;
    }

    std::vector<stat_elem<std::string>> get_country_stat() {
        std::vector<stat_elem<std::string>> stat_vector;
        for (auto &[data, count] : country_stat) {
            stat_vector.push_back({data, count, (double)count/(double)_count});
        }
        sort(stat_vector.begin(), stat_vector.end());
        return stat_vector;
    }

    std::vector<stat_elem<std::string>> get_region_stat() {
        std::vector<stat_elem<std::string>> stat_vector;
        for (auto &[data, count] : region_stat) {
            stat_vector.push_back({data, count, (double)count/(double)_count});
        }
        sort(stat_vector.begin(), stat_vector.end());
        return stat_vector;
    }

    std::vector<stat_elem<std::string>> get_city_stat() {
        std::vector<stat_elem<std::string>> stat_vector;
        for (auto &[data, count] : city_stat) {
            stat_vector.push_back({data, count, (double)count/(double)_count});
        }
        sort(stat_vector.begin(), stat_vector.end());
        return stat_vector;
    }

    std::vector<stat_elem<std::string>> get_street_stat() {
        std::vector<stat_elem<std::string>> stat_vector;
        for (auto &[data, count] : street_stat) {
            stat_vector.push_back({data, count, (double)count/(double)_count});
        }
        sort(stat_vector.begin(), stat_vector.end());
        return stat_vector;
    }

    std::vector<stat_elem<int>> get_house_number_stat() {
        std::vector<stat_elem<int>> stat_vector;
        for (auto &[data, count] : house_number_stat) {
            stat_vector.push_back({data, count, (double)count/(double)_count});
        }
        sort(stat_vector.begin(), stat_vector.end());
        return stat_vector;
    }

    std::vector<stat_elem<int>> get_apartment_number_stat() {
        std::vector<stat_elem<int>> stat_vector;
        for (auto &[data, count] : apartment_number_stat) {
            stat_vector.push_back({data, count, (double)count/(double)_count});
        }
        sort(stat_vector.begin(), stat_vector.end());
        return stat_vector;
    }

    std::vector<stat_elem<Date>> get_filling_date_stat() {
        std::vector<stat_elem<Date>> stat_vector;
        for (auto &[data, count] : filling_date_stat) {
            stat_vector.push_back({data, count, (double)count/(double)_count});
        }
        sort(stat_vector.begin(), stat_vector.end());
        return stat_vector;
    }
};