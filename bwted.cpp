// Author: Patrik Segedy, xseged00, <xseged00@vutbr.cz>
// File: bwted.cpp
// Date: 29.4.2018
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
bwted – záznam o dekódování
inputFile – vstupní soubor (kódovaný)
outputFile – výstupní soubor (dekódovaný)
návratová hodnota – 0 dekódování proběhlo v pořádku,-1 při dekódování
nastala chyba */
int BWTDecoding(tBWTED *ahed, std::fstream &inputFile, std::fstream &outputFile) {

    std::list<char> alphabet;
    // initialize alphabet
    for (int i = 0; i < 255; ++i)
        alphabet.push_front(char(i));

    // read stream to string
    std::string str((std::istreambuf_iterator<char>(inputFile)),
                     std::istreambuf_iterator<char>());

    std::cout << "infile: " << str << std::endl;
    std::string out = "";


    std::string rle_dec = "";
    RLEDecoding(str, rle_dec);
    std::cout << "rle dec: " << rle_dec << std::endl;
    std::cout << "rle dec size: " << rle_dec.size() << std::endl;
    str = "";
    MTFDecoding(rle_dec, str, alphabet);
    std::cout << "mtf dec: " << str << std::endl;
    std::cout << "mtf dec size: " << str.size() << std::endl;
    
    std::vector<char> column(str.begin(), str.end());
    std::vector<char> column_sorted(str.begin(), str.end());
    std::stable_sort(column_sorted.begin(), column_sorted.end());

    matrix_t table;
    table.resize(str.size(), std::vector<char>(str.size()));

    int i = str.size() - 1;
    table[i] = column_sorted;
    table = transpose(table);
    std::stable_sort(table.begin(), table.end(), [i](const std::vector< char >& a, const std::vector< char >& b){ return a[i] < b[i]; } );

    for (int i = str.size() - 2; i >= 0; i--) {
        table = transpose(table);
        table[i] = column;
        table = transpose(table);
        // https://stackoverflow.com/questions/14669533/sort-multidimensional-vector-of-ints
        std::stable_sort(table.begin(), table.end(), [i](const std::vector< char >& a, const std::vector< char >& b){ return a[i] < b[i]; } );
    }

    std::cout << "print table" << std::endl;
    for(auto i : table) {
        for(auto j : i) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // find row with last character == ETX
    for(auto i : table) {
        if (i.back() == ETX) {
            out = std::string(i.begin(), i.end());
            break;
        }
    }
    // delete STX, ETX
    out = out.substr(1, out.size() - 2);

    std::cout << "Decoded" << std::endl;
    std::cout << out << std::endl;
    for (auto i : out) {
        std::cout << std::hex << int(i) << " ";
    }
    std::cout << std::dec << std::endl;
    

    outputFile << out;

    return 0;
}

/* 
bwted – záznam o kódování
inputFile – vstupní soubor (nekódovaný)
outputFile – výstupní soubor (kódovaný)
návratová hodnota – 0 kódování proběhlo v pořádku,-1 při kódování
nastala chyba */
int BWTEncoding(tBWTED *bwted, std::fstream &inputFile, std::fstream &outputFile) {
    std::list<char> alphabet;
    // initialize alphabet
    for (int i = 0; i < 255; ++i)
        alphabet.push_front(char(i));

    std::vector<std::string> cyclic;
    // read stream to string
    std::string str((std::istreambuf_iterator<char>(inputFile)),
                     std::istreambuf_iterator<char>());
    
    // add start and end of transaction symbols to string
    str = STX + str + ETX;
    // std::cout << "String w/ STX, ETX: " << str << std::endl;


    std::cout << "Cyclic shifts" << std::endl;
    // create cyclic shifts
    std::string shifted;
    for (size_t i = 0; i < str.size(); i++) {
        shifted = str.substr(i, std::string::npos) + str.substr(0, i);
        cyclic.push_back(shifted);
    }

    std::cout << "Unsorted" << std::endl;
    // for(auto i : cyclic) {
    //     std::cout << i << std::endl;
    // }
    // std::cout << std::endl;


    // sort cyclic shifts lexicographicaly
    std::sort(cyclic.begin(), cyclic.end());

    std::cout << "Sorted" << std::endl;
    // for(auto i : cyclic) {
    //     std::cout << i << std::endl;
    // }
    // std::cout << std::endl;

    // get last column
    std::string out = "";
    for(auto i : cyclic) {
        // outputFile << i.back();
        out += i.back();
    }
    bwted->codedSize = out.size();

    std::cout << "Encoded" << std::endl;
    // std::cout << out << std::endl;
    // for (auto i : out) {
    //     std::cout << std::hex << int(i) << " ";
    // }
    // std::cout << std::dec << std::endl;
    std::cout << out << std::endl;

    std::string mtf_enc = "";

    MTFEncoding(out, mtf_enc, alphabet);
    std::cout << "mtf enc: " << mtf_enc << std::endl;
    std::cout << "mtf enc size: " << mtf_enc.size() << std::endl;
    out = "";
    RLEEncoding(mtf_enc, out);
    std::cout << "rle enc: " << out << std::endl;
    std::cout << "rle enc size: " << out.size() << std::endl;


    outputFile << out;

    return 0;
}
