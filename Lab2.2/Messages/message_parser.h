#pragma once
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "messages.h"

std::vector<Message> parse_messages(const std::string& filename) {
    std::vector<Message> messages;
    std::ifstream input_file(filename);
    std::stringstream line_stream;
    std::string line;
    Message current_message;
    while(getline(input_file, line)) {
        line_stream.clear();
        line_stream.str(line);
        line_stream >> current_message.date.day;
        line_stream.ignore(1);
        line_stream >> current_message.date.month;
        line_stream.ignore(1);
        line_stream >> current_message.date.year;
        getline(line_stream, current_message.name, ':');
        line_stream.ignore(1);
        getline(line_stream, current_message.data);
        messages.push_back(current_message);
    }
    return messages;
}