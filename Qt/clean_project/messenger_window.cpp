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
#include <iostream>

messenger_window::messenger_window(QWidget* parent) :QDialog(parent)
{
    current_user = -1;
    user_count = 10;
    user_name = new QString[user_count];
    user_layout = new QVBoxLayout[user_count];



    create_left_side();
    create_right_side();
    connect_signal_slot();
    create_main_layout();

    setLayout(main_layout);
}

void messenger_window::create_main_layout()
{
    main_layout = new QHBoxLayout;

    //main_layout -> addLayout(left_layout);
    main_layout -> addStretch();
    //main_layout -> addLayout(right_layout);

    main_layout -> addWidget(left_widget);
    main_layout -> addStretch();
    main_layout -> addWidget(right_widget);

}

void messenger_window::create_left_top_layout()
{
    left_top_layout = new QStackedLayout;


    for (int i = 0; i < user_count; ++i) {
        QWidget *tmp = new QWidget;
        user_layout[i].addStretch();
        tmp->setLayout(user_layout+i);
        left_top_layout -> addWidget(tmp);
    }



}

void messenger_window::create_left_bottom_layout()
{
    left_bottom_layout = new QHBoxLayout;

    message_text = new QTextEdit;
    QScrollBar *sb = message_text -> verticalScrollBar();
    sb -> setValue(sb->maximum());
    message_text -> setFixedHeight(50);
    send_button = new QPushButton("send");


    left_bottom_layout -> addStretch();
    left_bottom_layout -> addWidget(message_text);
    left_bottom_layout -> addWidget(send_button);
    left_bottom_layout -> addStretch();

}

void messenger_window::create_left_side()
{
    left_widget = new QWidget;    //-----

    left_layout = new QVBoxLayout();





    create_left_top_layout();
    create_left_bottom_layout();

    left_layout -> addLayout(left_top_layout);
    left_layout -> addLayout(left_bottom_layout);

    left_widget -> setLayout(left_layout); //-----

}

void messenger_window::create_right_side()
{
    right_widget = new QWidget; //-----

    right_layout = new QVBoxLayout;
    QLabel *ob = new QLabel("<h2><i>ONLINE USERS</i></h2>");
    right_layout -> addWidget(ob);

    online_users = new QListWidget();

    for(int i = 0; i < user_count; ++i){
        user_name[i].append("User ");
        user_name[i].append(QString::number(i));
        online_users -> addItem(user_name[i]);
    }
    right_layout -> addWidget(online_users);

    right_widget -> setLayout(right_layout); //----
}

void messenger_window::send_message()
{
    QString msg = message_text -> toPlainText();

    if ( !msg.isEmpty() && !(current_user == -1) ) {
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
    }

}

void messenger_window::connect_signal_slot()
{
    QObject::connect(send_button,SIGNAL(clicked()),this,SLOT(send_message()));

    QObject::connect(online_users,SIGNAL(currentRowChanged(int)),this,SLOT(set_current_user(int)));
    QObject::connect(online_users,SIGNAL(currentRowChanged(int)),left_top_layout,SLOT(setCurrentIndex(int)));

}

void messenger_window::set_current_user(int i)
{
    current_user = i;
}
