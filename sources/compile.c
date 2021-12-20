#include <stdlib.h>

#include "compile.h"
#include "scanner.h"
#include "utils.h"

void compile(char* src, FILE* output){
    Scanner* scanner = init_scanner(src);
    Token* token;

    while ((token = scan_next_token(scanner))->type != TOKEN_EOF){
       // fprintf(output,"TOKEN {%s} {%d}\n", token->value, token->type);
        char* t2s = token2str(token);
        fprintf(output, "%s", t2s);
        free(t2s);
        free(token->value);
        free(token);
    }
    // free end of file token
    free(token);
    free(scanner);
}

void compile_source(const char* filename, FILE* output){
    char* src = read_source(filename);
    compile(src, output);
    free(src);
}
