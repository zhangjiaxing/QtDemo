#include <QCoreApplication>
#include <QtRemoteObjects/QRemoteObjectNode>
#include <QtRemoteObjects/QRemoteObjectPendingCallWatcher>
#include "rep_sandboxService_replica.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QRemoteObjectNode *node = new QRemoteObjectNode;

    qDebug() << __LINE__ << node->connectToNode(QUrl("tcp://127.0.0.123:4567"));

    SandboxServiceReplica *serviceReplica = node->acquire<SandboxServiceReplica>();

    QObject::connect(serviceReplica, &SandboxServiceReplica::initialized, [=](){
        qDebug() << "initialized !!!!";
        auto response = serviceReplica->fileOutgoing("box1", "C:/windows/c.txt");
        QRemoteObjectPendingCallWatcher *watcher = new QRemoteObjectPendingCallWatcher(response);
        QObject::connect(watcher, &QRemoteObjectPendingCallWatcher::finished, [](QRemoteObjectPendingCallWatcher *self){
            qDebug() << "return value is " << self->returnValue().toString();
            self->deleteLater();
        });

    });

    QObject::connect(serviceReplica, &SandboxServiceReplica::stateChanged,
            [=](QRemoteObjectReplica::State state, QRemoteObjectReplica::State oldState){
                Q_UNUSED(oldState)
                qDebug() << "stateChanged" << state;
            }
    );

    QObject::connect(serviceReplica, &SandboxServiceReplica::fileOutgoingDone, [=](QString box, QString file){
        qDebug() << "export done " << box << file;
    });

    return a.exec();
}
