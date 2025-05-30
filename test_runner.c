#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "compiler.h"

#define MAX_PATH_LENGTH 256
#define MAX_FILES 100

typedef struct {
    char path[MAX_PATH_LENGTH];
    int expected_valid;
} TestFile;

void print_results(int total_tests, int correct_valid, int correct_invalid, int total_valid, int total_invalid) {
    int total_correct = correct_valid + correct_invalid;
    float accuracy = (float)total_correct / total_tests * 100;
    float valid_accuracy = (float)correct_valid / total_valid * 100;
    float invalid_accuracy = (float)correct_invalid / total_invalid * 100;
    
    printf("\n=== Test Results ===\n");
    printf("Valid Files:\n");
    printf("  Total valid files: %d\n", total_valid);
    printf("  Correctly identified as valid: %d\n", correct_valid);
    printf("  Valid files accuracy: %.2f%%\n", valid_accuracy);
    
    printf("\nInvalid Files:\n");
    printf("  Total invalid files: %d\n", total_invalid);
    printf("  Correctly identified as invalid: %d\n", correct_invalid);
    printf("  Invalid files accuracy: %.2f%%\n", invalid_accuracy);
    
    printf("\nOverall Results:\n");
    printf("  Total tests: %d\n", total_tests);
    printf("  Total correct: %d\n", total_correct);
    printf("  Overall accuracy: %.2f%%\n", accuracy);
}

int is_valid_oop_file(const char* filepath) {
    FILE* file = fopen(filepath, "r");
    if (!file) {
        printf("Error: Cannot open file %s\n", filepath);
        return -1;
    }

    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Read file content
    char* buffer = malloc(file_size + 1);
    fread(buffer, sizeof(char), file_size, file);
    buffer[file_size] = '\0';
    fclose(file);

    // Test the parser
    int result = test_parser(buffer);
    free(buffer);
    return result;
}

void run_tests(const char* valid_dir, const char* invalid_dir) {
    TestFile test_files[MAX_FILES];
    int file_count = 0;
    int total_valid = 0;
    int total_invalid = 0;
    DIR* dir;
    struct dirent* ent;
    char path[MAX_PATH_LENGTH];

    // Read valid files
    dir = opendir(valid_dir);
    if (dir != NULL) {
        while ((ent = readdir(dir)) != NULL && file_count < MAX_FILES) {
            if (strstr(ent->d_name, ".cpp") != NULL) {
                snprintf(path, MAX_PATH_LENGTH, "%s/%s", valid_dir, ent->d_name);
                strncpy(test_files[file_count].path, path, MAX_PATH_LENGTH);
                test_files[file_count].expected_valid = 1;
                file_count++;
                total_valid++;
            }
        }
        closedir(dir);
    }

    // Read invalid files
    dir = opendir(invalid_dir);
    if (dir != NULL) {
        while ((ent = readdir(dir)) != NULL && file_count < MAX_FILES) {
            if (strstr(ent->d_name, ".cpp") != NULL) {
                snprintf(path, MAX_PATH_LENGTH, "%s/%s", invalid_dir, ent->d_name);
                strncpy(test_files[file_count].path, path, MAX_PATH_LENGTH);
                test_files[file_count].expected_valid = 0;
                file_count++;
                total_invalid++;
            }
        }
        closedir(dir);
    }

    // Run tests
    int correct_valid = 0;
    int correct_invalid = 0;

    printf("Running tests...\n\n");
    printf("=== Valid Files ===\n");
    for (int i = 0; i < file_count; i++) {
        if (test_files[i].expected_valid) {
            int result = is_valid_oop_file(test_files[i].path);
            if (result == test_files[i].expected_valid) {
                correct_valid++;
            }
            printf("Testing %s: %s (Expected: Valid)\n", 
                   test_files[i].path,
                   result ? "Valid" : "Invalid");
        }
    }

    printf("\n=== Invalid Files ===\n");
    for (int i = 0; i < file_count; i++) {
        if (!test_files[i].expected_valid) {
            int result = is_valid_oop_file(test_files[i].path);
            if (result == test_files[i].expected_valid) {
                correct_invalid++;
            }
            printf("Testing %s: %s (Expected: Invalid)\n", 
                   test_files[i].path,
                   result ? "Valid" : "Invalid");
        }
    }

    print_results(file_count, correct_valid, correct_invalid, total_valid, total_invalid);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <valid_dir> <invalid_dir>\n", argv[0]);
        return 1;
    }

    run_tests(argv[1], argv[2]);
    return 0;
}