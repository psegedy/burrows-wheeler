// Author: Patrik Segedy, xseged00, <xseged00@vutbr.cz>
// File: bwted.h
// Date: 29.4.2018
// Description: Burrows-Wheeler Transformation library header file

#ifndef __BWTED_H_
#define __BWTED_H_

#include <sys/types.h>
#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>
#include <vector>
#include <algorithm>


#define STX '\x02'  // start of transaction
#define ETX '\x03'  // end of transaction
// #define STX '^'  // start of transaction
// #define ETX '|'  // end of transaction

typedef struct {
    int64_t uncodedSize;
    int64_t codedSize;
} tBWTED;
/* 
bwted – záznam o dekódování
inputFile – vstupní soubor (kódovaný)
outputFile – výstupní soubor (dekódovaný)
návratová hodnota – 0 dekódování proběhlo v pořádku,-1 při dekódování
nastala chyba */
int BWTDecoding(tBWTED *ahed, std::fstream &inputFile, std::fstream &outputFile);

/* 
bwted – záznam o kódování
inputFile – vstupní soubor (nekódovaný)
outputFile – výstupní soubor (kódovaný)
návratová hodnota – 0 kódování proběhlo v pořádku,-1 při kódování
nastala chyba */
int BWTEncoding(tBWTED *bwted, std::fstream &inputFile, std::fstream &outputFile);

#endif // __BWTED_H_
