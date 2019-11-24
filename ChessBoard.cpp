#include "ChessBoard.h"

#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

ChessBoard::ChessBoard(ostream& ostr):
    m_ostr(ostr)
{
    memset(m_board, 0, sizeof(m_board));
    resetBoard();
}

ChessBoard::~ChessBoard()
{
    for (int r = 0; r < ROW; r ++)
        for (int c = 0; c < COL; c ++)
            delete m_board[r][c];
}

void ChessBoard::resetBoard()
{
    for (int r = 0; r < ROW; r ++)
        for (int c = 0; c < COL; c ++)
            delete m_board[r][c];
    memset(m_board, 0, sizeof(m_board));
    memset(m_king, 0, sizeof(m_king));
    memset(m_passant_pawn, 0, sizeof(m_passant_pawn));
    memset(m_promotion_pawn, 0, sizeof(m_promotion_pawn));
    m_status = NORMAL;
    m_side = WHITE;
    m_winner = UNKNOWN;

    m_king[WHITE] = new King(this, WHITE, strCoord("E1"));
    m_king[BLACK] = new King(this, BLACK, strCoord("E8"));

    setPiece(strCoord("A1"), new Rook(this, WHITE, strCoord("A1")));
    setPiece(strCoord("B1"), new Knight(this, WHITE, strCoord("B1")));
    setPiece(strCoord("C1"), new Bishop(this, WHITE, strCoord("C1")));
    setPiece(strCoord("D1"), new Queen(this, WHITE, strCoord("D1")));
    setPiece(strCoord("E1"), m_king[WHITE]);
    setPiece(strCoord("F1"), new Bishop(this, WHITE, strCoord("F1")));
    setPiece(strCoord("G1"), new Knight(this, WHITE, strCoord("G1")));
    setPiece(strCoord("H1"), new Rook(this, WHITE, strCoord("H1")));

    setPiece(strCoord("A2"), new Pawn(this, WHITE, strCoord("A2")));
    setPiece(strCoord("B2"), new Pawn(this, WHITE, strCoord("B2")));
    setPiece(strCoord("C2"), new Pawn(this, WHITE, strCoord("C2")));
    setPiece(strCoord("D2"), new Pawn(this, WHITE, strCoord("D2")));
    setPiece(strCoord("E2"), new Pawn(this, WHITE, strCoord("E2")));
    setPiece(strCoord("F2"), new Pawn(this, WHITE, strCoord("F2")));
    setPiece(strCoord("G2"), new Pawn(this, WHITE, strCoord("G2")));
    setPiece(strCoord("H2"), new Pawn(this, WHITE, strCoord("H2")));

    setPiece(strCoord("A8"), new Rook(this, BLACK, strCoord("A8")));
    setPiece(strCoord("B8"), new Knight(this, BLACK, strCoord("B8")));
    setPiece(strCoord("C8"), new Bishop(this, BLACK, strCoord("C8")));
    setPiece(strCoord("D8"), new Queen(this, BLACK, strCoord("D8")));
    setPiece(strCoord("E8"), m_king[BLACK]);
    setPiece(strCoord("F8"), new Bishop(this, BLACK, strCoord("F8")));
    setPiece(strCoord("G8"), new Knight(this, BLACK, strCoord("G8")));
    setPiece(strCoord("H8"), new Rook(this, BLACK, strCoord("H8")));

    setPiece(strCoord("A7"), new Pawn(this, BLACK, strCoord("A7")));
    setPiece(strCoord("B7"), new Pawn(this, BLACK, strCoord("B7")));
    setPiece(strCoord("C7"), new Pawn(this, BLACK, strCoord("C7")));
    setPiece(strCoord("D7"), new Pawn(this, BLACK, strCoord("D7")));
    setPiece(strCoord("E7"), new Pawn(this, BLACK, strCoord("E7")));
    setPiece(strCoord("F7"), new Pawn(this, BLACK, strCoord("F7")));
    setPiece(strCoord("G7"), new Pawn(this, BLACK, strCoord("G7")));
    setPiece(strCoord("H7"), new Pawn(this, BLACK, strCoord("H7")));

    m_ostr << "A new chess game is started!" << endl;
    return;
}

