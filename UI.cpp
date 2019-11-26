/***********************************************************************
* UI.cpp Implementation of terminal UI for chess game                  *
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

#include "UI.h"

#include "ChessBoard.h"

#include <cctype>

using namespace std;
using namespace finalcut;


void RecordView::appendStr(string str)
{
    // I
    if (str.back() != '\n')
        str.push_back('\n');
    unsigned int start = 0;

    // Loop for every char in order to split in proper place.
    for (unsigned int i = 0; i < str.length(); i ++)
    {
        // If the char is end-of-line.
        if (str.at(i) == '\n')
        {
            // A char other than white space char ('\n', '\t', ' ') must be used, to generate a empty line.
            if (i == start)
                append("~");
            else
                append(str.substr(start, i - start));
            start = i + 1;
        }

        // If the current row reaches the max length.
        else if (i - start == getWidth() - 2)
        {
            append(str.substr(start, i - start));
            start = i;
        }
    }
}

/*
 * Keypress event is capture to disable default movement of TextView when up or down is pressed
 */
void RecordView::onKeyPress(FKeyEvent* ev)
{
    ev->accept();
    return FTextView::onKeyPress(ev);
}

/*
 * Wheel event is capture to prevent crash when the TextView is not scrollable.
 */
void RecordView::onWheel(FWheelEvent* ev)
{
    if (!ev || !scrollable())
        return;
    return FTextView::onWheel(ev);
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

const pair<const char*, int> View::STATUS[STATUS_NUM] =
{
    pair<const char*, int>("Normal", fc::Green),
    pair<const char*, int>("Check", fc::Yellow),
    pair<const char*, int>("Stalemate", fc::Red),
    pair<const char*, int>("Checkmate", fc::Red)
};

View::View(FWidget* parent):
    FDialog(parent), m_istr(""), m_focus_r(0), m_focus_c(0), m_select_r(-1), m_select_c(-1), m_style(0)
{
    // Generate the core object for simulation.
    m_board = new ChessBoard(m_istr);

    // Draw the dialog.
    setBold();
    setGeometry(2, 2, 1 + 1 + ChessBoard::COL * WIDTH + 3 + 30 + 1, 1 + 1 + 1 + ChessBoard::ROW * HEIGHT + 1);
    setText("Terminal Chess - Powered by SBofGaySchoolBuPaAnything");

    // Draw the status bar.
    m_bar = new FStatusBar(this);
    m_bar->setMessage(STATUS_BAR);
    m_bar->setDisable();

    // Generate row ruler.
    for (int r = 0; r < ChessBoard::ROW; r++)
    {
        m_coord_row[r] = new FLabel(this);
        m_coord_row[r]->setGeometry(1, 1 + 1 + r * HEIGHT, 1, HEIGHT);
        m_coord_row[r]->setText(COORD_ROW[r]);
        m_coord_row[r]->setForegroundColor(fc::Black);
        m_coord_row[r]->setBackgroundColor(r % 2 ? fc::LightGray : fc::White);
    }

    // Generate column ruler.
    for (int c = 0; c < ChessBoard::COL; c++)
    {
        m_coord_col[c] = new FLabel(this);
        m_coord_col[c]->setGeometry(1 + 1 + c * WIDTH, 1, WIDTH, 1);
        m_coord_col[c]->setText(COORD_COL[c]);
        m_coord_col[c]->setForegroundColor(fc::Black);
        m_coord_col[c]->setBackgroundColor(c % 2 ? fc::LightGray : fc::White);
    }

    // Generate all grids.
    for (int r = 0; r < ChessBoard::ROW; r++)
    {
        for (int c = 0; c < ChessBoard::COL; c++)
        {
            m_pieces[r][c] = new FLabel(this);
            m_pieces[r][c]->setGeometry(1 + 1 + c * WIDTH, 1 + 1 + r * HEIGHT, WIDTH, HEIGHT);
            changePieceColor(r, c);
        }
    }

    // Generate widgets for selection information.
    m_selection_label = new FLabel(this);
    m_selection_label->setGeometry(1 + 1 + ChessBoard::COL * WIDTH + 3, 1, 16, 2);
    m_selection_label->setText("Selected Piece:\nCoordinate:");
    m_selection = new FLabel(this);
    m_selection->setGeometry(1 + 1 + ChessBoard::COL * WIDTH + 3 + 16 + 1, 1, WIDTH, HEIGHT);
    m_selection->setBackgroundColor(fc::LightGray);
    m_selection_coord = new FLabel(this);
    m_selection_coord->setGeometry(1 + 1 + ChessBoard::COL * WIDTH + 3, 1 + 2, 3, 1);

    // Generate widgets for status information.
    m_status_label = new FLabel(this);
    m_status_label->setGeometry(1 + 1 + ChessBoard::COL * WIDTH + 3, 1 + 3 + 1, 17, 3);
    m_status_label->setText("Game Status:\nCurrent Player:\nStatus:");
    m_status_player = new FLabel(this);
    m_status_player->setGeometry(1 + 1 + ChessBoard::COL * WIDTH + 3 + 17, 1 + 3 + 1 + 1, 13, 1);
    m_status_player->setText("White");
    m_status_state = new FLabel(this);
    m_status_state->setGeometry(1 + 1 + ChessBoard::COL * WIDTH + 3 + 17, 1 + 3 + 1 + 2, 13, 1);
    m_status_state->setText("Normal");

    // Generate widgets for record information.
    m_record_label = new FLabel(this);
    m_record_label->setGeometry(1 + 1 + ChessBoard::COL * WIDTH + 3, 1 + 3 + 1 + 3 + 1, 15, 1);
    m_record_label->setText("Game Record:");
    m_record = new RecordView(this);
    m_record->unsetFocusable();
    m_record->setGeometry(1 + 1 + ChessBoard::COL * WIDTH + 3, 1 + 3 + 1 + 3 + 1 + 1, 30, 16);

    // Unselect any pieces.
    selectPiece(-1, -1);

    // Focus on the grid on the left-up corner.
    focusPiece(0, 0);

    // Load the board.
    load();
}

/*
 * All child of the dialog does not need to be delete manually,
 * as it is said here: https://github.com/gansm/finalcut/blob/master/doc/first-steps.md#memory-management
 */
View::~View()
{
    // Delete the board.
    delete m_board;
}

void View::focusPiece(int r, int c)
{
    // Change the previous focused grid to a proper colour.
    if (m_focus_r != m_select_r || m_focus_c != m_select_c)
        changePieceColor(m_focus_r, m_focus_c);

    // Change the current focused grid to a proper colour.
    if (r != m_select_r || c != m_select_c)
        changePieceColor(r, c, FOCUSED);

    // Update variables.
    m_focus_r = r;
    m_focus_c = c;
}

void View::selectPiece(int r, int c)
{
    // If unselecting.
    if (r < 0)
    {
        // Change the previous selected grid to a proper colour
        if (m_select_r >= 0)
        {
            if (m_select_r == m_focus_r && m_select_c == m_focus_c)
                changePieceColor(m_select_r, m_select_c, FOCUSED);
            else
                changePieceColor(m_select_r, m_select_c);
        }

        // Change the selection information.
        m_selection->setText(PIECE_UNKNOWN);
        m_selection_coord->setText("??");
    }

    // Selecting.
    else
    {
        // If a grid is been selected, unselect it first.
        if (m_select_r >= 0)
            selectPiece(-1, -1);
        // Change the grid to a proper colour.
        changePieceColor(r, c, SELECTED);

        //  Change the selection information.
        m_selection->setText(m_pieces[r][c]->getText());
        m_selection_coord->setText(coordStr(r, c));
    }

    // Update variables.
    m_select_r = r;
    m_select_c = c;
}

void View::draw()
{
    // Draw normally first.
    FDialog::draw();
    setBold();

    // Draw the vertical separator.
    setColor(fc::Black, fc::White);
    for (int r = 1 + 1 + 1; r < 1 + 1 + 1 + ChessBoard::ROW * HEIGHT + 1; r++)
    {
        setPrintPos(1 + 1 + ChessBoard::COL * WIDTH + 2, r);
        print("|");
    }

    // Draw the two horizontal separator.
    setPrintPos(1 + 1 + ChessBoard::COL * WIDTH + 3, 1 + 1 + 1 + 3);
    print(FString(31, '-'));
    setPrintPos(1 + 1 + ChessBoard::COL * WIDTH + 3, 1 + 1 + 1 + 3 + 1 + 3);
    print(FString(31, '-'));
}

void View::onKeyPress(FKeyEvent* ev)
{
    if (!ev)
        return;

    // If the main dialog do not has the focus, do nothing but normal behaviours.
    else if (getMoveSizeWidget() || !hasFocus())
        return FDialog::onKeyPress(ev);
    switch (ev->key())
    {
        // Key Up is pressed, move the cursor upward.
        case fc::Fkey_up:
        {
            ev->accept();
            focusPiece(normalize(m_focus_r - 1), m_focus_c);
            redraw();
            return;
        }

        // Key Down is pressed, move the cursor downward.
        case fc::Fkey_down:
        {
            ev->accept();
            focusPiece(normalize(m_focus_r + 1), m_focus_c);
            redraw();
            return;
        }

        // Key Left is pressed, move the cursor leftward.
        case fc::Fkey_left:
        {
            ev->accept();
            focusPiece(m_focus_r, normalize(m_focus_c - 1));
            redraw();
            return;
        }

        // Key Right is pressed, move the cursor rightward.
        case fc::Fkey_right:
        {
            ev->accept();
            focusPiece(m_focus_r, normalize(m_focus_c + 1));
            redraw();
            return;
        }

        // Key enter is pressed.
        case fc::Fkey_return:
        case fc::Fkey_enter:
        {
            ev->accept();
            bool promoting = false;

            // If not selected, select the grid.
            if (m_select_r == -1)
                selectPiece(m_focus_r, m_focus_c);

            // Else, submit the movement.
            else
                promoting = submit();

            // Update the board first.
            redraw();

            // If a pawn is going to be promoted.
            if (promoting)
            {
                // Show the promotion dialog and get a valid type.
                string type;
                while (!type.length())
                {
                    PromotionView dlg(this);
                    dlg.setModal();
                    dlg.exec();
                    type = dlg.getType();
                }

                // Submit the promotion.
                promote(type);

                // Draw again.
                redraw();
            }
            return;
        }

        // Key U is pressed, unselect any grid.
        case 'u':
        {
            ev->accept();
            selectPiece(-1, -1);
            redraw();
            return;
        }

        // Key R is pressed, show the confirmation message box and restart the game.
        case 'r':
        {
            ev->accept();
            int res = FMessageBox::info(
                this,
                "Restart",
                "Do you really want\nto restart the game ?",
                FMessageBox::Yes,
                FMessageBox::No
            );
            if (res == FMessageBox::Yes)
            {
                selectPiece(-1, -1);
                restart();
            }
            redraw();
            return;
        }

        // Key S is pressed, switch the style of pieces and draw again.
        case 's':
        {
            ev->accept();
            m_style = 1 - m_style;
            load(false);
            selectPiece(m_select_r, m_select_c);
            redraw();
            return;
        }

        // Key H is pressed, show the help message box.
        case 'h':
        {
            ev->accept();
            FMessageBox::info(
                this,
                "Help",
                HELP,
                FMessageBox::Ok
            );
            redraw();
            return;
        }

        // Key Q or Esc is press, trigger close event.
        case 'q':
        case fc::Fkey_escape:
        case fc::Fkey_escape_mintty:
        {
            ev->accept();
            close();
            return;
        }
        default:
            break;
    }
    return FDialog::onKeyPress(ev);
}

void View::changePieceColor(int r, int c, int type)
{
    // If the grid is selected, change the colour to red.
    if (type == SELECTED)
    {
        m_pieces[r][c]->setForegroundColor(fc::White);
        m_pieces[r][c]->setBackgroundColor(fc::Red);
    }

    // If the grid is focused, change the colour to green.
    else if (type == FOCUSED)
    {
        m_pieces[r][c]->setForegroundColor(fc::White);
        m_pieces[r][c]->setBackgroundColor(fc::Green);
    }

    // If the grid is not selected and not focused, change the colour to white or gray.
    else
    {
        m_pieces[r][c]->setForegroundColor(fc::Black);
        if ((r + c) % 2)
            m_pieces[r][c]->setBackgroundColor(fc::White);
        else
            m_pieces[r][c]->setBackgroundColor(fc::LightGray);
    }
}

void View::onWindowRaised(FEvent* ev)
{
    // Set the status bar message before the window is raised.
    m_bar->setMessage(STATUS_BAR);
    return FDialog::onWindowRaised(ev);
}

void View::onWindowActive(FEvent* ev)
{
    // Set the status bar message before the window is active.
    m_bar->setMessage(STATUS_BAR);
    return FDialog::onWindowActive(ev);
}

void View::onClose(FCloseEvent *ev)
{
    // Show the confirmation message box before quit the programme.
    return FApplication::closeConfirmationDialog(this, ev);
}

bool View::load(bool msg)
{
    char chr;

    // If there is any message beforehand.
    if (msg)
    {
        // Move the pointer to the front of the steam
        m_istr.seekg(0, ios::beg);

        // Read everything and append them to the record displayer.
        string ipt;
        while (m_istr.get(chr))
            ipt.push_back(chr);
        ipt.push_back('\n');
        m_record->appendStr(ipt);

        // Finally clean the stream.
        cleanStream();
    }

    // Request the core to draw the board.
    m_board->drawBoard(true);

    // Rewind the pointer before reading.
    m_istr.seekg(0, ios::beg);

    // Read and display all information.
    int player, state, promoting;
    m_istr >> player >> state >> promoting;
    m_status_player->setText(player ? "Black" : "White");
    m_status_state->setText(STATUS[state].first);
    m_status_state->setForegroundColor((FColor) STATUS[state].second);

    // Read and display all pieces.
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

    // Clean the stream and scroll the record displayer to the bottom.
    cleanStream();
    m_record->scrollBottom();

    // Return if any pawn is going to be promoted.
    return promoting != 0;
}

void View::restart()
{
    // Clean the record and the stream, and then reset and reload the board.
    m_record->clear();
    cleanStream();
    m_board->resetBoard();
    load();
}

bool View::submit()
{
    // Unselect all pieces, clean the stream, submit the movement and reload the board.
    string src = coordStr(m_select_r, m_select_c), dst = coordStr(m_focus_r, m_focus_c);
    selectPiece(-1, -1);
    cleanStream();
    m_board->submitMove(src, dst);
    return load();
}

void View::promote(string type)
{
    // Clean the stream, submit the promotion and reload the board.
    cleanStream();
    m_board->submitPromotion(type);
    load();
}

void promotionSetValue(FWidget* w, FWidget::data_ptr data)
{
    // Set the result type variable.
    PromotionView* dlg = static_cast<PromotionView*>(data);
    dlg->m_type = (dynamic_cast<FButton*>(w))->getText();
    dlg->m_type.erase(0, 1);
    dlg->close();
}

PromotionView::PromotionView(FWidget* parent):
    FDialog(parent), m_type("")
{
    // Create the dialog.
    setText("Promoting Pawn");
    setGeometry(10, 10, 38, 6);

    // Create the button for queen.
    m_queen = new FButton("&queen", this);
    m_queen->setGeometry(1, 1, 8, 3);
    m_queen->setShadow(false);
    m_queen->setClickAnimation(false);
    m_queen->addCallback("clicked", F_FUNCTION_CALLBACK(&promotionSetValue), this);
    m_queen->setStatusbarMessage("Promote the pawn to queen");

    // Create the button for rook.
    m_rook = new FButton("&rook", this);
    m_rook->setGeometry(10, 1, 8, 3);
    m_rook->setShadow(false);
    m_rook->setClickAnimation(false);
    m_rook->addCallback("clicked", F_FUNCTION_CALLBACK(&promotionSetValue), this);
    m_rook->setStatusbarMessage("Promote the pawn to rook");

    // Create the button for knight.
    m_knight = new FButton("&knight", this);
    m_knight->setGeometry(19, 1, 8, 3);
    m_knight->setShadow(false);
    m_knight->setClickAnimation(false);
    m_knight->addCallback("clicked", F_FUNCTION_CALLBACK(&promotionSetValue), this);
    m_knight->setStatusbarMessage("Promote the pawn to knight");

    // Create the button for bishop.
    m_bishop = new FButton("&bishop", this);
    m_bishop->setGeometry(28, 1, 8, 3);
    m_bishop->setShadow(false);
    m_bishop->setClickAnimation(false);
    m_bishop->addCallback("clicked", F_FUNCTION_CALLBACK(&promotionSetValue), this);
    m_bishop->setStatusbarMessage("Promote the pawn to bishop");

    // Set focus on the queen.
    m_queen->setFocus();
}
