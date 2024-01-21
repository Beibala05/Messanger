#include "messanger.h"

Messanger::Messanger(MainWindow* win)
{
    this->win = win;
    client = new Client();
    client->connect();
}

Messanger::~Messanger()
{
    client->disconnect();

    delete client;
}

void Messanger::sendMessageToBrowserSlot()
{ 
    QString textFromEdit    = win->getTextEdit();
    QString textFromBrowser = win->getTextBrowser();

    if (textFromEdit == "/connect")
    {
        client->connect();
        win->clearTextEdit();
    }

    if (textFromEdit == "/disconnect")
    {
        client->disconnect();
        win->clearTextEdit();

        QWidget* informationWidget = new QWidget();
        QMessageBox::information(informationWidget, "Ура", "Соединение с сервером прервано");

        return;
    }

    bool check = client->sendMessage(textFromEdit);

    if (!check)
    {
        QWidget* criticalWidget = new QWidget();
        QMessageBox::critical(criticalWidget, "Ошибка", "Собщение не отправилось, введите команду /connect для повторного соединения");
    }
    else
    {
        QString ans = client->fromServer();

        if (ans == "/connect")
        {
            QWidget* informationWidget = new QWidget();
            QMessageBox::information(informationWidget, "Ура", "Соединение с сервером установлено");
            return;
        }

        win->setTextBrowser(textFromBrowser + ans + "\n\n");
        win->clearTextEdit();
    }
}