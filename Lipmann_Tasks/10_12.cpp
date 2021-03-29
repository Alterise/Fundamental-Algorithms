#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

struct Sales_data
{
	string isbn() const { return bookNo; }
	// Sales_data& combine(const Sales_data&);
	// double avg_price() const;

	string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};

bool compareIsbn(const Sales_data& sd1, const Sales_data& sd2)
{
	return sd1.isbn() < sd2.isbn();
}


int main()
{
	vector<Sales_data> sd_vec = {{"somebody", 41, 187.33}, {"once", 39, 127.36}, {"one", 16, 255.32},
	{"something", 94, 11.33}, {"bababoy", 141, 1821.23}};
	sort(sd_vec.begin(), sd_vec.end(), compareIsbn);
	for (auto &i : sd_vec)
	{
		cout << i.isbn() << endl;
	}
	
}