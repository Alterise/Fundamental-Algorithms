#pragma once
#include <vector>
#include <set>
#include "interface.h"

class recursive_solver : public solver {
public:
    std::set<std::vector<std::vector<bool>>> solve() override {
        std::set<std::vector<std::vector<bool>>> solutions;
        std::vector<std::vector<int>> diagonals_tmp (8, std::vector<int> (8));
        straight_diagonals = diagonals_tmp;
        back_diagonals = diagonals_tmp;
        diagonals_filling(8);
        std::vector<QueenInfo> queens_info;


        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                recursive_queens_info_filling(queens_info, j, i, solutions, 0);
            }
        }
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

    void recursive_queens_info_filling (std::vector<QueenInfo> queens_info, int x, int y,
                                                          std::set<std::vector<std::vector<bool>>>& solutions, int depth) {
        if (depth >= 8) {
            return;
        }
        QueenInfo current_queen_info;
        current_queen_info.vertical_value = y;
        current_queen_info.horisontal_value = x;
        current_queen_info.straight_diagonal_value = straight_diagonals[y][x];
        current_queen_info.back_diagonal_value = back_diagonals[y][x];
        if (queens_check(queens_info, current_queen_info)) {
            queens_info.push_back(current_queen_info);
            if (queens_info.size() >= 8) {
                solutions.insert(place_queens(queens_info));
                return;
            }
            for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 8; ++j) {
                    recursive_queens_info_filling(queens_info, j, i, solutions, depth + 1);
                }
            }
        }
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