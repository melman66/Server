
#include "servermodel.h"

ServerModel::ServerModel(QObject *parent)
    : port_num{0}
    , QObject{parent}
    , server{new QTcpServer{this}}
    , messages_db{nullptr}
    , next_block_size{0}
{}

QString ServerModel::readIpFromFile(const QString &file_path)
{
    QFile file(file_path);
    QString ip{""};

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        emit readFromClient("file with ip is not open!");
        return ip;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        ip = ip + in.readLine();
    }
    return ip;
}

bool ServerModel::getStateServer() const
{
    return server->isListening();
}

bool ServerModel::sendMsgToClient(const QString &message)
{
    QByteArray arrDataBlock;
    QDataStream out(&arrDataBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_6);

    out << quint16(0)
        << message;

    out.device()->seek(0);
    out << quint16(arrDataBlock.size() - sizeof(quint8));

    for(auto &i : clients)
        clients.key(i)->write(arrDataBlock);

    if (messages_db->dbIsOpen()){
        messages_db->addMessage("server", server->serverAddress().toString(), message);
    }

    return true;
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
    QString      ipString = readIpFromFile("StringLocalIpAddressForServer.txt");

    if(ipString == "") {
        emit readFromClient("IP file is empty.\n"
                            "The first unoccupied address will be generated");

        const QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
        for (const QHostAddress &entry : ipAddressesList) {
            if (entry != QHostAddress::LocalHost && entry.toIPv4Address()) {
                ipAddress = entry;
                break;
            }
        }
    }
    else
        ipAddress = QHostAddress{ipString};

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

    forever{
        if(!next_block_size){
            if(client_socket->bytesAvailable() < sizeof(quint16))
                break;
            in >> next_block_size;
        }
        in >> msg;

        next_block_size = 0;
    }
    if(clients[client_socket] == QString{""}){
        if(clients.key(msg)) {
            while(clients.key(msg))
                msg = msg + "1";
            sendMsgToClient(QString{"Your name is occuped. Your new name on server: " + msg}
                            , client_socket);
        }

        clients[client_socket] = msg;
        emit clientName(msg);
        return;
    }

    if (messages_db->dbIsOpen()){
        messages_db->addMessage(clients[client_socket]
                                , client_socket->localAddress().toString(), msg);
    }

    emit readFromClient(QDate::currentDate().toString() + "   "
                        + QTime::currentTime().toString()+"\n"
                        + clients[client_socket] + ":\n"
                        +msg);
}
