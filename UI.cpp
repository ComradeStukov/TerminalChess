#include "UI.h"

#include "ChessBoard.h"

#include <cctype>


void RecordView::appendStr(std::string str)
{
    if (str.back() != '\n')
        str.push_back('\n');
    unsigned int start = 0;
    for (unsigned int i = 0; i < str.length(); i ++)
    {
        if (str.at(i) == '\n')
        {
            if (i == start)
                append("~");
            else
                append(str.substr(start, i - start));
            start = i + 1;
        }
        else if (i - start == getWidth() - 2)
        {
            append(str.substr(start, i - start));
            start = i;
        }
    }
    return;
}

void RecordView::onKeyPress(finalcut::FKeyEvent* ev)
{
    ev->accept();
    return finalcut::FTextView::onKeyPress(ev);
}

void RecordView::onWheel(finalcut::FWheelEvent* ev)
{
    if (!ev || !scrollable())
        return;
    return finalcut::FTextView::onWheel(ev);
}

const char* View::PIECE[STYLE_NUM][PIECE_NUM][ChessBoard::SIDE] =
{
    {
        {"   _   \n  ( )  \n  / \\  ", "   _   \n  (#)  \n  /#\\  "},
        {"  uuu  \n  | |  \n  / \\  ", "  uuu  \n  |#|  \n  /#\\  "},
        {"  ,^.  \n (  '\\ \n |  \\  ", "  ,^.  \n (##'\\ \n |##\\  "},
        {"   O/  \n  ( )  \n  / \\  ", "   O/  \n  (#)  \n  /#\\  "},
        {"  WWW  \n  \\ /  \n  / \\  ", "  WWW  \n  \\#/  \n  /#\\  "},
        {"  _+_  \n  \\ /  \n  / \\  ", "  _#_  \n  \\#/  \n  /#\\  "}
    },
    {
        {"       \n WHITE \n PAWN  ", "       \n black \n pawn  "},
        {"       \n WHITE \n ROOK  ", "       \n black \n rook  "},
        {"       \n WHITE \nKNIGHT ", "       \n black \nknight "},
        {"       \n WHITE \nBISHOP ", "       \n black \nbishop "},
        {"       \n WHITE \n QUEEN ", "       \n black \n queen "},
        {"       \n WHITE \n KING  ", "       \n black \n king  "}
    }
};

const char* View::PIECE_NULL = "       \n       \n       ";

const char* View::PIECE_UNKNOWN = "       \n   ?   \n       ";

const char* View::COORD_ROW[ChessBoard::ROW] =
{
    "\n8\n ",
    "\n7\n ",
    "\n6\n ",
    "\n5\n ",
    "\n4\n ",
    "\n3\n ",
    "\n2\n ",
    "\n1\n ",
};

const char* View::COORD_COL[ChessBoard::COL] =
{
    "   A   ",
    "   B   ",
    "   C   ",
    "   D   ",
    "   E   ",
    "   F   ",
    "   G   ",
    "   H   ",
};

const char* View::HELP = ""
    "+--------+---------+---------+    +-------+----------------------+\n"
    "|        |  White  |  Black  |    |  Key  |      Operation       |\n"
    "+--------+---------+---------+    +-------+----------------------+\n"
    "|        |    _    |    _    |    |  Up   |  Move up the cursor  |\n"
    "|  Pawn  |   ( )   |   (#)   |    +-------+----------------------+\n"
    "|        |   / \\   |   /#\\   |    |  Down | Move down the cursor |\n"
    "+--------+---------+---------+    +-------+----------------------+\n"
    "|        |   uuu   |   uuu   |    |  Left | Move left the cursor |\n"
    "|  Rook  |   | |   |   |#|   |    +-------+----------------------+\n"
    "|        |   / \\   |   /#\\   |    | Right | Move right the cursor|\n"
    "+--------+---------+---------+    +-------+----------------------+\n"
    "|        |   ,^.   |   ,^.   |    |       |If no piece selected, |\n"
    "| Knight |  (  '\\  |  (##'\\  |    | Enter |  Select the cursor   |\n"
    "|        |  |  \\   |  |##\\   |    |       |Else, Submit movement |\n"
    "+--------+---------+---------+    +-------+----------------------+\n"
    "|        |    O/   |    O/   |    |   U   | Unselected the piece |\n"
    "| Bishop |   ( )   |   (#)   |    +-------+----------------------+\n"
    "|        |   / \\   |   /#\\   |    |   S   |Switch the piece style|\n"
    "+--------+---------+---------+    +-------+----------------------+\n"
    "|        |   WWW   |   WWW   |    |   H   | Open the help window |\n"
    "|  King  |   \\ /   |   \\#/   |    +-------+----------------------+\n"
    "|        |   / \\   |   /#\\   |    |   R   |   Restart the game   |\n"
    "+--------+---------+---------+    +-------+----------------------+\n"
    "|        |   _+_   |   _#_   |    |   Q   |                      |\n"
    "|  Queen |   \\ /   |   \\#/   |    +-------+   Quit the program   |\n"
    "|        |   / \\   |   /#\\   |    |  ESC  |                      |\n"
    "+--------+---------+---------+    +-------+----------------------+";

