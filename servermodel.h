
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
#include <QThread>

#include "messagesdb.h"

class ServerModel : public QObject
{
    Q_OBJECT

private:
    QTcpServer *server{nullptr};
    MessagesDB *messages_db{nullptr};
    QThread    *thread_db{nullptr};

    quint16     next_block_size;
    quint16     port_num;

    QMap <QTcpSocket*, QString> clients;

    bool stateServer{ false };

private:
    bool createDB();
    bool sendMsgToClient(const QString &message, QTcpSocket* client_socket, bool saveToDB = {true});

public:
    explicit ServerModel(QObject *parent = nullptr);

    bool getStateServer() const;
    bool sendMsgToClient(const QString& client, const QString& message, bool saveToDB = {true});
    bool startServer(const QString& s_port);
    bool stopServer();

private slots:
    virtual void slotNewConnection();
            void slotReadFromClient();
            void slotClientDisconnected();

signals:
    void clientName(QString);
    void errorServer(QString);
    void sendMsgToGUI(QString);
    void removeClientFromList(QString);
    void stateServerChanged(bool);

};

#endif // SERVERMODEL_H
