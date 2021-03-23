#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

struct Sales_data
{
	string isbn() const { return bookNo; }
	Sales_data& combine(const Sales_data&);
	double avg_price() const;

	string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};

Sales_data add(const Sales_data&, const Sales_data&);
ostream& print(ostream&, const Sales_data&);
istream& read(istream&, Sales_data&);

bool compareIsbn(const string& s1, const string& s2)
{
	return s1.size() < s2.size();
}


int main()
{

}