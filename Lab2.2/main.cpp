#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include "RB_tree.h"
#include "concrete_strategies.h"
#include "relation.h"
#include "messages.h"
#include "message_parser.h"
#include "documents.h"
#include "document_parser.h"

const int CURRENT_TEST = 1;

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
        rel.insert_tree(new RB_tree<int*>(new int_ptr_strategy, false));
        rel.insert_tree(new RB_tree<int*>(new int_ptr_strategy_reverse, false));
        rel.insert(2);
        rel.insert(11);
        int id = rel.insert_tree(new RB_tree<int*>(new int_ptr_strategy_odd_first, false));
        rel.insert(15);
        auto ptr = rel.search(id, 8);
        if (ptr != nullptr) {
            std::cout << *ptr << std::endl;
        } else {
            std::cout << "No" << std::endl;
        }
        rel.insert(8);
        ptr = rel.search(id, 8);
        if (ptr != nullptr) {
            std::cout << *ptr << std::endl;
        } else {
            std::cout << "No" << std::endl;
        }
        rel.remove(5);
        rel.remove(8);
        rel.remove(11);
        rel.remove(2);
        rel.remove(15);
    }

    // Message class test
    if (CURRENT_TEST == 3) {
        std::vector<Message> messages;
        messages = parse_messages("input.txt");
        relation<Message> rel(new message_strategy);
        int id_by_date = rel.insert_tree(new RB_tree<Message*> (new message_ptr_strategy_date, false));
        for (const auto &message : messages) {
            rel.insert(message);
        }
        rel.insert_tree(new RB_tree<Message*> (new message_ptr_strategy_username, false));
        int id_by_data = rel.insert_tree(new RB_tree<Message*> (new message_ptr_strategy_data, false));
        rel.insert_tree(new RB_tree<Message*> (new message_ptr_strategy_username_date, false));
        auto ptr = rel.search(id_by_data, {{},"","Hello Adam"});
        auto ptr2 = rel.search(id_by_data, {{},"","Hello John"});
        auto ptr3 = rel.search(id_by_data, {{},"","Hello Valera"});
        if (ptr != nullptr) {
            std::cout << ptr->name << std::endl;
        } else {
            std::cout << "No" << std::endl;
        }
        if (ptr2 != nullptr) {
            std::cout << ptr2->name << std::endl;
        } else {
            std::cout << "No" << std::endl;
        }
        if (ptr3 != nullptr) {
            std::cout << ptr3->name << std::endl;
        } else {
            std::cout << "No" << std::endl;
        }
    }

    if (CURRENT_TEST == 4) {
        std::vector<Document> documents;
        documents = parse_documents("input2.txt");
        relation<Document> rel(new documents_strategy);
        for (const auto &document : documents) {
            rel.insert(document);
        }
        int id = rel.insert_tree(new RB_tree<Document*> (new documents_ptr_strategy_id, false));
        rel.insert_tree(new RB_tree<Document*> (new documents_ptr_strategy_date, false));
        rel.insert_tree(new RB_tree<Document*> (new documents_ptr_strategy_cost, false));
        auto ptr = rel.search(id, documents[1]);
        auto ptr2 = rel.search(id, documents[0]);
        if (ptr != nullptr) {
            std::cout << ptr->patronymic << std::endl;
        } else {
            std::cout << "No" << std::endl;
        }
        if (ptr2 != nullptr) {
            std::cout << ptr2->patronymic << std::endl;
        } else {
            std::cout << "No" << std::endl;
        }
    }
}