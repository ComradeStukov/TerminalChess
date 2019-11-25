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
    explicit View(finalcut::FWidget* parent=nullptr);
    ~View() override;
protected:
    void draw() override;
    void onKeyPress(finalcut::FKeyEvent* ev) override;
    void onWindowRaised(finalcut::FEvent* ev) override;
    void onWindowActive(finalcut::FEvent* ev) override;
    void onClose(finalcut::FCloseEvent* ev) override;
private:
    inline void cleanStream()
    {
        m_istr.str("");
        m_istr.clear();
    }
private:
    void changePieceColor(int r, int c, int select=UNSELECTED);
    void focusPiece(int r, int c);
    void selectPiece(int r, int c);
    bool load(bool msg=true);
    void restart();
    bool submit();
    void promote(std::string type);
public:
    static const int PIECE_NUM = 6;
    static const int PAWN = 0, ROOK = 1, KNIGHT = 2, BISHOP = 3, QUEEN = 4, KING = 5;
    static const int WIDTH = 7, HEIGHT = 3;
    static const int STYLE_NUM = 2;
    static const char* PIECE[STYLE_NUM][PIECE_NUM][ChessBoard::SIDE];
    static const char* PIECE_NULL;
    static const char* PIECE_UNKNOWN;
    static const char* COORD_ROW[ChessBoard::ROW];
    static const char* COORD_COL[ChessBoard::COL];
    static const char* HELP;
    static const char* STATUS_BAR;
    static const int UNSELECTED = 0, SELECTED = 1, FOCUSED = 2;
    static const int STATUS_NUM = 4;
    static const std::pair<const char*, int> STATUS[STATUS_NUM];
private:
    finalcut::FStatusBar* m_bar;
    finalcut::FLabel* m_coord_row[ChessBoard::ROW];
    finalcut::FLabel* m_coord_col[ChessBoard::COL];
    finalcut::FLabel* m_pieces[ChessBoard::ROW][ChessBoard::COL];
    finalcut::FLabel* m_selection_label;
    finalcut::FLabel* m_selection_coord;
    finalcut::FLabel* m_selection;
    finalcut::FLabel* m_status_label;
    finalcut::FLabel* m_status_player;
    finalcut::FLabel* m_status_state;
    finalcut::FLabel* m_record_label;
    RecordView* m_record;
    std::stringstream m_istr;
    int m_focus_r, m_focus_c;
    int m_select_r, m_select_c;
    int m_style;
    ChessBoard* m_board;
};

void promotionSetValue(finalcut::FWidget* w, finalcut::FWidget::data_ptr data);

class PromotionView: public finalcut::FDialog
{
    friend void promotionSetValue(finalcut::FWidget* w, finalcut::FWidget::data_ptr data);
public:
    explicit PromotionView(finalcut::FWidget* parent=nullptr);
    ~PromotionView() override = default;
    inline std::string getType()
    {
        return m_type;
    }
private:
    std::string m_type;
    finalcut::FButton* m_queen;
    finalcut::FButton* m_rook;
    finalcut::FButton* m_knight;
    finalcut::FButton* m_bishop;
};

#endif
