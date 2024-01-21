#ifndef SERVER
#define SERVER

#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include <QString>
#include <QVector>

class Server : public QTcpServer 
{
public:
    Server(QObject *parent = nullptr);

public:
    bool startServer();
    void sendToClient(const QByteArray& message);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private:
    QTcpSocket*      clientConnection;

private slots:
    void onReadyRead();
};

#endif // SERVER