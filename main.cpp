// Author: Patrik Segedy, xseged00, <xseged00@vutbr.cz>
// File: main.cpp
// Date: 29.4.2018
// Description: Burrows-Wheeler Transformation application
//              BWT -> MTF -> RLE-0 -> Entropy coder
#include "bwted.h"
#include "mtf.h"

using namespace std;


int main(int argc, char const **argv) {
    fstream ifs("test/test.txt", istream::in);
    fstream banana("test_in.txt", istream::in);
    fstream ofs("test_out.txt", ios_base::out|ios_base::in|ios_base::trunc);
    fstream ofs2("test_out2.txt", ostream::out);
    tBWTED bwted;

    // BWTEncoding(&bwted, ifs, ofs);



    // ofs.seekg (0, ofs.beg);

    // BWTDecoding(&bwted, ofs, ofs2);

    vector<size_t> v;

    MTFEncoding(banana, v);
    for(auto i : v) {
        cout << i << " ";
    }
    cout << endl;

    string mtf_dec = "";
    MTFDecoding(v, mtf_dec);
    std::cout << "decoded" << endl;
    cout << mtf_dec << endl;

    ifs.close();
    ofs.close();
    ofs2.close();

    return 0;
}