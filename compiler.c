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
    TKN_VOID,

    //Flow Statement Keywords
    TKN_IF,
    TKN_ELSE,
    TKN_FOR,
    TKN_WHILE,

    //OOP Keywords
    TKN_CLASS,    
    TKN_PUBLIC,   
    TKN_PRIVATE,  
    TKN_PROTECTED,
    TKN_THIS,     
    TKN_NEW,      
    TKN_DELETE,   
    TKN_VIRTUAL,  
    TKN_OVERRIDE, 
    TKN_STATIC,   

    TKN_COLON,
    TKN_SCOPE,
    TKN_DOT,   
    TKN_ARROW,
    TKN_AMPERSAND,
    
    //Libraries
    TKN_HASH,          
    TKN_INCLUDE,

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
    TKN_STAR,
    TKN_SLASH,
    TKN_MODULO,
    TKN_ASSIGN,
    TKN_EQ,
    TKN_NEQ,
    TKN_LT,
    TKN_GT,
    TKN_LTE,
    TKN_GTE,

    //Unary Operators
    TKN_INCREMENT,
    TKN_DECREMENT,

    //Compound Operators
    TKN_PLUS_EQUAL,       
    TKN_MINUS_EQUAL,      
    TKN_STAR_EQUAL,       
    TKN_SLASH_EQUAL,      
    TKN_MODULO_EQUAL,

    //Logical Operators
    TKN_AND,
    TKN_OR,
    TKN_NOT,

    // ~
    TKN_TILDE,

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

/*[PERCHANCE]
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
        case TKN_VOID: return "TKN_VOID";

        // Flow Statement Keywords
        case TKN_IF: return "TKN_IF";
        case TKN_ELSE: return "TKN_ELSE";
        case TKN_FOR: return "TKN_FOR";
        case TKN_WHILE: return "TKN_WHILE";

            //OOP Keywords
        case TKN_CLASS: return "TKN_CLASS";
        case TKN_PUBLIC: return "TKN_PUBLIC";  
        case TKN_PROTECTED: return "TKN_PROTECTED";    
        case TKN_THIS: return "TKN_THIS"; 
        case TKN_NEW: return "TKN_NEW";     
        case TKN_DELETE: return "TKN_DELETE"; 
        case TKN_VIRTUAL: return "TKN_VIRTUAL";
        case TKN_OVERRIDE: return "TKN_OVERRIDE";
        case TKN_STATIC: return "TKN_STATIC";
        case TKN_COLON: return "TKN_COLON";
        case TKN_SCOPE: return "TKN_SCOPE";
        case TKN_DOT: return "TKN_DOT";
        case TKN_ARROW: return "TKN_ARROW";

        //Preprocesor
        case TKN_HASH: return "TKN_HASH";
        case TKN_INCLUDE: return "TKN_INCLUDE";

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
        case TKN_STAR: return "TKN_STAR";
        case TKN_SLASH: return "TKN_SLASH";
        case TKN_MODULO: return "TKN_MODULO";
        case TKN_ASSIGN: return "TKN_ASSIGN";
        case TKN_EQ: return "TKN_EQ";
        case TKN_NEQ: return "TKN_NEQ";
        case TKN_LT: return "TKN_LT";
        case TKN_GT: return "TKN_GT";
        case TKN_LTE: return "TKN_LTE";
        case TKN_GTE: return "TKN_GTE";
        
        //Unary Operators
        case TKN_INCREMENT: return "TKN_INCREMENT";
        case TKN_DECREMENT: return "TKN_DECREMENT";

        //Compound Operators
        case TKN_PLUS_EQUAL: return "TKN_PLUS_EQUAL";      
        case TKN_MINUS_EQUAL: return "TKN_MINUS_EQUAL";      
        case TKN_STAR_EQUAL: return "TKN_STAR_EQUAL";       
        case TKN_SLASH_EQUAL: return "TKN_SLASH_EQUAL";      
        case TKN_MODULO_EQUAL: return "TKN_MODULO_EQUAL";
        
        // Logical Operators
        case TKN_AND: return "TKN_AND";
        case TKN_OR: return "TKN_OR";
        case TKN_NOT: return "TKN_NOT";

        // ~
        case TKN_TILDE: return "TKN_TILDE"; 

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

Token* lexer_single_char_token(Lexer* lexer, TokenType type) {
    char token_buffer[] = {lexer->current_char, '\0'};
    lexer_advance(lexer);
    return create_token(type, token_buffer, lexer->line);
}

Token* lexer_two_char_token(Lexer* lexer, TokenType type) {
    char token_buffer[] = {lexer->current_char, lexer_peek(lexer), '\0'};
    lexer_advance(lexer);
    lexer_advance(lexer);
    return create_token(type, token_buffer, lexer->line);
}

/*[PERCHANCE]
    Escape sequences '\n', '\t'
*/
Token* lexer_char_or_string(Lexer* lexer, int line) {
    if(lexer->current_char == '\''){
        lexer_advance(lexer);

        // char c = '';
        if(lexer->current_char == '\''){
            lexer_advance(lexer);
            return create_token(TKN_ERROR, "Char literal empty", line);
        }

        // char y = '
        if(lexer->current_char == '\n' || lexer->current_char == '\0'){
            return create_token(TKN_ERROR, "Char literal unclosed", line);
        }
        
        // char x = 'sdaxzx'; || char v = 'aio
        if(lexer_peek(lexer) != '\''){
            while(lexer->current_char != '\'' && lexer->current_char != '\n' && lexer->current_char != '\0'){
                lexer_advance(lexer);
            }
            if(lexer->current_char == '\''){
                lexer_advance(lexer);
                return create_token(TKN_ERROR, "Char literal too long", line);
            }
            return create_token(TKN_ERROR, "Char literal unclosed", line);
        }

        char token_buffer[] = {lexer->current_char, '\0'};
        lexer_advance(lexer);
        lexer_advance(lexer);

        Token* token = create_token(TKN_CHAR_LIT, token_buffer, line);
        token->value.char_value = token_buffer[0];
        return token;
    }

    lexer_advance(lexer);

    // char* x = " || string x = "
    if(lexer->current_char == '\n' || lexer->current_char == '\0'){
        return create_token(TKN_ERROR, "String literal unclosed", line);
    }

    char token_buffer[256]; 
    int token_position = 0;

    while(lexer->current_char != '"' && lexer->current_char != '\0' && lexer->current_char != '\n' && token_position < 255){
        token_buffer[token_position++] = lexer->current_char;
        lexer_advance(lexer);
    }

    if(lexer->current_char == '"'){
        lexer_advance(lexer);
        token_buffer[token_position] = '\0';
    
        Token* token = create_token(TKN_STRING_LIT, token_buffer, line);
        token->value.string_value = token->lexeme;
        return token;
    }
    
    return create_token(TKN_ERROR, "String literal unclosed", line);
}