const char* View::STATUS_BAR = "OPERATIONS: Arrows: Move Cursor ｜ Enter: Select and Move | U: Unselect | S: Switch Style | R: Restart | H: Help | Esc or Q: Quit";

const std::pair<const char*, int> View::STATUS[STATUS_NUM] =
{
    std::pair<const char*, int>("Normal", finalcut::fc::Green),
    std::pair<const char*, int>("Check", finalcut::fc::Yellow),
    std::pair<const char*, int>("Stalemate", finalcut::fc::Red),
    std::pair<const char*, int>("Checkmate", finalcut::fc::Red)
};

View::View(FWidget* parent):
    FDialog(parent), m_istr(""), m_focus_r(0), m_focus_c(0), m_select_r(-1), m_select_c(-1), m_style(0)
{
    m_board = new ChessBoard(m_istr);
    setBold();
    setGeometry(2, 2, 1 + 1 + ChessBoard::COL * WIDTH + 3 + 30 + 1, 1 + 1 + 1 + ChessBoard::ROW * HEIGHT + 1);
    setText("Terminal Chess - Powered by SBofGaySchoolBuPaAnything");
    m_bar = new finalcut::FStatusBar(this);
    m_bar->setMessage(STATUS_BAR);
    m_bar->setDisable();

    for (int r = 0; r < ChessBoard::ROW; r++)
    {
        m_coord_row[r] = new finalcut::FLabel(this);
        m_coord_row[r]->setGeometry(1, 1 + 1 + r * HEIGHT, 1, HEIGHT);
        m_coord_row[r]->setText(COORD_ROW[r]);
        m_coord_row[r]->setForegroundColor(finalcut::fc::Black);
        m_coord_row[r]->setBackgroundColor(r % 2 ? finalcut::fc::LightGray : finalcut::fc::White);
    }
    for (int c = 0; c < ChessBoard::COL; c++)
    {
        m_coord_col[c] = new finalcut::FLabel(this);
        m_coord_col[c]->setGeometry(1 + 1 + c * WIDTH, 1, WIDTH, 1);
        m_coord_col[c]->setText(COORD_COL[c]);
        m_coord_col[c]->setForegroundColor(finalcut::fc::Black);
        m_coord_col[c]->setBackgroundColor(c % 2 ? finalcut::fc::LightGray : finalcut::fc::White);
    }
    for (int r = 0; r < ChessBoard::ROW; r++)
    {
        for (int c = 0; c < ChessBoard::COL; c++)
        {
            m_pieces[r][c] = new finalcut::FLabel(this);
            m_pieces[r][c]->setGeometry(1 + 1 + c * WIDTH, 1 + 1 + r * HEIGHT, WIDTH, HEIGHT);
            changePieceColor(r, c);
        }
    }
    m_selection_label = new finalcut::FLabel(this);
    m_selection_label->setGeometry(1 + 1 + ChessBoard::COL * WIDTH + 3, 1, 16, 2);
    m_selection_label->setText("Selected Piece:\nCoordinate:");
    m_selection = new finalcut::FLabel(this);
    m_selection->setGeometry(1 + 1 + ChessBoard::COL * WIDTH + 3 + 16 + 1, 1, WIDTH, HEIGHT);
    m_selection->setBackgroundColor(finalcut::fc::LightGray);
    m_selection_coord = new finalcut::FLabel(this);
    m_selection_coord->setGeometry(1 + 1 + ChessBoard::COL * WIDTH + 3, 1 + 2, 3, 1);
    m_status_label = new finalcut::FLabel(this);
    m_status_label->setGeometry(1 + 1 + ChessBoard::COL * WIDTH + 3, 1 + 3 + 1, 17, 3);
    m_status_label->setText("Game Status:\nCurrent Player:\nStatus:");
    m_status_player = new finalcut::FLabel(this);
    m_status_player->setGeometry(1 + 1 + ChessBoard::COL * WIDTH + 3 + 17, 1 + 3 + 1 + 1, 13, 1);
    m_status_player->setText("White");
    m_status_state = new finalcut::FLabel(this);
    m_status_state->setGeometry(1 + 1 + ChessBoard::COL * WIDTH + 3 + 17, 1 + 3 + 1 + 2, 13, 1);
    m_status_state->setText("Normal");
    m_record_label = new finalcut::FLabel(this);
    m_record_label->setGeometry(1 + 1 + ChessBoard::COL * WIDTH + 3, 1 + 3 + 1 + 3 + 1, 15, 1);
    m_record_label->setText("Game Record:");
    m_record = new RecordView(this);
    m_record->unsetFocusable();
    m_record->setGeometry(1 + 1 + ChessBoard::COL * WIDTH + 3, 1 + 3 + 1 + 3 + 1 + 1, 30, 16);
    selectPiece(-1, -1);
    focusPiece(0, 0);
    load();
}

