#include <iostream>
#include <vector>
#include <list>
using namespace std;



int main()
{
	int ia[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89 };
	vector<int> vec(ia, ia + 11);
	list<int> lst(ia, ia + 11);

	auto iter = vec.begin();
	while (iter != vec.end())
	{
		if (!(*iter % 2))
			iter = vec.erase(iter);
		else
			iter++;
	}

	auto iter2 = lst.begin();
	while (iter2 != lst.end())
	{
		if (*iter2 % 2)
			iter2 = lst.erase(iter2);
		else
			iter2++;
	}

	for (auto& i : vec)
		cout << i << " ";
	cout << endl;
	for (auto& i : lst)
		cout << i << " ";
}