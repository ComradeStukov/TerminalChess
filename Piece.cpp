/***********************************************************************
* Piece.cpp Implementation of different piece class for chess game     *
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

#include "Piece.h"
#include "ChessBoard.h"

#include <cmath>

using namespace std;


string Piece::getName()
{
    // Get prefix of a piece.
    return m_board->getPlayer(m_side) + "'s ";
}

/*
 * This function assumes that destination is on the same row, same column or a same diagonal with the piece.
 */
bool Piece::pathCheck(coord pos)
{
    // Get the direction of the movement (e.g., dr = -1, dc = 0 means move downward.)
    int dr = (pos.first == m_pos.first) ? 0 : (pos.first > m_pos.first ? 1 : -1);
    int dc = (pos.second == m_pos.second) ? 0 : (pos.second > m_pos.second ? 1 : -1);

    // Go through the whole path
    int nr = m_pos.first + dr, nc = m_pos.second + dc;
    while (pos.first != nr || pos.second != nc)
    {
        // If there is a piece on the path, return false.
        if (m_board->getPiece(make_pair(nr, nc)))
            return false;
        nr += dr, nc += dc;
    }

    return true;
}

/*
 * This function is expected to be override by the Pawn class.
 */
bool Piece::isPawn()
{
    return false;
}

/*
 * This function is a general precondition check for movements of all pieces.
 * It is expected to be override by, and be called in every son classes.
 */
Piece* Piece::pieceCheck(coord pos)
{
    // The coordinate must be valid.
    if (!ChessBoard::checkCoord(pos))
        return nullptr;

    // There should be no pieces which is on the same side with the moving piece.
    Piece* p = m_board->getPiece(pos);
    if (p && p->m_side == m_side)
        return nullptr;
    return this;
}

string King::getName()
{
    return Piece::getName() + "King";
}

Piece* King::pieceCheck(coord pos)
{
    // Check the precondition.
    if (!Piece::pieceCheck(pos))
        return nullptr;

    // The king must only move to eight grids next to it.
    else if (max(abs(pos.first - m_pos.first), abs(pos.second - m_pos.second)) > 1)
        return nullptr;

    // Take any pieces, if necessary.
    Piece* p = m_board->getPiece(pos);
    return p ? p : (Piece*)this;
}

char King::getSymbol()
{
    return m_side ? 'k' : 'K';
}

std::string Rook::getName()
{
    return Piece::getName() + "Rook";
}

Piece* Rook::pieceCheck(coord pos)
{
    // Check the precondition.
    if (!Piece::pieceCheck(pos))
        return nullptr;

    // The destination must be on the same row or same column.
    else if (pos.first != m_pos.first && pos.second != m_pos.second)
        return nullptr;

    // The path must be empty.
    if (!pathCheck(pos))
        return nullptr;

    // Take any pieces, if necessary.
    Piece* p = m_board->getPiece(pos);
    return p ? p : (Piece*)this;
}

char Rook::getSymbol()
{
    return m_side ? 'r' : 'R';
}

std::string Bishop::getName()
{
    return Piece::getName() + "Bishop";
}

Piece* Bishop::pieceCheck(coord pos)
{
    // Check the precondition.
    if (!Piece::pieceCheck(pos))
        return nullptr;

    // The destination must be on a same diagonal with the piece.
    else if (pos.first + pos.second != m_pos.first + m_pos.second &&
             pos.first - pos.second != m_pos.first - m_pos.second)
        return nullptr;

    // And the path must be empty.
    if (!pathCheck(pos))
        return nullptr;

    // Take any pieces, if necessary.
    Piece* p = m_board->getPiece(pos);
    return p ? p : (Piece*)this;
}

char Bishop::getSymbol()
{
    return m_side ? 'b' : 'B';
}

std::string Queen::getName()
{
    return Piece::getName() + "Queen";
}

Piece* Queen::pieceCheck(coord pos)
{
    // Check the precondition.
    if (!Piece::pieceCheck(pos))
        return nullptr;

    // The destination must be on the same row, same column or a same diagonal with the piece.
    else if (pos.first != m_pos.first &&
             pos.second != m_pos.second &&
             pos.first + pos.second != m_pos.first + m_pos.second &&
             pos.first - pos.second != m_pos.first - m_pos.second)
        return nullptr;

    // And the path must be empty.
    if (!pathCheck(pos))
        return nullptr;

    // Take any pieces, if necessary.
    Piece* p = m_board->getPiece(pos);
    return p ? p : (Piece*)this;
}

char Queen::getSymbol()
{
    return m_side ? 'q' : 'Q';
}

std::string Knight::getName()
{
    return Piece::getName() + "Knight";
}

Piece* Knight::pieceCheck(coord pos)
{
    // Check the precondition.
    if (!Piece::pieceCheck(pos))
        return nullptr;

    // The knight must move in 'L' shape.
    else if (!(
        (abs(pos.first - m_pos.first) == 2 && abs(pos.second - m_pos.second) == 1) ||
        (abs(pos.first - m_pos.first) == 1 && abs(pos.second - m_pos.second) == 2)
    ))
        return nullptr;

    // Take any pieces, if necessary.
    Piece* p = m_board->getPiece(pos);
    return p ? p : (Piece*)this;
}

char Knight::getSymbol()
{
    return m_side ? 'n' : 'N';
}

std::string Pawn::getName()
{
    return Piece::getName() + "Pawn";
}

Piece* Pawn::pieceCheck(coord pos)
{
    // Check the precondition.
    if (!Piece::pieceCheck(pos))
        return nullptr;

    // The pawn can only move to (r + 1, c), (r + 1, c + 1), (r + 1, c - 1) or (r + 2, c)
    else if ((pos.first - m_pos.first) * m_direct <= 0 ||
        (pos.first - m_pos.first) * m_direct > 2 ||
        abs(pos.second - m_pos.second) > 1)
        return nullptr;

    // If the pawn moves one line forward.
    else if ((pos.first - m_pos.first) * m_direct == 1)
    {
        // If the pawn is moving directly forward, it can take nothing.
        if (pos.second == m_pos.second)
            return m_board->getPiece(pos) ? nullptr : (Piece*)this;

        // Else, it must take something.
        else
        {
            Piece* obj = m_board->getPiece(pos);
            if (obj)
                return obj;

            // If the destination is empty, check if the movement is an en-passant.
            obj = m_board->getPiece(make_pair(m_pos.first, pos.second));
            if (obj == m_board->getPassantPawn(1 - m_side))
                return obj;
            return nullptr;
        }
    }

    // If the pawn is moving two rows forward, it must only move, and it must not be moved before.
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