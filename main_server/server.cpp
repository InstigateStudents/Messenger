#include "server.hpp"

//Constructor for class server. Fills the map with info from the database.
Server::Server()
{
	int a;
	std::string line;
	std::string username;
	std::string password;
	std::ifstream file ("../dtb/user_list.txt");
	if (file.is_open()){
		while (!file.eof()){
			getline(file,line);
			if(file.eof()){break;}
			int j;
			for(j = 0; line[j] != ' '; ++j){
				username.insert(j, 1, line[j]);
			}
			j++;
			for(int k = j; line[j] != '\0'; ++j){
				password.insert(j - k, 1, line[j]);
			}
			m_users[username].m_pswd = password;
			m_users[username].IP = "*";
			std::cout << username << ' ' << password << std::endl;	
			username = "";
			password = "";
		}      
	}
	file.close();
	run();
}

std::string Server::parse(std::map<std::string, user_info> mp)
{
	std::string result;
	for(std::map<std::string, user_info>::iterator it = mp.begin(); it != mp.end(); ++it) {
		if(it->second.IP != "*") {
			result += (it->second.IP + ";");
			result += (it->first + "\n");
		}
	}
	return result;
}



//Checks if the given password is correct, and stores the IP address. 
bool Server::user_login (Server* server, std::string usr, std::string pswd, std::string IP)
{
	std::cout << "Login " << usr << " " << pswd << std::endl;
	if ((server->m_users[usr].IP != "*")||(server->m_users[usr].m_pswd != pswd)) {
		return false;
	}
	server->m_users[usr].IP = IP;
	return true;
}
//Deletes the user's IP and marks him as offline.
void Server::user_logout (Server* server, std::string usr, std::string pswd)
{
	std::cout << "Logout " << usr << " " << pswd << std::endl;
	server->m_users[usr].IP = "*";
}
//Creates a new record in the database with the given username and password.
bool Server::user_register (Server* server, std::string usr, std::string pswd)
{
	std::cout << "Register " << usr << " " << pswd << std::endl;
	if(server->m_users.count(usr) == 1){
		return false;
	}
	server->m_users[usr].m_pswd = pswd;
	server->m_users[usr].IP = "*";
	return true;
}
//Updates the database according to the map.
void Server::update_file(Server* server)
{
	while(true) {
		FILE * filename = fopen("../dtb/user_list.txt","w");
			for(std::map<std::string, user_info>::iterator it = server->m_users.begin(); it != server->m_users.end(); ++it){
				std::string usr = it->first;
				fputs ((usr + ' ' + server->m_users[usr].m_pswd + "\n").c_str(), filename);
			}
		fclose(filename);
		sleep(1);
	}
}
//List of all online users.
void Server::update_online_file(Server* s)
{
	while(true) {
		FILE * filename = fopen("../dtb/online_user_list.txt","w");
			for(std::map<std::string, user_info>::iterator it = s->m_users.begin(); it != s->m_users.end(); ++it){
				std::string usr = it->first;
				if(s->m_users[usr].IP != "*") {
					fputs ((usr + ' ' + s->m_users[usr].IP + "\n").c_str(), filename);
				}
			}
		fclose(filename);
		// parser function that returns string
		std::string r = s->parse(s->m_users);
		std::cout << r << std::endl;
		send_to(s,r);
		sleep(5);
	}
}

void Server::send_to(Server* s,std::string r)
{
	int s_master_socket;
	s_master_socket = socket(AF_INET, SOCK_STREAM,0);
	sockaddr_in pair_addr;
        char buf[1024];
	strcpy(buf,r.c_str()); //incorrect =
	bzero((sockaddr*)&pair_addr, sizeof(pair_addr));
	pair_addr.sin_family = AF_INET;
	pair_addr.sin_port = htons(12345);
	for (std::map<std::string,user_info>::iterator it = s->m_users.begin();it != s->m_users.end(); ++it) {
		 bzero((sockaddr*)&pair_addr, sizeof(pair_addr));
		 std::string usr = it->first;
		 if (s->m_users[usr].IP != "*"){
	 		pair_addr.sin_addr.s_addr = std::stoi(s->m_users[usr].IP);
         		if(connect(s_master_socket, (sockaddr *)&pair_addr, sizeof(pair_addr)) < 0) {
	 			std::cerr << "Error in connection" << std::endl;
	 		}
	 	 	else {
					if(write(s_master_socket, buf, strlen(buf)) < 0 ) {
            					std::cerr << "Error in writing" << std::endl;
        				}
    			}
		}
	
	}
}
//Does the communications with the client, and waits for commands.
void Server::run()
{
	m_master_socket = socket(AF_INET, SOCK_STREAM, 0);
	std::thread(Server::update_file,this).detach();
	std::thread(Server::update_online_file,this).detach();
	int newsocket;
	sockaddr_in serv_addr, client_addr;
	socklen_t clientlength;
	bzero((sockaddr *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(12345);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	if(bind(m_master_socket,(sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		std::cerr << "Error in binding" << std::endl;
	}
	listen(m_master_socket,10);
	clientlength = sizeof(client_addr);
	while(true) {
		bzero((sockaddr *)&client_addr, clientlength);
		newsocket = accept(m_master_socket,(sockaddr *)&client_addr, &clientlength);
        std::cout << client_addr.sin_addr.s_addr << std::endl;
		if(!newsocket) {
			std::cerr << "Error in accepting" << std::endl;
		}
		else {
			std::string IP = std::to_string(client_addr.sin_addr.s_addr);
			std::thread(Server::recieve_command, this, newsocket, IP).detach();
		}
	}
}

//Parses the given command and calls the appropriate function.
void Server::recieve_command(Server* server, int socket, std::string IP)
{
	while(true) {
		char buf[256];
		bzero(buf,sizeof(buf));
		if(read(socket, buf, 256) < 0) {
			std::cerr << "Error in reading" << std::endl;
		}
		std::cout << "after read" <<std::endl;
		std::string s = std::string(buf);
		std::cout << s << std::endl;
		std::string command, username, password;
		int command_end = s.find('?');
		command.insert(0, s, 0, command_end);
		std::cout << command << "\n";
		if(command == "login" || command == "registration") {
			std::cout << "break" << std::endl;
			int username_end = s.find(';');
			username.insert(0, s, command_end+1, username_end-command_end-1);
			std::cout << username << "\n";
			password.insert(0, s, username_end+1, s.size()-username_end-1);
			if(command == "login") {
				user_login(server, username, password, IP);
			}
			else {	
				user_register(server, username, password);
			}
		}
		else if(command == "logout") {
			username.insert(0, s, command_end+1, s.size()-command_end-1);
			std::cout << username << "\n";
			user_logout (server, username, password);
		}
		else {
			std::cout << "wrong command\n";

		}
	}
}
