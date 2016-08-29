#ifndef _CLIENT_HPP_
#define _CLIENT_HPP_
#include "user.hpp"
#include <thread>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <exception>

class client
{
    private:
        user pair;
        static void start_communication(user& p);
    public:
        client(const std::string& u_name);
        user get_pair();
        void send_message(const std::string& message);
};


#endif //_CLIENT_HPP_
