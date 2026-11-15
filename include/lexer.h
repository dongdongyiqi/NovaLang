#pragma once
#include "nova_all.h"

enum class TokenType {
    LET, PRINT, IF, ELSE, WHILE,
    IDENTIFIER, NUMBER, STRING, // <-- 新增 STRING
    PLUS, MINUS, MUL, DIV, ASSIGN,
    EQ, NEQ, LT, GT, LE, GE,
    LPAREN, RPAREN, LBRACE, RBRACE, SEMICOLON, END
};

struct Token {
    TokenType type;
    std::string text;
};

class Lexer {
private:
    std::string src;
    size_t pos = 0;

    inline char peek() const { return pos < src.size() ? src[pos] : '\0'; }
    inline char peekNext() const { return pos + 1 < src.size() ? src[pos + 1] : '\0'; }
    inline char advance() { return pos < src.size() ? src[pos++] : '\0'; }

public:
    explicit Lexer(std::string source);
    std::vector<Token> tokenize();
};
