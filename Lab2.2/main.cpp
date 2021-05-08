#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include "RB_tree.h"
#include "concrete_strategies.h"
#include "relation.h"
#include "messages.h"
#include "message_parser.h"

const int CURRENT_TEST = 2;

int main() {
    // RB Tree test
    if (CURRENT_TEST == 1) {
        srand(time(0));
        const int N = 100;
        RB_tree<int> tree(new int_strategy);
        std::vector<int> buffer;
        std::vector<int> buffer2;
        for (int i = 0; i < N; ++i) {
            buffer.push_back(rand() % 25000 - 12500);
            int a = buffer.back();
            tree.insert(a);
        }
        for (const auto &item : buffer) {
            std::cout << item << " ";
        }
        std::cout << std::endl << std::endl;
        tree.print();
        for (int i = 0; i < N; ++i) {
            int a = (rand() % (N - i));
            int b = buffer[a];
            tree.remove(b);
            buffer.erase(buffer.begin() + a);
            buffer2.push_back(b);
            tree.print();
        }
    }

    // Class relation test
    if (CURRENT_TEST == 2) {
        relation<int> rel(new int_strategy);
        rel.insert(5);
        rel.insert_tree(new RB_tree<int*>(new int_ptr_strategy));
        rel.insert_tree(new RB_tree<int*>(new int_ptr_strategy_reverse));
        rel.insert(8);
        rel.insert(11);
        rel.insert(2);
        rel.insert(11);
        int id = rel.insert_tree(new RB_tree<int*>(new int_ptr_strategy_odd_first));
        rel.insert(15);
//        auto ptr = rel.search(id, 8);
//        if (ptr != nullptr) {
//            std::cout << *ptr << std::endl;
//        } else {
//            std::cout << "No" << std::endl;
//        }
//        ptr = rel.search(id, 8);
//        if (ptr != nullptr) {
//            std::cout << *ptr << std::endl;
//        } else {
//            std::cout << "No" << std::endl;
//        }
        rel.remove(5);
        rel.remove(8);
        rel.remove(11);
        rel.remove(2);
        rel.remove(11);
        rel.remove(15);
        std::cout << 1;
    }

    // Message class test
//    if (CURRENT_TEST == 3) {
//        std::vector<Message> messages;
//        messages = parse_messages("input.txt");
//        std::vector<Message> messages_dates;
//        messages_dates.reserve(messages.size());
//        for (const auto &message : messages) {
//            messages_dates.push_back({message.date,"",""});
//        }
//        relation<Message> rel(new message_strategy, false);
//        int id_by_date = rel.insert_tree(new RB_tree<Message*> (new message_strategy_date, false));
////        rel.insert_tree(new RB_tree<Message*> (new message_strategy_username, false));
////        rel.insert_tree(new RB_tree<Message*> (new message_strategy_data, false));
////        rel.insert_tree(new RB_tree<Message*> (new message_strategy_username_date, false));
//    }

}