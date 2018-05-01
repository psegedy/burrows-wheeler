#ifndef __MTF_H_
#define __MTF_H_

#include <fstream>
#include <list>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>




int MTFEncoding(std::fstream &input, std::vector<size_t> &mtf_enc);

int MTFDecoding(std::vector<size_t> &mtf_enc, std::string &mtf_dec);

#endif // __MTF_H_
