#ifndef SOCKETTEST_H
#define SOCKETTEST_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QMap>
#include <functional>
class SocketTest : public QObject
{
    Q_OBJECT
public:
    explicit SocketTest(QObject *parent = 0);
    void Listen(QString server, int port, QString password, QString username, QString nickname, QString channel) const;
    void sendMessage(QString message, QString channel) const;
signals:

public slots:

private:
    void sendPass(QString password) const;
    void sendUser(QString username) const;
    void sendNick(QString nickname) const;
    void sendJoin(QString channel) const;
    QTcpSocket *IRCsocket;

private slots:
  void connected();
  void disconnected();
  void readyRead();
};

#endif // SOCKETTEST_H
