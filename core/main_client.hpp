#ifndef _MAIN_CLIENT_HPP_
#define _MAIN_CLIENT_HPP_
#include "user.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <thread>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <exception>
#include <cassert>


class main_client
{
    private :
        //socket for connection with main server
        int m_main_socket;
        user m_me;
        //connect with main server
        static void connect_server(int& m_main_socket,const std::string& serv_ip);
    public:
        //default constructor for starting
        main_client(const std::string& serv_ip);
        //user registration
        bool registration(const std::string& u_name,const std::string& u_password);
        //login through username and password   
        bool login(const std::string& u_name,const std::string& u_password);
        //takes list of online users from main server 
        void give_online_list();        
        //takes list of registered users
        void give_registered_list();
        //logout by user profile
        bool logout();
};

#endif //_MAIN_CLIENT_HPP_
