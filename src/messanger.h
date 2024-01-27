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
    void                sendMessageToBrowserSlot();

public:
    static QString      userName;

private:
    QString             messageToServer(QString textFromEdit);
    void                parseMessage(QString& otherName, QString& ans);

private:
    QWidget*            informationWidget;
    MainWindow*         win;
    Client*             client;
};

#endif // MESSANGER