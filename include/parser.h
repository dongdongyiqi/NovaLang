#pragma once
#include "nova_all.h"
#include "lexer.h"
#include "ast.h"

class Parser {
private:
    std::vector<Token> tokens;
    size_t pos = 0;

    inline const Token& peek() const { return tokens[pos]; }
    inline const Token& advance() { return tokens[pos++]; }
    bool match(TokenType type);

    // 表达式解析（按优先级从低到高）
    std::unique_ptr<Expr> parseComparison();
    std::unique_ptr<Expr> parseAddition();
    std::unique_ptr<Expr> parseMultiplication();
    std::unique_ptr<Expr> parsePrimary();

    // 语句解析
    std::unique_ptr<Stmt> parseStatement();
    std::unique_ptr<Stmt> parseBlock();

public:
    explicit Parser(std::vector<Token> t);
    std::vector<std::unique_ptr<Stmt>> parseProgram();
};
