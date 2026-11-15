#pragma once
#include "nova_all.h"

enum class TokenType {
    LET, PRINT, IDENTIFIER, NUMBER,
    PLUS, MINUS, MUL, DIV, ASSIGN, SEMICOLON, END
};

struct Token {
    TokenType type;
    std::string text;
};

class Lexer {
private:
    std::string src;
    size_t pos = 0;

    // 内联函数通常直接写在头文件中
    inline char peek() const {
        return pos < src.size() ? src[pos] : '\0';
    }

    inline char advance() {
        return pos < src.size() ? src[pos++] : '\0';
    }

public:
    explicit Lexer(std::string source);
    std::vector<Token> tokenize();
};
