#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include <ctime>
#include "concrete_generator_factory1.h"
#include "concrete_strategies.h"
#include "RB_tree.h"


int main() {
    const auto factory = new generator_factory1;
    const auto generator = factory->create_generator();
    Document* current_document;
    RB_tree<Document> tree(new documents_strategy, false);

    auto start = std::chrono::steady_clock::now();
    const int N = 50000;

    for (int i = 0; i < N; ++i) {
        current_document = generator->generate();
        tree.insert(*current_document);
//        std::cout << "Document " + std::to_string(i) + " generated" << std::endl;
        delete current_document;
//        buffer.push_back(current_document);
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_time = end - start;
    std::cout << "time passed: " << elapsed_time.count() << "s" << std::endl;
//    for (const auto &item : buffer) {
//        delete item;
//    }

    delete generator;
    delete factory;
    return 0;
}