#ifndef MESSENGER_WINDOW_H
#define MESSENGER_WINDOW_H

#include <QDialog>
#include <QStringList>

class QHBoxLayout;
class QVBoxLayout;
class QTextEdit;
class QPushButton;

class QLabel;
class QListWidget;
class QListWidgetItem;
class QStackedLayout;

class messenger_window : public QDialog
{
	Q_OBJECT
public:
	messenger_window(const QStringList& /*QWidget* parent = 0*/);
signals:
	void send_message_to_client(const QString&, const QString&);

private slots:
	void send_message();
	void receive_messege(const QString& from, const QString& msg);

private:
	QHBoxLayout *m_main_layout;

	QWidget *m_left_widget;
	QHBoxLayout *m_left_layout;
	QVBoxLayout *m_left_left_layout;
	QLabel *m_current_user_name;
	QStackedLayout *m_message_board;
	QTextEdit *m_user_text_edit;

	QVBoxLayout *m_left_right_layout;

	QWidget *m_right_widget;
	QVBoxLayout *m_right_layout;

	QTextEdit *m_message_text;
	QPushButton *m_send_button;


	void create_main_layout();

	void create_left_left_layout();
	void create_left_right_layout();

	void create_left_side();

	void create_right_side();

	void connect_signal_slot();

	//
	int m_user_count;
	int m_current_user;
	QStringList m_user_name;


	QListWidget *m_online_users;
	QListWidgetItem *m_list_widget_item;
private slots:
	void set_current_user(int = 0);


};


#endif // MESSENGER_WINDOW_H
