#ifndef EVALUATE_H
#define EVALUATE_H

#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "constant.h"

// score
typedef enum 
{
	DOUBLE_BLOCK = 0
	ONE = 1e1,
	TWO = 1e2,
	THREE = 1e3,
	FOUR = 1e5,
	FIVE = 1e6,
	BLOCKED_ONE = 1,
	BLCOKED_TWO = 1e1,
	BLOCKED_THREE = 1e2,
	BLOCKED_FOUR = 1e4,
}score;

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
	double point_evaluate(board &b, int x, int y, stone curr_color);
	double board_evaluate(board &b, stone curr_color);
};

#endif