View::~View()
{
    delete m_board;
}

void View::focusPiece(int r, int c)
{
    if (m_focus_r != m_select_r || m_focus_c != m_select_c)
        changePieceColor(m_focus_r, m_focus_c);
    if (r != m_select_r || c != m_select_c)
        changePieceColor(r, c, FOCUSED);
    m_focus_r = r;
    m_focus_c = c;
    return;
}

void View::selectPiece(int r, int c)
{
    if (r < 0)
    {
        if (m_select_r >= 0)
        {
            if (m_select_r == m_focus_r && m_select_c == m_focus_c)
                changePieceColor(m_select_r, m_select_c, FOCUSED);
            else
                changePieceColor(m_select_r, m_select_c);
        }
        m_selection->setText(PIECE_UNKNOWN);
        m_selection_coord->setText("??");
    }
    else
    {
        if (m_select_r >= 0)
            selectPiece(-1, -1);
        changePieceColor(r, c, SELECTED);
        m_selection->setText(m_pieces[r][c]->getText());
        m_selection_coord->setText(coordStr(r, c));
    }
    m_select_r = r;
    m_select_c = c;
    return;
}

void View::draw()
{
    finalcut::FDialog::draw();
    setBold();
    setColor(finalcut::fc::Black, finalcut::fc::White);
    for (int r = 1 + 1 + 1; r < 1 + 1 + 1 + ChessBoard::ROW * HEIGHT + 1; r++)
    {
        setPrintPos(1 + 1 + ChessBoard::COL * WIDTH + 2, r);
        print("|");
    }
    setPrintPos(1 + 1 + ChessBoard::COL * WIDTH + 3, 1 + 1 + 1 + 3);
    print(finalcut::FString(31, '-'));
    setPrintPos(1 + 1 + ChessBoard::COL * WIDTH + 3, 1 + 1 + 1 + 3 + 1 + 3);
    print(finalcut::FString(31, '-'));
    return;
}

