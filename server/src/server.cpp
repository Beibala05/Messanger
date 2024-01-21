#include "server.h"

Server::Server(QObject *parent) : QTcpServer(parent)
{
    if (startServer()) qDebug() << "Сервер запущен";
    else qDebug() << "Ошибка запуска сервера";
}

bool Server::startServer() 
{
    return this->listen(QHostAddress::Any, 2323);
}

void Server::incomingConnection(qintptr socketDescriptor) 
{
    clientConnection = new QTcpSocket(this);
    clientConnection->setSocketDescriptor(socketDescriptor);

    QObject::connect(clientConnection, &QAbstractSocket::disconnected, clientConnection, &QObject::deleteLater);
    QObject::connect(clientConnection, &QIODevice::readyRead, this, &Server::onReadyRead);
}

void Server::sendToClient(const QByteArray& message)
{
    if (clientConnection) 
    {
        clientConnection->write(message);
    }
}

void Server::onReadyRead() 
{
    clientConnection = (QTcpSocket *) sender();

    if (clientConnection) 
    {
        QByteArray message = clientConnection->readAll();
        qDebug() << "message: " << QString::fromUtf8(message);
        sendToClient(message);
    }
}

int main(int argc, char** argv) 
{
  QCoreApplication app(argc, argv);

  Server server;

  return app.exec();
}