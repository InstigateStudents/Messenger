#ifndef _SERVER_HPP_
#define _SERVER_HPP_
#include <thread>
#include <string>
#include <vector>
#include "user.hpp"

class Server
{
    private:
        //starting server, create socket,bind,listen,accept
        static void start_server();
        // read message and print in stdout
        static void read_message(User u);
    public:
        // default constructor
        Server();
        //close all sockets
        void stop_server();
};


#endif //_SERVER_HPP_