void View::onKeyPress(finalcut::FKeyEvent* ev)
{
    if (!ev)
        return;
    else if (getMoveSizeWidget() || !hasFocus())
        return finalcut::FDialog::onKeyPress(ev);
    switch (ev->key())
    {
        case finalcut::fc::Fkey_up:
        {
            ev->accept();
            focusPiece(normalize(m_focus_r - 1), m_focus_c);
            redraw();
            return;
        }
        case finalcut::fc::Fkey_down:
        {
            ev->accept();
            focusPiece(normalize(m_focus_r + 1), m_focus_c);
            redraw();
            return;
        }
        case finalcut::fc::Fkey_left:
        {
            ev->accept();
            focusPiece(m_focus_r, normalize(m_focus_c - 1));
            redraw();
            return;
        }
        case finalcut::fc::Fkey_right:
        {
            ev->accept();
            focusPiece(m_focus_r, normalize(m_focus_c + 1));
            redraw();
            return;
        }
        case finalcut::fc::Fkey_return:
        case finalcut::fc::Fkey_enter:
        {
            ev->accept();
            bool promoting = false;
            if (m_select_r == -1)
                selectPiece(m_focus_r, m_focus_c);
            else
                promoting = submit();
            redraw();
            if (promoting)
            {
                std::string type;
                while (!type.length())
                {
                    PromotionView dlg(this);
                    dlg.setModal();
                    dlg.exec();
                    type = dlg.getType();
                }
                promote(type);
                redraw();
            }
            return;
        }
        case 'u':
        {
            ev->accept();
            selectPiece(-1, -1);
            redraw();
            return;
        }
        case 'r':
        {
            ev->accept();
            int res = finalcut::FMessageBox::info(
                this,
                "Restart",
                "Do you really want\nto restart the game ?",
                finalcut::FMessageBox::Yes,
                finalcut::FMessageBox::No
            );
            if (res == finalcut::FMessageBox::Yes)
            {
                selectPiece(-1, -1);
                restart();
            }
            redraw();
            return;
        }
        case 's':
        {
            ev->accept();
            m_style = 1 - m_style;
            load(false);
            selectPiece(m_select_r, m_select_c);
            redraw();
            return;
        }
        case 'h':
        {
            ev->accept();
            finalcut::FMessageBox::info(
                this,
                "Help",
                HELP,
                finalcut::FMessageBox::Ok
            );
            redraw();
            return;
        }
        case 'q':
        case finalcut::fc::Fkey_escape:
        case finalcut::fc::Fkey_escape_mintty:
        {
            ev->accept();
            close();
            return;
        }
        default:
            break;
    }
    return finalcut::FDialog::onKeyPress(ev);
}

void View::changePieceColor(int r, int c, int type)
{
    if (type == SELECTED)
    {
        m_pieces[r][c]->setForegroundColor(finalcut::fc::White);
        m_pieces[r][c]->setBackgroundColor(finalcut::fc::Red);
    }
    else if (type == FOCUSED)
    {
        m_pieces[r][c]->setForegroundColor(finalcut::fc::White);
        m_pieces[r][c]->setBackgroundColor(finalcut::fc::Green);
    }
    else
    {
        m_pieces[r][c]->setForegroundColor(finalcut::fc::Black);
        if ((r + c) % 2)
            m_pieces[r][c]->setBackgroundColor(finalcut::fc::White);
        else
            m_pieces[r][c]->setBackgroundColor(finalcut::fc::LightGray);
    }
    return;
}

void View::onWindowRaised(finalcut::FEvent* ev)
{
    m_bar->setMessage(STATUS_BAR);
    return finalcut::FDialog::onWindowActive(ev);
}

void View::onWindowActive(finalcut::FEvent* ev)
{
    m_bar->setMessage(STATUS_BAR);
    return finalcut::FDialog::onWindowActive(ev);
}

void View::onClose(finalcut::FCloseEvent *ev)
{
    return finalcut::FApplication::closeConfirmationDialog(this, ev);
}

