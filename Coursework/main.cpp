#include "Database.h"
#include "menu.h"
#include "RB_tree_implementation.h"
#include "map_implementation.h"

int main() {
    data_base current_data_base(new map_implementation);
    while(menu(current_data_base));
    return 0;
}