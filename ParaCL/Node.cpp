#include "Node.hpp"

Node::~Node() {}
// NUMBER
RType Value::calc()
{
    return val;
}
void Value::dump() const
{
    std::cout << "Node Value: " << val << std::endl;
}
Value::~Value() {}

RType Decl::calc()
{
    return val;
}
void Decl::dump() const
{
    std::cout << "Node Decl: " << val << std::endl;
}
void Decl::SetValue(int Val)
{
   val = Val;
}
Decl::~Decl() {}

// SCOPE

RType Scope::calc()
{
    for (auto x : branches)
        x->calc();

    return 0;
}
void Scope::dump() const
{
    std::cout << "Node Scope: " << std::endl;
    for (auto const x : branches)
        x->dump();
}
Scope * Scope::resetScope() const { return prev_scope; }
void Scope::addBranch(Node * branch)
{
    branches.push_back(branch);
}

Node * Scope::operator[](std::string const & var_name)
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
Node * Scope::existsLater(std::string const & var_name)
{
    Node * f = nullptr;
    if (memory.find(var_name) != memory.end())
        return memory[var_name];
    if (prev_scope && !f)
        f = prev_scope->existsLater(var_name);

    return f;
}

Scope::~Scope()
{
    for (auto x : branches)
        delete x;

    for (auto x : memory)
        delete x.second;
}

RType Op::calc()
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
    case Ops::GreaterEq:
        return left->calc() >= right->calc();
        break;
    case Ops::LessEq:
        return left->calc() <= right->calc();
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
    case Ops::NotEqual:
        return (left->calc() != right->calc());
        break;
    case Ops::Not:
        return !static_cast<bool>(right->calc());
        break;
    case Ops::And:
        return left->calc() && right->calc();
        break;
    case Ops::Or:
        return left->calc() || right->calc();
        break;
    case Ops::Div:
        val = right->calc();
        if (!val)
        {
            std::cerr << "Division by zero!" << std::endl;
            exit(1);
        }
        return left->calc() / right->calc();
        break;
    case Ops::Mul:
        return left->calc() * right->calc();
        break;
    case Ops::Mod:
        return left->calc() % right->calc();
        break;
    default:
        return 999;
    }

    return 998;
}
void Op::dump() const
{
    std::cout << "Node Op: ";
    int val = 0;
    switch (op)
    {
    case Ops::Plus:
        std::cout << "Plus" << std::endl;
        if (left == nullptr)
            right->dump();
        else 
        {
            left->dump();
            right->dump();
        }
        break;
    case Ops::Minus:
        std::cout << "Minus" << std::endl;
        if (left == nullptr)
            right->dump();
        else 
        {
            left->dump();
            right->dump();
        }
        break;
    case Ops::Greater:
        std::cout << "Greater" << std::endl;
        left->dump();
        right->dump();
        break;
    case Ops::Less:
        std::cout << "Less" << std::endl;
        left->dump();
        right->dump();
        break;
    case Ops::Assign:
        std::cout << "Assign" << std::endl;
        left->dump();
        right->dump();
        break;
    case Ops::StdOut:
        std::cout << "StdOut" << std::endl;
        right->dump();
        break;
    case Ops::StdIn:
        std::cout << "StdIn" << std::endl;
        break;
    case Ops::Equal:
        std::cout << "Equal" << std::endl;
        left->dump();
        right->dump();
        break;
    }
}
Op::~Op() 
{ 
    if (left && typeid(Decl) != typeid(*left))
        delete left;
    if (right && typeid(Decl) != typeid(*right))
        delete right;
}


RType While::calc()
{
    while(op->calc())
        scope->calc();

    return 0;
}
void While::dump() const
{
    std::cout << "Node While " << std::endl;
    scope->dump();
}
While::~While()
{
    if (op && typeid(Decl) != typeid(*op))
        delete op;
    delete scope;
}

RType If::calc()
{
    if (op->calc())
        scope->calc();

    return 0;
}
void If::dump() const
{
    std::cout << "Node If " << std::endl;
    scope->dump();
}
If::~If() 
{ 
    if (op && typeid(Decl) != typeid(*op))
        delete op;
    delete scope;
}