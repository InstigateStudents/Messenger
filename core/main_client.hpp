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
#include <csignal>

class main_client
{
    private :
        //socket for connection with main server
        int m_main_socket;
        //information about current logged user
        user m_me;
        //flag checking logout
        bool m_logout_flag;
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
        static void give_online_list(main_client* m_s);        
        //logout by user profile
        bool logout();
};

#endif //_MAIN_CLIENT_HPP_
