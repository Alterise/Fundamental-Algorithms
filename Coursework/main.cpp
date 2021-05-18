#include <iostream>
#include <chrono>
#include <vector>
#include "concrete_strategies.h"
#include "DataBase.h"
#include "map_implementation.h"
#include "RB_tree_implementation.h"

int main() {
    data_base current_data_base(new RB_tree_implementation);
    auto start = std::chrono::steady_clock::now();
    current_data_base.generate(5000000);
    auto stat = current_data_base.statistics.get_citizenship_stat();
    for (const auto &item : stat) {
        std::cout << item.data << " " << item.abs_count << " " << item.rel_count << std::endl;
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> time = end - start;
    std::cout << "time passed: " << time.count() << "s" << std::endl;
//    auto filling_date_strategy = new documents_filling_date_strategy;
//    Document current_document;
//    current_document.filling_date = {22, 02, 2020};
//    auto ptr = data_base.search(current_document, filling_date_strategy);
//    if (ptr != nullptr) {
//        std::cout << ptr->name << std::endl;
//    } else {
//        std::cout << "NO" << std::endl;
//    }
//
//    data_base.remove(*ptr);
//    ptr = data_base.search(current_document, filling_date_strategy);
//    if (ptr != nullptr) {
//        std::cout << ptr->name << std::endl;
//    } else {
//        std::cout << "NO" << std::endl;
//    }
//    delete filling_date_strategy;
    return 0;
}