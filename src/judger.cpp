#include "judger.h"

// static inline get_index(int id, int &x, int &y)
// {
// 	x = id / BOARD_SIZE;
// 	y = id % BOARD_SIZE;
// }

judger::judger(void)
{
	log_num = 0;
}


stone judger::is_terminated(board &b)
{
	// first judge whether these is no valid move
	if(b.total_moves==TOTAL_BLANK) return NO_WINNER;

	// judge if the player with (int)color already has five stone in a line
	int length = 0;

	// 8 single directions, 4 bidirections.
	int dx[8] = {-1,1, 0,0, -1,1, -1,1};
	int dy[8] = {0,0, -1,1, -1,1, 1,-1};

	for(auto x=0;x<BOARD_SIZE;++x)
		for(auto y=0;y<BOARD_SIZE;++y)
		{
			if(b.board_look[x][y]==NONE) continue;
			stone color = b.board_look[x][y];	//current color in consideration
			for(int i=0;i<8;++i)
			{
				int tx = x + dx[i], ty = y + dy[i];
				if(b.in_board(tx,ty))
					while(b.board_look[tx][ty]==color)
					{
						++length;
						tx += dx[i]; ty += dy[i];
						if(!b.in_board(tx, ty)) break;
					}
				if (i%2)	// finish in a bi-direction
				{
					++length;	// add the stone in center(i.e., the stone at (x,y) )
					if(length>=5) return color;
					length = 0; 
				}
			}
		}
	return NONE;
}

stone judger::winner(board &b)
{
	return is_terminated(b);
}

int judger::pop_log(void)
{
	if(log_num==0) return -1;
	return log[--log_num];
}

void judger::add_log(int id)
{
	log[log_num++] = id;
}

void judger::add_log(int x, int y)
{
	log[log_num++] = x*BOARD_SIZE + y;
}

void judger::remove_log(void)
{
	if(log_num==0) return;
	--log_num;
}

void judger::save_game(stone winner)
{
	// use the time of the game as the log file name.
	time_t t = time(0); 
	char time_str[64]; 
	strftime(time_str, sizeof(time_str), "%Y_%m_%d_%H-%M-%S",localtime(&t) );

	// open the file
	FILE *log_file;
	char file_name[64];
	strcpy(file_name, "../logs/");
	strcat(file_name, time_str);
	strcat(file_name, ".log");
    log_file = fopen(file_name, "w");

    // write logs
    fprintf(log_file, "time: ");
    fprintf(log_file, time_str);
    fprintf(log_file, "\ttotal_moves: %d\n", log_num);

    stone current_color = BLACK;
    for(int i=0;i<log_num;++i)
    {
    	int x,y;
    	get_index(log[i], x, y);
    	switch(current_color)
    	{
    		case BLACK: fprintf(log_file, "B[%d %d]", x, y); break;
    		case WHITE: fprintf(log_file, "W[%d %d]", x, y); break;
    		default:
    			fprintf(stderr, "Wrong log file element format, please check!\n");
    			break;
    	}
    	//if(!i%10) fprintf(log_file, "\n");
    	next_color(current_color);
    }
    fprintf(log_file, "\n");
	switch(winner)
	{
		case BLACK: fprintf(log_file, "winner: BLACK\n"); break;
		case WHITE: fprintf(log_file, "winner: WHITE\n"); break;
		default: break;
	}

	fclose(log_file);
}