#include "log_in_window.h"

//#include <QApplication>

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QErrorMessage>
#include <unistd.h>

#define HORIZONTAL_MOVE_LIMIT 20

log_in_window::log_in_window(QWidget* p)
    : QDialog(p)
{
	create_username_layout();
	create_passwd_layout();
	create_button_layout();
	create_error_layout();
	connect_signal_slot();
	create_main_layout();
}

void log_in_window::checking_login_fields(const QString& s)
{
	if (uname_line_edit->text().isEmpty() ||
            upasswd_line_edit->text().isEmpty()) {
		login_button->setEnabled(false);
	} else {
		login_button->setEnabled(true);
	}
}

void log_in_window::checkin_login()
{
	emit login(uname_line_edit->text(), upasswd_line_edit->text());
}

void log_in_window::create_username_layout()
{
	uname_label = new QLabel("User name");
	uname_line_edit = new QLineEdit;
	uname_layout = new QHBoxLayout;
	uname_layout->addWidget(uname_label);
	uname_layout->addWidget(uname_line_edit);
}

void log_in_window::create_passwd_layout()
{
	upasswd_label = new QLabel("Password");
	upasswd_line_edit = new QLineEdit;
	upasswd_line_edit ->setEchoMode(QLineEdit::Password);
	upasswd_layout = new QHBoxLayout;
	upasswd_layout -> addWidget(upasswd_label);
	upasswd_layout -> addStretch();
	upasswd_layout -> addWidget(upasswd_line_edit);
}

void log_in_window::create_error_layout()
{
	error_layout = new QHBoxLayout;
	error_label  = new QLabel(/*"Erro"*/);
	error_layout->addWidget(error_label);
}

void log_in_window::show_login_error(const QString &s)
{
	error_label->setAlignment(Qt::AlignRight);
	error_label->setText(s);
	QRect r = geometry();
	int x = r.x();
	int y = r.y();
	for (int i = 0; i < 70; ++i) {
		move(r.x() + HORIZONTAL_MOVE_LIMIT, r.y());
		sleep(0.8);
		move(x, y);
		move(r.x() - HORIZONTAL_MOVE_LIMIT, r.y());
	}
	move(x,y);
}

void log_in_window::create_button_layout()
{
	reg_button = new QPushButton("Registration");
	login_button = new QPushButton("LogIn");
	login_button -> setEnabled(false);
	butt_layout = new QHBoxLayout;
	butt_layout -> addWidget(reg_button);
	butt_layout -> addWidget(login_button);
}

void log_in_window::create_main_layout()
{
	QVBoxLayout* reg_layout = new QVBoxLayout;
	reg_layout->addLayout(uname_layout);
	reg_layout->addLayout(upasswd_layout);
	reg_layout->addLayout(error_layout);
	reg_layout->addLayout(butt_layout);
	setLayout(reg_layout);
	setWindowTitle("ITC Local Messenger");
	setFixedHeight(sizeHint().height());
	setFixedWidth(sizeHint().width());
}

void log_in_window::connect_signal_slot()
{
	QObject::connect(uname_line_edit,SIGNAL(textChanged(const QString&)),
			this, SLOT(checking_login_fields(const QString&)));
	QObject::connect(upasswd_line_edit,SIGNAL(textChanged(const QString&)),
			this, SLOT(checking_login_fields(const QString&)));
	QObject::connect(login_button, SIGNAL(clicked()),
			this, SLOT(checkin_login()));
}

