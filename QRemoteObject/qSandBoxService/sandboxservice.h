#ifndef SANDBOXSERVICE_H
#define SANDBOXSERVICE_H

#include "rep_sandboxService_source.h"


#include <QObject>

class SandboxService : public SandboxServiceSource
{
    Q_OBJECT
public:
    explicit SandboxService(QObject *parent = nullptr);

    virtual QString fileOutgoing(QString sandboxId, QString path);

};

#endif // SANDBOXSERVICE_H
