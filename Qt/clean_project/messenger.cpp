#include "messenger.h"
#include "messenger_window.h"
#include "log_in_window.h"
//#include "main_client.h"

#include <cassert>
#include <iostream>

messenger::messenger(const std::string&)
{
	m_log_in_window = new log_in_window();
	//m_main_client = new m_main_client(ip);
	m_messenger_window = new messenger_window();
	connect(m_log_in_window, SIGNAL(login(const QString&,const QString&)), 
					this, SLOT(login(const QString&,const QString&)));

}

void messenger::run()
{
	assert(0 != m_log_in_window);
	m_log_in_window->show();
}

void messenger::login(const QString& u, const QString& p)
{
	//m_main_client->login(u, p);	
	std::cout << u.toStdString() << std::endl;
	std::cout << p.toStdString() << std::endl;
}
