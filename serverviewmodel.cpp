
#include "serverviewmodel.h"

ServerViewModel::ServerViewModel(QObject *parent)
    : QObject{parent}
    , server_model(new ServerModel{this})
{
    //clientName
    connect(server_model, &ServerModel::clientName
            , this, &ServerViewModel::clientName);

    //errorServer
    connect(server_model, &ServerModel::errorServer
            , this, &ServerViewModel::errorServer);

    //readFromClient
    connect(server_model, &ServerModel::readFromClient
            , this, &ServerViewModel::readFromClient);

    //removeClientFromList
    connect(server_model, &ServerModel::removeClientFromList
            , this, &ServerViewModel::removeClientFromList);
}

bool ServerViewModel::getStateServerStarted() const
{
    return server_model->getStateServer();
}

bool ServerViewModel::sendMsgToClient(const QString& client, const QString &message) const
{
    return server_model->sendMsgToClient(client, message);
}

bool ServerViewModel::startServer(const QString &port) const
{
    return server_model->startServer(port);
}

bool ServerViewModel::stopServer() const
{
    return server_model->stopServer();
}


