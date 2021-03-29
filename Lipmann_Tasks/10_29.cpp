#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
using namespace std;

int main()


{
    ifstream File("text.txt");
    istream_iterator<string> it(File);
    istream_iterator<string> eof;
    vector<string> vec(it, eof);
    for (auto &i : vec)
    {
        cout << i << " ";        
    }
    
}