
#include "messagesdb.h"

MessagesDB::MessagesDB(QObject *parent, const QString &host, const QString &username)
    : QObject{parent}, stateDB{false}
{
    stateDB = openDatabase("messages_db.accdb", host, username);
    qDebug() << messages_db.lastError();
}

MessagesDB::~MessagesDB()
{
    if (stateDB)
        messages_db.close();
}

void MessagesDB::addMessage(const QString& sender_name, const QString& sender_address
                            , const QString& msg)
{
    QSqlQuery query = QSqlQuery(messages_db);

    query.prepare("INSERT INTO messages (sender_name, sender_address, msg_text, send_time)"
                  " VALUES (:name, :address, :msg, :time)");
    query.bindValue(":name", sender_name);
    query.bindValue(":address", sender_address);
    query.bindValue(":msg", msg);
    query.bindValue(":time", QDateTime::currentDateTime());

    query.exec();
}

void MessagesDB::closeDatabase()
{
    messages_db.close();
}

bool MessagesDB::dbIsOpen() const
{
    return stateDB;
}

bool MessagesDB::openDatabase(const QString &name_file_db, const QString &host, const QString &username)
{
    QString dsn_string = QString("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};FIL={MS Access};DBQ=%1")
                             .arg(QDir::currentPath() + "/" + name_file_db);
    qDebug() << QDir::currentPath() + "/" + name_file_db;

    messages_db = QSqlDatabase::addDatabase("QODBC");

    messages_db.setDatabaseName(dsn_string);
    messages_db.setHostName(host);
    messages_db.setUserName(username);
    messages_db.setPassword("admin");

    return messages_db.open();
}


