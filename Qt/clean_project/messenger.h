#ifndef MESSENGER_H
#define MESSENGER_H
#include <string>
#include <QObject>


class log_in_window;
class messenger_window;
class main_client;

class messenger: 
public QObject
{
Q_OBJECT
private:
	log_in_window * m_log_in_window;
	messenger_window * m_messenger_window;
	main_client *m_main_client;

public:
	messenger(const std::string& ip);
	void run();
public slots:
	void login(const QString&, const QString&);
};

#endif // MESSENGER_H
