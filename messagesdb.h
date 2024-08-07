
#ifndef MESSAGESDB_H
#define MESSAGESDB_H


#include <QObject>
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QFile>
#include <QDateTime>
#include <QStandardPaths>
#include <QDir>

#include "config.h"

class MessagesDB : public QObject
{
    Q_OBJECT

    QSqlDatabase messages_db;
    bool stateDB;

private:
    bool openDatabase(const QString &path_db, const QString &host, const QString &username);

public:
    explicit MessagesDB(QObject *parent, const QString &host, const QString &username);
    explicit MessagesDB(const QString &host, const QString &username);
    virtual ~MessagesDB();

    void addMessage(const QString& sender_name, const QString& sender_address, const QString& msg);
    void closeDatabase();
    bool dbIsOpen() const;
    //bool openDatabase(const QString &path_db, const QString &host, const QString &username);

};

#endif // MESSAGESDB_H
