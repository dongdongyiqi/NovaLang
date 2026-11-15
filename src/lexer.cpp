#include "lexer.h"

Lexer::Lexer(std::string source) : src(std::move(source)) {}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    while (pos < src.size()) {
        char c = peek();
        if (std::isspace(c)) {
            advance();
        } else if (std::isdigit(c)) {
            std::string num;
            while (std::isdigit(peek())) num += advance();
            tokens.push_back({TokenType::NUMBER, num});
        } else if (std::isalpha(c)) {
            std::string id;
            while (std::isalnum(peek())) id += advance();
            if (id == "let") tokens.push_back({TokenType::LET, id});
            else if (id == "print") tokens.push_back({TokenType::PRINT, id});
            else tokens.push_back({TokenType::IDENTIFIER, id});
        } else {
            advance();
            switch (c) {
                case '+': tokens.push_back({TokenType::PLUS, "+"}); break;
                case '-': tokens.push_back({TokenType::MINUS, "-"}); break;
                case '*': tokens.push_back({TokenType::MUL, "*"}); break;
                case '/': tokens.push_back({TokenType::DIV, "/"}); break;
                case '=': tokens.push_back({TokenType::ASSIGN, "="}); break;
                case ';': tokens.push_back({TokenType::SEMICOLON, ";"}); break;
                default: std::cerr << "未知字符: " << c << "\n"; break;
            }
        }
    }
    tokens.push_back({TokenType::END, ""});
    return tokens;
}
