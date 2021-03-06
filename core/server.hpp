#ifndef _SERVER_HPP_
#define _SERVER_HPP_
#include <thread>
#include <string>
#include <vector>
#include <exception>
#include "user.hpp"
#include <QObject>
#include <QString>


class server: public QObject
{
	Q_OBJECT
signals:
    //signal for receive_messages
    void receive_message(const QString&, const QString&);

private:
    //vector for opened sockets
    std::vector<int> m_sockets_id;
    //starting server, create socket,bind,listen,accept
    static void start_server(server* s);
    // read message and give signal
    static void read_message(server* s, user& u);
public:
    // default constructor
    server();
    ~server();
};


#endif //_SERVER_HPP_
