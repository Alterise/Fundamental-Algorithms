#pragma once
#include <vector>

class solver {
    virtual std::set<std::vector<std::vector<bool>>> solve() = 0;
};