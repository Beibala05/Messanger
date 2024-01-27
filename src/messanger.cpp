#include "messanger.h"

QString Messanger::userName;

Messanger::Messanger(MainWindow* win)
{
    this->win = win;
    client = new Client();
    informationWidget = new QWidget();
    client->connect(); 

    QMessageBox::information(informationWidget, "Команды", "Полезный команды\n"
    "\n/help - Отображает текущее окно с подсказками"
    "\n/clear - Очистить историю"
    "\n/connect - Программа соединяеться с сервером"
    "\n/disconnect - Программа отсоединяеться от сервера"
    "\n/set_user_name - Задает новое имя пользователя (Структура: /set_user_name [new_user_name])");
}

Messanger::~Messanger()
{
    client->disconnect();

    delete informationWidget;
    delete client;
}

QString Messanger::messageToServer(QString textFromEdit)
{
    QString userNameSize = QString::number(this->userName.size());

    return userNameSize + userName + textFromEdit;
}

void Messanger::parseMessage(QString& otherName, QString& ans)
{
    bool ok;
    QString size_qstr = ans.at(0);
    int size_int = size_qstr.toInt(&ok);

    if (ok)
    {
        ans.remove(0, 1);

        otherName = ans.left(size_int);

        ans.remove(0, size_int);
    }
}

void Messanger::sendMessageToBrowserSlot()
{ 
    QString textFromEdit    = win->getTextEdit();
    QString textFromBrowser = win->getTextBrowser();

    if (textFromEdit.isEmpty())
    {
        return;
    }

    if (textFromEdit == "/connect")
    {
        client->connect();
        win->clearTextEdit();

        QMessageBox::information(informationWidget, "Сообщение", "Попытка соединиться с сервером\n\nОтправьте сообщение еще раз");

        return;
    }

    if (textFromEdit == "/disconnect")
    {
        client->disconnect();
        win->clearTextEdit();

        QMessageBox::information(informationWidget, "Сообщение", "Соединение с сервером прервано");

        return;
    }

    if (textFromEdit == "/help")
    {
        win->clearTextEdit();

        QMessageBox::information(informationWidget, "Команды", "Полезный команды\n"
        "\n/help - Отображает текущее окно с подсказками"
        "\n/clear - Очистить историю"
        "\n/connect - Программа соединяеться с сервером"
        "\n/disconnect - Программа отсоединяеться от сервера"
        "\n/set_user_name - Задает новое имя пользователя (Структура: /set_user_name [new_user_name])");

        return;
    }

    if (textFromEdit == "/clear")
    {
        win->clearTextEdit();
        win->setTextBrowser("");

        return;
    }

    if (textFromEdit.contains("/set_user_name"))
    {
        textFromEdit.replace("/set_user_name", "");
        textFromEdit.remove(' ');

        if (textFromEdit.size() > 9)
        {
            QMessageBox::information(informationWidget, "Ошибка", "Имя пользователя не должно содержать больше 9 символов");
            return;
        }

        QString oldUserName = this->userName;
        this->userName = textFromEdit;
        win->clearTextEdit();

        QMessageBox::information(informationWidget, "Новое имя пользователя", "Имя пользователя изменено с " + oldUserName + " на " + this->userName);

        return;
    }

    bool check = client->sendMessage(Messanger::messageToServer(textFromEdit));

    if (!check)
    {
        QMessageBox::critical(informationWidget, "Ошибка", "Собщение не отправилось, введите команду /connect для повторного соединения");
    }
    else
    {
        QString clientName;
        QString ans = client->fromServer();

        parseMessage(clientName, ans);

        win->setTextBrowser(textFromBrowser + "Пользователь: " + clientName + "\n" + ans + "\n\n");
        win->clearTextEdit();
    }
}