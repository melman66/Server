﻿
#ifndef SERVERVIEW_H
#define SERVERVIEW_H

#include <QObject>
#include <QDebug>
#include <QtQml>
#include <QThread>

#include "servermodel.h"
#include "serverviewmodel.h"

class ServerView : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(bool stateServerStarted
                   READ getStateServerStarted
                           NOTIFY stateServerStartedChanged)

private:
    ServerViewModel *server_view_model;
    QThread         *backendThread;

    bool stateServerStarted{ false };

public:
    explicit ServerView(QObject *parent = nullptr);

    bool getStateServerStarted() const;

    Q_INVOKABLE QString getCurrentDateTime() const;
    Q_INVOKABLE bool    sendMsgToClient(const QString& client, const QString& message) const;
    Q_INVOKABLE void    startServer(const QString& port);
    Q_INVOKABLE void    stopServer();

signals:
    void clientName(QString);
    void errorServer(QString);
    void messageSended(const QString&);
    void sendMsgToGUI(QString);
    void removeClientFromList(QString);
    void stateServerStartedChanged(bool);
};

#endif // SERVERVIEW_H
