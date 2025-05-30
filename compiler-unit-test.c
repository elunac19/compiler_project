#include "unity.h"
#include "compiler.h"
#include <stdlib.h>

void setUp(void)
{
    // Set up code that runs before each test
}

void tearDown(void)
{
    // Clean up code that runs after each test
}

// Test init_lexer with various input scenarios
void test_init_lexer_normal_input(void)
{
    char *input = "int x = 5;";
    Lexer *lexer = init_lexer(input);

    TEST_ASSERT_NOT_NULL(lexer);
    TEST_ASSERT_EQUAL_STRING(input, lexer->buffer);
    TEST_ASSERT_EQUAL(0, lexer->position);
    TEST_ASSERT_EQUAL(1, lexer->line);
    TEST_ASSERT_EQUAL(1, lexer->column);
    TEST_ASSERT_EQUAL('i', lexer->current_char);

    free(lexer);
}

void test_init_lexer_empty_input(void)
{
    char *input = "";
    Lexer *lexer = init_lexer(input);

    TEST_ASSERT_NOT_NULL(lexer);
    TEST_ASSERT_EQUAL_STRING(input, lexer->buffer);
    TEST_ASSERT_EQUAL(0, lexer->position);
    TEST_ASSERT_EQUAL(1, lexer->line);
    TEST_ASSERT_EQUAL(1, lexer->column);
    TEST_ASSERT_EQUAL('\0', lexer->current_char);

    free(lexer);
}

// Test create_token with different token types
void test_create_token_keyword(void)
{
    Token *token = create_token(TKN_INT, "int", 1);

    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TKN_INT, token->type);
    TEST_ASSERT_EQUAL_STRING("int", token->lexeme);
    TEST_ASSERT_EQUAL(1, token->line);

    free(token->lexeme);
    free(token);
}

void test_create_token_identifier(void)
{
    Token *token = create_token(TKN_ID, "variable", 2);

    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TKN_ID, token->type);
    TEST_ASSERT_EQUAL_STRING("variable", token->lexeme);
    TEST_ASSERT_EQUAL(2, token->line);

    free(token->lexeme);
    free(token);
}

// Test lexer_advance functionality
void test_lexer_advance_normal(void)
{
    char *input = "abc";
    Lexer *lexer = init_lexer(input);

    TEST_ASSERT_EQUAL('a', lexer->current_char);
    lexer_advance(lexer);
    TEST_ASSERT_EQUAL('b', lexer->current_char);
    TEST_ASSERT_EQUAL(1, lexer->position);
    TEST_ASSERT_EQUAL(2, lexer->column);

    lexer_advance(lexer);
    TEST_ASSERT_EQUAL('c', lexer->current_char);
    TEST_ASSERT_EQUAL(2, lexer->position);
    TEST_ASSERT_EQUAL(3, lexer->column);

    free(lexer);
}

void test_lexer_advance_end_of_input(void)
{
    char *input = "a";
    Lexer *lexer = init_lexer(input);

    lexer_advance(lexer);
    TEST_ASSERT_EQUAL('\0', lexer->current_char);
    TEST_ASSERT_EQUAL(1, lexer->position);
    TEST_ASSERT_EQUAL(2, lexer->column);

    free(lexer);
}

// Test lexer_skip_whitespace functionality
void test_lexer_skip_whitespace_spaces(void)
{
    char *input = "   int";
    Lexer *lexer = init_lexer(input);

    lexer_skip_whitespace(lexer);
    TEST_ASSERT_EQUAL('i', lexer->current_char);
    TEST_ASSERT_EQUAL(3, lexer->position);
    TEST_ASSERT_EQUAL(4, lexer->column);

    free(lexer);
}

void test_lexer_skip_whitespace_newlines(void)
{
    char *input = "\n\nint";
    Lexer *lexer = init_lexer(input);

    lexer_skip_whitespace(lexer);
    TEST_ASSERT_EQUAL('i', lexer->current_char);
    TEST_ASSERT_EQUAL(2, lexer->position);
    TEST_ASSERT_EQUAL(1, lexer->column);
    TEST_ASSERT_EQUAL(3, lexer->line);

    free(lexer);
}

