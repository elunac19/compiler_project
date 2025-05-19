#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>

typedef enum {
    //DataType Keywords
    TKN_CHAR,       
    TKN_INT,      
    TKN_LONG,       
    TKN_FLOAT,
    TKN_DOUBLE,
    TKN_STRING,

    //Flow Statement Keywords
    TKN_IF,
    TKN_ELSE,
    TKN_FOR,
    TKN_WHILE,

    //Exit Statement Keyword
    TKN_RETURN,

    //Identifiers and literals
    TKN_ID,
    TKN_CHAR_LIT,
    TKN_NUMBER_LIT,
    TKN_DECIMAL_LIT,
    TKN_STRING_LIT,

    //Arithmetic Operators
    TKN_PLUS,
    TKN_MINUS,
    TKN_MULTIPLY,
    TKN_DIVIDE,
    TKN_MODULO,
    TKN_ASSIGN,
    TKN_EQ,
    TKN_NEQ,
    TKN_LT,
    TKN_GT,
    TKN_LTE,
    TKN_GTE,

    //Logical Operators
    TKN_AND,
    TKN_OR,
    TKN_NOT,

    //Punctuation
    TKN_LPAREN,
    TKN_RPAREN,
    TKN_LBRACE,
    TKN_RBRACKET,
    TKN_LBRACKET,
    TKN_RBRACE,
    TKN_SEMICOLON,
    TKN_COMMA,

    //Other
    TKN_ERROR,
    TKN_EOF

} TokenType;

/*[NICE TO HAVE]
    ValueType 
*/
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
    // Source code (str) 
    char* buffer;
    // Length of source code   
    size_t buffer_len;
    // Current position
    size_t position;
    // Current line
    size_t line;
    // Current column
    size_t column;
    // Current character being processed
    char current_char;
} Lexer;

const char* token_type_to_string(TokenType type) {
    switch (type) {
        // DataType Keywords
        case TKN_CHAR: return "TKN_CHAR";
        case TKN_INT: return "TKN_INT";
        case TKN_LONG: return "TKN_LONG";
        case TKN_FLOAT: return "TKN_FLOAT";
        case TKN_DOUBLE: return "TKN_DOUBLE";
        case TKN_STRING: return "TKN_STRING";

        // Flow Statement Keywords
        case TKN_IF: return "TKN_IF";
        case TKN_ELSE: return "TKN_ELSE";
        case TKN_FOR: return "TKN_FOR";
        case TKN_WHILE: return "TKN_WHILE";

        // Exit Statement Keyword
        case TKN_RETURN: return "TKN_RETURN";

        // Identifiers and literals
        case TKN_ID: return "TKN_ID";
        case TKN_CHAR_LIT: return "TKN_CHAR_LIT";
        case TKN_NUMBER_LIT: return "TKN_NUMBER_LIT";
        case TKN_DECIMAL_LIT: return "TKN_DECIMAL_LIT";
        case TKN_STRING_LIT: return "TKN_STRING_LIT";

        // Arithmetic Operators
        case TKN_PLUS: return "TKN_PLUS";
        case TKN_MINUS: return "TKN_MINUS";
        case TKN_MULTIPLY: return "TKN_MULTIPLY";
        case TKN_DIVIDE: return "TKN_DIVIDE";
        case TKN_MODULO: return "TKN_MODULO";
        case TKN_ASSIGN: return "TKN_ASSIGN";
        case TKN_EQ: return "TKN_EQ";
        case TKN_NEQ: return "TKN_NEQ";
        case TKN_LT: return "TKN_LT";
        case TKN_GT: return "TKN_GT";
        case TKN_LTE: return "TKN_LTE";
        case TKN_GTE: return "TKN_GTE";

        // Logical Operators
        case TKN_AND: return "TKN_AND";
        case TKN_OR: return "TKN_OR";
        case TKN_NOT: return "TKN_NOT";

        // Punctuation
        case TKN_LPAREN: return "TKN_LPAREN";
        case TKN_RPAREN: return "TKN_RPAREN";
        case TKN_LBRACE: return "TKN_LBRACE";
        case TKN_RBRACKET: return "TKN_RBRACKET";
        case TKN_LBRACKET: return "TKN_LBRACKET";
        case TKN_RBRACE: return "TKN_RBRACE";
        case TKN_SEMICOLON: return "TKN_SEMICOLON";
        case TKN_COMMA: return "TKN_COMMA";

        // Other
        case TKN_ERROR: return "TKN_ERROR";
        case TKN_EOF: return "TKN_EOF";

        default: return "UNKNOWN";
    }
}

