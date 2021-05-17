#include <iostream>
#include <chrono>
#include <vector>
#include "concrete_strategies.h"
#include "DataBase.h"
#include "map_implementation.h"
#include "RB_tree_implementation.h"

int main() {
    data_base data_base(new map_realisation);
    auto start = std::chrono::steady_clock::now();
    data_base.generate(50000);
    auto filling_date_strategy = new documents_filling_date_strategy;
    Document current_document;
    current_document.filling_date = {22, 02, 2020};
    auto ptr = data_base.search(current_document, filling_date_strategy);
    if (ptr != nullptr) {
        std::cout << ptr->name << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }

    data_base.remove(*ptr);
    ptr = data_base.search(current_document, filling_date_strategy);
    if (ptr != nullptr) {
        std::cout << ptr->name << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }
    delete filling_date_strategy;


    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_time = end - start;
    std::cout << "time passed: " << elapsed_time.count() << "s" << std::endl;

    return 0;
}