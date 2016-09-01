#include "dispatcher.hpp"

dispatcher::dispatcher(const std::string& i)
{
    assert(!i.empty());
    m_client = NULL;
    serv = NULL;
    m_client = new main_client(i);
}

void dispatcher::send_to(const std::string& u_n, const std::string& m)
{
    assert(!u_n.empty());
    assert(!m.empty());
    clear_clients_list();
    for (clients::iterator i = m_clients_list.begin(); i != m_clients_list.end(); ++i) {
        if (i->get_pair().username == u_n) {
            i->send_message(m);
            std::cout << "after sending"  <<std::endl;
            return;
        }
    }
    m_clients_list.push_back(client(u_n));
    (m_clients_list.end() - 1)->send_message(m);
    std::cout << "after sending" << std::endl;
}

void dispatcher::clear_clients_list()
{
      for (std::vector<client>::iterator i = m_clients_list.begin(); i != m_clients_list.end(); i++) {
        if (i->get_pair().current_socket == -1) {
            std::cout << "\n deleted user" << i->get_pair().username <<std::endl;
            m_clients_list.erase(i);
        }
    }
}

bool dispatcher::registration(const std::string& u_n,const std::string& u_p)
{
    assert(!u_n.empty());
    assert(!u_p.empty());
    return m_client->registration(u_n, u_p);
}

bool dispatcher::login(const std::string& u_n, const std::string& u_p)
{
    assert(!u_n.empty());
    assert(!u_p.empty());
    // making the condition true as the main server isn't working yet
        bool b = m_client->login(u_n, u_p);
        std::cout << b << std::endl;
    if (b) { 
        std::cout << "in dispatcher Login" << std::endl;
        serv = new server;
	    connect(serv,SIGNAL(receive_message(const QString&, const QString&)),
            this, SIGNAL(new_message(const QString&, const QString&)),
	    Qt::QueuedConnection);	
        return true;
    }
    return false;
}

void dispatcher::logout()
{
    if(m_client->logout()) {
        std::cout << "dispatcher logout" <<std::endl;
        delete serv;
        serv = NULL;
        m_clients_list.clear();
    }
    else {
        //   throw std::runtime_error("Error in logout");
    }
}

dispatcher::~dispatcher()
{
    delete m_client;
    m_client = NULL;
    if (serv != NULL) {
        delete serv;
        serv = NULL;
    }
}

std::vector<std::string> dispatcher::get_onlines()
{
    FILE* d = fopen("./core/files/ipuser","r");
    char buf[256];
    std::string buffer, name;
    unsigned int pos;
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

std::vector<std::string> dispatcher::get_registered_users()
{
    FILE* d = fopen("./core/files/regs","r");
    char buf[256];
    std::string buffer, name;
    unsigned int pos;
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
    dispatcher d;
 //   d.send_to("Gevorg","hasav?");
    d.registration("Artur","grigoryan");
 //   sleep(5);
 //   d.login("Artur","grigoryan");
 //   sleep(5);
 //   d.logout();
    while(true);
    return 0;
}*/
