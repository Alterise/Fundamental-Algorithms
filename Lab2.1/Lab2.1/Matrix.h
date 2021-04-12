#pragma once
#include <exception>
#include <iostream>

using namespace std;

class Matrix
{
public:
	Matrix(int size = 0, double default_value = 0) {
		if (size < 0) {
			throw invalid_argument("Invalid matrix size");
		}
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

	Matrix(const Matrix& to_copy) {
		size_value = to_copy.size_value;
		data = new double* [size_value];
		for (size_t i = 0; i < size_value; i++)
		{
			data[i] = new double[size_value];
			for (size_t j = 0; j < size_value; j++)
			{
				data[i][j] = to_copy.data[i][j];
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

	Matrix operator=(const Matrix& rhs) {
		for (size_t i = 0; i < size_value; i++)
		{
			delete data[i];
		}
		delete[] data;

		size_value = rhs.size_value;
		data = new double* [size_value];
		for (size_t i = 0; i < size_value; i++)
		{
			data[i] = new double[size_value];
			for (size_t j = 0; j < size_value; j++)
			{
				data[i][j] = rhs.data[i][j];
			}
		}
		return *this;
	}

	Matrix operator+(const Matrix& rhs) {
		if (size_value != rhs.size_value) {
			throw invalid_argument("Matrices' sizes aren't equal");
		}

		for (size_t i = 0; i < size_value; i++)
		{
			for (size_t j = 0; j < size_value; j++)
			{
				data[i][j] += rhs.data[i][j];
			}
		}
		return *this;
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