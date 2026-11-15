cmake_minimum_required(VERSION 3.20)
project(NovaLang)

# 指定使用 C++20 标准（也可改为 17）
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 将 include 目录加入头文件搜索路径，这样 #include "nova_all.h" 就能直接找到
include_directories(include)

# 生成名为 nova 的可执行文件，包含所有 .cpp 源文件
add_executable(nova
        src/main.cpp
        src/lexer.cpp
        src/parser.cpp
)
