#include "dispatcher.hpp"

dispatcher::dispatcher(const std::string& i)
{
    assert(!i.empty());
    m_client = NULL;
    serv = NULL;
    m_client = new main_client(i);
    serv = new server;
    connect(serv,SIGNAL(receive_message(const QString&, const QString&)),
            this, SIGNAL(new_message(const QString&, const QString&)),
            Qt::QueuedConnection);	
}

void dispatcher::send_to(const std::string& u_n, const std::string& m)
{
    assert(!u_n.empty());
    assert(!m.empty());
    clear_clients_list();
    for (clients::iterator i = m_clients_list.begin(); i != m_clients_list.end(); ++i) {
        if (i->get_pair().username == u_n) {
            i->send_message(m);
            return;
        }
    }
    m_clients_list.push_back(client(u_n));
    (m_clients_list.end() - 1)->send_message(m);
}

void dispatcher::clear_clients_list()
{
      for (std::vector<client>::iterator i = m_clients_list.begin(); i != m_clients_list.end(); i++) {
        if (i->get_pair().current_socket == -1) {
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
    return m_client->login(u_n, u_p);
}

void dispatcher::logout()
{
    if(m_client->logout()) {
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

