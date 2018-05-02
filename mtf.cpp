#include "mtf.h"



int MTFEncoding(std::fstream &input, std::vector<size_t> &mtf_enc) {
    std::list<char> alphabet;
    // initialize alphabet
    for (int i = 0; i < 255; ++i)
        alphabet.push_front(char(i));

    // input to string
    std::string str((std::istreambuf_iterator<char>(input)),
                     std::istreambuf_iterator<char>());

    size_t rank = 0;

    for(char& c : str) {
        // get rank of char
        rank = distance(alphabet.begin(), find(alphabet.begin(), alphabet.end(), c));
        mtf_enc.push_back(rank);

        // update alphabet
        alphabet.remove(c);
        alphabet.push_front(c);
    }

    return 0;
}

int MTFDecoding(std::vector<size_t> &mtf_enc, std::string &mtf_dec) {
    std::list<char> alphabet;
    // initialize alphabet
    for (int i = 0; i < 255; ++i)
        alphabet.push_front(char(i));

    for(auto i : mtf_enc) {
        // iterator to given char in alphabet
        auto it = std::next(alphabet.begin(), i);
        char e = *it;
        mtf_dec += e;

        // update alphabet
        alphabet.erase(it);
        alphabet.push_front(e);
    }

    return 0;
}