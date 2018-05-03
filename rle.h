// Author: Patrik Segedy, xseged00, <xseged00@vutbr.cz>
// File: rle.h
// Date: 2.5.2018
// Description: Run length encoding header file

#ifndef __RLE_H_
#define __RLE_H_

#include <string>

// RLE delimiter
#define DELIM '\x04'

// RLE encode
int RLEEncoding(std::string &str_in, std::string &str_out);
// RLE decode
int RLEDecoding(std::string &str_in, std::string &str_out);

#endif // __RLE_H_
