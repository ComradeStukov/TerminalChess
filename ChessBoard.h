#ifndef _CHESS_BOARD_H_
#define _CHESS_BOARD_H_

#include <iostream>
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
    inline static std::string coordStr(const coord pos)
    {
        return std::string(1, pos.second + 'A') + std::string(1, pos.first + '1');
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
    ChessBoard(std::ostream& ostr=std::cout);
    ~ChessBoard();
    void resetBoard();
    void submitMove(std::string src, std::string dst);
    void submitPromotion(std::string type);
    void drawBoard(bool simple=false);
    inline Piece* getPiece(coord pos)
    {
        return m_board[pos.first][pos.second];
    }
    inline void setPiece(coord pos, Piece* piece)
    {
        m_board[pos.first][pos.second] = piece;
        return;
    }
    inline Piece* getPassantPawn(int side)
    {
        return m_passant_pawn[side];
    }
private:
    Piece* dryrunMove(coord pos, Piece* piece);
    void swapPlayer();
    bool castlingCheck(Piece *king, coord king_dst);
    bool checkCheck(int side);
    bool mateCheck(int side);

public:
    static const int SIDE = 2;
    static const int WHITE = 0, BLACK = 1, UNKNOWN = -1;
    static const int ROW = 8, COL = 8;
    static const int NORMAL = 0, CHECK = 1, STALEMATE = 2, CHECKMATE = 3;

private:
    int m_winner;
    int m_side;
    int m_status;
    Piece* m_board[ROW][COL];
    Piece* m_king[SIDE];
    Piece* m_passant_pawn[SIDE];
    Piece* m_promotion_pawn[SIDE];
    std::ostream& m_ostr;
};

#endif
