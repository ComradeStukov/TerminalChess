/***********************************************************************
* ChessUI.cpp Entrance of terminal UI of chess game                    *
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

#include <final/final.h>


/*
 * A terminal UI for the chess game using finalcult library.
 */
int main(int argc, char* argv[])
{
    // Generate the root application object.
    finalcut::FApplication app(argc, argv);

    // Generate the main dialog.
    View view(&app);
    app.setMainWidget(&view);
    view.show();

    // Run forever.
    return app.exec();
}
