# Nova Programming Language (`.nv`)

English | [简体中文](README_CN.md)

A lightweight, clean-syntax programming language interpreter built from scratch in modern **C++20**.

## ✨ Features
- **Variables & Types**: Dynamic support for integers and strings (`let x = 10;`, `let name = "Nova";`).
- **Expressions**: Full arithmetic operations (`+`, `-`, `*`, `/`), parentheses `( )`, string concatenation, and comparison operators (`==`, `!=`, `<`, `>`, `<=`, `>=`).
- **Control Flow**: Conditional branching (`if` / `else`) and `while` loops.
- **File Execution**: Directly runs external `.nv` source files.

## 🚀 Quick Start

### 1. Build with CMake
```bash
mkdir build && cd build
cmake ..
cmake --build .
```

### 2. Write a Nova Program (`hello.nv`)
```javascript
// Calculate the sum from 1 to 10
let sum = 0;
let i = 1;

while (i <= 10) {
    sum = sum + i;
    i = i + 1;
}

print "Sum is:";
print sum;
```

### 3. Run
```bash
./nova ../hello.nv
```

## 📁 Project Structure
- `include/` — Header files (`nova_all.h`, `lexer.h`, `ast.h`, `parser.h`)
- `src/` — Core implementation (`lexer.cpp`, `parser.cpp`, `main.cpp`)
- `hello.nv` — Sample Nova script

## 📄 License
This project is licensed under the [MIT License](LICENSE).
