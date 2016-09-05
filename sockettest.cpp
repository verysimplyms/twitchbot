#include "sockettest.h"
#include <array>

SocketTest::SocketTest(QObject *parent) : QObject(parent), IRCsocket(new QTcpSocket(this))
{
    qDebug() << "IRCBot Object Created";
}

void SocketTest::Listen(QString server, int port, QString password, QString username, QString nickname, QString channel) const
{
    connect(IRCsocket, SIGNAL(connected()), this, SLOT(connected()));
    connect(IRCsocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(IRCsocket, SIGNAL(readyRead()), this, SLOT(readyRead()));

   IRCsocket->connectToHost(server, port);

    if(!IRCsocket->waitForConnected()) {
        qDebug() << "Could not connect: " << IRCsocket->errorString();
    } else {
        qDebug() << "Connected successfully! ";
    }
}

void SocketTest::sendPass(QString password) const
{
    QByteArray package;
    package.append("PASS ");
    package.append(password);
    package.append("\r\n");
    IRCsocket->write(package);
    IRCsocket->flush();
}

void SocketTest::sendUser(QString username) const
{
    QByteArray package;
    package.append("USER ");
    package.append(username);
    package.append(" 8 *: ");
    package.append(username);
    package.append("\r\n");

    IRCsocket->write(package);
    IRCsocket->flush();
}

void SocketTest::sendNick(QString nickname) const
{
    QByteArray package;
    package.append("NICK ");
    package.append(nickname);
    package.append("\r\n");
    IRCsocket->write(package);
    IRCsocket->flush();
}

void SocketTest::sendJoin(QString channel) const
{
    QByteArray package;
    package.append("JOIN #");
    package.append(channel);
    package.append("\r\n");
    IRCsocket->write(package);
    IRCsocket->flush();
}

void SocketTest::readyRead()
{
    QByteArray array;
    while(!(array = IRCsocket->readLine()).isNull()) {
        qDebug() << array;
        QRegExp rx("[:]");
        QString test = array;
        QStringList list = test.split(rx, QString::SkipEmptyParts);

        if(list.size() >= 2) {
            qDebug() << list[1];
        }
    }
}

void SocketTest::connected()
{
    this->sendPass("oauth key");
    this->sendUser("username");
    this->sendNick("username");
    this->sendJoin("channel name");
}

void SocketTest::disconnected() {

}
