#ifndef _DISPATCHER_HPP_
#define _DISPATCHER_HPP_

#include "client.hpp"
#include "server.hpp"
#include "main_client.hpp"
#include "user.hpp"
#include <vector>
#include <string>

#include <QObject>
//#include <QApplication>


class Dispatcher : public QObject{

	Q_OBJECT

signals:
	void new_message(const QString&, const QString&);

private:
    // list of users
    std::vector<Client> clients_list;
    // pointer to main client object
    Main_Client* m_client;
    // pointer to server object 
    Server* serv;
public:
    // constructor for start main_client and server
    Dispatcher();
    // send message to signed user
    void send_to(std::string u_name, std::string message);
    // check if we have connection with signed user
    void clear_clients_list();
    // slot registration 
    bool registration(std::string u_name, std::string u_pass);
    // slot login
    bool login(std::string u_name, std::string u_pass);
    // slot logout
    void logout();
    // gives list of online users
    std::vector<std::string> get_onlines();

    ~Dispatcher();
};


#endif //_DISPATCHER_HPP_
