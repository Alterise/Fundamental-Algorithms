#pragma once
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "documents.h"

std::vector<Document> parse_documents(const std::string& filename) {
    std::vector<Document> documents;
    std::ifstream input_file(filename);
    std::stringstream line_stream;
    std::string line;
    Document current_document;
    Arrangement current_arrangement;
    std::string tmp;
    while(getline(input_file, line)) {
        if (line == "{") {
            getline(input_file, line);
            while(line != "}") {
                line_stream.clear();
                line_stream.str(line);
                line_stream >> current_arrangement.number;
                line_stream >> tmp;
                line_stream >> current_arrangement.start_date.day;
                line_stream.ignore(1);
                line_stream >> current_arrangement.start_date.month;
                line_stream.ignore(1);
                line_stream >> current_arrangement.start_date.year;
                line_stream >> tmp;
                line_stream >> tmp;
                line_stream >> current_arrangement.cost;
                if (tmp != "present") {
                    line_stream.clear();
                    line_stream.str(tmp);
                    line_stream >> current_arrangement.end_date.day;
                    line_stream.ignore(1);
                    line_stream >> current_arrangement.end_date.month;
                    line_stream.ignore(1);
                    line_stream >> current_arrangement.end_date.year;
                    current_arrangement.is_finished = true;
                } else {
                    current_arrangement.is_finished = false;
                    current_arrangement.end_date.day = 0;
                    current_arrangement.end_date.month = 0;
                    current_arrangement.end_date.year = 0;
                }
                current_document.arrangements.push_back(current_arrangement);
                getline(input_file, line);
            }
            documents.push_back(current_document);
        } else {
            line_stream.clear();
            line_stream.str(line);
            line_stream >> current_document.name >> current_document.surname >> current_document.patronymic;
        }
    }
    return documents;
}