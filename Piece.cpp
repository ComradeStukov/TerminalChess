#include "Piece.h"
#include "ChessBoard.h"

#include <cmath>

using namespace std;

string Piece::getName()
{
    return m_board->getPlayer(m_side) + "'s ";
}

bool Piece::pathCheck(coord pos)
{
    int dr = (pos.first == m_pos.first) ? 0 : (pos.first > m_pos.first ? 1 : -1);
    int dc = (pos.second == m_pos.second) ? 0 : (pos.second > m_pos.second ? 1 : -1);
    int nr = m_pos.first + dr, nc = m_pos.second + dc;
    while (pos.first != nr || pos.second != nc)
    {
        if (m_board->getPiece(make_pair(nr, nc)))
            return false;
        nr += dr, nc += dc;
    }
    return true;
}

bool Piece::isPawn()
{
    return false;
}

Piece* Piece::pieceCheck(coord pos)
{
    if (!ChessBoard::checkCoord(pos))
        return nullptr;
    Piece* p = m_board->getPiece(pos);
    if (p && p->m_side == m_side)
        return nullptr;
    return this;
}

string King::getName()
{
    return Piece::getName() + "king";
}

Piece* King::pieceCheck(coord pos)
{
    if (!Piece::pieceCheck(pos))
        return nullptr;
    else if (max(abs(pos.first - m_pos.first), abs(pos.second - m_pos.second)) > 1)
        return nullptr;
    Piece* p = m_board->getPiece(pos);
    return p ? p : (Piece*)this;
}

char King::getSymbol()
{
    return m_side ? 'k' : 'K';
}

std::string Rook::getName()
{
    return Piece::getName() + "rook";
}

Piece* Rook::pieceCheck(coord pos)
{
    if (!Piece::pieceCheck(pos))
        return nullptr;
    else if (pos.first != m_pos.first && pos.second != m_pos.second)
        return nullptr;
    if (!pathCheck(pos))
        return nullptr;
    Piece* p = m_board->getPiece(pos);
    return p ? p : (Piece*)this;
}

char Rook::getSymbol()
{
    return m_side ? 'r' : 'R';
}

std::string Bishop::getName()
{
    return Piece::getName() + "bishop";
}

Piece* Bishop::pieceCheck(coord pos)
{
    if (!Piece::pieceCheck(pos))
        return nullptr;
    else if (pos.first + pos.second != m_pos.first + m_pos.second &&
             pos.first - pos.second != m_pos.first - m_pos.second)
        return nullptr;
    if (!pathCheck(pos))
        return nullptr;
    Piece* p = m_board->getPiece(pos);
    return p ? p : (Piece*)this;
}

char Bishop::getSymbol()
{
    return m_side ? 'b' : 'B';
}

std::string Queen::getName()
{
    return Piece::getName() + "queen";
}

Piece* Queen::pieceCheck(coord pos)
{
    if (!Piece::pieceCheck(pos))
        return nullptr;
    else if (pos.first != m_pos.first &&
             pos.second != m_pos.second &&
             pos.first + pos.second != m_pos.first + m_pos.second &&
             pos.first - pos.second != m_pos.first - m_pos.second)
        return nullptr;
    if (!pathCheck(pos))
        return nullptr;
    Piece* p = m_board->getPiece(pos);
    return p ? p : (Piece*)this;
}

char Queen::getSymbol()
{
    return m_side ? 'q' : 'Q';
}

std::string Knight::getName()
{
    return Piece::getName() + "knight";
}

Piece* Knight::pieceCheck(coord pos)
{
    if (!Piece::pieceCheck(pos))
        return nullptr;
    else if (!(
        (abs(pos.first - m_pos.first) == 2 && abs(pos.second - m_pos.second) == 1) ||
        (abs(pos.first - m_pos.first) == 1 && abs(pos.second - m_pos.second) == 2)
    ))
        return nullptr;
    Piece* p = m_board->getPiece(pos);
    return p ? p : (Piece*)this;
}

char Knight::getSymbol()
{
    return m_side ? 'c' : 'C';
}

std::string Pawn::getName()
{
    return Piece::getName() + "pawn";
}

Piece* Pawn::pieceCheck(coord pos)
{
    if ((pos.first - m_pos.first) * m_direct <= 0 ||
        (pos.first - m_pos.first) * m_direct > 2 ||
        abs(pos.second - m_pos.second) > 1)
        return nullptr;
    else if ((pos.first - m_pos.first) * m_direct == 1)
    {
        if (pos.second == m_pos.second)
            return m_board->getPiece(pos) ? nullptr : (Piece*)this;
        else
        {
            Piece* obj = m_board->getPiece(pos);
            if (obj)
                return obj;
            obj = m_board->getPiece(make_pair(m_pos.first, pos.second));
            if (obj == m_board->getPassantPawn(1 - m_side))
                return obj;
            return nullptr;
        }
    }
    else if ((pos.first - m_pos.first) * m_direct == 2 && pos.second == m_pos.second)
    {
        if (m_board->getPiece(pos) || m_moved || !pathCheck(pos))
            return nullptr;
        return this;
    }
    return nullptr;
}

bool Pawn::isPawn()
{
    return true;
}

char Pawn::getSymbol()
{
    return m_side ? 'p' : 'P';
}