#ifndef CONSTANT_H
#define CONSTANT_H

#include <stdio.h>
#include <stdlib.h>

#define abs(x) (x>=0)?x:-x;

// Board size
#define BOARD_SIZE 15
#define TOTAL_BLANK BOARD_SIZE*BOARD_SIZE

// max command length
#define MAX_COMMAND_LEN 50

// Some functional constant
#define NOT_IN_BOARD -1

// The name of the ai player
#define AI_NAME "Gobang_player"

// Calculate id
#define get_id(x,y,id) \
	id = x*BOARD_SIZE + y;

// Calculate index
#define get_index(x,y,id) \
	x = id / BOARD_SIZE; \
	y = id % BOARD_SIZE;

// Change color
#define next_color(color) \
	color = (color==BLACK)? WHITE:BLACK;

// opposite color
#define opposite_color(color) (color==BLACK)? WHITE:BLACK

// Calculate the Manhattan distance
#define man_dis(x1,y1,x2,y2,dis) \
	dis = abs(x1-x2) + abs(y1-y2);

// The definition of stone
typedef enum _STONE
{
	NONE,
	WHITE,
	BLACK,
	NO_WINNER	// this is used by judger class, if no valid moves in the board, return this
}stone;

// The definition of COMMAND code, we use string command for human 
// player and the COMMAND code for the computer, the translator class
// will translate these two kinds of command.
typedef enum _COMMAND
{						// definition								|	string command
						// ----------------------------------------------------------------------
	INVALID_COMMAND,	// wrong format command or error command 	|	
	CLEAR_BOARD,		// clean the current 						|	clear_board
	NAME,				// return the player's name 				|	name
	PLAY,				// put a stone on the board 				|	play b/w [index, e.g. a3, e5]
	GEN_MOVE,			// generate a move from AI					|	genmove
	VIEW_BOARD,			// show the board 							|	show_board
	SAVE_GAME,			// save the game 							|	save
	TOTAL_MOVE,			// show the total move of current board 	|	total_move
	UNDO,				// undo a move 								|	undo
	EXIT				// exit game 								|	exit
}command;

#endif