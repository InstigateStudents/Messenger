#include "messenger.h"
#include "messenger_window.h"
#include "log_in_window.h"
//#include "main_client.h"
#include "dispatcher.hpp"

#include <cassert>
#include <iostream>

messenger::messenger(const std::string&)
{
	m_log_in_window = new log_in_window();
	//m_main_client = new m_main_client(ip);

	m_dispatcher = new Dispatcher();
	connect_signal_slot();

}

void messenger::run()
{
	assert(0 != m_log_in_window);
	m_log_in_window->show();
}

QStringList messenger::fake_list_generator()
{
	QStringList l;
	return l;
}

void messenger::login(const QString& u, const QString& p)
{
	bool b = true;
	//b = m_main_client->login(u, p);	
	std::cout << u.toStdString() << std::endl;
	std::cout << p.toStdString() << std::endl;
	if (b) {
		m_log_in_window ->hide();	
		//l = m_main_client->get_contacts_list();	
		
		QStringList l = fake_list_generator(); 
		m_messenger_window = new messenger_window(l);
		connect(m_messenger_window, 
			SIGNAL(send_message_to_client(const QString&, const QString&)),
			this, SLOT(send_to_client(const QString&, const QString&)));
		m_messenger_window ->show();	
	} else {
		m_log_in_window->show_login_error("Incorrect username/password.");
	}

}


void messenger::send_to_client(const QString& to, const QString& msg)
{
    std::cout<<"working send_to_client slot: "<<to.toStdString ()<<msg.toStdString() <<"\n";    
	m_dispatcher -> send_to(to.toStdString (), msg.toStdString ());
}

void messenger::connect_signal_slot()
{
	connect(m_log_in_window, SIGNAL(login(const QString&,const QString&)),
                                        this, SLOT(login(const QString&,const QString&)));
	
	//connect(m_messenger_window, SIGNAL(send_message_to_client(const QString&, const QString&)),
	//				this, SLOT(send_to_client(const QString&, const QString&)));

}
