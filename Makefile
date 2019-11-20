chess: ChessMain.cpp ChessBoard.h ChessBoard.cpp Piece.cpp Piece.h Makefile
	g++ -Wall -g ChessMain.cpp ChessBoard.h ChessBoard.cpp Piece.cpp Piece.h -o chess

.PHONY: run
run:
	./chess

gamecli: GameCLI.cpp ChessBoard.h ChessBoard.cpp Piece.cpp Piece.h Makefile
	g++ -Wall -g GameCLI.cpp ChessBoard.h ChessBoard.cpp Piece.cpp Piece.h -o gamecli

.PHONY: run_gamecli
run_gamecli:
	./gamecli

gameui: libs GameUI.cpp UI.h UI.cpp ChessBoard.h ChessBoard.cpp Piece.cpp Piece.h Makefile
	g++ -Wall -g GameUI.cpp UI.h UI.cpp ChessBoard.h ChessBoard.cpp Piece.cpp Piece.h -o gameui

.PHONY: run_gameui
run_gameui:
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