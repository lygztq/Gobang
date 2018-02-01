#include "evaluate.h"

inline fast_point_score fast_evaluator::get_point_score(int stone_num, int blocked)
{
	if(blocked==2) return FAST_DOUBLE_BLOCKED;
	else if(stone_num>=5) return FAST_FIVE;
	else if(blocked==1)
	{
		switch(stone_num)
		{
			case 1: return FAST_BLOCKED_ONE;
			case 2: return FAST_BLOCKED_TWO;
			case 3: return FAST_BLOCKED_THREE;
			case 4: return FAST_BLOCKED_FOUR;
			default: return FAST_WRONG;
		}
	}
	else if(blocked==0)
	{
		switch(stone_num)
		{
			case 1: return FAST_ONE;
			case 2: return FAST_TWO;
			case 3: return FAST_THREE;
			case 4: return FAST_FOUR;
			default: return FAST_WRONG;
		}
	}
	else return FAST_WRONG;
}

score fast_evaluator::point_evaluate(board &b, int x, int y)
{
	return single_point_evaluate(b,x,y,b.get_player()) + single_point_evaluate(b,x,y,opposite_color(b.get_player()));
}

score fast_evaluator::single_point_evaluate(board &b, int x, int y, stone curr_color)
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

	if(b.get_player()!=curr_color) value/=2;
	return value;
}


score fast_evaluator::board_evaluate(board &b, stone curr_color)
{
	int value = 0;
	for(int x=0;x<BOARD_SIZE;++x)
		for(int y=0;y<BOARD_SIZE;++y)
			if(b.is_in_consideration(x,y) and b.board_look[x][y]==NONE)
			{
				value += single_point_evaluate(b,x,y,curr_color);
				value -= (single_point_evaluate(b,x,y,opposite_color(curr_color)) * 2);
			}
	return value;
}

stone evaluator::get_line_value(board &b, int x, int y, direction d, int i)
{
	switch(d)
	{
		case LEFT:		x -= i; break;
		case RIGHT:		x += i; break;
		case UP:		y -= i; break;
		case DOWN:		y += i; break;
		case UP_LEFT:	x -= i;y -= i; break;
		case UP_RIGHT:	x += i;y -= i; break;
		case DOWN_LEFT:	x -= i;y += i; break;
		case DOWN_RIGHT:x += i;y += i; break;
	}
	if(x<0 or x>=BOARD_SIZE or y<0 or y>=BOARD_SIZE)
		return NOT_IN_BOARD;
	else
		return b.board_look[x][y];
}

score evaluator::one_player_point_evaluate(board &b, int x, int y, stone to_evl)
{
	int value = 0,
		num_of_two = 0;

	bool my_turn = (to_evl == b.get_player());
	stone oppo_player = opposite_color(to_evl);

	printf("%d %d\n",get_line_value(b,x,y,LEFT,0), to_evl);

	for(direction d = LEFT; d<=DOWN_RIGHT; d = (direction)(d+1))
	{
		// ?1111*
		if(get_line_value(b,x,y,d,-1) == to_evl 
			and get_line_value(b,x,y,d,-2) == to_evl
			and get_line_value(b,x,y,d,-3) == to_evl
			and get_line_value(b,x,y,d,-4) == to_evl)
		{
			// 01111*
			if(get_line_value(b,x,y,d,-5) == NONE)	
				value += 300000;
			// 21111*
			else if(get_line_value(b,x,y,d,-5) == oppo_player or get_line_value(b,x,y,d,-2) == NOT_IN_BOARD)
				value += 250000;

			if(!my_turn) value -= 500;
			continue;
		}

		// 111*1
		if(get_line_value(b,x,y,d,-1) == to_evl 
			and get_line_value(b,x,y,d,-2) == to_evl
			and get_line_value(b,x,y,d,-3) == to_evl
			and get_line_value(b,x,y,d,1) == to_evl)
		{
			value += 240000;
			if(!my_turn) value-=500;
			continue;
		}

		// 11*11
		if(get_line_value(b,x,y,d,-1) == to_evl 
			and get_line_value(b,x,y,d,-2) == to_evl
			and get_line_value(b,x,y,d,1) == to_evl
			and get_line_value(b,x,y,d,2) == to_evl)
		{
			value += 230000;
			if(!my_turn) value-=500;
			continue;
		}

		// 111*0
		if(get_line_value(b,x,y,d,-1) == to_evl 
			and get_line_value(b,x,y,d,-2) == to_evl
			and get_line_value(b,x,y,d,-3) == to_evl)
		{
			if(get_line_value(b,x,y,d,-1) == NONE)
			{
				value += 750;
				if(get_line_value(b,x,y,d,-4) == NONE)
				{
					if(!my_turn) value -= 300;
					value += 3150;
				}
			}
			else if(get_line_value(b,x,y,d,1) == oppo_player or get_line_value(b,x,y,d,1) == NOT_IN_BOARD)
			{
				if(get_line_value(b,x,y,d,-4) == NONE)
					value+=500;
			}
				continue;
		}

		// 1110*
		if(get_line_value(b,x,y,d,-1) == NONE 
			and get_line_value(b,x,y,d,-2) == to_evl
			and get_line_value(b,x,y,d,-3) == to_evl
			and get_line_value(b,x,y,d,-4) == to_evl)
		{
			value+=350;
			continue;
		}

		// 11*1
		if(get_line_value(b,x,y,d,-1) == to_evl 
			and get_line_value(b,x,y,d,-2) == to_evl
			and get_line_value(b,x,y,d,1) == to_evl)
		{
			value += 600;
			if(get_line_value(b,x,y,d,-3) == NONE and  get_line_value(b,x,y,d,2) == NONE)
			{
				value+=3150;
				continue;
			}
			if(get_line_value(b,x,y,d,-3) == oppo_player or get_line_value(b,x,y,d,-3) == NOT_IN_BOARD)
				continue;
			else if(get_line_value(b,x,y,d,2) == oppo_player or get_line_value(b,x,y,d,2) == NOT_IN_BOARD)
				continue;
			else
				value += 700;
			continue;
		}

		if(get_line_value(b,x,y,d,-1) == to_evl
			and get_line_value(b,x,y,d,-2) ==to_evl
			and get_line_value(b,x,y,d,-3) !=oppo_player
			and get_line_value(b,x,y,d,-1) !=oppo_player)
			++num_of_two;
		
		int num_of_player = 0;
		for(int k=-4;k<=0;++k)
		{
			int tmp = 0;
			for (int l = 0; l <= 4; ++l)
			{
				if(get_line_value(b,x,y,d,k+l)==to_evl)
					++tmp;
				else if(get_line_value(b,x,y,d,k+l)==oppo_player or get_line_value(b,x,y,d,k+l)==NOT_IN_BOARD)
				{
					tmp = 0;
					break;
				}
			}
			num_of_player += tmp;
		}
		value += num_of_player * 15;
	}

	if(num_of_two>=2)
	{
		value+=3000;
		if(!my_turn) value -= 100;
	}
	return value;
}

score evaluator::point_evaluate(board &b, int x, int y)
{
	return one_player_point_evaluate(b,x,y,b.get_player()) + one_player_point_evaluate(b,x,y,opposite_color(b.get_player()));
}