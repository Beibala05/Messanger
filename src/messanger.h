#ifndef MESSANGER
#define MESSANGER

#include "main_window.h"
#include "client.h"

#include <QObject>
#include <QDebug>
#include <QMessageBox>

class MainWindow;

class Messanger final : public QObject
{
public:
    Messanger(MainWindow* win);
    ~Messanger();

public slots:
    void sendMessageToBrowserSlot();

private:
    MainWindow* win;
    Client*     client;
};

#endif // MESSANGER