void test_lexer_skip_whitespace_mixed(void)
{
    char *input = " \n \n  int";
    Lexer *lexer = init_lexer(input);

    lexer_skip_whitespace(lexer);
    TEST_ASSERT_EQUAL('i', lexer->current_char);
    TEST_ASSERT_EQUAL(6, lexer->position);
    TEST_ASSERT_EQUAL(3, lexer->column);
    TEST_ASSERT_EQUAL(3, lexer->line);

    free(lexer);
}

// Test lexer_peek functionality
void test_lexer_peek_normal(void)
{
    char *input = "abc";
    Lexer *lexer = init_lexer(input);

    TEST_ASSERT_EQUAL('b', lexer_peek(lexer));
    lexer_advance(lexer);
    TEST_ASSERT_EQUAL('c', lexer_peek(lexer));

    free(lexer);
}

void test_lexer_peek_end_of_input(void)
{
    char *input = "a";
    Lexer *lexer = init_lexer(input);

    TEST_ASSERT_EQUAL('\0', lexer_peek(lexer));

    free(lexer);
}

// Test lexer_skip_equal_decl functionality
void test_lexer_skip_equal_decl_simple(void)
{
    char *input = "= 5;";
    Lexer *lexer = init_lexer(input);

    lexer_skip_equal_decl(lexer);
    TEST_ASSERT_EQUAL(';', lexer->current_char);

    free(lexer);
}

void test_lexer_skip_equal_decl_with_parens(void)
{
    char *input = "= (a + b);";
    Lexer *lexer = init_lexer(input);

    lexer_skip_equal_decl(lexer);
    TEST_ASSERT_EQUAL(')', lexer->current_char);

    free(lexer);
}

void test_lexer_skip_equal_decl_with_braces(void)
{
    char *input = "= { x = 5; };";
    Lexer *lexer = init_lexer(input);

    lexer_skip_equal_decl(lexer);
    TEST_ASSERT_EQUAL(';', lexer->current_char);

    free(lexer);
}

// Test lexer_skip_comments functionality
void test_lexer_skip_comments_single_line(void)
{
    char *input = "// This is a comment\nint x;";
    Lexer *lexer = init_lexer(input);

    lexer_skip_comments(lexer);
    TEST_ASSERT_EQUAL('\n', lexer->current_char);
    TEST_ASSERT_EQUAL(1, lexer->line);

    free(lexer);
}

void test_lexer_skip_comments_multi_line(void)
{
    char *input = "/* This is a\nmulti-line\ncomment */\nint x;";
    Lexer *lexer = init_lexer(input);

    lexer_skip_comments(lexer);
    TEST_ASSERT_EQUAL('\n', lexer->current_char);
    TEST_ASSERT_EQUAL(3, lexer->line);

    free(lexer);
}

// Test lexer_skip_special_identifiers functionality
void test_lexer_skip_special_identifiers_template(void)
{
    char *input = "template<typename T> class MyClass;";
    Lexer *lexer = init_lexer(input);

    int result = lexer_skip_special_identifiers(lexer);
    TEST_ASSERT_EQUAL(1, result);
    TEST_ASSERT_EQUAL(1, lexer->line); // moves to next line
    TEST_ASSERT_EQUAL(35, lexer->position);
    TEST_ASSERT_EQUAL('\0', lexer->current_char); // Should be at end of line

    free(lexer);
}

void test_lexer_skip_special_identifiers_const(void)
{
    char *input = "const int x = 5;";
    Lexer *lexer = init_lexer(input);

    int result = lexer_skip_special_identifiers(lexer);
    TEST_ASSERT_EQUAL(1, result);                // Should return 1 to indicate it was skipped
    TEST_ASSERT_EQUAL(' ', lexer->current_char); // Should be at 'int'
    TEST_ASSERT_EQUAL(5, lexer->position);       // space char after const

    free(lexer);
}

