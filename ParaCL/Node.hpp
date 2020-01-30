#pragma once

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <typeinfo>

class Node
{
public:
    virtual int calc() = 0;
    virtual void dump() const = 0;
    virtual ~Node() = 0;
};

using RType = int;

// NUMBER
class Value final : public Node
{
    int val;

public: 
    Value(int v) : val(v) {}
    RType calc() override;
    void dump() const override;
    ~Value();
};

class Decl final : public Node
{
    int val;
public:
    Decl() = default;
    RType calc() override;
    void dump() const override;
    void SetValue(int Val);
    ~Decl();
};

// SCOPE
class Scope final : public Node
{
    std::vector<Node *> branches;
    std::map<std::string, Node *> memory;

    Scope * prev_scope;

public:
    Scope(Scope * prev) : prev_scope(prev) {}
    RType calc() override;
    void dump() const override;
    Scope * resetScope()const;
    void addBranch(Node * branch);

    Node * operator[](std::string const & var_name);
    Node * existsLater(std::string const & var_name);

    ~Scope();
};

// OPERATIONS
enum class Ops
{
    Plus,
    Minus,
    Assign, 
    Greater, 
    Less, 
    GreaterEq, 
    LessEq, 
    StdOut, 
    StdIn, 
    Equal, 
    NotEqual, 
    Div, 
    Mul, 
    Mod, 
    Not,
    And,
    Or
};


class Op final : public Node
{
    Node * right;
    Node * left;
    Ops op;

public:
    Op(Node * l, Ops o, Node * r) : left(l), right(r), op(o) {}
    RType calc() override;
    void dump() const override;
    ~Op();
};


// WHILE
class While final : public Node
{
    Node * op = nullptr;
    Node * scope = nullptr;

public:
    While(Node * o, Node * s) : op(o), scope(s) {}
    RType calc() override;
    void dump() const override;
    ~While();
};

class If final : public Node
{
    Node * op;
    Node * scope;

public:
    If(Node * o, Node * s) : op(o), scope(s) {}
    RType calc() override;
    void dump() const override;
    ~If();
};