Lexer* init_lexer(char* buffer) {
    Lexer* lexer = malloc(sizeof(Lexer));
    lexer->buffer = buffer;
    lexer->buffer_len = strlen(buffer);
    lexer->position = 0;
    lexer->line = 1;
    lexer->column = 1;
    lexer->current_char = (lexer->buffer_len > 0) ? lexer->buffer[lexer->position] : '\0' ;
    return lexer;
}

Token* create_token(TokenType type, char* lexeme, int line) {
    Token* token = malloc(sizeof(Token));
    token->type = type;
    token->lexeme = strdup(lexeme);
    token->line = line;
    return token;
}

int issybol(char c) {
    switch (c) {
        case '+': case '-': case '*': case '/': case '%':
        case '=': case '<': case '>': case '!':
        case '(': case ')': case '{': case '}': case ';': case ',': case '[': case ']':
        case '&': case '|':
            return 1;
        default:
            return 0;
    }
}

void lexer_advance(Lexer* lexer) {
    if(lexer->position < lexer->buffer_len){
        lexer->position++;
        lexer->current_char = lexer->buffer[lexer->position];
        lexer->column++;
    } else {
        lexer->current_char = '\0';
    }
}

void lexer_skip_whitespace(Lexer* lexer) {
    while(lexer->current_char == ' ' || lexer->current_char == '\n'){
        if(lexer->current_char == '\n'){
            lexer->line++;
            lexer->column=0;
        }
        lexer_advance(lexer);
    }
}

char lexer_peek(Lexer* lexer) {
    if(lexer->position + 1 >= lexer->buffer_len){
        return '\0';
    }
    return lexer->buffer[lexer->position + 1];
}

void lexer_skip_comments(Lexer* lexer) {
    if(lexer->current_char == '/' && lexer_peek(lexer) == '/'){
        while(lexer->current_char != '\n' && lexer->current_char != '\0'){
            lexer_advance(lexer);
        }
    }

    if(lexer->current_char == '/' && lexer_peek(lexer) == '*'){
        lexer_advance(lexer);
        lexer_advance(lexer);

        while(lexer->current_char != '*' && lexer_peek(lexer) != '/' && lexer->current_char != '\0'){
            if(lexer->current_char == '\n'){
                lexer->line++;
                lexer->column=0;
            } 
            lexer_advance(lexer);
        }
        lexer_advance(lexer);
        lexer_advance(lexer);
    }
}

/*[NICE TO HAVE]
    Escape sequences '\n', '\t'
    Unclosed string or char
    Error handling
*/
Token* lexer_char_or_string(Lexer* lexer, int line) {
    if(lexer->current_char == '\''){
        lexer_advance(lexer);
        char token_buffer[] = {lexer->current_char, '\0'};
        lexer_advance(lexer);
        lexer_advance(lexer);

        Token* token = create_token(TKN_CHAR_LIT, token_buffer, line);
        token->value.char_value = token_buffer[0];
        return token;
    }

    if(lexer->current_char == '"'){
        char token_buffer[256]; 
        int token_position = 0;
        lexer_advance(lexer);

        while(lexer->current_char != '"' && lexer->current_char != '\0' && token_position < 255){
            token_buffer[token_position++] = lexer->current_char;
            lexer_advance(lexer);
        }

        lexer_advance(lexer);
        token_buffer[token_position] = '\0';

        Token* token = create_token(TKN_STRING_LIT, token_buffer, line);
        token->value.string_value = token->lexeme;
        return token;
    }
    return create_token(TKN_ERROR, "Error", line);
}

