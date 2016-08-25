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
	connect(m_log_in_window, SIGNAL(login(const QString&,const QString&)), 
					this, SLOT(login(const QString&,const QString&)));

}

void messenger::run()
{
	assert(0 != m_log_in_window);
	m_log_in_window->show();
}

QStringList messenger::fake_list_generator()
{
	QStringList l;
	l << "User1" << "User2" << "User3"<< "User4";
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
	//	QList =
		QStringList l = fake_list_generator(); 
		m_messenger_window = new messenger_window(l);
		m_messenger_window ->show();	
	} else {
		m_log_in_window->show_login_error("Wrong Login");
	}

}
