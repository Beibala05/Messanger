#include "messanger.h"

Messanger::Messanger(MainWindow* win)
{
    this->win = win;
}

void Messanger::sendMessageToBrowserSlot()
{ 
    QString text = win->getTextEdit();
    win->setTextBrowser(text);
    win->clearTextEdit();
}