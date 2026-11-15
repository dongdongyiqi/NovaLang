# Nova 编程语言 (`.nv`)

[English](README.md) | 简体中文

一门使用现代 **C++20** 从零构建的轻量级、语法简洁的编程语言解释器。

## ✨ 核心特性
- **变量与数据类型**：原生支持整数与字符串动态类型（`let x = 10;`、`let name = "Nova";`）。
- **表达式计算**：支持完整四则运算（`+`、`-`、`*`、`/`）、括号优先级 `( )`、字符串拼接以及比较运算符（`==`、`!=`、`<`、`>`、`<=`、`>=`）。
- **流程控制**：支持 `if` / `else` 条件分支与 `while` 循环结构。
- **脚本文件运行**：支持直接读取并执行外部 `.nv` 源码文件。

## 🚀 快速开始

### 1. 使用 CMake 编译
```bash
mkdir build && cd build
cmake ..
cmake --build .
```

### 2. 编写 Nova 程序 (`hello.nv`)
```javascript
// 计算 1 到 10 的累加和
let sum = 0;
let i = 1;

while (i <= 10) {
    sum = sum + i;
    i = i + 1;
}

print "Sum is:";
print sum;
```

### 3. 运行程序
```bash
./nova ../hello.nv
```

## 📁 项目结构
- `include/` — 头文件目录（`nova_all.h`、`lexer.h`、`ast.h`、`parser.h`）
- `src/` — 核心源码实现（`lexer.cpp`、`parser.cpp`、`main.cpp`）
- `hello.nv` — Nova 示例代码文件

## 📄 开源协议
本项目基于 [MIT License](LICENSE) 开源。
