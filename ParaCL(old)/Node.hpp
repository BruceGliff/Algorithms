#pragma once
#include <vector>
#include <map>
#include <string>
#include <iostream>

class Node
{
public:
    virtual int calc() = 0;
    virtual ~Node() = 0;
};
Node::~Node() {}

using RType = int;

// NUMBER
class Value final : public Node
{
    int val;

public: 
    Value(int v) : val(v) {}
    RType calc() override
    {
        return val;
    }
    ~Value() {}
};

class Decl final : public Node
{
    int val;
public:
    Decl() = default;
    RType calc() override
    {
        return val;
    }
    void SetValue(int Val)
    {
       val = Val;
    }
    ~Decl() {}
};

// SCOPE
class Scope final : public Node
{
    std::vector<Node *> branches;
    std::map<std::string, Node *> memory;

    Scope * prev_scope;

public:
    Scope(Scope * prev) : prev_scope(prev) {}
    RType calc() override
    {
        for (auto x : branches)
            x->calc();
    }
    Scope * resetScope() const { return prev_scope; }
    void addBranch(Node * branch)
    {
        branches.push_back(branch);
    }

    Node * operator[](std::string const & var_name)
    {
        Node * t = existsLater(var_name);
        if (t)
            return t;

        Node * dec = new Decl;
        memory[var_name] = dec;
        return dec;

        // if (memory.find(var_name) == memory.end())
        // {
        //     if (prev_scope)
        //         return prev_scope->operator[](var_name);
            
        //     Decl * dec = new Decl;
        //     memory[var_name] = dec;
        //     return dec;
        // }

        // return memory[var_name];
    }
    Node * existsLater(std::string const & var_name)
    {
        Node * f = nullptr;
        if (memory.find(var_name) != memory.end())
            return memory[var_name];
        if (prev_scope && !f)
            f = prev_scope->existsLater(var_name);

        return f;
    }

    ~Scope()
    {
        for (auto x : branches)
            delete x;

        for (auto x : memory)
            delete x.second;
    }
};

// OPERATIONS
enum class Ops
{
    Plus,
    Minus,
    Assign,
    Greater,
    Less,
    StdOut,
    StdIn,
    Equal,
    // Div,
    // Times
};


class Op final : public Node
{
    Node * right;
    Node * left;
    Ops op;

public:
    Op(Node * l, Ops o, Node * r) : left(l), right(r), op(o) {}
    RType calc() override
    {
        int val = 0;
        switch (op)
        {
        case Ops::Plus:
            if (left == nullptr)
                return 0 + right->calc();
            return left->calc() + right->calc();
            break;
        case Ops::Minus:
            if (left == nullptr)
                return 0 - right->calc();
            return left->calc() - right->calc();
            break;
        case Ops::Greater:
            return left->calc() > right->calc();
            break;
        case Ops::Less:
            return left->calc() < right->calc();
            break;
        case Ops::Assign:
            val = right->calc();
            static_cast<Decl * >(left)->SetValue(val);
            return val;
            break;
        case Ops::StdOut:
            std::cout << right->calc() << std::endl;
            break;
        case Ops::StdIn:
            std::cin >> val;
            return val;
            break;
        case Ops::Equal:
            return (left->calc() == right->calc());
            break;
        // Not available yet
        // case Ops::Div:
        //     return left->calc() / right->calc();
        //     break;
        // case Ops::Times:
        //     return left->calc() * right->calc();
        //     break;
        }
    }
    ~Op() 
    { 
        if (!dynamic_cast<Decl *>(right))
            delete right;
        if (!dynamic_cast<Decl *>(left))
            delete left; 
    }
};


// WHILE
class While final : public Node
{
    Node * op = nullptr;
    Node * scope = nullptr;

public:
    While(Node * o, Node * s) : op(o), scope(s) {}
    RType calc() override
    {
        while(op->calc())
            scope->calc();

        return 0;
    }
    ~While()
    {
        if (!dynamic_cast<Decl *>(op))
            delete op;
        delete scope;
    }
};

class If final : public Node
{
    Node * op;
    Node * scope;

public:
    If(Node * o, Node * s) : op(o), scope(s) {}
    RType calc() override
    {
        if (op->calc())
            scope->calc();

        return 0;
    }
    ~If() 
    { 
        if (!dynamic_cast<Decl *>(op))
            delete op;
        delete scope;
    }
};






