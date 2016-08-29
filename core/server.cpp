#include "server.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

Server::Server() {
    std::thread(start_server, this).detach();
}

void Server::start_server(Server* s) {
    int m_read_socket;
    int newsocket;
    User current_user;
    std::string u_ip;
    sockaddr_in serv_addr, client_addr;
    socklen_t clientlength;
    bzero((sockaddr *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(12345);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    m_read_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(m_read_socket < 0) {
        std::cerr << "Error in creating socket" << std::endl;
    }
    if(bind(m_read_socket,(sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Error in binding" << std::endl;
    }
    listen(m_read_socket,5);
    clientlength = sizeof(client_addr);
    while(true) {
        bzero((sockaddr *)&client_addr, sizeof(client_addr));
        newsocket = accept(m_read_socket,(sockaddr *)&client_addr,
                &clientlength);
        if(!newsocket) {
            std::cerr << "Error in accepting" << std::endl;
        }
        u_ip = std::to_string(client_addr.sin_addr.s_addr);
        current_user.username = get_username_by_ip(u_ip); 
        current_user.current_ip =u_ip;
        current_user.current_socket = newsocket;
        std::thread(read_message, s, current_user).detach();
    }
}

void Server::read_message(Server* s, User u) {
    char buf[1024];
    std::string buffer;
    while(true) {
        bzero(buf,1024);
        if(read(u.current_socket, buf, 1024) > 0) {
    		buffer = std::string(buf);
		
	    	QString to = QString::fromStdString(u.username);
	    	QString m  = QString::fromStdString(buffer);	
	
            emit s->receive_message(to, m);
		//std::cout << "Message from " << u.username << buffer << std::flush;
        }
        else {
            u.current_socket = -1;
            return;
        }
    }
}

/*

int main() {

    Server s;
    return 0;
}
*/
