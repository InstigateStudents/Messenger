#include "main_client.hpp"

Main_Client::Main_Client(std::string serv_ip) {
    main_socket= socket(AF_INET, SOCK_STREAM, 0); 
    me.current_socket =main_socket;
    me.current_ip = std::to_string(INADDR_ANY);
    if(me.current_socket < 0) {
        std::cerr << "Error in creating socket" << std::endl;
        //exception
    }
    std::thread(connect_server, me.current_socket, serv_ip).join();
}

void Main_Client::connect_server(int socket, std::string serv_ip) {
    sockaddr_in serv_addr;
    char buf[256];
    bzero((sockaddr*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(12345);
    strcpy(buf, serv_ip.c_str());
    serv_addr.sin_addr.s_addr = inet_addr(buf);//16777343 must be changed to real address
    if(connect(socket, (sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Error in connection" << std::endl;
        //exception
    }
}


bool Main_Client::registration(std::string u_name, std::string u_password) {
    std::cout << "in reg" << std::endl;
    char buf[256];
    bzero(buf,sizeof(buf));
    std::string buffer;
    buffer = std::string("registration?") + u_name + std::string(";") + u_password;
    strcpy(buf,buffer.c_str());
    write(main_socket, buf, strlen(buf));
    bzero(buf,sizeof(buf));
 //   read(main_socket, buf, 256);
    if(buf == "YES") {
        return true;
    }
    else {
        return false;
    }   
}


bool Main_Client::login(std::string u_name, std::string u_password) {
    std::cout << "in main_client Login" << std::endl;
    me.username = u_name;
    std::cout << "in login" << std::endl;
    char buf[256];
    bzero(buf,sizeof(buf));
    std::string buffer;
    buffer = std::string("login?") + u_name + std::string(";") + u_password;
    strcpy(buf,buffer.c_str());
    write(main_socket, buf, strlen(buf));
   // read(main_socket, buf, 256);
    if(buf == "YES") {
        return true;
    }
    else {
        return false;
    }   
}

bool Main_Client::logout() {
    char buf[256];
    std::string buffer = std::string("logout?") + me.username;
    strcpy(buf, buffer.c_str());
    write(main_socket, buf, strlen(buf));
  //  read(main_socket, buf, 256);
    if(buf == "YES") {
        return true;
    }
    else {
        return false;
    }   
}


void Main_Client::give_online_list() {
    FILE* fd = fopen("./files/ipuser", "w");
    while(true) {
        char buf[4096];
        bzero(buf,sizeof(buf));
        read(main_socket, buf, 4096);
        fwrite(buf, sizeof(char), sizeof(buf), fd);
    }
    fclose(fd);
}


void Main_Client::give_registered_list() {
    FILE* fd = fopen("./files/regs", "w");
        char buf[4096];
        bzero(buf,sizeof(buf));
        read(main_socket, buf, 4096);
        fwrite(buf, sizeof(char), sizeof(buf), fd);
    fclose(fd);
}

/*
int main() {
    Main_Client c("192.168.68.111");
    c.registration("Artur","Grigoryan");
    c.login("Artur","Grigoryan");
    c.logout();
    //    c.give_online_list();
    while(true);
    return 0;
}*/
