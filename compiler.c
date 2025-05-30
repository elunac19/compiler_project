#include <compiler.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>


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

Parser* init_parser(Lexer* lexer) {
    Parser* parser = malloc(sizeof(Parser));
    parser->lexer = lexer;
    parser->current_token = lexer_get_next_token(lexer);
    parser->stack_capacity = 1000;
    parser->stack = malloc(sizeof(StackItem) * parser->stack_capacity);
    parser->stack_top = -1;
    parser->grammar = grammar_rules;
    parser->num_rules = sizeof(grammar_rules) / sizeof(GrammarRule);;
    return parser;
}

int token_to_terminal_index(TokenType token_type) {
    switch (token_type) {
        case TKN_CLASS: return 0;
        case TKN_ID: return 1;
        case TKN_COLON: return 2;
        case TKN_COMMA: return 3;
        case TKN_PUBLIC: return 4;
        case TKN_PRIVATE: return 5;
        case TKN_PROTECTED: return 6;
        case TKN_LPAREN: return 7;
        case TKN_RPAREN: return 8;
        case TKN_LBRACE: return 9;
        case TKN_RBRACE: return 10;
        case TKN_SEMICOLON: return 11;
        case TKN_INT: return 12;
        case TKN_CHAR: return 13;
        case TKN_LONG: return 14;
        case TKN_FLOAT: return 15;
        case TKN_DOUBLE: return 16;
        case TKN_STRING: return 17;
        case TKN_VOID: return 18;
        case TKN_STAR: return 19;
        case TKN_AMPERSAND: return 20;
        case TKN_EOF: return 21;
        default: return -1;
    }
}

void push_stack(Parser* parser, int state, int symbol, Token* token) {
    if (parser->stack_top >= parser->stack_capacity - 1) {
        parser->stack_capacity *= 2;
        parser->stack = realloc(parser->stack, sizeof(StackItem) * parser->stack_capacity);
    }
    
    parser->stack_top++;
    parser->stack[parser->stack_top].state = state;
    parser->stack[parser->stack_top].symbol = symbol;
    parser->stack[parser->stack_top].token = token;
}

StackItem pop_stack(Parser* parser) {
    if (parser->stack_top >= 0) {
        return parser->stack[parser->stack_top--];
    }
    // Return empty item if stack is empty
    StackItem empty = {-1, 0, NULL};
    return empty;
}

int get_current_state(Parser* parser) {
    if (parser->stack_top >= 0) {
        return parser->stack[parser->stack_top].state;
    }
    return 0;
}

