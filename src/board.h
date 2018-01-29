#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "constant.h"
#include "judger.h"
#include "error.h"
#include "evaluate.h"


// extern declaration
class judger;
class evaluator;

/********************************************************************************************
*
*	macros that deal with the change of consideration domain
*	each time a stone add or remove from the board, the consideration domain will change
*	"expend" means that the consider domain matrix element that near a new stone will add 1
*	"shrink" means that the consider domain matrix element that near a removed stone will sub 1 
*	"near a stone" means that the Manhattan Distance between vertexs are less than or equal to 3
*
*******************************************************************************************/
#define expend_consider_domain(x,y,board_look,consideration_domain) \
	int dx[25] = { \
		-3, \
		-2,-2,-2, \
		-1,-1,-1,-1,-1, \
		 0, 0, 0, 0, 0, 0, 0, \
		 1, 1, 1, 1, 1, \
		 2, 2, 2, \
		 3}; \
	int dy[25] = { \
		0, \
		-1, 0, 1, \
		-2,-1, 0, 1, 2, \
		-3,-2,-1, 0, 1, 2, 3, \
		-2,-1, 0, 1, 2, \
		-1, 0, 1, \
		0}; \
	for(int i=0;i<25;++i) \
	{ \
		if(x+dx[i]>=0 and x+dx[i]<BOARD_SIZE and y+dy[i]>=0 and y+dy[i]<BOARD_SIZE) \
			++consideration_domain[x+dx[i]][y+dy[i]]; \
	}

#define shrink_consider_domain(x,y,board_look,consideration_domain) \
	int dx[25] = {\
		-3, \
		-2,-2,-2, \
		-1,-1,-1,-1,-1, \
		0, 0, 0, 0, 0, 0, 0, \
		1, 1, 1, 1, 1, \
		2, 2, 2, \
		3}; \
	int dy[25] = { \
		0, \
		-1, 0, 1, \
		-2,-1, 0, 1, 2, \
		-3,-2,-1, 0, 1, 2, 3, \
		-2,-1, 0, 1, 2, \
		-1, 0, 1, \
		0}; \
	for(int i=0;i<25;++i) \
	{ \
		if(x+dx[i]>=0 and x+dx[i]<BOARD_SIZE and y+dy[i]>=0 and y+dy[i]<BOARD_SIZE) \
			--consideration_domain[x+dx[i]][y+dy[i]]; \
	}



/******************************************************************************************
*	The definition of board
*		1. The definition of consideration domain
*		the consideration domain is the current battle field in the board
*		obviously every gobang player will not consiter moves out of the 
*		current battle field.
* 	
*		The consideration domain is the set of vertex(set is implemented using int
* 		matrix) that has <=3 Manhattan Distance from the vertex that has stone on it. 
*		If exist such vertex with stone, current vertex's consideration domain value will
*		increase 1. Similarly, if a stone is removed, the vertex' value will decrease 1. 
*		
*		2. The board_look shows the current board(use BLACK, WHITE and NONE)
*		
*		3. current_color means the current player's stone color, the board force the players
*		and the users to put the stone on the board in "BLACK and WHITE order", any move that
*		does not obey this order will be warned and ignored. 
*		
*******************************************************************************************/
class board
{
	friend class judger;
	friend class evaluator;
private:
	int consideration_domain[BOARD_SIZE][BOARD_SIZE];
	stone board_look[BOARD_SIZE][BOARD_SIZE];
	int total_moves;
	stone current_color;
public:
	board(void);
	board(const board & other);
	board operator=(const board & other);
	void add_stone(int x,int y);
	void remove_stone(int x, int y);
	void clear_board(void);
	bool in_board(int x,int y);
	bool is_valid(int x,int y);
	bool is_in_consideration(int x, int y);
	int id(int x, int y);
	void index(int id, int &x, int &y);
	void print_board(bool print_consider_domain=false);
	stone get_player(void){return current_color;}
	int get_total_moves(void){return total_moves;}
};

#endif
