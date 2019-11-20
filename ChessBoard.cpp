#include "ChessBoard.h"

#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

ChessBoard::ChessBoard()
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
    memset(m_passant_pawn, 0, sizeof(m_passant_pawn));
    memset(m_king, 0, sizeof(m_king));
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

    // TODO: assign King pointers.
    cout << "A new chess game is started!" << endl;
    return;
}

void ChessBoard::submitMove(const std::string src, const std::string dst)
{
    if (m_winner != UNKNOWN)
    {
        cout << "The game is already over" << endl;
        return;
    }

    coord s = strCoord(src), d = strCoord(dst);
    if (!checkCoord(s))
    {
        cout << src << " is not a valid position!" << endl;
        return;
    }
    else if (!checkCoord(d))
    {
        cout << dst << " is not a valid position!" << endl;
        return;
    }

    Piece* piece = getPiece(s);
    if (!piece)
    {
        cout << "There is no piece at position " << src << "!" << endl;
        return;
    }
    if (piece->getSide() != m_side)
    {
        cout << "It is not " << getPlayer(piece->getSide()) << "’s turn to move!" << endl;
        return;
    }

    // TODO: Add castling judgement here.
    Piece* obj = dryrunMove(d, piece);
    if (!obj)
    {
        cout << piece->getName() << " cannot move to " << dst << "!" << endl;
        return;
    }

    cout << piece->getName() << " moves from " << src << " to " + dst;
    if (obj != piece)
    {
        cout << " taking " << obj->getName();
        setPiece(obj->getPos(), nullptr);
        delete obj;
    }
    setPiece(d, piece);
    piece->setPos(d);
    piece->setMoved(true);
    setPiece(s, nullptr);
    cout << endl;

    // drawBoard();

    if (piece->isPawn() && abs(s.first - d.first) == 2)
        m_passant_pawn[m_side] = piece;
    else
        m_passant_pawn[m_side] = nullptr;

    m_side = 1 - m_side;

    bool check = checkCheck(m_side);
    // drawBoard();
    bool mate = mateCheck(m_side);
    // drawBoard();
    if (check && mate)
    {
        m_winner = 1 - m_side;
        cout << getPlayer(m_side) << " is in checkmate" << endl;
    }
    else if (check)
        cout << getPlayer(m_side) << " is in check" << endl;
    else if (mate)
    {
        m_winner = 1 - m_side;
        cout << getPlayer(m_side) << " is in stalemate" << endl;
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

bool ChessBoard::checkCheck(int side)
{
    coord tar = getKing(side)->getPos();
    // cout << side << " " << tar.first << " " << tar.second << endl;
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

void ChessBoard::drawBoard()
{
    cout << " |A B C D E F G H| " << endl;
    cout << "-------------------" << endl;
    for (int r = ROW - 1; r >= 0; r --)
    {
        cout << (char)('1' + r);
        for (int c = 0; c < COL; c ++)
            cout << '|' << (!getPiece(make_pair(r, c)) ? ' ' : getPiece(make_pair(r, c))->getSymbol());
        cout << '|' << (char)('1' + r) << endl;
        cout << "-------------------" << endl;
    }
    cout << " |A B C D E F G H| " << endl;
    return;
}