// Test lexer_single_char_token functionality
void test_lexer_single_char_token_star(void)
{
    char *input = "*";
    Lexer *lexer = init_lexer(input);

    Token *token = lexer_single_char_token(lexer, TKN_STAR);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TKN_STAR, token->type);
    TEST_ASSERT_EQUAL_STRING("*", token->lexeme);
    TEST_ASSERT_EQUAL(1, token->line);

    free(token->lexeme);
    free(token);
    free(lexer);
}

void test_lexer_single_char_token_semicolon(void)
{
    char *input = ";";
    Lexer *lexer = init_lexer(input);

    Token *token = lexer_single_char_token(lexer, TKN_SEMICOLON);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TKN_SEMICOLON, token->type);
    TEST_ASSERT_EQUAL_STRING(";", token->lexeme);
    TEST_ASSERT_EQUAL(1, token->line);

    free(token->lexeme);
    free(token);
    free(lexer);
}

void test_lexer_single_char_token_ampersand(void)
{
    char *input = "&";
    Lexer *lexer = init_lexer(input);

    Token *token = lexer_single_char_token(lexer, TKN_AMPERSAND);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TKN_AMPERSAND, token->type);
    TEST_ASSERT_EQUAL_STRING("&", token->lexeme);
    TEST_ASSERT_EQUAL(1, token->line);

    free(token->lexeme);
    free(token);
    free(lexer);
}

// Test lexer_two_char_token functionality
void test_lexer_two_char_token_comment_start(void)
{
    char *input = "//";
    Lexer *lexer = init_lexer(input);

    Token *token = lexer_two_char_token(lexer, TKN_ERROR); // Using ERROR as type since we don't have a specific type for comments
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL_STRING("//", token->lexeme);
    TEST_ASSERT_EQUAL(1, token->line);

    free(token->lexeme);
    free(token);
    free(lexer);
}

void test_lexer_two_char_token_comment_block_start(void)
{
    char *input = "/*";
    Lexer *lexer = init_lexer(input);

    Token *token = lexer_two_char_token(lexer, TKN_ERROR); // Using ERROR as type since we don't have a specific type for comments
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL_STRING("/*", token->lexeme);
    TEST_ASSERT_EQUAL(1, token->line);

    free(token->lexeme);
    free(token);
    free(lexer);
}

// Test lexer_char_or_string functionality
void test_lexer_char_or_string_single_char(void)
{
    char *input = "'a'";
    Lexer *lexer = init_lexer(input);

    Token *token = lexer_char_or_string(lexer, 1);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TKN_CHAR_LIT, token->type);
    TEST_ASSERT_EQUAL_STRING("a", token->lexeme);
    TEST_ASSERT_EQUAL('a', token->value.char_value);
    TEST_ASSERT_EQUAL(1, token->line);

    free(token->lexeme);
    free(token);
    free(lexer);
}

void test_lexer_char_or_string_empty_char(void)
{
    char *input = "''";
    Lexer *lexer = init_lexer(input);

    Token *token = lexer_char_or_string(lexer, 1);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TKN_ERROR, token->type);
    TEST_ASSERT_EQUAL_STRING("Char literal empty", token->lexeme);
    TEST_ASSERT_EQUAL(1, token->line);

    free(token->lexeme);
    free(token);
    free(lexer);
}

void test_lexer_char_or_string_string_lit(void)
{
    char *input = "\"hello world\"";
    Lexer *lexer = init_lexer(input);

    Token *token = lexer_char_or_string(lexer, 1);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TKN_STRING_LIT, token->type);
    TEST_ASSERT_EQUAL_STRING("hello world", token->lexeme);
    TEST_ASSERT_EQUAL_STRING("hello world", token->value.string_value);
    TEST_ASSERT_EQUAL(1, token->line);

    free(token->lexeme);
    free(token);
    free(lexer);
}

