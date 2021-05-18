#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include "Database.h"
#include "date.h"

void insert_section(data_base&);
void search_section(data_base&);
void check_buffer(data_base&);
void remove_section(data_base&);
void generate_section(data_base&);

void search_by_id(data_base&);
void search_by_tax_authority(data_base&);
void search_by_full_name(data_base&);
void search_by_passport_id(data_base&);
void search_by_filling_date(data_base&);

bool menu(data_base& current_data_base) {
    std::string str_switcher;
    int switcher;
    std::cout << std::endl << "  Menu:" << std::endl;
    std::cout << "1. Insert document in database" << std::endl;
    std::cout << "2. Search document in database" << std::endl;
    std::cout << "3. Check document in buffer" << std::endl;
    std::cout << "4. Delete document in buffer from database" << std::endl;
    std::cout << "5. Generate documents and put them in database" << std::endl;
    std::cout << "0. Exit" << std::endl;
    while(true) {
        std::cout << std::endl << "Input: ";
        std::getline(std::cin, str_switcher);
        if (std::all_of(str_switcher.begin(), str_switcher.end(), isdigit) && (str_switcher.size() == 1)) {
            switcher = stoi(str_switcher);
            if ((switcher < 0) || (switcher > 5)) {
                std::cout << "Wrong input. Try again." << std::endl;
            } else {
                break;
            }
        } else {
            std::cout << "Wrong input. Try again." << std::endl;
        }
    }

    if (switcher == 1) {
        insert_section(current_data_base);
        return true;
    } else if (switcher == 2) {
        search_section(current_data_base);
        return true;
    } else if (switcher == 3) {
        check_buffer(current_data_base);
        return true;
    } else if (switcher == 4) {
        remove_section(current_data_base);
        return true;
    } else if (switcher == 5) {
        generate_section(current_data_base);
        return true;
    } else {
        return false;
    }
}

