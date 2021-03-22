#include <iostream>
#include <vector>
#include <list>
using namespace std;

int main()
{
    vector<int> my_vec = { 1, 2, 3, 4, 5 };
    list<int> my_list = { 1, 2, 3, 4, 5 };
    bool is_equal = (my_list.size() == my_vec.size());
    if (is_equal)
    {
        auto iter1 = my_vec.begin();
        auto iter2 = my_list.begin();
        for (iter1, iter2; (iter1 != my_vec.end() || iter2 != my_list.end()); iter1++, iter2++)
        {
            if (*iter1 != *iter2)
            {
                is_equal = false;
                break;
            }
        }
    }

    cout << is_equal << endl;
}