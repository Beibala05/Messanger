#ifndef MESSANGER
#define MESSANGER

#include "main_window.h"

#include <QObject>
#include <QDebug>

class MainWindow;

class Messanger final : public QObject
{
public:
    Messanger(MainWindow* win);

public slots:
    void sendMessageToBrowserSlot();

private:
    MainWindow* win;
};

#endif // MESSANGER