#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    vector<string> strings;
    vector<const char*> c_strings = { "Somebody", "once", "told", "me" };

    strings.assign(c_strings.cbegin(), c_strings.cend());

    for (auto& i : strings)
    {
        cout << i << endl;
    }
}