void init_parse_tables(Parser* parser) {
    // Initialize all entries to ERROR
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            parser->action_table[i][j].type = ACTION_ERROR;
            parser->action_table[i][j].state_or_rule = -1;
        }
        for (int j = 0; j < 50; j++) {
            parser->goto_table[i][j].next_state = -1;
        }
    }
    
    // Estado I0
    parser->action_table[0][0] = (ParserAction){ACTION_SHIFT, 14}; // class
    parser->action_table[0][12] = (ParserAction){ACTION_SHIFT, 1}; // int
    parser->action_table[0][13] = (ParserAction){ACTION_SHIFT, 2}; // char
    parser->action_table[0][14] = (ParserAction){ACTION_SHIFT, 3}; // long
    parser->action_table[0][15] = (ParserAction){ACTION_SHIFT, 4}; // float
    parser->action_table[0][16] = (ParserAction){ACTION_SHIFT, 5}; // double
    parser->action_table[0][17] = (ParserAction){ACTION_SHIFT, 6}; // string
    parser->action_table[0][18] = (ParserAction){ACTION_SHIFT, 7}; // void
    parser->action_table[0][1] = (ParserAction){ACTION_SHIFT, 8}; // id
    parser->action_table[0][7] = (ParserAction){ACTION_SHIFT, 32}; // (
    parser->goto_table[0][NT_A] = (GotoEntry){49};
    parser->goto_table[0][NT_C] = (GotoEntry){50};
    parser->goto_table[0][NT_B] = (GotoEntry){46};
    parser->goto_table[0][NT_D] = (GotoEntry){48};
    parser->goto_table[0][NT_E] = (GotoEntry){31};
    parser->goto_table[0][NT_O] = (GotoEntry){9};

    // Estados I1-I8 (todos tienen R9-R16 respectivamente)
    for (int term = 0; term < 22; term++) {
        if (term == 21) { // EOF ($)
            parser->action_table[1][term] = (ParserAction){ACTION_REDUCE, 9};
            parser->action_table[2][term] = (ParserAction){ACTION_REDUCE, 10};
            parser->action_table[3][term] = (ParserAction){ACTION_REDUCE, 11};
            parser->action_table[4][term] = (ParserAction){ACTION_REDUCE, 12};
            parser->action_table[5][term] = (ParserAction){ACTION_REDUCE, 13};
            parser->action_table[6][term] = (ParserAction){ACTION_REDUCE, 14};
            parser->action_table[7][term] = (ParserAction){ACTION_REDUCE, 15};
            parser->action_table[8][term] = (ParserAction){ACTION_REDUCE, 16};
        } else {
            parser->action_table[1][term] = (ParserAction){ACTION_REDUCE, 9};
            parser->action_table[2][term] = (ParserAction){ACTION_REDUCE, 10};
            parser->action_table[3][term] = (ParserAction){ACTION_REDUCE, 11};
            parser->action_table[4][term] = (ParserAction){ACTION_REDUCE, 12};
            parser->action_table[5][term] = (ParserAction){ACTION_REDUCE, 13};
            parser->action_table[6][term] = (ParserAction){ACTION_REDUCE, 14};
            parser->action_table[7][term] = (ParserAction){ACTION_REDUCE, 15};
            parser->action_table[8][term] = (ParserAction){ACTION_REDUCE, 16};
        }
    }

    // Estado I9
    parser->action_table[9][19] = (ParserAction){ACTION_SHIFT, 10}; // *
    parser->action_table[9][20] = (ParserAction){ACTION_SHIFT, 11}; // &
    parser->action_table[9][1] = (ParserAction){ACTION_SHIFT, 13}; // id
    parser->action_table[9][7] = (ParserAction){ACTION_SHIFT, 13}; // (
    parser->action_table[9][11] = (ParserAction){ACTION_SHIFT, 13}; // ;
    parser->goto_table[9][NT_P] = (GotoEntry){12};

    // Estado I10
    parser->action_table[10][1] = (ParserAction){ACTION_REDUCE, 17}; // id

    // Estado I11
    parser->action_table[11][1] = (ParserAction){ACTION_REDUCE, 18}; // id

    // Estado I12
    parser->action_table[12][1] = (ParserAction){ACTION_SHIFT, 13}; // id

    // Estado I13
    parser->action_table[13][7] = (ParserAction){ACTION_REDUCE, 8}; // (
    parser->action_table[13][11] = (ParserAction){ACTION_REDUCE, 8}; // ;
    parser->action_table[13][0] = (ParserAction){ACTION_REDUCE, 8}; // class
    parser->action_table[13][12] = (ParserAction){ACTION_REDUCE, 8}; // int
    parser->action_table[13][13] = (ParserAction){ACTION_REDUCE, 8}; // char
    parser->action_table[13][14] = (ParserAction){ACTION_REDUCE, 8}; // long
    parser->action_table[13][15] = (ParserAction){ACTION_REDUCE, 8}; // float
    parser->action_table[13][16] = (ParserAction){ACTION_REDUCE, 8}; // double
    parser->action_table[13][17] = (ParserAction){ACTION_REDUCE, 8}; // string
    parser->action_table[13][18] = (ParserAction){ACTION_REDUCE, 8}; // void
    parser->action_table[13][1] = (ParserAction){ACTION_REDUCE, 8}; // id
    parser->action_table[13][21] = (ParserAction){ACTION_REDUCE, 8}; // $

    // Estado I14
    parser->action_table[14][1] = (ParserAction){ACTION_SHIFT, 15}; // id

    // Estado I15
    parser->action_table[15][9] = (ParserAction){ACTION_SHIFT, 16}; // {
    parser->action_table[15][2] = (ParserAction){ACTION_SHIFT, 20}; // :
    parser->goto_table[15][NT_J] = (GotoEntry){16};

    // Estado I16
    parser->action_table[16][9] = (ParserAction){ACTION_SHIFT, 17}; // {

    // Estado I17
    parser->action_table[17][10] = (ParserAction){ACTION_SHIFT, 18}; // }

    // Estado I18
    parser->action_table[18][11] = (ParserAction){ACTION_SHIFT, 19}; // ;

    // Estado I19
    parser->action_table[19][0] = (ParserAction){ACTION_REDUCE, 7}; // class
    parser->action_table[19][12] = (ParserAction){ACTION_REDUCE, 7}; // int
    parser->action_table[19][13] = (ParserAction){ACTION_REDUCE, 7}; // char
    parser->action_table[19][14] = (ParserAction){ACTION_REDUCE, 7}; // long
    parser->action_table[19][15] = (ParserAction){ACTION_REDUCE, 7}; // float
    parser->action_table[19][16] = (ParserAction){ACTION_REDUCE, 7}; // double
    parser->action_table[19][17] = (ParserAction){ACTION_REDUCE, 7}; // string
    parser->action_table[19][18] = (ParserAction){ACTION_REDUCE, 7}; // void
    parser->action_table[19][1] = (ParserAction){ACTION_REDUCE, 7}; // id
    parser->action_table[19][7] = (ParserAction){ACTION_REDUCE, 7}; // (
    parser->action_table[19][21] = (ParserAction){ACTION_REDUCE, 7}; // $

    // Estado I20
    parser->action_table[20][4] = (ParserAction){ACTION_SHIFT, 21}; // public
    parser->action_table[20][5] = (ParserAction){ACTION_SHIFT, 22}; // private
    parser->action_table[20][6] = (ParserAction){ACTION_SHIFT, 23}; // protected
    parser->action_table[20][1] = (ParserAction){ACTION_SHIFT, 24}; // id
    parser->goto_table[20][NT_K] = (GotoEntry){27};
    parser->goto_table[20][NT_L] = (GotoEntry){28};
    parser->goto_table[20][NT_M] = (GotoEntry){25};

    // Estados I21-I23
    parser->action_table[21][1] = (ParserAction){ACTION_REDUCE, 26}; // id
    parser->action_table[22][1] = (ParserAction){ACTION_REDUCE, 27}; // id
    parser->action_table[23][1] = (ParserAction){ACTION_REDUCE, 28}; // id

    // Estado I24
    parser->action_table[24][9] = (ParserAction){ACTION_REDUCE, 25}; // {
    parser->action_table[24][3] = (ParserAction){ACTION_REDUCE, 25}; // ,

    // Estado I25
    parser->action_table[25][1] = (ParserAction){ACTION_SHIFT, 26}; // id

    // Estado I26
    parser->action_table[26][9] = (ParserAction){ACTION_REDUCE, 24}; // {
    parser->action_table[26][3] = (ParserAction){ACTION_REDUCE, 24}; // ,

    // Estado I27
    parser->action_table[27][9] = (ParserAction){ACTION_REDUCE, 20}; // {
    parser->action_table[27][3] = (ParserAction){ACTION_SHIFT, 29}; // ,

    // Estado I28
    parser->action_table[28][9] = (ParserAction){ACTION_REDUCE, 23}; // {
    parser->action_table[28][3] = (ParserAction){ACTION_REDUCE, 23}; // ,

    // Estado I29
    parser->action_table[29][4] = (ParserAction){ACTION_SHIFT, 21}; // public
    parser->action_table[29][5] = (ParserAction){ACTION_SHIFT, 22}; // private
    parser->action_table[29][6] = (ParserAction){ACTION_SHIFT, 23}; // protected
    parser->action_table[29][1] = (ParserAction){ACTION_SHIFT, 24}; // id
    parser->goto_table[29][NT_L] = (GotoEntry){30};
    parser->goto_table[29][NT_M] = (GotoEntry){25};

    // Estado I30
    parser->action_table[30][9] = (ParserAction){ACTION_REDUCE, 22}; // {

    // Estado I31
    parser->action_table[31][7] = (ParserAction){ACTION_SHIFT, 32}; // (
    parser->action_table[31][11] = (ParserAction){ACTION_SHIFT, 33}; // ;
    parser->goto_table[31][NT_F] = (GotoEntry){34};

    // Estado I32
    parser->action_table[32][12] = (ParserAction){ACTION_SHIFT, 1}; // int
    parser->action_table[32][13] = (ParserAction){ACTION_SHIFT, 2}; // char
    parser->action_table[32][14] = (ParserAction){ACTION_SHIFT, 3}; // long
    parser->action_table[32][15] = (ParserAction){ACTION_SHIFT, 4}; // float
    parser->action_table[32][16] = (ParserAction){ACTION_SHIFT, 5}; // double
    parser->action_table[32][17] = (ParserAction){ACTION_SHIFT, 6}; // string
    parser->action_table[32][18] = (ParserAction){ACTION_SHIFT, 7}; // void
    parser->action_table[32][1] = (ParserAction){ACTION_SHIFT, 8}; // id
    parser->action_table[32][8] = (ParserAction){ACTION_REDUCE, 30}; // )
    parser->goto_table[32][NT_G] = (GotoEntry){37};
    parser->goto_table[32][NT_N] = (GotoEntry){35};
    parser->goto_table[32][NT_E] = (GotoEntry){36};
    parser->goto_table[32][NT_O] = (GotoEntry){38};

    // Estado I33
    parser->action_table[33][0] = (ParserAction){ACTION_REDUCE, 34}; // class
    parser->action_table[33][12] = (ParserAction){ACTION_REDUCE, 34}; // int
    parser->action_table[33][13] = (ParserAction){ACTION_REDUCE, 34}; // char
    parser->action_table[33][14] = (ParserAction){ACTION_REDUCE, 34}; // long
    parser->action_table[33][15] = (ParserAction){ACTION_REDUCE, 34}; // float
    parser->action_table[33][16] = (ParserAction){ACTION_REDUCE, 34}; // double
    parser->action_table[33][17] = (ParserAction){ACTION_REDUCE, 34}; // string
    parser->action_table[33][18] = (ParserAction){ACTION_REDUCE, 34}; // void
    parser->action_table[33][1] = (ParserAction){ACTION_REDUCE, 34}; // id
    parser->action_table[33][7] = (ParserAction){ACTION_REDUCE, 34}; // (
    parser->action_table[33][21] = (ParserAction){ACTION_REDUCE, 34}; // $

    // Estado I34
    parser->action_table[34][0] = (ParserAction){ACTION_REDUCE, 6}; // class
    parser->action_table[34][12] = (ParserAction){ACTION_REDUCE, 6}; // int
    parser->action_table[34][13] = (ParserAction){ACTION_REDUCE, 6}; // char
    parser->action_table[34][14] = (ParserAction){ACTION_REDUCE, 6}; // long
    parser->action_table[34][15] = (ParserAction){ACTION_REDUCE, 6}; // float
    parser->action_table[34][16] = (ParserAction){ACTION_REDUCE, 6}; // double
    parser->action_table[34][17] = (ParserAction){ACTION_REDUCE, 6}; // string
    parser->action_table[34][18] = (ParserAction){ACTION_REDUCE, 6}; // void
    parser->action_table[34][1] = (ParserAction){ACTION_REDUCE, 6}; // id
    parser->action_table[34][7] = (ParserAction){ACTION_REDUCE, 6}; // (
    parser->action_table[34][21] = (ParserAction){ACTION_REDUCE, 6}; // $

    // Estado I35
    parser->action_table[35][8] = (ParserAction){ACTION_REDUCE, 29}; // )
    parser->action_table[35][3] = (ParserAction){ACTION_SHIFT, 39}; // ,

    // Estado I36
    parser->action_table[36][8] = (ParserAction){ACTION_REDUCE, 32}; // )

    // Estado I37
    parser->action_table[37][8] = (ParserAction){ACTION_SHIFT, 41}; // )

    // Estado I38
    parser->action_table[38][19] = (ParserAction){ACTION_SHIFT, 10}; // *
    parser->action_table[38][20] = (ParserAction){ACTION_SHIFT, 11}; // &
    parser->action_table[38][1] = (ParserAction){ACTION_SHIFT, 45}; // id
    parser->action_table[38][8] = (ParserAction){ACTION_REDUCE, 19}; // )
    parser->goto_table[38][NT_P] = (GotoEntry){44}; //-------->

    // Estado I39
    parser->action_table[39][12] = (ParserAction){ACTION_SHIFT, 1}; // int
    parser->action_table[39][13] = (ParserAction){ACTION_SHIFT, 2}; // char
    parser->action_table[39][14] = (ParserAction){ACTION_SHIFT, 3}; // long
    parser->action_table[39][15] = (ParserAction){ACTION_SHIFT, 4}; // float
    parser->action_table[39][16] = (ParserAction){ACTION_SHIFT, 5}; // double
    parser->action_table[39][17] = (ParserAction){ACTION_SHIFT, 6}; // string
    parser->action_table[39][18] = (ParserAction){ACTION_SHIFT, 7}; // void
    parser->action_table[39][1] = (ParserAction){ACTION_SHIFT, 8}; // id
    parser->goto_table[39][NT_E] = (GotoEntry){40};
    parser->goto_table[39][NT_O] = (GotoEntry){38};

    // Estado I40
    parser->action_table[40][8] = (ParserAction){ACTION_REDUCE, 31}; // )

    // Estado I41
    parser->action_table[41][9] = (ParserAction){ACTION_SHIFT, 42}; // {

    // Estado I42
    parser->action_table[42][10] = (ParserAction){ACTION_SHIFT, 43}; // }

    // Estado I43
    parser->action_table[43][0] = (ParserAction){ACTION_REDUCE, 33}; // class
    parser->action_table[43][12] = (ParserAction){ACTION_REDUCE, 33}; // int
    parser->action_table[43][13] = (ParserAction){ACTION_REDUCE, 33}; // char
    parser->action_table[43][14] = (ParserAction){ACTION_REDUCE, 33}; // long
    parser->action_table[43][15] = (ParserAction){ACTION_REDUCE, 33}; // float
    parser->action_table[43][16] = (ParserAction){ACTION_REDUCE, 33}; // double
    parser->action_table[43][17] = (ParserAction){ACTION_REDUCE, 33}; // string
    parser->action_table[43][18] = (ParserAction){ACTION_REDUCE, 33}; // void
    parser->action_table[43][1] = (ParserAction){ACTION_REDUCE, 33}; // id
    parser->action_table[43][7] = (ParserAction){ACTION_REDUCE, 33}; // (
    parser->action_table[43][21] = (ParserAction){ACTION_REDUCE, 33}; // $

    // Estado I44
    parser->action_table[44][1] = (ParserAction){ACTION_SHIFT, 45}; // id
    parser->action_table[44][8] = (ParserAction){ACTION_REDUCE, 8}; // )

    // Estado I45
    parser->action_table[45][8] = (ParserAction){ACTION_REDUCE, 8}; // )

    // Estado I46
    parser->action_table[46][0] = (ParserAction){ACTION_SHIFT, 14}; // class
    parser->action_table[46][12] = (ParserAction){ACTION_SHIFT, 1}; // int
    parser->action_table[46][13] = (ParserAction){ACTION_SHIFT, 2}; // char
    parser->action_table[46][14] = (ParserAction){ACTION_SHIFT, 3}; // long
    parser->action_table[46][15] = (ParserAction){ACTION_SHIFT, 4}; // float
    parser->action_table[46][16] = (ParserAction){ACTION_SHIFT, 5}; // double
    parser->action_table[46][17] = (ParserAction){ACTION_SHIFT, 6}; // string
    parser->action_table[46][18] = (ParserAction){ACTION_SHIFT, 7}; // void
    parser->action_table[46][1] = (ParserAction){ACTION_SHIFT, 8}; // id
    parser->action_table[46][7] = (ParserAction){ACTION_SHIFT, 32}; // (
    parser->action_table[46][21] = (ParserAction){ACTION_REDUCE, 4}; // $
    parser->goto_table[46][NT_C] = (GotoEntry){47};
    parser->goto_table[46][NT_B] = (GotoEntry){46};
    parser->goto_table[46][NT_D] = (GotoEntry){48};
    parser->goto_table[46][NT_E] = (GotoEntry){31};
    parser->goto_table[46][NT_O] = (GotoEntry){9};

    // Estado I47
    parser->action_table[47][21] = (ParserAction){ACTION_REDUCE, 3}; // $

    // Estado I48
    parser->action_table[48][0] = (ParserAction){ACTION_REDUCE, 5}; // class
    parser->action_table[48][12] = (ParserAction){ACTION_REDUCE, 5}; // int
    parser->action_table[48][13] = (ParserAction){ACTION_REDUCE, 5}; // char
    parser->action_table[48][14] = (ParserAction){ACTION_REDUCE, 5}; // long
    parser->action_table[48][15] = (ParserAction){ACTION_REDUCE, 5}; // float
    parser->action_table[48][16] = (ParserAction){ACTION_REDUCE, 5}; // double
    parser->action_table[48][17] = (ParserAction){ACTION_REDUCE, 5}; // string
    parser->action_table[48][18] = (ParserAction){ACTION_REDUCE, 5}; // void
    parser->action_table[48][1] = (ParserAction){ACTION_REDUCE, 5}; // id
    parser->action_table[48][7] = (ParserAction){ACTION_REDUCE, 5}; // (
    parser->action_table[48][21] = (ParserAction){ACTION_REDUCE, 5}; // $

    // Estado I49
    parser->action_table[49][21] = (ParserAction){ACTION_ACCEPT, 0}; // $

    // Estado I50
    parser->action_table[50][21] = (ParserAction){ACTION_REDUCE, 2}; // $
}

