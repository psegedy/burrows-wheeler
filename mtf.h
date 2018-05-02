#ifndef __MTF_H_
#define __MTF_H_

#include <fstream>
#include <list>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

int MTFEncoding(std::string &str, std::string &mtf_enc, std::list<char> alphabet);
int MTFDecoding(std::string &mtf_enc, std::string &mtf_dec, std::list<char> alphabet);

#endif // __MTF_H_
