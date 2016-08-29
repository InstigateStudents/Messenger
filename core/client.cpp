#include "client.hpp"

client::client(const std::string& u_n)
{
    pair.username = u_n;
    pair.current_ip = get_ip_by_username(u_n);
    pair.current_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (pair.current_socket < 0) {
        std::cerr << "Error in creating socket" << std::endl;
        throw std::runtime_error("Error in creating socket");
    }
    std::thread(start_communication, pair).join();
}

void client::start_communication(user& p)
{
    sockaddr_in pair_addr; 
    bzero((sockaddr*)&pair_addr, sizeof(pair_addr));
    pair_addr.sin_family = AF_INET;
    pair_addr.sin_port = htons(12345);
    pair_addr.sin_addr.s_addr = std::stoi(p.current_ip);
    if (connect(p.current_socket, (sockaddr *)&pair_addr, sizeof(pair_addr)) < 0) {
        std::cerr << "Error in connection" << std::endl;
    }
    else {
        std::cout << "connected" <<std::endl;
    }
}

void client::send_message(const std::string& m)
{
    char buf[1024];
    strcpy(buf,  m.c_str());
        if(write(pair.current_socket, buf, strlen(buf)) < 0 ) {
            std::cerr << "Error in writing" << std::endl;
            pair.current_socket = -1;
        }
}


user client::get_pair()
{
    return pair;
}


/* 
int main() {
    client a("Gevorg");
    return 0;
}
*/
