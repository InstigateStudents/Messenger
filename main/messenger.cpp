#include "messenger.h"
#include "messenger_window.h"
#include "log_in_window.h"
#include "dispatcher.hpp"

#include "myThread.h"

#include <cassert>
#include <iostream>

messenger::messenger(const std::string& i)
{
    m_log_in_window = new log_in_window();
    m_dispatcher = new dispatcher(i);
    connect(m_log_in_window, SIGNAL(login(const QString&, const QString&)),
            this, SLOT(login(const QString&, const QString&)), Qt::QueuedConnection);
    connect(m_log_in_window, SIGNAL(registration(const QString&, const QString&)),
			this, SLOT(registration(const QString&, const QString&)));
	connect(m_dispatcher, SIGNAL(new_message(const QString&, const QString&)),
            this, SLOT(receive_message(const QString&, const QString&)), Qt::QueuedConnection);
}

void messenger::run()
{
    assert(0 != m_log_in_window);
    m_log_in_window->show();
}

QStringList messenger::fake_list_generator()
{   
    assert(0 != m_dispatcher);
    std::vector<std::string> n = m_dispatcher->get_onlines();
    QStringList l;
    for (unsigned int i = 0; i < n.size(); ++i) {
        l << QString::fromUtf8(n[i].c_str());
    }
	//l << "Art" << "Sash" << "Gev";
    return l;
}

void messenger::login(const QString& u, const QString& p)
{
    assert(!u.isEmpty());
    assert(!p.isEmpty());
    assert(0 != m_dispatcher);
    bool b = m_dispatcher->login(u.toStdString(), p.toStdString()); 
    if (b) {
		std::cout<<"messenger.cpp\n";
        assert(0 != m_log_in_window);
        m_log_in_window->hide(); 
	    m_log_in_window->clear_login_fields();	
        QStringList l = fake_list_generator(); 
        m_messenger_window = new messenger_window(l);
        connect(m_messenger_window,
                SIGNAL(send_message_to_client(const QString&, const QString&)),
                this,
                SLOT(send_to_client(const QString&, const QString&)), Qt::QueuedConnection);
		connect(m_messenger_window, SIGNAL(logout()), this, SLOT(user_logout()));
        assert(0 != m_messenger_window);
        m_messenger_window->show();
		// --- new ---
		m_thread = new my_thread();
		connect(m_thread, SIGNAL(refresh()), this, SLOT(refresh_online_users()));
		m_thread->start();
    } else {
        m_log_in_window->show_login_error("Incorrect username/password.");
    }
}

void messenger::registration(const QString& u, const QString& p)
{
	//return value
	m_dispatcher->registration(u.toStdString(),p.toStdString());
	std::cout<<"new Account\n";
	std::cout<<u.toStdString()<<"\t"<<p.toStdString()<<"\n";
}



void messenger::send_to_client(const QString& t, const QString& m)
{
    assert(!t.isEmpty());
    assert(!m.isEmpty());
    assert(0 != m_dispatcher);
    m_dispatcher->send_to(t.toStdString(), m.toStdString());
}

void messenger::receive_message(const QString& f, const QString& m)
{
    assert(!f.isEmpty());
    assert(!m.isEmpty());
    assert(0 != m_messenger_window);
    m_messenger_window->receive_message(f, m);
}


void messenger::refresh_online_users()
{
        std::cout<<"start refresh online users" <<std::endl;
	    std::vector<std::string> v = m_dispatcher->get_onlines();
        std::cout<< "get_onlines end"<<std::endl;
        QVector<QString> online;
        for (std::vector<std::string>::size_type i = 0; i < v.size(); ++i) {
            online.append(QString::fromUtf8(v[i].c_str()));
        }
        std::cout<<"refresh_show_online_users START"<<std::endl;
        m_messenger_window->refresh_show_online_users(online);
        std::cout<< "end of refresh online users" <<std::endl;
}

void messenger::user_logout()
{
    my_bool = false;
	//m_thread->terminate();
	m_messenger_window->close();
	m_log_in_window->show();
    m_dispatcher->logout();
}
