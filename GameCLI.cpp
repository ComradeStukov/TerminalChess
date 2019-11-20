#include "ChessBoard.h"

#include <iostream>

using namespace std;

int main()
{
    string src, dst;
    ChessBoard board;
    cout << "====================\n";
    cout << "  New Game Started  \n";
    cout << "====================\n\n";
    board.drawBoard();
    cout << endl;
    while (true)
    {
        cin >> src;
        cout << endl;
        if (src == "quit")
            break;
        else if (src == "restart")
        {
            board.resetBoard();
            cout << "====================\n";
            cout << "  New Game Started  \n";
            cout << "====================\n\n";
            board.drawBoard();
            cout << endl;
        }
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