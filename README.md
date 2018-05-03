# Burrows-Wheeler transform
Text file compression using Burrows-Wheeler transform.

BWT -> MTF -> RLE -> Entropy coding

First BWT is applied. Next is Move-To-Front transform, Run-length-encoding and Entropy coding.
Entropy coding is not implemented, it should use e.g. Arithmetic coding, Huffman coding or Adaptive Huffman coding. 


**Usage**
```
./bwted -i infile -o outfile -l logfile -c

Parameters
-i <infile>                  Input file - if empty read stdin
-o <outfile>                 Output file - if empty print to stdout 
-l <logfile>                 Log file filename
-c                           Compress
-x                           Decompress
-h                           Print this help
```

Created as project for KKO class @[FIT VUT](http://www.fit.vutbr.cz)
