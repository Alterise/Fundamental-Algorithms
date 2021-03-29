#include <iostream>
#include <forward_list>
#include <string>
using namespace std;

void insert_in_list(forward_list<string>& lst, const string& str1, const string& str2)
{
	auto prev = lst.before_begin();
	auto curr = lst.begin();
	for (curr, prev; curr != lst.end(); curr++, prev++)
	{
		if (*curr == str1)
		{
			break;
		}
	}
	if (curr != lst.end())
	{
		lst.insert_after(curr, str2);
	}
	else
	{
		lst.insert_after(prev, str2);

	}
}

int main()
{
	forward_list<string> lst = { "Somebody", "once", "told", "me" };
	insert_in_list(lst, "once", "memes");

	for (auto& i : lst)
	{
		cout << i << " ";
	}
}