#include <iostream>
#include <vector>
#include <list>
using namespace std;

int main()
{
    int N;
    cin >> N;
    //�� � ��� ����� ������� deque �� list
    list<string> strings(N);

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