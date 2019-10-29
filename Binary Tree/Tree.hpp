//#include "Node.h"

namespace BinTree
{

template<typename T>
Tree<T>::Tree(const std::vector<T> & points)
{
	for (auto const & point : points)
		insert(point);
}


template<typename T>
Tree<T>::~Tree<T>()
{
	for (auto & node : NodesArray_)
		{/*std::cout << node->key_;*/ delete node; }
}

template<typename T>
Tree<T> & Tree<T>::insert(const T & NodeValue)
{
	Node<T> * out = nullptr;
	Root = Root->insert(Root, NodeValue, out);
	std::cout << out;
	NodesArray_.push_back(out);
}

template<typename T>
void Tree<T>::erase(const T & NodeValue)
{
	Node<T> * out = nullptr;
	Root = Root->remove(Root, NodeValue, out);
	NodesArray_.erase(out->GetIndex());
	delete out;
}

template<typename T>
void Tree<T>::print() const
{
	Root->print();
}



}