/*[NICE TO HAVE]
    Unary operators: Recognize ++ and -- as separate tokens.
    Compound operators: Support for +=, -=, *=, /=, %=, &=, |=, etc.
    Better error reporting: Show clear messages like Unexpected symbol '#' at line 3.
    Better handling for symbols that have a bitwise operator
    Dot and arrow operators: Tokenize . and -> for future struct/member access support.
    * (pointers)
    & (pointers)
    PERCHANCE, MAYHAPSS -> refactor repeated code
*/
Token* lexer_symbol(Lexer* lexer, int line) {
    switch (lexer->current_char) {
        case '+': {
            char token_buffer[] = {lexer->current_char, '\0'};
            lexer_advance(lexer);
            return create_token(TKN_PLUS, token_buffer, line);
        }
        case '-': {
            char token_buffer[] = {lexer->current_char, '\0'};
            lexer_advance(lexer);
            return create_token(TKN_MINUS, token_buffer, line);
        }
        case '*': {
            char token_buffer[] = {lexer->current_char, '\0'};
            lexer_advance(lexer);
            return create_token(TKN_MULTIPLY, token_buffer, line);
        }
        case '/': {
            char token_buffer[] = {lexer->current_char, '\0'};
            lexer_advance(lexer);
            return create_token(TKN_DIVIDE, token_buffer, line);
        }
        case '%': {
            char token_buffer[] = {lexer->current_char, '\0'};
            lexer_advance(lexer);
            return create_token(TKN_MODULO, token_buffer, line);
        }
        case '=': {
            if(lexer_peek(lexer) == '='){
                char token_buffer[] = {lexer->current_char, lexer_peek(lexer), '\0'};
                lexer_advance(lexer);
                lexer_advance(lexer);
                return create_token(TKN_EQ, token_buffer, line);
            }
            char token_buffer[] = {lexer->current_char, '\0'};
            lexer_advance(lexer);
            return create_token(TKN_ASSIGN, token_buffer, line);
        }
        case '!': {
            if(lexer_peek(lexer) == '='){
                char token_buffer[] = {lexer->current_char, lexer_peek(lexer), '\0'};
                lexer_advance(lexer);
                lexer_advance(lexer);
                return create_token(TKN_NEQ, token_buffer, line); 
            }
            char token_buffer[] = {lexer->current_char, '\0'};
            lexer_advance(lexer);
            return create_token(TKN_NOT, token_buffer, line);
        }
        case '<': {
            if(lexer_peek(lexer) == '='){
                char token_buffer[] = {lexer->current_char, lexer_peek(lexer), '\0'};
                lexer_advance(lexer);
                lexer_advance(lexer);
                return create_token(TKN_LTE, token_buffer, line); 
            }
            char token_buffer[] = {lexer->current_char, '\0'};
            lexer_advance(lexer);
            return create_token(TKN_LT, token_buffer, line);
        }
        case '>': {
            if(lexer_peek(lexer) == '='){
                char token_buffer[] = {lexer->current_char, lexer_peek(lexer), '\0'};
                lexer_advance(lexer);
                lexer_advance(lexer);
                return create_token(TKN_GTE, token_buffer, line); 
            }
            char token_buffer[] = {lexer->current_char, '\0'};
            lexer_advance(lexer);
            return create_token(TKN_GT, token_buffer, line);
        }
        case '&': {
            if(lexer_peek(lexer) == '&'){
                char token_buffer[] = {lexer->current_char, lexer_peek(lexer), '\0'};
                lexer_advance(lexer);
                lexer_advance(lexer);
                return create_token(TKN_AND, token_buffer, line); 
            }
            lexer_advance(lexer);
            return create_token(TKN_ERROR, (char[]){"Error symbol"}, line);
        }
        case '|': {
            if(lexer_peek(lexer) == '|'){
                char token_buffer[] = {lexer->current_char, lexer_peek(lexer), '\0'};
                lexer_advance(lexer);
                lexer_advance(lexer);
                return create_token(TKN_OR, token_buffer, line); 
            }
            lexer_advance(lexer);
            return create_token(TKN_ERROR, (char[]){"Error symbol"}, line);
        }
        case '(': {
            char token_buffer[] = {lexer->current_char, '\0'};
            lexer_advance(lexer);
            return create_token(TKN_LPAREN, token_buffer, line);
        }
        case ')': {
            char token_buffer[] = {lexer->current_char, '\0'};
            lexer_advance(lexer);
            return create_token(TKN_RPAREN, token_buffer, line);
        }
        case '{': {
            char token_buffer[] = {lexer->current_char, '\0'};
            lexer_advance(lexer);
            return create_token(TKN_LBRACE, token_buffer, line);
        }
        case '}': {
            char token_buffer[] = {lexer->current_char, '\0'};
            lexer_advance(lexer);
            return create_token(TKN_RBRACE, token_buffer, line);
        }
        case '[': {
            char token_buffer[] = {lexer->current_char, '\0'};
            lexer_advance(lexer);
            return create_token(TKN_LBRACKET, token_buffer, line);
        }
        case ']': {
            char token_buffer[] = {lexer->current_char, '\0'};
            lexer_advance(lexer);
            return create_token(TKN_RBRACKET, token_buffer, line);
        }
        case ';': {
            char token_buffer[] = {lexer->current_char, '\0'};
            lexer_advance(lexer);
            return create_token(TKN_SEMICOLON, token_buffer, line);
        }
        case ',': {
            char token_buffer[] = {lexer->current_char, '\0'};
            lexer_advance(lexer);
            return create_token(TKN_COMMA, token_buffer, line);
        }
        default: {
            lexer_advance(lexer);
            return create_token(TKN_ERROR, (char[]){"Error symbol"}, line);
        }
    }
}

