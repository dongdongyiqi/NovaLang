#pragma once
#include "nova_all.h"

using Env = std::unordered_map<std::string, int>;

struct Expr {
    virtual ~Expr() = default;
    virtual int eval(Env& env) const = 0;
};

struct NumberExpr : Expr {
    int val;
    explicit NumberExpr(int v) : val(v) {}
    int eval(Env&) const override { return val; }
};

struct VarExpr : Expr {
    std::string name;
    explicit VarExpr(std::string n) : name(std::move(n)) {}
    int eval(Env& env) const override { return env[name]; }
};

struct BinaryExpr : Expr {
    char op;
    std::unique_ptr<Expr> left, right;
    BinaryExpr(char o, std::unique_ptr<Expr> l, std::unique_ptr<Expr> r)
        : op(o), left(std::move(l)), right(std::move(r)) {}

    int eval(Env& env) const override {
        int l = left->eval(env), r = right->eval(env);
        if (op == '+') return l + r;
        if (op == '-') return l - r;
        if (op == '*') return l * r;
        if (op == '/') return r != 0 ? l / r : 0;
        return 0;
    }
};