/*[PERCHANCE]
   Better handling for longs and float: 456L, 0xF, 2.7f
*/
Token* lexer_number(Lexer* lexer, int line) {
    char token_buffer[256];
    int token_position = 0;
    int is_float = 0;

    while (isdigit(lexer->current_char) && token_position < 255) {
        token_buffer[token_position++] = lexer->current_char;
        lexer_advance(lexer);
    }

    if(lexer->current_char == '.') {
        is_float = 1;
        token_buffer[token_position++] = lexer->current_char;
        lexer_advance(lexer);

        while (isdigit(lexer->current_char) && token_position < 255) {
            token_buffer[token_position++] = lexer->current_char;
            lexer_advance(lexer);
        }

        if (lexer->current_char == '.'){
            lexer_advance(lexer);
            return create_token(TKN_ERROR, "Multiple decimal points", line);
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
    if (strcmp(token_buffer, "string") == 0) return create_token(TKN_STRING, token_buffer, line);
    if (strcmp(token_buffer, "void") == 0) return create_token(TKN_VOID, token_buffer, line);
    if (strcmp(token_buffer, "if") == 0) return create_token(TKN_IF, token_buffer, line);
    if (strcmp(token_buffer, "else") == 0) return create_token(TKN_ELSE, token_buffer, line);
    if (strcmp(token_buffer, "for") == 0) return create_token(TKN_FOR, token_buffer, line);
    if (strcmp(token_buffer, "while") == 0) return create_token(TKN_WHILE, token_buffer, line);
    if (strcmp(token_buffer, "class") == 0) return create_token(TKN_CLASS, token_buffer, line);
    if (strcmp(token_buffer, "public") == 0) return create_token(TKN_PUBLIC, token_buffer, line);
    if (strcmp(token_buffer, "private") == 0) return create_token(TKN_PRIVATE, token_buffer, line);
    if (strcmp(token_buffer, "protected") == 0) return create_token(TKN_PROTECTED, token_buffer, line);
    if (strcmp(token_buffer, "this") == 0) return create_token(TKN_THIS, token_buffer, line);
    if (strcmp(token_buffer, "new") == 0) return create_token(TKN_NEW, token_buffer, line);
    if (strcmp(token_buffer, "delete") == 0) return create_token(TKN_DELETE, token_buffer, line);
    if (strcmp(token_buffer, "virtual") == 0) return create_token(TKN_VIRTUAL, token_buffer, line);
    if (strcmp(token_buffer, "override") == 0) return create_token(TKN_OVERRIDE, token_buffer, line);
    if (strcmp(token_buffer, "static") == 0) return create_token(TKN_STATIC, token_buffer, line);
    if (strcmp(token_buffer, "include") == 0) return create_token(TKN_INCLUDE, token_buffer,line);
    if (strcmp(token_buffer, "return") == 0) return create_token(TKN_RETURN, token_buffer, line);

    return create_token(TKN_ID, token_buffer, line);
}

Token* lexer_get_next_token(Lexer* lexer) {
    while(lexer->current_char != '\0'){
        if (lexer->current_char == ' ' || lexer->current_char == '\n') {
            lexer_skip_whitespace(lexer);
            continue;
        }

        if (lexer->current_char == '/' && (lexer_peek(lexer) == '/' || lexer_peek(lexer) == '*')) {
            lexer_skip_comments(lexer);
            continue;
        }
        
        int line = lexer->line;
        
        if (lexer->current_char == '\'' || lexer->current_char == '"') {
            return lexer_char_or_string(lexer, line);
        }

        if (isdigit(lexer->current_char) || (lexer->current_char == '.' && isdigit(lexer_peek(lexer)))) {
            return lexer_number(lexer, line);
        }

        if (isalpha(lexer->current_char) || lexer->current_char == '_') {
            return lexer_identifier(lexer, line);            
        }

        switch (lexer->current_char) {
            case '+': {
                if(lexer_peek(lexer) == '=') return lexer_two_char_token(lexer, TKN_PLUS_EQUAL);
                if(lexer_peek(lexer) == '+') return lexer_two_char_token(lexer, TKN_INCREMENT);
                return lexer_single_char_token(lexer, TKN_PLUS);
            }
            case '-': {
                if(lexer_peek(lexer) == '=') return lexer_two_char_token(lexer, TKN_MINUS_EQUAL);
                if(lexer_peek(lexer) == '-') return lexer_two_char_token(lexer, TKN_DECREMENT);
                if(lexer_peek(lexer) == '>') return lexer_two_char_token(lexer, TKN_ARROW);
                return lexer_single_char_token(lexer, TKN_MINUS);
            }
            case '*': {
                if(lexer_peek(lexer) == '=') return lexer_two_char_token(lexer, TKN_STAR_EQUAL);
                return lexer_single_char_token(lexer, TKN_STAR);
            }
            case '/': {
                if(lexer_peek(lexer) == '=') return lexer_two_char_token(lexer, TKN_SLASH_EQUAL);
                return lexer_single_char_token(lexer, TKN_SLASH);
            }
            case '%': {
                if(lexer_peek(lexer) == '=') return lexer_two_char_token(lexer, TKN_MODULO_EQUAL);
                return lexer_single_char_token(lexer, TKN_MODULO);
            }
            case '=': {
                if(lexer_peek(lexer) == '=') return lexer_two_char_token(lexer, TKN_EQ);
                return lexer_single_char_token(lexer, TKN_ASSIGN);
            }
            case '!': {
                if(lexer_peek(lexer) == '=') return lexer_two_char_token(lexer, TKN_NEQ); 
                return lexer_single_char_token(lexer, TKN_NOT);
            }
            case '<': {
                if(lexer_peek(lexer) == '=') return lexer_two_char_token(lexer, TKN_LTE); 
                return lexer_single_char_token(lexer, TKN_LT);
            }
            case '>': {
                if(lexer_peek(lexer) == '=') return lexer_two_char_token(lexer, TKN_GTE); 
                return lexer_single_char_token(lexer, TKN_GT);
            }
            case '&': {
                if(lexer_peek(lexer) == '&') return lexer_two_char_token(lexer, TKN_AND); 
                return lexer_single_char_token(lexer, TKN_AMPERSAND);
            }
            case '|': {
                if(lexer_peek(lexer) == '|') return lexer_two_char_token(lexer, TKN_OR); 
                return lexer_single_char_token(lexer, TKN_ERROR);
            }
            case '(': {
                return lexer_single_char_token(lexer, TKN_LPAREN);
            }
            case ')': {
                return lexer_single_char_token(lexer, TKN_RPAREN);
            }
            case '{': {
                return lexer_single_char_token(lexer, TKN_LBRACE);
            }
            case '}': {
                return lexer_single_char_token(lexer, TKN_RBRACE);
            }
            case '[': {
                return lexer_single_char_token(lexer, TKN_LBRACKET);
            }
            case ']': {
                return lexer_single_char_token(lexer, TKN_RBRACKET);
            }
            case ';': {
                return lexer_single_char_token(lexer, TKN_SEMICOLON);
            }
            case ',': {
                return lexer_single_char_token(lexer, TKN_COMMA);
            }
            case '#': {
                return lexer_single_char_token(lexer, TKN_HASH);
            }
            case ':': {
                if(lexer_peek(lexer) == ':') return lexer_two_char_token(lexer, TKN_SCOPE);
                return lexer_single_char_token(lexer, TKN_COLON);
            }
            case '.': {
                return lexer_single_char_token(lexer, TKN_DOT);
            }
            default: {
                lexer_advance(lexer);
                return lexer_single_char_token(lexer, TKN_ERROR);
            }
        }
    }
    return create_token(TKN_EOF, "", lexer->line);
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

    FILE* file = fopen(argv[1], "r");
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

    Token* token;
    TokenType type;
    do {
        token = lexer_get_next_token(lexer);
        printf("Token: %-20s Lexeme: %-24s Line: %d\n", token_type_to_string(token->type), token->lexeme, token->line);
        
        type = token->type;
        free(token->lexeme);
        free(token);
    } while (type != TKN_EOF);
    
    free(buffer);
    free(lexer);

    return 0;
}