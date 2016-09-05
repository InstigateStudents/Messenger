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
#include <cassert>

class client
{
private:
    //user we want to connect
    user pair;
    //connection start
    static void start_communication(user& p);
public:
    //constructor, receives as argument the user for connecting
    client(const std::string& u_name);
    //returns pair
    user get_pair();
    //function for sending message, receives as argument username and message text
    void send_message(const std::string& message);
};

#endif //_CLIENT_HPP_
