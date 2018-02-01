#ifndef EVALUATE_H
#define EVALUATE_H

#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "constant.h"

// score
typedef int score;

// direction used by the evaluator class
typedef enum _DIRECTION
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	UP_LEFT,
	UP_RIGHT,
	DOWN_LEFT,
	DOWN_RIGHT 
}direction;

typedef enum _FAST_POINT_SCORE
{
	FAST_WRONG = -1,
    FAST_DOUBLE_BLOCKED = 0,
    FAST_ONE = 10,
    FAST_TWO = 100,
    FAST_THREE = 1000,
    FAST_FOUR = 100000,
    FAST_FIVE = 1000000,
    FAST_BLOCKED_ONE = 1,
    FAST_BLOCKED_TWO = 10,
    FAST_BLOCKED_THREE = 100,
    FAST_BLOCKED_FOUR = 10000
}fast_point_score;

// typedef enum _POINT_SCORE
// {
// 	WRONG = -1,
// 	FIVE_A = 300000,	//	01111*
// 	FIVE_B = 250000,	//	21111*
// 	FIVE_C = 240000,	//	111*1
// 	FIVE_D = 230000,	//	11*11
// 	FIVE_DECAY = 500,	//	if current evaluated player is not the current move player, use it
// 	FOUR_A = 
// }point_score;

// used in fast evaluate, to update the value of the vertex
#define update_value(reg_value, stone_num, blocked, value) \
	reg_value = get_point_score(stone_num, blocked); \
	if(reg_value>=0) value+=reg_value; \
	else \
	{  \
		fprintf(stderr, "Error in function get_point_score, please check.\n"); \
		return -1; \
	}

// used by evaluator class to get the relative index value
// b 	board 	
// x,y	index
// d 	direction
// i 	relative index
// v 	value
// #define get_line_value(b,x,y,d,i,v) \
// 	int tmp_x = x, tmp_y = y; \
// 	switch(d) \
// 	{ \
// 		case LEFT:		tmp_x -= i; break; \
// 		case RIGHT:		tmp_x += i; break; \
// 		case UP:		tmp_y -= i; break; \
// 		case DOWN:		tmp_y += i; break; \
// 		case UP_LEFT:	tmp_x -= i;tmp_y -= i; break; \
// 		case UP_RIGHT:	tmp_x += i;tmp_y -= i; break; \
// 		case DOWN_LEFT:	tmp_x -= i;tmp_y += i; break; \
// 		case DOWN_RIGHT:tmp_x += i;tmp_y += i; break; \
// 	} \
// 	if(tmp_x<0 or tmp_x>=BOARD_SIZE or tmp_y<0 or tmp_y<=BOARD_SIZE) \
// 		v = NOT_IN_BOARD; \
// 	else \
// 		v = b.board_look[tmp_x][tmp_y];


// extern declaration
class board;

/*******************************************************************************************
*
*	The fast_evaluator class evaluates the board situation according to the current player's color
*	and gives suggestion to the ai player. The result of the fast evaluator may be not good enough,
*	but it's speed is faster.
*
*	The point evaluate function evaluates the value of a vertex in the board to determine which
*	vertex is better for the next move.
*
*	The board evaluate function evaluates the total board and judge the current situation for 
*	current player.
*
*	TODO:
*	1. evaluate the point value according to the distance between current point and the center
*	of the board.
*
*	2. evaluate the point value according to the stone around the current point.
*
********************************************************************************************/

class fast_evaluator
{
public:
	fast_point_score get_point_score(int stone_num, int blocked);
	score point_evaluate(board &b, int x, int y);
	score single_point_evaluate(board &b, int x, int y, stone curr_color);
	score board_evaluate(board &b, stone curr_color);
};

class evaluator
{
public:
	stone get_line_value(board &b, int x, int y, direction d, int i);
	score one_player_point_evaluate(board &b, int x, int y, stone to_evl);
	score point_evaluate(board &b, int x, int y);
};

#endif