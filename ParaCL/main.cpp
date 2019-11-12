#include <iostream>
#include "Node.hpp"


int main()
{
    Node * root = new Scope{nullptr};

    {
        Scope * scope = static_cast<Scope *>(root);
        std::string s = "fst";
        scope->addBranch(new Op((*scope)[s], nullptr, Ops::StdIn));

        Scope * u = new Scope{scope};
        scope->addBranch(u);

        u->addBranch(new Op(nullptr, (*u)[s], Ops::StdOut));

        root->calc();



    }
    


}