#include "server.h"

Server::Server(QObject *parent) : QTcpServer(parent)
{
    #ifndef DEBUG_OFF
        if (startServer()) qDebug() << "Сервер запущен";
        else qDebug() << "Ошибка при запуске сервера";
    #endif // DEBUG_OFF
}

bool Server::startServer() 
{
    return this->listen(QHostAddress::Any, PORT);
}

void Server::incomingConnection(qintptr socketDescriptor) 
{
    clientConnection = new QTcpSocket(this);

    if (clientConnection->setSocketDescriptor(socketDescriptor))
    {
        clients.push_back(clientConnection);
    
        QObject::connect(clientConnection, &QAbstractSocket::disconnected, this, &Server::onClientDisconnected);
        QObject::connect(clientConnection, &QIODevice::readyRead, this, &Server::onReadyRead);

        #ifndef DEBUG_OFF
            qDebug() << "Подключился новый клиент, количество клиентов" << clients.size();
        #endif // DEBUG_OFF
    }
    else delete clientConnection;
}

void Server::onClientDisconnected()
{
    QTcpSocket *client = (QTcpSocket *)sender();
    clients.removeAll(client);
    client->deleteLater();

    #ifndef DEBUG_OFF
        qDebug() << "Один из клиентов отсоединился от сервера, количество клиентов" << clients.size();
    #endif // DEBUG_OFF
}

void Server::onReadyRead() 
{
    clientConnection = (QTcpSocket *) sender();
    QByteArray message = clientConnection->readAll();
    #ifndef DEBUG_OFF
        qDebug() << "Сообщение от клиента:\t" << QString::fromUtf8(message);
    #endif // DEBUG_OFF

    for (const auto& client : clients)
    {
        if (client->state() == QAbstractSocket::ConnectedState)
        {
            client->write(message);
        }
    }
}

int main(int argc, char** argv) 
{
  QCoreApplication app(argc, argv);

  Server server;

  return app.exec();
}