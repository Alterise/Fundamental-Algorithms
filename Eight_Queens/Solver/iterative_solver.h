#pragma once
#include <vector>
#include "interface.h"

class iterative_solver : public solver {
    std::vector<std::vector<std::vector<bool>>> solve() override {
        std::vector<std::vector<bool>> (8, std::vector<bool> (8, false)) field;
        std::vector<std::vector<std::vector<bool>>> solutions;
        return solutions;
    }
};