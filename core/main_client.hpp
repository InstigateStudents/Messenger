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


class Main_Client {
    private :
        //socket for connection with main server
        int main_socket;
        User me;
        //connect with main server
        static void connect_server(int main_socket,std::string serv_ip);
    public:
        //default constructor for starting
        Main_Client(std::string serv_ip);
        //user registration
        bool registration(std::string u_name, std::string u_password);
        //login through username and password   
        bool login(std::string u_name, std::string u_password);
        //takes list of online users from main server 
        void give_online_list();        
        //takes list of registered users
        void give_registered_list();
        //logout by user profile
        bool logout();

};

#endif //_MAIN_CLIENT_HPP_
