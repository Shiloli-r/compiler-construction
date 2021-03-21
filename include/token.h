#ifndef COMPILER_CONSTRUCTION_TOKEN_H
#define COMPILER_CONSTRUCTION_TOKEN_H

typedef struct Token{
    char* value;
    enum{
        TOKEN_ID,
        TOKEN_EQUALS,
        TOKEN_LPAREN,
        TOKEN_RPAREN,
        TOKEN_INT,
        TOKEN_FLOAT,
        TOKEN_STRING,
        TOKEN_KEYWORD,
        TOKEN_UNKNOWN,
        TOKEN_LBRACKET,
        TOKEN_RBRACKET,
        TOKEN_LT,
        TOKEN_LBRACE,
        TOKEN_RBRACE,
        TOKEN_COMMA,
        TOKEN_PLUS_EQUALS,
        TOKEN_FORWARD_SLASH,
        TOKEN_EOF
    } type;
} Token;

Token* init_token(char* value, int type); //initialize the token

#endif //COMPILER_CONSTRUCTION_TOKEN_H
