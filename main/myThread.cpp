#include "myThread.h"
#include <vector>
#include <QVector>
#include <QString>
#include <iostream>
#include <QObject>


void my_thread::run() 
{
		while(1)
		{
			std::cout << "Thread is working\n";
		/*	std::vector<std::string> v = m_server->get_onlines();
			QVector<QString> online;
			for (int i = 0; i < v.size(); ++i) {
				         online.append(QString::fromUtf8(v[i].c_str()));
			}
			m_gui->refresh_show_online_users(online);*/


			sleep(5);
			emit refresh();
		}

}

