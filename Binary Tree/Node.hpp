namespace BinTree
{

template <typename T>
Node<T>::Node(T key) :
	key_(key),
	height_(1),
	left_(nullptr),
	right_(nullptr)
{}

/* HEIGHT WORK */
template <typename T>
unsigned int Node<T>::height(Node * p)
{
	return p ? p->height_ : 0;
}

template <typename T>
int Node<T>::bfactor(Node * p)
{
	return height(p->right_) - height(p->left_);
}

template <typename T>
void Node<T>::fixheight(Node* p)
{
	unsigned int hl = height(p->left_);
	unsigned int hr = height(p->right_);
	p->height_ = (hl > hr ? hl : hr) + 1;
}

/* BALANCED */
template <typename T>
Node<T> * Node<T>::rotateright(Node * p)
{
	Node * q = p->left_;
	p->left_ = q->right_;
	q->right_ = p;
	fixheight(p);
	fixheight(q);
	return q;
}

template <typename T>
Node<T> * Node<T>::rotateleft(Node * q)
{
	Node * p = q->right_;
	q->right_ = p->left_;
	p->left_ = q;
	fixheight(q);
	fixheight(p);
	return p;
}

template <typename T>
Node<T> * Node<T>::balance(Node * p)
{
	fixheight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right_) < 0)
			p->right_ = rotateright(p->right_);
		return rotateleft(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left_) > 0)
			p->left_ = rotateleft(p->left_);
		return rotateright(p);
	}
	return p;
}

/* FIND MINIMAL NODES */
template <typename T>
Node<T> * Node<T>::findmin(Node * p)
{
	return p->left_ ? findmin(p->left_) : p;
}

/*  PRINT NODES  */
template <typename T>
void Node<T>::print() const
{
	if (left_)
		left_->print();
	std::cout << key_ << '\n';
	if (right_)
		right_->print();
}

/* ADDED NODES */
template <typename T>
Node<T> * Node<T>::insert(Node<T> * p, const T k, Node<T> * out)
{
	if (!p) 
	{
		out = new Node<T>(k);
		return out;
	}
	if (k < p->key_)
		p->left_ = insert(p->left_, k, out);
	else
		p->right_ = insert(p->right_, k, out);
	return balance(p);
}

/* DELETED NODES */
template <typename T>
Node<T> * Node<T>::removemin(Node<T> * p)
{
	if (p->left_ == 0)
		return p->right_;
	p->left_ = removemin(p->left_);
	return balance(p);
}

template <typename T>
Node<T> * Node<T>::remove(Node<T> * p, const T k, Node<T> * out)
{
	if (!p) return 0;
	if (k < p->key_)
		p->left_ = remove(p->left_, k);
	else if (k > p->key_)
		p->right_ = remove(p->right_, k);
	else
	{
		Node<T> * q = p->left_;
		Node<T> * r = p->right_;

		out = p;

		if (!r) return q;
		Node<T> * min = findmin(r);
		min->right_ = removemin(r);
		min->left_ = q;
		return balance(min);
	}
	return balance(p);
}

}