const char* non_terminal_to_string(NonTerminal nt) {
    switch (nt) {
        case NT_A: return "A";
        case NT_C: return "C";
        case NT_B: return "B";
        case NT_D: return "D";
        case NT_E: return "E";
        case NT_F: return "F";
        case NT_G: return "G";
        case NT_J: return "J";
        case NT_K: return "K";
        case NT_L: return "L";
        case NT_M: return "M";
        case NT_N: return "N";
        case NT_O: return "O";
        case NT_P: return "P";
        default: return "unknown";
    }
}

int parse(Parser* parser) {
    printf("Starting parse...\n");
    
    while (1) {
        int current_state = get_current_state(parser);
        int terminal_index = token_to_terminal_index(parser->current_token->type);
        
        if (terminal_index == -1) {
            printf("Error: Unknown token type %d\n", parser->current_token->type);
            return 0;
        }
        
        ParserAction action = parser->action_table[current_state][terminal_index];
        
        printf("State: %d, Token: %s, Action: ", current_state, 
               token_type_to_string(parser->current_token->type));
        
        switch (action.type) {
            case ACTION_SHIFT:
                printf("SHIFT %d\n", action.state_or_rule);
                // Push current token and new state onto stack

                if (parser->current_token->type == TKN_EOF) {
                    return 1;
                }

                push_stack(parser, action.state_or_rule, -parser->current_token->type, parser->current_token);
                // Get next token
                parser->current_token = lexer_get_next_token(parser->lexer);
                break;
                
            case ACTION_REDUCE:
                printf("REDUCE by rule %d\n", action.state_or_rule);
                // Get the grammar rule
                GrammarRule rule = parser->grammar[action.state_or_rule];
                
                // Pop items from stack according to rule
                for (int i = 0; i < rule.right_count; i++) {
                    pop_stack(parser);
                }
                
                // Get new current state
                current_state = get_current_state(parser);
                
                // Push non-terminal and go to new state
                int next_state = parser->goto_table[current_state][rule.left].next_state;
                if (next_state == -1) {
                    printf("Error: No GOTO entry for state %d, non-terminal %s\n", 
                           current_state, non_terminal_to_string(rule.left));
                    return 0;
                }
                push_stack(parser, next_state, rule.left, NULL);
                break;
                
            case ACTION_ACCEPT:
                printf("ACCEPT\n");
                printf("Parse successful!\n");
                return 1;
                
            case ACTION_ERROR:
            default:
                printf("ERROR\n");
                printf("Parse error at line %d: unexpected token '%s'\n", 
                       parser->current_token->line, parser->current_token->lexeme);
                return 0;
        }
    }
}

