#include "dispatcher.hpp"

Dispatcher::Dispatcher() {
  //  m_client = new Main_Client("192.168.68.111"); //???
    serv = new Server;
}

void Dispatcher::send_to(std::string u_name,std::string message)
{
    clear_clients_list();
    for(std::vector<Client>::iterator i = clients_list.begin(); i != clients_list.end(); ++i) {
        if(i->get_pair().username == u_name) {
            i->send_message(message);
            std::cout << i->get_pair().username << i->get_pair().current_socket << i->get_pair().current_ip <<std::endl;
            return;
        }
    }
    clients_list.push_back(Client(u_name));
    (clients_list.end() - 1)->send_message(message);
}

void Dispatcher::clear_clients_list() {
      for(std::vector<Client>::iterator i = clients_list.begin(); i != clients_list.end(); i++) {
        if(i->get_pair().current_socket == -1) {
            clients_list.erase(i);
        }
    }
}

void Dispatcher::registration(std::string u_name, std::string u_pass) {
    // handle returned value of function for false case
    m_client->registration(u_name, u_pass);
}

void Dispatcher::login(std::string u_name, std::string u_pass) {
    // handle returned value of function for false case
    m_client->login(u_name, u_pass);
}

void Dispatcher::logout() {
    m_client->logout();
}

Dispatcher::~Dispatcher() {
    delete m_client;
    delete serv;
}
/*
int main() {
    Dispatcher d;
    d.send_to("Artur", "barev");
    while(true);
    return 0;
}*/
