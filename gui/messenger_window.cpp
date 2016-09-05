#include "messenger_window.h"

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QScrollBar>

#include <QLabel>
#include <QScrollArea>

#include <QListWidget>
#include <QStackedLayout>

#include <QApplication>
#include <QDesktopWidget>
#include <iostream>

#include <QVector>
#include <cassert>

messenger_window::messenger_window(const QStringList& l)
    : QDialog()
{
	m_current_user = 0;
	m_user_count = l.count();
	m_user_name = l;
	create_left_side();
	create_right_side();
	connect_signal_slot();
	create_main_layout();
	QRect r = QApplication::desktop()->screenGeometry();
	int width = r.width();
	m_right_widget->setMaximumWidth(width/5);	
	m_left_widget->setMaximumWidth(width/2);	
	setLayout(m_main_layout);
}

void messenger_window::create_main_layout()
{
	m_main_layout = new QHBoxLayout;
	m_main_layout->addWidget(m_left_widget);
	m_main_layout->addWidget(m_right_widget);
}

void messenger_window::create_left_left_layout()
{
	m_left_left_layout = new QVBoxLayout;
	m_message_board = new QStackedLayout;
	m_message_text = new QTextEdit;
	QScrollBar* sb = m_message_text->verticalScrollBar();
	sb->setValue(sb->maximum());
	m_message_text->setFixedHeight(50);
	m_user_text_edit.resize(m_user_count);
	for (int i = 0; i < m_user_count; ++i) {
		m_user_text_edit[i] = new QTextEdit;
	}
	for (int i = 0; i < m_user_count; ++i) {
		m_message_board->addWidget(m_user_text_edit[i]);
		m_user_text_edit[i]->append(m_user_name[i]);
		m_user_text_edit[i]->setReadOnly(true);
	}
	m_current_user_name = new QLabel;
	set_current_user();
	m_left_left_layout->addWidget(m_current_user_name);	
	m_left_left_layout->addLayout(m_message_board);
	m_left_left_layout->addWidget(m_message_text);
}

void messenger_window::create_left_right_layout()
{
    m_left_right_layout = new QVBoxLayout;
    m_send_button = new QPushButton();
	QIcon icon("./gui/icons/send.png");
	m_send_button->setIconSize(QSize(20,30));
	m_send_button->setIcon(icon);
    m_left_right_layout->addStretch();
    m_left_right_layout->addWidget(m_send_button);
}

void messenger_window::create_left_side()
{
	m_left_widget = new QWidget;
	m_left_layout = new QHBoxLayout;
	create_left_left_layout();
	create_left_right_layout();
	m_left_layout->addLayout(m_left_left_layout);
	m_left_layout->addLayout(m_left_right_layout);
	m_left_widget->setLayout(m_left_layout);
}

void messenger_window::create_right_side()
{
	m_right_widget = new QWidget;
	m_right_layout = new QVBoxLayout;
	QLabel *ob = new QLabel("<h2><i>ONLINE USERS</i></h2>");
	m_logout = new QPushButton();
	QIcon icon("./gui/icons/logout.png");
	m_logout->setIcon(icon);
	QHBoxLayout* t = new QHBoxLayout;
	t->addWidget(ob);
	t->addStretch();
	t->addWidget(m_logout);
	m_right_layout->addLayout(t);
	m_online_users = new QListWidget();
	//m_list_widget_item.reserve(m_user_count);
	for (int i = 0; i < m_user_count; ++i) {
		m_list_widget_item.push_back(new QListWidgetItem);
	}
	assert(m_list_widget_item.size() == m_user_count);
	for (int i = 0; i < m_user_count; ++i) {
		QIcon icon("./gui/icons/user.png");
		m_list_widget_item[i]->setIcon(icon);
		m_list_widget_item[i]->setText(m_user_name[i]);
		m_list_widget_item[i]->setSizeHint(QSize(50, 50));
		m_online_users->addItem(m_list_widget_item[i]);
	}
	m_right_layout->addWidget(m_online_users);
	m_right_widget->setLayout(m_right_layout);
}

void messenger_window::send_message()
{
	if ( !(m_message_text->toPlainText().isEmpty()) ) {
		QString msg = "->\n"+m_message_text->toPlainText()+"\n";
		m_user_text_edit[m_current_user]->setTextColor(QColor(0,0,0));
		m_user_text_edit[m_current_user]->append(msg);
		//emit
		QString to(m_user_name[m_current_user]);
		QString m(m_message_text->toPlainText());
		emit send_message_to_client(to, m);
		m_message_text->clear();
	}
}

void messenger_window::receive_message(const QString& f, const QString& m)
{
	int index = m_user_name.indexOf(f);
	m_user_text_edit[index]->setTextColor(QColor(139,0,0));
	m_user_text_edit[index]->append("<-\n" + m + "\n");
	if (m_current_user != index) {
		m_list_widget_item[index]->setTextColor(QColor(255,0,0));
	}
}

void messenger_window::refresh_show_online_users(const QVector<QString>& o)
{
	for (int i = 0; i < m_list_widget_item.size(); ++i) {
        assert(0 != m_list_widget_item[i]);
		m_list_widget_item[i]->setHidden(true);
	}
	int j = -1;
	for (int i = 0; i < o.size(); ++i) {
		if (m_user_name.contains(o[i])) {
			j = m_user_name.indexOf(o[i]);
			m_list_widget_item[j]->setHidden(false);
		} else {
			++m_user_count;
			m_user_name << o[i];
			QTextEdit* t = new QTextEdit;
			m_user_text_edit.push_back(t);
			int q = m_user_text_edit.size()-1;
			m_message_board->addWidget(m_user_text_edit[q]);
			QListWidgetItem* a = new QListWidgetItem;
			QIcon icon("./gui/icons/user.png");
			a->setIcon(icon);
			a->setText(m_user_name[q]);
			a->setSizeHint(QSize(50,50));
			a->setHidden(false);
			m_list_widget_item.push_back(a);
			int b = m_list_widget_item.size()-1;
			m_online_users->addItem(m_list_widget_item[b]);
		}	
	}
}

void messenger_window::connect_signal_slot()
{
    assert(0 != m_send_button);
    assert(0 != m_online_users);
    assert(0 != m_logout);
	QObject::connect(m_send_button, SIGNAL(clicked()),
            this, SLOT(send_message()));
	QObject::connect(m_online_users, SIGNAL(currentRowChanged(int)),
            this, SLOT(set_current_user(int)));
	QObject::connect(m_online_users, SIGNAL(currentRowChanged(int)),
            m_message_board, SLOT(setCurrentIndex(int)));
	QObject::connect(m_online_users, SIGNAL(currentRowChanged(int)),
            this, SLOT(set_color_black(int)));
	QObject::connect(m_logout, SIGNAL(clicked()),
            this, SIGNAL(logout()));
}

void messenger_window::set_current_user(int i)
{
	m_current_user = i;
	QString tmp;
	tmp.append("<h2><font color=green>");
	tmp.append(m_user_name[i]);
	tmp.append("</font></h2>");
	m_current_user_name->setText(tmp);
}

void messenger_window::set_color_black(int i)
{
    assert(i < m_list_widget_item.size());
    assert(0 != m_list_widget_item[i]);
	m_list_widget_item[i]->setTextColor(QColor(0, 0, 0));
}

