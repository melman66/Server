
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include <QDebug>

#include "serverview.h"
#include "config.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/qt/qml/Server/GUI/ServerWindow.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    qmlRegisterType<ServerView>("Server", 1, 0, "ServerView");

    app.setWindowIcon(QIcon(ICON_SOURCE));

    return app.exec();
}
