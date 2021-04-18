#pragma once
#include <exception>
#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

struct Index
{
	int y;
	int x;
};

class Matrix
{
private:
	double** data;
	size_t size_value;
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

	void operator+=(const Matrix& rhs) {
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
	}

	Matrix operator+(const Matrix& rhs) {
		if (size_value != rhs.size_value) {
			throw invalid_argument("Matrices' sizes aren't equal");
		}

		Matrix sum(*this);
		sum += rhs;
		return sum;
	}

	void operator-=(const Matrix& rhs) {
		if (size_value != rhs.size_value) {
			throw invalid_argument("Matrices' sizes aren't equal");
		}

		for (size_t i = 0; i < size_value; i++)
		{
			for (size_t j = 0; j < size_value; j++)
			{
				data[i][j] -= rhs.data[i][j];
			}
		}
	}

	Matrix operator-(const Matrix& rhs) {
		if (size_value != rhs.size_value) {
			throw invalid_argument("Matrices' sizes aren't equal");
		}

		Matrix diff(*this);
		diff -= rhs;
		return diff;
	}

	void operator*=(const Matrix& rhs) {
		if (size_value != rhs.size_value) {
			throw invalid_argument("Matrices' sizes aren't equal");
		}

		Matrix tmp(*this);

		for (size_t i = 0; i < size_value; i++)
		{
			for (size_t j = 0; j < size_value; j++)
			{
				double sum = 0;
				for (size_t k = 0; k < size_value; k++)
				{
					sum += tmp.data[j][k] * rhs.data[k][j];
				}
				data[i][j] = sum;
			}
		}
	}

	void operator*=(const double& rhs) {

		for (size_t i = 0; i < size_value; i++)
		{
			for (size_t j = 0; j < size_value; j++)
			{
				data[i][j] *= rhs;
			}
		}
	}

	Matrix operator*(const Matrix& rhs) {
		if (size_value != rhs.size_value) {
			throw invalid_argument("Matrices' sizes aren't equal");
		}

		Matrix tmp(*this);
		tmp *= rhs;
		return tmp;
	}

	Matrix operator*(const double& rhs) {

		Matrix tmp(*this);
		tmp *= rhs;
		return tmp;
	}

	friend Matrix operator*(const double& lhs, const Matrix& rhs) {
		Matrix tmp(rhs);
		tmp *= lhs;
		return tmp;
	}

	bool operator==(const Matrix& rhs) {
		if (size_value != rhs.size_value) {
			throw invalid_argument("Matrices' sizes aren't equal");
		}

		double e = 1e-6;
		for (size_t i = 0; i < size_value; i++)
		{
			for (size_t j = 0; j < size_value; j++)
			{
				if (fabs(data[i][j] - rhs.data[i][j]) > 1e-6) return false;
			}
		}
		return true;
	}

	bool operator!=(const Matrix& rhs) {
		return !(*this == rhs);
	}

	double& operator[](const Index& index) {
		if (index.x < 0 || index.y < 0 || index.x >= size_value || index.y >= size_value) {
			throw invalid_argument("Index out of bounds");
		}

		return data[index.y][index.x];
	}

	friend ostream& operator<<(ostream& stream, const Matrix& matrix) {
		for (size_t i = 0; i < matrix.size_value; i++)
		{
			for (size_t j = 0; j < matrix.size_value; j++)
			{
				stream << matrix.data[i][j] << " ";
			}
			stream << endl;
		}
		return stream;
	}

