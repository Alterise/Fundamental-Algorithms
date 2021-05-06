#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include "RB_tree.h"
#include "concrete_strategies.h"

int main()
{
    const int N = 500;
    RB_tree<int> tree(new int_strategy);
    std::vector<int> buffer;
    std::vector<int> buffer2;
    for (int i = 0; i < N; ++i) {
        buffer.push_back(rand() % 25000 - 12500);
        int a = buffer.back();
        tree.insert(a);
    }
    for (const auto &item : buffer) {
        cout << item << " ";
    }
    cout << endl << endl;
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