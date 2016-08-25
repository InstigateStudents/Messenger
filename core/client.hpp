#ifndef _CLIENT_HPP_
#define _CLIENT_HPP_
#include "user.hpp"
#include <thread>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

class Client {
    private:
        User pair;
        static void start_communication(User p);
    public:
        Client(std::string u_name);
        User get_pair();
        void send_message(std::string message);
};


#endif //_CLIENT_HPP_
