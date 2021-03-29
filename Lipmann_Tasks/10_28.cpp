#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <queue>
#include <list>
using namespace std;
int main()

{
    vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    list<int> lst1 (vec.begin(), vec.end());
    list<int> lst2 (vec.begin(), vec.end());
    list<int> lst3 (vec.begin(), vec.end());
    auto in = inserter(lst1, find(lst1.begin(), lst1.end(), 5));
    auto b_in = back_inserter(lst2);
    auto f_in = front_inserter(lst3);
    
    in = 83;
    in = 82;
    in = 81;
    for (auto &i : lst1)
    {
        cout << i << " ";
    }
    cout << endl;

    b_in = 81;
    b_in = 82;
    b_in = 83;
    for (auto &i : lst2)
    {
        cout << i << " ";
    }
    cout << endl;
    
    f_in = 83;
    f_in = 82;
    f_in = 81;
    for (auto &i : lst3)
    {
        cout << i << " ";
    }
    cout << endl;

}