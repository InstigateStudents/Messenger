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

messenger_window::messenger_window(const QStringList& l) :QDialog()
{
	m_current_user = 0;
	m_user_count = l.count();
	//m_user_name = new QString[m_userm_user_count];
	m_user_name = l;

	create_left_side();
	create_right_side();
	connect_signal_slot();
	create_main_layout();

	QRect rec = QApplication::desktop()->screenGeometry();
	int width = rec.width();
	m_right_widget -> setMaximumWidth(width/5);	
	m_left_widget  -> setMaximumWidth(width/2);	
	setLayout(m_main_layout);
}

void messenger_window::create_main_layout()
{
	m_main_layout = new QHBoxLayout;
	//m_main_layout -> addStretch();
	m_main_layout -> addWidget(m_left_widget);
	//m_main_layout -> addStretch(); 
	m_main_layout -> addWidget(m_right_widget);

}

void messenger_window::create_left_left_layout()
{
	m_left_left_layout = new QVBoxLayout;
	m_message_board = new QStackedLayout;

	m_message_text = new QTextEdit;
	QScrollBar *sb = m_message_text -> verticalScrollBar();
	sb -> setValue(sb->maximum());
	m_message_text -> setFixedHeight(50);
	//   ---- new Func
	m_user_text_edit = new QTextEdit[m_user_count];
	for (int i = 0; i < m_user_count; ++i) {
		m_message_board -> addWidget(m_user_text_edit+i);
		//m_user_name[i].append("User ");
		//m_user_name[i].append(QString::number(i));

		m_user_text_edit[i].append(m_user_name[i]);
		m_user_text_edit[i].setReadOnly(true);
	}
	//
	m_current_user_name = new QLabel;

	set_current_user();

	m_left_left_layout -> addWidget(m_current_user_name);	
	m_left_left_layout -> addLayout(m_message_board);
	m_left_left_layout -> addWidget(m_message_text);

}

void messenger_window::create_left_right_layout()
{
    m_left_right_layout = new QVBoxLayout;

    m_send_button = new QPushButton("send");


    m_left_right_layout -> addStretch();
    m_left_right_layout -> addWidget(m_send_button);

}

void messenger_window::create_left_side()
{
	m_left_widget = new QWidget;    //----- 
	m_left_layout = new QHBoxLayout;
	
	create_left_left_layout();
	create_left_right_layout();
	m_left_layout -> addLayout(m_left_left_layout);
	m_left_layout -> addLayout(m_left_right_layout);
	m_left_widget -> setLayout(m_left_layout); //-----
}

void messenger_window::create_right_side()
{
	m_right_widget = new QWidget; //-----

	m_right_layout = new QVBoxLayout;
	QLabel *ob = new QLabel("<h2><i>ONLINE USERS</i></h2>");
	m_right_layout -> addWidget(ob);

	//   ---- new func
	m_online_users = new QListWidget();
	m_list_widget_item = new QListWidgetItem[m_user_count];

	for(int i = 0; i < m_user_count; ++i){
		QIcon icon("/home/student/Desktop/Messenger/gui/user.png");
		//QString m_user_name;
		//m_user_name.append("User ");
		//m_user_name.append(QString::number(i));

		m_list_widget_item[i].setIcon(icon);
		m_list_widget_item[i].setText(m_user_name[i]);
		m_list_widget_item[i].setSizeHint(QSize(50,50));

		m_online_users -> addItem( &m_list_widget_item[i]);
	}
	m_right_layout -> addWidget(m_online_users);

	m_right_widget -> setLayout(m_right_layout); //----
}

void messenger_window::send_message()
{

	if ( !(m_message_text -> toPlainText().isEmpty()) /*!msg.isEmpty() */ ) {

		QString msg = ">>>>\n"+m_message_text -> toPlainText()+"\n";
		//m_user_text_edit[m_current_user].setAlignment(Qt::AlignRight);
		m_user_text_edit[m_current_user].setTextColor(QColor(0,0,0));
		m_user_text_edit[m_current_user].append(msg);
		m_message_text -> clear();
		receive_messege(m_current_user,"Hello!!");
	}
}

void messenger_window::receive_messege(/*const QString& from*/int i, const QString& msg)
{
	
		m_user_text_edit[m_current_user].setAlignment(Qt::AlignLeft);
		m_user_text_edit[m_current_user].setTextColor(QColor(255,0,0));
	m_user_text_edit[m_current_user].append("<<<<\n"+msg+"\n");

	/*int index = -1;
	for ( int i = 0; i < m_user_count; ++i) {
		if (m_user_name[i] == from) {
			index = i;
			break;
		}
	}*/
	//todo
	//m_user_text_edit[m_user_name];
 	
}

void messenger_window::connect_signal_slot()
{
	QObject::connect(m_send_button,SIGNAL(clicked()),this,SLOT(send_message()));

	QObject::connect(m_online_users,SIGNAL(currentRowChanged(int)),this,SLOT(set_current_user(int)));
	QObject::connect(m_online_users,SIGNAL(currentRowChanged(int)),m_message_board,SLOT(setCurrentIndex(int)));

}

void messenger_window::set_current_user(int i)
{
	m_current_user = i;
	
	QString tmp;
	tmp.append("<h2><font color=green>");
	tmp.append(m_user_name[i]);
	tmp.append("</font></h2>");
	m_current_user_name -> setText(tmp);
}
