#include <iostream>
#include "Node.hpp"


int main()
{
    Node * root = new Scope;

    {
        std::map<std::string, Node *> m;


        std::string variable = "fst";
        int val = 12;
        
        if (m.find(variable) == m.end())
        {
            Node * dec = new Decl;
            m[variable] = dec;

        }        

        static_cast<Scope *>(root)->addBranch(new Op(m[variable], nullptr, Ops::StdIn));
       // static_cast<Scope *>(root)->addBranch(new Op(m[variable], new Value(val), Ops::Assign));
        static_cast<Scope *>(root)->addBranch(new Op(nullptr, m[variable], Ops::StdOut));

        root->calc();



    }
    


}