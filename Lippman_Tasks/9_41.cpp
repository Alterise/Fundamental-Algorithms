#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
	vector<char> vec_str = { 'b', 'a', 'b', 'a', 'b', 'o', 'y' };
	string str(vec_str.begin(), vec_str.end());
	cout << str << endl;
}