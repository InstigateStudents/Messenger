#include "dispatcher.hpp"

Dispatcher::Dispatcher() {
 //   m_client = new Main_Client("192.168.68.111"); //???
    serv = new Server;
	connect(serv,SIGNAL(receive_message(const QString&, const QString&)), this, SIGNAL(new_message(const QString&, const QString&)),
	Qt::QueuedConnection);	

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

bool Dispatcher::registration(std::string u_name, std::string u_pass) {
    // handle returned value of function for false case
    m_client->registration(u_name, u_pass);
    return true;
}

bool Dispatcher::login(std::string u_name, std::string u_pass) {
    // handle returned value of function for false case
    m_client->login(u_name, u_pass);
    return true;
}

void Dispatcher::logout() {
    m_client->logout();
}

Dispatcher::~Dispatcher() {
    delete m_client;
    delete serv;
}

std::vector<std::string> Dispatcher::get_onlines() {
    FILE* d = fopen("./core/files/ipuser","r");
    char buf[256];
    std::string buffer, name;
    int pos;
    std::vector<std::string> onlines;
    while(fgets(buf, 256, d)) {
        buffer = std::string(buf);
        pos = buffer.find(";");
        if (pos != std::string::npos) {
            name = buffer.substr(pos + 1);
            onlines.push_back(name);
        }
    }
    return onlines;
}


/*int main() {
    Dispatcher d;
 //   d.send_to("Gevorg","hasav?");
    d.registration("Artur","grigoryan");
 //   sleep(5);
 //   d.login("Artur","grigoryan");
 //   sleep(5);
 //   d.logout();
    while(true);
    return 0;
}*/
