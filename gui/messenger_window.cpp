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

messenger_window::messenger_window(QWidget* parent) :QDialog(parent)
{
	current_user = -1;
	user_count = 10;
	user_name = new QString[user_count];

	create_left_side();
	create_right_side();
	connect_signal_slot();
	create_main_layout();

	QRect rec = QApplication::desktop()->screenGeometry();
	int width = rec.width();
	right_widget -> setMaximumWidth(width/5);	
	left_widget  -> setMaximumWidth(width/2);	
	setLayout(main_layout);
}

void messenger_window::create_main_layout()
{
	main_layout = new QHBoxLayout;
	//main_layout -> addStretch();
	main_layout -> addWidget(left_widget);
	//main_layout -> addStretch(); 
	main_layout -> addWidget(right_widget);

}

void messenger_window::create_left_left_layout()
{
	left_left_layout = new QVBoxLayout;
	message_board = new QStackedLayout;

	message_text = new QTextEdit;
	QScrollBar *sb = message_text -> verticalScrollBar();
	sb -> setValue(sb->maximum());
	message_text -> setFixedHeight(50);
	//   ---- new Func
	vector = new QTextEdit[user_count];
	for (int i = 0; i < user_count; ++i) {
		message_board -> addWidget(vector+i);
		vector[i].append("User "+QString::number(i));
		vector[i].setReadOnly(true);
	}
	left_left_layout -> addLayout(message_board);
	left_left_layout -> addWidget(message_text);

}

void messenger_window::create_left_right_layout()
{
    left_right_layout = new QVBoxLayout;

    send_button = new QPushButton("send");


    left_right_layout -> addStretch();
    left_right_layout -> addWidget(send_button);

}

void messenger_window::create_left_side()
{
	left_widget = new QWidget;    //----- 
	left_layout = new QHBoxLayout;
	
	create_left_left_layout();
	create_left_right_layout();
	left_layout -> addLayout(left_left_layout);
	left_layout -> addLayout(left_right_layout);
	left_widget -> setLayout(left_layout); //-----
}

void messenger_window::create_right_side()
{
	right_widget = new QWidget; //-----

	right_layout = new QVBoxLayout;
	QLabel *ob = new QLabel("<h2><i>ONLINE USERS</i></h2>");
	right_layout -> addWidget(ob);

	//   ---- new func
	online_users = new QListWidget();
	list_widget_item = new QListWidgetItem[user_count];

	for(int i = 0; i < user_count; ++i){
		QIcon icon("/home/student/Desktop/QT/porc/user.png");
		QString user_name;
		user_name.append("User ");
		user_name.append(QString::number(i));

		list_widget_item[i].setIcon(icon);
		list_widget_item[i].setText(user_name);
		list_widget_item[i].setSizeHint(QSize(50,50));

		online_users->addItem( &list_widget_item[i]);
	}
	right_layout -> addWidget(online_users);

	right_widget -> setLayout(right_layout); //----
}

void messenger_window::send_message()
{
    QString msg = message_text -> toPlainText();

    /*if ( !msg.isEmpty() && !(current_user == -1) ) {
        QLabel *lab = new QLabel;

        //QPixmap pix("/home/student/Desktop/Qt1/project_1/msg.png");
        lab -> setStyleSheet("background-color: rgb(220,220,220)");
        lab -> setMargin(7);

        lab -> setFrameStyle(QFrame::StyledPanel |QFrame::Shadow_Mask);
        lab -> setText(msg);


        QHBoxLayout *lay = new QHBoxLayout;
        lay -> addStretch();
        lay -> addWidget(lab);
        user_layout[current_user].addLayout(lay);
        message_text -> clear();
    }*/

}

void messenger_window::connect_signal_slot()
{
    QObject::connect(send_button,SIGNAL(clicked()),this,SLOT(send_message()));

    QObject::connect(online_users,SIGNAL(currentRowChanged(int)),this,SLOT(set_current_user(int)));
    QObject::connect(online_users,SIGNAL(currentRowChanged(int)),message_board,SLOT(setCurrentIndex(int)));

}

void messenger_window::set_current_user(int i)
{
    current_user = i;
}
