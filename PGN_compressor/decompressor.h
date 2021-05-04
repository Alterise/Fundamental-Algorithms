#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void decompress(const std::string input_name, const std::string output_name) {
    std::ifstream bin_input(input_name, std::ios::binary);
    std::ofstream pgn_output(output_name);
    std::vector<std::string> tags;
    tags.reserve(7);
    std::vector<std::string> moves;
    std::vector<std::string> internal_comments;
    std::vector<std::string> line_comments;
    std::string str_tmp;
    for (int i = 0; i < 7; ++i) {
        getline(bin_input, str_tmp);
        tags.push_back(str_tmp);
    }
    size_t icomments_size, lcomments_size, moves_size;
    bin_input >> moves_size >> icomments_size >> lcomments_size;

    for (int i = 0; i < (moves_size + icomments_size + lcomments_size); ++i) {
        bin_input >> str_tmp;
        moves.push_back(str_tmp);
    }
    skip_spaces(bin_input);
    for (int i = 0; i < icomments_size; ++i) {
        getline(bin_input, str_tmp);
        internal_comments.push_back(str_tmp);
    }
    for (int i = 0; i < lcomments_size; ++i) {
        getline(bin_input, str_tmp);
        line_comments.push_back(str_tmp);
    }

    pgn_output << "[Event \"" << tags[0] << "\"]" << std::endl;
    pgn_output << "[Site \"" << tags[1] << "\"]" << std::endl;
    pgn_output << "[Date \"" << tags[2] << "\"]" << std::endl;
    pgn_output << "[Round \"" << tags[3] << "\"]" << std::endl;
    pgn_output << "[White \"" << tags[4] << "\"]" << std::endl;
    pgn_output << "[Black \"" << tags[5] << "\"]" << std::endl;
    pgn_output << "[Result \"" << tags[6] << "\"]" << std::endl;
    pgn_output << std::endl;

    str_tmp.clear();
    bool is_black_move = false;
    int move_counter = 1;
    int icom_counter = 0;
    int lcom_counter = 0;
    for (const auto &item : moves) {
        if(item == "icom") {
            str_tmp += "{" + internal_comments[icom_counter++] + "} ";
        } else if(item == "lcom") {
            pgn_output << str_tmp << std::endl;
            str_tmp.clear();
            pgn_output << ";" + line_comments[lcom_counter++] << std::endl;
        } else {
            if(is_black_move) {
                move_counter++;
                str_tmp += item + " ";
                is_black_move = false;
            } else {
                str_tmp += std::to_string(move_counter) + ". " + item + " ";
                is_black_move = true;
            }
        }
        if(!is_black_move && str_tmp.length() > 80) {
            pgn_output << str_tmp << std::endl;
            str_tmp.clear();
        }
    }
    str_tmp += tags[6];
    pgn_output << str_tmp << std::endl;
}