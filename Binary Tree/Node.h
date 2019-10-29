#pragma once

#include <iostream>
#include <vector>

namespace BinTree
{

template <typename T>
class Node
{public:
	T key_;
	unsigned int height_;
	Node * left_;
	Node * right_;

	typename std::vector<Node*>::iterator it;

	/* HEIGHT WORK */
	unsigned int height(Node * p);
	int bfactor(Node * p);
	void fixheight(Node* p);


	/* BALANCED */
	Node * rotateright(Node * p);
	Node * rotateleft(Node * q);
	Node * balance(Node * p);

	/* FIND MINIMAL NODES */
	Node * findmin(Node * p);

public:
	Node(T key);

	auto GetIndex() const
	{ return it; }

	/*  PRINT NODES  */
	void print() const;

	/* ADDED NODES */
	Node * insert(Node * p, const T k, Node * out);

	/* DELETED NODES */
	Node * removemin(Node * p);
	Node * remove(Node * p, const T k, Node * out);


};



template<typename T>
class Tree
{
	std::vector<Node<T>*> NodesArray_;
	Node<T> * Root = nullptr;


public:
	Tree(const std::vector<T> & points);
	Tree() = default;

	~Tree();

	Tree & insert(const T & NodeValue);
	void erase(const T & NodeValue);
	void print() const;

	// bool isContain(const T & NodeValue) const;



};



}

#include "Node.hpp"

#include "Tree.hpp"