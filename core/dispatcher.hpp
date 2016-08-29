#ifndef _DISPATCHER_HPP_
#define _DISPATCHER_HPP_

#include "client.hpp"
#include "server.hpp"
#include "main_client.hpp"
#include "user.hpp"
#include <vector>
#include <string>
#include <QObject>


class Dispatcher : public QObject {

	Q_OBJECT
//slots for signals
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
    // constructor takes in argument ip of main_server,and starting main_client
    Dispatcher(std::string m_server_ip);
    // send message to signed user
    void send_to(std::string u_name, std::string message);
    // check if we have connection with signed user
    void clear_clients_list();
    // registration function takes arguments username and password
    bool registration(std::string u_name, std::string u_pass);
    // function login takes arguments username and password
    bool login(std::string u_name, std::string u_pass);
    // function logout
    void logout();
    // gives list of online users
    std::vector<std::string> get_onlines();
    // gives list of registered users 
    std::vector<std::string> get_registered_users();
    //destructor
    ~Dispatcher();
};


#endif //_DISPATCHER_HPP_
