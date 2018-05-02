#include "mtf.h"

int MTFEncoding(std::string &str, std::string &mtf_enc, std::list<char> alphabet) {
    uint8_t rank = 0;

    for(char& c : str) {
        // get rank of char
        rank = distance(alphabet.begin(), find(alphabet.begin(), alphabet.end(), c));
        mtf_enc += rank;

        // update alphabet
        alphabet.remove(c);
        alphabet.push_front(c);
    }

    return 0;
}

int MTFDecoding(std::string &mtf_enc, std::string &mtf_dec, std::list<char> alphabet) {
    for(auto& i : mtf_enc) {
        // iterator to given char in alphabet
        auto it = std::next(alphabet.begin(), i);
        // char from iterator
        char e = *it;
        // write char to output
        mtf_dec += e;

        // update alphabet
        alphabet.erase(it);
        alphabet.push_front(e);
    }

    return 0;
}