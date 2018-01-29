#include "evaluate.h"

inline point_score evaluator::get_point_score(int stone_num, int blocked)
{
	if(blocked==2) return DOUBLE_BLOCKED;
	else if(stone_num==5) return FIVE;
	else if(blocked==1)
	{
		switch(stone_num)
		{
			case 1: return BLOCKED_ONE;
			case 2: return BLCOKED_TWO;
			case 3: return BLOCKED_THREE;
			case 4: return BLOCKED_FOUR;
			default: return WRONG;
		}
	}
	else if(blocked==0)
	{
		switch(stone_num)
		{
			case 1: return ONE;
			case 2: return TWO;
			case 3: return THREE;
			case 4: return FOUR;
			default: return WRONG;
		}
	}
	else return WRONG;
}

score evaluator::point_evaluate(board &b, int x, int y, stone curr_color)
{
	if(b.board_look[x][y]!=NONE) fprintf(stderr, "Invalid evaluation! This vertex has stone on it\n");
	
	int value = 0, reg_value=0;
	// horizontal
	int ptrx = x-1, stone_num = 1, blocked = 0;
	stone oppo_color = opposite_color(curr_color);
	while(ptrx>=0 and b.board_look[ptrx][y]==curr_color)
	{
		++stone_num;
		--ptrx;
	}
	if(ptrx<0) ++blocked;
	else if(b.board_look[ptrx][y]==oppo_color) ++blocked;

	ptrx = x+1;
	while(ptrx<BOARD_SIZE and b.board_look[ptrx][y]==curr_color)
	{
		++stone_num;
		++ptrx;
	}
	if(ptrx>=BOARD_SIZE) ++blocked;
	else if(b.board_look[ptrx][y]==oppo_color) ++blocked;

	update_value(reg_value, stone_num, blocked, value);
	// reg_value = get_point_score(stone_num, blocked);
	// if(reg_value>=0) value+=reg_value;
	// else 
	// {
	// 	fprintf(stderr, "Error in function get_point_score, please check.\n");
	// 	return -1;
	// }

	// vertical
	stone_num = 1; blocked = 0;
	int ptry = y-1;
	while(ptry>=0 and b.board_look[x][ptry]==curr_color)
	{
		++stone_num;
		--ptry;
	}
	if(ptry<0) ++blocked;
	else if(b.board_look[x][ptry]==oppo_color) ++blocked;

	ptry = y+1;
	while(ptry<BOARD_SIZE and b.board_look[x][ptry]==curr_color)
	{
		++stone_num;
		++ptry;
	}
	if(ptry>=BOARD_SIZE) ++blocked;
	else if(b.board_look[x][ptry]==oppo_color) ++blocked;
	update_value(reg_value, stone_num, blocked, value);

	// up-left
	stone_num = 1; blocked = 0;
	ptrx = x-1; ptry = y-1;
	while(ptry>=0 and ptrx>=0 and b.board_look[ptrx][ptry]==curr_color)
	{
		++stone_num;
		--ptrx; --ptry;
	}
	if(ptrx<0) ++blocked;
	else if(ptry<0) ++blocked;
	else if(b.board_look[ptrx][ptry]==oppo_color) ++blocked;

	ptry = y+1;ptrx = x+1;
	while(ptrx<BOARD_SIZE and ptry<BOARD_SIZE and b.board_look[ptrx][ptry]==curr_color)
	{
		++stone_num;
		++ptrx; ++ptry;
	}
	if(ptrx>=BOARD_SIZE) ++blocked;
	else if(ptry>=BOARD_SIZE) ++blocked;
	else if(b.board_look[ptrx][ptry]==oppo_color) ++blocked;
	update_value(reg_value, stone_num, blocked, value);

	// up-right
	stone_num = 1; blocked = 0;
	ptrx = x+1; ptry = y-1;
	while(ptrx<BOARD_SIZE and ptry>=0 and b.board_look[ptrx][ptry]==curr_color)
	{
		++stone_num;
		++ptrx; --ptry;
	}
	if(ptrx>=BOARD_SIZE) ++blocked;
	else if(ptry<0) ++blocked;
	else if(b.board_look[ptrx][ptry]==oppo_color) ++blocked;

	ptrx = x-1; ptry = y+1;
	while(ptrx>=0 and ptry<BOARD_SIZE and b.board_look[ptrx][ptry]==curr_color)
	{
		++stone_num;
		--ptrx; ++ptry;
	}
	if(ptrx<0) ++blocked;
	else if(ptry>=BOARD_SIZE) ++blocked;
	else if(b.board_look[ptrx][ptry]==oppo_color) ++blocked;
	update_value(reg_value, stone_num, blocked, value);

	return value;
}


score evaluator::board_evaluate(board &b, stone curr_color)
{
	int value = 0;
	for(int x=0;x<BOARD_SIZE;++x)
		for(int y=0;y<BOARD_SIZE;++y)
			if(b.is_in_consideration(x,y) and b.board_look[x][y]==NONE)
			{
				value += point_evaluate(b,x,y,curr_color);
				value -= point_evaluate(b,x,y,opposite_color(curr_color));
			}
	return value;
}