
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "serverview.h";

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/Server/GUI/ServerWindow.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    qmlRegisterType<ServerView>("Server", 1, 0, "ServerView");


    return app.exec();
}
