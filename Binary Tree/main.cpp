
#include "Node.h"

int main()
{
	{
		std::vector<int> vec = {10};//, 5, 9, 1, 0};
		BinTree::Tree<int> t{vec};
		t.print();
	}

	return 0;
}
