#include "tcpServer.h"

TCPServer::TCPServer(int port) : QObject () {
    this->port = port;
}

bool TCPServer::startListening()
{
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost && ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }

    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty()) {
       ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    }

    this->setIsListening(this->server.listen(QHostAddress::LocalHost, static_cast<quint16>(this->port)));

    if ( !this->isListening ) {
        this->errorMessage = "Impossibile avviare il server: %1" + this->server.errorString();
        return false;
    }

    qDebug("%s %s, port %d", "Listening to IP ", qPrintable(ipAddress), this->port);

    return true;
}

void TCPServer::setIsListening(bool value)
{
    if (this->isListening != value) {
        this->isListening = value;
        emit isListeningChanged();
    }
}
