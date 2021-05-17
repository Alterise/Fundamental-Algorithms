#pragma once
#include <string>
#include <algorithm>
#include <cctype>
#include "strategy.h"
#include "document.h"

class documents_strategy : public strategy<Document> {
public:
    int compare(const Document& lhs, const Document& rhs) override {
        if (lhs.id != rhs.id) {
            return lhs.id - rhs.id;
        } else if (lhs.fiscal_year != rhs.fiscal_year) {
            return lhs.fiscal_year - rhs.fiscal_year;
        } else if (lhs.passport_id != rhs.passport_id) {
            return lhs.passport_id - rhs.passport_id;
        } else if (lhs.tax_authority_id != rhs.tax_authority_id) {
            return lhs.tax_authority_id - rhs.tax_authority_id;
        } else if (lhs.postal_code != rhs.postal_code) {
            return lhs.postal_code - rhs.postal_code;
        } else if (lhs.house_number != rhs.house_number) {
            return lhs.house_number - rhs.house_number;
        } else if (lhs.apartment_number != rhs.apartment_number) {
            return lhs.apartment_number - rhs.apartment_number;
        } else if (lhs.name != rhs.name) {
            return lhs.name < rhs.name ? -1 : 1;
        } else if (lhs.surname != rhs.surname) {
            return lhs.surname < rhs.surname ? -1 : 1;
        } else if (lhs.patronymic != rhs.patronymic) {
            return lhs.patronymic < rhs.patronymic ? -1 : 1;
        } else if (lhs.gender != rhs.gender) {
            return (int)lhs.gender - (int)rhs.gender;
        } else if (lhs.tax_authority != rhs.tax_authority) {
            return lhs.tax_authority < rhs.tax_authority ? -1 : 1;
        } else if (lhs.country != rhs.country) {
            return lhs.country < rhs.country ? -1 : 1;
        } else if (lhs.region != rhs.region) {
            return lhs.region < rhs.region ? -1 : 1;
        } else if (lhs.city != rhs.city) {
            return lhs.city < rhs.city ? -1 : 1;
        } else if (lhs.street != rhs.street) {
            return lhs.street < rhs.street ? -1 : 1;
        } else if (lhs.birth_date != rhs.birth_date) {
            return lhs.birth_date < rhs.birth_date ? -1 : 1;
        } else if (lhs.passport_date_of_issue != rhs.passport_date_of_issue) {
            return lhs.passport_date_of_issue < rhs.passport_date_of_issue ? -1 : 1;
        } else if (lhs.filling_date != rhs.filling_date) {
            return lhs.filling_date < rhs.filling_date ? -1 : 1;
        } else if (lhs.citizenship.size() != rhs.citizenship.size()) {
            return ((int)lhs.citizenship.size() - (int)rhs.citizenship.size());
        } else {
            for (int i = 0; i < lhs.citizenship.size(); ++i) {
                if (lhs.citizenship[i] != rhs.citizenship[i]) {
                    return (lhs.citizenship[i] < rhs.citizenship[i] ? -1 : 1);
                }
            }
            return 0;
        }
    }
};

class documents_id_strategy : public strategy<Document> {
public:
    int compare(const Document& lhs, const Document& rhs) override {
        if (lhs.id != rhs.id) {
            return lhs.id - rhs.id;
        } else {
            return 0;
        }
    }
};

class documents_tax_authority_strategy : public strategy<Document> {
public:
    int compare(const Document& lhs, const Document& rhs) override {
        if (lhs.tax_authority_id != rhs.tax_authority_id) {
            return lhs.tax_authority_id - rhs.tax_authority_id;
        } else if (lhs.tax_authority != rhs.tax_authority) {
            return lhs.tax_authority < rhs.tax_authority ? -1 : 1;
        } else {
            return 0;
        }
    }
};

class documents_full_name_strategy : public strategy<Document> {
public:
    int compare(const Document& lhs, const Document& rhs) override {
        if (lhs.name != rhs.name) {
            return lhs.name < rhs.name ? -1 : 1;
        } else if (lhs.surname != rhs.surname) {
            return lhs.surname < rhs.surname ? -1 : 1;
        } else if (lhs.patronymic != rhs.patronymic) {
            return lhs.patronymic < rhs.patronymic ? -1 : 1;
        } else {
            return 0;
        }
    }
};

class documents_passport_id_strategy : public strategy<Document> {
public:
    int compare(const Document& lhs, const Document& rhs) override {
        if (lhs.passport_id != rhs.passport_id) {
            return lhs.passport_id - rhs.passport_id;
        } else {
            return 0;
        }
    }
};

class documents_filling_date_strategy : public strategy<Document> {
public:
    int compare(const Document& lhs, const Document& rhs) override {
        if (lhs.filling_date != rhs.filling_date) {
            return lhs.filling_date < rhs.filling_date ? -1 : 1;
        } else {
            return 0;
        }
    }
};