
#include "serverview.h"

ServerView::ServerView(QObject *parent)
    : QObject{parent}
    , server_view_model{new ServerViewModel{this}}
{
    //clientName
    connect(server_view_model, &ServerViewModel::clientName
            , this, &ServerView::clientName);

    //errorServer
    connect(server_view_model, &ServerViewModel::errorServer
            , this, &ServerView::errorServer);

    //readFromClient
    connect(server_view_model, &ServerViewModel::readFromClient
            , this, &ServerView::readFromClient);

    //removeClientFromList
    connect(server_view_model, &ServerViewModel::removeClientFromList
            , this, &ServerView::removeClientFromList);
}

bool ServerView::getStateServerStarted() const
{
    return server_view_model->getStateServerStarted();
}

QString ServerView::getCurrentDateTime() const
{
    return QString{QDate::currentDate().toString() + "   "
                   + QTime::currentTime().toString()};
}

bool ServerView::sendMsgToClient(const QString& message) const
{
    return server_view_model->sendMsgToClient(message);
}

void ServerView::startServer(const QString &port)
{
    stateServerStarted = server_view_model->startServer(port);

    emit stateServerStartedChanged(stateServerStarted);
}

void ServerView::stopServer()
{
    stateServerStarted = server_view_model->stopServer();

    emit stateServerStartedChanged(stateServerStarted);
}







