#pragma once
#include "Matrix.h"
#include <exception>
#include <iostream>
#include <sstream>
#include <string>

//// Examples
 //expression [[1, 5, 2], [4, 9, 5], [8, 7, 6]] + [[0, 2, 1], [8, 2, 7], [3, 2, 5]]
 //expression [[1, 5, 2], [4, 9, 5], [8, 7, 6]] - [[0, 2, 1], [8, 2, 7], [3, 2, 5]]
 //expression [[1, 5, 2], [4, 9, 5], [8, 7, 6]] * [[0, 2, 1], [8, 2, 7], [3, 2, 5]]
 //expression [[1, 5, 2], [4, 9, 5], [8, 7, 6]] * 5
 //expression 8 * [[0, 2, 1], [8, 2, 7], [3, 2, 5]]
 //expression [[1, 5, 2], [4, 9, 5], [8, 7, 6]] == [[0, 2, 1], [8, 2, 7], [3, 2, 5]]
 //expression [[1, 5, 2], [4, 9, 5], [8, 7, 6]] != [[0, 2, 1], [8, 2, 7], [3, 2, 5]]
 //determinant [[1, 5, 2], [4, 9, 5], [8, 7, 6]]
 //reversed [[1, 5, 2], [4, 9, 5], [8, 7, 6]]
 //transpose [[1, 5, 2], [4, 9, 5], [8, 7, 6]]
 //trace [[1, 5, 2], [4, 9, 5], [8, 7, 6]]
 //exponential [[1, 5, 2], [4, 9, 5], [8, 7, 6]]

string get_operand(istream&);
void skip_spaces(istream&);

void parse(istream& input_stream, ostream& output_stream) {
	string line;
	stringstream line_stream;
	while (getline(input_stream, line)) {
		if (line == "") {
			continue;
		}
		try {
			line_stream.clear();
			line_stream.str(line);
			int result_switcher = 0;
			bool bool_result;
			double double_result;
			string instruction;
			string operation;
			string operand1;
			string operand2;
			double num_operand;
			int num_operand_position = 0;
			Matrix matrix1;
			Matrix matrix2;
			Matrix final_matrix;

			line_stream >> instruction;
			if (instruction == "expression") {
				operand1 = get_operand(line_stream);
				line_stream >> operation;
				operand2 = get_operand(line_stream);
				try {
					if (operand1[0] == '[') {
						istringstream tmp_stream(operand1);
						tmp_stream >> matrix1;
					}
					else if (isdigit(operand1[0])) {
						num_operand = stod(operand1);
						num_operand_position = -1;
					}
					else {
						throw exception();
					}
				}
				catch (exception&) {
					throw invalid_argument("Invalid operand");
				}

				try {
					if (operand2[0] == '[') {
						istringstream tmp_stream(operand2);
						tmp_stream >> matrix2;
					}
					else if (isdigit(operand2[0])) {
						num_operand = stod(operand2);
						num_operand_position = 1;
					}
					else {
						throw exception();
					}
				}
				catch (exception&) {
					throw invalid_argument("Invalid operand");
				}

				if (operation == "+") {
					final_matrix = matrix1 + matrix2;
				}
				else if (operation == "-") {
					final_matrix = matrix1 - matrix2;
				}
				else if (operation == "*") {
					if (!num_operand_position) {
						final_matrix = matrix1 * matrix2;
					}
					else if (num_operand_position == 1) {
						final_matrix = matrix1 * num_operand;
					}
					else {
						final_matrix = num_operand * matrix2;
					}
				}
				else if (operation == "==") {
					result_switcher = 1;
					bool_result = (matrix1 == matrix2);
				}
				else if (operation == "!=") {
					result_switcher = 1;
					bool_result = (matrix1 != matrix2);
				}
				else {
					throw invalid_argument("Invalid operation");
				}

			}
			else if (instruction == "determinant") {
				operand1 = get_operand(line_stream);
				istringstream tmp_stream(operand1);
				tmp_stream >> matrix1;
				double_result = determinant(matrix1);
				result_switcher = 2;
			}
			else if (instruction == "reversed") {
				operand1 = get_operand(line_stream);
				istringstream tmp_stream(operand1);
				tmp_stream >> matrix1;
				final_matrix = reversed(matrix1);
			}
			else if (instruction == "transpose") {
				operand1 = get_operand(line_stream);
				istringstream tmp_stream(operand1);
				tmp_stream >> matrix1;
				final_matrix = transpose(matrix1);
			}
			else if (instruction == "trace") {
				operand1 = get_operand(line_stream);
				istringstream tmp_stream(operand1);
				tmp_stream >> matrix1;
				double_result = trace(matrix1);
				result_switcher = 2;
			}
			else if (instruction == "exponential") {
				operand1 = get_operand(line_stream);
				istringstream tmp_stream(operand1);
				tmp_stream >> matrix1;
				final_matrix = exponential(matrix1);
			}
			else {
				throw invalid_argument("Wrong instruction");
			}

			output_stream << "Input: " << endl << line << endl << endl;
			if (result_switcher == 0) {
				output_stream << "Result: " << endl << final_matrix << endl;
			}
			else if (result_switcher == 1) {
				output_stream << "Result: " << endl << (bool_result ? "TRUE" : "FALSE") << endl << endl;
			}
			else {
				output_stream << "Result: " << endl << double_result << endl << endl;
			}
		}
		catch (invalid_argument& ex) {
			cerr << ex.what() << endl;
		}
	}
}

string get_operand(istream& stream) {
	string operand;
	while (stream.peek() == ' ') {
		stream.ignore(1);
	}
	if (stream.peek() == '[') {
		operand.push_back(stream.get());
		size_t brackets = 1;
		while (brackets) {
			if (stream.peek() != EOF) {
				operand.push_back(stream.get());
				if (operand.back() == '[') {
					brackets++;
				}
				else if (operand.back() == ']') {
					brackets--;
				}
			}
			else {
				throw invalid_argument("Invalid operand");
			}
		}
	}
	else if (isdigit(stream.peek())) {
		stream >> operand;
	}
	else {
		throw invalid_argument("Invalid operand");
	}
	return operand;
}