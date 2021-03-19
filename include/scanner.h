#ifndef COMPILER_CONSTRUCTION_SCANNER_H
#define COMPILER_CONSTRUCTION_SCANNER_H

#include <stdio.h>

typedef struct Scanner{
    char* src;
    size_t src_size;
    char c;
    unsigned int i;
} Scanner;

Scanner* init_scanner(char* src); //initializes the scanner


#endif //COMPILER_CONSTRUCTION_SCANNER_H
