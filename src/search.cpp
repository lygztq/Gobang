#include "search.h"

bool comp(node n1, node n2)
{
	return n1.value > n2.value;
}

std::vector<node> search_tree::gen_search_node(board &b)
{
	fast_evaluator evalutor;
	std::vector<node> nodes;
	for(int i=0;i<BOARD_SIZE;++i)
		for(int j=0;j<BOARD_SIZE;++j)
		{
			if(b.board_look[i][j]==NONE and b.is_in_consideration(i,j))
			{
				int value = evalutor.point_evaluate(b,i,j);
				node new_item(i,j,value);
				nodes.push_back(new_item);
			}
		}

	std::sort(nodes.begin(), nodes.end(),comp);

	// for test
	printf("the candidates: ");
	for(int i=0;i<(int)nodes.size();++i)
	{
		if(i>=10) break;
		printf("(%c, %d, %d) -> ", nodes[i].x + 'a', nodes[i].y+1, nodes[i].value);
	}
	printf("\n");

	return nodes;
}