void ChessBoard::submitMove(const std::string src, const std::string dst)
{
    if (m_winner != UNKNOWN)
    {
        m_ostr << "The game is already over!" << endl;
        return;
    }
    else if (m_promotion_pawn[m_side])
    {
        m_ostr << getPlayer(m_side) << " has a pawn to be promoted!" << endl;
        return;
    }

    coord s = strCoord(src), d = strCoord(dst);
    if (!checkCoord(s))
    {
        m_ostr << src << " is not a valid position!" << endl;
        return;
    }
    else if (!checkCoord(d))
    {
        m_ostr << dst << " is not a valid position!" << endl;
        return;
    }

    Piece* piece = getPiece(s);
    if (!piece)
    {
        m_ostr << "There is no piece at position " << src << "!" << endl;
        return;
    }
    if (piece->getSide() != m_side)
    {
        m_ostr << "It is not " << getPlayer(piece->getSide()) << "'s turn to move!" << endl;
        return;
    }

    if (!castlingCheck(piece, d))
    {
        Piece *obj = dryrunMove(d, piece);
        if (!obj)
        {
            m_ostr << piece->getName() << " cannot move to " << dst << "!" << endl;
            return;
        }

        m_ostr << piece->getName() << " moves from " << src << " to " + dst;
        if (obj != piece)
        {
            m_ostr << " taking " << obj->getName();
            setPiece(obj->getPos(), nullptr);
            delete obj;
        }
        setPiece(d, piece);
        piece->setPos(d);
        piece->setMoved(true);
        setPiece(s, nullptr);
        m_ostr << endl;
    }

    if (piece->isPawn() && abs(s.first - d.first) == 2)
        m_passant_pawn[m_side] = piece;
    else
        m_passant_pawn[m_side] = nullptr;

    if (piece->isPawn() && (piece->getPos().first == (1 - m_side) * (ROW - 1)))
    {
        m_promotion_pawn[m_side] = piece;
        m_ostr << piece->getName() << " is going to be promoted" << endl;
        return;
    }

    swapPlayer();

    return;
}

void ChessBoard::submitPromotion(std::string type)
{
    if (m_winner != UNKNOWN)
    {
        m_ostr << "The game is already over!" << endl;
        return;
    }
    if (!m_promotion_pawn[m_side])
    {
        m_ostr << getPlayer(m_side) << " has no pawn to be promoted!" << endl;
        return;
    }

    Piece* new_piece = nullptr;
    if (type == "rook")
        new_piece = new Rook(this, m_side, m_promotion_pawn[m_side]->getPos());
    else if (type == "knight")
        new_piece = new Knight(this, m_side, m_promotion_pawn[m_side]->getPos());
    else if (type == "bishop")
        new_piece = new Bishop(this, m_side, m_promotion_pawn[m_side]->getPos());
    else if (type == "queen")
        new_piece = new Queen(this, m_side, m_promotion_pawn[m_side]->getPos());

    if (!new_piece)
    {
        m_ostr << type << " is not a valid type!" << endl;
        return;
    }

    m_ostr << m_promotion_pawn[m_side]->getName() << " at " << coordStr(m_promotion_pawn[m_side]->getPos());

    setPiece(m_promotion_pawn[m_side]->getPos(), nullptr);
    delete m_promotion_pawn[m_side];
    m_promotion_pawn[m_side] = nullptr;
    setPiece(new_piece->getPos(), new_piece);

    m_ostr << " get promoted and become " << new_piece->getName() << endl;

    swapPlayer();

    return;
}

void ChessBoard::drawBoard(bool simple)
{
    if (!simple)
    {
        m_ostr << "Current Player: " << getPlayer(m_side) << endl;
        m_ostr << "Status: ";
        switch (m_status)
        {
            case CHECK:
            {
                m_ostr << "Checked" << endl;
                break;
            }
            case STALEMATE:
            {
                m_ostr << "Stalemated" << endl;
                break;
            }
            case CHECKMATE:
            {
                m_ostr << "Checkmated" << endl;
                break;
            }
            default:
                m_ostr << "Normal" << endl;
        }
        m_ostr << "Promoting: ";
        if (m_promotion_pawn[m_side])
            m_ostr << "Yes, " << coordStr(m_promotion_pawn[m_side]->getPos()) << endl;
        else
            m_ostr << "None" << endl;
        m_ostr << endl;
        m_ostr << "  A B C D E F G H  " << endl;
        m_ostr << " +-+-+-+-+-+-+-+-+ " << endl;
        for (int r = ROW - 1; r >= 0; r--)
        {
            m_ostr << (char) ('1' + r);
            for (int c = 0; c < COL; c++)
                m_ostr << '|' << (!getPiece(make_pair(r, c)) ? ' ' : getPiece(make_pair(r, c))->getSymbol());
            m_ostr << '|' << (char) ('1' + r) << endl;
            m_ostr << " +-+-+-+-+-+-+-+-+ " << endl;
        }
        m_ostr << "  A B C D E F G H  " << endl;
    }
    else
    {
        m_ostr << m_side << " " << m_status << " " << (m_promotion_pawn[m_side] ? 1 : 0) << endl;
        for (int r = ROW - 1; r >= 0; r--)
        {
            for (int c = 0; c < COL; c++)
                m_ostr << (!getPiece(make_pair(r, c)) ? '.' : getPiece(make_pair(r, c))->getSymbol());
            m_ostr << endl;
        }
    }
    return;
}

