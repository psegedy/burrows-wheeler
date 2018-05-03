// Author: Patrik Segedy, xseged00, <xseged00@vutbr.cz>
// File: main.cpp
// Date: 29.4.2018
// Description: Burrows-Wheeler Transformation application
//              BWT -> MTF -> RLE-0 -> Entropy coder

#include "main.h"
#include "bwted.h"

using namespace std;

int main(int argc, char **argv) {

    params p;
    tBWTED bwted;

    int rc;
    // get program arguments
    if ((rc = get_args(argc, argv, &p)) != 2)
        return rc;

    // input output
    ifstream ifs(p.infile);
    ofstream ofs(p.outfile);
    // default to stdin, stdout
    istream fin(cin.rdbuf());
    ostream fout(cout.rdbuf());

    // use input file if -i argument exists
    // else use stdin
    if(ifs)
        fin.rdbuf(ifs.rdbuf());

    // use output file if -o argument exists
    // else use stdout
    if(ofs)
        fout.rdbuf(ofs.rdbuf());

    // compression
    if (p.compress) {
        BWTEncoding(&bwted, fin, fout);
        bwted.codedSize = ofs.tellp();
    }

    // decompression
    if (p.decompress) {
        BWTDecoding(&bwted, fin, fout);
        bwted.uncodedSize = ofs.tellp();
    }

    // log info
    if (p.logfile != "") {
        ofstream log(p.logfile);
        log << "login = xseged00" << endl;
        log << "uncodedSize = " << bwted.uncodedSize << endl;
        log << "codedSize = " << bwted.codedSize << endl;
        log.close();
    }

    ifs.close();
    ofs.close();

    return 0;
}

int get_args(int argc, char **argv, params *p) {
    int index;
    int c;

    p->infile = "";
    p->outfile = "";
    p->logfile = "";
    p->compress = false;
    p->decompress = false;

    while ((c = getopt (argc, argv, "i:o:l:cxh")) != -1)
        switch (c) {
            case 'i':
                p->infile = optarg;
                break;
            case 'o':
                p->outfile = optarg;
                break;
            case 'l':
                p->logfile = optarg;
                break;
            case 'c':
                p->compress = true;
                break;
            case 'x':
                p->decompress = true;
                break;
            case 'h':
                usage();
                return 0;
            case '?':
                cerr << "Bad program arguments" << endl;
                usage();
                return 1;
            default:
                abort();
        }

    for (index = optind; index < argc; index++) {
        cerr << "Non-option argument" << argv[index] << endl;
        usage();
        return 1;
    }

    return 2;
}

void usage() {
    cout << "Usage:" << endl
         << "./bwted -i infile -o outfile -l logfile -c" << endl << endl
         << "Parameters" << endl
         << "\t-i <infile>                  Input file - if empty read stdin" << endl
         << "\t-o <outfile>                 Output file - if empty print to stdout " << endl
         << "\t-l <logfile>                 Log file filename" << endl
         << "\t-c                           Compress" << endl
         << "\t-x                           Decompress" << endl
         << "\t-h                           Print this help" << endl;
}
