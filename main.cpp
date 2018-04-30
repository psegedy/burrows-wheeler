// Author: Patrik Segedy, xseged00, <xseged00@vutbr.cz>
// File: main.cpp
// Date: 29.4.2018
// Description: Burrows-Wheeler Transformation application
//              BWT -> MTF -> RLE-0 -> Entropy coder
#include "bwted.h"

using namespace std;


int main(int argc, char const **argv) {
    fstream ifs("test_in.txt", istream::in);
    fstream ofs("test_out.txt", ios_base::out|ios_base::in|ios_base::trunc);
    fstream ofs2("test_out2.txt", ostream::out);
    tBWTED bwted;

    BWTEncoding(&bwted, ifs, ofs);

    // fstream ifs("test_out.txt", istream::in);
    // ifs.open
    // ofs.Seek(0, SeekOrigin.Begin);
    ofs.seekg (0, ofs.beg);

    BWTDecoding(&bwted, ofs, ofs2);

    ifs.close();
    ofs.close();

    return 0;
}