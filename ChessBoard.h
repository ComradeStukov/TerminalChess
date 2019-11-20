#ifndef _CHESS_BOARD_H_
#define _CHESS_BOARD_H_

#include <string>

#include "Piece.h"

/*
=====
move(p, pos)
=====

piece_check(p, pos)
make_the_move
check_check(x)
For all piece of 1-x:
	if piece_check(that piece, king of x):
	    true
rollback_the_move

=====
judge(x)
=====

check_check(x)
mate_check(x) :
For all piece of x:
    For all pos:
	    if move(that piece, pos):
		    true

*/

class ChessBoard
{
public:
    inline static coord strCoord(const std::string& str)
    {
        return str.length() != 2 ? std::make_pair(-1, -1) : std::make_pair(str.at(1) - '1', str.at(0) - 'A');
    }
    inline static bool checkCoord(const coord& pos)
    {
        return 0 <= pos.first && pos.first < ROW && 0 <= pos.second && pos.second < COL;
    }
    inline static std::string getPlayer(int side)
    {
        return side ? std::string("Black") : std::string("White");
    }
public:
    ChessBoard();
    ~ChessBoard();
    void resetBoard();
    void submitMove(std::string drc, std::string dst);
    Piece* dryrunMove(coord pos, Piece* piece);
    bool checkCheck(int side);
    bool mateCheck(int side);
    inline Piece* getPiece(coord pos)
    {
        return m_board[pos.first][pos.second];
    }
    inline void setPiece(coord pos, Piece* piece)
    {
        m_board[pos.first][pos.second] = piece;
        return;
    }
    inline King* getKing(int side)
    {
        return m_king[side];
    }
    inline Piece* getPassantPawn(int side)
    {
        return m_passant_pawn[side];
    }
    void drawBoard();

public:
    static const int SIDE = 2;
    static const int WHITE = 0, BLACK = 1, UNKNOWN = -1;
    static const int ROW = 8, COL = 8;

private:
    int m_winner;
    int m_side;
    Piece* m_board[ROW][COL];
    King* m_king[SIDE];
    Piece* m_passant_pawn[SIDE];
};

#endif
