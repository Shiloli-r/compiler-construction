#include <stdlib.h>
#include <string.h>
#include "scanner.h"

Scanner* init_scanner(char* src){
    Scanner* scanner = calloc(1, sizeof(Scanner));

    scanner->src = src;
    scanner->src_size = strlen(src);
    scanner->i = 0;
    scanner->c = src[scanner->i];

    return scanner;
}
