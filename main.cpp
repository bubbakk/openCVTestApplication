#include "stockhouseManagerWindow.h"
#include <QApplication>
#include <QSettings>
#include <QTextStream>
#include "tcpServer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StockhouseManager w;

    // just some applicatione meta-data
    QCoreApplication::setOrganizationName("elite");
    QCoreApplication::setApplicationName("Stockhouse Manager");
    QTextStream out(stdout);
    out << "Qt version: " << qVersion() << endl;

    // application settings
    QSettings settings;
    int tcpPort = settings.value("TCPCamera/TCP_Port", 7200).toInt();   // default port is 7200

    // START TCP SERVER
    TCPServer cameraTCPServer(tcpPort);
    cameraTCPServer.startListening();

    w.show();

    return a.exec();
}
