#include "messanger.h"

QString Messanger::userName;

Messanger::Messanger(MainWindow* win)
{
    this->win = win;
    client = new Client();
    informationWidget = new QWidget();
    client->connect(); 

    QMessageBox::information(informationWidget, "Сообщение", "Некоторые полезные команды\n"
    "\n/help - Отображает текущее окно с подсказками"
    "\n/connect - Программа подключается к серверу"
    "\n/disconnect - Программа отключается от сервера к серверу"
    "\n/set_user_name - Задает новое имя пользователя"
    "\n/set_text_size - Задает размер текста");
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

        QMessageBox::information(informationWidget, "Сообщение", "Имя пользователя было изменено с " + oldUserName + " на " + this->userName);

        return;
    }

    if (textFromEdit == "/help")
    {
        QMessageBox::information(informationWidget, "Сообщение", "Некоторые полезные команды\n"
        "\n/help - Отображает текущее окно с подсказками"
        "\n/connect - Программа подключается к серверу"
        "\n/disconnect - Программа отключается от сервера к серверу"
        "\n/set_user_name - Задает новое имя пользователя"
        "\n/set_text_size - Задает размер текста");

        win->clearTextEdit();

        return;
    }

    if (textFromEdit.contains("/set_text_size"))
    {
        textFromEdit.replace("/set_text_size", "");
        textFromEdit.remove(' ');

        bool ok;
        int new_size = textFromEdit.toInt(&ok);

        if (ok)
        {
            win->setTextSize(new_size);
        }
        else
        {
            QMessageBox::critical(informationWidget, "Ошибка", "Что-то не так ):\n\nНе удалось задать новый размер текста");
        }

        win->clearTextEdit();

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