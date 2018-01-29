#Makefile begin
CC=g++

main.o: main.cpp
	$(CC) -c $< -o $@
translator.o: translator.cpp
	$(CC) -c $< -o $@
judger.o: judger.cpp
	$(CC) -c $< -o $@
board.o: board.cpp
	$(CC) -c $< -o $@
test.o: test.cpp
	$(CC) -c $< -o $@
#all: board.cpp test.cpp
test: test.o board.o judger.o translator.o
	$(CC) $^ -o test_board.exe
all: main.o board.o judger.o translator.o
	$(CC) $^ -o gobang.exe

clean:
	rm *.o
	rm *.exe
#Makefile end
