#include <iostream>
#include <vector>
using namespace std;

int main()
{
    const int k = 8;
    auto f = [k](int a){return a + k;};
    cout << f(7) << endl;
}