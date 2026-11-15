#include "nova_all.h"
#include "lexer.h"
#include "parser.h"

void runFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "错误: 找不到源码文件 '" << path << "'\n";
        return;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();

    Lexer lexer(buffer.str());
    auto tokens = lexer.tokenize();

    Parser parser(std::move(tokens));
    auto program = parser.parseProgram();

    Env memory;
    for (const auto& stmt : program) {
        stmt->exec(memory);
    }
}

int main(int argc, char* argv[]) {
    // 如果命令行传了文件名（如 ./nova test.nv）就运行指定文件，否则默认运行项目根目录的 hello.nv
    std::string scriptPath = (argc > 1) ? argv[1] : "../hello.nv";
    runFile(scriptPath);
    return 0;
}
