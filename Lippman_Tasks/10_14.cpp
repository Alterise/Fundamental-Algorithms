#include <iostream>
#include <vector>
using namespace std;

int main()
{
    auto f = [](int a, int b){return a + b;};
    cout << f(5, 9) << endl;
}