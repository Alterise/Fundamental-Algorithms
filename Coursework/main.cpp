#include <iostream>
//#include <chrono>
#include <vector>
#include <string>
#include "concrete_strategies.h"
#include "Database.h"
#include "menu.h"
#include "map_implementation.h"
#include "RB_tree_implementation.h"

int main() {
    data_base current_data_base(new RB_tree_implementation);
    while(menu(current_data_base));
    return 0;
}
