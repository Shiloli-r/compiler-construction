#ifndef COMPILER_CONSTRUCTION_SCANNER_H
#define COMPILER_CONSTRUCTION_SCANNER_H

#include <stdio.h>
#include "token.h"

typedef struct Scanner{
    char* src; //the source
    size_t src_size;  //size of the source
    char c; // current character
    unsigned int i;  //index
} Scanner;

Scanner* init_scanner(char* src); //initializes the scanner

void scanner_adv(Scanner* scanner);  //(advance) - moves the scanner to the next character (increments scanner pos by 1)

void scanner_ret(Scanner* scanner); //(retreat) - moves the scanner to the prev character (decrements scanner pos by 1)

Token* scanner_adv_curr(Scanner* scanner, int type);  //creates a token from the current character,then advances scanner

char scanner_check_next(Scanner* scanner, int offset);  // checks the next character that the scanner will move to

void skip_whitespace(Scanner* scanner); // skips any new line, carriage return, tab or whitespace

Token* scanner_parse_id(Scanner* scanner); //parses Identifiers

Token* scanner_parse_number(Scanner* scanner);  //parses Integers

Token* scanner_parse_string(Scanner* scanner); //parses Strings

Token* scanner_parse_unknown(Scanner* scanner); //parses unknown characters

Token* scanner_adv_with(Scanner* scanner, Token* token); //advances scanner while retaining current char

Token* scan_next_token(Scanner* scanner); // The real deal: converts entire program to tokens (i.e tokenizer)

static const char* token_type2str(int type);  //Converts the token type to string

char* token2str(Token* token);  //converts the token to string

#endif //COMPILER_CONSTRUCTION_SCANNER_H
