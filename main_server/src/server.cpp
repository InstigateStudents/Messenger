#include "server.hpp"

//Constructor for class server. Fills the map with info from the database.
main_server::main_server()
{
	std::cout << "SERVER STARTED.." << std::endl;
	signal(SIGPIPE, SIG_IGN); 
	int a;
	std::string l;
	std::string u;
	std::string p;
	std::ifstream file ("../dtb/user_list.txt");
	if (file.is_open()){
		while (!file.eof()){
			getline(file,l);
			if(file.eof()){break;}
			int j;
			for(j = 0; l[j] != ' '; ++j){
				u.insert(j, 1, l[j]);
			}
			j++;
			for(int k = j; l[j] != '\0'; ++j){
				p.insert(j - k, 1, l[j]);
			}
			m_users[u].m_password = p;
			m_users[u].m_IP = "*";
			u = "";
			p = "";
		}      
	}
	file.close();
	run();
}

std::string main_server::parse(std::map<std::string, user_info> mp)
{
	std::string r;
	for(std::map<std::string, user_info>::iterator it = mp.begin(); it != mp.end(); ++it){
		if(it->second.m_IP != "*"){
			r += (it->second.m_IP + ";");
			r += (it->first + "\n");
		}
	}
	return r;
}

//Checks if the given password is correct, and stores the IP address. 
bool main_server::user_login (main_server* server, const std::string user, const std::string password, const std::string IP)
{
	std::cout << "User:" << user << " is logging in "  << std::endl;
	if(server->m_users.count(user) == 0){
		return false;
	}
	if ((server->m_users[user].m_IP != "*")||(server->m_users[user].m_password != password)){
		return false;
	}
	server->m_users[user].m_IP = IP;
	return true;
}
//Deletes the user's IP and marks him as offline.
void main_server::user_logout (main_server* server, const std::string user)
{
	std::cout << "User: " << user << " is logging out " << std::endl;
	server->m_users[user].m_IP = "*";
}
//Creates a new record in the database with the given username and password.
bool main_server::user_register (main_server* server, const std::string user, const std::string password)
{
	std::cout << "User " << user << " successfully registred " << std::endl;
	if(server->m_users.count(user) == 1){
		return false;
	}
	server->m_users[user].m_password = password;
	server->m_users[user].m_IP = "*";
	return true;
}
//Updates the database according to the map.
void main_server::update_file(main_server* server)
{
	while(true){
		FILE * filename = fopen("../dtb/user_list.txt","w");
			for(std::map<std::string, user_info>::iterator it = server->m_users.begin(); it != server->m_users.end(); ++it){
				std::string u = it->first;
				fputs ((u + ' ' + server->m_users[u].m_password + "\n").c_str(), filename);
			}
		fclose(filename);
		sleep(1);
	}
}

//List of all online users.
void main_server::update_online_users(main_server* s)
{
	while(true){
		FILE * filename = fopen("../dtb/online_user_list.txt","w");
			for(std::map<std::string, user_info>::iterator it = s->m_users.begin(); it != s->m_users.end(); ++it){
				std::string u = it->first;
				if(s->m_users[u].m_IP != "*") {
					fputs ((u + ' ' + s->m_users[u].m_IP + "\n").c_str(), filename);
				}
			}
		fclose(filename);
		sleep(1);
	}
}

void main_server::send_to(int m, const std::string& r)
{
	char buf[1024];
	strcpy(buf,r.c_str()); //incorrect =
	if(write(m, buf, strlen(buf)) < 0 ){
            	std::cerr << "Error in writing" << std::endl;
    }
	else{
		bzero(buf,strlen(buf));
	}
}

//Does the communications with the client, and waits for commands.
void main_server::run()
{
	m_master_socket = socket(AF_INET, SOCK_STREAM, 0);
	std::thread(main_server::update_file,this).detach();
	std::thread(main_server::update_online_users,this).detach();
	int n;
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
	while(true){
		bzero((sockaddr *)&client_addr, clientlength);
		n = accept(m_master_socket,(sockaddr *)&client_addr, &clientlength);
		if(!n){
			std::cerr << "Error in accepting" << std::endl;
		}
		else {
			std::string IP = std::to_string(client_addr.sin_addr.s_addr);
			std::thread(main_server::recieve_command, this, n, IP).detach();
		}
	}
}


//Parses the given command and calls the appropriate function.
void main_server::recieve_command(main_server* server, int socket, const std::string IP)
{
	char buf[256];
	while(true){
		bzero(buf,sizeof(buf));
		if(read(socket, buf, 256) <= 0){
			remove_offline_user(server,IP);
			return;
		}
		std::string s = std::string(buf);
		std::string c, u, p;
		int ce = s.find('?');
		c.insert(0, s, 0, ce);
		if(c == "login" || c == "registration" || c == "update"){
			int ue = s.find(';');
			u.insert(0, s, ce+1, ue-ce-1);
			p.insert(0, s, ue+1, s.size()-ue-1);
			if(c == "login"){
				if(user_login(server, u, p, IP)){
					write(socket,"YES",strlen("YES"));
				}
				else{
					write(socket,"NO",strlen("NO"));
				}
			}
			else if (c == "registration"){
				if(user_register(server, u, p)){
					write(socket,"YES",strlen("YES"));
				}
				else{
					write(socket,"NO",strlen("NO"));
				}
			}
			else if (c == "update"){
				std::string r = server->parse(server->m_users);
				send_to(socket,r);
			}
		}
		else if(c == "logout"){
			u.insert(0, s, ce+1, s.size()-ce-1);
			user_logout (server, u);
			write(socket,"YES",strlen("YES"));
		}
		else {
			write(socket,"NO",strlen("NO"));	
		}
	}
}




void main_server::remove_offline_user(main_server* serv, const std::string& IP)
{
	for(std::map<std::string, user_info>::iterator it = serv->m_users.begin(); it != serv->m_users.end(); ++it) {
		if(it->second.m_IP == IP) {
			it->second.m_IP = "*";
		}
	}
}
