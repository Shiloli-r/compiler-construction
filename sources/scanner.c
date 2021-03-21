#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "scanner.h"
#include "macros.h"
#include "token.h"
#include "keywords.h"

Scanner *init_scanner(char *src)
{
    Scanner *scanner = calloc(1, sizeof(Scanner));
    scanner->src = src;
    scanner->src_size = strlen(src);
    scanner->i = 0;
    scanner->c = src[scanner->i];

    return scanner;
}

void scanner_adv(Scanner *scanner)
{
    if (scanner->i < scanner->src_size && scanner->c != '\0')
    {                                          //index < size of src and current != Null char
        scanner->i += 1;                       //increment index
        scanner->c = scanner->src[scanner->i]; //move to next character in the src
    }
}

void scanner_ret(Scanner* scanner){
    scanner->i -=1;
    scanner->c = scanner->src[scanner->i];
}

void skip_whitespace(Scanner* scanner){
    // 13 (carriage return),  10 (new line), \t (tab)
    while (scanner->c == 13 || scanner->c == 10 || scanner->c == ' ' || scanner->c == '\t')
    {
        scanner_adv(scanner); //keep moving the scanner forward
    }
}

Token* scanner_parse_id(Scanner* scanner){
    char* value  = calloc(1, sizeof(char));
    while(isalnum(scanner->c) || scanner->c == 95){
        value = realloc(value, strlen(value)+2 * sizeof(char));  //increase memory size of value
        strcat(value, (char[]){scanner->c, 0}); //concatenate the character into value
        scanner_adv(scanner); // advance the scanner
    }
    scanner_ret(scanner);

    // Get the keywords
    int keywordsCount = sizeof keywords / sizeof *keywords;
    for(int i=0; i<keywordsCount; i++){
        if(strcmp(value, keywords[i]) == 0){
            return init_token(value, TOKEN_KEYWORD);
        }
    }
    return init_token(value, TOKEN_ID); //initialize a token and return it
}

Token* scanner_parse_number(Scanner* scanner){
    bool float_ = false;
    char* value  = calloc(1, sizeof(char));
    while(isdigit(scanner->c)){  // while the character is a number
        value = realloc(value, strlen(value)+2 * sizeof(char));  //increase memory size of value
        strcat(value, (char[]){scanner->c, 0}); //concatenate the character into value

        //check for floats
        if(scanner_check_next(scanner, 1) == '.' && !float_){
            scanner_adv(scanner);
            if(!isdigit(scanner_check_next(scanner, 1))){
                scanner_ret(scanner);
                break;
            }
            strcat(value, (char[]){scanner->c, 0}); //concatenate the character into value
            float_ = true;
        }
        //A second decimal point (unexpected character)
        if(scanner_check_next(scanner, 1) == '.' && float_){
            break;
        }
        //if the next char is neither a digit nor a decimal point (break)
        if(!isdigit(scanner_check_next(scanner, 1)) && scanner_check_next(scanner, 1) != '.'){
            break;
        }

        scanner_adv(scanner); // advance the scanner
    }
    if(float_)
        return init_token(value, TOKEN_FLOAT);  //initialize a token and return it
    return init_token(value, TOKEN_INT);  //initialize a token and return it
}

Token *scanner_parse_string(Scanner *scanner)
{
    char *value = calloc(1, sizeof(char));
    scanner_adv(scanner);
    while (scanner->c != '"')
    {
        value = realloc(value, strlen(value) + 2 * sizeof(char));
        strcat(value, (char[]){scanner->c, 0}); //concatenate the character into value
        scanner_adv(scanner);
    }
    return init_token(value, TOKEN_STRING); //initialize a token and return it
}

Token* scanner_parse_unknown(Scanner* scanner){
    char* value  = calloc(1, sizeof(char));
    strcat(value, (char[]){scanner->c, 0}); //concatenate the character into value

    // fprintf(stderr,"[scanner error]: Unexpected character `%c` \n", scanner->c);
    printf("[scanner error]: Unexpected character `%c` ", scanner->c); //prints the unexpected char "Error"

    return init_token(value, TOKEN_UNKNOWN);
}

Token* scanner_adv_with(Scanner* scanner, Token* token){
    scanner_adv(scanner);
    return token;
}

