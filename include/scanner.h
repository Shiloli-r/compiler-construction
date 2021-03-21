#ifndef COMPILER_CONSTRUCTION_SCANNER_H
#define COMPILER_CONSTRUCTION_SCANNER_H

#include <stdio.h>

typedef struct Scanner{
    char* src; //the source
    size_t src_size;  //size of the source
    char c; // current character
    unsigned int i;  //index
} Scanner;

Scanner* init_scanner(char* src); //initializes the scanner


#endif //COMPILER_CONSTRUCTION_SCANNER_H