void test_lexer_char_or_string_unclosed_string(void)
{
    char *input = "\"hello world";
    Lexer *lexer = init_lexer(input);

    Token *token = lexer_char_or_string(lexer, 1);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TKN_ERROR, token->type);
    TEST_ASSERT_EQUAL_STRING("String literal unclosed", token->lexeme);
    TEST_ASSERT_EQUAL(1, token->line);

    free(token->lexeme);
    free(token);
    free(lexer);
}

// Test lexer_identifier functionality
void test_lexer_identifier_keyword(void)
{
    char *input = "int";
    Lexer *lexer = init_lexer(input);

    Token *token = lexer_identifier(lexer, 1);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TKN_INT, token->type);
    TEST_ASSERT_EQUAL_STRING("int", token->lexeme);
    TEST_ASSERT_EQUAL(1, token->line);

    free(token->lexeme);
    free(token);
    free(lexer);
}

void test_lexer_identifier_class(void)
{
    char *input = "class";
    Lexer *lexer = init_lexer(input);

    Token *token = lexer_identifier(lexer, 1);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TKN_CLASS, token->type);
    TEST_ASSERT_EQUAL_STRING("class", token->lexeme);
    TEST_ASSERT_EQUAL(1, token->line);

    free(token->lexeme);
    free(token);
    free(lexer);
}

void test_lexer_identifier_variable(void)
{
    char *input = "myVariable123";
    Lexer *lexer = init_lexer(input);

    Token *token = lexer_identifier(lexer, 1);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TKN_ID, token->type);
    TEST_ASSERT_EQUAL_STRING("myVariable123", token->lexeme);
    TEST_ASSERT_EQUAL(1, token->line);

    free(token->lexeme);
    free(token);
    free(lexer);
}

// Test lexer_get_next_token functionality
void test_lexer_get_next_token_keywords(void)
{
    char *input = "int class void";
    Lexer *lexer = init_lexer(input);

    Token *token = lexer_get_next_token(lexer);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TKN_INT, token->type);
    TEST_ASSERT_EQUAL_STRING("int", token->lexeme);
    free(token->lexeme);
    free(token);

    token = lexer_get_next_token(lexer);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TKN_CLASS, token->type);
    TEST_ASSERT_EQUAL_STRING("class", token->lexeme);
    free(token->lexeme);
    free(token);

    token = lexer_get_next_token(lexer);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TKN_VOID, token->type);
    TEST_ASSERT_EQUAL_STRING("void", token->lexeme);
    free(token->lexeme);
    free(token);

    free(lexer);
}

void test_lexer_get_next_token_mixed(void)
{
    char *input = "int x = 5;";
    Lexer *lexer = init_lexer(input);

    Token *token = lexer_get_next_token(lexer);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TKN_INT, token->type);
    TEST_ASSERT_EQUAL_STRING("int", token->lexeme);
    free(token->lexeme);
    free(token);

    token = lexer_get_next_token(lexer);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TKN_ID, token->type);
    TEST_ASSERT_EQUAL_STRING("x", token->lexeme);
    free(token->lexeme);
    free(token);

    token = lexer_get_next_token(lexer);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TKN_SEMICOLON, token->type);
    free(token->lexeme);
    free(token);

    free(lexer);
}

void test_lexer_get_next_token_comments(void)
{
    char *input = "// comment\nint x;";
    Lexer *lexer = init_lexer(input);

    Token *token = lexer_get_next_token(lexer);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TKN_INT, token->type);
    TEST_ASSERT_EQUAL_STRING("int", token->lexeme);
    free(token->lexeme);
    free(token);

    token = lexer_get_next_token(lexer);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TKN_ID, token->type);
    TEST_ASSERT_EQUAL_STRING("x", token->lexeme);
    free(token->lexeme);
    free(token);

    token = lexer_get_next_token(lexer);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TKN_SEMICOLON, token->type);
    TEST_ASSERT_EQUAL_STRING(";", token->lexeme);
    free(token->lexeme);
    free(token);

    free(lexer);
}

