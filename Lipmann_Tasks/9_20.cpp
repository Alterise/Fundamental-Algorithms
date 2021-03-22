#include <iostream>
#include <vector>
#include <deque>
#include <list>
using namespace std;
int main()
{
    list<int> nums = { 1, 2, 3, 4, 5, 6, 7, 8 };
    deque<int> odd, even;

    for (auto& i : nums)
    {
        if (i % 2)
        {
            odd.push_back(i);
        }
        else
        {
            even.push_back(i);
        }
    }

    for (auto& i : odd)
    {
        cout << i << " ";
    }
    cout << endl;

    for (auto& i : even)
    {
        cout << i << " ";
    }
}