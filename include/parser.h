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

    std::unique_ptr<Expr> parsePrimary();
    std::unique_ptr<Expr> parseTerm();
    std::unique_ptr<Expr> parseExpr();

public:
    explicit Parser(std::vector<Token> t);
    void run(Env& env);
};