bool View::load(bool msg)
{
    char chr;
    if (msg)
    {
        m_istr.seekg(0, std::ios::beg);
        std::string ipt;
        while (m_istr.get(chr))
            ipt.push_back(chr);
        ipt.push_back('\n');
        m_record->appendStr(ipt);
        cleanStream();
    }
    m_board->drawBoard(true);
    m_istr.seekg(0, std::ios::beg);
    int player, state, promoting;
    m_istr >> player >> state >> promoting;
    m_status_player->setText(player ? "Black" : "White");
    m_status_state->setText(STATUS[state].first);
    m_status_state->setForegroundColor(STATUS[state].second);
    for (int r = 0; r < ChessBoard::ROW; r++)
    {
        for (int c = 0; c < ChessBoard::COL; c++)
        {
            m_istr >> chr;
            int side = islower(chr) ? ChessBoard::BLACK : ChessBoard::WHITE;
            switch(toupper(chr))
            {
                case 'P':
                {
                    m_pieces[r][c]->setText(PIECE[m_style][PAWN][side]);
                    break;
                }
                case 'R':
                {
                    m_pieces[r][c]->setText(PIECE[m_style][ROOK][side]);
                    break;
                }
                case 'N':
                {
                    m_pieces[r][c]->setText(PIECE[m_style][KNIGHT][side]);
                    break;
                }
                case 'B':
                {
                    m_pieces[r][c]->setText(PIECE[m_style][BISHOP][side]);
                    break;
                }
                case 'Q':
                {
                    m_pieces[r][c]->setText(PIECE[m_style][QUEEN][side]);
                    break;
                }
                case 'K':
                {
                    m_pieces[r][c]->setText(PIECE[m_style][KING][side]);
                    break;
                }
                default:
                    m_pieces[r][c]->setText(PIECE_NULL);
            }
        }
    }
    m_istr.clear();
    m_record->scrollBottom();
    return promoting ? true : false;
}

void View::restart()
{
    m_record->clear();
    cleanStream();
    m_board->resetBoard();
    load();
    return;
}

bool View::submit()
{
    std::string src = coordStr(m_select_r, m_select_c), dst = coordStr(m_focus_r, m_focus_c);
    selectPiece(-1, -1);
    cleanStream();
    m_board->submitMove(src, dst);
    return load();
}

void View::promote(std::string type)
{
    cleanStream();
    m_board->submitPromotion(type);
    load();
    return;
}

void promotionSetValue(finalcut::FWidget* w, finalcut::FWidget::data_ptr data)
{
    PromotionView* dlg = static_cast<PromotionView*>(data);
    dlg->m_type = (dynamic_cast<finalcut::FButton*>(w))->getText();
    dlg->m_type.erase(0, 1);
    dlg->close();
    return;
}

PromotionView::PromotionView(finalcut::FWidget* parent):
    FDialog(parent), m_type("")
{
    setText("Promoting Pawn");
    setGeometry(10, 10, 38, 6);
    m_queen = new finalcut::FButton("&queen", this);
    m_queen->setGeometry(1, 1, 8, 3);
    m_queen->setShadow(false);
    m_queen->setClickAnimation(false);
    m_queen->addCallback("clicked", F_FUNCTION_CALLBACK(&promotionSetValue), this);
    m_queen->setStatusbarMessage("Promote the pawn to queen");
    m_rook = new finalcut::FButton("&rook", this);
    m_rook->setGeometry(10, 1, 8, 3);
    m_rook->setShadow(false);
    m_rook->setClickAnimation(false);
    m_rook->addCallback("clicked", F_FUNCTION_CALLBACK(&promotionSetValue), this);
    m_rook->setStatusbarMessage("Promote the pawn to rook");
    m_knight = new finalcut::FButton("&knight", this);
    m_knight->setGeometry(19, 1, 8, 3);
    m_knight->setShadow(false);
    m_knight->setClickAnimation(false);
    m_knight->addCallback("clicked", F_FUNCTION_CALLBACK(&promotionSetValue), this);
    m_knight->setStatusbarMessage("Promote the pawn to knight");
    m_bishop = new finalcut::FButton("&bishop", this);
    m_bishop->setGeometry(28, 1, 8, 3);
    m_bishop->setShadow(false);
    m_bishop->setClickAnimation(false);
    m_bishop->addCallback("clicked", F_FUNCTION_CALLBACK(&promotionSetValue), this);
    m_bishop->setStatusbarMessage("Promote the pawn to bishop");
    m_queen->setFocus();
}