void insert_section(data_base& current_data_base) {
    Document current_document;
    std::string str_tmp;
    long long long_long_tmp;
    int int_tmp;
    Date date_tmp;
    while (true) {
        std::cout << "Input ID (12 digits): ";
        std::getline(std::cin, str_tmp);
        if (std::all_of(str_tmp.begin(), str_tmp.end(), isdigit) && (str_tmp.size() == 12)) {
            long_long_tmp = stol(str_tmp);
            break;
        } else {
            std::cout << "Wrong input. Try again." << std::endl;
        }
    }
    current_document.id = long_long_tmp;

    while (true) {
        std::cout << "Input fiscal year (4 digits): ";
        std::getline(std::cin, str_tmp);
        if (std::all_of(str_tmp.begin(), str_tmp.end(), isdigit) && (str_tmp.size() == 4)) {
            int_tmp = stoi(str_tmp);
            if (int_tmp <= 1900) {
                std::cout << "Wrong input. Try again." << std::endl;
                continue;
            }
            break;
        } else {
            std::cout << "Wrong input. Try again." << std::endl;
        }
    }
    current_document.fiscal_year = int_tmp;

    std::cout << "Input tax authority: ";
    std::getline(std::cin, current_document.tax_authority);

    while (true) {
        std::cout << "Input tax authority ID (< 5001): ";
        std::getline(std::cin, str_tmp);
        if (std::all_of(str_tmp.begin(), str_tmp.end(), isdigit) && (str_tmp.size() == 4)) {
            int_tmp = stoi(str_tmp);
            if (int_tmp > 5000) {
                std::cout << "Wrong input. Try again." << std::endl;
                continue;
            }
            break;
        } else {
            std::cout << "Wrong input. Try again." << std::endl;
        }
    }
    current_document.tax_authority_id = int_tmp;


    std::cout << "Input surname: ";
    std::getline(std::cin, current_document.surname);
    std::cout << "Input name: ";
    std::getline(std::cin, current_document.name);
    std::cout << "Input patronymic: ";
    std::getline(std::cin, current_document.patronymic);
    while (true) {
        std::cout << "Input birth date (dd/mm/yyyy): ";
        std::getline(std::cin, str_tmp);
        if ((str_tmp.size() == 10)) {
            if (!isdigit(str_tmp[0]) || !isdigit(str_tmp[1]) || !isdigit(str_tmp[3]) ||
                !isdigit(str_tmp[4]) || !isdigit(str_tmp[6]) || !isdigit(str_tmp[7]) ||
                !isdigit(str_tmp[8]) || !isdigit(str_tmp[9]) || str_tmp[2] != '/' || str_tmp[5] != '/') {
                std::cout << "Wrong input. Try again." << std::endl;
                continue;
            }
            date_tmp.day = (str_tmp[0] - '0') * 10 + (str_tmp[1] - '0');
            date_tmp.month = (str_tmp[3] - '0') * 10 + (str_tmp[4] - '0');
            date_tmp.day =
                    (str_tmp[6] - '0') * 1000 + (str_tmp[7] - '0') * 100 + (str_tmp[8] - '0') * 10 + (str_tmp[9] - '0');
            break;
        } else {
            std::cout << "Wrong input. Try again." << std::endl;
        }
    }
    current_document.birth_date = date_tmp;


    while (true) {
        std::cout << "Input gender (M/F): ";
        std::getline(std::cin, str_tmp);
        if ((str_tmp.size() == 1)) {
            if (str_tmp[0] != 'M' && str_tmp[0] != 'F') {
                std::cout << "Wrong input. Try again." << std::endl;
                continue;
            }
            break;
        } else {
            std::cout << "Wrong input. Try again." << std::endl;
        }
    }
    current_document.gender = str_tmp[0];

    while (true) {
        std::cout << "How many citizenships do you have? (< 100)" << std::endl;;
        std::cout << "Input count: ";
        std::getline(std::cin, str_tmp);
        if (std::all_of(str_tmp.begin(), str_tmp.end(), isdigit) && (str_tmp.size() <= 2)) {
            int_tmp = stoi(str_tmp);
            break;
        } else {
            std::cout << "Wrong input. Try again." << std::endl;
        }
    }
    for (int i = 1; i <= int_tmp; ++i) {
        std::cout << "Input citizenship No." << i << ": ";
        std::getline(std::cin, str_tmp);
        current_document.citizenship.push_back(str_tmp);
    }

    while (true) {
        std::cout << "Input passport ID (10 digits): ";
        std::getline(std::cin, str_tmp);
        if (std::all_of(str_tmp.begin(), str_tmp.end(), isdigit) && (str_tmp.size() == 10)) {
            long_long_tmp = stol(str_tmp);
            break;
        } else {
            std::cout << "Wrong input. Try again." << std::endl;
        }
    }
    current_document.passport_id = long_long_tmp;

    while (true) {
        std::cout << "Input passport date of issue (dd/mm/yyyy): ";
        std::getline(std::cin, str_tmp);
        if ((str_tmp.size() == 10)) {
            if (!isdigit(str_tmp[0]) || !isdigit(str_tmp[1]) || !isdigit(str_tmp[3]) ||
                !isdigit(str_tmp[4]) || !isdigit(str_tmp[6]) || !isdigit(str_tmp[7]) ||
                !isdigit(str_tmp[8]) || !isdigit(str_tmp[9]) || str_tmp[2] != '/' || str_tmp[5] != '/') {
                std::cout << "Wrong input. Try again." << std::endl;
                continue;
            }
            date_tmp.day = (str_tmp[0] - '0') * 10 + (str_tmp[1] - '0');
            date_tmp.month = (str_tmp[3] - '0') * 10 + (str_tmp[4] - '0');
            date_tmp.day =
                    (str_tmp[6] - '0') * 1000 + (str_tmp[7] - '0') * 100 + (str_tmp[8] - '0') * 10 + (str_tmp[9] - '0');
            break;
        } else {
            std::cout << "Wrong input. Try again." << std::endl;
        }
    }
    current_document.passport_date_of_issue = date_tmp;

    while (true) {
        std::cout << "Input postal code (6 digits): ";
        std::getline(std::cin, str_tmp);
        if (std::all_of(str_tmp.begin(), str_tmp.end(), isdigit) && (str_tmp.size() == 4)) {
            int_tmp = stoi(str_tmp);
            if (int_tmp <= 1900) {
                std::cout << "Wrong input. Try again." << std::endl;
                continue;
            }
            break;
        } else {
            std::cout << "Wrong input. Try again." << std::endl;
        }
    }
    current_document.postal_code = int_tmp;

    std::cout << "Input country: ";
    std::getline(std::cin, current_document.country);
    std::cout << "Input region: ";
    std::getline(std::cin, current_document.region);
    std::cout << "Input city: ";
    std::getline(std::cin, current_document.city);
    std::cout << "Input street name: ";
    std::getline(std::cin, current_document.street);

    while (true) {
        std::cout << "Input house number (< 1000): ";
        std::getline(std::cin, str_tmp);
        if (std::all_of(str_tmp.begin(), str_tmp.end(), isdigit) && (str_tmp.size() < 4)) {
            int_tmp = stoi(str_tmp);
            break;
        } else {
            std::cout << "Wrong input. Try again." << std::endl;
        }
    }
    current_document.house_number = int_tmp;

    while (true) {
        std::cout << "Input apartment number (< 1000): ";
        std::getline(std::cin, str_tmp);
        if (std::all_of(str_tmp.begin(), str_tmp.end(), isdigit) && (str_tmp.size() < 4)) {
            int_tmp = stoi(str_tmp);
            break;
        } else {
            std::cout << "Wrong input. Try again." << std::endl;
        }
    }
    current_document.apartment_number = int_tmp;

    while (true) {
        std::cout << "Input filling date (dd/mm/yyyy): ";
        std::getline(std::cin, str_tmp);
        if ((str_tmp.size() == 10)) {
            if (!isdigit(str_tmp[0]) || !isdigit(str_tmp[1]) || !isdigit(str_tmp[3]) ||
                !isdigit(str_tmp[4]) || !isdigit(str_tmp[6]) || !isdigit(str_tmp[7]) ||
                !isdigit(str_tmp[8]) || !isdigit(str_tmp[9]) || str_tmp[2] != '/' || str_tmp[5] != '/') {
                std::cout << "Wrong input. Try again." << std::endl;
                continue;
            }
            date_tmp.day = (str_tmp[0] - '0') * 10 + (str_tmp[1] - '0');
            date_tmp.month = (str_tmp[3] - '0') * 10 + (str_tmp[4] - '0');
            date_tmp.day =
                    (str_tmp[6] - '0') * 1000 + (str_tmp[7] - '0') * 100 + (str_tmp[8] - '0') * 10 + (str_tmp[9] - '0');
            break;
        } else {
            std::cout << "Wrong input. Try again." << std::endl;
        }
    }
    current_document.filling_date = date_tmp;

    std::cout << "That's all." << std::endl;
    std::cout << "Do you want to check your document? (Y/N)" << std::endl;
    while (true) {
        std::cin >> str_tmp;
        if (str_tmp == "Y") {
            std::cout << current_document << std:: endl;
            break;
        } else if (str_tmp == "N") {
            break;
        } else {
            std::cout << "Wrong input. Try again." << std::endl;
        }
    }
    std::cout << "Do you want to add your document to database? (Add/Discard)" << std::endl;
    while (true) {
        std::cin >> str_tmp;
        if (str_tmp == "Add") {
            current_data_base.insert(current_document);
            break;
        } else if (str_tmp == "Discard") {
            break;
        } else {
            std::cout << "Wrong input. Try again." << std::endl;
        }
    }
}

