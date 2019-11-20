#ifndef _PIECE_H_
#define _PIECE_H_

#include <string>

typedef std::pair<int, int> coord;

class ChessBoard;

class Piece
{
public:
    Piece(ChessBoard* board, int side, coord pos):
        m_board(board), m_side(side), m_pos(pos), m_moved(false)
    {
    }
    virtual ~Piece()
    {
    }
    virtual std::string getName();
    inline ChessBoard* getBoard()
    {
        return m_board;
    }
    inline int getSide()
    {
        return m_side;
    }
    inline coord getPos()
    {
        return m_pos;
    }
    inline void setPos(coord pos)
    {
        m_pos = pos;
        return;
    }
    inline bool getMoved()
    {
        return m_moved;
    }
    inline void setMoved(bool moved)
    {
        m_moved = moved;
        return;
    }
    bool pathCheck(coord pos);
    virtual Piece* pieceCheck(coord pos);
    virtual bool isPawn();
    virtual char getSymbol() = 0;

protected:
    ChessBoard* m_board;
    int m_side;
    coord m_pos;
    bool m_moved;
};

class King: public Piece
{
public:
    King(ChessBoard* board, int side, coord pos):
        Piece(board, side, pos)
    {
    }
    virtual ~King()
    {
    }
    virtual std::string getName();
    virtual Piece* pieceCheck(coord pos);
    virtual char getSymbol();
};

class Rook: public Piece
{
public:
    Rook(ChessBoard* board, int side, coord pos):
        Piece(board, side, pos)
    {
    }
    virtual ~Rook()
    {
    }
    virtual std::string getName();
    virtual Piece* pieceCheck(coord pos);
    virtual char getSymbol();
};

class Bishop: public Piece
{
public:
    Bishop(ChessBoard* board, int side, coord pos):
        Piece(board, side, pos)
    {
    }
    virtual ~Bishop()
    {
    }
    virtual std::string getName();
    virtual Piece* pieceCheck(coord pos);
    virtual char getSymbol();
};

class Queen: public Piece
{
public:
    Queen(ChessBoard* board, int side, coord pos):
        Piece(board, side, pos)
    {
    }
    virtual ~Queen()
    {
    }
    virtual std::string getName();
    virtual Piece* pieceCheck(coord pos);
    virtual char getSymbol();
};

class Knight: public Piece
{
public:
    Knight(ChessBoard* board, int side, coord pos):
        Piece(board, side, pos)
    {
    }
    virtual ~Knight()
    {
    }
    virtual std::string getName();
    virtual Piece* pieceCheck(coord pos);
    virtual char getSymbol();
};

class Pawn: public Piece
{
public:
    Pawn(ChessBoard* board, int side, coord pos):
        Piece(board, side, pos), m_direct(side ? -1 : 1)
    {
    }
    virtual ~Pawn()
    {
    }
    virtual std::string getName();
    virtual bool isPawn();
    virtual Piece* pieceCheck(coord pos);
    virtual char getSymbol();
private:
    int m_direct;
};

#endif
