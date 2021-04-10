#pragma once
#include <exception>
#include <iostream>

using namespace std;

class Matrix
{
public:
	Matrix(size_t size = 0, double default_value = 0) {
		size_value = size;
		data = new double* [size_value];
		for (size_t i = 0; i < size_value; i++)
		{
			data[i] = new double[size_value];
			for (size_t j = 0; j < size_value; j++)
			{
				data[i][j] = default_value;
			}
		}
	}
	~Matrix() {
		for (size_t i = 0; i < size_value; i++)
		{
			delete data[i];
		}
		delete[] data;
	}

	void print() {
		for (size_t i = 0; i < size_value; i++)
		{
			for (size_t j = 0; j < size_value; j++)
			{
				cout << data[i][j] << " ";
			}
			cout << endl;
		}
	}
private:
	double** data;
	size_t size_value;
};