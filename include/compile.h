#ifndef COMPILER_CONSTRUCTION_COMPILE_H
#define COMPILER_CONSTRUCTION_COMPILE_H

void compile(char* src, FILE* output); // prints tokens (types and values)

void compile_source(const char* filename, FILE* output); //only func called in main, reads source code & calls compile

#endif //COMPILER_CONSTRUCTION_COMPILE_H
