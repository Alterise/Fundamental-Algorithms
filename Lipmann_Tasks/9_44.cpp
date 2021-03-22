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
	for (int i = 0; i < str.length();)
	{
		if (str[i] == substr_to_replace[0])
		{
			auto iter1 = i;
			auto iter2 = 0;
			for (iter1, iter2; (iter1 < str.length()) && (iter2 < substr_to_replace.length()
				&& (str[iter1] == substr_to_replace[iter2])); iter1++, iter2++);
			if (iter2 == substr_to_replace.length())
			{
				str.replace(i, substr_to_replace.length(), replacement);
				i += replacement.length();
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