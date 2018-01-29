#include "translator.h"

bool translator::index_transform(int &x, int &y)
{
	char *ptr = &buffer[0];
	
	// skip the spaces
	while(*ptr==' ') ++ptr;

	// read x index
	if(*ptr>='a' && *ptr<='z') x = (*ptr - 'a');
	else if(*ptr>='A' && *ptr<='Z') x = (*ptr - 'A');
	else return false;
	++ptr;

	// skip the spaces
	while(*ptr==' ') ++ptr;
	
	//read y index
	int tmp_y = 0;
	while(*ptr>='0' && *ptr<='9')
	{
		tmp_y = tmp_y*10 + (*ptr - '0');
		++ptr;
	}
	y = --tmp_y;

	return true;
}


command translator::read_command(stone &player, int &x, int &y)
{
	scanf("%s", buffer);

	if(!strcmp(buffer, "clear_board") ) return CLEAR_BOARD;
	if(!strcmp(buffer, "name") ) return NAME;
	if(!strcmp(buffer, "play") )
	{
		scanf("%s", buffer);
		if(!strcmp(buffer, "w")) player = WHITE;
		else if(!strcmp(buffer, "b")) player = BLACK;
		else return INVALID_COMMAND;

		scanf("%s", buffer);
		if(index_transform(x,y)) return PLAY;
		else return INVALID_COMMAND;
	}
	if(!strcmp(buffer, "genmove") ) return GEN_MOVE;
	if(!strcmp(buffer, "show_board") ) return VIEW_BOARD;
	if(!strcmp(buffer, "save") ) return SAVE_GAME;
	if(!strcmp(buffer, "total_move") ) return TOTAL_MOVE;
	if(!strcmp(buffer, "undo") ) return UNDO;
	if(!strcmp(buffer, "exit") ) return EXIT;
	return INVALID_COMMAND;
}

void translator::speak_command(char *buf, command com, stone color, int x, int y)
{
	char tmp_buf[5]; // buffer for command parameters
	char char_x, char_y_pre, char_y_lat, char_color;  // char parameters
	switch(com)
	{
		case CLEAR_BOARD:	strcpy(buf, "clear_board"); break;

		case NAME:			strcpy(buf, "name"); break;

		case PLAY:			strcpy(buf, "play ");
							char_color = (color==BLACK)?'b':'w';
							sprintf(tmp_buf, "%c ", char_color);
							strcat(buf, tmp_buf);
							char_x = x+'a';
							char_y_pre = (y+1)/10 + '0';
							char_y_lat = (y+1)%10 + '0';
							sprintf(tmp_buf, "%c", char_x);
							strcat(buf, tmp_buf);
							if(y>8)
							{
								sprintf(tmp_buf, "%c", char_y_pre);
								strcat(buf, tmp_buf);
							} 
							sprintf(tmp_buf, "%c", char_y_lat);
							strcat(buf, tmp_buf);
							break;
		
		case GEN_MOVE:		strcpy(buf, "genmove"); break;

		case VIEW_BOARD:	strcpy(buf, "show_board"); break;

		case SAVE_GAME:		strcpy(buf, "save"); break;

		case TOTAL_MOVE:	strcpy(buf, "total_move"); break;

		case UNDO:			strcpy(buf, "undo"); break;

		case EXIT:			strcpy(buf, "exit"); break;

		default:			fprintf(stderr, "You are translating a wrong COMMAND CODE! please check.\n");
							strcpy(buf, "wrong command code");
							break;
	}
}