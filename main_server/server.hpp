#ifndef _SERVER_HPP
#define _SERVER_HPP
#include "user_info.hpp"
#include <map>
#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <thread>
#include <netinet/in.h>
#include <exception>
#include <string.h>
#include <fstream>
class Server{
	int m_master_socket;
	void run(); 
	public:
		std::map<std::string, user_info> m_users;
		static void send_to(Server*,std::string);
		static bool user_login(Server*, std::string, std::string, std::string);
		static void user_logout(Server*, std::string, std::string);
		static bool user_register(Server*, std::string, std::string);
		static void recieve_command(Server*, int, std::string);
		Server();
		std::string parse(std::map<std::string, user_info> mp);
		static void update_file(Server*);
		static void update_online_file(Server*);
};

#endif //_SERVER_HPP
