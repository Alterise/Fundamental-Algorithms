#pragma once
#include <vector>
#include "interface.h"

class recursive_solver : public solver {
public:
    std::set<std::vector<std::vector<bool>>> solve() override {
        std::set<std::vector<std::vector<bool>>> solutions;
        return solutions;
    }
private:
    void diagonals_filling(int N) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                straight_diagonals[i][j] = i + j;
                back_diagonals[i][j] = i - j + (N - 1);
            }
        }
    }
    std::vector<std::vector<int>> straight_diagonals;
    std::vector<std::vector<int>> back_diagonals;
};