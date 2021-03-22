#include <iostream>
#include <vector>
using namespace std;

bool find_in_range(const vector<int>::iterator iter1, const vector<int>::iterator iter2, int num) {
    for (auto iter = iter1; iter < iter2; iter++)
    {
        if (*iter == num) return true;
    }
    return false;
}

int main()
{
    vector<int> nums = { 1, 61, 9, 32, 5, 17, 4, 97, 35 };
    cout << find_in_range(nums.begin() + 2, nums.end() - 3, 35) << endl;
}