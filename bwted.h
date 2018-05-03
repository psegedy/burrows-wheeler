// Author: Patrik Segedy, xseged00, <xseged00@vutbr.cz>
// File: bwted.h
// Date: 3.5.2018
// Description: Burrows-Wheeler Transformation library header file

#ifndef __BWTED_H_
#define __BWTED_H_

#include <sys/types.h>
#include <fstream>
#include <streambuf>
#include <string>
#include <vector>
#include <algorithm>


#define STX '\x02'  // start of text
#define ETX '\x03'  // end of text
#define CHUNK_SIZE 2048

// matrix data type
using matrix_t = std::vector< std::vector<char> >;


typedef struct {
    int64_t uncodedSize;
    int64_t codedSize;
} tBWTED;

/* 
bwted – record of decompress
inputFile – input file (compressed)
outputFile – output file (uncompressed)
 */
int BWTDecoding(tBWTED *bwted, std::istream &inputFile, std::ostream &outputFile);

/* 
bwted – record of compress
inputFile – input file (uncompressed)
outputFile – output file (compressed)
 */
int BWTEncoding(tBWTED *bwted, std::istream &inputFile, std::ostream &outputFile);

#endif // __BWTED_H_
