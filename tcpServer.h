#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QHostAddress>
#include <QNetworkInterface>

class TCPServer : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool isListening MEMBER isListening WRITE setIsListening NOTIFY isListeningChanged)

public:
    explicit TCPServer(int port);
    bool startListening();

signals:
    bool isListeningChanged();

public slots:

private:
    int port = 0;
    bool isListening = false;
    QString errorMessage = "";
    QTcpServer server;

    void setIsListening(bool value);
};

#endif // TCPSERVER_H
