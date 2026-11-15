#include "lexer.h"

Lexer::Lexer(std::string source) : src(std::move(source)) {}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    while (pos < src.size()) {
        char c = peek();
        if (std::isspace(c)) {
            advance();
        } else if (c == '/' && peekNext() == '/') {
            while (peek() != '\n' && peek() != '\0') advance();
        } else if (c == '"') {
            // 【新增】读取双引号里的字符串内容
            advance(); // 吃掉开头的 '"'
            std::string str;
            while (peek() != '"' && peek() != '\0') {
                str += advance();
            }
            if (peek() == '"') advance(); // 吃掉结尾的 '"'
            tokens.push_back({TokenType::STRING, str});
        } else if (std::isdigit(c)) {
            std::string num;
            while (std::isdigit(peek())) num += advance();
            tokens.push_back({TokenType::NUMBER, num});
        } else if (std::isalpha(c) || c == '_') {
            std::string id;
            while (std::isalnum(peek()) || peek() == '_') id += advance();
            if (id == "let") tokens.push_back({TokenType::LET, id});
            else if (id == "print") tokens.push_back({TokenType::PRINT, id});
            else if (id == "if") tokens.push_back({TokenType::IF, id});
            else if (id == "else") tokens.push_back({TokenType::ELSE, id});
            else if (id == "while") tokens.push_back({TokenType::WHILE, id});
            else tokens.push_back({TokenType::IDENTIFIER, id});
        } else {
            advance();
            switch (c) {
                case '+': tokens.push_back({TokenType::PLUS, "+"}); break;
                case '-': tokens.push_back({TokenType::MINUS, "-"}); break;
                case '*': tokens.push_back({TokenType::MUL, "*"}); break;
                case '/': tokens.push_back({TokenType::DIV, "/"}); break;
                case '(': tokens.push_back({TokenType::LPAREN, "("}); break;
                case ')': tokens.push_back({TokenType::RPAREN, ")"}); break;
                case '{': tokens.push_back({TokenType::LBRACE, "{"}); break;
                case '}': tokens.push_back({TokenType::RBRACE, "}"}); break;
                case ';': tokens.push_back({TokenType::SEMICOLON, ";"}); break;
                case '=':
                    if (peek() == '=') { advance(); tokens.push_back({TokenType::EQ, "=="}); }
                    else tokens.push_back({TokenType::ASSIGN, "="});
                    break;
                case '!':
                    if (peek() == '=') { advance(); tokens.push_back({TokenType::NEQ, "!="}); }
                    break;
                case '<':
                    if (peek() == '=') { advance(); tokens.push_back({TokenType::LE, "<="}); }
                    else tokens.push_back({TokenType::LT, "<"});
                    break;
                case '>':
                    if (peek() == '=') { advance(); tokens.push_back({TokenType::GE, ">="}); }
                    else tokens.push_back({TokenType::GT, ">"});
                    break;
                default: std::cerr << "[词法错误] 未知字符: " << c << "\n"; break;
            }
        }
    }
    tokens.push_back({TokenType::END, ""});
    return tokens;
}
