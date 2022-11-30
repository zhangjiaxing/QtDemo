#include "sandboxservice.h"

SandboxService::SandboxService(QObject *parent)
    : SandboxServiceSource{parent}
{

}


QString SandboxService::fileOutgoing(QString sandboxId, QString path){
    qDebug() << "export file " << sandboxId << path;
    Q_EMIT(fileOutgoingDone(sandboxId, path));
    return "Hello World";
}
