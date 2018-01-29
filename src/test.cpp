#include <stdio.h>
#include <stdlib.h>
#include "constant.h"
#include "board.h"
#include "judger.h"
#include "translator.h"

class judger;
class board;

int main(void)
{
	// TODO: add a config part? Is this really necessary?
	// TODO: start ai model
	board test_board;
	judger test_judger;
	translator test_translator;
	for(int i=0;i<4;++i)
	{
		test_board.add_stone('g'-'a', i+2); //g8
		test_judger.add_log('g'-'a', i+2);

		test_board.add_stone('f'-'a', i+2); //g8
		test_judger.add_log('f'-'a', i+2);
	}
	test_board.add_stone('g'-'a',6);
	test_board.print_board(true);
	test_judger.save_game(test_judger.winner(test_board));
	system("PAUSE");
	return EXIT_SUCCESS;
}