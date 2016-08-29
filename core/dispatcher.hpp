#ifndef _DISPATCHER_HPP_
#define _DISPATCHER_HPP_

#include "client.hpp"
#include "server.hpp"
#include "main_client.hpp"
#include "user.hpp"
#include <vector>
#include <string>
#include <QObject>


class dispatcher : public QObject
{
	Q_OBJECT

private:
    typedef std::vector<Client> clients;
    typedef std::vector<std::string> users;

private:
    // list of users
    clients clients_list;
    // pointer to main client object
    Main_Client* m_client;
    // pointer to server object 
    Server* serv;

    // @name slots for signals
signals:
	void new_message(const QString&, const QString&);

public:
    // send message to signed user
    void send_to(const std::string& u_name, const std::string& message);
    // check if we have connection with signed user
    void clear_clients_list();
    // registration function takes arguments username and password
    bool registration(std::string u_name, std::string u_pass);
    // function login takes arguments username and password
    bool login(std::string u_name, std::string u_pass);
    // function logout
    void logout();
    // gives list of online users
    users get_onlines();
    // gives list of registered users 
    users get_registered_users();
public:
    // constructor takes in argument ip of main_server,and starting main_client
    dispatcher(std::string m_server_ip);
    //destructor
    ~dispatcher();
};


#endif //_DISPATCHER_HPP_
