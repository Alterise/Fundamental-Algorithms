#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void skip_spaces(std::istream&);

void compress(const std::string input_name, const std::string output_name) {
    std::ifstream pgn_input(input_name);
    std::ofstream bin_output(output_name, std::ios::binary);
    std::vector<std::string> tags;
    tags.reserve(7);
    std::vector<std::string> moves;
    std::vector<std::string> internal_comments(0);
    std::vector<std::string> line_comments(0);
    std::string str_tmp;
    for (int i = 0; i < 7; ++i) {
        getline(pgn_input, str_tmp, '"');
        getline(pgn_input, str_tmp, '"');
        tags.push_back(str_tmp);
        getline(pgn_input, str_tmp);
    }
    for (const auto &item : tags) {
        bin_output << item << std::endl;
    }

    skip_spaces(pgn_input);
    while(pgn_input.peek() != EOF) {
        if(isdigit(pgn_input.peek())) {
            pgn_input >> str_tmp;
        } else if(pgn_input.peek() == '{') {
            pgn_input.ignore(1);
            getline(pgn_input, str_tmp, '}');
            internal_comments.push_back(str_tmp);
            moves.push_back("icom");
        } else if(pgn_input.peek() == ';') {
            pgn_input.ignore(1);
            getline(pgn_input, str_tmp);
            line_comments.push_back(str_tmp);
            moves.push_back("lcom");
        } else {
            pgn_input >> str_tmp;
            moves.push_back(str_tmp);
        }
        skip_spaces(pgn_input);
    }

    size_t icomments_size = internal_comments.empty() ? 0 : internal_comments.size();
    size_t lcomments_size = line_comments.empty() ? 0 : line_comments.size();
    size_t moves_size = moves.empty() ? 0 : moves.size() - icomments_size - lcomments_size;
    bin_output <<  moves_size << " " << icomments_size << " " << lcomments_size << std::endl;

    for (const auto &item : moves) {
        bin_output << item << " ";
    }
    bin_output << std::endl;
    for (const auto &item : internal_comments) {
        bin_output << item << std::endl;
    }
    for (const auto &item : line_comments) {
        bin_output << item << std::endl;
    }
}

void skip_spaces(std::istream& stream) {
    while ((stream.peek() == ' ') || (stream.peek() == '\n')) {
        stream.ignore(1);
    }
}