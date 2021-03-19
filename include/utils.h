#ifndef COMPILER_CONSTRUCTION_UTILS_H
#define COMPILER_CONSTRUCTION_UTILS_H

#ifdef _WIN32
size_t getline(char **lineptr, size_t *n, FILE* stream); //(for windows systems) reads line from file

#endif

char* read_source(const char* filename); // Reads the code from the a source file, returns it in char *buffer

#endif //COMPILER_CONSTRUCTION_UTILS_H
