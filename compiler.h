#ifndef COMPILER_H
#define COMPILER_H

#include <stddef.h>
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

// functions to unit test
Lexer* init_lexer(char* buffer);
Token* create_token(TokenType type, char* lexeme, int line);
void lexer_advance(Lexer* lexer);
void lexer_skip_whitespace(Lexer* lexer);
char lexer_peek(Lexer* lexer);
void lexer_skip_equal_decl(Lexer* lexer);
void lexer_skip_comments(Lexer* lexer);
int lexer_skip_special_identifiers(Lexer* lexer);
Token* lexer_single_char_token(Lexer* lexer, TokenType type);
Token* lexer_two_char_token(Lexer* lexer, TokenType type);
Token* lexer_identifier(Lexer* lexer, int line);
Token* lexer_get_next_token(Lexer* lexer);
void push_stack(Parser* parser, int state, int symbol, Token* token);
StackItem pop_stack(Parser* parser);
int parse(Parser* parser);
Parser* init_parser(Lexer* lexer);
void free_parser(Parser* parser);

#endif // COMPILER_H 