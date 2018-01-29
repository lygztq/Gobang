#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constant.h"


/**********************************************************
*	The definition of the translator
*		the buffer store a single string command
*
*		the index_transform try to transfrom the string index
*		in the buffer to the numerical index. Return true if
*		success, else return false.
*		
*		The read_command function translate a string command
*		into COMMAND code
*
*		The speak_command function translate a COMMAND code
*		into string command
**********************************************************/

class translator
{
private:
	char buffer[MAX_COMMAND_LEN];
public:
	translator(void){}
	bool index_transform(int &x, int &y);
	command read_command(stone &player, int &x, int &y);
	void speak_command(char *buf, command com, stone color=BLACK, int x=0, int y=0);
};

#endif		