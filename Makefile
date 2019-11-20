chess: ChessMain.cpp ChessBoard.h ChessBoard.cpp Piece.cpp Piece.h Makefile
	g++ -Wall -g ChessMain.cpp ChessBoard.h ChessBoard.cpp Piece.cpp Piece.h -o chess

.PHONY: test
test:
	./chess

.PHONY: clean
clean:
	rm -f *.o chess *.tmp