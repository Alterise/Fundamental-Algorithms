#include <iostream>
#include <vector>
#include <deque>
#include <list>
using namespace std;

int main()
{
    vector<int> vec = {};
    if (!vec.empty())
    {
        cout << vec.front() << endl;
        cout << *vec.begin() << endl;
        cout << vec.at(0) << endl;
        cout << vec[0] << endl;
    }
}