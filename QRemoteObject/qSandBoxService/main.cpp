#include <QCoreApplication>
#include <QRemoteObjectHost>
#include "sandboxservice.h"
#include <QDebug>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "ASDF asdf";


    QRemoteObjectHost *host = new QRemoteObjectHost;
    host->setHostUrl(QUrl("tcp://127.0.0.123:4567"));

    SandboxService *service = new SandboxService;
    host->enableRemoting(service);

    return a.exec();
}
