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
├── test/           # Test files
├── oop_valid/      # Valid OOP test cases
├── oop_invalid/    # Invalid OOP test cases
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
- `test`: Basic compiler test
- `oop`: OOP analyzer
- `oop2`: Alternative OOP analyzer
- `unit_test`: Unit tests
- `test_runner`: Comprehensive test runner

## Running Tests
The project includes several test options:

1. Comprehensive OOP test suite (provides Accuracy, Precision, Recall stats):
```bash
make oop_test
```

2. Unit tests:
```bash
make unit_test
```

3. Basic compiler test:
```bash
make test
```

4. OOP analysis test:
```bash
make oop
```

5. Alternative OOP analysis:
```bash
make pp
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
