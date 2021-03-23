#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

bool isShorter(const string& s1, const string& s2)
{
	return s1.size() < s2.size();
}

bool isSame(const string& s1, const string& s2)
{
	return s1.size() == s2.size();
}

void elimDups(vector<string>& words)
{
	stable_sort(words.begin(), words.end(), isShorter);
	auto end_unique = unique(words.begin(), words.end(), isSame);

	words.erase(end_unique, words.end());
}

int main()
{
	vector<string> vec = { "somebody", "once", "told", "once", "once", "me", "memes", "told", "memes", "bababoy" };
	elimDups(vec);
	for (auto& i : vec)
	{
		cout << i << " ";
	}
}