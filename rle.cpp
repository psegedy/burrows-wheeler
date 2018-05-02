#include "rle.h"

int RLEEncoding(std::string &str_in, std::string &str_out) {
    size_t c_cnt = 0; // char count
    size_t r_cnt = 1; // repeat count
    char sc;

    // algorithm from KKO
    char c;
    // need +1 iteration to write last sequence
    for (size_t i = 0; i <= str_in.size(); i++) {
        // get next char
        if (i < str_in.size())
            c = str_in[i];
        c_cnt++;
        if (c_cnt == 1) {
            sc = c;
            continue;
        }
        // don't compare on last iteration
        if (sc == c && i != str_in.size()) {
            r_cnt++;
            continue;
        }
        if (r_cnt < 4) {
            // write r_cnt times same character
            for (size_t i = 0; i < r_cnt; i++) {
                str_out += sc;
            }
            c_cnt = 1;
            r_cnt = 1;
            sc = c;
        }
        else {
            // write compressed sequence
            // delimiter, number of chars, char
            str_out += DELIM;
            str_out += std::to_string(r_cnt);
            str_out += sc;

            r_cnt = 1;
            c_cnt = 1;
            sc = c;
        }
    }

    return 0;
}

int RLEDecoding(std::string &str_in, std::string &str_out) {
    int flag = 0; // compress flag
    std::string digit = "";
    size_t n;

    for(auto& c : str_in) {
        if (flag == 0) {
            // if format is compressed
            if (c == DELIM)
                flag = 1;
            else
                str_out += c;
            continue;
        }
        // get n from compressed format
        if (flag && std::isdigit(c)) {
            digit += c;
        }
        // print character n times
        else {
            n = std::stoul(digit);
            for (size_t i = 0; i < n; i++)
                str_out += c;
            flag = 0;
            digit = "";
        }

    }

    return 0;
}