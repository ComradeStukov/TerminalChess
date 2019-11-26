/***********************************************************************
* GameCLI.cpp Implementation of simple cli game interface              *
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

#include "ChessBoard.h"

#include <iostream>

using namespace std;


const char* NEW_GAME = ""
    "====================\n"
    "  New Game Started  \n"
    "====================\n";

const char* HELP = ""
    "Symbols:\n"
    "\n"
    " - P & p - Pawn, R & r - Rook, N & n - Knight\n"
    " - B & b - Bishop, Q & q - Queen, K & k - king\n"
    "\n"
    " - UPPER ALPHA - WHITE, lower alpha - black\n"
    "\n"
    "Available options:\n"
    "\n"
    " - <SRC> <DST>:       Move the piece at SRC to DST.\n"
    "                      e.g. D2 D4.\n"
    "\n"
    " - <Promotiong Type>: Promote a pawn to the designated type.\n"
    "                      The type must be one of the following four:\n"
    "                      queen, rook, knight, bishop.\n"
    "\n"
    " - help:              Show available options.\n"
    "\n"
    " - restart:           Restart the game.\n"
    "\n"
    " - quit:              Quit the program.\n";

/*
 * A simple game interfact on CLI.
 */
int main()
{
    // Output necessary message.
    cout << HELP << endl;
    cout << NEW_GAME << endl;

    // Create an object for the core chess game simulation.
    ChessBoard board;
    cout << endl;
    board.drawBoard();
    cout << endl;

    // Input command.
    string src, dst;
    while (true)
    {
        // Get the first command.
        cin >> src;
        cout << endl;

        // Quit the program.
        if (src == "quit")
            break;

        // Restart the game.
        else if (src == "restart")
        {
            cout << NEW_GAME << endl;
            board.resetBoard();
            cout << endl;
            board.drawBoard();
            cout << endl;
        }

        // Show help message.
        else if (src == "help")
            cout << HELP << endl;

        // Pawn promotion.
        else if (src == "rook" || src == "knight" || src == "bishop" || src == "queen")
        {
            board.submitPromotion(src);
            cout << endl;
            board.drawBoard();
            cout << endl;
        }

        // Normal movement.
        else
        {
            cin >> dst;
            board.submitMove(src, dst);
            cout << endl;
            board.drawBoard();
            cout << endl;
        }
    }

    return 0;
}