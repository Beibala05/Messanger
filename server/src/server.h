#ifndef SERVER
#define SERVER

#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include <QString>
#include <QVector>

#define DEBUG_OFF

class Server : public QTcpServer 
{
public:
    Server(QObject *parent = nullptr);

public:
    bool                    startServer();

protected:
    void                    incomingConnection(qintptr socketDescriptor) override;

private:
    QTcpSocket*             clientConnection;
    QVector<QTcpSocket*>    clients;

private slots:
    void                    onReadyRead();
    void                    onClientDisconnected();
};

#endif // SERVER