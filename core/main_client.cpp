#include "main_client.hpp"

main_client::main_client(const std::string& s_i)
{
    m_logout_flag = 0;
    m_main_socket = -1;
    assert(!s_i.empty());
    m_main_socket= socket(AF_INET, SOCK_STREAM, 0); 
    m_me.current_socket = m_main_socket;
    m_me.current_ip = std::to_string(INADDR_ANY);
    if (m_me.current_socket < 0) {
        throw std::runtime_error("Error in creating socket");
    }
    std::thread(connect_server, std::ref(m_me.current_socket), std::ref(s_i)).join();
}

void main_client::connect_server(int& socket,const std::string& serv_ip)
{
    assert(socket != -1);
    assert(!serv_ip.empty());
    sockaddr_in serv_addr;
    char buf[256];
    bzero((sockaddr*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(12345);
    strcpy(buf, serv_ip.c_str());
    serv_addr.sin_addr.s_addr = inet_addr(buf);
    if (connect(socket, (sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        throw std::runtime_error("Error in connection");
    }
}


bool main_client::registration(const std::string& u_n,const std::string& u_p)
{
    assert(!u_n.empty());
    assert(!u_p.empty());
    char buf[256];
    bzero(buf, sizeof(buf));
    std::string buffer;
    buffer = std::string("registration?") + u_n + std::string(";") + u_p;
    strcpy(buf,buffer.c_str());
    // TODO handle write error case
    if (write(m_main_socket, buf, strlen(buf)) < 0) {
        throw std::runtime_error("Error in registration, write");
    } else {
        bzero(buf,sizeof(buf));
        if(read(m_main_socket, buf, 256) < 0) {
            std::cout << "error in read" <<std::endl;
            throw std::runtime_error("Error in reading, registration");
        }

        if (strcmp(buf, "YES")) {
            return false;
        } else {
            return true;
        }      
    }
}

bool main_client::login(const std::string& u_n,const std::string& u_p)
{
    assert(!u_n.empty());
    assert(!u_p.empty());
    m_me.username = u_n;
    char buf[256];
    bzero(buf,sizeof(buf));
    std::string buffer;
    buffer = std::string("login?") + u_n + std::string(";") + u_p;
    strcpy(buf,buffer.c_str());
    // TODO handle write error case
    if (write(m_main_socket, buf, strlen(buf)) < 0) {
        throw std::runtime_error("Error in write, login");
    } else {
        bzero(buf,sizeof(buf));
        if (read(m_main_socket, buf, 256) < 0) {
            throw std::runtime_error("Error in reading, login");
        }
        if (strcmp(buf, "YES")) {
            return false;
        } else {
            m_logout_flag = 1;
            std::thread(give_online_list, this).detach();
            sleep(1);
            return true;
        }   
    }
}

bool main_client::logout()
{
    char buf[256];
    std::string buffer = std::string("logout?") + m_me.username;
    strcpy(buf, buffer.c_str());
    // TODO handle write error case
    if (write(m_main_socket, buf, strlen(buf)) < 0) {
        throw std::runtime_error("Error in write,logout");
    } else {
        bzero(buf,sizeof(buf));
        if (read(m_main_socket, buf, 256) < 0) {
            throw std::runtime_error("Error in reading,logout");
        }
        if (strcmp(buf, "YES")) {
            return false;
        } else {
            m_logout_flag = 0;
            return true;
        }   
    }
}

void main_client::give_online_list(main_client* m_s) 
{ 
    char buf[4096];
    while (m_s->m_logout_flag) {
        FILE* fd = fopen("./core/files/ipuser", "w");
        if (fd == NULL) {
            throw std::runtime_error("Error in open file");
        }
        if (write(m_s->m_main_socket, "update", strlen("update")) < 0) {
            throw std::runtime_error("Error in write,give_online_list");
        }
        bzero(buf,sizeof(buf));
        // TODO handle read error case
        if (read(m_s->m_main_socket, buf, 4096) < 0) {
            throw std::runtime_error("Error in read,give_online_list");
        } else {
            fprintf(fd, "%s\n", buf);
        }
        fclose(fd);
        sleep(5);
    }
}

