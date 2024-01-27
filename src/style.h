#ifndef STYLE
#define STYLE

#include <QString>
#include <QFont>

namespace styles
{
    const QString main_window_style =
        "background-color: #22222e;";

    const QString dialog_window_btn_red_style =
        "color: white;"
        "background-color: #22222e;"
        "border: 2px solid red;";

    const QString dialog_window_btn_green_style =
        "color: white;"
        "background-color: #22222e;"
        "border: 2px solid green;";

    const QFont fontTextEdit("Montserrat", 12);
    const QFont fontTextBrowser("Montserrat", 15);
};

#endif //STYLE