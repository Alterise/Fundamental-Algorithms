#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int main()
{
    int N;
    cin >> N;
    deque<string> strings(N);

    for (auto& i : strings)
    {
        cin >> i;
    }

    cout << endl;
    for (auto& i : strings)
    {
        cout << i << endl;
    }
}