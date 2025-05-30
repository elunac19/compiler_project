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

    //OOP Keywords
    TKN_CLASS,    
    TKN_PUBLIC,   
    TKN_PRIVATE,  
    TKN_PROTECTED,

    TKN_COLON,
    TKN_AMPERSAND,
    TKN_STAR,
    
    //Libraries
    TKN_HASH,          

    //Identifiers and literals
    TKN_ID,

    TKN_CHAR_LIT,
    TKN_STRING_LIT,

    //Punctuation
    TKN_LPAREN,
    TKN_RPAREN,
    TKN_LBRACE,
    TKN_RBRACE,
    TKN_LBRACKET,
    TKN_RBRACKET,
    TKN_SEMICOLON,
    TKN_COMMA,

    //Other
    TKN_ERROR,
    TKN_EOF
} TokenType;

typedef enum {
    NT_PRIME,
    NT_A, // program
    NT_C, // Declaration list  
    NT_B, // Declaration
    NT_D, // Class declaration
    NT_E, // Type with modifiers
    NT_F, // Function or variable end
    NT_G, // Parameter list
    NT_J, // Inheritance part
    NT_K, // Base class list
    NT_L, // Base class item
    NT_M, // Access modifier
    NT_N, // Non-empty parameter list
    NT_O, // Type specifier
    NT_P, // Pointer/reference modifier
    NUM_NON_TERMINALS
} NonTerminal;

typedef enum {
    ACTION_SHIFT,
    ACTION_REDUCE,
    ACTION_ACCEPT,
    ACTION_ERROR
} ActionType;

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

typedef struct {
    NonTerminal left;           
    int right[10];       
    int right_count;           
    int rule_num;              
} GrammarRule;

typedef struct {
    ActionType type;
    int state_or_rule;  
} ParserAction;

typedef struct {
    int next_state;
} GotoEntry;

typedef struct {
    int state;
    int symbol;  
    Token* token; 
} StackItem;

typedef struct {
    Lexer* lexer;
    Token* current_token;
    StackItem* stack;
    int stack_top;
    int stack_capacity;
    ParserAction action_table[100][100];  
    GotoEntry goto_table[100][50];        
    GrammarRule* grammar;
    int num_rules;
} Parser;

GrammarRule grammar_rules[] = {
    // Empece mi tabla en el 1 y no quiero cambiar todo XD
    {0, {}, 0, 0},
    
    // Rule 1: A' → A (Augmented Grammar)
    {NT_PRIME, {NT_A}, 1, 1},
    
    // Rule 2: A → C
    {NT_A, {NT_C}, 1, 2},
    
    // Rule 3: C → B C
    {NT_C, {NT_B, NT_C}, 2, 3},
    
    // Rule 4: C → ε
    {NT_C, {}, 0, 4},
    
    // Rule 5: B → D
    {NT_B, {NT_D}, 1, 5},
    
    // Rule 6: B → E F
    {NT_B, {NT_E, NT_F}, 2, 6},
    
    // Rule 7: D → class id J { } ;
    {NT_D, {-TKN_CLASS, -TKN_ID, NT_J, -TKN_LBRACE, -TKN_RBRACE, -TKN_SEMICOLON}, 6, 7},
    
    // Rule 8: E → O P id
    {NT_E, {NT_O, NT_P, -TKN_ID}, 3, 8},
    
    // Rule 9: O → int
    {NT_O, {-TKN_INT}, 1, 9},
    
    // Rule 10: O → char
    {NT_O, {-TKN_CHAR}, 1, 10},
    
    // Rule 11: O → long
    {NT_O, {-TKN_LONG}, 1, 11},
    
    // Rule 12: O → float
    {NT_O, {-TKN_FLOAT}, 1, 12},
    
    // Rule 13: O → double
    {NT_O, {-TKN_DOUBLE}, 1, 13},
    
    // Rule 14: O → string
    {NT_O, {-TKN_STRING}, 1, 14},
    
    // Rule 15: O → void
    {NT_O, {-TKN_VOID}, 1, 15},
    
    // Rule 16: O → id
    {NT_O, {-TKN_ID}, 1, 16},
    
    // Rule 17: P → *
    {NT_P, {-TKN_STAR}, 1, 17},
    
    // Rule 18: P → &
    {NT_P, {-TKN_AMPERSAND}, 1, 18},
    
    // Rule 19: P → ε 
    {NT_P, {}, 0, 19},
    
    // Rule 20: J → : K
    {NT_J, {-TKN_COLON, NT_K}, 2, 20},
    
    // Rule 21: J → ε
    {NT_J, {}, 0, 21},
    
    // Rule 22: K → K , L
    {NT_K, {NT_K, -TKN_COMMA, NT_L}, 3, 22},
    
    // Rule 23: K → L
    {NT_K, {NT_L}, 1, 23},
    
    // Rule 24: L → M id
    {NT_L, {NT_M, -TKN_ID}, 2, 24},
    
    // Rule 25: L → id
    {NT_L, {-TKN_ID}, 1, 25},
    
    // Rule 26: M → public
    {NT_M, {-TKN_PUBLIC}, 1, 26},
    
    // Rule 27: M → private
    {NT_M, {-TKN_PRIVATE}, 1, 27},
    
    // Rule 28: M → protected
    {NT_M, {-TKN_PROTECTED}, 1, 28},
    
    // Rule 29: G → N
    {NT_G, {NT_N}, 1, 29},
    
    // Rule 30: G → ε
    {NT_G, {}, 0, 30},
    
    // Rule 31: N → N , E
    {NT_N, {NT_N, -TKN_COMMA, NT_E}, 3, 31},
    
    // Rule 32: N → E
    {NT_N, {NT_E}, 1, 32},
    
    // Rule 33: F → ( G ) { }
    {NT_F, {-TKN_LPAREN, NT_G, -TKN_RPAREN, -TKN_LBRACE, -TKN_RBRACE}, 5, 33},
    
    // Rule 34: F → ;
    {NT_F, {-TKN_SEMICOLON}, 1, 34},
};

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

        //OOP Keywords
        case TKN_CLASS: return "TKN_CLASS";
        case TKN_PUBLIC: return "TKN_PUBLIC";  
        case TKN_PROTECTED: return "TKN_PROTECTED";    
        case TKN_COLON: return "TKN_COLON";

        //Preprocesor
        case TKN_HASH: return "TKN_HASH";

        // Identifiers and literals
        case TKN_ID: return "TKN_ID";
        case TKN_CHAR_LIT: return "TKN_CHAR_LIT";
        case TKN_STRING_LIT: return "TKN_STRING_LIT";

        // Arithmetic Operators
        case TKN_STAR: return "TKN_STAR";

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

