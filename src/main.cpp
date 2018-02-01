#include <stdio.h>
#include <stdlib.h>
#include "constant.h"
#include "board.h"
#include "judger.h"
#include "translator.h"
#include "evaluate.h"
#include "search.h"
#include <vector>

class judger;
class board;

// the main process of the game
void gaming()
{
	board game_board;
	judger game_judger;
	translator game_translator;
	fast_evaluator game_evaluator;
	search_tree tree;

	int next_x, next_y, pre_x, pre_y, pre_id;
	char yse_or_no;
	stone next_color, win_player;
	printf("COMMAND:> ");
	command comm = game_translator.read_command(next_color, next_x, next_y);

	while(comm!=EXIT)
	{
		int reg;
		switch(comm)
		{
			case CLEAR_BOARD:	game_board.clear_board();
								game_judger.clear_log();
								break;

			case NAME:			printf(AI_NAME);printf("\n");
								break;

			case PLAY:			// first check whether this is a valid move
								if(!game_board.is_valid(next_x, next_y))
								{
									fprintf(stderr, "Invalid move, please check!\n");
									break;
								}
								if(game_board.get_player()!=next_color)
								{
									fprintf(stderr, "Move for wrong player!\n");
									break;
								}

								// add the stone to the board
								tree.gen_search_node(game_board);
								game_board.add_stone(next_x, next_y);
								game_judger.add_log(next_x, next_y);

								// if the game is terminated
								if(win_player = game_judger.is_terminated(game_board))
								{
									switch(win_player)
									{
										case BLACK:		printf("The Black player win.\n");break;
										case WHITE:		printf("The White player win.\n");break;
										case NO_WINNER:	printf("No winner.\n"); break;
										default: 		break;
									}
									game_board.print_board();

									// ask the player whether save the game.
									yse_or_no = '?';
									while(yse_or_no!='n' and yse_or_no!='y')
									{
										fflush(stdin);
										printf("Do you want to save this game?(y/n)\n");
										scanf("%c", &yse_or_no);
										if(yse_or_no=='y')
										{
											game_judger.save_game(win_player);
											return;
										}
										else if(yse_or_no=='n')
											return;
									}
								}

								// else show the board after each move
								game_board.print_board();
								break;

			case GEN_MOVE:		break;

			case UNDO:			pre_id = game_judger.pop_log();
								if(pre_id==-1)
								{
									fprintf(stderr, "There is nothing to undo.\n");
									break;
								}
								game_board.index(pre_id, pre_x, pre_y);
								game_board.remove_stone(pre_x, pre_y);
								printf("remove stone at (%c, %d)\n", (pre_x+'a'), pre_y+1);
								game_board.print_board();
								break;

			case VIEW_BOARD:	game_board.print_board();
								break;

			case SAVE_GAME:		game_judger.save_game(game_judger.winner(game_board));
								break;

			case TOTAL_MOVE:	printf("Total move is: %d\n", game_board.get_total_moves());
								break;

			case INVALID_COMMAND:	fprintf(stderr, "Wrong command format! Please try again.\n");
									break;

			default: break;
		}
		printf("COMMAND:> ");
		comm = game_translator.read_command(next_color, next_x, next_y);
	}
}

int main(void)
{
	gaming();
	system("PAUSE");
	return EXIT_SUCCESS;
}