#include "main_client.hpp"

main_client::main_client(const std::string& s_i)
{
    m_main_socket = -1;
    assert(!s_i.empty());
    m_main_socket= socket(AF_INET, SOCK_STREAM, 0); 
    m_me.current_socket = m_main_socket;
    m_me.current_ip = std::to_string(INADDR_ANY);
    if (m_me.current_socket < 0) {
        std::cerr << "Error in creating socket" << std::endl;
 //       throw std::runtime_error("Error in creating socket");
    }
    std::thread(connect_server, m_me.current_socket, s_i).join();
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
        std::cerr << "Error in connection" << std::endl;
        //exception
    }
}


bool main_client::registration(const std::string& u_n,const std::string& u_p)
{
    assert(!u_n.empty());
    assert(!u_p.empty());
    std::cout << "in reg" << std::endl;
    char buf[256];
    bzero(buf,sizeof(buf));
    std::string buffer;
    buffer = std::string("registration?") + u_n + std::string(";") + u_p;
    strcpy(buf,buffer.c_str());
    // TODO handle write error case
    if (write(m_main_socket, buf, strlen(buf)) < 0) {
   //     throw std::runtime_error("Error in registration");
    }
    else {
        bzero(buf,sizeof(buf));
        read(m_main_socket, buf, 256);
        if (strcmp(buf, "YES")) {
            return false;
        }
        else {
            return true;
        }      
    }
}

bool main_client::login(const std::string& u_n,const std::string& u_p)
{
    
    assert(!u_n.empty());
    assert(!u_p.empty());
    std::cout << "in main_client Login" << std::endl;
    m_me.username = u_n;
    std::cout << "in login" << std::endl;
    char buf[256];
    bzero(buf,sizeof(buf));
    std::string buffer;
    buffer = std::string("login?") + u_n + std::string(";") + u_p;
    strcpy(buf,buffer.c_str());
    // TODO handle write error case
    if (write(m_main_socket, buf, strlen(buf)) < 0) {
    //exception
        std::cout << "execption in write" <<std::endl;
    //    throw std::runtime_error("Error in login");
    } else {
        char buff[256];
        bzero(buff,sizeof(buff));
        if( read(m_main_socket, buff, 256) < 0) {
                std::cout << "error in read" <<std::endl;
        }
        //printf(buff, 256);
        std::cout << std::endl;
        if (strcmp(buff, "YES")) {
            return false;
        }
        else {
            m_online_list_thread = std::thread(give_online_list, m_main_socket);
            m_online_list_thread.detach();
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
     //   throw std::runtime_error("Error in logout");
    } else {
            bzero(buf,sizeof(buf));
            if (read(m_main_socket, buf, 256) < 0) {
                std::cout << "error in read" <<std::endl;
            }
            printf(buf, sizeof(buf));
            std::cout <<std::endl;
            if (strcmp(buf, "YES")) {
                return false;
            } else {
                std::cout << "raised LOGOUT signal " << std::endl;
                //std::raise(LOGOUT);
                m_online_list_thread.~thread();
                return true;
            }   
    }
}


void main_client::give_online_list(int s_id) 
{
    std::signal(LOGOUT, term);
    while (true) {
        FILE* fd = fopen("./core/files/ipuser", "w");
        if (fd == NULL) {
            throw std::runtime_error("Error in open file");
        }
        
        char buf1[4096];
        if (write(s_id, "update", strlen("update")) < 0) {
        //exception
        }
        bzero(buf1,sizeof(buf1));
        // TODO handle read error case
        if (read(s_id, buf1, 4096) < 0) {
            //exception
        } else {
            fprintf(fd, "%s\n", buf1);
        }
        fclose(fd);
        sleep(5);
    }
}

void main_client::term(int s)
{
    std::cout << "in signal slot" << std::endl;
    std::terminate();
}

/*
int main() {
    main_client c("192.168.68.111");
    c.registration("Artur","Grigoryan");
    c.login("Artur","Grigoryan");
    c.logout();
    //    c.give_online_list();
    while(true);
    return 0;
}*/