/*[NICE TO HAVE]
   Better handling for longs and float: 456L, 0xF, 2.7f
   Better error handling and reporting: 3. invalid
*/
Token* lexer_number(Lexer* lexer, int line) {
    char token_buffer[256];
    int token_position = 0;
    int is_float = 0;

    while (isdigit(lexer->current_char) && token_position < 255) {
        token_buffer[token_position++] = lexer->current_char;
        lexer_advance(lexer);
    }

    if(lexer->current_char == '.' && isdigit(lexer_peek(lexer))) {
        is_float = 1;
        token_buffer[token_position++] = lexer->current_char;
        lexer_advance(lexer);

        while (isdigit(lexer->current_char) && token_position < 255) {
            token_buffer[token_position++] = lexer->current_char;
            lexer_advance(lexer);
        }
    }

    token_buffer[token_position++] = '\0';
    Token* token;
    if(is_float){
        token = create_token(TKN_DECIMAL_LIT, token_buffer, line);
        token->value.float_value = (atof(token_buffer));
    } else {
        token = create_token(TKN_NUMBER_LIT, token_buffer, line);
        token->value.int_value = (atoi(token_buffer));
    }
    return token;
}

Token* lexer_identifier(Lexer* lexer, int line) {
    char token_buffer[256];
    int token_position = 0;

    while((isalnum(lexer->current_char) || lexer->current_char == '_') && token_position < 255) {
        token_buffer[token_position++] = lexer->current_char;
        lexer_advance(lexer);
    }

    token_buffer[token_position++] = '\0';
    
    if (strcmp(token_buffer, "char") == 0) return create_token(TKN_CHAR, token_buffer, line);
    if (strcmp(token_buffer, "int") == 0) return create_token(TKN_INT, token_buffer, line);
    if (strcmp(token_buffer, "long") == 0) return create_token(TKN_LONG, token_buffer, line);
    if (strcmp(token_buffer, "float") == 0) return create_token(TKN_FLOAT, token_buffer, line);
    if (strcmp(token_buffer, "double") == 0) return create_token(TKN_DOUBLE, token_buffer, line);
    if (strcmp(token_buffer, "if") == 0) return create_token(TKN_IF, token_buffer, line);
    if (strcmp(token_buffer, "else") == 0) return create_token(TKN_ELSE, token_buffer, line);
    if (strcmp(token_buffer, "while") == 0) return create_token(TKN_WHILE, token_buffer, line);
    if (strcmp(token_buffer, "for") == 0) return create_token(TKN_FOR, token_buffer, line);
    if (strcmp(token_buffer, "return") == 0) return create_token(TKN_RETURN, token_buffer, line);

    return create_token(TKN_ID, token_buffer, line);
}