// Test push_stack and pop_stack functionality
void test_push_stack_normal(void)
{
    Lexer *lexer = init_lexer("");
    Parser *parser = init_parser(lexer);
    Token *token = create_token(TKN_INT, "int", 1);
    
    push_stack(parser, 1, -TKN_INT, token);
    TEST_ASSERT_EQUAL(0, parser->stack_top);
    TEST_ASSERT_EQUAL(1, parser->stack[0].state);
    TEST_ASSERT_EQUAL(-TKN_INT, parser->stack[0].symbol);
    TEST_ASSERT_EQUAL(token, parser->stack[0].token);
    
    free(token->lexeme);
    free(token);
    free_parser(parser);
    free(lexer);
}

void test_pop_stack_normal(void)
{
    Lexer *lexer = init_lexer("");
    Parser *parser = init_parser(lexer);
    Token *token = create_token(TKN_INT, "int", 1);
    
    push_stack(parser, 1, -TKN_INT, token);
    StackItem item = pop_stack(parser);
    
    TEST_ASSERT_EQUAL(-1, parser->stack_top);
    TEST_ASSERT_EQUAL(1, item.state);
    TEST_ASSERT_EQUAL(-TKN_INT, item.symbol);
    TEST_ASSERT_EQUAL(token, item.token);
    
    free(token->lexeme);
    free(token);
    free_parser(parser);
    free(lexer);
}

void test_pop_stack_empty(void)
{
    Lexer *lexer = init_lexer("");
    Parser *parser = init_parser(lexer);
    
    StackItem item = pop_stack(parser);
    
    TEST_ASSERT_EQUAL(-1, item.state);
    TEST_ASSERT_EQUAL(0, item.symbol);
    TEST_ASSERT_NULL(item.token);
    
    free_parser(parser);
    free(lexer);
}

void test_push_pop_sequence(void)
{
    Lexer *lexer = init_lexer("");
    Parser *parser = init_parser(lexer);
    
    // Push multiple items
    Token *token1 = create_token(TKN_INT, "int", 1);
    Token *token2 = create_token(TKN_ID, "x", 1);
    Token *token3 = create_token(TKN_SEMICOLON, ";", 1);
    
    push_stack(parser, 1, -TKN_INT, token1);
    push_stack(parser, 2, -TKN_ID, token2);
    push_stack(parser, 3, -TKN_SEMICOLON, token3);
    
    // Pop them in reverse order
    StackItem item3 = pop_stack(parser);
    TEST_ASSERT_EQUAL(3, item3.state);
    TEST_ASSERT_EQUAL(-TKN_SEMICOLON, item3.symbol);
    TEST_ASSERT_EQUAL(token3, item3.token);
    
    StackItem item2 = pop_stack(parser);
    TEST_ASSERT_EQUAL(2, item2.state);
    TEST_ASSERT_EQUAL(-TKN_ID, item2.symbol);
    TEST_ASSERT_EQUAL(token2, item2.token);
    
    StackItem item1 = pop_stack(parser);
    TEST_ASSERT_EQUAL(1, item1.state);
    TEST_ASSERT_EQUAL(-TKN_INT, item1.symbol);
    TEST_ASSERT_EQUAL(token1, item1.token);
    
    // Stack should be empty
    TEST_ASSERT_EQUAL(-1, parser->stack_top);
    
    free(token1->lexeme);
    free(token1);
    free(token2->lexeme);
    free(token2);
    free(token3->lexeme);
    free(token3);
    free_parser(parser);
    free(lexer);
}

// Test parse functionality
void test_parse_valid_class_declaration(void)
{
    char *input = "class MyClass { };";
    Lexer *lexer = init_lexer(input);
    Parser *parser = init_parser(lexer);
    
    int result = parse(parser);
    TEST_ASSERT_EQUAL(1, result); // Should return 1 for successful parse
    
    free_parser(parser);
    free(lexer);
}

