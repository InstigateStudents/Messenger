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
#define LOGOUT 1111

class main_client
{
    private :
        //socket for connection with main server
        int m_main_socket;
        user m_me;
        //thread for receive online list
 //       std::thread m_list_receiver_thread;
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
        static void give_online_list(int m_m_s);        
        //logout by user profile
        bool logout();
        std::thread m_online_list_thread;
        static void term(int s);
};

#endif //_MAIN_CLIENT_HPP_
