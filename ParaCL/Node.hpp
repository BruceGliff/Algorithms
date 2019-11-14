#pragma once
#include <vector>
#include <map>
#include <string>
#include <iostream>

class Node
{
    Node * scope;
public:
    virtual int calc() = 0;
    virtual ~Node() = 0;
};
Node::~Node() {}

using tmp = int;

// NUMBER
class Value final : public Node
{
    int val;

public: 
    Value(int v) : val(v) {}
    tmp calc() override
    {
        return val;
    }
};

class Decl final : public Node
{
    int val;

public:
    Decl() = default;
    tmp calc() override
    {
        return val;
    }

    void SetValue(int Val)
    {
       val = Val;
    }
};

// SCOPE
class Scope final : public Node
{
    std::vector<Node *> branches;
    std::map<std::string, Node *> memory;

    Scope * prev_scope;

public:
    Scope(Scope * prev) : prev_scope(prev) {}
    tmp calc() override
    {
        for (auto x : branches)
            x->calc();
    }
    Scope * resetScope() { return prev_scope; }
    void addBranch(Node * branch)
    {
        branches.push_back(branch);
    }

    Node * operator[](std::string const & var_name)
    {
        if (memory.find(var_name) == memory.end())
        {
            if (!prev_scope)
            {
                Decl * dec = new Decl;
                memory[var_name] = dec;
                return dec;
            }
            if (prev_scope->memory.find(var_name) == prev_scope->memory.end())
            {
                Decl * dec = new Decl;
                memory[var_name] = dec;
                return dec;
            }
            else
                return prev_scope->memory[var_name];
        }
        return memory[var_name];
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
    StdIn
};


class Op : public Node
{
protected:
    Node * right;
    Node * left;
    Ops op;

public:
    Op(Node * l, Ops o, Node * r) : left(l), right(r), op(o) {}
    tmp calc() override
    {
        int val = 0;
        switch (op)
        {
        case Ops::Plus:
            return left->calc() + right->calc();
            break;
        case Ops::Minus:
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
            return val; // BE CAREFUL
            break;
        case Ops::StdOut:
            std::cout << right->calc() << std::endl;
            break;
        case Ops::StdIn:
            std::cin >> val;
            return val;
            break;
        }
    }
};




// WHILE
class While : public Node
{
    Node * op;
    Node * scope;

public:
    While(Node * o, Node * s) : op(o), scope(s) {}
    tmp calc() override
    {
        while(op->calc())
            scope->calc();
    }
};






