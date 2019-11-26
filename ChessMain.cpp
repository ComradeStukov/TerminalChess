/***********************************************************************
* ChessMain.cpp Implementation of original coursework objects          *
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

/*
 * This is only a main function for the original coursework.
 */
int main()
{
    cout << "========================\n";
    cout << "Testing the Chess Engine\n";
    cout << "========================\n\n";

    ChessBoard cb;
    cout << '\n';

    cb.submitMove("D7", "D6");
    cout << '\n';

    cb.submitMove("D4", "H6");
    cout << '\n';

    cb.submitMove("D2", "D4");
    cout << '\n';

    cb.submitMove("F8", "B4");
    cout << '\n';

    cout << "=========================\n";
    cout << "Alekhine vs. Vasic (1931)\n";
    cout << "=========================\n\n";

    cb.resetBoard();
    cout << '\n';

    cb.submitMove("E2", "E4");
    cb.submitMove("E7", "E6");
    cout << '\n';

    cb.submitMove("D2", "D4");
    cb.submitMove("D7", "D5");
    cout << '\n';

    cb.submitMove("B1", "C3");
    cb.submitMove("F8", "B4");
    cout << '\n';

    cb.submitMove("F1", "D3");
    cb.submitMove("B4", "C3");
    cout << '\n';

    cb.submitMove("B2", "C3");
    cb.submitMove("H7", "H6");
    cout << '\n';

    cb.submitMove("C1", "A3");
    cb.submitMove("B8", "D7");
    cout << '\n';

    cb.submitMove("D1", "E2");
    cb.submitMove("D5", "E4");
    cout << '\n';

    cb.submitMove("D3", "E4");
    cb.submitMove("G8", "F6");
    cout << '\n';

    cb.submitMove("E4", "D3");
    cb.submitMove("B7", "B6");
    cout << '\n';

    cb.submitMove("E2", "E6");
    cb.submitMove("F7", "E6");
    cout << '\n';

    cb.submitMove("D3", "G6");
    cout << '\n';

    return 0;
}
