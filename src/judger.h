#ifndef JUDGER_H
#define JUDGER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "constant.h"
#include "board.h"

class board;


/********************************************************************************************
*	The definition of the judger:	the judger checks whether the game is terminated, 
*									determines the winner and saves the game log.
*-------------------------------------------------------------------------------------------
*		log[TOTAL_BLANK]:			record the id of vertex through the game, it does not consider the color
*
*		log_num:					total number of log	
*
*		is_terminateed(board &):	return the stone color which have five stones in a line,
*									if noone have five stones in a line, return NONE.
*
*		winner(board &b):			return the winner if the game is terminated.
*		
*		add_log(int id):			add a new move into the log
*		
*		remove_log():				remove a move in the log	
*
*		pop_log():					pop the last log in the log array, if no log in the array, return -1	
*		
*		save_game(stone winner):	save the log file with a winner. Default(or unfinished game) with NONE winner. 
*		
*******************************************************************************************/
class judger
{
private:
	int log[TOTAL_BLANK];
	int log_num;
public:
	judger(void);
	stone is_terminated(board &b);
	stone winner(board &b);
	void add_log(int id);
	void add_log(int x, int y);
	void remove_log(void);
	int pop_log(void);
	void clear_log(void){log_num=0;}
	void save_game(stone winner=NONE);
	int * get_log(void){return &log[0];}
	int get_log_num(void){return log_num;}
};

#endif