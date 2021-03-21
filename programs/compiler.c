#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mini_compiler.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Please provide an input file (containing source code)");
        exit(1);
    }

    FILE* input = fopen(argv[1], "rb");
    if(!input)
        error("Input file not found");

    if (argc == 2)
        compile_source(argv[1], stdout);
    else if (strcmp(argv[2], "-o") == 0)
    {
        if (argc == 3)
            error("Please Provide an Output File");

        FILE *output = fopen(argv[3], "w");
        if (!output)
            error("Output File Not Found");
        compile_source(argv[1], output);
        fclose(output);
    }
    else
        error("Unknown command line argument(s)");

    fclose(input);
    return 0;
}
