#ifndef _SERVER_HPP_
#define _SERVER_HPP_
#include <thread>
#include <string>
#include <vector>
#include "user.hpp"

#include <QObject>
#include <QString>


class Server: public QObject
{
	Q_OBJECT
//signal for receive_messages
signals:
	void receive_message(const QString&, const QString&);

    private:
        //starting server, create socket,bind,listen,accept
        static void start_server(Server* s);
        // read message and give signal
        static void read_message(Server* s, User u);
    public:
        // default constructor
        Server();
};


#endif //_SERVER_HPP_