long get_file_size(FILE* file){
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}

/*[INSIGHT]
    argc -> number of arguments
    argv -> array of the arguments
*/
int main(int argc, char* argv[]) {

    if(argc > 2){
        printf("Error: too many arguments\n");
        return 1;
    }

    if(argc < 2){
        printf("Error: missing input file\n");
        return 1;
    }

    FILE* file = fopen(argv[1], "r+");
    if (!file) {
        printf("Error: cannot open file %s\n", argv[1]);
        return 1;
    }

    long file_size = get_file_size(file);

    /*[INSIGHT] 
        By default, 'a-z' are int, so they are 4 bytes, 
        but when you cast them as char or declare them as such, they are 1 byte.
    */
    char* buffer = malloc(file_size + 1);
    fread(buffer, sizeof(char), file_size, file);
    buffer[file_size] = '\0';
    fclose(file);

    Lexer* lexer = init_lexer(buffer);
    
    while(lexer->current_char != '\0'){
        if (lexer->current_char == ' ' || lexer->current_char == '\n') {
            lexer_skip_whitespace(lexer);
            continue;
        }
        if (lexer->current_char == '/' && (lexer_peek(lexer) == '/' || lexer_peek(lexer) == '*')) {
            lexer_skip_comments(lexer);
            continue;
        }
        if (lexer->current_char == '\'' || lexer->current_char == '"') {
            int line = lexer->line;
            Token* token = lexer_char_or_string(lexer, line);
            printf("--- %s -> Lexeme: %s (line %d)\n", token_type_to_string(token->type), token->lexeme, token->line);
            
            free(token->lexeme);
            free(token);
            continue;
        }
        if (issybol(lexer->current_char)) {
            int line = lexer->line;
            Token* token = lexer_symbol(lexer, line);
            printf("--- %s -> Lexeme: %s (line %d)\n", token_type_to_string(token->type), token->lexeme, token->line);

            free(token->lexeme);
            free(token);
            continue;
        }
        if (isdigit(lexer->current_char) || (lexer->current_char == '.' && isdigit(lexer_peek(lexer)))) {
            int line = lexer->line;
            Token* token = lexer_number(lexer, line);
            printf("--- %s -> Lexeme: %s (line %d)\n", token_type_to_string(token->type), token->lexeme, token->line);
            
            free(token->lexeme);
            free(token);
            continue;
        }
        if (isalpha(lexer->current_char) || lexer->current_char == '_') {
            int line = lexer->line;
            Token* token = lexer_identifier(lexer, line);            
            printf("--- %s -> Lexeme: %s (line %d)\n", token_type_to_string(token->type), token->lexeme, token->line);

            free(token->lexeme);
            free(token);
            continue;
        }
        printf("Current char: '%c' (line %zu, column %zu)\n", lexer->current_char, lexer->line, lexer->column);
        lexer_advance(lexer);
    }
    
    free(buffer);
    free(lexer);
    return 0;
}