Token *scanner_adv_curr(Scanner *scanner, int type)
{
    char *value = calloc(2, sizeof(char));
    value[0] = scanner->c;
    value[1] = '\0';

    Token *token = init_token(value, type);
    scanner_adv(scanner);

    return token;
}
char scanner_check_next(Scanner *scanner, int offset)
{
    // check next characters with an offset
    return scanner->src[MIN(scanner->i + offset, scanner->src_size)];
}

Token *scan_next_token(Scanner *scanner)
{
    while (scanner->c != '\0')
    {
        skip_whitespace(scanner);
        if (isalpha(scanner->c))
            return scanner_adv_with(scanner, scanner_parse_id(scanner));
        if (isdigit(scanner->c))
            return scanner_adv_with(scanner, scanner_parse_number(scanner));
        switch(scanner->c){
            case '=': return scanner_adv_curr(scanner, TOKEN_EQUALS);
            case '(': return scanner_adv_curr(scanner, TOKEN_LPAREN);
            case ')': return scanner_adv_curr(scanner, TOKEN_RPAREN);
            case '[': return scanner_adv_curr(scanner, TOKEN_LBRACKET);
            case ']': return scanner_adv_curr(scanner, TOKEN_RBRACKET);
            case '{': return scanner_adv_curr(scanner, TOKEN_LBRACE);
            case '}': return scanner_adv_curr(scanner, TOKEN_RBRACE);
            case '<': return scanner_adv_curr(scanner, TOKEN_LT);
            case ',': return scanner_adv_curr(scanner, TOKEN_COMMA);
            case '+': {
                if (scanner_check_next(scanner, 1) == '='){
                    scanner_adv(scanner);
                    return scanner_adv_with(scanner, init_token("+=", TOKEN_PLUS_EQUALS));
                }else{
                    return scanner_adv_with(scanner, scanner_parse_unknown(scanner));
                }
            }
            case '"': return scanner_adv_with(scanner, scanner_parse_string(scanner));
            case '/': return scanner_adv_curr(scanner, TOKEN_FORWARD_SLASH);
            case '\0': break;
            default: return scanner_adv_with(scanner, scanner_parse_unknown(scanner));
        }
    }

    //At the end of the file now
    return init_token(0, TOKEN_EOF);
}

static const char* token_type2str(int type){
    switch (type) {
        case TOKEN_ID: return "IDENTIFIER (TOKEN_ID)";
        case TOKEN_EQUALS: return " OPERATOR (TOKEN_EQUALS)";
        case TOKEN_LPAREN: return "OPERATOR (TOKEN_LPAREN)";
        case TOKEN_RPAREN: return "OPERATOR (TOKEN_RPAREN)";
        case TOKEN_INT: return "INT (TOKEN_INT)";
        case TOKEN_FLOAT: return "FLOAT (TOKEN_FLOAT)";
        case TOKEN_UNKNOWN: return "UNEXPECTED CHARACTER)";
        case TOKEN_STRING: return "STRING (TOKEN_STRING)";
        case TOKEN_KEYWORD: return "KEYWORD (TOKEN_KEYWORD)";
        case TOKEN_LBRACKET: return "OPERATOR (TOKEN_LBRACKET)";
        case TOKEN_RBRACKET: return "OPERATOR (TOKEN_RBRACKET)";
        case TOKEN_LBRACE: return "OPERATOR (TOKEN_LBRACE)";
        case TOKEN_RBRACE: return "OPERATOR (TOKEN_RBRACE)";
        case TOKEN_LT: return "OPERATOR (TOKEN_LT)";
        case TOKEN_COMMA: return "OPERATOR (TOKEN_COMMA)";
        case TOKEN_PLUS_EQUALS: return "OPERATOR (TOKEN_PLUS_EQUALS)";
        case TOKEN_FORWARD_SLASH: return "OPERATOR (TOKEN_FORWARD_SLASH)";
        case TOKEN_EOF: return " TOKEN_EOF";
    }
    return "Token type could not be converted to string";
}

char *token2str(Token *token)
{
    const char *type_str = token_type2str(token->type);
    const char *format = "<type=%s, token_type_id=%d, value= %s >\n";

    char *str = calloc(strlen(type_str) + strlen(format) + 12, sizeof(char));
    sprintf(str, format, type_str, token->type, token->value);
    return str;
}
