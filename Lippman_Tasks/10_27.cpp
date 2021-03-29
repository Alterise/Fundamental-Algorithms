#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
using namespace std;
int main()

{
    vector<int> vec = {1, 7, 9, 3, 5, 7, 5, 2, 8, 3, 2, 1, 4, 9, 0, 4, 8};
    sort(vec.begin(), vec.end());
    list<int> lst(vec.size());
    list<int>::iterator it = unique_copy(vec.begin(), vec.end(), lst.begin());
    lst.resize(distance(lst.begin(), it));
    for (auto &i : lst)
    {
        cout << i << endl;
    }
    
}