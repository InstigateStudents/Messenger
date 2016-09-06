#include "server.hpp"

#include <cassert>

/// TODO This is temporary solution, shold be made parametric
std::string g_path = "main_server/dtb";

main_server::main_server()
{
	std::cout << "SERVER STARTED.." << std::endl;
	signal(SIGPIPE, SIG_IGN); 
	std::string l, u, p;
	std::ifstream file(g_path + "/user_list.txt");
	if (file.is_open()) {
		while (!file.eof()) {
			getline(file, l);
			if (file.eof()){break;}
			int j;
			for (j = 0; l[j] != ' '; ++j){
				u.insert(j, 1, l[j]);
			}
			j++;
			for (int k = j; l[j] != '\0'; ++j){
				p.insert(j - k, 1, l[j]);
			}
			m_users[u].m_password = p;
			m_users[u].m_ip = "*";
			u = "";
			p = "";
		}      
		file.close();
		run();
	} else {
		std::cerr << "Unable to read the database" << std::endl;
		exit(1);
	}
}

std::string main_server::parse(user_name_to_info m)
{
	std::string r;
    user_name_to_info::iterator i = m.begin();
	for (; i != m.end(); ++i){
		if (i->second.m_ip != "*"){
			r += (i->second.m_ip + ";");
			r += (i->first + "\n");
		}
	}
	return r;
}

bool main_server::user_login (main_server* s, const std::string& u, const std::string& p, const std::string& i)
{
    assert (0 != s);
    assert (!u.empty());
    assert (!p.empty());
    assert (!i.empty());
	std::cout << "User:" << u << " is logging in "  << std::endl;
	if (s->m_users.count(u) == 0){
		return false;
	}
	if ((s->m_users[u].m_ip != "*")||(s->m_users[u].m_password != p)){
		return false;
	}
	s->m_users[u].m_ip = i;
	return true;
}

void main_server::user_logout (main_server* s, const std::string& u)
{
    assert (0 != s);
    assert (!u.empty());
	std::cout << "User: " << u << " is logging out " << std::endl;
	s->m_users[u].m_ip = "*";
}

bool main_server::user_register(main_server* s, const std::string& u,
        const std::string& p)
{
    assert(0 != s);
    assert(!u.empty());
    assert(!p.empty());
	std::cout << "User " << u << " successfully registered " << std::endl;
	if (1 == s->m_users.count(u)) {
		return false;
	}
	s->m_users[u].m_password = p;
	s->m_users[u].m_ip = "*";
	return true;
}

void main_server::update_file(main_server* s)
{
    assert(0 != s);
	while (true) {
		std::string p = g_path + "/user_list.txt";
		FILE* f = fopen(p.c_str(), "w");
        if (f == NULL) {
            std::cerr << "Can't open file " << std:: endl;
            exit(1);
        }
	    user_name_to_info::iterator i = s->m_users.begin();
        for (; i != s->m_users.end(); ++i){
            std::string u = i->first;
            fputs((u + ' ' + s->m_users[u].m_password + "\n").c_str(), f);
        }
		fclose(f);
		sleep(1);
	}
}

void main_server::update_online_users(main_server* s)
{
    assert (0 != s );
	while (true) {
		std::string p = g_path + "/online_user_list.txt";
		FILE* filename = fopen(p.c_str(), "w");
            if ( filename == NULL ) {
                std::cerr << "Can't open file " << std::endl;
                exit(1);
            }
            user_name_to_info::iterator i = s->m_users.begin();
			for (; i != s->m_users.end(); ++i){
				std::string u = i->first;
				if (s->m_users[u].m_ip != "*") {
					fputs ((u + ' ' + s->m_users[u].m_ip + "\n").c_str(), filename);
				}
			}
		fclose(filename);
		sleep(1);
	}
}

void main_server::send_to(int m, const std::string& r)
{
    assert (!r.empty());
	char buf[1024];
	strcpy(buf, r.c_str());
	if (write(m, buf, strlen(buf)) < 0 ){
            	std::cerr << "Error in writing" << std::endl;
    } else {
            bzero(buf,strlen(buf));
	  }
}

void main_server::run()
{
	m_master_socket = socket(AF_INET, SOCK_STREAM, 0);
	std::thread(main_server::update_file, this).detach();
	std::thread(main_server::update_online_users, this).detach();
	int n;
	sockaddr_in serv_addr, client_addr;
	socklen_t clientlength;
	bzero((sockaddr *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(12345);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(m_master_socket,(sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		std::cerr << "Error in binding" << std::endl;
	}
	listen(m_master_socket,10);
	clientlength = sizeof(client_addr);
	while (true){
		bzero((sockaddr *)&client_addr, clientlength);
		n = accept(m_master_socket,(sockaddr *)&client_addr, &clientlength);
		if (!n){
			std::cerr << "Error in accepting" << std::endl;
		} else {
			    std::string IP = std::to_string(client_addr.sin_addr.s_addr);
			    std::thread(main_server::recieve_command, this, n, IP).detach();
		  }
	}
}


void main_server::recieve_command(main_server* o, int m, const std::string& i)
{
    assert (0 != o);
    assert (!i.empty());
	char buf[256];
	while (true) {
		bzero(buf,sizeof(buf));
		if (read(m, buf, 256) <= 0){
			remove_offline_user(o,i);
			return;
		}
		std::string s = std::string(buf);
		std::string c, u, p;
		int ce = s.find('?');
		c.insert(0, s, 0, ce);
		if (c == "login" || c == "registration" || c == "update"){
			int ue = s.find(';');
			u.insert(0, s, ce+1, ue-ce-1);
			p.insert(0, s, ue+1, s.size()-ue-1);
			if (c == "login"){
				if (user_login(o, u, p, i)){
					write(m,"YES",strlen("YES"));
				} else{
					write(m,"NO",strlen("NO"));
				}
			} else if (c == "registration") {
				if (user_register(o, u, p)) {
					write(m,"YES",strlen("YES"));
				} else {
					write(m,"NO",strlen("NO"));
				}
			} else if (c == "update") {
				std::string r = o->parse(o->m_users);
				send_to(m,r);
			}
		} else if (c == "logout") {
			u.insert(0, s, ce + 1, s.size() - ce - 1);
			user_logout (o, u);
			write(m,"YES",strlen("YES"));
		} else {
			write(m,"NO",strlen("NO"));	
		}
	}
}

void main_server::remove_offline_user(main_server* s, const std::string& p)
{
	assert(0 != s);
	assert(!p.empty());
	user_name_to_info::iterator i = s->m_users.begin();
	for (; i != s->m_users.end(); ++i) {
		if (i->second.m_ip == p) {
			i->second.m_ip = "*";
		}
	}
}

