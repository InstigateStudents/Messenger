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
signals:
	void receive_message(const QString&, const QString&);

    private:
        //starting server, create socket,bind,listen,accept
        static void start_server(Server* s);
        // read message and print in stdout
        static void read_message(Server* s, User u);
    public:
        // default constructor
        Server();
        //close all sockets
        void stop_server();
};


#endif //_SERVER_HPP_
