#ifndef _DISPATCHER_HPP_
#define _DISPATCHER_HPP_

#include "client.hpp"
#include "server.hpp"
#include "main_client.hpp"
#include "user.hpp"
#include <vector>
#include <string>

class Dispatcher {
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
    void registration(std::string u_name, std::string u_pass);
    // slot login
    void login(std::string u_name, std::string u_pass);
    // slot logout
    void logout();
    ~Dispatcher();
};


#endif //_DISPATCHER_HPP_
