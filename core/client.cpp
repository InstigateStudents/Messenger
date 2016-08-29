#include "client.hpp"

Client::Client(std::string u_name) {
    pair.username = u_name;
    pair.current_ip = get_ip_by_username(u_name);
    pair.current_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(pair.current_socket < 0) {
        std::cerr << "Error in creating socket" << std::endl;
    }
    std::thread(start_communication, pair).join();
}

void Client::start_communication(User p) {
    sockaddr_in pair_addr; 
    bzero((sockaddr*)&pair_addr, sizeof(pair_addr));
    pair_addr.sin_family = AF_INET;
    pair_addr.sin_port = htons(12345);
    pair_addr.sin_addr.s_addr = std::stoi(p.current_ip);
    if(connect(p.current_socket, (sockaddr *)&pair_addr, sizeof(pair_addr)) < 0) {
        std::cerr << "Error in connection" << std::endl;
    }
    else {
        std::cout << "connected" <<std::endl;
    }
}

void Client::send_message(std::string message) {
    char buf[1024];
    strcpy(buf,  message.c_str());
        if(write(pair.current_socket, buf, strlen(buf)) < 0 ) {
            std::cerr << "Error in writing" << std::endl;
            pair.current_socket = -1;
        }
}


User Client::get_pair() {
    return pair;
}


/* 
int main() {
    Client a("Gevorg");
    return 0;
}
*/
