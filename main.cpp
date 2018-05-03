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
    fstream ifs("test/test.txt", istream::in|ios::ate);
    fstream banana("test_in.txt", istream::in);
    fstream test5k("test_5k.txt", istream::in);
    fstream test_start("test_start.txt", istream::in);
    fstream test_1ch("test_1ch.txt", istream::in);
    fstream test30k("test_30k.txt", istream::in);
    fstream test100k("test_100k.txt", istream::in);
    fstream ofs("test_out.txt", ios::out|ios::in|ios::trunc);
    fstream ofs2("test_out2.txt", ostream::out);
    tBWTED bwted;

    // string buff("", 5);
    // banana.seekg(0, banana.end);
    // cout << banana.tellg() << std::endl;
    // banana.seekg(0, banana.beg);
    // banana.read(&buff.front(), 5);
    // cout << buff << endl;
    // banana.seekg(5, banana.beg);
    // cout << banana.tellg() << std::endl;
    // banana.read(&buff.front(), 5);
    // cout << buff << endl;
    // // cout << buff << endl;
    // return 1;

    // std::list<char> alphabet;
    // // initialize alphabet
    // for (int i = 0; i < 255; ++i)
    //     alphabet.push_front(char(i));

    BWTEncoding(&bwted, test_1ch, ofs);
    cout << "Uncompressed: " << bwted.uncodedSize << endl;
    cout << "Compressed: " << ofs.tellg() << endl;
    cout << "Compressed bwt: " << bwted.codedSize << endl; 



    ofs.seekg (0, ofs.beg);

    BWTDecoding(&bwted, ofs, ofs2);

    // // vector<size_t> v;
    // string v;
    // string banan = "BAAANNA";
    // banan = STX + banan + ETX;

    // cout << "bana: " << banan << std::endl;

    // MTFEncoding(banan, v, alphabet);
    // cout << v << endl;

    // string mtf_dec = "";
    // MTFDecoding(v, mtf_dec, alphabet);
    // std::cout << "decoded" << endl;
    // cout << mtf_dec << endl;


    // string a = banan;
    // string b("aabcd");
    // string c("abbbcda");
    // string d("aaaaaaabccccccd");
    // string e("aaaaaaabccccccdddddd");

    // string out = "";
    // string out2 = "";

    // RLEEncoding(a, out);
    // cout << a << ": " << out << endl;
    // RLEDecoding(out, out2);
    // cout << out2 << endl;
    // out2 = "";
    // out = "";

    // RLEEncoding(b, out);
    // cout << b << ": " << out << endl;
    // RLEDecoding(out, out2);
    // cout << out2 << endl;
    // out2 = "";
    // out = "";

    // RLEEncoding(c, out);
    // cout << c << ": " << out << endl;
    // RLEDecoding(out, out2);
    // cout << out2 << endl;
    // out2 = "";
    // out = "";

    // RLEEncoding(d, out);
    // cout << d << ": " << out << endl;
    // RLEDecoding(out, out2);
    // cout << out2 << endl;
    // out2 = "";
    // out = "";

    // RLEEncoding(e, out);
    // cout << e << ": " << out << endl;
    // RLEDecoding(out, out2);
    // cout << out2 << endl;
    // out2 = "";
    // out = "";





    ifs.close();
    ofs.close();
    ofs2.close();

    return 0;
}
