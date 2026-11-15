#include "nova_all.h"
#include "lexer.h"
#include "parser.h"

int main() {
    std::string novaCode = R"(
        let x = 10;
        let y = 25;
        let result = x + y * 2 - 5;
        print result;
    )";

    Lexer lexer(novaCode);
    auto tokens = lexer.tokenize();

    Env memory;
    Parser parser(std::move(tokens));
    parser.run(memory);

    return 0;
}
