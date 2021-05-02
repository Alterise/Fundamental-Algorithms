//#include <iostream>
#include "RB_tree.h"
#include "../Strategies/concrete_strategies.h"

int main()
{
    RB_tree<Message> tree(new messages_strategy);
}