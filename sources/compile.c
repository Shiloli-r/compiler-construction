#include <stdlib.h>

#include "compile.h"
#include "scanner.h"
#include "utils.h"

void compile(char* src, FILE* output){
    Scanner* scanner = init_scanner(src);
    Token* token;

    while ((token = scan_next_token(scanner))->type != TOKEN_EOF){
        fprintf(output,"TOKEN {%s} {%d}\n", token->value, token->type);
//        fprintf(output, "%s", token2str(token));  TODO: Implement this
    }
}

void compile_source(const char* filename, FILE* output){
    char* src = read_source(filename);
    compile(src, output);
    free(src);
}
