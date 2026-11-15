#pragma once
#include "nova_all.h"
#include <variant>

// 【C++ 现代特性：std::variant】一个万能盒子，既能装整数 int，也能装字符串 std::string！
using Value = std::variant<int, std::string>;
using Env = std::unordered_map<std::string, Value>;

// 辅助函数：把 Value 转换成整数（用于条件判断和数学计算）
inline int asInt(const Value& v) {
    if (std::holds_alternative<int>(v)) return std::get<int>(v);
    return 0;
}

struct Expr {
    virtual ~Expr() = default;
    virtual Value eval(Env& env) const = 0;
};

struct NumberExpr : Expr {
    int val;
    explicit NumberExpr(int v) : val(v) {}
    Value eval(Env&) const override { return val; }
};

struct StringExpr : Expr {
    std::string val;
    explicit StringExpr(std::string v) : val(std::move(v)) {}
    Value eval(Env&) const override { return val; }
};

struct VarExpr : Expr {
    std::string name;
    explicit VarExpr(std::string n) : name(std::move(n)) {}
    Value eval(Env& env) const override {
        if (env.count(name)) return env[name];
        return 0;
    }
};

struct BinaryExpr : Expr {
    std::string op;
    std::unique_ptr<Expr> left, right;
    BinaryExpr(std::string o, std::unique_ptr<Expr> l, std::unique_ptr<Expr> r)
        : op(std::move(o)), left(std::move(l)), right(std::move(r)) {}

    Value eval(Env& env) const override {
        Value lv = left->eval(env);
        Value rv = right->eval(env);

        // 支持两个字符串用 '+' 拼接！例如 "Hello " + "Nova"
        if (op == "+" && std::holds_alternative<std::string>(lv) && std::holds_alternative<std::string>(rv)) {
            return std::get<std::string>(lv) + std::get<std::string>(rv);
        }

        int l = asInt(lv), r = asInt(rv);
        if (op == "+") return l + r;
        if (op == "-") return l - r;
        if (op == "*") return l * r;
        if (op == "/") return r != 0 ? l / r : 0;
        if (op == "==") return l == r ? 1 : 0;
        if (op == "!=") return l != r ? 1 : 0;
        if (op == "<")  return l < r ? 1 : 0;
        if (op == ">")  return l > r ? 1 : 0;
        if (op == "<=") return l <= r ? 1 : 0;
        if (op == ">=") return l >= r ? 1 : 0;
        return 0;
    }
};

struct Stmt {
    virtual ~Stmt() = default;
    virtual void exec(Env& env) const = 0;
};

struct LetStmt : Stmt {
    std::string name;
    std::unique_ptr<Expr> expr;
    LetStmt(std::string n, std::unique_ptr<Expr> e) : name(std::move(n)), expr(std::move(e)) {}
    void exec(Env& env) const override {
        if (expr) env[name] = expr->eval(env);
    }
};

struct AssignStmt : Stmt {
    std::string name;
    std::unique_ptr<Expr> expr;
    AssignStmt(std::string n, std::unique_ptr<Expr> e) : name(std::move(n)), expr(std::move(e)) {}
    void exec(Env& env) const override {
        if (expr) env[name] = expr->eval(env);
    }
};

struct PrintStmt : Stmt {
    std::unique_ptr<Expr> expr;
    explicit PrintStmt(std::unique_ptr<Expr> e) : expr(std::move(e)) {}
    void exec(Env& env) const override {
        if (!expr) {
            std::cerr << "[语法错误] print 语句缺少有效内容或分号！\n";
            return;
        }
        Value v = expr->eval(env);
        // 自动判断打印数字还是字符串
        if (std::holds_alternative<int>(v)) std::cout << std::get<int>(v) << "\n";
        else if (std::holds_alternative<std::string>(v)) std::cout << std::get<std::string>(v) << "\n";
    }
};

struct BlockStmt : Stmt {
    std::vector<std::unique_ptr<Stmt>> stmts;
    void exec(Env& env) const override {
        for (const auto& s : stmts) {
            if (s) s->exec(env);
        }
    }
};

struct IfStmt : Stmt {
    std::unique_ptr<Expr> cond;
    std::unique_ptr<Stmt> thenBranch, elseBranch;
    IfStmt(std::unique_ptr<Expr> c, std::unique_ptr<Stmt> t, std::unique_ptr<Stmt> e)
        : cond(std::move(c)), thenBranch(std::move(t)), elseBranch(std::move(e)) {}
    void exec(Env& env) const override {
        if (cond && asInt(cond->eval(env)) != 0) {
            if (thenBranch) thenBranch->exec(env);
        } else if (elseBranch) {
            elseBranch->exec(env);
        }
    }
};

struct WhileStmt : Stmt {
    std::unique_ptr<Expr> cond;
    std::unique_ptr<Stmt> body;
    WhileStmt(std::unique_ptr<Expr> c, std::unique_ptr<Stmt> b)
        : cond(std::move(c)), body(std::move(b)) {}
    void exec(Env& env) const override {
        while (cond && asInt(cond->eval(env)) != 0) {
            if (body) body->exec(env);
        }
    }
};
