#ifndef _USER_HPP_
#define _USER_HPP_
#include <string>
#include <iostream>
#include <stdio.h>

struct User
{
    std::string username;
    std::string current_ip;
    int current_socket;
    User() {}
    User(std::string u, std::string c_i, int c_s)
    {
        username = u;
        current_ip = c_i;
        current_socket = c_s;
    }
};

static std::string get_username_by_ip(std::string ip)
{
    char buf[256];
    std::string line;
    unsigned int pos;
    std::string u_name;
    FILE* fd = fopen("./core/files/ipuser","r");
    if(fd == NULL) {
        std::cerr << "File is not opened";
    }
    while(fgets(buf, 256, fd)) {
        line = std::string(buf);
        pos = line.find(ip);
        if(pos != std::string::npos) {
            u_name = line.substr(pos + ip.length() + 1, line.length());
            return u_name;
        }                
    }
    return NULL; 
}

static std::string get_ip_by_username(std::string u_name) {
    char buf[256];
    std::string line;
    std::string u_ip;
    unsigned int pos;
    FILE* fd = fopen("./core/files/ipuser","r");
    if(fd == NULL) {
        std::cerr << "File is not opened";
    }
    while(fgets(buf, 256, fd)) {
        line = std::string(buf);
        pos = line.find(u_name);
        if(pos != std::string::npos) {  //npos = -1
            u_ip = line.substr(0,pos-1);
            return u_ip;
        }                
    }
    return NULL; 
}

/*
   int main() {
   std::string s = get_username_by_ip("192.168.68.105");
   std::cout << s <<std::endl;
   return 0;
   }
 */

#endif //_USER_HPP_
