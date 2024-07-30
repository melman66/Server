
#include "servermodel.h"

ServerModel::ServerModel(QObject *parent)
    : port_num{0}
    , QObject{parent}
    , server{new QTcpServer{this}}
    , messages_db{nullptr}
    , next_block_size{0}
{}
//PRIVATE
bool ServerModel::sendMsgToClient(const QString& client, const QString &message)
{
    if(clients.key(client))
        return sendMsgToClient(message, clients.key(client));
    else
        return false;
}

//PUBLIC
bool ServerModel::getStateServer() const
{
    return server->isListening();
}

bool ServerModel::sendMsgToClient(const QString &message, QTcpSocket *client_socket)
{
    QByteArray arrDataBlock;
    QDataStream out(&arrDataBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_6);

    out << quint16(0)
        << message;

    out.device()->seek(0);
    out << quint16(arrDataBlock.size() - sizeof(quint8));

    client_socket->write(arrDataBlock);

    if (messages_db->dbIsOpen()){
        messages_db->addMessage("server", server->serverAddress().toString(), message);
    }

    return true;
}

bool ServerModel::startServer(const QString& s_port)
{
    port_num = s_port.toUInt();
    server = new QTcpServer{this};

    if ((port_num < 49152) || (port_num > 65535))
        return false;

    QHostAddress ipAddress;

    QHostInfo info = QHostInfo::fromName(QHostInfo::localHostName());
    ipAddress = info.addresses().last();

    if (!server->listen(ipAddress, port_num)){
        emit errorServer(server->errorString());
        return false;
    }
    else
        emit readFromClient("Server is started. IP: " + ipAddress.toString()
                            + " port: " + s_port);

    //newConnection
    connect(server, &QTcpServer::newConnection
            , this, &ServerModel::slotNewConnection);

    //errors
    connect(server, &QTcpServer::acceptError
            , [&](){
                emit stateServerChanged(false);
                emit errorServer(server->errorString());
            });

    messages_db = new MessagesDB{this, server->serverAddress().toString(), "server"};

    if (messages_db->dbIsOpen())
        emit readFromClient("Database is open.");
    else
        emit readFromClient("Database is not open.");

    stateServer = server->isListening();

    return stateServer;
}

bool ServerModel::stopServer()
{
    stateServer = false;
    server->close();

    for(auto &i: clients){
        clients.key(i)->deleteLater();
    }
    clients.clear();

    messages_db->closeDatabase();
    messages_db->deleteLater();

    emit readFromClient("Server is stoped");

    return stateServer;
}

//SLOTS
void ServerModel::slotClientDisconnected()
{
    emit removeClientFromList(clients[(QTcpSocket*)sender()]);

    clients.remove((QTcpSocket*)sender());
}

void ServerModel::slotNewConnection()
{
    QTcpSocket *temp_socket = server->nextPendingConnection();

    clients.insert(temp_socket, QString{""});

    //disconnected
    connect(temp_socket, &QTcpSocket::disconnected
            , this, &ServerModel::slotClientDisconnected);

    //readyRead
    connect(temp_socket, &QTcpSocket::readyRead
            , this, &ServerModel::slotReadFromClient);
}

void ServerModel::slotReadFromClient()
{
    QTcpSocket* client_socket = (QTcpSocket*)sender();
    QDataStream in(client_socket);
    in.setVersion(QDataStream::Qt_6_6);

    QString msg;

    //read message from socket
    forever{
        if(!next_block_size){
            if(client_socket->bytesAvailable() < sizeof(quint16))
                break;
            in >> next_block_size;
        }
        in >> msg;

        next_block_size = 0;
    }

    //add to clients map
    if(clients[client_socket] == QString{""}){
        if(clients.key(msg)) {
            while(clients.key(msg))
                msg = msg + "1";
        }
        sendMsgToClient(msg, client_socket);
        clients[client_socket] = msg;
        emit clientName(msg);
        return;
    }

    //add message to database
    if (messages_db->dbIsOpen()){
        messages_db->addMessage(clients[client_socket]
                                , client_socket->localAddress().toString(), msg);
    }

    //send message to GUI
    emit readFromClient(QDate::currentDate().toString() + "   "
                        + QTime::currentTime().toString()+"\n"
                        + clients[client_socket] + ":\n"
                        +msg);
}
