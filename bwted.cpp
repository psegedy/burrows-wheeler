// Author: Patrik Segedy, xseged00, <xseged00@vutbr.cz>
// File: bwted.cpp
// Date: 3.5.2018
// Description: Burrows-Wheeler Transformation library

#include "bwted.h"
#include "mtf.h"
#include "rle.h"

// traspose matrix
matrix_t transpose(matrix_t &vec) {
    matrix_t transposed(vec[0].size(), std::vector<char>());

    for (size_t i = 0; i < vec.size(); i++)
        for (size_t j = 0; j < vec[0].size(); j++)
            transposed[j].push_back(vec[i][j]);

    return transposed;
}

/* 
bwted – record of decompress
inputFile – input file (compressed)
outputFile – output file (uncompressed)
 */
int BWTDecoding(tBWTED *bwted, std::istream &inputFile, std::ostream &outputFile) {

    std::list<char> alphabet;
    // initialize alphabet
    for (int i = 0; i < 255; ++i)
        alphabet.push_front(char(i));

    // get filesize
    inputFile.seekg(0, inputFile.end);
    long filesize = inputFile.tellg();
    bwted->codedSize = filesize;
    inputFile.seekg(0, inputFile.beg);

    // read stream to string
    std::string str2((std::istreambuf_iterator<char>(inputFile)),
                     std::istreambuf_iterator<char>());

    std::string rle_dec = "";
    // RLE Decoding
    RLEDecoding(str2, rle_dec);

    str2 = "";
    // MTF Decoding
    MTFDecoding(rle_dec, str2, alphabet);

    size_t bufsize = CHUNK_SIZE + 2;
    // Decode BWT by chunks
    while(str2.size() > 0) {
        if (str2.size() < bufsize) {
            bufsize = str2.size();
        }

        std::string str = str2.substr(0, bufsize);
        str2.erase(0, bufsize);

        std::string out = "";
        
        std::vector<char> column(str.begin(), str.end());
        std::vector<char> column_sorted(str.begin(), str.end());
        std::stable_sort(column_sorted.begin(), column_sorted.end());

        // Init matrix for decoding
        matrix_t table;
        table.resize(str.size(), std::vector<char>(str.size()));

        // Decode, trasnpose matrix
        // add new column and sort
        int i = str.size() - 1;
        table[i] = column_sorted;
        table = transpose(table);
        std::stable_sort(table.begin(), table.end(), [i](const std::vector< char >& a, const std::vector< char >& b){ return a[i] < b[i]; } );

        // transpose, add new column and sort
        for (int i = str.size() - 2; i >= 0; i--) {
            table = transpose(table);
            table[i] = column;
            table = transpose(table);
            // https://stackoverflow.com/questions/14669533/sort-multidimensional-vector-of-ints
            std::stable_sort(table.begin(), table.end(), [i](const std::vector< char >& a, const std::vector< char >& b){ return a[i] < b[i]; } );
        }

        // find row with last character == ETX
        for(auto i : table) {
            if (i.back() == ETX) {
                out = std::string(i.begin(), i.end());
                break;
            }
        }
        // delete STX, ETX
        if (out.size() > 0) {
            out = out.substr(1, out.size() - 2);
        }

        // write to file
        outputFile << out;
    }

    
    return 0;
}

/* 
bwted – record of compress
inputFile – input file (uncompressed)
outputFile – output file (compressed)
 */
int BWTEncoding(tBWTED *bwted, std::istream &inputFile, std::ostream &outputFile) {
    std::list<char> alphabet;
    // initialize alphabet
    for (int i = 0; i < 255; ++i)
        alphabet.push_front(char(i));

    // vector for premutations of input
    std::vector<std::string> cyclic;

    // get filesize
    inputFile.seekg(0, inputFile.end);
    size_t filesize = inputFile.tellg();
    bwted->uncodedSize = filesize;
    inputFile.seekg(0, inputFile.beg);

    size_t bufsize = CHUNK_SIZE;
    // encode by chunks
    while(filesize > 0) {
        if (filesize < CHUNK_SIZE) {
            bufsize = filesize;
        }
        filesize -= bufsize;

        // read bufsize length from input file
        std::string str("", bufsize);
        inputFile.read(&str.front(), bufsize);
        
        // add start and end of transaction symbols to string
        str = STX + str + ETX;

        // create cyclic shifts - permutations of input
        std::string shifted;
        for (size_t i = 0; i < str.size(); i++) {
            shifted = str.substr(i, std::string::npos) + str.substr(0, i);
            cyclic.push_back(shifted);
        }
        // clear strings to save RAM
        shifted.clear();
        str.clear();

        // sort cyclic shifts lexicographicaly
        std::sort(cyclic.begin(), cyclic.end());

        // get last column
        std::string out = "";
        for(auto i : cyclic)
            out += i.back();

        // clear strings to save RAM
        cyclic.clear();


        // MTF Encoding
        std::string mtf_enc = "";
        MTFEncoding(out, mtf_enc, alphabet);

        // RLE Encoding
        out = "";
        RLEEncoding(mtf_enc, out);


        // write to output
        outputFile << out;

        out.clear();
    }

    return 0;
}
