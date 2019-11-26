/***********************************************************************
* Piece.h Declaration of different piece class for chess game          *
*                                                                      *
* This file is part of Terminal Chess.                                 *
*                                                                      *
* Copyright 2019-2020 SBofGaySchoolBuPaAnything                        *
*                                                                      *
* Terminal Chess is free software under LGPLv3.                        *
*                                                                      *
* You should have received a copy of the GNU Lesser General Public     *
* License along with this program.  If not, see                        *
* <http://www.gnu.org/licenses/>.                                      *
***********************************************************************/

#ifndef _PIECE_H_
#define _PIECE_H_

#include <string>

// Using pair<int, int> to represent a coordinate.
typedef std::pair<int, int> coord;

// Forward declaration the ChessBoard class.
class ChessBoard;

/**
 * The abstract class representing a general chess piece.
 */
class Piece
{
public:
    /**
     * Constructor.
     * @param board: A pointer pointing to the board.
     * @param side: Which side the piece belongs to.
     * @param pos: Initial position.
     */
    Piece(ChessBoard* board, int side, coord pos):
        m_board(board), m_side(side), m_pos(pos), m_moved(false)
    {
    }
    /**
     * Deconstructor.
     */
    virtual ~Piece() = default;
    /**
     * Get the name of the piece, including side and type.
     * @return The name.
     */
    virtual std::string getName();
    /**
     * Get the side of the piece.
     * @return The side.
     */
    inline int getSide()
    {
        return m_side;
    }
    /**
     * Get current position of the piece.
     * @return The current position.
     */
    inline coord getPos()
    {
        return m_pos;
    }
    /**
     * Set current position for the piece.
     * @param pos: The current position.
     */
    inline void setPos(coord pos)
    {
        m_pos = pos;
    }
    /**
     * Get if the piece has been moved.
     * @return The result.
     */
    inline bool getMoved()
    {
        return m_moved;
    }
    /**
     * Set if the piece is moved.
     * @param moved: If the piece is moved.
     */
    inline void setMoved(bool moved)
    {
        m_moved = moved;
    }
    /**
     * Check whether there is any other piece on the direct path to the destination(excluded).
     * @param pos Destination.
     * @return The result.
     */
    bool pathCheck(coord pos);
    /**
     * Check whether the piece can move to the designated position.
     * Note: This check does not consider the situation of the king after the movement.
     * @param pos: The position.
     * @return nullptr if this is invalid movement,
     * or a pointer to another piece, if any piece is going to be taken,
     * or a pointer to the piece itself, if none piece is going to be take.
     */
    virtual Piece* pieceCheck(coord pos);
    /**
     * Check if the piece is a pawn.
     * @return The result
     */
    virtual bool isPawn();
    /**
     * Get the one-char symbol of the piece.
     * @return The symbol.
     */
    virtual char getSymbol() = 0;

protected:
    // The chess board the piece is on.
    ChessBoard* m_board;
    // Which side the piece belongs to.
    int m_side;
    // The current position.
    coord m_pos;
    // If the piece has been moved.
    bool m_moved;
};

/**
 * Derived class representing a King.
 * For detailed information, please see the super class Piece.
 */
class King: public Piece
{
public:
    King(ChessBoard* board, int side, coord pos):
        Piece(board, side, pos)
    {
    }
    ~King() override = default;
    std::string getName() override;
    Piece* pieceCheck(coord pos) override;
    char getSymbol() override;
};

/**
 * Derived class representing a King.
 * For detailed information, please see the super class Piece.
 */
class Rook: public Piece
{
public:
    Rook(ChessBoard* board, int side, coord pos):
        Piece(board, side, pos)
    {
    }
    ~Rook() override = default;
    std::string getName() override;
    Piece* pieceCheck(coord pos) override;
    char getSymbol() override;
};

/**
 * Derived class representing a King.
 * For detailed information, please see the super class Piece.
 */
class Bishop: public Piece
{
public:
    Bishop(ChessBoard* board, int side, coord pos):
        Piece(board, side, pos)
    {
    }
    ~Bishop() override = default;
    std::string getName() override;
    Piece* pieceCheck(coord pos) override;
    char getSymbol() override;
};

/**
 * Derived class representing a King.
 * For detailed information, please see the super class Piece.
 */
class Queen: public Piece
{
public:
    Queen(ChessBoard* board, int side, coord pos):
        Piece(board, side, pos)
    {
    }
    ~Queen() override = default;
    std::string getName() override;
    Piece* pieceCheck(coord pos) override;
    char getSymbol() override;
};

/**
 * Derived class representing a King.
 * For detailed information, please see the super class Piece.
 */
class Knight: public Piece
{
public:
    Knight(ChessBoard* board, int side, coord pos):
        Piece(board, side, pos)
    {
    }
    ~Knight() override = default;
    std::string getName() override;
    Piece* pieceCheck(coord pos) override;
    char getSymbol() override;
};

/**
 * Derived class representing a King.
 * For detailed information, please see the super class Piece.
 */
class Pawn: public Piece
{
public:
    Pawn(ChessBoard* board, int side, coord pos):
        Piece(board, side, pos), m_direct(side ? -1 : 1)
    {
    }
    ~Pawn() override = default;
    std::string getName() override;
    bool isPawn() override;
    Piece* pieceCheck(coord pos) override;
    char getSymbol() override;
private:
    // The direct (up or down) which the pawn can move.
    int m_direct;
};

#endif
