/***********************************************************************
* UI.h Declaration of terminal UI for chess game                       *
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

#ifndef _UI_H_
#define _UI_H_

#include "ChessBoard.h"

#include <final/final.h>

#include <string>
#include <iostream>
#include <sstream>


/**
 * The class for the chess game record view.
 */
class RecordView: public finalcut::FTextView
{
public:
    /**
     * Constructor.
     * @param parent: The parent widget.
     */
    explicit RecordView(finalcut::FWidget* parent=nullptr):
        FTextView(parent)
    {
    }
    /**
     * Deconstructor.
     */
    ~RecordView() override = default;
    /**
     * Append a string, split it into rows, if necessary.
     * @param str: The appending string.
     */
    void appendStr(std::string str);
    /**
     * If the view is currently scrollable.
     * @return The result.
     */
    inline bool scrollable()
    {
        return getRows() > getHeight() - 2;
    }
    /**
     * Scroll the view to the bottom.
     */
    inline void scrollBottom()
    {
        // If it is scrollable.
        if (scrollable())
            // Scroll it to the right position.
            scrollToY((int)getRows() - (int)getHeight() + 2);
    }

protected:
    /**
     * Event Handler: handle keypress event.
     * @param ev The event object pointer.
     */
    void onKeyPress(finalcut::FKeyEvent* ev) override;
    /**
     * Event Handler: handle wheel event.
     * @param ev The event object pointer.
     */
    void onWheel(finalcut::FWheelEvent* ev) override;
};

/**
 * Main view(dialog) for the chess game.
 */
class View: public finalcut::FDialog
{
public:
    /**
     * Convert a grid into a two-char string.
     * @param r: The row number.
     * @param c: The column number.
     * @return The two-char string representing corresponding position on the board.
     */
    inline static std::string coordStr(int r, int c)
    {
        return std::string(1, c + 'A') + std::string(1, ChessBoard::ROW - 1 - r + '1');
    }
    /**
     * Normalize a index to the range 0 ~ (ROW - 1);
     * @param x: The index.
     * @return Normalized result.
     */
    inline static int normalize(int x)
    {
        return (x + ChessBoard::ROW) % ChessBoard::ROW;
    }

public:
    /**
     * Constructor.
     * @param parent: Parent widget.
     */
    explicit View(finalcut::FWidget* parent=nullptr);
    /**
     * Destructor.
     */
    ~View() override;

protected:
    /**
     * Override draw function.
     */
    void draw() override;
    /**
     * Event Handler: handle keypress event.
     * @param ev The event object pointer.
     */
    void onKeyPress(finalcut::FKeyEvent* ev) override;
    /**
     * Event Handler: handle window raise event.
     * @param ev The event object pointer.
     */
    void onWindowRaised(finalcut::FEvent* ev) override;
    /**
     * Event Handler: handle window active event.
     * @param ev The event object pointer.
     */
    void onWindowActive(finalcut::FEvent* ev) override;
    /**
     * Event Handler: handle close event.
     * @param ev The event object pointer.
     */
    void onClose(finalcut::FCloseEvent* ev) override;

private:
    /**
     * Clean the input stream.
     */
    inline void cleanStream()
    {
        m_istr.str("");
        m_istr.clear();
    }
    /**
     * Change the colour of a grid.
     * @param r: The row number.
     * @param c: The column number.
     * @param select: The new status of the grid.
     */
    void changePieceColor(int r, int c, int select=UNSELECTED);
    /**
     * Focus the cursor to a grid.
     * @param r: The row number.
     * @param c: The column number.
     */
    void focusPiece(int r, int c);
    /**
     * Select a grid as the source of a movement.
     * @param r: The row number.
     * @param c: The column number.
     */
    void selectPiece(int r, int c);
    /**
     * Load the current status from input stream.
     * @param msg: If there is any message in the stream beforehand.
     * @return If there is currently any pawn needed to be promoted.
     */
    bool load(bool msg=true);
    /**
     * Restart the game.
     */
    void restart();
    /**
     * Submit a movement.
     * @return If there is any pawn needed to be promoted after the movement.
     */
    bool submit();
    /**
     * Submit a promotion.
     * @param type
     */
    void promote(std::string type);

public:
    // Number of type of pieces, and there symbol.
    static const int PIECE_NUM = 6;
    static const int PAWN = 0, ROOK = 1, KNIGHT = 2, BISHOP = 3, QUEEN = 4, KING = 5;
    // Number of rows and columns used when drawing a single grid.
    static const int WIDTH = 7, HEIGHT = 3;
    // Number of different available style.
    static const int STYLE_NUM = 2;
    // ASCII picture of different pieces in different style.
    static const char* PIECE[STYLE_NUM][PIECE_NUM][ChessBoard::SIDE];
    static const char* PIECE_NULL;
    static const char* PIECE_UNKNOWN;
    // Row and column rulers.
    static const char* COORD_ROW[ChessBoard::ROW];
    static const char* COORD_COL[ChessBoard::COL];
    // Help message.
    static const char* HELP;
    // Status bar message.
    static const char* STATUS_BAR;
    // Symbols for different status of a grid.
    static const int UNSELECTED = 0, SELECTED = 1, FOCUSED = 2;
    // Number of different status of a side(player).
    static const int STATUS_NUM = 4;
    // Message and style for different status of a side.
    static const std::pair<const char*, int> STATUS[STATUS_NUM];

private:
    // Status bar object.
    finalcut::FStatusBar* m_bar;
    // Row and column ruler object.
    finalcut::FLabel* m_coord_row[ChessBoard::ROW];
    finalcut::FLabel* m_coord_col[ChessBoard::COL];
    // Pieces (board) object.
    finalcut::FLabel* m_pieces[ChessBoard::ROW][ChessBoard::COL];
    // Widgets for selection information.
    finalcut::FLabel* m_selection_label;
    finalcut::FLabel* m_selection_coord;
    finalcut::FLabel* m_selection;
    // Widgets for status information.
    finalcut::FLabel* m_status_label;
    finalcut::FLabel* m_status_player;
    finalcut::FLabel* m_status_state;
    // Widgets for game record.
    finalcut::FLabel* m_record_label;
    RecordView* m_record;
    // Input stream.
    std::stringstream m_istr;
    // Current focused grid.
    int m_focus_r, m_focus_c;
    // Current selected grid.
    int m_select_r, m_select_c;
    // Current piece style.
    int m_style;
    // Core object for chess game simulation.
    ChessBoard* m_board;
};

/**
 * Callback Function, select a promotion type.
 * @param w: Clicked button.
 * @param data: Promotion setting dialog.
 */
void promotionSetValue(finalcut::FWidget* w, finalcut::FWidget::data_ptr data);

/**
 * A dialog class for pawn promoting dialog.
 */
class PromotionView: public finalcut::FDialog
{
    // Mark callback function as friend.
    friend void promotionSetValue(finalcut::FWidget* w, finalcut::FWidget::data_ptr data);

public:
    /**
     * Constructor.
     * @param parent: The parent widget.
     */
    explicit PromotionView(finalcut::FWidget* parent=nullptr);
    /**
     * Deconstructor.
     */
    ~PromotionView() override = default;
    /**
     * Get the promotion selection result.
     * @return The result, one of "", "queen", "rook", "knight" and "bishop"
     */
    inline std::string getType()
    {
        return m_type;
    }

private:
    // Selected type.
    std::string m_type;
    // Buttons for different options.
    finalcut::FButton* m_queen;
    finalcut::FButton* m_rook;
    finalcut::FButton* m_knight;
    finalcut::FButton* m_bishop;
};

#endif