void lexer_skip_equal_decl(Lexer* lexer){
    if(lexer->current_char == '='){
        lexer_advance(lexer);

        int paren_count = 0;
        int brace_count = 0;

        while (lexer->current_char != '\0') {
            if (lexer->current_char == '(') {
                paren_count++;
            } else if (lexer->current_char == ')') {
                if (paren_count > 0) paren_count--;
                else break; 
            } else if (lexer->current_char == '{') {
                brace_count++;
            } else if (lexer->current_char == '}') {
                if (brace_count > 0) brace_count--;
            }

            if (paren_count == 0 && brace_count == 0 &&
                (lexer->current_char == ';' ||
                 lexer->current_char == ',' ||
                 lexer->current_char == ')')) {
                break;
            }

            lexer_advance(lexer);
        }

    }
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

        while((lexer->current_char != '*' && lexer_peek(lexer) != '/') && lexer->current_char != '\0'){
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

int lexer_skip_special_identifiers(Lexer* lexer) {
    int start_pos = lexer->position;
    int start_col = lexer->column;

    char token_buffer[256];
    int token_position = 0;

    while(isalpha(lexer->current_char) && token_position < 255) {
        token_buffer[token_position++] = lexer->current_char;
        lexer_advance(lexer);
    }

    token_buffer[token_position++] = '\0';

    if (strcmp(token_buffer, "template") == 0 || strcmp(token_buffer, "using") == 0 || strcmp(token_buffer, "typedef") == 0 ) {
        while (lexer->current_char != '\0' && lexer->current_char != '\n') {
            lexer_advance(lexer);
        }
        return 1;  
    }

    if (strcmp(token_buffer, "const") == 0 || strcmp(token_buffer, "inline") == 0 || strcmp(token_buffer, "static") == 0) {
        return 1;
    }

    if (strcmp(token_buffer, "std") == 0){
        lexer_advance(lexer);
        lexer_advance(lexer);
        return 1;
    }

    lexer->position = start_pos;
    lexer->column = start_col;
    lexer->current_char = lexer->buffer[lexer->position];
    return 0;
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

/*
struct{}; -> ignorar todo literalmente 
*/
Token* lexer_identifier(Lexer* lexer, int line) {
    char token_buffer[256];
    int token_position = 0;

    while((isalnum(lexer->current_char) || lexer->current_char == '_') && token_position < 255) {
        token_buffer[token_position++] = lexer->current_char;
        lexer_advance(lexer);
    }

    token_buffer[token_position] = '\0';

    if (strcmp(token_buffer, "char") == 0) return create_token(TKN_CHAR, token_buffer, line);
    if (strcmp(token_buffer, "int") == 0) return create_token(TKN_INT, token_buffer, line);
    if (strcmp(token_buffer, "long") == 0) return create_token(TKN_LONG, token_buffer, line);
    if (strcmp(token_buffer, "float") == 0) return create_token(TKN_FLOAT, token_buffer, line);
    if (strcmp(token_buffer, "double") == 0) return create_token(TKN_DOUBLE, token_buffer, line);
    if (strcmp(token_buffer, "string") == 0) return create_token(TKN_STRING, token_buffer, line);
    if (strcmp(token_buffer, "void") == 0) return create_token(TKN_VOID, token_buffer, line);
    if (strcmp(token_buffer, "class") == 0) return create_token(TKN_CLASS, token_buffer, line);
    if (strcmp(token_buffer, "public") == 0) return create_token(TKN_PUBLIC, token_buffer, line);
    if (strcmp(token_buffer, "private") == 0) return create_token(TKN_PRIVATE, token_buffer, line);
    if (strcmp(token_buffer, "protected") == 0) return create_token(TKN_PROTECTED, token_buffer, line);
    if (strcmp(token_buffer, "vector") == 0) {
        if (lexer->current_char == '<') {
            int croc_count = 0;
            while (lexer->current_char != '\0') {
                if (lexer->current_char == '<') {
                    croc_count++;
                } else if (lexer->current_char == '>') {
                    croc_count--;
                    if (croc_count == 0) {
                        lexer_advance(lexer);
                        break;
                    }
                }
                lexer_advance(lexer);
            }
        }
    
        return create_token(TKN_VOID, token_buffer, line);
    }

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

        if (isalpha(lexer->current_char) || lexer->current_char == '_') {
           if (!lexer_skip_special_identifiers(lexer)) {
               return lexer_identifier(lexer, line);            
           }
           continue;
        }

        switch (lexer->current_char) {
            case '*': {
                return lexer_single_char_token(lexer, TKN_STAR);
            }
            case '&': {
                return lexer_single_char_token(lexer, TKN_AMPERSAND);
            }
            case '(': {
                return lexer_single_char_token(lexer, TKN_LPAREN);
            }
            case ')': {
                return lexer_single_char_token(lexer, TKN_RPAREN);
            }
            case '{': {
                int brace_count = 0;
                int line = lexer->line;
                while (lexer->current_char != '\0') {
                    if(lexer->current_char == '\n'){
                        lexer->line++;
                        lexer->column=0;
                    } 
                    if (lexer->current_char == '{') {
                        brace_count++;
                    } else if (lexer->current_char == '}') {
                        brace_count--;
                        if (brace_count == 0) {
                            break;
                        }
                    }
                    lexer_advance(lexer);
                }
                return create_token(TKN_LBRACE, (char[]){'{','\0'}, line);
            }
            case '}': {
                return lexer_single_char_token(lexer, TKN_RBRACE);
            }
            case ';': {
                return lexer_single_char_token(lexer, TKN_SEMICOLON);
            }
            case ',': {
                int start_pos = lexer->position;
                int start_col = lexer->column;
                int paren_count = 0;
                int brace_detected = 0;
                lexer_advance(lexer);  

                while (lexer->current_char != '\0') {
                    if (lexer->current_char == '(') {
                        paren_count++;
                    } else if (lexer->current_char == ')') {
                        if (paren_count > 0) paren_count--;
                    } 
                    else if (lexer->current_char == '{') {
                        brace_detected = 1;
                        break;
                    } 
                    else if (lexer->current_char == ';' && paren_count == 0) {
                        break;
                    }

                    lexer_advance(lexer);
                }

                if (brace_detected) {
                    lexer->position = start_pos;
                    lexer->column = start_col;
                    lexer->current_char = lexer->buffer[lexer->position];
                    return lexer_single_char_token(lexer, TKN_COMMA);
                }
                continue;
            }
            case ':': {
                return lexer_single_char_token(lexer, TKN_COLON);
            }
            case '#': {
                while (lexer->current_char != '\0' && lexer->current_char != '\n') {
                    lexer_advance(lexer);
                }   
                continue;
            }
            case '[': {
                lexer_advance(lexer);
                while(lexer->current_char != ']' && lexer->current_char != '\0'){
                    lexer_advance(lexer);
                }
                lexer_advance(lexer);
                continue;
            }
            case '=': {
                lexer_skip_equal_decl(lexer);
                continue;
            }
            default: {
                lexer_advance(lexer);
                return create_token(TKN_ERROR, (char[]){lexer->current_char, '\0'}, lexer->line);
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

