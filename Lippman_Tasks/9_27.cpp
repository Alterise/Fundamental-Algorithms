#include <iostream>
#include <vector>
#include <forward_list>
using namespace std;

int main()
{
	forward_list<int> lst = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	auto prev = lst.before_begin();
	auto curr = lst.begin();
	while (curr != lst.end())
	{
		if (*curr % 2)
		{
			curr = lst.erase_after(prev);
		}
		else
		{
			prev = curr;
			curr++;
		}
	}

	for (auto& i : lst)
	{
		cout << i << " ";
	}
}