void test_parse_valid_method_declaration(void)
{
    char *input = "int main() { };";
    Lexer *lexer = init_lexer(input);
    Parser *parser = init_parser(lexer);
    
    int result = parse(parser);
    TEST_ASSERT_EQUAL(1, result); // Should return 1 for successful parse
    
    free_parser(parser);
    free(lexer);
}

void test_parse_invalid_syntax(void)
{
    char *input = "class { };"; // Missing class name
    Lexer *lexer = init_lexer(input);
    Parser *parser = init_parser(lexer);
    
    int result = parse(parser);
    TEST_ASSERT_EQUAL(0, result); // Should return 0 for failed parse
    
    free_parser(parser);
    free(lexer);
}

#ifdef TEST // avoid duplicate mains
int main(void)
{
    UNITY_BEGIN();

    // Run init_lexer tests
    RUN_TEST(test_init_lexer_normal_input);
    RUN_TEST(test_init_lexer_empty_input);

    // Run create_token tests
    RUN_TEST(test_create_token_keyword);
    RUN_TEST(test_create_token_identifier);

    // Run lexer_advance tests
    RUN_TEST(test_lexer_advance_normal);
    RUN_TEST(test_lexer_advance_end_of_input);

    // Run lexer_skip_whitespace tests
    RUN_TEST(test_lexer_skip_whitespace_spaces);
    RUN_TEST(test_lexer_skip_whitespace_newlines);
    RUN_TEST(test_lexer_skip_whitespace_mixed);

    // Run lexer_peek tests
    RUN_TEST(test_lexer_peek_normal);
    RUN_TEST(test_lexer_peek_end_of_input);

    // Run lexer_skip_equal_decl tests
    RUN_TEST(test_lexer_skip_equal_decl_simple);
    RUN_TEST(test_lexer_skip_equal_decl_with_parens);
    RUN_TEST(test_lexer_skip_equal_decl_with_braces);

    // Run lexer_skip_comments tests
    RUN_TEST(test_lexer_skip_comments_single_line);
    RUN_TEST(test_lexer_skip_comments_multi_line);

    // Run lexer_skip_special_identifiers tests
    RUN_TEST(test_lexer_skip_special_identifiers_template);
    RUN_TEST(test_lexer_skip_special_identifiers_const);

    // Run lexer_single_char_token tests
    RUN_TEST(test_lexer_single_char_token_star);
    RUN_TEST(test_lexer_single_char_token_semicolon);
    RUN_TEST(test_lexer_single_char_token_ampersand);

    // Run lexer_two_char_token tests
    RUN_TEST(test_lexer_two_char_token_comment_start);
    RUN_TEST(test_lexer_two_char_token_comment_block_start);

    // Run lexer_char_or_string tests
    RUN_TEST(test_lexer_char_or_string_single_char);
    RUN_TEST(test_lexer_char_or_string_empty_char);
    RUN_TEST(test_lexer_char_or_string_string_lit);
    RUN_TEST(test_lexer_char_or_string_unclosed_string);

    // Run lexer_identifier tests
    RUN_TEST(test_lexer_identifier_keyword);
    RUN_TEST(test_lexer_identifier_class);
    RUN_TEST(test_lexer_identifier_variable);

    // Run lexer_get_next_token tests
    RUN_TEST(test_lexer_get_next_token_keywords);
    RUN_TEST(test_lexer_get_next_token_mixed);
    RUN_TEST(test_lexer_get_next_token_comments);

    // Run push_stack and pop_stack tests
    RUN_TEST(test_push_stack_normal);
    RUN_TEST(test_pop_stack_normal);
    RUN_TEST(test_pop_stack_empty);
    RUN_TEST(test_push_pop_sequence);

    // Run parse tests
    RUN_TEST(test_parse_valid_class_declaration);
    RUN_TEST(test_parse_valid_method_declaration);
    RUN_TEST(test_parse_invalid_syntax);

    return UNITY_END();
}
#endif // COMPILER_H