# compiler_project
A lightweight C++ code analyzer that determines whether a given codebase uses object-oriented programming principles.

## Requirements
- GCC compiler (tested with gcc)
- Make build system
- C standard library
- POSIX-compliant operating system (for directory operations)

## Project Structure
```
.
├── build/           # Compiled binaries
├── libs/           # Third-party libraries
├── compiler.c      # Main compiler implementation
├── compiler.h      # Header file
├── test_runner.c   # Test runner implementation
└── Makefile        # Build configuration
```

## Building the Project
To build the project, simply run:
```bash
make
```

This will create the following executables in the `build` directory:
- `unit_test`: Unit tests
- `test_runner`: Comprehensive test runner

## Running Tests
The project includes the following test options:

1. Comprehensive OOP test suite (provides Accuracy, Precision, Recall stats):
```bash
make oop_test
```

2. Unit tests:
```bash
make unit_test
```

## Cleaning Build Files
To remove all compiled binaries:
```bash
make clean
```

## Usage
The compiler analyzes C++ source files to determine if they follow object-oriented programming principles. It can be used in two ways:

1. Direct analysis of a single file:
```bash
./build/oop <path_to_cpp_file>
```

2. Batch analysis of multiple files:
```bash
./build/test_runner <valid_oop_dir> <invalid_oop_dir>
```

The test runner will provide detailed statistics about the analysis, including:
- Accuracy
- Precision
- Recall
- Valid/Invalid file detection rates
