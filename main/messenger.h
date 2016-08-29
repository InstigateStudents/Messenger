#ifndef MESSENGER_H
#define MESSENGER_H
#include <string>
#include <QObject>
#include <QStringList>
#include <vector>


class log_in_window;
class messenger_window;
//class main_client;

class Dispatcher;
class messenger: 
public QObject
{
Q_OBJECT
private:
	log_in_window * m_log_in_window;
	messenger_window * m_messenger_window;
	//main_client *m_main_client;
	Dispatcher *m_dispatcher;
	QStringList fake_list_generator();

public:
	messenger(const std::string& ip);
	void run();
public slots:
	void login(const QString&, const QString&);
	void send_to_client(const QString&, const QString&);
	void receive_message(const QString&, const QString&);
	void refresh_online_users(std::vector<std::string>);
};

#endif // MESSENGER_H
