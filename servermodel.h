
#ifndef SERVERMODEL_H
#define SERVERMODEL_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTime>
#include <QDate>
#include <QList>
#include <QMap>
#include <QHostInfo>
#include <QNetworkInterface>
#include <QDir>

#include "messagesdb.h"

class ServerModel : public QObject
{
    Q_OBJECT

private:
    QTcpServer *server;
    MessagesDB *messages_db;

    quint16     next_block_size;
    quint16     port_num;

    QMap <QTcpSocket*, QString> clients;

    bool stateServer{ false };

public:
    explicit ServerModel(QObject *parent = nullptr);

    QString readIpFromFile(const QString& file_path);

    bool getStateServer() const;
    bool sendMsgToClient(const QString& message);
    bool sendMsgToClient(const QString &message, QTcpSocket* client_socket);
    bool startServer(const QString& port);
    bool stopServer();

private slots:
    virtual void slotNewConnection();
            void slotReadFromClient();
            void slotClientDisconnected();

signals:
    void clientName(QString);
    void errorServer(QString);
    void readFromClient(QString);
    void removeClientFromList(QString);
    void stateServerChanged(bool);

};

#endif // SERVERMODEL_H
