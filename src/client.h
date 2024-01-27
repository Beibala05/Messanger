#ifndef CLIENT
#define CLIENT

#define ADDRESS "127.0.0.1"
#define PORT    2323

#include <QTcpSocket>

class Client : public QObject 
{
public:
  Client();
  ~Client();

public:
  bool sendMessage(const QString& message);
  void connect();
  bool disconnect();
  QString fromServer();

private:
  QTcpSocket*    socket;
  bool           checkConnect;
};

#endif // CLIENT