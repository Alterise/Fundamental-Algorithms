#include <iostream>
#include <vector>
using namespace std;

vector<int>::iterator find_in_range(const vector<int>::iterator iter1, const vector<int>::iterator iter2, int num) {
    auto iter = iter1;
    for (iter; iter < iter2; iter++)
    {
        if (*iter == num) break;
    }
    return iter;
}

int main()
{
    vector<int> nums = { 1, 61, 9, 32, 5, 17, 4, 97, 35 };
    vector<int>::iterator iter1 = nums.begin() + 2;
    vector<int>::iterator iter2 = nums.end() - 3;
    auto found_iter = find_in_range(iter1, iter2, 17);
    if (found_iter == iter2) {
        cout << "Value WASN'T found" << endl;
    }
    else {
        cout << "Value WAS found" << endl;
        cout << "Value: " << *found_iter << endl;
    }
}