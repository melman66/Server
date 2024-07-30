
#ifndef SERVERVIEWMODEL_H
#define SERVERVIEWMODEL_H

#include "servermodel.h"

#include <QObject>

class ServerViewModel : public QObject
{
    Q_OBJECT

private:
    ServerModel* server_model;

public:
    explicit ServerViewModel(QObject *parent = nullptr);

    bool getStateServerStarted() const;
    bool sendMsgToClient(const QString& client, const QString& message) const;
    bool startServer(const QString& port) const;
    bool stopServer() const;

signals:
    void clientName(QString);
    void errorServer(QString);
    void sendMsgToGUI(QString);
    void removeClientFromList(QString);
};

#endif // SERVERVIEWMODEL_H
