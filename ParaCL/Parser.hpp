#pragma once

#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "Node.hpp"
#include <set>

#define A std::cout<<"A"<<std::endl;
#define B(a) std::cout<<a<<std::endl;

class PureFile
{
    char * buffer = nullptr;
    int size = 0;
    int it = 0;

    void convert(int fd)
    {
        struct stat f_stat;
        fstat(fd, &f_stat);
        size = f_stat.st_size;
        buffer = new char[size];
        ::read(fd, buffer, size);
        ::close(fd);
    }

public:
    PureFile(char const * filename)
    {
        int fd = open(filename, O_RDWR);
        if (fd <= 0) return;
        convert(fd);
    }
    int GetIt() const { return it; }
    int SetIt(int i) { it = i; }
    bool isEnd() { return it >= size; }
    bool isBegin() { return !it; }
    void out() { std::cout << buffer << std::endl; }
    ~PureFile() { delete[] buffer; }

    PureFile & operator++() { ++it; }
    char operator*() const { return *(buffer + it); }
    PureFile & operator+(int i) { it += i; }
    PureFile & operator--() { --it; }
    PureFile & operator-(int i) { it -= i; }

};


class Parser
{
    PureFile f_;
    Scope * currentScope = nullptr;
    std::set<char> availableOps{'=', '<', '>', '?', '+', '-'};

    bool Find(char const * what, PureFile & where);

    Scope * GetScope(PureFile &f);
    Node * GetIf(PureFile & f) {};
    Node * GetWhile(PureFile & f) {};
    Node * GetDecl(PureFile & f);
    Node * GetNum(PureFile & f);
    Node * GetOperation(PureFile & f);
    Ops GetOp(PureFile & f);

    void skipSpace(PureFile & f)
    {
        while (*f == ' ' || *f == '\n' || *f == '\t')
            ++f;   
    }

public:
    Parser(char const * filename) : f_(PureFile{filename})
    {
        while(!f_.isEnd())
            currentScope = GetScope(f_);
    }
    void exec() { if (currentScope) currentScope->calc(); }

};

Node * Parser::GetOperation(PureFile & f)
{
    skipSpace(f);
    Node * lft = GetDecl(f); 
    if (!lft) lft = GetNum(f);

    skipSpace(f);
    if (*f == ')' || *f == ';' || *f == '}' || f.isEnd())
    { if (*f == ';') ++f; return lft;}
    
    Ops op = GetOp(f);
    Node * rgh = GetOperation(f);

    return new Op{lft, op, rgh};   
}

Node * Parser::GetDecl(PureFile & f)
{
    std::string tmp{};
    skipSpace(f);
    int const it = f.GetIt();
    
    while(isalpha(*f))
    {
        tmp+=*f;
        ++f;
    }
    if (tmp.empty() || tmp == "print")
    {
        f.SetIt(it);
        return nullptr;
    }

    return (*currentScope)[tmp];
}

Ops Parser::GetOp(PureFile & f)
{
    skipSpace(f);
    Ops op;
    if (Find("print ", f))
        return Ops::StdOut;
    if (Find("?", f))
        return Ops::StdIn;
    if (Find(">", f))
        return Ops::Greater;
    if (Find("<", f))
        return Ops::Less;
    if (Find("=", f))
        return Ops::Assign;
    if (Find("+", f))
        return Ops::Plus;
    if (Find("-", f))
        return Ops::Minus;
}

Node * Parser::GetNum(PureFile & f)
{
    int num = 0;
    bool fl = false;
    skipSpace(f);
    while(isdigit(*f))
    {
        num = num * 10 + ((*f) - '0');
        ++f;
        fl = true;
    }

    if (!fl) return nullptr;
    return new Value{num};
}

bool Parser::Find(char const * what, PureFile & where)
{
    skipSpace(where);
    int It = where.GetIt();
    int size = strlen(what);
    for (int i = 0; i < size; ++i, ++where)
        if (*where != what[i])
        { where.SetIt(It); return false; }
    return true;
}

Scope * Parser::GetScope(PureFile & f)
{
    skipSpace(f);
    if (*f != '{' && currentScope)
        return nullptr;
    if (*f == '{' && currentScope)
        ++f; // skip {
    currentScope = new Scope{currentScope};
    
    while(*f != '}' && !f.isEnd())
    {
        Scope * newS = GetScope(f);
        if (newS)
        {
            currentScope->addBranch(newS);
            continue;
        }
        Node * tmp = GetOperation(f);
        if (tmp)
            currentScope->addBranch(tmp);
    }
    skipSpace(f);    
    if (*f == '}')
        ++f;
    Scope * tmp = currentScope;
    currentScope = currentScope->resetScope();
    return tmp;
}
