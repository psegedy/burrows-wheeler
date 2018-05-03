#ifndef __RLE_H_
#define __RLE_H_

#include <string>
#include <iostream>


#define DELIM '\x04'
// #define DELIM '@'

int RLEEncoding(std::string &str_in, std::string &str_out);

int RLEDecoding(std::string &str_in, std::string &str_out);

#endif // __RLE_H_