void search_section(data_base& current_data_base) {
    std::string str_switcher;
    int switcher;
    std::cout << std::endl << "How do you want to search your document?" << std::endl << std::endl;
    std::cout << "1. By ID" << std::endl;
    std::cout << "2. By tax authority" << std::endl;
    std::cout << "3. By full name" << std::endl;
    std::cout << "4. By passport ID" << std::endl;
    std::cout << "5. By filling date" << std::endl;
    std::cout << "0. Exit" << std::endl;
    while(true) {
        std::cout << std::endl << "Input: ";
        std::getline(std::cin, str_switcher);
        if (std::all_of(str_switcher.begin(), str_switcher.end(), isdigit) && (str_switcher.size() == 1)) {
            switcher = stoi(str_switcher);
            if ((switcher < 0) || (switcher > 5)) {
                std::cout << "Wrong input. Try again." << std::endl;
            } else {
                break;
            }
        } else {
            std::cout << "Wrong input. Try again." << std::endl;
        }
    }

    if (switcher == 1) {
        search_by_id(current_data_base);
    } else if (switcher == 2) {
        search_by_tax_authority(current_data_base);
    } else if (switcher == 3) {
        search_by_full_name(current_data_base);
    } else if (switcher == 4) {
        search_by_passport_id(current_data_base);
    } else if (switcher == 5) {
        search_by_filling_date(current_data_base);
    }
}

void check_buffer(data_base& current_data_base) {
    auto ptr = current_data_base.get_buffered();
    if (ptr == nullptr) {
        std::cout << "There is no document in buffer" << std::endl;
    } else {
        std::cout << *ptr;
    }
}

void remove_section(data_base& current_data_base) {
    auto ptr = current_data_base.get_buffered();
    if (ptr == nullptr) {
        std::cout << "There is no document in buffer" << std::endl;
    } else {
        current_data_base.remove_buffered();
    }
}

