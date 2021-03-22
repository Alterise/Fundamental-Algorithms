#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> vec1 = { 1, 2, 3, 4, 5 };
    vector<int> vec2 = { 1, 2, 3, 4, 5 };
    cout << (vec1 == vec2) << endl;
}