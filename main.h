// Author: Patrik Segedy, xseged00, <xseged00@vutbr.cz>
// File: main.h
// Date: 3.5.2018
// Description: Burrows-Wheeler Transformation main header

#ifndef __MAIN_H_
#define __MAIN_H_

#include <string>
#include <unistd.h>
#include <iostream>

typedef struct params {
    std::string infile;
    std::string outfile;
    std::string logfile;
    bool compress;
    bool decompress;
} params;

// print help
void usage();
// parse program arguments
int get_args(int argc, char **argv, params *p);

#endif // __MAIN_H_