void generate_section(data_base& current_data_base) {
    std::cout << "How much documents you want to generate?" << std::endl;
    std::string str_count;
    int count;
    while(true) {
        std::cout << std::endl << "Input: ";
        std::getline(std::cin, str_count);
        if (std::all_of(str_count.begin(), str_count.end(), isdigit) && (str_count.size() <= 7)) {
            count = stoi(str_count);
            if (count > 1000000) {
                std::cout << "That would took much time and space. Are you sure? (Y/N)" << std::endl;
                std::string tmp;
                std::cin >> tmp;
                if (tmp == "Y") {
                    current_data_base.generate(count);
                    break;
                } else if (tmp == "N") {
                    continue;
                } else {
                    std::cout << "Wrong input. Try again." << std::endl;
                }
            }
            current_data_base.generate(count);
            break;
        } else {
            std::cout << "Wrong input. Try again." << std::endl;
        }
    }
}

void search_by_id(data_base& current_data_base) {
    std::string str_tmp;
    long long long_long_tmp;
    auto strategy = new documents_id_strategy;
    Document current_document;
    while (true) {
        std::cout << "Input ID (12 digits): ";
        std::getline(std::cin, str_tmp);
        if (std::all_of(str_tmp.begin(), str_tmp.end(), isdigit) && (str_tmp.size() == 12)) {
            long_long_tmp = stol(str_tmp);
            break;
        } else {
            std::cout << "Wrong input. Try again." << std::endl;
        }
    }
    current_document.id = long_long_tmp;
    current_data_base.search(current_document, strategy);
    delete strategy;
}
void search_by_tax_authority(data_base& current_data_base) {
    std::string str_tmp;
    int int_tmp;
    auto strategy = new documents_tax_authority_strategy;
    Document current_document;
    std::cout << "Input tax authority: ";
    std::getline(std::cin, current_document.tax_authority);
    while (true) {
        std::cout << "Input tax authority ID (< 5001): ";
        std::getline(std::cin, str_tmp);
        if (std::all_of(str_tmp.begin(), str_tmp.end(), isdigit) && (str_tmp.size() == 4)) {
            int_tmp = stoi(str_tmp);
            if (int_tmp > 5000) {
                std::cout << "Wrong input. Try again." << std::endl;
                continue;
            }
            break;
        } else {
            std::cout << "Wrong input. Try again." << std::endl;
        }
    }
    current_document.tax_authority_id = int_tmp;
    current_data_base.search(current_document, strategy);
    delete strategy;
}

void search_by_full_name(data_base& current_data_base) {
    auto strategy = new documents_full_name_strategy;
    Document current_document;
    std::cout << "Input surname: ";
    std::getline(std::cin, current_document.surname);
    std::cout << "Input name: ";
    std::getline(std::cin, current_document.name);
    std::cout << "Input patronymic: ";
    std::getline(std::cin, current_document.patronymic);
    current_data_base.search(current_document, strategy);
    delete strategy;
}

void search_by_passport_id(data_base& current_data_base) {
    std::string str_tmp;
    long long long_long_tmp;
    auto strategy = new documents_passport_id_strategy;
    Document current_document;
    while (true) {
        std::cout << "Input passport ID (10 digits): ";
        std::getline(std::cin, str_tmp);
        if (std::all_of(str_tmp.begin(), str_tmp.end(), isdigit) && (str_tmp.size() == 10)) {
            long_long_tmp = stol(str_tmp);
            break;
        } else {
            std::cout << "Wrong input. Try again." << std::endl;
        }
    }
    current_document.passport_id = long_long_tmp;
    current_data_base.search(current_document, strategy);
    delete strategy;
}

void search_by_filling_date(data_base& current_data_base) {
    std::string str_tmp;
    Date date_tmp;
    auto strategy = new documents_filling_date_strategy;
    Document current_document;while (true) {
        std::cout << "Input filling date (dd/mm/yyyy): ";
        std::getline(std::cin, str_tmp);
        if ((str_tmp.size() == 10)) {
            if (!isdigit(str_tmp[0]) || !isdigit(str_tmp[1]) || !isdigit(str_tmp[3]) ||
                !isdigit(str_tmp[4]) || !isdigit(str_tmp[6]) || !isdigit(str_tmp[7]) ||
                !isdigit(str_tmp[8]) || !isdigit(str_tmp[9]) || str_tmp[2] != '/' || str_tmp[5] != '/') {
                std::cout << "Wrong input. Try again." << std::endl;
                continue;
            }
            date_tmp.day = (str_tmp[0] - '0') * 10 + (str_tmp[1] - '0');
            date_tmp.month = (str_tmp[3] - '0') * 10 + (str_tmp[4] - '0');
            date_tmp.day =
                    (str_tmp[6] - '0') * 1000 + (str_tmp[7] - '0') * 100 + (str_tmp[8] - '0') * 10 + (str_tmp[9] - '0');
            break;
        } else {
            std::cout << "Wrong input. Try again." << std::endl;
        }
    }
    current_document.filling_date = date_tmp;
    current_data_base.search(current_document, strategy);
    delete strategy;
}