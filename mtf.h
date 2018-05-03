// Author: Patrik Segedy, xseged00, <xseged00@vutbr.cz>
// File: mtf.h
// Date: 1.5.2018
// Description: Move to front transform header file

#ifndef __MTF_H_
#define __MTF_H_

#include <list>
#include <algorithm>
#include <string>

// MTF encode
int MTFEncoding(std::string &str, std::string &mtf_enc, std::list<char> alphabet);
// MTF decode
int MTFDecoding(std::string &mtf_enc, std::string &mtf_dec, std::list<char> alphabet);

#endif // __MTF_H_
