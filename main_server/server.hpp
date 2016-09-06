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
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <pwd.h>
#include <signal.h>
#include <sys/mman.h>

/**
 * @brief main_server
 *  
 */
class main_server
{
private:
	typedef std::map<std::string, user_info> user_name_to_info;
private:
	int m_master_socket;
	user_name_to_info m_users;
private:
	/**
	 * This function is automatically called when a server instance is created.
	 * It is used to start the update_file and update_online_users threads,
	 * manage communications with the client and call the receive command
	 * function when a command is given.
	 */
	void run(); 
public:
	/**
	 * Sends the list of all online users to all online users once.
     * @param i - socket to which the list will sent
     * @param s - The string that must be sent to all online clients. It
     * contains all the online users and their addresses in correct format.
     * This string is built with parse function.
	 */
	static void send_to(int i, const std::string& s);

	/**
	 * Checks if the username and password match. If they do it marks that
	 * person as online, and stores his address in the map.
	 * @param A pointer to a main_server object who's map is going to be changed.
	 * @param The username of the person wanting to log in.
	 * @param The password.
	 * @param The address from which the command was sent.
	 */
	static bool user_login(main_server*, const std::string&, const std::string&, const std::string&);

	/**
	 * Marks the user as offline and deletes the person's address from the map.
	 * @param A point to a main_server object who's map is going to be changed.
	 * @param The username of the person wishing to logout.
	 * @param His password.
	 */
	static void user_logout(main_server*, const std::string&);

	/**
	 * Checks if the username is taken and creates a new record of a person
	 * with the given username and password.
     * @param A pointer to a main_server object who's map is going to be
     * changed.
	 * @param The desired username.
	 * @param It's password
	 */
	static bool user_register(main_server*, const std::string&,
            const std::string&);

	/**
	 * Reads the client's input, calls the appropriate command function
	 * depending on the string received from the client.
	 * @param A pointer to a main_server object who's map is going to be used
	 * in later functions.
	 * @param Client's socket.
	 * @param IP address of the client.
	 */
	static void recieve_command(main_server*, int, const std::string&);

	/**
	 * Turns a map of users into a string of online users and their addresses
	 * that can be transfered to the client.
	 * @param The original map
	 */
	std::string parse(user_name_to_info);

	/**
	 * Updates the database every 5 seconds
	 * @param A pointer to a main_server object who's map is going to be used
	 * to update.
	 */
	static void update_file(main_server*);

	/**
	 * Updates the list of online users and sends the parsed map to all online
	 * users once every second. 
	 * @param A pointer to a main_server object who's map is going to be used
	 * to determine online users.
	 */
	static void update_online_users(main_server*);
	
	static void remove_offline_user(main_server*,const std::string&);	
public:
	/**
	 * Constructor for main_server object. Reads the contents of a database and
	 * fills the map with it.
	 */
	main_server();
};

#endif //_SERVER_HPP