Piece* ChessBoard::dryrunMove(coord dst, Piece* piece)
{
    Piece* obj = piece->pieceCheck(dst);
    if (!obj)
        return nullptr;
    else if (obj == piece)
        obj = nullptr;

    bool piece_moved = piece->getMoved();
    coord piece_src = piece->getPos(), obj_src = obj ? obj->getPos() : make_pair(-1, -1);

    if (obj)
        setPiece(obj_src, nullptr);
    setPiece(dst, piece);
    piece->setPos(dst);
    piece->setMoved(true);
    setPiece(piece_src, nullptr);

    bool res = !checkCheck(m_side);

    setPiece(piece_src, piece);
    piece->setMoved(piece_moved);
    piece->setPos(piece_src);
    setPiece(dst, nullptr);
    if (obj)
        setPiece(obj_src, obj);

    if (!res)
        return nullptr;
    return obj ? obj : piece;
}

void ChessBoard::swapPlayer()
{
    m_side = 1 - m_side;
    m_status = NORMAL;

    bool check = checkCheck(m_side), mate = mateCheck(m_side);
    if (check && mate)
    {
        m_status = CHECKMATE;
        m_winner = 1 - m_side;
        m_ostr << getPlayer(m_side) << " is in checkmate" << endl;
    }
    else if (check)
    {
        m_status = CHECK;
        m_ostr << getPlayer(m_side) << " is in check" << endl;
    }
    else if (mate)
    {
        m_status = STALEMATE;
        m_winner = 1 - m_side;
        m_ostr << getPlayer(m_side) << " is in stalemate" << endl;
    }

    return;
}

bool ChessBoard::castlingCheck(Piece *king, coord king_dst)
{
    if (king != m_king[m_side] ||
        king_dst.first != king->getPos().first ||
        abs(king_dst.second - king->getPos().second) != 2 ||
        king->getMoved())
        return false;
    int d = king_dst.second > king->getPos().second ? 1 : -1;
    int r = king->getPos().first, c = king->getPos().second + d;
    while (0 < c && c < COL - 1)
    {
        if (getPiece(make_pair(r, c)))
            return false;
        c += d;
    }
    Piece* rook = getPiece(make_pair(r, c));
    if (!rook || rook->getMoved())
        return false;
    Piece* p;
    for (r = 0; r < ROW; r++)
        for (c = 0; c < COL; c++)
            if ((p = getPiece(make_pair(r, c))) && p->getSide() == 1 - m_side)
                for (int i = 0; i < 3; i++)
                    if (p->pieceCheck(make_pair(king->getPos().first, king->getPos().second + i * d)))
                        return false;
    coord king_src = king->getPos(), rook_src = rook->getPos(), rook_dst = king->getPos();
    rook_dst.second = rook_dst.second + d;

    setPiece(king_dst, king);
    king->setPos(king_dst);
    king->setMoved(true);
    setPiece(king_src, nullptr);

    setPiece(rook_dst, rook);
    rook->setPos(rook_dst);
    rook->setMoved(true);
    setPiece(rook_src, nullptr);

    m_ostr << king->getName() << " castling from " << coordStr(king_src) << " to " << coordStr(king_dst) << " with ";
    m_ostr << rook->getName() << " from " << coordStr(rook_src) << " to " << coordStr(rook_dst) << endl;

    return true;
}

bool ChessBoard::checkCheck(int side)
{
    coord tar = m_king[side]->getPos();
    // m_ostr << side << " " << tar.first << " " << tar.second << endl;
    Piece* p;
    for (int r = 0; r < ROW; r++)
        for (int c = 0; c < COL; c++)
            if ((p = getPiece(make_pair(r, c))) && p->getSide() == 1 - side && p->pieceCheck(tar))
                return true;
    return false;
}

bool ChessBoard::mateCheck(int side)
{
    /*
     * Castling is not considered as a valid movement here.
     * But this does not influence the result.
     * Because if the Castling is available,
     * the two grid next to the king must be safe to move to.
     * Thus, if Castling is available, there are definitely other available moves.
     * So Castling is not needed to be checked.
     */
    Piece* p;
    for (int r = 0; r < ROW; r++)
        for (int c = 0; c < COL; c++)
            if ((p = getPiece(make_pair(r, c))) && p->getSide() == side)
                for (int i = 0; i < ROW; i++)
                    for (int j = 0; j < COL; j++)
                        if (dryrunMove(make_pair(i, j), p))
                            return false;
    return true;
}
