#include <iostream>
#include <vector>
#include <string>
using namespace std;

void replace_substr(string& str, const string& substr_to_replace, const string& replacement)
{
	if (substr_to_replace.empty())
	{
		return;
	}
	for (auto i = str.begin(); i < str.end();)
	{
		if (*i == *substr_to_replace.begin())
		{
			auto iter1 = i;
			auto iter2 = substr_to_replace.begin();
			for (iter1, iter2; (iter1 < str.end()) && (iter2 < substr_to_replace.end() && (*iter1 == *iter2));
				iter1++, iter2++);
			if (iter2 == substr_to_replace.end())
			{
				str.erase(i, i + substr_to_replace.length());
				i = str.insert(i, replacement.begin(), replacement.end()) + replacement.length();
			}
			else
			{
				i++;
			}
		}
		else
		{
			i++;
		}
	}
}

int main()
{
	string str = "bababoy boba boy";
	replace_substr(str, "ba", "YAY");
	cout << str;
}