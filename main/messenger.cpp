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
	// TODO specify the IP of the main server
	m_dispatcher = new Dispatcher("must be IP of main server");
	connect(m_log_in_window, SIGNAL(login(const QString&,const QString&)),
                               this, SLOT(login(const QString&,const QString&)),Qt::QueuedConnection);
	connect(m_dispatcher,SIGNAL(new_message(const QString&,const QString&)),
				this,SLOT(receive_message(const QString&,const QString&)),Qt::QueuedConnection);
}

void messenger::run()
{
	assert(0 != m_log_in_window);
	m_log_in_window->show();
}

QStringList messenger::fake_list_generator()
{	
	//std::cout<< "STARTTTTTTTTTTTT\n";
	std::vector<std::string> usr_name = m_dispatcher -> get_onlines();
	QStringList l;
	for (int i = 0; i < usr_name.size(); ++i) {
		l << QString::fromUtf8( usr_name[i].c_str() );
	}
	//l << "Artur" << "Gevorg" << "Argisht" << "Gev";
	//std::cout<< "NOOOOOOOOOOOOOOOOOOOo\n";	
	return l;
}

void messenger::login(const QString& u, const QString& p)
{
//	bool b = true;
	bool b = m_dispatcher->login(u.toStdString(), p.toStdString());	
	//std::cout << u.toStdString() << std::endl;
	//std::cout << p.toStdString() << std::endl;
	if (b) {
		m_log_in_window ->hide();	
		//l = m_main_client->get_contacts_list();	
		
		QStringList l = fake_list_generator(); 
		m_messenger_window = new messenger_window(l);
		connect(m_messenger_window,SIGNAL(send_message_to_client(const QString&, const QString&)),
						this, SLOT(send_to_client(const QString&, const QString&)),Qt::QueuedConnection);
		m_messenger_window ->show();	
	} else {
		m_log_in_window->show_login_error("Incorrect username/password.");
	}

}


void messenger::send_to_client(const QString& to, const QString& msg)
{
    //std::cout<<"messanger.cpp:\tworking send_to_client slot: "<<to.toStdString ()<<msg.toStdString() <<"\n";    
	m_dispatcher -> send_to(to.toStdString (), msg.toStdString ());
}

void messenger::receive_message(const QString& from, const QString& msg)
{
	//QString str = QString::fromUtf8(content.c_str());
        //std::cout << "messenger.cpp:\treceive_message\n";	
	m_messenger_window -> receive_message(from,  msg);
}


void messenger::refresh_online_users(std::vector<std::string> vec)
{
	QVector<QString> online;
	for (int i = 0; i < vec.size(); ++i) {
		online.append( QString::fromUtf8(vec[i].c_str()) );
	}
	m_messenger_window -> refresh_show_online_users(online);

}