void free_parser(Parser* parser) {
    free(parser->stack);
    free(parser);
}

int test_parser(char* source_code) {
    Lexer* lexer = init_lexer(source_code);
    Parser* parser = init_parser(lexer);
    
    int success = parse(parser);
    
    free_parser(parser);
    free(lexer);
    
    return success;
}

/*[INSIGHT]
    argc -> number of arguments
    argv -> array of the arguments
*/
#ifdef NOT_TEST
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

    printf("=== LEXICAL ANALYSIS ===\n");
    Lexer* lexer = init_lexer(buffer);

    Token* token;
    TokenType type;
    do {
        token = lexer_get_next_token(lexer);
        printf("Token: %-20s Lexeme: %-24s Line: %d\n", 
               token_type_to_string(token->type), token->lexeme, token->line);
        
        type = token->type;
        free(token->lexeme);
        free(token);
    } while (type != TKN_EOF);
    
    free(lexer);

    // // Análisis sintáctico (parsing)
    // printf("\n=== SYNTAX ANALYSIS ===\n");
    // int parse_result = test_parser(buffer);
    
    // if (parse_result) {
    //     printf("Parsing successful!\n");
    // } else {
    //     printf("Parsing failed!\n");
    // }

    // Limpieza de memoria
    free(buffer);

    return parse_result ? 0 : 1;
}
#endif