#include "server.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

server::server() {
    std::thread(start_server, this).detach();
}

void server::start_server(server* s)
{
    int m_read_socket;
    int newsocket;
    user current_user;
    std::string u_ip;
    sockaddr_in serv_addr, client_addr;
    socklen_t clientlength;
    bzero((sockaddr *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(12345);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    m_read_socket = socket(AF_INET, SOCK_STREAM, 0);
    s->m_sockets_id.push_back(m_read_socket);
    if (m_read_socket < 0) {
        throw std::runtime_error("Error in creating socket");
    }
    if (bind(m_read_socket,(sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        throw std::runtime_error("Error in binding");
    }
    listen(m_read_socket,5);
    clientlength = sizeof(client_addr);
    while (true) {
        bzero((sockaddr *)&client_addr, sizeof(client_addr));
        newsocket = accept(m_read_socket,(sockaddr *)&client_addr,
                &clientlength);
        if (!newsocket) {
            throw std::runtime_error("Error in accepting");
        }
        s->m_sockets_id.push_back(newsocket);
        u_ip = std::to_string(client_addr.sin_addr.s_addr);
        current_user.username = get_username_by_ip(u_ip); 
        current_user.current_ip =u_ip;
        current_user.current_socket = newsocket;
        std::thread(read_message, std::ref(s), std::ref(current_user)).detach();
    }
}

void server::read_message(server* s, user& u)
{
    char buf[1024];
    std::string buffer;
    while (true) {
        bzero(buf,1024);
        if (read(u.current_socket, buf, 1024) > 0) {
    		buffer = std::string(buf);
		
	    	QString to = QString::fromStdString(u.username);
	    	QString m  = QString::fromStdString(buffer);	
	
            emit s->receive_message(to, m);
        }
        else {
            u.current_socket = -1;
            return;
        }
    }
}

server::~server()
{
    for(std::vector<int>::iterator i = m_sockets_id.begin();
        i != m_sockets_id.end(); ++i) {
            close(*i);    
    }
    m_sockets_id.clear();
}
