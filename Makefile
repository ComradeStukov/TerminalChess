chess: ChessMain.cpp ChessBoard.h ChessBoard.cpp Piece.cpp Piece.h Makefile
	g++ -std=c++11 -Wall -g -o chess ChessMain.cpp ChessBoard.cpp Piece.cpp

.PHONY: run
run: chess
	./chess

.PHONY: run_chess
run_chess: chess
	./chess

gamecli: GameCLI.cpp ChessBoard.h ChessBoard.cpp Piece.cpp Piece.h Makefile
	g++ -std=c++11 -Wall -g -o gamecli GameCLI.cpp ChessBoard.cpp Piece.cpp

.PHONY: run_gamecli
run_gamecli: gamecli
	./gamecli

# Example: g++ -g -O2 -o hello hello.cpp -I../libs/include -L../libs/lib ../libs/lib/libfinal.a -ltermcap
gameui: libs GameUI.cpp UI.h UI.cpp ChessBoard.h ChessBoard.cpp Piece.cpp Piece.h Makefile
	g++ -std=c++11 -Wall -g -O2 -o gameui GameUI.cpp UI.cpp ChessBoard.cpp Piece.cpp -Ilibs/include -Llibs/lib libs/lib/libfinal.a -ltermcap

.PHONY: run_gameui
run_gameui: gameui
	./gameui

.PHONY: clean
clean:
	rm -f *.o *.tmp chess gamecli gameui

libs: genlibs.sh
	bash ./genlibs.sh

.PHONY: clean_libs
clean_libs:
	rm -rf ./libs

all: chess gamecli gameui