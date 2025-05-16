#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    //DataType Keywords
    TKN_CHAR,       
    TKN_INT,        
    TKN_SHORT,      
    TKN_LONG,       
    TKN_FLOAT,
    TKN_DOUBLE,
    TKN_UNSIGNED,

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
    TKN_INT_LIT,
    TKN_SHORT_LIT,
    TKN_LONG_LIT,
    TKN_FLOAT_LIT,
    TKN_DOUBLE_LIT,
    TKN_UNSIGNED_LIT,
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
    TKN_RBRACE,
    TKN_SEMICOLON,
    TKN_COMMA,

    //Other
    TKN_ERROR,
    TKN_EOF

} TokenType;

typedef struct {
    TokenType type;
    char* lexeme; 
    int line;
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

Lexer* init_lexer(char* buffer){
    Lexer* lexer = malloc(sizeof(Lexer));
    lexer->buffer = buffer;
    lexer->buffer_len = strlen(buffer);
    lexer->position = 0;
    lexer->line = 1;
    lexer->column = 1;
    lexer->current_char = (lexer->buffer_len > 0) ? lexer->buffer[lexer->position] : '\0' ;
    return lexer;
}

void lexer_advance(Lexer* lexer){
    if(lexer->position < lexer->buffer_len){
        lexer->position++;
        lexer->current_char = lexer->buffer[lexer->position];
        lexer->column++;
    } else {
        lexer->current_char = '\0';
    }
}

void lexer_skip_whitespace(Lexer* lexer){
    while(lexer->current_char == ' ' || lexer->current_char == '\n'){
        if(lexer->current_char == '\n'){
            lexer->line++;
            lexer->column=0;
        }
        lexer_advance(lexer);
    }
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
        printf("First char: '%c' (line %zu, column %zu)\n", lexer->current_char, lexer->line, lexer->column);
        lexer_advance(lexer);
    }
    
    free(buffer);
    free(lexer);

    return 0;
}