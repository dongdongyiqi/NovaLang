#include "parser.h"

Parser::Parser(std::vector<Token> t) : tokens(std::move(t)) {}

bool Parser::match(TokenType type) {
    if (peek().type == type) {
        advance();
        return true;
    }
    return false;
}

std::unique_ptr<Expr> Parser::parsePrimary() {
    if (peek().type == TokenType::NUMBER) {
        return std::make_unique<NumberExpr>(std::stoi(advance().text));
    }
    if (peek().type == TokenType::STRING) {
        return std::make_unique<StringExpr>(advance().text);
    }
    if (peek().type == TokenType::IDENTIFIER) {
        return std::make_unique<VarExpr>(advance().text);
    }
    if (match(TokenType::LPAREN)) {
        auto expr = parseComparison();
        match(TokenType::RPAREN);
        return expr;
    }
    return nullptr;
}


std::unique_ptr<Expr> Parser::parseMultiplication() {
    auto left = parsePrimary();
    while (peek().type == TokenType::MUL || peek().type == TokenType::DIV) {
        std::string op = advance().text;
        left = std::make_unique<BinaryExpr>(op, std::move(left), parsePrimary());
    }
    return left;
}

std::unique_ptr<Expr> Parser::parseAddition() {
    auto left = parseMultiplication();
    while (peek().type == TokenType::PLUS || peek().type == TokenType::MINUS) {
        std::string op = advance().text;
        left = std::make_unique<BinaryExpr>(op, std::move(left), parseMultiplication());
    }
    return left;
}

std::unique_ptr<Expr> Parser::parseComparison() {
    auto left = parseAddition();
    while (peek().type == TokenType::EQ || peek().type == TokenType::NEQ ||
           peek().type == TokenType::LT || peek().type == TokenType::GT ||
           peek().type == TokenType::LE || peek().type == TokenType::GE) {
        std::string op = advance().text;
        left = std::make_unique<BinaryExpr>(op, std::move(left), parseAddition());
    }
    return left;
}

std::unique_ptr<Stmt> Parser::parseBlock() {
    auto block = std::make_unique<BlockStmt>();
    while (peek().type != TokenType::RBRACE && peek().type != TokenType::END) {
        block->stmts.push_back(parseStatement());
    }
    match(TokenType::RBRACE);
    return block;
}

std::unique_ptr<Stmt> Parser::parseStatement() {
    if (match(TokenType::LET)) {
        std::string name = advance().text;
        match(TokenType::ASSIGN);
        auto expr = parseComparison();
        match(TokenType::SEMICOLON);
        return std::make_unique<LetStmt>(name, std::move(expr));
    }
    if (match(TokenType::PRINT)) {
        auto expr = parseComparison();
        match(TokenType::SEMICOLON);
        return std::make_unique<PrintStmt>(std::move(expr));
    }
    if (match(TokenType::IF)) {
        match(TokenType::LPAREN);
        auto cond = parseComparison();
        match(TokenType::RPAREN);
        match(TokenType::LBRACE);
        auto thenBranch = parseBlock();
        std::unique_ptr<Stmt> elseBranch = nullptr;
        if (match(TokenType::ELSE)) {
            match(TokenType::LBRACE);
            elseBranch = parseBlock();
        }
        return std::make_unique<IfStmt>(std::move(cond), std::move(thenBranch), std::move(elseBranch));
    }
    if (match(TokenType::WHILE)) {
        match(TokenType::LPAREN);
        auto cond = parseComparison();
        match(TokenType::RPAREN);
        match(TokenType::LBRACE);
        auto body = parseBlock();
        return std::make_unique<WhileStmt>(std::move(cond), std::move(body));
    }
    // 处理变量重新赋值，例如：sum = sum + i;
    if (peek().type == TokenType::IDENTIFIER) {
        std::string name = advance().text;
        match(TokenType::ASSIGN);
        auto expr = parseComparison();
        match(TokenType::SEMICOLON);
        return std::make_unique<AssignStmt>(name, std::move(expr));
    }
    advance();
    return nullptr;
}

std::vector<std::unique_ptr<Stmt>> Parser::parseProgram() {
    std::vector<std::unique_ptr<Stmt>> program;
    while (peek().type != TokenType::END) {
        auto stmt = parseStatement();
        if (stmt) program.push_back(std::move(stmt));
    }
    return program;
}
