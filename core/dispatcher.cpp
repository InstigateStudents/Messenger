#include "dispatcher.hpp"

Dispatcher::Dispatcher(std::string ip) {
    m_client = NULL;
    serv = NULL;
    m_client = new Main_Client(ip);
}


void Dispatcher::send_to(std::string u_name,std::string message)
{
    clear_clients_list();
    for(std::vector<Client>::iterator i = clients_list.begin(); i != clients_list.end(); ++i) {
        if(i->get_pair().username == u_name) {
            i->send_message(message);
            std::cout << "after sending"  <<std::endl;
            return;
        }
    }
    clients_list.push_back(Client(u_name));
    (clients_list.end() - 1)->send_message(message);
    std::cout << "after sending" <<std::endl;
}

void Dispatcher::clear_clients_list() {
      for(std::vector<Client>::iterator i = clients_list.begin(); i != clients_list.end(); i++) {
        if(i->get_pair().current_socket == -1) {
            std::cout << "\n deleted user" << i->get_pair().username <<std::endl;
            clients_list.erase(i);
        }
    }
}

bool Dispatcher::registration(std::string u_name, std::string u_pass) {
    return m_client->registration(u_name, u_pass);
}

bool Dispatcher::login(std::string u_name, std::string u_pass) {
    // making the condition true as the main server isn't working yet
    if( m_client->login(u_name, u_pass) || true) { // || true need to delete
        std::cout << "in Dispatcher Login" << std::endl;
        serv = new Server;
	    connect(serv,SIGNAL(receive_message(const QString&, const QString&)),
	    this,SIGNAL(new_message(const QString&, const QString&)),
	    Qt::QueuedConnection);	
        return true;
    }
    return false;
}

void Dispatcher::logout() {
    m_client->logout();
    delete serv;
    serv = NULL;
    clients_list.clear();
}

Dispatcher::~Dispatcher() {
    delete m_client;
    m_client = NULL;
    if(serv != NULL) {
        delete serv;
        serv = NULL;
    }
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
    fclose(d);
    return onlines;
}


std::vector<std::string> Dispatcher::get_registered_users() {
    FILE* d = fopen("./core/files/regs","r");
    char buf[256];
    std::string buffer, name;
    int pos;
    std::vector<std::string> regs;
    while(fgets(buf, 256, d)) {
        buffer = std::string(buf);
        pos = buffer.find(";");
        if (pos != std::string::npos) {
            name = buffer.substr(pos + 1);
            regs.push_back(name);
        }
    }
    fclose(d);
    return regs;
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
