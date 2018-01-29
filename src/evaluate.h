#ifndef EVALUATE_H
#define EVALUATE_H

#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "constant.h"

// score
typedef int score;

typedef enum _POINT_SCORE
{
	WRONG = -1,
    DOUBLE_BLOCKED = 0,
    ONE = 10,
    TWO = 100,
    THREE = 1000,
    FOUR = 100000,
    FIVE = 1000000,
    BLOCKED_ONE = 1,
    BLCOKED_TWO = 10,
    BLOCKED_THREE = 100,
    BLOCKED_FOUR = 10000
}point_score;

#define update_value(reg_value, stone_num, blocked, value) \
	reg_value = get_point_score(stone_num, blocked); \
	if(reg_value>=0) value+=reg_value; \
	else \
	{  \
		fprintf(stderr, "Error in function get_point_score, please check.\n"); \
		return -1; \
	}


// extern declaration
class board;

/*******************************************************************************************
*
*	The evaluator class evaluates the board situation according to the current player's color
*	and gives suggestion to the ai player.
*
*	The point evaluate function evaluates the value of a vertex in the board to determine which
*	vertex is better for the next move.
*
*	The boarrd evaluate function evaluates the total board and judge the current situation for 
*	current player.
*
*	TODO:
*	1. evaluate the point value according to the distance between current point and the center
*	of the board.
*
*	2. evaluate the point value according to the stone around the current point.
*
********************************************************************************************/

class evaluator
{
public:
	point_score get_point_score(int stone_num, int blocked);
	score point_evaluate(board &b, int x, int y, stone curr_color);
	score board_evaluate(board &b, stone curr_color);
};

#endif