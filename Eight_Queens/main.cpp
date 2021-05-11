#include <iostream>
#include <vector>
#include <set>
#include <chrono>
#include "iterative_solver.h"
#include "recursive_solver.h"

int main() {
//    std::vector<std::vector<std::vector<bool>>> solutions;
    std::set<std::vector<std::vector<bool>>> solutions;
    iterative_solver i_solver;
    recursive_solver r_solver;
    auto start = std::chrono::steady_clock::now();
    solutions = i_solver.solve();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_time = end - start;
    std::cout << "time passed (iterative): " << elapsed_time.count() << "s\n";
//    for (const auto &solution : solutions) {
//        for (int i = 0; i < 7; ++i) {
//            for (int j = 0; j < 7; ++j) {
//                std::cout << solution[i][j] << " ";
//            }
//            std::cout << std::endl;
//        }
//        std::cout << std::endl << std::endl;
//    }
    start = std::chrono::steady_clock::now();
//    solutions = r_solver.solve();
    end = std::chrono::steady_clock::now();
    elapsed_time = end - start;
    std::cout << "time passed (recursive): " << elapsed_time.count() << "s\n";
//    for (const auto &solution : solutions) {
//        for (int i = 0; i < 7; ++i) {
//            for (int j = 0; j < 7; ++j) {
//                std::cout << solution[i][j] << " ";
//            }
//            std::cout << std::endl;
//        }
//        std::cout << std::endl << std::endl;
//    }
}
