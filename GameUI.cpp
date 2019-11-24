#include "UI.h"

#include <final/final.h>

int main(int argc, char* argv[])
{
    finalcut::FApplication app(argc, argv);
    View view(&app);
    app.setMainWidget(&view);
    view.show();
    return app.exec();
}
