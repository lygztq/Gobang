#include "board.h"

inline stone oppo_color(stone color)
{
	// get the opposite color
	return (color==BLACK)? WHITE:BLACK;
}

board::board(void)
{
	int i, j;
	for(i=0;i<BOARD_SIZE;++i)
		for(j=0;j<BOARD_SIZE;++j)
		{
			consideration_domain[i][j] = 0;
			board_look[i][j] = NONE;
		}
	total_moves = 0;
	current_color = BLACK;
}

board::board(const board & other)
{
	int i, j;
	for(i=0;i<BOARD_SIZE;++i)
		for(j=0;j<BOARD_SIZE;++j)
		{
			consideration_domain[i][j] = other.consideration_domain[i][j];
			board_look[i][j] = other.board_look[i][j];
		}
	total_moves = other.total_moves;
	current_color = other.current_color;
}

board board::operator=(const board & other)
{
	if(this == &other) return *this;

	int i,j;
	for(i=0;i<BOARD_SIZE;++i)
		for(j=0;j<BOARD_SIZE;++j)
		{
			consideration_domain[i][j] = other.consideration_domain[i][j];
			board_look[i][j] = other.board_look[i][j];
		}
	total_moves = other.total_moves;
	current_color = other.current_color;
	return *this;
}

void board::clear_board(void)
{
	int i, j;
	for(i=0;i<BOARD_SIZE;++i)
		for(j=0;j<BOARD_SIZE;++j)
		{
			consideration_domain[i][j] = 0;
			board_look[i][j] = NONE;
		}
	total_moves = 0;
	current_color = BLACK;
}

bool board::in_board(int x, int y)
{
	return (x>=0 and x<BOARD_SIZE and y>=0 and y<BOARD_SIZE);
}

bool board::is_valid(int x, int y)
{
	// check whether the move is valid
	bool in_board = (x>=0 and x<BOARD_SIZE and y>=0 and y<BOARD_SIZE);
	bool no_stone = (board_look[x][y]==NONE);
	return (no_stone and in_board);
}

bool board::is_in_consideration(int x, int y)
{
	if(total_moves==0 and x == BOARD_SIZE/2 and y==BOARD_SIZE/2) return true; 
	return (consideration_domain[x][y]!=0);
}

int board::id(int x, int y)
{	
	// get the id of a vertex
	return x*BOARD_SIZE + y;
}

void board::index(int id, int &x, int &y)
{
	// get the index of a vertex
	x = id / BOARD_SIZE;
	y = id % BOARD_SIZE;
}

void board::add_stone(int x, int y)
{
	// check whether this vertex is valid
	if(!is_valid(x,y))
	{
		//fprintf(stderr, "%s\n", NOT_VALID_VERTEX);
		fprintf(stderr, "This vertex is not vaild, please check your input.\n");
		return;
	}

	// add and remove should in order, otherwise the color will mix up. 
	++total_moves;
	board_look[x][y] = current_color;
	next_color(current_color);
	expend_consider_domain(x,y,board_look,consideration_domain);
}

void board::remove_stone(int x, int y)
{
	// check whether this vertex is valid
	if( !in_board(x,y) || board_look[x][y]!=oppo_color(current_color) )
	{
		fprintf(stderr, "%s\n", NOT_VALID_VERTEX);
		return;
	}

	// add and remove should in order, otherwise the color will mix up. 
	--total_moves;
	board_look[x][y] = NONE;
	next_color(current_color);
	shrink_consider_domain(x,y,board_look,consideration_domain);
}

void board::print_board(bool print_consider_domain)
{
	int i, j;
	//print head
	printf("The BOARD:\n  ");
	for(int i=0;i<BOARD_SIZE;++i)
	{
		if(i>8)
			printf("%d ", i+1);
		else
			printf("%d  ", i+1);
	}
	printf("\n");

	//print mid
	for(i=0;i<BOARD_SIZE;++i)
	{
		printf("%c ", 'a'+i);
		for(j=0;j<BOARD_SIZE;++j)
			switch(board_look[i][j])
			{
				case NONE:	printf(".  "); break;
				case BLACK:	printf("@  "); break;
				case WHITE:	printf("O  "); break;
			}
		printf("%c \n", 'a'+i);
	}

	//print tail
	printf("  ");
	for(int i=0;i<BOARD_SIZE;++i)
	{
		if(i>8)
			printf("%d ", i+1);
		else
			printf("%d  ", i+1);
	}
	printf("\n");

	if(print_consider_domain)
	{
		printf("\n------------\n");
		//print head
		printf("The CONSIDERATION DOMAIN\n  ");
		for(int i=0;i<BOARD_SIZE;++i)
		{
			if(i>8)
				printf("%d ", i+1);
			else
				printf("%d  ", i+1);
		}
		printf("\n");

		//print mid
		for(i=0;i<BOARD_SIZE;++i)
		{
			printf("%c ", 'a'+i);
			for(j=0;j<BOARD_SIZE;++j)
			{
				if(consideration_domain[i][j]==0)
					printf(".  ");
				else
					printf("C  ");
			}

			printf("%c \n", 'a'+i);
		}

		//print tail
		printf("  ");
		for(int i=0;i<BOARD_SIZE;++i)
		{
			if(i>8)
				printf("%d ", i+1);
			else
				printf("%d  ", i+1);
		}
		printf("\n");
	}
}

