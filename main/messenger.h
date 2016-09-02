#ifndef MESSENGER_H
#define MESSENGER_H

#include <string>
#include <vector>

#include <QObject>
#include <QStringList>
#include "myThread.h"


class log_in_window;
class messenger_window;
class dispatcher;

/**
 * @brief messenger is the entry point
 *
 * It creates the GUI and sets up connection with the dispatcher, which is the
 * public API of the messenger core.
 */
class messenger: public QObject
{
    Q_OBJECT
private:
	log_in_window* m_log_in_window;
	messenger_window* m_messenger_window;
	dispatcher* m_dispatcher;
	my_thread* m_thread;
	bool my_bool;
private:
	QStringList fake_list_generator();

    /// @name Connection setup and functionality
public:
    /// @brief Starts the GUI - the login/registration window
	void run();
public slots:
	void login(const QString&, const QString&);
	void registration(const QString& u, const QString& p);
	void send_to_client(const QString&, const QString&);
	void receive_message(const QString&, const QString&);
	void refresh_online_users();
	void user_logout();
    /// @name Special member functions
public:
    /**
     * @brief Constructor
     * 
     * @details Sets up the connection with dispatcher
     * @param i - IP of the main server
     */
	messenger(const std::string& i);
};

#endif // MESSENGER_H
