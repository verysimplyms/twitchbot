#include <QCoreApplication>
#include "sockettest.h"

int main(int argc, char *argv[])
{
   QCoreApplication a(argc, argv);

   SocketTest cTest;
   //Password = oauth key
   cTest.Listen("irc.chat.twitch.tv", 6667, "oauth", "username", "username", "channel name");

    return a.exec();
}
