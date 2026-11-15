#include "parser.h"

Parser::Parser(std::vector<Token> t) : tokens(std::move(t)) {}

std::unique_ptr<Expr> Parser::parsePrimary() {
    if (peek().type == TokenType::NUMBER) {
        return std::make_unique<NumberExpr>(std::stoi(advance().text));
    }
    if (peek().type == TokenType::IDENTIFIER) {
        return std::make_unique<VarExpr>(advance().text);
    }
    return nullptr;
}

std::unique_ptr<Expr> Parser::parseTerm() {
    auto left = parsePrimary();
    while (peek().type == TokenType::MUL || peek().type == TokenType::DIV) {
        char op = advance().text[0];
        left = std::make_unique<BinaryExpr>(op, std::move(left), parsePrimary());
    }
    return left;
}

std::unique_ptr<Expr> Parser::parseExpr() {
    auto left = parseTerm();
    while (peek().type == TokenType::PLUS || peek().type == TokenType::MINUS) {
        char op = advance().text[0];
        left = std::make_unique<BinaryExpr>(op, std::move(left), parseTerm());
    }
    return left;
}

void Parser::run(Env& env) {
    while (peek().type != TokenType::END) {
        if (peek().type == TokenType::LET) {
            advance();
            std::string name = advance().text;
            advance();
            auto expr = parseExpr();
            advance();
            env[name] = expr->eval(env);
        } else if (peek().type == TokenType::PRINT) {
            advance();
            auto expr = parseExpr();
            advance();
            std::cout << "[Nova 输出] >> " << expr->eval(env) << "\n";
        } else {
            advance();
        }
    }
}
