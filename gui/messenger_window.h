#ifndef MESSENGER_WINDOW_H
#define MESSENGER_WINDOW_H

#include <QWidget>
#include <QStringList>
#include <QVector>


class QHBoxLayout;
class QVBoxLayout;
class QTextEdit;
class QPushButton;

class QLabel;
class QListWidget;
class QListWidgetItem;
class QStackedLayout;

class messenger_window : public QWidget 
{
	Q_OBJECT

private:
	typedef QVector<QTextEdit*> Text_Edit_Container;
    typedef QVector<QListWidgetItem*> Widget_Item_Container;

signals:
	void send_message_to_client(const QString&, const QString&);
	void logout();

private slots:
	void send_message();
	void set_color_black(int);
	void set_current_user(int = 0);


private:
	void create_main_layout();
	void create_left_left_layout();
	void create_left_right_layout();
	void create_left_side();
	void create_right_side();
	void connect_signal_slot();

private:
	QHBoxLayout *m_main_layout;
	QWidget *m_left_widget;
	QHBoxLayout *m_left_layout;
	QVBoxLayout *m_left_left_layout;
	QLabel *m_current_user_name;
	QStackedLayout *m_message_board;
	Text_Edit_Container  m_user_text_edit;
	QVBoxLayout *m_left_right_layout;
	QWidget *m_right_widget;
	QVBoxLayout *m_right_layout;
	QTextEdit *m_message_text;
	QPushButton *m_send_button;
	QPushButton *m_logout;
	int m_user_count;
	int m_current_user;
	QStringList m_user_name;
	QListWidget *m_online_users;
	Widget_Item_Container 	m_list_widget_item;

	/// @name Interface to communicate with the controller (core)
public:
    /**
     * TODO
     */
	void receive_message(const QString& s, const QString& n);

	/**
     * TODO
	 */
	void refresh_show_online_users(const QVector<QString>& v);

	/// @name Special 
public:
	/**
     * TODO
	 */
	messenger_window(const QStringList& l);
};


#endif // MESSENGER_WINDOW_H
