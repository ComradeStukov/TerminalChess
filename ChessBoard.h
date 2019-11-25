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

/**
 * Core class for chess game.
 * This class taking all responsibilities of chess game simulation in logic.
 */
class ChessBoard
{
public:
    /**
     * Transfer a string into coordinate.
     * @param str: A two-char string representing a position on chess board (e.g. "A1").
     * @return Coordinate.
     */
    inline static coord strCoord(const std::string& str)
    {
        return str.length() != 2 ? std::make_pair(-1, -1) : std::make_pair(str.at(1) - '1', str.at(0) - 'A');
    }
    /**
     * Transfer a coordnate back to string
     * @param pos: A coordinate.
     * @return Corresponding string.
     */
    inline static std::string coordStr(const coord pos)
    {
        return std::string(1, pos.second + 'A') + std::string(1, pos.first + '1');
    }
    /**
     * Check if a coordinate is valid.
     * @param pos: The coordinate.
     * @return If it is valid.
     */
    inline static bool checkCoord(const coord& pos)
    {
        return 0 <= pos.first && pos.first < ROW && 0 <= pos.second && pos.second < COL;
    }
    /**
     * Get the name of player on a side.
     * @param side: Needed side.
     * @return Player's name.
     */
    inline static std::string getPlayer(int side)
    {
        return side ? std::string("Black") : std::string("White");
    }

public:
    /**
     * Constructor for the class.
     * @param ostr: An ostream object where the output flows to.
     */
    explicit ChessBoard(std::ostream& ostr=std::cout);
    /**
     * Deconstructor.
     */
    ~ChessBoard();
    /**
     * Reset the whole board.
     */
    void resetBoard();
    /**
     * Interface function. Submit a movement with two two-char strings representing the source and destination.
     * @param src: The source(e.g. "D2").
     * @param dst: The destination(e.g. "D4").
     */
    void submitMove(std::string src, std::string dst);
    /**
     * Interface function. Submit a pawn promotion with a string representing the promoted type.
     * @param type: One of "queen", "rook", "knight" and "bishop".
     */
    void submitPromotion(std::string type);
    /**
     * Interface function. Draw the board, either in simple form or cli form.
     * @param simple: Whether this is simple draw.
     */
    void drawBoard(bool simple=false);
    /**
     * Get a piece at a position.
     * @param pos: Designated position.
     * @return The pointer pointing to the piece, can be nullptr.
     */
    inline Piece* getPiece(coord pos)
    {
        return m_board[pos.first][pos.second];
    }
    /**
     * Get the pawn of a side which can be taken by a en-passant.
     * @param side: The side.
     * @return The pointer pointing to pawn which might be taken by a en-passant, can be nullptr.
     */
    inline Piece* getPassantPawn(int side)
    {
        return m_passant_pawn[side];
    }

private:
    /**
     * Try to submit a movement, and then rollback.
     * If it is a valid movement, returning either the piece which is going to be taken,
     * or the moving piece, if none other pieces will be take.
     * Else, return nullptr.
     * @param pos: The destination coordinate.
     * @param piece: The moving piece.
     * @return A pointer pointing to the moving piece or the taken piece.
     */
    Piece* dryrunMove(coord pos, Piece* piece);
    /**
     * Swap the current player and check if the current player is in check, checkmate or stalemate.
     */
    void swapPlayer();
    /**
     * Check if a castling is valid.
     * @param king: The moving king.
     * @param king_dst: King's destination.
     * @return If it is valid.
     */
    bool castlingCheck(Piece *king, coord king_dst);
    /**
     * Check if a player is in check or checkmate.
     * @param side: The player needed to check.
     * @return The result.
     */
    bool checkCheck(int side);
    /**
     * Check if a player is in stalemate or checkmate.
     * @param side: The player needed to check.
     * @return The result.
     */
    bool mateCheck(int side);
    /**
     * Set a piece to a position.
     * Note, the function does not delete the previous piece at the position, if there is any.
     * @param pos: The position.
     * @param piece: The piece.
     */
    inline void setPiece(coord pos, Piece* piece)
    {
        m_board[pos.first][pos.second] = piece;
    }

public:
    // Number of sides(players).
    static const int SIDE = 2;
    // Symbol for different sids.
    static const int WHITE = 0, BLACK = 1, UNKNOWN = -1;
    // Size of the board.
    static const int ROW = 8, COL = 8;
    // Symbol for different status.
    static const int NORMAL = 0, CHECK = 1, STALEMATE = 2, CHECKMATE = 3;

private:
    // Current winner.
    int m_winner;
    // Current playing side.
    int m_side;
    // Current status for the current player.
    int m_status;
    // The chess board containing piece pointers.
    Piece* m_board[ROW][COL];
    // Pointers to the kings.
    Piece* m_king[SIDE];
    // Pointers to the pawns which can be taken by an en-passent, if any.
    Piece* m_passant_pawn[SIDE];
    // Pointers to the pawns needed to be promoted, if any.
    Piece* m_promotion_pawn[SIDE];
    // Reference of output stream.
    std::ostream& m_ostr;
};

#endif
