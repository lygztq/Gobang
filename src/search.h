#ifndef SEARCH_H
#define SEARCH_H

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include "constant.h"
#include "board.h"
#include "evaluate.h"

// extern
class board;
class fast_evaluator;
class evaluator;

struct node
{
	int id;
	int x;
	int y;
	int value;

	node(int i, int v)
	{
		id = i;
		get_index(id,x,y);
		value = v;
	}

	node(int n_x,int n_y,int v)
	{
		x = n_x; y = n_y;
		get_id(x,y,id);
		value = v;
	}
};

class search_tree
{
private:
	int search_depth;
public:
	search_tree(int depth = 5){search_depth = depth;}
	std::vector<node> gen_search_node(board &b);
};

#endif