// Author: Patrik Segedy, xseged00, <xseged00@vutbr.cz>
// File: main.cpp
// Date: 29.4.2018
// Description: Burrows-Wheeler Transformation application
//              BWT -> MTF -> RLE-0 -> Entropy coder
#include "bwted.h"
#include "mtf.h"
#include "rle.h"

using namespace std;


int main(int argc, char const **argv) {
    fstream ifs("test/test.txt", istream::in);
    fstream banana("test_in.txt", istream::in);
    fstream test5k("test_5k.txt", istream::in);
    fstream test30k("test_30k.txt", istream::in);
    fstream test100k("test_100k.txt", istream::in);
    fstream ofs("test_out.txt", ios_base::out|ios_base::in|ios_base::trunc);
    fstream ofs2("test_out2.txt", ostream::out);
    tBWTED bwted;

    // BWTEncoding(&bwted, test30k, ofs);



    // ofs.seekg (0, ofs.beg);

    // BWTDecoding(&bwted, ofs, ofs2);

    // vector<size_t> v;

    // MTFEncoding(banana, v);
    // for(auto i : v) {
    //     cout << i << " ";
    // }
    // cout << endl;

    // string mtf_dec = "";
    // MTFDecoding(v, mtf_dec);
    // std::cout << "decoded" << endl;
    // cout << mtf_dec << endl;


    string a("abcd");
    string b("aabcd");
    string c("abbbcd");
    string d("aaaaaaabccccccd");
    string e("aaaaaaabccccccdddddd");

    string out = "";
    string out2 = "";

    RLEEncoding(a, out);
    cout << a << ": " << out << endl;
    RLEDecoding(out, out2);
    cout << out2 << endl;
    out2 = "";
    out = "";

    RLEEncoding(b, out);
    cout << b << ": " << out << endl;
    RLEDecoding(out, out2);
    cout << out2 << endl;
    out2 = "";
    out = "";

    RLEEncoding(c, out);
    cout << c << ": " << out << endl;
    RLEDecoding(out, out2);
    cout << out2 << endl;
    out2 = "";
    out = "";

    RLEEncoding(d, out);
    cout << d << ": " << out << endl;
    RLEDecoding(out, out2);
    cout << out2 << endl;
    out2 = "";
    out = "";

    RLEEncoding(e, out);
    cout << e << ": " << out << endl;
    RLEDecoding(out, out2);
    cout << out2 << endl;
    out2 = "";
    out = "";





    ifs.close();
    ofs.close();
    ofs2.close();

    return 0;
}