#pragma once


#include <llvm/ADT/APFloat.h>
#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>


#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <typeinfo>

class Scope;
void InitModule(Scope *begin);

class Node
{
public:
    virtual int calc() = 0;
    virtual void dump() const = 0;
    virtual llvm::Value *codegen() = 0;
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
    llvm::Value *codegen() override;
    ~Value();
};

class Decl final : public Node
{
    int val;
    llvm::Value *v;
    llvm::Value *ItSelf{nullptr};
public:
    Decl() = default;
    RType calc() override;
    void dump() const override;
    llvm::Value *codegen() override;
    void SetValue(int Val);
    void SetValue(llvm::Value* v_in) {v = v_in;}
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
    llvm::Value *codegen() override;
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
    llvm::Value *codegen() override;
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
    llvm::Value *codegen() override;
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
    llvm::Value *codegen() override;
    ~If();
};
