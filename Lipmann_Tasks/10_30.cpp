#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
using namespace std;

int main()


{
    istream_iterator<string> i_it(cin);
    ostream_iterator<string> o_it(cout, " ");
    istream_iterator<string> eof;
    vector<string> vec(i_it, eof);
    sort(vec.begin(), vec.end());
    copy(vec.begin(), vec.end(), o_it);
}