	friend istream& operator>>(istream& stream, Matrix& matrix) {
		string str_tmp;
		getline(stream, str_tmp);
		istringstream tmp_stream(str_tmp);
		Matrix tmp = matrix;
		char sym;
		tmp_stream >> sym;
		if (sym != '[') {
			throw invalid_argument("Wrong input");
		}
		for (size_t i = 0; i < tmp.size_value; i++)
		{
			tmp_stream >> sym;
			if (sym != '[') {
				throw invalid_argument("Wrong input");
			}
			for (size_t j = 0; j < tmp.size_value; j++)
			{
				try {
					tmp_stream >> tmp.data[i][j];
				} catch(exception& ex) {
					throw invalid_argument("Wrong input");
				}
				if ((j + 1) < tmp.size_value) {
					tmp_stream >> sym;
					if (sym != ',') {
						throw invalid_argument("Wrong input");
					}
				}
			}
			tmp_stream >> sym;
			if (sym != ']') {
				throw invalid_argument("Wrong input");
			}
			if ((i + 1) < tmp.size_value) {
				tmp_stream >> sym;
				if (sym != ',') {
					throw invalid_argument("Wrong input");
				}
			}
		}
		if (sym != ']') {
			throw invalid_argument("Wrong input");
		}
		tmp_stream >> sym;
		while ((sym = tmp_stream.get()) == ' ');
		if (sym != EOF) {
			throw invalid_argument("Wrong input");
		}
		matrix = tmp;
		return stream;
	}

	friend Matrix transpose(const Matrix& matrix) {
		Matrix new_matrix(matrix);
		for (size_t i = 0; i < new_matrix.size_value; i++)
		{
			for (size_t j = i + 1; j < new_matrix.size_value; j++)
			{
				swap(new_matrix.data[i][j], new_matrix.data[j][i]);
			}
		}
		return new_matrix;
	}

	friend double determinant(const Matrix& matrix) {
		//Computing determinant using Gaussian elimination
		double det = 1, mtp, key_elem;
		Matrix tmp_matrix(matrix);
		for (size_t i = 0; i < tmp_matrix.size_value; i++)
		{
			key_elem = tmp_matrix.data[i][i];
			int j;
			if (!key_elem)
			{
				j = i + 1;
				while (!key_elem && j < tmp_matrix.size_value)
				{
					key_elem = tmp_matrix.data[j][i];
					j++;
				}
				j--;
				if (!key_elem)
				{
					return 0;
				}
				else
				{
					for (size_t k = i; k < tmp_matrix.size_value; k++)
					{
						tmp_matrix.data[i][k] += tmp_matrix.data[j][k];
					}
				}
			}

			for (j = i + 1; j < tmp_matrix.size_value; j++)
			{
				mtp = tmp_matrix.data[j][i] / key_elem;
				tmp_matrix.data[j][i] = 0;
				for (size_t k = i + 1; k < tmp_matrix.size_value; k++)
				{
					tmp_matrix.data[j][k] = tmp_matrix.data[j][k] - tmp_matrix.data[i][k] * mtp;
				}
			}
			det *= key_elem;
		}

		return det;
	}

	friend Matrix reversed(const Matrix &matrix) {
		double det = determinant(matrix);
		Matrix reversed_matrix(matrix.size_value);
		for (size_t i = 0; i < matrix.size_value; i++)
		{
			for (size_t j = 0; j < matrix.size_value; j++)
			{
				reversed_matrix.data[i][j] = determinant(matrix.getminor({(int)i, (int)j})) * 
											 ((i + j) % 2 ? -1 : 1);
			}
		}
		reversed_matrix = transpose(reversed_matrix);

		for (size_t i = 0; i < matrix.size_value; i++)
		{
			for (size_t j = 0; j < matrix.size_value; j++)
			{
				reversed_matrix.data[i][j] /= det;
			}
		}

		return reversed_matrix;
	}

private:
	Matrix getminor(const Index& index) const {
		size_t m_i = 0, m_j = 0;
		Matrix block(size_value - 1);
		for (size_t i = 0; i < size_value; i++)
		{
			if (i == index.y) {
				continue;
			}
			m_j = 0;
			for (size_t j = 0; j < size_value; j++)
			{
				if (j == index.x) {
					continue;
				}
				block.data[m_i][m_j] = data[i][j];
				m_j++;
			}
			m_i++;
		}
		return block;
	}
};

