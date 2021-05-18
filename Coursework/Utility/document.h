#pragma once
#include <vector>
#include <string>
#include "date.h"

struct Document {
    long long id; // 1
    int fiscal_year;
    std::string tax_authority; // 2
    int tax_authority_id; // 2

    std::string surname; // 3
    std::string name; // 3
    std::string patronymic; // 3
    Date birth_date;
    char gender;

    std::vector<std::string> citizenship;

    long long passport_id; // 4
    Date passport_date_of_issue;

    int postal_code;
    std::string country;
    std::string region;
    std::string city;
    std::string street;
    int house_number;
    int apartment_number;

    Date filling_date; // 5

    friend std::ostream& operator<<(std::ostream& stream, const Document& document) {
        stream << "Document: " << std::endl
               << "ID: " << document.id << std::endl
               << "Fiscal year: " << document.fiscal_year << std::endl
               << "Tax authority: " << document.tax_authority << std::endl
               << "Tax authority ID: " << document.tax_authority_id << std::endl
               << "Surname: " << document.surname << std::endl
               << "Name: " << document.name << std::endl
               << "Patronymic: " << document.patronymic << std::endl
               << "Birth date: " << document.birth_date << std::endl
               << "Gender: " << document.gender << std::endl
               << "Citizenship:" << std::endl;
        for (const auto &item : document.citizenship) {
                stream << "    " << item << std::endl;
        }
        stream << "Passport ID: " << document.passport_id << std::endl
               << "Passport date of issue: " << document.passport_date_of_issue << std::endl
               << "Postal code: " << document.postal_code << std::endl
               << "Country: " << document.country << std::endl
               << "Region: " << document.region << std::endl
               << "City: " << document.city << std::endl
               << "Street: " << document.street << std::endl
               << "House number: " << document.house_number << std::endl
               << "Apartment number: " << document.apartment_number << std::endl
               << "Filling date: " << document.filling_date << std::endl;
        return stream;
    }
};