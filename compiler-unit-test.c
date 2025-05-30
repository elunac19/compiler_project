#include "unity.h"
#include "compiler.h"
#include <stdlib.h>

void setUp(void) {
    // Set up code that runs before each test
}

void tearDown(void) {
    // Clean up code that runs after each test
}

// Test init_lexer with various input scenarios
void test_init_lexer_normal_input(void) {
    char* input = "int x = 5;";
    Lexer* lexer = init_lexer(input);
    
    TEST_ASSERT_NOT_NULL(lexer);
    TEST_ASSERT_EQUAL_STRING(input, lexer->buffer);
    TEST_ASSERT_EQUAL(0, lexer->position);
    TEST_ASSERT_EQUAL(1, lexer->line);
    TEST_ASSERT_EQUAL(1, lexer->column);
    TEST_ASSERT_EQUAL('i', lexer->current_char);
    
    free(lexer);
}

void test_init_lexer_empty_input(void) {
    char* input = "";
    Lexer* lexer = init_lexer(input);

    TEST_ASSERT_NOT_NULL(lexer);
    TEST_ASSERT_EQUAL_STRING(input, lexer->buffer);
    TEST_ASSERT_EQUAL(0, lexer->position);
    TEST_ASSERT_EQUAL(1, lexer->line);
    TEST_ASSERT_EQUAL(1, lexer->column);
    TEST_ASSERT_EQUAL('\0', lexer->current_char);

    free(lexer);
}

// Test create_token with different token types
void test_create_token_keyword(void) {
    Token* token = create_token(TKN_INT, "int", 1);
    
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TKN_INT, token->type);
    TEST_ASSERT_EQUAL_STRING("int", token->lexeme);
    TEST_ASSERT_EQUAL(1, token->line);
    
    free(token->lexeme);
    free(token);
}

void test_create_token_identifier(void) {
    Token* token = create_token(TKN_ID, "variable", 2);
    
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TKN_ID, token->type);
    TEST_ASSERT_EQUAL_STRING("variable", token->lexeme);
    TEST_ASSERT_EQUAL(2, token->line);
    
    free(token->lexeme);
    free(token);
}

// Test lexer_advance functionality
void test_lexer_advance_normal(void) {
    char* input = "abc";
    Lexer* lexer = init_lexer(input);
    
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

void test_lexer_advance_end_of_input(void) {
    char* input = "a";
    Lexer* lexer = init_lexer(input);
    
    lexer_advance(lexer);
    TEST_ASSERT_EQUAL('\0', lexer->current_char);
    TEST_ASSERT_EQUAL(1, lexer->position);
    TEST_ASSERT_EQUAL(2, lexer->column);
    
    free(lexer);
}

// Test lexer_skip_whitespace functionality
void test_lexer_skip_whitespace_spaces(void) {
    char* input = "   int";
    Lexer* lexer = init_lexer(input);
    
    lexer_skip_whitespace(lexer);
    TEST_ASSERT_EQUAL('i', lexer->current_char);
    TEST_ASSERT_EQUAL(3, lexer->position);
    TEST_ASSERT_EQUAL(4, lexer->column);
    
    free(lexer);
}

void test_lexer_skip_whitespace_newlines(void) {
    char* input = "\n\nint";
    Lexer* lexer = init_lexer(input);
    
    lexer_skip_whitespace(lexer);
    TEST_ASSERT_EQUAL('i', lexer->current_char);
    TEST_ASSERT_EQUAL(2, lexer->position);
    TEST_ASSERT_EQUAL(1, lexer->column);
    TEST_ASSERT_EQUAL(3, lexer->line);
    
    free(lexer);
}

void test_lexer_skip_whitespace_mixed(void) {
    char* input = " \n \n  int";
    Lexer* lexer = init_lexer(input);
    
    lexer_skip_whitespace(lexer);
    TEST_ASSERT_EQUAL('i', lexer->current_char);
    TEST_ASSERT_EQUAL(6, lexer->position);
    TEST_ASSERT_EQUAL(3, lexer->column);
    TEST_ASSERT_EQUAL(3, lexer->line);
    
    free(lexer);
}

// Test lexer_peek functionality
void test_lexer_peek_normal(void) {
    char* input = "abc";
    Lexer* lexer = init_lexer(input);
    
    TEST_ASSERT_EQUAL('b', lexer_peek(lexer));
    lexer_advance(lexer);
    TEST_ASSERT_EQUAL('c', lexer_peek(lexer));
    
    free(lexer);
}

void test_lexer_peek_end_of_input(void) {
    char* input = "a";
    Lexer* lexer = init_lexer(input);
    
    TEST_ASSERT_EQUAL('\0', lexer_peek(lexer));
    
    free(lexer);
}

// Test lexer_skip_equal_decl functionality
void test_lexer_skip_equal_decl_simple(void) {
    char* input = "= 5;";
    Lexer* lexer = init_lexer(input);
    
    lexer_skip_equal_decl(lexer);
    TEST_ASSERT_EQUAL(';', lexer->current_char);
    
    free(lexer);
}

void test_lexer_skip_equal_decl_with_parens(void) {
    char* input = "= (a + b);";
    Lexer* lexer = init_lexer(input);
    
    lexer_skip_equal_decl(lexer);
    TEST_ASSERT_EQUAL(';', lexer->current_char);
    
    free(lexer);
}

void test_lexer_skip_equal_decl_with_braces(void) {
    char* input = "= { x = 5; };";
    Lexer* lexer = init_lexer(input);
    
    lexer_skip_equal_decl(lexer);
    TEST_ASSERT_EQUAL(';', lexer->current_char);
    
    free(lexer);
}

// Test lexer_skip_comments functionality
void test_lexer_skip_comments_single_line(void) {
    char* input = "// This is a comment\nint x;";
    Lexer* lexer = init_lexer(input);
    
    lexer_skip_comments(lexer);
    TEST_ASSERT_EQUAL('i', lexer->current_char);
    TEST_ASSERT_EQUAL(2, lexer->line);
    
    free(lexer);
}

void test_lexer_skip_comments_multi_line(void) {
    char* input = "/* This is a\nmulti-line\ncomment */\nint x;";
    Lexer* lexer = init_lexer(input);
    
    lexer_skip_comments(lexer);
    TEST_ASSERT_EQUAL('i', lexer->current_char);
    TEST_ASSERT_EQUAL(4, lexer->line);
    
    free(lexer);
}

void test_lexer_skip_comments_nested(void) {
    char* input = "/* Outer /* Inner */ comment */\nint x;";
    Lexer* lexer = init_lexer(input);
    
    lexer_skip_comments(lexer);
    TEST_ASSERT_EQUAL('i', lexer->current_char);
    TEST_ASSERT_EQUAL(2, lexer->line);
    
    free(lexer);
}

int main(void) {
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
    RUN_TEST(test_lexer_skip_comments_nested);
    
    return UNITY_END();
}
