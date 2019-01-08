#pragma once
#include "B_Tree.h"
template<class T, class comparator, class printer>
class B_Tree_Paint: public B_Tree<T, comparator, printer>{
private:
	int row;
	int col;
	int node_width;
	int width;
};