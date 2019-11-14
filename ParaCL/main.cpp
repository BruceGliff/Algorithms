#include <iostream>
#include "Node.hpp"
#include "Parser.hpp"


int main()
{
    Parser p{"main.pcl"};
    p.exec();   

    // Scope * curr = new Scope{nullptr};

    // std::string a{"a"}, b{"b"}, c{"c"};

    // Node * de = new Op{(*curr)[c], Ops::Assign, new Value{13}};
    // curr->addBranch(de);
    // Node * op1 = new Op{(*curr)[b], Ops::Assign, (*curr)[c]};
    // Node * op2 = new Op{(*curr)[a], Ops::Assign, op1};
    // curr->addBranch(op2);
    // curr->addBranch(new Op{nullptr, Ops::StdOut, (*curr)[a]});
    // curr->calc();
}