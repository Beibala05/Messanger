#include "client.h"

Client::Client()
{
    socket = new QTcpSocket(this);
}

Client::~Client()
{
    delete socket;
}

bool Client::sendMessage(const QString &message) 
{
    QByteArray data = message.toUtf8();
    
    qint64 bytesWritten = socket->write(data);
    
    if (bytesWritten == -1) 
    {
        qDebug() << "Ошибка при отправке сообщения";
        return false;
    }
    
    socket->waitForBytesWritten(1000);
    return true;
}

void Client::connect()
{
    socket->connectToHost(LOCAL_IP_ADDRESS, PORT);
}

bool Client::disconnect()
{
    if (socket)
    {
        socket->close();
        return true;
    }
    else return false;
}

QString Client::fromServer()
{
    if (socket->waitForReadyRead(1000)) 
    {
        QByteArray responseData = socket->readAll();
        return QString::fromUtf8(responseData);
    }
}