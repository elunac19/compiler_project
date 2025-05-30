#ifndef COMPILER_H
#define COMPILER_H

#include <stddef.h>

// TokenType enum
typedef enum {
    TKN_CHAR, TKN_INT, TKN_LONG, TKN_FLOAT, TKN_DOUBLE, TKN_STRING, TKN_VOID,
    TKN_CLASS, TKN_PUBLIC, TKN_PRIVATE, TKN_PROTECTED,
    TKN_COLON, TKN_AMPERSAND, TKN_STAR,
    TKN_HASH,
    TKN_ID, TKN_CHAR_LIT, TKN_STRING_LIT,
    TKN_LPAREN, TKN_RPAREN, TKN_LBRACE, TKN_RBRACE, TKN_LBRACKET, TKN_RBRACKET, TKN_SEMICOLON, TKN_COMMA,
    TKN_ERROR, TKN_EOF
} TokenType;

typedef struct {
    TokenType type;
    char* lexeme;
    int line;
    union {
        char char_value;
        int int_value;
        long long_value;
        float float_value;
        double double_value;
        char *string_value;
    } value;
} Token;

typedef struct {
    char* buffer;
    size_t buffer_len;
    size_t position;
    size_t line;
    size_t column;
    char current_char;
} Lexer;

Lexer* init_lexer(char* buffer);
Token* create_token(TokenType type, char* lexeme, int line);
void lexer_advance(Lexer* lexer);
void lexer_skip_whitespace(Lexer* lexer);
char lexer_peek(Lexer* lexer);
void lexer_skip_equal_decl(Lexer* lexer);
void lexer_skip_comments(Lexer* lexer);

#endif // COMPILER_H 