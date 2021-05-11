#pragma once
#include <vector>
#include <algorithm>
#include "interface.h"

struct QueenInfo {
    int vertical_value;
    int horisontal_value;
    int straight_diagonal_value;
    int back_diagonal_value;

    bool operator==(const QueenInfo& rhs) const {
        if (vertical_value == rhs.vertical_value) {
            return true;
        } else if (horisontal_value == rhs.horisontal_value) {
            return true;
        } else if (straight_diagonal_value == rhs.straight_diagonal_value) {
            return true;
        } else if (back_diagonal_value == rhs.back_diagonal_value) {
            return true;
        } else {
            return false;
        }
    }
};

class iterative_solver : public solver {
public:
    std::set<std::vector<std::vector<bool>>> solve() override {
        std::set<std::vector<std::vector<bool>>> solutions;
        std::vector<std::vector<int>> diagonals_tmp (8, std::vector<int> (8));
        straight_diagonals = diagonals_tmp;
        back_diagonals = diagonals_tmp;
        diagonals_filling(8);
        std::vector<int> queens_y = {0, 1, 2, 3, 4, 5, 6, 7};
        std::vector<QueenInfo> queens_info;
        do {
            queens_info = queens_info_filling(queens_y);
            if (queens_info.size() == 8) {
                solutions.insert(place_queens(queens_info));
            }
        } while (std::next_permutation(queens_y.begin(), queens_y.end()));
        return solutions;
    }

private:
    std::vector<std::vector<bool>> place_queens(const std::vector<QueenInfo>& queens_info) {
        std::vector<std::vector<bool>> field (8, std::vector<bool> (8, false));
        for (const auto &queen : queens_info) {
            field[queen.vertical_value][queen.horisontal_value] = true;
        }
        return field;
    }

    std::vector<QueenInfo> queens_info_filling (std::vector<int> queens_y) {
        std::vector<QueenInfo> queens_info;
        QueenInfo current_queen_info;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                current_queen_info.vertical_value = queens_y[i];
                current_queen_info.horisontal_value = j;
                current_queen_info.straight_diagonal_value = straight_diagonals[queens_y[i]][j];
                current_queen_info.back_diagonal_value = back_diagonals[queens_y[i]][j];
                if (queens_check(queens_info, current_queen_info)) {
                    queens_info.push_back(current_queen_info);
                }
            }
        }
        return queens_info;
    }

    void diagonals_filling(int N) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                straight_diagonals[i][j] = i + j;
                back_diagonals[i][j] = i - j + (N - 1);
            }
        }
    }

    bool queens_check (const std::vector<QueenInfo>& queens_info, const QueenInfo& current_queen_info) {
        for (const auto &queen : queens_info) {
            if (queen == current_queen_info) {
                return false;
            }
        }
        return true;
    }

    std::vector<std::vector<int>> straight_diagonals;
    std::vector<std::vector<int>> back_diagonals;
};